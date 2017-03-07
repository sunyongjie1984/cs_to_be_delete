#include "../public/poll.h"


xpoll_handle * g_iocp;


DWORD WINAPI ServerWorkerThread(LPVOID CompletionPort);



int main(int argc, char* argv[])
{
	SYSTEM_INFO siSys;
	DWORD nThreadID;
	int i = 0;

	if (xsocket_init())
	{
		return -1;
	}
	if (xpollcb_open(&g_iocp))
	{
		return -1;
	}
	//获取CPU数目
	GetSystemInfo(&siSys);
	for (i = 0;i<(int)1; i++)//NumberOfProcessors
	{
		HANDLE hThread;
		hThread = CreateThread(NULL, 0, ServerWorkerThread, NULL, 0, &nThreadID);
		CloseHandle(hThread);
	}
	xsocket_handle * acceptor;
	if (xsocket_tcp_acceptor_create(&acceptor, 9999, 5, 1))
	{
		return -1;
	}
	xsocket_handle * channel;
	while(true)
	{
		//接收用户连接，被和完成端口关联
		xsocket_accept(&channel, acceptor);

		//关联SOCKET和完成端口
		xpollcb_insert(g_iocp, channel, 24);
	}
	xsocket_close(acceptor);
	getchar();
	return 0;
}




DWORD WINAPI ServerWorkerThread(LPVOID CompletionPort)
{
	char			* buff = NULL;
	unsigned long	len = 0;
	xsocket_handle	* channel = NULL;

	while(true)
	{
		//等待完成端口上SOCKET的完成
		xpollcb_await(g_iocp, &channel, INFINITE);

		switch (channel->OperationType)
		{
		case RECV_POSTED:
			xpoll_read(channel, &buff, &len);

			free(buff);
			buff = (char *)malloc(1024);
			sprintf(buff, "hello world");
			xpoll_write(channel, buff, 1024);
			continue;
		case SEND_POSTED:
			break;
		}
		xpoll_read_mailing(channel, 24);
	}
}