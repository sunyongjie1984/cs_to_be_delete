// UDPSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "UDPSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDPSocket

CUDPSocket::CUDPSocket()
{
}

CUDPSocket::~CUDPSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUDPSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CUDPSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUDPSocket member functions

void CUDPSocket::OnReceive(int nErrorCode) 
{
	
	CAsyncSocket::OnReceive(nErrorCode);
}
