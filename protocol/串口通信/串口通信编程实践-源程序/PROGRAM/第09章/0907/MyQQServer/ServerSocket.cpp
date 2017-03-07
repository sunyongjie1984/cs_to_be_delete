// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MyQQServer.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ServerSocket

ServerSocket::ServerSocket()
{
}

ServerSocket::~ServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(ServerSocket, CSocket)
	//{{AFX_MSG_MAP(ServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// ServerSocket member functions

void ServerSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CClientSocket * m_pNewClient = new CClientSocket(); //创建Socket处理连接
	ASSERT(m_pNewClient != NULL);
	Accept(*m_pNewClient);


	CSocket::OnAccept(nErrorCode);
}
