// LisnSocket.cpp : implementation file
//

#include "stdafx.h"
#include "chatserver.h"
#include "LisnSocket.h"
#include "chatserverView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLisnSocket

CLisnSocket::CLisnSocket(CChatserverView *pvew)
{
	p_view=pvew;
}

CLisnSocket::~CLisnSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CLisnSocket, CSocket)
	//{{AFX_MSG_MAP(CLisnSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CLisnSocket member functions

void CLisnSocket::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	p_view->Accept();
}
