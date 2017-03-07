// ChatSocket.cpp: implementation of the CChatSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{

}

CChatSocket::CChatSocket(CChatClientDoc* pDoc)
{
	ASSERT(pDoc != NULL);
	m_pDoc = pDoc;
}

void CChatSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);

	m_pDoc->ProcessPendingRead();
}
