// Multicast.cpp: implementation of the CMulticast class.
//
//////////////////////////////////////////////////////////////////////

#include "Multicast.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMulticast::CMulticast()
{
	m_bStartUp_Flag = TRUE;
	
	if( WSAStartup(MAKEWORD(2,2), &m_wsaData) != 0 )
	{
		m_bStartUp_Flag = FALSE;			
	}
}

CMulticast::~CMulticast()
{
	if (m_bStartUp_Flag)
	{
		WSACleanup();
	}
}

int CMulticast::Initialize(int af, int type, int protoco)
{
	m_socket = socket(af, type, protoco); //创建一个UDP套接口
	
	if (SOCKET_ERROR == m_socket)
	{
		m_bStartUp_Flag = FALSE;
		WSACleanup();
		return -1;
	}
	return 0;
}

int CMulticast::SetSockOpt(int				level,
						   int				optname,
						   const char FAR * optval,
						   int				optlen)
{
	int ret = setsockopt(m_socket, level, optname, optval, optlen);
	
	if( ret == SOCKET_ERROR )
	{
		m_bStartUp_Flag = FALSE;
		WSACleanup();	
		return -1;
	}
	return 0;
}

int CMulticast::Bind(const struct sockaddr FAR *addr, int namelen)
{
	int ret = bind(m_socket, addr, namelen);
	
	if( ret == SOCKET_ERROR )
	{
		m_bStartUp_Flag = FALSE;
		WSACleanup();
		return -1;
	}
	return 0;
}

int CMulticast::Send_n(const char FAR * buf,
					   int				len,
					   int				flags,
					   const struct sockaddr FAR *to,
					   int				tolen)
{
	int ret = 0;

	for (int transfer_bytes = 0; transfer_bytes < len; transfer_bytes += ret)
	{		
		ret = sendto(	m_socket,
						buf + transfer_bytes,
						len - transfer_bytes,
						flags,
						to,
						tolen	);

		if (ret == 0 || ret == -1)
		{
			return ret;
		}
	}
	return transfer_bytes;
}

int CMulticast::Rece_n(char FAR		* buf,
					   int			len,
					   int			flags,
					   struct sockaddr FAR *from,
					   int FAR		* fromlen)
{
	int ret = 0;
	
	for (int transfer_bytes = 0; transfer_bytes < len; transfer_bytes += ret)
    {
		ret = recvfrom(m_socket, buf, len, flags, from, fromlen);
	
		if (0 == ret || SOCKET_ERROR == ret)
		{
			//do_read在用户直接回车发送了一个空字符串或接收失败
			return ret;
		}
	}
	buf[ret] = '\0';
	
	return 0;
}

void CMulticast::SetAddr(sockaddr_in	&local,
						 short			sin_family,
						 u_short		hostshort,
						 const char FAR * cp)
{
	memset(&local, 0, sizeof(local));
	
	local.sin_family		= sin_family;
	local.sin_port			= htons(hostshort);
	local.sin_addr.s_addr	= inet_addr (cp);
}

void CMulticast::SetAddr(sockaddr_in	&local,
						 short			sin_family,
						 u_short		hostshort,
						 u_long			S_addr)
{
	memset(&local, 0, sizeof(local));
	
	local.sin_family			= sin_family;
	local.sin_port				= htons(hostshort);
	local.sin_addr.S_un.S_addr	= S_addr;
}

void CMulticast::SetMreg(ip_mreq		&mreq,
						 u_long			S_addr,
						 const char FAR * cp)
{
	memset(&mreq, 0, sizeof(mreq));
	
	mreq.imr_interface.S_un.S_addr = S_addr;
	mreq.imr_multiaddr.S_un.S_addr = inet_addr(cp);
}