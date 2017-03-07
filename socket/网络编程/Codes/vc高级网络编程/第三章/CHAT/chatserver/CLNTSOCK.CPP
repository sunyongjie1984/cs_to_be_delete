// clntsock.cpp : implementation of the CClientSocket class
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
#include "clntsock.h"
#include "srvrdoc.h"
#include "message.h"

/////////////////////////////////////////////////////////////////////////////
// CClientSocket Construction

CClientSocket::CClientSocket(CServerDoc* pDoc)
{
	m_pDoc = pDoc;
	m_nMsgCount = 0;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
	needdel=false;
}

/////////////////////////////////////////////////////////////////////////////
// CClientSocket Operations

void CClientSocket::Init()
{
	m_pFile = new CSocketFile(this);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
}

void CClientSocket::Abort()
{
	if (m_pArchiveOut != NULL){
		m_pArchiveOut->Abort();
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
	}
}

void CClientSocket::SendMsg(CMessage* pMsg)
{
	if (m_pArchiveOut != NULL){
		pMsg->Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}

void CClientSocket::ReceiveMsg(CMessage* pMsg)
{
	pMsg->Serialize(*m_pArchiveIn);
}

/////////////////////////////////////////////////////////////////////////////
// CClientSocket Overridable callbacks

void CClientSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);

	m_pDoc->ProcessPendingRead(this);
}

BOOL CClientSocket::HasConnectionDropped( void )
{
	BOOL bConnDropped = FALSE;
	INT iRet = 0;
	BOOL bOK = TRUE;
	
	struct timeval timeout = { 0, 0 };
	fd_set readSocketSet;
	
	FD_ZERO( &readSocketSet );
	FD_SET( m_hSocket, &readSocketSet );
	
	iRet = ::select( 0, &readSocketSet, NULL, NULL, &timeout );
	bOK = (iRet > 0);
	
	if(bOK){
		bOK = FD_ISSET( m_hSocket, &readSocketSet );
	}
	
	if( bOK ){
		CHAR szBuffer[1] = "";
		iRet = ::recv( m_hSocket, szBuffer, 1, MSG_PEEK );
		bOK = ( iRet > 0 );
		if( !bOK ){
			INT iError = ::WSAGetLastError();
			bConnDropped = ( ( iError == WSAENETRESET ) ||
				( iError == WSAECONNABORTED ) ||
				( iError == WSAECONNRESET ) ||
				( iError == WSAEINVAL ) ||
				( iRet == 0 ) ); //Graceful disconnect from other side.
		}
	}
	return( bConnDropped );
}

/////////////////////////////////////////////////////////////////////////////
// CSocket Implementation

CClientSocket::~CClientSocket()
{
	if (m_pArchiveOut != NULL)
		delete m_pArchiveOut;

	if (m_pArchiveIn != NULL)
		delete m_pArchiveIn;

	if (m_pFile != NULL)
		delete m_pFile;
}

#ifdef _DEBUG
void CClientSocket::AssertValid() const
{
	CSocket::AssertValid();
}

void CClientSocket::Dump(CDumpContext& dc) const
{
	CSocket::Dump(dc);
}
#endif //_DEBUG

IMPLEMENT_DYNAMIC(CClientSocket, CSocket)
