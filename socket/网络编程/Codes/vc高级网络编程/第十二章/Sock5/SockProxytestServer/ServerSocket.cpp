// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions

void CServerSocket::OnAccept(int nErrorCode) 
{
	char* buf = "Good morning!";

	CSocket t;
	SOCKADDR addr;
	int len = sizeof(SOCKADDR);
	if (Accept(t, &addr, &len)){
		int n = t.Send(buf, strlen(buf), 0);
		if(m_udp.m_hSocket != NULL)
			m_udp.Close();
		m_udp.Create(1230, SOCK_STREAM, FD_READ | FD_WRITE);
		//m_udp.Bind(&addr,len);// 1230, "");
		m_udp.Bind(1230, "10.12.11.74");
	}
	CSocket::OnAccept(nErrorCode);
}
