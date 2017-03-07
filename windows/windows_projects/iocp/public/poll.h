#ifndef __POLL_H__
#define __POLL_H__


#include "sockets.h"



struct xpoll_handle
{
    HANDLE iocp_handle;
};


int xpoll_read_mailing(xsocket_handle * channel, unsigned long len)
{
	unsigned long dwFlags = 0;
	unsigned long numberOfBytesRecvd;

	channel->OperationType = RECV_POSTED;

	channel->buffers.len = len;
	channel->buffers.buf = (char *)malloc(channel->buffers.len);
	memset(channel->buffers.buf, 0, channel->buffers.len);
	memset(&(channel->overlapped), 0, sizeof(channel->overlapped));
	
	if (SOCKET_ERROR == WSARecv(channel->socketdes, &(channel->buffers), 1, &numberOfBytesRecvd, &dwFlags, &(channel->overlapped), NULL))
		return WSAGetLastError();
	else
		return 0;
}

void xpoll_read(xsocket_handle * channel, char ** buff, unsigned long * len)
{
	if (channel->buffers.buf)
	{
		printf("read [%d][%s]\n", channel->buffers.len, channel->buffers.buf);
		free(channel->buffers.buf);
		channel->buffers.buf = NULL;
		
		*len = 1024;
		*buff = (char *)malloc(*len);
		socket_read(channel, *buff, len);
	}
}

int xpoll_write(xsocket_handle * channel, const char * buff, unsigned long len)
{
	unsigned long dwFlags = 0;
	unsigned long numberOfBytesRecvd;
	
	channel->buffers.buf = (char *)buff;
	channel->buffers.len = len;
	
	memset(&(channel->overlapped), 0, sizeof(channel->overlapped));
	channel->OperationType = SEND_POSTED;
	
	if (SOCKET_ERROR == WSASend(channel->socketdes, &(channel->buffers), 1, &numberOfBytesRecvd, dwFlags, &(channel->overlapped), NULL))
		return WSAGetLastError();
	else
		return 0;
}

int xpoll_create(xpoll_handle ** h)
{
	*h = (xpoll_handle *)malloc(sizeof(xpoll_handle));
	if (*h)
		return 0;
	else
		return -1;
}

int xpoll_destroy(xpoll_handle * h)
{
	if (h)
	{
		free(h);
		return 0;
	}
	return -1;
}

int xpollcb_open(xpoll_handle ** h)
{
	xpoll_create(h);
	(*h)->iocp_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (INVALID_HANDLE_VALUE == (*h)->iocp_handle)
		return WSAGetLastError();
	else
		return 0;
}

int xpollcb_close(xpoll_handle * h)
{
	return xpoll_destroy(h);
}


int xpollcb_insert(xpoll_handle * ph, xsocket_handle * sh, unsigned long len)
{
	//关联SOCKET和完成端口
	if (CreateIoCompletionPort((HANDLE)(sh->socketdes), ph->iocp_handle, (DWORD)sh, 0))
	{
		xpoll_read_mailing(sh, len);
		return 0;
	}
	return WSAGetLastError();
}

int xpollcb_await(xpoll_handle * ph, xsocket_handle ** sh, unsigned long milli_seconds/* = INFINITE*/)
{
	DWORD			BytesTransferred	= 0;
	LPOVERLAPPED	overlapped			= NULL;

	if (GetQueuedCompletionStatus(ph->iocp_handle, &BytesTransferred, (LPDWORD)sh, &overlapped, milli_seconds))
	{
		memcpy(&((*sh)->overlapped), overlapped, sizeof(OVERLAPPED));

		if (0 == BytesTransferred)
		{
			//检查是否有错误产生
			switch ((*sh)->OperationType)
			{
			//关闭SOCKET
			case RECV_POSTED:
			case SEND_POSTED:
				xsocket_close(*sh);
				return -1;
			}
		}
		return 0;
	}
	return -1;
}

#endif//__POLL_H__
