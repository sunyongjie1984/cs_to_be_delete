// TestIOCP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InitSock.h"

CInitSock theSock;

#define BUFFER_SIZE 1024

typedef struct _PER_HANDLE_DATA
{
	SOCKET s;  //对应的套接字句柄
	sockaddr_in addr;  //客户端IP地址
}PER_HANDLE_DATA, *PPER_HANDLE_DATA;

typedef struct _PER_IO_DATA
{
	OVERLAPPED ol; //重叠结构
	char buf[BUFFER_SIZE]; //数据缓冲区
	int nOperationType;  //操作类型
#define OP_READ 1
#define OP_WRITE 2
#define OP_ACCEPT 3
}PER_IO_DATA, *PPER_IO_DATA;

DWORD WINAPI ServerThread(LPVOID lpParam);

int main(int argc, char* argv[])
{
	int nPort = 4567; 

	//创建完成端口对象
	HANDLE hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	::CreateThread(NULL, 0, ServerThread, (LPVOID)hCompletion, 0, 0);

	//创建监听套接字
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN si;
	si.sin_family = AF_INET;
	si.sin_port = ::ntohs(nPort);
	si.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(sListen, (sockaddr*)&si, sizeof(si));
	::listen(sListen, 5);

	//循环处理到来的连接
	while (TRUE)
	{
		//等待接受未决的连接请求
		SOCKADDR_IN saRemote;
		int nRemoteLen = sizeof(saRemote);
		SOCKET sNew = ::accept(sListen, (sockaddr*)&saRemote, &nRemoteLen);
		//接受到新的连接后，为他创建一个per-handle数据，并将它们关联到端口对象
		PPER_HANDLE_DATA pPerHandle = (PPER_HANDLE_DATA)::GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		pPerHandle->s = sNew;
		memcpy(&pPerHandle->addr, &saRemote, nRemoteLen);
		::CreateIoCompletionPort((HANDLE)pPerHandle->s, hCompletion, (DWORD)pPerHandle, 0);
		//投递一个接受请求
		PPER_IO_DATA pPerIO = (PPER_IO_DATA)::GlobalAlloc(GPTR, sizeof(PER_IO_DATA));
		pPerIO->nOperationType = OP_READ;
		WSABUF buf;
		buf.buf = pPerIO->buf;
		buf.len = BUFFER_SIZE;
		DWORD dwRecv;
		DWORD dwFlags = 0;
		::WSARecv(pPerHandle->s, &buf, 1, &dwRecv, &dwFlags, &pPerIO->ol, NULL);
	}
	return 0;
}

DWORD WINAPI ServerThread(LPVOID lpParam)
{
	//得到完成端口对象的句柄
	HANDLE hCompletion = (HANDLE)lpParam;
	DWORD dwTrans;
	PPER_HANDLE_DATA pPerhandle;
	PPER_IO_DATA pPerIO;
	while (TRUE)
	{
		//在关联到此端口的所有套接字上等待IO端口完成
		BOOL bOk = ::GetQueuedCompletionStatus(hCompletion, 
			&dwTrans, (LPDWORD)&pPerhandle, (LPOVERLAPPED*)&pPerIO, WSA_INFINITE);

		if (bOk != TRUE)  //此套接字上有错误发生
		{
			::closesocket(pPerhandle->s);
			::GlobalFree(pPerhandle);
			::GlobalFree(pPerIO);
			continue;
		}

		if (dwTrans == 0 && (pPerIO->nOperationType == OP_READ || 
			pPerIO->nOperationType == OP_WRITE))  //此套接字被对方关闭
		{
			::closesocket(pPerhandle->s);
			::GlobalFree(pPerhandle);
			::GlobalFree(pPerIO);
			continue;
		}

		switch (pPerIO->nOperationType) //看看是什么类型的IO请求完成了
		{
		case OP_READ: //完成一个接收请求
			{
				pPerIO->buf[dwTrans] = '\0';
				printf(pPerIO->buf);
				//继续投递IO请求
				pPerIO->nOperationType = OP_READ;
				WSABUF buf;
				buf.buf = pPerIO->buf;
				buf.len = BUFFER_SIZE;
				DWORD dwFlags = 0;
				::WSARecv(pPerhandle->s, &buf, 1, &dwTrans, &dwFlags, &pPerIO->ol, NULL);
			}
			break;
			//以下两个请求并未实现
		case OP_ACCEPT:
			break;
		case OP_WRITE:
			break;
		}
	}
	return 0;
}

