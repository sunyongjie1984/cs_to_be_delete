// ChatClientDoc.cpp : implementation of the CChatClientDoc class
//

#include "stdafx.h"
#include "ChatClient.h"

#include "ChatClientDoc.h"
#include "CntrItem.h"
#include "ChatSocket.h"
#include "chatclientview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SAFEDELETE(x) if(x!=NULL){delete x;x=NULL;}
#define WM_ADDLIST    WM_USER + 1001

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc

IMPLEMENT_DYNCREATE(CChatClientDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CChatClientDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CChatClientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc construction/destruction

CChatClientDoc::CChatClientDoc()
{
	m_bConnected = FALSE;
	m_pSocket = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
	m_bFilter = FALSE;
}

CChatClientDoc::~CChatClientDoc()
{
	msg.type = -2;
	msg.m_bClose = TRUE;
	msg.from = m_strHandle;
	msg.to = "所有人";
	msg.secret = FALSE;
	msg.m_strText ="Hello";
	msg.color = RGB(0,136,255); 
	SendMsg();

	SAFEDELETE(m_pArchiveIn);
	SAFEDELETE(m_pArchiveOut);
	SAFEDELETE(m_pFile);
	SAFEDELETE(m_pSocket);
}

BOOL CChatClientDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CChatClientDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CChatClientCntrItem(preo, (CChatClientDoc*) this);
}

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc serialization

void CChatClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc diagnostics

#ifdef _DEBUG
void CChatClientDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CChatClientDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatClientDoc commands

void CChatClientDoc::ProcessPendingRead()
{
	do
	{
		ReceiveMsg();
		if (m_pSocket == NULL)
			return;
	}
	while(!m_pArchiveIn->IsBufferEmpty());
}

BOOL CChatClientDoc::ConnectSocket(LPCTSTR lpszHandle, LPCTSTR lpszAddress, LPCTSTR m_strImage, UINT nPort)
{
	if(m_bConnected)
		return FALSE;
	m_strHandle = lpszHandle;

	SAFEDELETE(m_pArchiveIn);
	SAFEDELETE(m_pArchiveOut);
	SAFEDELETE(m_pFile);
	SAFEDELETE(m_pSocket);

	if(m_pSocket == NULL){
		m_pSocket = new CChatSocket(this);
		ASSERT(m_pSocket != NULL);
	}

	if (!m_pSocket->Create())
	{
		delete m_pSocket;
		m_pSocket = NULL;
		TRACE("Create Socket Error!\n");
		return FALSE;
	}

	while (!m_pSocket->Connect(lpszAddress, nPort))
	{
		if (AfxMessageBox(IDS_RETRYCONNECT,MB_YESNO) == IDNO)
		{
			delete m_pSocket;
			m_pSocket = NULL;
			return FALSE;
		}
	}

	m_pFile = new CSocketFile(m_pSocket);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
	
	msg.type = -1;
	msg.m_bClose = FALSE;
	msg.from = m_strHandle;
	msg.to = "所有人";
	msg.secret = FALSE;
	msg.m_strText ="Hello";
	msg.color = RGB(0,136,255); 
	msg.image = atoi(m_strImage);

	SendMsg();
	m_bConnected = TRUE;
	GetView()->GetParent()->SetWindowText(m_strHandle);
	return TRUE;
}

void CChatClientDoc::SendMsg()
{
	msg.from = m_strHandle;
	if (m_pArchiveOut != NULL)
	{
		TRY
		{
			msg.Serialize(*m_pArchiveOut);
			m_pArchiveOut->Flush();
		}
		CATCH(CFileException, e)
		{
			m_pArchiveOut->Abort();
			delete m_pArchiveOut;
			m_pArchiveOut = NULL;
		
			CString strTemp;
			if (strTemp.LoadString(IDS_SERVERRESET))
				DisplayMsg(strTemp);
		}
		END_CATCH
	}
}

void CChatClientDoc::DisplayMsg(LPCTSTR lpszText)
{
	CChatClientView* pView = (CChatClientView*)GetView();

	if(pView != NULL)
		pView->TextOut(lpszText, RGB(128,0,0));
}

void CChatClientDoc::ReceiveMsg()
{
	TRY
	{
		msg.Serialize(*m_pArchiveIn);
		DisplayRecMsg(msg.type, msg.from, msg.to, msg.secret, 
				msg.m_strText, msg.color);
		if(msg.type == -7 || msg.type == -2 || msg.type == -9)
			m_bConnected = FALSE;
		if(msg.type == -9)
			DisplayMsg("该用户名已经有人使用，请更名重新登录!\n");
	}
	CATCH(CFileException, e)
	{
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort();
		
		CString strTemp;
		if (strTemp.LoadString(IDS_SERVERRESET))
			DisplayMsg(strTemp);
		if (strTemp.LoadString(IDS_CONNECTIONCLOSED))
			DisplayMsg(strTemp);
	}
	END_CATCH
		
	if(msg.m_bClose && (msg.from == m_strHandle)){
		SAFEDELETE(m_pArchiveIn);
		SAFEDELETE(m_pArchiveOut);
		SAFEDELETE(m_pFile);
		SAFEDELETE(m_pSocket);
		m_bConnected = FALSE;
	}
	if((msg.type == -1 && msg.from != m_strHandle) || (msg.type == -8)){
		GetView()->GetParent()->SendMessage(WM_ADDLIST, (LPARAM)&(msg.from), msg.image);
	}
	if((msg.type == -7) || (msg.type == -2)){
		GetView()->GetParent()->SendMessage(WM_ADDLIST + 1, (LPARAM)&(msg.from), msg.image);
	}
}

void CChatClientDoc::DisplayRecMsg(int type, CString from, CString to,
		BOOL sec, CString str, COLORREF clr)
{
	CChatClientView* pView = (CChatClientView*)GetView();

	if(type == -7){
		pView->TextOut(_T("系统：聊天室掌门人以一招'佛山无影脚',将"),RGB(0,0,0));
		if(from == m_strHandle){
			pView->TextOut(_T("你"),RGB(0,0,255));
		}
		else
			pView->TextOut(from,RGB(0,0,255));
		pView->TextOut(_T("踢出门外\r\n"),RGB(0,0,0));
	}   
	if(type == -5){
		return;	
	}
	if(type == -3){
		pView->TextOut(_T("系统：服务器已关闭!"),RGB(0,0,0));
		return;
	}
	if(type == -1 ){
		pView->TextOut(from, RGB(0,0,255));
		pView->TextOut(_TEXT("风尘仆仆地推门而入\r\n"),RGB(255,0,0));
	}
	if(type == -2){
		pView->TextOut(from, RGB(0,0,255));
		pView->TextOut(_TEXT("静静地离开了，孤单的背影显得格外潇洒\r\n"),RGB(255,0,0));
	}
	if(type >= 0){
		if(from == m_strHandle || to == m_strHandle || sec == FALSE || to =="所有人")
			talk(type, from, to, str, clr);			
	}
}

void CChatClientDoc::talk(int type, CString form, CString to,
						  CString str, COLORREF clr)
{
	CChatClientView* pView = (CChatClientView*)GetView();
	
	if(form != m_strHandle && to != m_strHandle && m_bFilter)
		return;
	CString temp,to2,first,second;
	
	if(type > 32 || type < 0) 
		return;  
	temp.LoadString(IDS_TALK0 + type);	
	int i=temp.Find(",");
	if(i != -1){
		first = temp.Left(i);
		if(i != temp.GetLength() - 1){
			second = temp.Mid(i + 1);
			second += "：";
		}
		else{
			second="：";
		}
		pView->TextOut((LPCTSTR)form, RGB(0,0,255));
		pView->TextOut((LPCTSTR)first, RGB(0,0,0));
		pView->TextOut((LPCTSTR)to, RGB(0,0,255));
		pView->TextOut((LPCTSTR)second, RGB(0,0,0));
		pView->TextOut((LPCTSTR)str,clr);
		pView->TextOut((LPCTSTR)"\r\n",clr);
	}
	else{
		first=temp;
		second="： ";
		pView->TextOut(form,RGB(0,0,255));
		pView->TextOut(first,RGB(0,0,0));
		pView->TextOut(second,RGB(0,0,0));
		pView->TextOut(str,clr);
		pView->TextOut("\r\n",clr);
	}
}

void CChatClientDoc::Disconnect()
{
	msg.type = -2;
	msg.m_bClose = TRUE;
	msg.from = m_strHandle;
	msg.to = "所有人";
	msg.secret = FALSE;
	msg.m_strText ="Hello";
	msg.color = RGB(0,136,255); 

	SendMsg();
	m_bConnected = FALSE;
	msg.from = "DUMP";
	GetView()->GetParent()->SendMessage(WM_ADDLIST + 1, (LPARAM)&(msg.from), msg.image);
}
