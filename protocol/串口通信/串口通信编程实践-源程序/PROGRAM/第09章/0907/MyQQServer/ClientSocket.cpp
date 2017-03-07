// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MyQQServer.h"
#include "MyQQServerDlg.h"
#include "ClientSocket.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

extern CMyMyQQServerApp theApp;

void CClientSocket::OnReceive(int nErrorCode) 
{	
	// TODO: Add your specialized code here and/or call the base class
	CMyMyQQServerDlg *pDlg = (CMyMyQQServerDlg*)AfxGetMainWnd();
	Message m_Message;
	memset(&m_Message,0,sizeof(m_Message));
	Receive(&m_Message,sizeof(m_Message));

	CString strUserName = m_Message.strName;
	CString strClientName = m_Message.strClientName;


	if(m_Message.iType == FIRSTLOG)
	{
		
		CPtrList * m_pClientList = theApp.m_pClientSocketList;//Socket链表
		int iCount = m_pClientList->GetCount();
		POSITION pos = m_pClientList ->GetHeadPosition();

		CString strUserName = m_Message.strName;
		CString strClientName = m_Message.strClientName;
	
		if(pos)
		{	
			for(int i = 0; i < m_pClientList ->GetCount(); i++)
			{
				CClientSocket *m_pClientSocket = static_cast < CClientSocket *>(m_pClientList->GetNext(pos));
				if(m_pClientSocket->GetUserName() == strUserName)
				{
					Message msObj;
					memset(&msObj,0,sizeof(Message));
					msObj.iType = SYSERROR;
					msObj.iSubType = USEREXSIT;
					Send(&msObj,sizeof(Message));
					return;
				}
				else
				{
					Message msObj1;
					memset(&msObj1,0,sizeof(Message));
					msObj1.iType = USERLOG;
					msObj1.iSubType = USERLOGIN;
					CString strTemp;
					strTemp = m_pClientSocket->GetUserName();
					int len = strTemp.GetLength();
					lstrcpy(msObj1.strName,strTemp.GetBuffer(len));
					Send(&msObj1,sizeof(Message));
				}
			
			}
	
		
		}

		iCount = m_pClientList->GetCount();
		pos = m_pClientList ->GetHeadPosition();


		if(pos)
		{
			for(int i = 0; i < m_pClientList ->GetCount(); i++)
			{
				CClientSocket *m_pClientSocket = static_cast < CClientSocket *>(m_pClientList->GetNext(pos));
				m_Message.iType = USERLOG;
				m_Message.iSubType = USERLOGIN;
			    m_pClientSocket->Send(&m_Message,sizeof(Message));
											
			}
		}


		SetUserName(m_Message.strName);
		theApp.m_pClientSocketList->AddTail(this);
		CString sList;
		sList = m_Message.strName;
		pDlg->m_SendNameCtrl.AddString(sList);
		sList = sList + " 登陆了";
		pDlg->m_ClientList.InsertString(0,sList);

	}

	else
	{
		if(m_Message.iType == USERSESSION)
		{
			if(m_Message.iSubType == SAYINPRIVATE)
			{
				CPtrList * m_pClientList = theApp.m_pClientSocketList;
				int iCount = m_pClientList->GetCount();
				POSITION pos = m_pClientList ->GetHeadPosition();
				if(pos)
				{	for(int i = 0; i < m_pClientList ->GetCount(); i++)
					{
						CClientSocket *m_pClientSocket = static_cast < CClientSocket *>(m_pClientList->GetNext(pos));
						CString strName = m_pClientSocket ->GetUserName();
						if(strName == strClientName )
						{
							m_pClientSocket->Send(&m_Message,sizeof(Message));
							
							CString strOut;
							strOut.Format("%d %d %s\n",m_Message.iType,m_Message.iSubType,m_Message.strName);
							TRACE0(strOut);
							return;
						}
						
					}
				}
			}
			if(m_Message.iSubType == USERQUIT)
			{
				CPtrList * m_pClientList = theApp.m_pClientSocketList;
				int iCount = m_pClientList->GetCount();
				POSITION pos = m_pClientList ->GetHeadPosition();
				POSITION tempos = pos;
				if(pos)
				{	 
					for(int i = 0; i < m_pClientList ->GetCount(); i++)
					{
						tempos = pos;
						CClientSocket *m_pClientSocket = static_cast < CClientSocket *>(m_pClientList->GetNext(pos));
						if(m_pClientSocket ->GetUserName() == strUserName)
						{
							m_pClientSocket ->ShutDown();
							m_pClientSocket ->Close();
							delete m_pClientSocket;
							m_pClientList->RemoveAt(tempos);
							pDlg->m_ClientList.InsertString(0,strUserName+" 退出了");
							for(int j=0 ;j<pDlg->m_SendNameCtrl.GetCount();j++)
							{
								CString strName;
								pDlg->m_SendNameCtrl.GetLBText(j,strName);
								if(strName == strUserName)
								{
									pDlg->m_SendNameCtrl.DeleteString(j);
									break;
								}//if
							}//for
							break;
						}//if
						
					}//for
				}//if(pos)

				m_Message.iType = USERLOG;
				m_Message.iSubType = USERLOGOUT;					
			
				m_pClientList = theApp.m_pClientSocketList;
				pos = m_pClientList ->GetHeadPosition();
				if(pos)
				{
					CClientSocket *  m_pClientSocket;
					for(int i = 0; i < m_pClientList ->GetCount(); i++)
					{
						m_pClientSocket = static_cast < CClientSocket *>(m_pClientList->GetNext(pos));
						m_pClientSocket ->Send(&m_Message,sizeof(Message));
						
						Sleep(100);
						
					}
				}
			//	g_cs.Unlock();
			}//if(m_Message.iSubType == USERQUIT)
		}//if(m_Message.iType == USERSESSION)
	}//else

	


	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::SetUserName(CString sName)
{
	m_UserName = sName;
}

CString CClientSocket::GetUserName()
{
	return m_UserName;
}

