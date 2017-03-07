// MainSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MyQQClient.h"
#include "MyQQClientDlg.h"
#include "MainSocket.h"
#include "Message.h"
#include "TypeDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainSocket

CMainSocket::CMainSocket()
{
}

CMainSocket::~CMainSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMainSocket, CSocket)
	//{{AFX_MSG_MAP(CMainSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMainSocket member functions

void CMainSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMyMyQQClientDlg * pWnd = static_cast <CMyMyQQClientDlg *>(AfxGetMainWnd());
	Message msContent;
	int iLen1 = sizeof(msContent);	
	int iLen2 = sizeof(Message);
	memset(&msContent,0,sizeof(msContent));
	int iLen = Receive(&msContent,sizeof(msContent));
	pWnd->SendMessage(WM_RECEIVEMESSAGE,WPARAM(&msContent),0);
	CSocket::OnReceive(nErrorCode);
}

void CMainSocket::SetUserName(CString sName)
{
	m_UserName = sName;
}

CString CMainSocket::GetUserName()
{
	return m_UserName;
}

void CMainSocket::SendMessage(CString UserName, CString strMessage)
{

	Message msObj;
	msObj.iType = USERSESSION;
	msObj.iSubType = SAYINPRIVATE;
	CString strTemp = UserName;
	int iLen = strTemp.GetLength();
	iLen > 20 ? 20 : iLen;
	lstrcpy(msObj.strClientName,strTemp.GetBuffer(iLen));

	strTemp = m_UserName;
	iLen = strTemp.GetLength();
	iLen > 20 ? 20 : iLen;
	lstrcpy(msObj.strName,strTemp.GetBuffer(iLen));

	strTemp = strMessage;
	iLen = strTemp.GetLength();
	iLen > 1024 ? 1024 : iLen;
	lstrcpy(msObj.strContent,strTemp.GetBuffer(iLen));
	
//	msObj.iImage = m_image;
	Send(&msObj,sizeof(msObj));
}

