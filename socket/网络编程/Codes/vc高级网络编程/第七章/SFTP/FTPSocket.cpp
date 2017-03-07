// FTPSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SFTP.h"
#include "FTPSocket.h"
#include "SFTPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPSocket

CFTPSocket::CFTPSocket()
{
	m_pDoc = NULL;
}

CFTPSocket::~CFTPSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CFTPSocket, CSocket)
	//{{AFX_MSG_MAP(CFTPSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CFTPSocket member functions

void CFTPSocket::OnReceive(int nErrorCode) 
{
	if(m_pDoc != NULL)
		m_pDoc->Receive();
	
	CSocket::OnReceive(nErrorCode);
}
