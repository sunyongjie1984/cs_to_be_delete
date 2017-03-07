#if !defined(AFX_PROXYSOCKET_H__F1A524AF_55AE_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_PROXYSOCKET_H__F1A524AF_55AE_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProxySocket.h : header file
//

#if !defined(SOCK5_PROXY_CONST)
#define SOCK5_PROXY_CONST

#define SOCKS_VER		0x05

#define METHOD_AUTH_NO		0x00
#define METHOD_AUTH			0x02
#define METHOD_GSSAPI		0x01
#define METHOD_NO_ACCEPT	0xFF

#define CMD_CONNECT			0x01
#define CMD_BIND			0x02
#define CMD_UDP				0x03

#define FIELD_RSV			0x00

#define ATYP_IPV4			0x01
#define ATYP_DOMAINNAME		0x03
#define ATYP_IPV6			0x04

#define REP_SUCCESS			0x00
#define REP_FAIL_GENERAL	0x01
#define REP_CONNECT_DENY	0x02
#define REP_UNREACHABLE		0x03
#define REP_HOST_NOTFIND	0x04
#define REP_REFUSED			0x05
#define	REP_TTL_EXPIRED		0x06
#define REP_NOT_SUPPORT		0x07
#define REP_ATYP_NOTSUPPORT 0x08

#define BUFF_SIZE 1024

#endif //!defined(SOCK5_PROXY_CONST)

class CAsyncProxySocket;
/////////////////////////////////////////////////////////////////////////////
// CProxySocket command target

class CProxySocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CProxySocket();
	virtual ~CProxySocket();

// Overrides
public:
	BOOL ProxyAccept(CAsyncProxySocket& rConnectedSock, SOCKADDR* lpSockAddr = NULL, int* lpSockAddrLen = NULL );
	BOOL ProxyListen();
	static struct in_addr GetIpByHost(char *szHost);
	BOOL ProxyConnect(CString addr, unsigned short port, CString proxyaddr, 
						LONG proxyport,	CString User, CString Pass, int mode);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProxySocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CProxySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	int m_mode;
	CString m_strSend;

	CString m_strServer;
	CString m_strUser;
	CString m_strPass;
	unsigned short m_nPort;
	CString m_strRemote;
	unsigned short m_nPortRemote;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROXYSOCKET_H__F1A524AF_55AE_11D5_B587_00E04C39B036__INCLUDED_)
