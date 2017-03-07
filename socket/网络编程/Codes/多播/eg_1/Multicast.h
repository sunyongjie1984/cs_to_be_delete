// Multicast.h: interface for the CMulticast class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTICAST_H__F8C251C5_3D66_4515_9DED_E93E01F10C5D__INCLUDED_)
#define AFX_MULTICAST_H__F8C251C5_3D66_4515_9DED_E93E01F10C5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <winsock2.h> //注意这里的include文件顺序
#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class CMulticast
{
public:
	CMulticast();
	virtual ~CMulticast();

	int		Initialize(	int af,
						int type,
						int protoco	);
	
	int		SetSockOpt(	int level,
						int optname,
						const char FAR * optval,
						int optlen	);

	int		Bind(	const struct sockaddr FAR *addr,
					int namelen	);

	int		Send_n(	const char FAR * buf,
					int len,
					int flags,
					const struct sockaddr FAR *to,
					int tolen	);
	
	int		Rece_n(	char FAR * buf,
					int len,
					int flags,
					struct sockaddr FAR *from,
					int FAR * fromlen	);

	void	SetAddr(sockaddr_in &local,
					short sin_family,
					u_short hostshort,
					const char FAR * cp);

	void	SetAddr(sockaddr_in &local,
					short sin_family,
					u_short hostshort,
					u_long S_addr);
	
	void	SetMreg(ip_mreq &mreq,
					u_long S_addr,
					const char FAR * cp);
protected:
	WSAData m_wsaData;
	SOCKET m_socket;
	BOOL m_bStartUp_Flag;
	
private:
};

#endif // !defined(AFX_MULTICAST_H__F8C251C5_3D66_4515_9DED_E93E01F10C5D__INCLUDED_)
