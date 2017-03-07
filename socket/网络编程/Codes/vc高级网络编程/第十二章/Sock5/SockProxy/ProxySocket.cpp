// ProxySocket.cpp : implementation file
//

#include "stdafx.h"
#include "SockProxy.h"
#include "ProxySocket.h"
#include "asyncproxysocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProxySocket

CProxySocket::CProxySocket()
{
	m_mode = 0;
}

CProxySocket::~CProxySocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CProxySocket, CSocket)
	//{{AFX_MSG_MAP(CProxySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CProxySocket member functions

BOOL CProxySocket::ProxyConnect(CString addr, unsigned short port, 
								CString proxyaddr, LONG proxyport,
								CString User, CString Pass, int mode)
{
	BOOL bRet = FALSE;
	in_addr sa;
	m_mode = mode;

	m_strServer = proxyaddr;
	m_strRemote = addr;
	m_nPort = (unsigned short)proxyport;
	m_nPortRemote = port;
	m_strUser = User;
	m_strPass = Pass;

	bRet = Connect(proxyaddr, proxyport);
	if(!bRet){
		TRACE("Cann't connect to the proxy server!\n");
		return FALSE;
	}
	char send[3];

	m_strSend.Empty();
	m_strSend = _T("");

	send[0] = SOCKS_VER;
	send[1] = 0x01;
	send[2] = METHOD_AUTH;

	int num = Send(send, 3);
	if(num != 3){
		TRACE("Send negotiate command error!\n");
		return FALSE;
	}
	char szReadBuf[BUFF_SIZE];

	memset(szReadBuf, 0, BUFF_SIZE);
	num = Receive(szReadBuf, BUFF_SIZE);
	if(num == 0){
		TRACE("Maybe the server is not properly open!\n");
		return FALSE;
	}
	if(szReadBuf[0] == SOCKS_VER && szReadBuf[1] == METHOD_AUTH){
		m_strSend += (char)1;
		m_strSend += (char)User.GetLength();
		m_strSend += User;
		m_strSend += (char)Pass.GetLength();
		m_strSend += Pass;
		int len =m_strSend.GetLength();
		char* p = m_strSend.GetBuffer(0);
		num = Send(p, len);
		m_strSend.ReleaseBuffer();
		if(num == 0){
			TRACE("Send Authority negotiate command error!\n");
			return FALSE;
		}
		memset(szReadBuf, 0, BUFF_SIZE);
		num = Receive(szReadBuf, BUFF_SIZE);
		if(num == SOCKET_ERROR || num == 0){
			TRACE("error:%d\n", GetLastError());
			return FALSE;
		}
		if(szReadBuf[0] != 1 || szReadBuf[1] != 0){
			AfxMessageBox("Your Username or Password is invalid!");
			return FALSE;
		}
		unsigned short pt = htons(port);
		TRACE("The server has passed your authoritory!\n");
		memset(szReadBuf, 0, BUFF_SIZE);
		szReadBuf[0] = SOCKS_VER;
		szReadBuf[1] = mode;//CMD_CONNECT;
		szReadBuf[2] = FIELD_RSV;
		sa = GetIpByHost(addr.GetBuffer(0));
		addr.ReleaseBuffer(0);
		if(sa.s_addr != INADDR_NONE){
			szReadBuf[3] = ATYP_IPV4;
			memcpy(szReadBuf + 4, &sa, 4);
			memcpy(szReadBuf + 8, &pt, 2);
			len = 10;
		}
		else{
			szReadBuf[3] = ATYP_DOMAINNAME;
			len = szReadBuf[4] = addr.GetLength();
			memcpy(szReadBuf + 5, addr.GetBuffer(0), szReadBuf[4]);
			addr.ReleaseBuffer();
			memcpy(szReadBuf + len + 5, &pt, 2);
			len = len + 7;
		}
		num = Send(szReadBuf, len);
		if(num == 0){
			TRACE("Send Authority negotiate command error!\n");
			return FALSE;
		}
		memset(szReadBuf, 0, BUFF_SIZE);
		num = Receive(szReadBuf, BUFF_SIZE, 0);
		if(num == SOCKET_ERROR || num == 0){
			TRACE("Connection to remote host error!\n");
			return FALSE;
		}
		if(szReadBuf[1] != REP_SUCCESS){
			TRACE("Connect to remote address failed,error code:%d\n", szReadBuf[1]);
			return FALSE;
		}
	}
	return TRUE;
}

struct in_addr CProxySocket::GetIpByHost(char *szHost)
{
	struct in_addr in;
	if (szHost == NULL)
	{
		in.s_addr = INADDR_NONE;
	}
	else
	{
		unsigned long addr = inet_addr(szHost);
		if (addr == INADDR_NONE)
		{
			LPHOSTENT lphost;
			lphost = gethostbyname(szHost);
			if (lphost != NULL)
				in = *(LPIN_ADDR)*(lphost->h_addr_list);
			else
				in.s_addr = INADDR_NONE;
		}
		else
			in.s_addr = addr;
	}
	return in;
}

BOOL CProxySocket::ProxyListen()
{
	int num = 0;
	char szReadBuf[BUFF_SIZE];
	memset(szReadBuf, 0, BUFF_SIZE);

	if(m_mode == CMD_BIND){
		while(1){
			num = Receive(szReadBuf, BUFF_SIZE);
			if(szReadBuf[1] != REP_SUCCESS){
				TRACE("Connect to remote address failed!\n");
				return FALSE;
			}
			if(szReadBuf[1] == REP_SUCCESS)
				break;
		}
	}
	else{
		TRACE("This function can only called by bind socket,else will cause failure!\n");
		return FALSE;
	}
	return TRUE;
}

BOOL CProxySocket::ProxyAccept(CAsyncProxySocket &rConnectedSock, 
							   SOCKADDR *lpSockAddr, int *lpSockAddrLen)
{
	rConnectedSock.m_mode = m_mode;
	rConnectedSock.m_nPort = m_nPort;
	rConnectedSock.m_nPortRemote = m_nPortRemote;
	rConnectedSock.m_strPass = m_strPass;
	rConnectedSock.m_strRemote = m_strRemote;
	rConnectedSock.m_strSend = m_strSend;
	rConnectedSock.m_strUser = m_strUser;
	
	//return Accept(rConnectedSock, lpSockAddr, lpSockAddrLen);
	rConnectedSock.m_hSocket = m_hSocket;
	return TRUE;
}
