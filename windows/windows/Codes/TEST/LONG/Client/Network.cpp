// Network.cpp: implementation of the CNetwork class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Network.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetwork::CNetwork()
{

}

CNetwork::~CNetwork()
{

}

int CNetwork::CreateReceiceThread()
{
	UINT uThreadId = 0;

	HANDLE hThread = (HANDLE)_beginthreadex( NULL,
											 0,
											 __ReceiceThread,
											 NULL,
											 0,
											 &uThreadId);

	CloseHandle( hThread );

	return 0;
}

unsigned _stdcall CNetwork::MsgReceiceTask( LPVOID param )
{
	PCLIENTSOCKET pClient = ( PCLIENTSOCKET )param;

	char  recvbuf[32]   = {0};
	char  szSendbuf[32] = {0};

	recv( pClient->receiceSocket, recvbuf, 32, 0 );

	DWORD dwReturnTime = 0;

	CNetwork::GetComputerTime( dwReturnTime );

	sprintf( szSendbuf, "%d", dwReturnTime );

	send( pClient->receiceSocket, szSendbuf, strlen(szSendbuf), 0);

	DWORD dwTime = (DWORD) atoi( recvbuf );

	CRegedit::WriteRegedit( dwTime );

	return 0;
}

int CNetwork::__InitSocket( SOCKET & socketA )
{
	WSADATA wsaData;

	int iResualt = WSAStartup(MAKEWORD(2, 2), &wsaData);

	socketA = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(INVALID_SOCKET == socketA )
	{
		WSACleanup();
		return -1;
	}

	sockaddr_in  service;
	service.sin_family			 = AF_INET;
	service.sin_port			 = htons(186);
	service.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	if(bind(socketA, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		closesocket(socketA);
		return -1;
	}

	return 0;
}

unsigned _stdcall CNetwork::__ReceiceThread( LPVOID param )
{
	SOCKET  socketA;

	int nStatus = __InitSocket( socketA );

	if ( -1 == nStatus )
	{
		return -1;
	}

	if(listen(socketA, 1) == SOCKET_ERROR)
	{
		closesocket(socketA);
		return -1;
	}

	while (TRUE)
	{
		CLIENTSOCKET client;

		client.receiceSocket = accept( socketA, NULL, NULL );

		if ( SOCKET_ERROR != client.receiceSocket )
		{
			UINT uThreadId = 0;

			HANDLE hThread = (HANDLE)_beginthreadex( NULL,
													 0,
													 MsgReceiceTask,
													 (LPVOID) &client,
													 0,
													 &uThreadId);

			CloseHandle( hThread );
		}
		else
		{
			closesocket(socketA);
			return -1;
		}
	}
	closesocket(socketA);

	return 0;
}

VOID CNetwork::GetComputerTime( DWORD &dwTime )
{
	SYSTEMTIME st;

	GetSystemTime(&st);

	dwTime = st.wHour + 8;
}