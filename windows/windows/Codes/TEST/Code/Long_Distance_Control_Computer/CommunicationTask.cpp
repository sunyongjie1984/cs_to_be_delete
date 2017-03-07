// CommunicationTask.cpp: implementation of the CCommunicationTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommunicationTask.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCommunicationTask::CCommunicationTask()
{

}

CCommunicationTask::~CCommunicationTask()
{

}
unsigned __stdcall CCommunicationTask::ReceiveControlMsgTask( LPVOID param )
{
	PCOMMUNICATION pAcceptSocket = (PCOMMUNICATION)param;
/*
	FD_SET			SocketSet;
	struct	timeval	timeout;
	
	timeout.tv_sec	= 0;		// Seconds
	timeout.tv_usec = 0;		// Micro Seconds
	
	// Set the Socket Set
	SocketSet.fd_count		= 1;
	SocketSet.fd_array[1]   = pAcceptSocket->AcceptSocket;

	DWORD dwRet = select( 0, &SocketSet, NULL, NULL, &timeout );
	
	if ( 0 == dwRet )
	{
		return -1;
	}
*/
	char szReceiveBuffer[1024] = {0};

	int  nLength = strlen(szReceiveBuffer);
	
	recv( pAcceptSocket->AcceptSocket,
		  szReceiveBuffer,
		  1024,
		  0 );
	
	send( pAcceptSocket->AcceptSocket,
		  szReceiveBuffer,
		  strlen(szReceiveBuffer),
		  0 );
	
	closesocket( pAcceptSocket->AcceptSocket );
	
//	delete pAcceptSocket;
//	pAcceptSocket = NULL;

	return 0;
}

int CCommunicationTask::InitializeSocket(
							IN    OUT	 SOCKET   &communicationSocket,
							IN			 u_short   dwCommunicationPort,
							IN			 PCHAR	   lpIpAddress		)
{
	WSADATA wsaData;
	
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
	
	if ( iResult != NO_ERROR )
	{
		
	}
	
	communicationSocket = WSASocket( AF_INET,
									 SOCK_STREAM,
									 IPPROTO_IP,
									 NULL,
									 0,
									 SOCK_STREAM );
	
	if ( SOCKET_ERROR == communicationSocket ) 
	{
		WSACleanup();
		return -1;
	}
	
	sockaddr_in service;
	
	service.sin_family			= AF_INET;
	service.sin_port			= htons( dwCommunicationPort );
	service.sin_addr.s_addr		= htonl(INADDR_ANY);
	
	int nStatus = bind( communicationSocket,
						(SOCKADDR*) &service,
						sizeof(service) );
	
	if ( SOCKET_ERROR == nStatus )
	{
		closesocket(communicationSocket);
		return -1;
	}
	
	int nZero = 0;
	
	nStatus = setsockopt( communicationSocket,
						  SOL_SOCKET,
						  SO_SNDBUF,
						  ( PCHAR )&nZero,
						  sizeof(nZero) );
	
	if ( nStatus )
	{
		closesocket(communicationSocket);
		return -1;
	}
	return 0;
}


unsigned __stdcall CCommunicationTask::__RunNetWorkListenTask( LPVOID param )
{
	SOCKET listenSocket;

	InitializeSocket( listenSocket, 11111, NULL );

	if ( SOCKET_ERROR == listen( listenSocket, SOMAXCONN ) )
	{
		closesocket(listenSocket);
		return -1;
	}	
	
 	sockaddr_in		   client;
	SOCKET			   AcceptSocket;
	int				   iAddrSize      = sizeof(client);
	
	while ( TRUE )
	{

		AcceptSocket = accept( listenSocket, (SOCKADDR*)&client, &iAddrSize);
		
		if ( INVALID_SOCKET != AcceptSocket )
		{			
			COMMUNICATION	iCommunication;

			iCommunication.AcceptSocket = AcceptSocket;

			UINT uThreadId = 0;

			HANDLE hThreadHandle = (HANDLE) _beginthreadex( NULL,
															0,
															ReceiveControlMsgTask,
															(LPVOID)&iCommunication,
															0,
															&uThreadId );

			if ( INVALID_HANDLE_VALUE == hThreadHandle )
			{
				//LogError
			}
			
			CloseHandle( hThreadHandle );
		}
		else
		{
			break;
		}			
	}
	
	closesocket(listenSocket);

	return 0;
}


BOOL CCommunicationTask::StartNetWorkListenTask()
{
	UINT uThreadId = 0;
	
	HANDLE hThreadHandle = (HANDLE) _beginthreadex( NULL,
													0,
													__RunNetWorkListenTask,
													0,
													0,
													&uThreadId );

	if ( INVALID_HANDLE_VALUE == hThreadHandle )
	{
		//LogError
	}
	
	CloseHandle( hThreadHandle );

	return TRUE;
}

/*
*/

