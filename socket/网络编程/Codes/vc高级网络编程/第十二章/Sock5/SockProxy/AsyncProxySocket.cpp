// AsyncProxySocket.cpp : implementation file
//

#include "stdafx.h"
#include "SockProxy.h"
#include "AsyncProxySocket.h"
#include "ProxySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsyncProxySocket

CAsyncProxySocket::CAsyncProxySocket()
{
}

CAsyncProxySocket::~CAsyncProxySocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CAsyncProxySocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CAsyncProxySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CAsyncProxySocket member functions

void CAsyncProxySocket::OnReceive(int nErrorCode) 
{
	CAsyncSocket::OnReceive(nErrorCode);
	if(nErrorCode != 0)
		return;
	char buf[BUFF_SIZE];
	char* p = NULL;

	int num = Receive(buf, BUFF_SIZE, 0);
	if(num == 0 || num == SOCKET_ERROR){
		TRACE("Error in receive UDP message!\n");
		return;
	}
	if(buf[0] == 0 && buf[1] == 0){
		TRACE("Received a UDP Packets!\n");
		switch(buf[2]){
		case ATYP_IPV4:
			p = buf + 10;
			//here add your processing code....
			break;
		case ATYP_DOMAINNAME:
			p = buf + buf[4] + 7;
			//here add your processing code....
			break;
		case ATYP_IPV6:
			p = buf + 22;
			//here add your processing code....
			break;
		}
	}
}

int CAsyncProxySocket::UDPSend(char *buf, int size)
{
	char* lpData = new char[size + 262];
	int len = 0;

	memset(lpData, 0, size + 262);
	lpData[2] = 0;     //不支持帧组合
	in_addr sa = CProxySocket::GetIpByHost(m_strRemote.GetBuffer(0));
	if(sa.s_addr != INADDR_NONE){
		lpData[3] = ATYP_IPV4;
		memcpy(lpData + 4, &sa, 4);
		memcpy(lpData + 8, &m_nPortRemote, 2);
		len = 10;
	}
	else{
		lpData[3] = ATYP_DOMAINNAME;
		len = lpData[4] = m_strRemote.GetLength();
		memcpy(lpData + 5, m_strRemote.GetBuffer(0), lpData[4]);
		m_strRemote.ReleaseBuffer();
		memcpy(lpData + len + 5, &m_nPortRemote, 2);
		len = len + 7;
	}
	memcpy(lpData + len, buf, size);
	int num = Send(lpData, len + size);
	if(num == 0 || num != (len +size)){
		TRACE("Send UDP error!\n");
		delete [] lpData;
		return 0;
	}
	delete [] lpData;
	return len + size;
}
