// chatSocket.cpp : implementation file
//

#include "stdafx.h"
#include "chatserver.h"
#include "chatSocket.h"
#include "ChatserverView.h"
#include "LisnSocket.h"
#include "Mesg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CchatSocket

CchatSocket::CchatSocket(CChatserverView *pview)
{
	m_pview=pview;
	m_pfile=NULL;
	m_in=NULL;
	m_out=NULL;
}

CchatSocket::~CchatSocket()
{
	if(m_in!=NULL)
	{
		delete m_in;
		m_in=NULL;
	}
	if(m_out!=NULL)
	{
		delete m_out;
		m_out=NULL;
	}
	if(m_pfile!=NULL)
	{
		delete m_pfile;
		m_pfile=NULL;
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CchatSocket, CSocket)
	//{{AFX_MSG_MAP(CchatSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CchatSocket member functions

void CchatSocket::Abort()
{
     if( m_out!=NULL)
	 {
		 m_out->Abort();
		 delete m_out;
		 m_out=NULL;
	 }
}

void CchatSocket::init()
{
     m_pfile=new CSocketFile(this);
	 m_in=new CArchive(m_pfile,CArchive::load);
	 m_out=new CArchive(m_pfile,CArchive::store);
	 name="";
}

void CchatSocket::receivemessage(CMesg *msg)
{
    msg->Serialize(*m_in);
}

void CchatSocket::sendmessage(CMesg *msg)
{
	if(m_out!=NULL)
	{
		msg->Serialize(*m_out);
		m_out->Flush();
	}
}

void CchatSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	m_pview->Receive(this);
}
