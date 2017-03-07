// CLientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"
#include "CLientSocket.h"
///////////////////////////////
#include "ChatView.h"
#include "ChatDoc.h"
////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCLientSocket

CCLientSocket::CCLientSocket(CChatView  *view)
{
	p_view=view;
}

CCLientSocket::~CCLientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCLientSocket, CSocket)
	//{{AFX_MSG_MAP(CCLientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCLientSocket member functions

void CCLientSocket::OnReceive(int nErrorCode)
{
      p_view->RecvMsg();
	  CSocket::OnReceive(nErrorCode);
}
