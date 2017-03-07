#ifndef __SOCKETS_H__
#define __SOCKETS_H__


#pragma comment(lib,"ws2_32.lib")


#include <stdio.h>
#include <memory.h>
#include <winsock2.h>


#define RECV_POSTED 1001
#define SEND_POSTED 1002


struct xsocket_handle
{
    SOCKET              socketdes;
	int					family;
    int                 sock_type;		/* SOCK_STREAM, SOCK_DGRAM */
    int                 protocol;
    struct sockaddr_in	local_addr;
	int					local_sa_len;
    struct sockaddr_in	remote_addr;
	int					remote_sa_len;
    int                 timeout_ms;		/* MUST MATCH if timeout > 0 */
    long				timeout;

	int					OperationType;
	OVERLAPPED			overlapped;
	WSABUF				buffers;
	//unsigned long		numberOfBytesRecvd;
};



int xsocket_fini(void)
{
	return WSACleanup();
}

int xsocket_init(void)
{
	WSAData		wsaData	= {0};
	const int	low		= 2;
	const int	high	= 2;
	int			rv		= WSAStartup(MAKEWORD(low, high), &wsaData);
	
	switch (rv)
	{
	case 0:	//0 成功
		if ((low != LOBYTE(wsaData.wVersion)) || (high != HIBYTE(wsaData.wVersion))) {
			xsocket_fini();
			rv = -1;
		}
		break;
	case WSAEINVAL:
		//应用程序指出的Windows Sockets版本不被该DLL支持
	case WSAVERNOTSUPPORTED:
		//所需的Windows Sockets API的版本未由特定的Windows Sockets实现提供
	case WSASYSNOTREADY:
		//网络通信依赖的网络子系统还没有准备好
		break;
	}	
	return rv;
}



int xsocket_create(xsocket_handle ** h)
{
	*h = (xsocket_handle *)malloc(sizeof(xsocket_handle));
	if (*h) {
		(*h)->family		= AF_INET;
		(*h)->protocol		= /*0*/IPPROTO_TCP;
		(*h)->sock_type		= SOCK_STREAM;
		(*h)->local_sa_len	= sizeof((*h)->local_addr);
		(*h)->remote_sa_len	= sizeof((*h)->remote_addr);

		memset(&((*h)->local_addr), 0, (*h)->local_sa_len);
		memset(&((*h)->remote_addr), 0, (*h)->remote_sa_len);

		memset(&((*h)->overlapped), 0, sizeof(OVERLAPPED));
		return 0;
	}
	return -1;
}

int xsocket_destroy(xsocket_handle * h)
{
	if (h)
	{
		delete h;
		return 0;
	}
	return -1;
}


int xsocket_option_set(xsocket_handle * h, const int optval)
{
	typedef struct __tagGTM_OPTION {
		int level;
		int optname;
	} GTM_OPTION;
	
	GTM_OPTION sock_opt[] = {
		{ SOL_SOCKET,	SO_REUSEADDR },
		{ IPPROTO_TCP,	TCP_NODELAY  }
	};
	int opt_len = sizeof(sock_opt)/(sizeof(GTM_OPTION));
	int rv		= -1;
	int i		= 0;
	
	for (i = 0; i < opt_len; i++)
	{
		int rv = setsockopt(h->socketdes, sock_opt->level, sock_opt->optname, (const char *)&optval, sizeof(optval));
		if (0 != rv)
			return -1;
	}
	return 0;
}


void xsocket_local_address_set(xsocket_handle * h, int port)
{
	h->local_addr.sin_family		= h->family;
	h->local_addr.sin_port			= htons(port);
	h->local_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
}

void socket_remote_address_set(xsocket_handle * h, const char * ip, int port)
{
	h->remote_addr.sin_family		= h->family;
	h->remote_addr.sin_port			= htons(port);
	h->remote_addr.sin_addr.s_addr	= inet_addr(ip);
}

int xsocket_open(xsocket_handle ** h)
{
	xsocket_create(h);

	(*h)->socketdes = WSASocket((*h)->family, (*h)->sock_type, (*h)->protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(SOCKET_ERROR == (*h)->socketdes)
	{
		xsocket_destroy(*h);
		*h = NULL;
		return -1;
	}
	return 0;
}

int xsocket_close(xsocket_handle * h)
{
	if (h)
	{
		closesocket(h->socketdes);
		h->socketdes = NULL;
		xsocket_destroy(h);
		return 0;
	}
	return -1;
}

int xsocket_bind(xsocket_handle * h)
{
	int rv = bind(h->socketdes, (struct sockaddr *)&(h->local_addr), h->local_sa_len);
	if (0 != rv) {
		xsocket_close(h);
		return WSAGetLastError();
	}
	return 0;
}

int xsocket_listen(xsocket_handle * h, int backlog)
{
	int rv = listen(h->socketdes, backlog);
	if (0 != rv) {
		xsocket_close(h);
		return WSAGetLastError();
	}
	return 0;
}


int xsocket_accept(xsocket_handle ** channel, xsocket_handle * acceptor)
{
	xsocket_create(channel);
	(*channel)->socketdes = WSAAccept(	acceptor->socketdes,
										(struct sockaddr *)&((*channel)->remote_addr),
										&((*channel)->remote_sa_len),
										NULL,
										0	);

	if (INVALID_SOCKET == (*channel)->socketdes)
	{
		int err = WSAGetLastError();
		if (err)
		{
			xsocket_destroy(*channel);
		}
		return err;
	}
	xsocket_option_set(*channel, 1);
	return 0;
}

int xsocket_tcp_acceptor_create(xsocket_handle ** acceptor, int port, int backlog, int optval)
{
	int rv = xsocket_open(acceptor);
	if (rv)
		return rv;
	rv = xsocket_option_set(*acceptor, optval);
	if (rv)
		return rv;
	xsocket_local_address_set(*acceptor, port);
	rv = xsocket_bind(*acceptor);
	if (rv)
		return rv;
	rv = xsocket_listen(*acceptor, backlog);
	return rv;
}



int socket_connect(xsocket_handle * h)
{
	int rv = connect(h->socketdes, (const struct sockaddr *)&(h->remote_addr), h->remote_sa_len);
	if (0 != rv) {
		xsocket_close(h);
		return WSAGetLastError();
	}
	return 0;
}

int socket_open(xsocket_handle ** h)
{
	xsocket_create(h);
	
	(*h)->socketdes = socket((*h)->family, (*h)->sock_type, (*h)->protocol);
	if(SOCKET_ERROR == (*h)->socketdes)
	{
		xsocket_destroy(*h);
		*h = NULL;
		return -1;
	}
	return 0;
}

int socket_write(xsocket_handle * h, const char * buff, unsigned long len)
{
	unsigned long write_len = send(h->socketdes, buff, len, 0);
	if (write_len == len)
		return 0;
	else
		return -1;
}

int socket_read(xsocket_handle * h, char * buff, unsigned long * len)
{
	unsigned long read_len = *len;

	*len = recv(h->socketdes, buff, read_len, 0);
	if (0 < *len)
		return 0;
	else
		return -1;
}

int xsocket_tcp_connector_create(xsocket_handle ** connector, const char * ip, int port)
{
	int rv = xsocket_open(connector);
	if (rv)
		return rv;
	socket_remote_address_set(*connector, ip, port);
	return socket_connect(*connector);
}

#endif//__SOCKETS_H__
