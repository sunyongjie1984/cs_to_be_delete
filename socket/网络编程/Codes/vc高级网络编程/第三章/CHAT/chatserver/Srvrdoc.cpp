// srvrdoc.cpp : implementation of the CServerDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "chatsrvr.h"

#include "srvrdoc.h"
#include "srvrvw.h"

#include "message.h"
#include "CleanDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerDoc

IMPLEMENT_DYNCREATE(CServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CServerDoc, CDocument)
	//{{AFX_MSG_MAP(CServerDoc)
	ON_COMMAND(ID_CLEAN, OnClean)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_MESSAGES, OnUpdateMessages)
	ON_UPDATE_COMMAND_UI(ID_CONNECTIONS, OnUpdateConnections)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDoc construction/destruction

CServerDoc::CServerDoc()
{
	m_pSocket = NULL;
	m_lCount = 0;
}

CServerDoc::~CServerDoc()
{
	if(m_pSocket != NULL)
		delete m_pSocket;
	m_pSocket = NULL;
}

//
//这里开始打开该端口的网络服务，等待客户的连接
//
BOOL CServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	m_pSocket = new CListeningSocket(this);
	if (m_pSocket->Create(PORT)){
		if (m_pSocket->Listen())
			return TRUE;
	}
	return FALSE;
}

//该函数在有客户连接时关闭服务器时调用
void CServerDoc::DeleteContents() 
{
	delete m_pSocket;
	m_pSocket = NULL;

	CString temp;
	temp="服务器已经关掉!";
	
	CMessage* pMsg = new CMessage;
	while(!m_connectionList.IsEmpty())
	{
		CClientSocket* pSocket = (CClientSocket*)m_connectionList.RemoveHead();
		if(pSocket==NULL ) continue;
		if (pMsg == NULL) continue;
		pMsg->m_bClose = TRUE;
		pMsg->from = pSocket->name;
		pMsg->m_strText = _TEXT("服务器已关闭");
		pMsg->to = _TEXT("所有人");
		pMsg->type = -3;

		SendMsg(pSocket, pMsg);
		
		if(!pSocket->IsAborted())
		{
			pSocket->ShutDown();
			BYTE Buffer[50];
			while (pSocket->Receive(Buffer,50) > 0);
			delete pSocket;
		}
	}
	delete pMsg;

	if (!m_viewList.IsEmpty())
		((CEditView*)m_viewList.GetHead())->SetWindowText(_T(""));

	CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
// CServerDoc serialization

void CServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// CEditView contains an edit control which handles all serialization
		((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CServerDoc diagnostics

#ifdef _DEBUG
void CServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServerDoc Operations

void CServerDoc::UpdateClients()
{
	CMessage* pMsg = AssembleMsg(NULL);
	if(pMsg->type >= 0)
		m_lCount ++;
	for(POSITION pos = m_connectionList.GetHeadPosition(); pos != NULL;){
		CClientSocket* pSocket = (CClientSocket*)m_connectionList.GetNext(pos);

		if (pMsg != NULL)
			SendMsg(pSocket, pMsg);
	}
}

void CServerDoc::ProcessPendingAccept() 
{
	CClientSocket* pSocket = new CClientSocket(this);

	if (m_pSocket->Accept(*pSocket))
	{
		pSocket->Init();
		m_connectionList.AddTail(pSocket);
	}
	else
		delete pSocket;
}

void CServerDoc::ProcessPendingRead(CClientSocket* pSocket)
{
	if(pSocket != NULL)
	{
		do{
			CMessage* pMsg = ReadMsg(pSocket);
			if(pMsg == NULL) return;
			if (pMsg->m_bClose)	
			{
				CloseSocket(pSocket);
				pMsg->m_bClose = FALSE;
				break;
			}
			if(pMsg->type == -1){
				UpdateList(pSocket);
			}
		}
		while (!pSocket->m_pArchiveIn->IsBufferEmpty());
	}	
	UpdateClients();
}

CMessage* CServerDoc::AssembleMsg(CClientSocket* pSocket)
{
	static CMessage msg;
	
	CMessage* tmp;

	tmp = m_lsMsg.RemoveHead();
	if(tmp != NULL)
		memcpy(&msg, tmp, sizeof(CMessage));

	return &msg;
}

CMessage* CServerDoc::ReadMsg(CClientSocket* pSocket)
{
	static CMessage msg;
	CClientSocket* pSock;
	TRY
	{
		pSocket->ReceiveMsg(&msg);
		if(msg.type == -1)
		{
			bool found=false;
			for(POSITION posname=m_connectionList.GetHeadPosition();posname;){				
				pSock = (CClientSocket*)m_connectionList.GetNext(posname);
				if(pSock->name==msg.from ){
					found=true;
					pSocket->needdel=true;
					DelSocket();
					return NULL;
				}
			}
			if(found==false)
			{
				pSocket->name = msg.from;
				pSocket->image = msg.image;
				Message1(msg.from);
				Message1("风尘仆仆地推门而入\r\n");
			}
		}
		if(msg.type == -2)
		{
			Message1(msg.from);
			Message1("静静地离开了，孤单的背影显得格外潇洒\r\n");
		}
		int i = msg.type;
		if(i >= 0 && i <= 32){
			talk(i,msg.from,msg.to,msg.m_strText);
		}
		if(i >= -2 && i <= 32){
			m_lsMsg.AddTail(&msg);
		}
	}
	CATCH(CFileException, e)
	{
		CString strTemp;
		if (strTemp.LoadString(IDS_READERROR))
			Message(strTemp);
		
		msg.m_bClose = TRUE;
		pSocket->Abort();
	}
	END_CATCH
	return &msg;
}

void CServerDoc::SendMsg(CClientSocket* pSocket, CMessage* pMsg)
{
	TRY
	{
		pSocket->SendMsg(pMsg);
	}
	CATCH(CFileException, e)
	{
		pSocket->Abort();

		CString strTemp;
		if (strTemp.LoadString(IDS_SENDERROR))
			Message(strTemp);
	}
	END_CATCH
}

void CServerDoc::CloseSocket(CClientSocket* pSocket)
{
	pSocket->Close();

	POSITION pos,temp;
	for(pos = m_connectionList.GetHeadPosition(); pos != NULL;)
	{
		temp = pos;
		CClientSocket* pSock = (CClientSocket*)m_connectionList.GetNext(pos);
		if (pSock == pSocket){
			m_connectionList.RemoveAt(temp);
			break;
		}
	}

	delete pSocket;
}

void CServerDoc::Message(LPCTSTR lpszMessage)
{
	((CServerView*)m_viewList.GetHead())->Message(lpszMessage);
}

void CServerDoc::Message1(LPCTSTR lpszMessage)
{
	((CServerView*)m_viewList.GetHead())->Message1(lpszMessage);
}
/////////////////////////////////////////////////////////////////////////////
// CServerDoc Handlers

void CServerDoc::OnUpdateMessages(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);

	CString strFmt;
	if (strFmt.LoadString(IDS_MESSAGESFMT))
	{
		CString strTemp;
		wsprintf(strTemp.GetBuffer(50),strFmt,m_lCount);
        strTemp.ReleaseBuffer();
		pCmdUI->SetText(strTemp);
	}
}

void CServerDoc::OnUpdateConnections(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);

	CString strFmt;
	if (strFmt.LoadString(IDS_CONNECTIONSFMT))
	{
		CString strTemp;
		wsprintf(strTemp.GetBuffer(50),strFmt,m_connectionList.GetCount());
		strTemp.ReleaseBuffer();
		pCmdUI->SetText(strTemp);
	}
}

void CServerDoc::talk(int type2, CString from1, CString to1, CString str1)
{
	CString temp,to2,first,second;

	if(type2 > 32 || type2 < 0)
	   return;
	temp.LoadString(IDS_TALK0 + type2);	
	int i=temp.Find(",");
	if(i!=-1){
		first=temp.Left(i);
		if(i!=temp.GetLength()-1){
			second=temp.Mid(i+1);
			second+="：";
		}
		else{
			second="：";
		}
		Message1(from1);
		Message1(first);
		Message1(to1);
		Message1(second);
		Message1(str1);
		Message1("\r\n");
	}
	else{
		first=temp;
		second="： ";
		Message1(from1);
		Message1(first);
		Message1(second);
		Message1(str1);
		Message1("\r\n");
	}
}

void CServerDoc::DelSocket()
{
	CClientSocket* pSock;
	POSITION pos, temp;
	for(pos = m_connectionList.GetHeadPosition(); pos != NULL;)
	{
		temp = pos;
		pSock = (CClientSocket*)m_connectionList.GetNext(pos);
	 	if (pSock->needdel==true)
		{
			m_connectionList.RemoveAt(temp);
			break;
		}
	}
	if(pSock==NULL) 
		return;
	CMessage* pMsg = new CMessage;
	pMsg->from = _TEXT("系统");
	pMsg->to = _TEXT("你");
	pMsg->m_bClose = TRUE;
	pMsg->type = -9;
	pMsg->color = RGB(128,0,222);

	SendMsg(pSock, pMsg);
	if (!pSock->IsAborted()){
		pSock->ShutDown();
		BYTE Buffer[50];
		while (pSock->Receive(Buffer,50) > 0);
		delete pSock;
	}
}

void CServerDoc::OnClean() 
{
	CCleanDlg clean;
    CString name; 
	if(clean.DoModal()==IDOK){
		if(clean.m_cleanname=="") return;
		CClientSocket* pSock;
		POSITION pos, temp,posname;
		bool found=false;
		for(posname = m_connectionList.GetHeadPosition(); posname;)
		{				
			pSock = (CClientSocket*)m_connectionList.GetNext(posname);
			
			if(pSock->name == clean.m_cleanname)
				found=true;
		}
		if(!found){
			Message1("系统:");
			Message1("不能进行'踢'操作!\r\n");
			return;
		}
		//type为-7表示把人踢出站外，先给每个人发一个通知，从在线列表里
		//删除该人，
		CMessage* pMsg = new CMessage;
		for(pos = m_connectionList.GetHeadPosition(); pos != NULL;)
		{
			temp = pos;
			pSock = (CClientSocket*)m_connectionList.GetNext(pos);
			pMsg->m_bClose = FALSE;
			pMsg->type = -7;
			pMsg->from = clean.m_cleanname;
			SendMsg(pSock, pMsg);
		}
		
		//第二次通知该人，你已经被踢出了，同时关闭与它的Socket连接
		for(pos = m_connectionList.GetHeadPosition(); pos != NULL;)
		{
			temp = pos;
			pSock = (CClientSocket*)m_connectionList.GetNext(pos);
			if (pSock->name == clean.m_cleanname)
			{		
				if(pSock == NULL) return;
				pMsg->m_bClose = TRUE;
				pMsg->type = -7;
				pMsg->from = clean.m_cleanname;
				SendMsg(pSock, pMsg);
				m_connectionList.RemoveAt(temp);
				if (!pSock->IsAborted())
				{
					pSock->ShutDown();
					BYTE Buffer[50];
					while (pSock->Receive(Buffer,50) > 0);
					delete pSock;
				}
				
				Message1("系统：聊天室掌门人以一招'佛山无影脚',将");
				Message1(clean.m_cleanname);
				Message1("踢出门外\r\n");
			}
		}
		delete pMsg;
	}
}

void CServerDoc::UpdateList(CClientSocket* pSocket)
{
	CMessage* pMsg = new CMessage;
	for(POSITION pos = m_connectionList.GetHeadPosition(); pos != NULL;){
		CClientSocket* pSock = (CClientSocket*)m_connectionList.GetNext(pos);
		pMsg->from = pSock->name;
		pMsg->type = -8;
		pMsg->image = pSock->image;
		SendMsg(pSocket, pMsg);
	}
}

void CServerDoc::Clean()
{
	OnClean();
}
