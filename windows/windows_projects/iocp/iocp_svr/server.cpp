#pragma hdrstop

//---------------------------------------------------------------------------
//#pragma argsused
#pragma comment(lib,"ws2_32.lib")
#include <stdio.h>
#include <memory.h>
#include <winsock2.h>
#include <iostream>
using namespace std;

#define RECV_POSTED 1001
#define SEND_POSTED 1002

int Init();

HANDLE hCompletionPort;
typedef struct _PER_HANDLE_DATA
{
	SOCKET sock;
}PER_HANDLE_DATA,* LPPER_HANDLE_DATA;

typedef struct _PER_IO_OPERATION_DATA
{
	OVERLAPPED Overlapped;
	WSABUF DataBuff;
	char Buff[24];
	BOOL OperationType;
}PER_IO_OPERATION_DATA,* LPPER_IO_OPERATION_DATA;

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPort);

int main(int argc, char* argv[])
{
	LPPER_HANDLE_DATA perHandleData;
	LPPER_IO_OPERATION_DATA ioperdata;
	SYSTEM_INFO siSys;
	SOCKET sockListen;
	struct sockaddr_in addrLocal;
	//char buf[24];
	int nRet = 0;
	DWORD nThreadID;
	SOCKET sockAccept;
	DWORD dwFlags = 0;
	DWORD dwRecvBytes;
	int nReuseAddr = 1;

	cout<<"初始环境..."<<endl;
	if(Init() != 0)
		return -1;

	//创建一个IO完成端口
	cout<<"创建一个IO完成端口"<<endl;
	hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
	if(hCompletionPort == INVALID_HANDLE_VALUE)
	{
		cout<<"创建IO完成端口失败"<<endl;
		return -1;
	}
	//获取CPU数目
	GetSystemInfo(&siSys);
	//创建一定数目的工作者线程，本例中以一个处理器一个线程搭配
	for(int i = 0;i<(int)1;i++)//NumberOfProcessors
	{
		HANDLE hThread;
		hThread = CreateThread(NULL,0,ServerWorkerThread,(LPVOID)hCompletionPort,0,&nThreadID);
		cout<<"创建工作者线程"<<i<<endl;
		CloseHandle(hThread);
	}
	//创建监听SOCKET
	cout<<"创建监听SOCKET"<<endl;
	sockListen = WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	if(sockListen == SOCKET_ERROR)
	{
		cout<<"WSASocket错误"<<endl;
		return -1;
	}

	if(setsockopt(sockListen,SOL_SOCKET,SO_REUSEADDR,(const char *)&nReuseAddr,sizeof(int)) != 0)
	{
		cout<<"setsockopt错误"<<endl;
		return -1;
	}
	addrLocal.sin_family = AF_INET;
	addrLocal.sin_addr.s_addr = htonl(INADDR_ANY);
	addrLocal.sin_port = htons(9198);
	if(bind(sockListen,(struct sockaddr *)&addrLocal,sizeof(sockaddr_in)) != 0)
	{
		cout<<"bind错误"<<endl;
		int n = WSAGetLastError();
		return -1;
	}
	//准备监听
	cout<<"准备监听"<<endl;
	if(listen(sockListen,5)!=0)
	{
		cout<<"listen错误"<<endl;
		return -1;
	}
	while(true)
	{
		//接收用户连接，被和完成端口关联
		sockAccept = WSAAccept(sockListen,NULL,NULL,NULL,0);
		perHandleData = (LPPER_HANDLE_DATA)malloc(sizeof(PER_HANDLE_DATA));
		if(perHandleData == NULL)
			continue;
		cout<<"socket number "<<sockAccept<<"接入"<<endl;
		perHandleData->sock = sockAccept;

		ioperdata = (LPPER_IO_OPERATION_DATA)malloc(sizeof(PER_IO_OPERATION_DATA));
		memset(&(ioperdata->Overlapped),0,sizeof(OVERLAPPED));
		ioperdata->DataBuff.len = 24;
		ioperdata->DataBuff.buf = ioperdata->Buff;
		ioperdata->OperationType = RECV_POSTED;
		if( ioperdata == NULL)
		{
			free(perHandleData);
			continue;
		}
		//关联
		cout<<"关联SOCKET和完成端口"<<endl;
		if(CreateIoCompletionPort((HANDLE)sockAccept,hCompletionPort,(DWORD)perHandleData,0) == NULL)
		{
			cout<<sockAccept<<"createiocompletionport错误"<<endl;
			free(perHandleData);
			free(ioperdata);
			continue;
		}
		//投递接收操作
		cout<<"投递接收操作"<<endl;
		if (SOCKET_ERROR == WSARecv(sockAccept,&(ioperdata->DataBuff),1,&dwRecvBytes,&dwFlags,&(ioperdata->Overlapped),NULL))
		{
			cout << "WSARecv ERROR:" << WSAGetLastError() << endl;
		}
	}
	getchar();
	return 0;
}
//---------------------------------------------------------------------------
int Init()
{
	WSAData wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		cout<<"WSAStartup失败"<<endl;
		return -1;
	}

	if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		cout<<"SOCKET版本不对"<<endl;
		WSACleanup();
		return -1;
	}
	return 0;
}

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPort)
{
	HANDLE ComPort = (HANDLE)CompletionPort;
	DWORD BytesTransferred;
	//LPOVERLAPPED Overlapped;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	DWORD SendBytes,RecvBytes;
	DWORD Flags = 0;
	BOOL bT;

	while(TRUE)
	{
		//等待完成端口上SOCKET的完成
		cout<<"等待完成端口上SOCKET的完成"<<endl;
		bT = GetQueuedCompletionStatus(ComPort,
			&BytesTransferred,(LPDWORD)&PerHandleData,
			(LPOVERLAPPED *)&PerIoData,INFINITE);

		//检查是否有错误产生
		if(BytesTransferred == 0 &&
			(PerIoData->OperationType == RECV_POSTED ||
			PerIoData->OperationType == SEND_POSTED))
		{
			//关闭SOCKET
			cout<<PerHandleData->sock<<"SOCKET关闭"<<endl;
			closesocket(PerHandleData->sock);
			free(PerHandleData);
			free(PerIoData);
			continue;
		}

		//为请求服务

		if(PerIoData->OperationType == RECV_POSTED)
		{
			//处理
			cout<<"接收处理"<<endl;
			cout<<PerHandleData->sock<<"SOCKET :"<<PerIoData->Buff<<endl;
			//回应客户端
			ZeroMemory(PerIoData->Buff,24);
			strcpy(PerIoData->Buff,"OK");
			Flags = 0;
			ZeroMemory((LPVOID)&(PerIoData->Overlapped),sizeof(OVERLAPPED));
			PerIoData->DataBuff.len = 2;
			PerIoData->DataBuff.buf = PerIoData->Buff;
			PerIoData->OperationType = SEND_POSTED;
			WSASend(PerHandleData->sock,&(PerIoData->DataBuff),
				1,&SendBytes,0,&(PerIoData->Overlapped),NULL);
		}
		else //if(PerIoData->OperationType == SEND_POSTED)
		{
			//发送时的处理
			cout<<"发送处理"<<endl;
			Flags = 0;
			ZeroMemory((LPVOID)&(PerIoData->Overlapped),sizeof(OVERLAPPED));
			ZeroMemory(PerIoData->Buff,24);
			PerIoData->DataBuff.len = 24;
			PerIoData->DataBuff.buf = PerIoData->Buff;
			PerIoData->OperationType = RECV_POSTED;
			WSARecv(PerHandleData->sock,&(PerIoData->DataBuff),
				1,&RecvBytes,&Flags,&(PerIoData->Overlapped),NULL);
		}
	}
}