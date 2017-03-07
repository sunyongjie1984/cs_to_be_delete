#include <winsock2.h>
#include <windows.h>
#include <stdio.h>


#pragma comment(lib, "ws2_32.lib")



#define PORT 5150
#define DATA_BUFSIZE 8192



//关键项
typedef struct
{
	OVERLAPPED Overlapped;
	WSABUF DataBuf;
	CHAR Buffer[DATA_BUFSIZE];
	DWORD BytesSEND;
	DWORD BytesRECV;
}
PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;

typedef struct 
{
	SOCKET Socket;
}
PER_HANDLE_DATA, * LPPER_HANDLE_DATA;



DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);


void main(void)
{
	SOCKADDR_IN				InternetAddr;
	SOCKET					Listen;
	SOCKET					Accept;
	HANDLE					CompletionPort;
	SYSTEM_INFO				SystemInfo;
	LPPER_HANDLE_DATA		PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	DWORD					i;
	DWORD					RecvBytes;
	DWORD					Flags;
	DWORD					ThreadID;
	WSADATA					wsaData;
	DWORD					Ret;
	
	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return;
	}
	//打开一个空的完成端口
	if ((CompletionPort = CreateIoCompletionPort(
													INVALID_HANDLE_VALUE,
													NULL,
													0,
													0
													)) == NULL)
	{
		printf( "CreateIoCompletionPort failed with error: %d\n", GetLastError());
		return;
	}
	// Determine how many processors are on the system.
	GetSystemInfo(&SystemInfo);
	// 开启cpu个数的2倍个的线程
	for(i = 0; i < SystemInfo.dwNumberOfProcessors * 2; i++)
	{
		HANDLE ThreadHandle;
		// Create a server worker thread and pass the completion port to the thread.
		if ((ThreadHandle = CreateThread(
											NULL,
											0,
											ServerWorkerThread,
											CompletionPort,
											0,
											&ThreadID
											)) == NULL)
		{
			printf("CreateThread() failed with error %d\n", GetLastError());
			return;
		}
		// Close the thread handle
		CloseHandle(ThreadHandle);
	}
	//打开一个服务器socket
	if ((Listen = WSASocket(
							AF_INET,
							SOCK_STREAM,
							0,
							NULL,
							0,
							WSA_FLAG_OVERLAPPED
							)) == INVALID_SOCKET)
	{
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		return;
	} 
	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(PORT);
	
	if (bind(
				Listen,
				(PSOCKADDR)&InternetAddr,
				sizeof(InternetAddr)
				) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return;
	}
	
	if (listen(Listen, 5) == SOCKET_ERROR)
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return;
	}
	//开始接收从客户端来的连接
	while(TRUE)
	{
		if ((Accept = WSAAccept(Listen, NULL, NULL, NULL, 0)) == SOCKET_ERROR)
		{
			printf("WSAAccept() failed with error %d\n", WSAGetLastError());
			return;
		}
		// 创建一个关键项用于保存这个客户端的信息，用户接收发送的重叠结构，
		// 还有使用到的缓冲区
		if ((PerHandleData = (LPPER_HANDLE_DATA)
									GlobalAlloc(
												GPTR, 
												sizeof(PER_HANDLE_DATA)
												)) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			return;
		}
		// Associate the accepted socket with the original completion port.
		printf("Socket number %d connected\n", Accept);
		
		PerHandleData->Socket = Accept;

		//与我们的创建的那个完成端口关联起来,将关键项也与指定的一个完成端口关联
		if (CreateIoCompletionPort(
									(HANDLE) Accept,
									CompletionPort,
									(DWORD)PerHandleData,
									0
									) == NULL)
		{
			printf("CreateIoCompletionPort failed with error %d\n", GetLastError());
			return;
		}

		// 投递一次接收，由于接收都需要使用这个函数来投递一个接收的准备
		if ((PerIoData = (LPPER_IO_OPERATION_DATA)
							GlobalAlloc(
										GPTR,
										sizeof(PER_IO_OPERATION_DATA)
										)) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			return;
		}
		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));

		PerIoData->BytesSEND	= 0;
		PerIoData->BytesRECV	= 0;
		PerIoData->DataBuf.len	= DATA_BUFSIZE;
		PerIoData->DataBuf.buf	= PerIoData->Buffer;
		Flags					= 0;

		if (WSARecv(
					Accept,
					&(PerIoData->DataBuf),
					1,
					&RecvBytes,
					&Flags,
					&(PerIoData->Overlapped),
					NULL
					) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				printf("WSARecv() failed with error %d\n", WSAGetLastError());
				return;
			}
		}
	}
}



//工作线程
DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
	HANDLE					CompletionPort = (HANDLE) CompletionPortID;
	DWORD					BytesTransferred;
	LPOVERLAPPED			Overlapped = NULL;
	LPPER_HANDLE_DATA		PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	DWORD					SendBytes, RecvBytes;
	DWORD					Flags;
	
	while(TRUE)
	{
		//完成端口有消息来了
		if (GetQueuedCompletionStatus(
										CompletionPort,
										&BytesTransferred,
										(LPDWORD)&PerHandleData,
										(LPOVERLAPPED *)&PerIoData,
										INFINITE
										) == 0)
		{
			printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());
			return 0;
		}
		
		//是不是有人退出了
		if (BytesTransferred == 0)
		{
			printf("Closing socket %d\n", PerHandleData->Socket);
			if (closesocket(PerHandleData->Socket) == SOCKET_ERROR)
			{
				printf("closesocket() failed with error %d\n", WSAGetLastError());
				return 0;
			}
			GlobalFree(PerHandleData);
			GlobalFree(PerIoData);
			continue;
		}
		//
		if (PerIoData->BytesRECV == 0)
		{
			PerIoData->BytesRECV = BytesTransferred;
			PerIoData->BytesSEND = 0;
		}
		else
		{
			PerIoData->BytesSEND += BytesTransferred;
		}
		if (PerIoData->BytesRECV > PerIoData->BytesSEND)
		{
			// Post another WSASend() request.
			// Since WSASend() is not gauranteed to send all of the bytes requested,
			// continue posting WSASend() calls until all received bytes are sent.
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
			PerIoData->DataBuf.buf = PerIoData->Buffer + PerIoData->BytesSEND;
			PerIoData->DataBuf.len = PerIoData->BytesRECV - PerIoData->BytesSEND;
			
			if (WSASend(
						PerHandleData->Socket,
						&(PerIoData->DataBuf),
						1,
						&SendBytes,
						0,
						&(PerIoData->Overlapped),
						NULL
						) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSASend() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
		}
		else
		{
			PerIoData->BytesRECV = 0;
			// Now that there are no more bytes to send post another WSARecv() request.
			Flags = 0;

			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
			
			PerIoData->DataBuf.len = DATA_BUFSIZE;
			PerIoData->DataBuf.buf = PerIoData->Buffer;

			if (WSARecv(
						PerHandleData->Socket,
						&(PerIoData->DataBuf),
						1,
						&RecvBytes,
						&Flags,
						&(PerIoData->Overlapped),
						NULL
						) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSARecv() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
		}
	}
}
