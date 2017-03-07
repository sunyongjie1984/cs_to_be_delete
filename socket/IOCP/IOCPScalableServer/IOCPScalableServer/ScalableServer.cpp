/*******************************************************************/
/* Purpose : The purpose of the code is to demonstrate a combination
/*			 of an IO Completion Port along with Asynchronous I/O 
/*			 technique to develope a Scalable Servers. This example 
/*			 shows how multiple clients can be served with a handful
/*			 number of thread which constitutes a Thread Pool.
/*******************************************************************/

#include "ScalableServer.h"


std::list<PPER_IO_DATA > sdList;

HANDLE acceptEvent = INVALID_HANDLE_VALUE;

HANDLE g_ThreadHandles[MAX_WORKER_THREAD];

unsigned int g_ThreadCount = 0;

HANDLE g_hIOCP = INVALID_HANDLE_VALUE;

CRITICAL_SECTION g_CriticalSection;		// Synchronize an access to global list
										// from different worker threads.

SOCKET g_ServerSocket = INVALID_SOCKET;

ServerSocket socketInfo;

HANDLE hWaitEventThread = INVALID_HANDLE_VALUE;

void main (int argc, char * argv[])
{	
	SYSTEM_INFO sysInfo;
	WSADATA wsaData;
	int retVal = -1;
	
	ZeroMemory(&sysInfo,sizeof(SYSTEM_INFO));
	ZeroMemory(&wsaData,sizeof(WSADATA));
	
	GetSystemInfo(&sysInfo);

	g_ThreadCount = sysInfo.dwNumberOfProcessors * 1;

	if( (retVal = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0 ) {
		cout << "WSAStartup Failed::Reason Code::"<< retVal << endl;
		return;
	}

	InitializeCriticalSection(&g_CriticalSection);


	g_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,g_ThreadCount);

	if (g_hIOCP == NULL)
	{
		cout << "CreateIoCompletionPort() Failed::Reason::"<< GetLastError() << endl;
		return;			
	}


	if (CreateServerSocket() == FALSE)
	{
		cout << "CreateServerSocket Failed::"<< endl;
		return ;
	}
	
	PPER_SOCKET_DATA lpServerSocket = new PER_SOCKET_DATA;
	lpServerSocket->listenSocket = ::g_ServerSocket;

	// Associate a IO Completion Port with a Server Socket i.e. listening Socket.
	if (CreateIoCompletionPort((HANDLE)g_ServerSocket,g_hIOCP,(ULONG_PTR)lpServerSocket,::g_ThreadCount) == NULL)
	{
		cout << "Binding Server Socket to IO Completion Port Failed::Reason Code::"<< GetLastError() << endl;
		return ;	
	}


	for( DWORD dwThread=0; dwThread < g_ThreadCount; dwThread++ )
	{
		HANDLE  hThread;
		DWORD   dwThreadId;

		hThread = CreateThread(NULL, 0, WorkerThread, g_hIOCP, 0, &dwThreadId);
		g_ThreadHandles[dwThread] = hThread;
		hThread = INVALID_HANDLE_VALUE;
	}

	acceptEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	
	// Create Thread which will be polling on an Event Object corresponding 
	// to FD_ACCEPT.
	DWORD dwThreadID = -1;
	hWaitEventThread = CreateThread(NULL,0,waitForNetworkEvent, &socketInfo,0, &dwThreadID);

	Sleep(1000000);
}

// This is to create a Server Socket.
BOOL CreateServerSocket(void) 
{

	int retVal = -1 ;

	addrinfo sockInfo;
	addrinfo *hostInfo = NULL;

	memset(&sockInfo, 0, sizeof(addrinfo));
	sockInfo.ai_flags  = socketInfo.ai_flags;
	sockInfo.ai_family = socketInfo.ai_family;
	sockInfo.ai_socktype = socketInfo.ai_socktype;
	sockInfo.ai_protocol = socketInfo.ai_protocol;

	if( getaddrinfo(socketInfo.szHostName, socketInfo.szPortNumber, &sockInfo, &hostInfo) != 0 ) {
		
        return(FALSE);
	}

	
	g_ServerSocket = WSASocket(hostInfo->ai_family,hostInfo->ai_socktype, \
								hostInfo->ai_protocol, NULL,0,WSA_FLAG_OVERLAPPED);

	if( g_ServerSocket == INVALID_SOCKET ) {
		cout << "Server Socket Creation Failed::Reason Code::" << WSAGetLastError() << endl;
		return(FALSE);

	}

	int nZero = 0;
	int nRet = setsockopt(g_ServerSocket, SOL_SOCKET, SO_SNDBUF, (char *)&nZero, sizeof(nZero));
	if( nRet == SOCKET_ERROR) {
		
		return(FALSE);
	}

	retVal = bind(g_ServerSocket,&*(hostInfo->ai_addr),hostInfo->ai_addrlen);
	if( retVal == SOCKET_ERROR ) {
		cout << "Server Soket Bind Failed::Reason Code::"<< WSAGetLastError() << endl;
		return(FALSE);
	}
	
	retVal = listen(g_ServerSocket, MAX_PENDING_CONNECTIONS);
	if( retVal == SOCKET_ERROR ) {
		cout << "Server Socket Listen Failed::Reason Code::"<< WSAGetLastError() << endl;
		return(FALSE);
	}

	// Associate an Event Object with a Network Event.
	retVal = WSAEventSelect(g_ServerSocket,socketInfo.wsaEvent,FD_ACCEPT);
	if (retVal != 0)
	{
		cout << "::WSAEventSelect Failed::Reason Code::"<< WSAGetLastError() << endl;
		return (FALSE);
	}

	return TRUE;
}


// This Thread Function is responsible to wait for an Event Object to
// be Signalled. As soon as Event Object get signalled, a Work Item is posted
// to a Worker Thread which is responsible to invoke AcceptEx() call.

DWORD WINAPI waitForNetworkEvent(LPVOID lpParameter)
{
	ServerSocket *pServerSocket = (ServerSocket*)lpParameter;
	

	while (1)
	{
		WSAWaitForMultipleEvents(1,&pServerSocket->wsaEvent,TRUE,WSA_INFINITE,FALSE);
		WSAResetEvent(pServerSocket->wsaEvent);
		PPER_SOCKET_DATA pSocketInfo = new PER_SOCKET_DATA;
		pSocketInfo->listenSocket = ::g_ServerSocket;
		CreateSocket(pSocketInfo);
		if (pSocketInfo->acceptSocket != INVALID_SOCKET)
		{
			QueueUserWorkItem(queueAccept,pSocketInfo,WT_EXECUTEDEFAULT);
			WaitForSingleObject(acceptEvent,INFINITE);
			ResetEvent (::acceptEvent);

		}
	}
}


// This Thread is responsible for invoking AcceptEx() function. This will cause
// a IO Completion Packet to be posted when pending Accept request gets finished.

DWORD WINAPI queueAccept(LPVOID lpParameter)
{
	PPER_SOCKET_DATA pSocketData =  (PPER_SOCKET_DATA)lpParameter;
	
	DWORD dwRecvNumBytes = 0;

	// Allocate IO Data with a new Socket on which an incoming connection is 
	// to be accepted.
	PPER_IO_DATA pIOData = AllocateIOData(pSocketData->acceptSocket,IOAccept);

	//int bVal = AcceptEx(pSocketData->listenSocket,pIOData->activeSocket,NULL,0,0,0,&dwRecvNumBytes,(LPOVERLAPPED)&pIOData->Overlapped);
	int nRet = AcceptEx(pSocketData->listenSocket, pIOData->activeSocket,
	                  (LPVOID)(pIOData->Buffer),
                    MAX_BUFF_SIZE - (2 * (sizeof(sockaddr_in  ) + 16)),
                  sizeof(sockaddr_in  ) + 16, sizeof(sockaddr_in  ) + 16,
                &dwRecvNumBytes, 
					(LPOVERLAPPED) &(pIOData->Overlapped));
	
	if( nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()) ) {
		return(FALSE);
	}

	return 0;
}


// This is to create a socket on which an incoming Socket is accepted.
SOCKET CreateSocket(PPER_SOCKET_DATA pSocketInfo) 
{
	int retVal = 0;
	
	SOCKET sdAcceptSocket = INVALID_SOCKET;

	sdAcceptSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED); 
	if( sdAcceptSocket == INVALID_SOCKET ) {
		cout << "::CreateSocket Failed::"<< endl;
		return (sdAcceptSocket);
	}

	// This means that we are setting buffer size for send to 0. So the send data
	// will not be buffered.
	int nZero = 0;
	int nRet = setsockopt(sdAcceptSocket, SOL_SOCKET, SO_SNDBUF, (char *)&nZero, sizeof(nZero));
	if( nRet == SOCKET_ERROR) {
		
		return(sdAcceptSocket);
	}

	pSocketInfo->acceptSocket = sdAcceptSocket;

 	return (sdAcceptSocket);
}


PPER_IO_DATA AllocateIOData(SOCKET sd, IO_OPERATION ClientIO) {

	PPER_IO_DATA lpPerIOContext;

	EnterCriticalSection(&g_CriticalSection);

	lpPerIOContext = new PER_IO_DATA;

	if( lpPerIOContext ) {
		lpPerIOContext->activeSocket = sd;
				
		lpPerIOContext->Overlapped.Internal = 0;
		lpPerIOContext->Overlapped.InternalHigh = 0;
		lpPerIOContext->Overlapped.Offset = 0;
		lpPerIOContext->Overlapped.OffsetHigh = 0;
		lpPerIOContext->Overlapped.hEvent = NULL;
		lpPerIOContext->opCode = ClientIO;
			
		lpPerIOContext->nTotalBytes = 0;
		lpPerIOContext->nSentBytes  = 0;
		lpPerIOContext->wsabuf.buf  = lpPerIOContext->Buffer;
		lpPerIOContext->wsabuf.len  = sizeof(lpPerIOContext->Buffer);

		ZeroMemory(lpPerIOContext->wsabuf.buf, lpPerIOContext->wsabuf.len);
		sdList.push_front(lpPerIOContext);
		cout << "::Size of List::"<< sdList.size() << endl;
		
	} else {
		cout << "::HeapAllocation Failed::"<<endl;
	}

	LeaveCriticalSection(&g_CriticalSection);

	return(lpPerIOContext);
} 



// This is a WorkerThread which is responsible to process 
// IO Completion Packets.
DWORD WINAPI WorkerThread (LPVOID WorkThreadContext) {

	HANDLE hIOCP = (HANDLE)WorkThreadContext;
	BOOL bSuccess = FALSE;
	int nRet = 0;
	LPWSAOVERLAPPED lpOverlapped = NULL;
	PPER_SOCKET_DATA lpPerSocketContext = NULL;
	PPER_IO_DATA lpIOContext = NULL; 
	WSABUF buffSend;
	DWORD dwRecvNumBytes = 0;
	DWORD dwSendNumBytes = 0;
	DWORD dwFlags = 0;
	DWORD dwIoSize = 0;

	while( TRUE ) {

   		bSuccess = GetQueuedCompletionStatus(g_hIOCP, &dwIoSize,
											 (PDWORD_PTR)&lpPerSocketContext,
											 (LPOVERLAPPED *)&lpOverlapped, 
											 INFINITE);

		lpIOContext = (PPER_IO_DATA)lpOverlapped;

		int nRet = setsockopt(
							 lpIOContext->activeSocket, 
							 SOL_SOCKET,
							 SO_UPDATE_ACCEPT_CONTEXT,
							 (char *)&lpPerSocketContext->listenSocket,
							 sizeof(lpPerSocketContext->listenSocket)
							 );
		
		char szTemp[MAX_BUFF_SIZE] = {'\0'};
	    
		char *revString = NULL;
		
		sockaddr_in  *sockLocalAdd = NULL;
		sockaddr_in  *sockRemoteAdd= NULL;

		int length = sizeof(SOCKADDR);
		

		// Check which type of IO packet has completed.
		switch( lpIOContext->opCode ) {
			case IOAccept:
				// This is to parse a data obtained from an AccpetEx() call.
				GetAcceptExSockaddrs(lpIOContext->Buffer,
							MAX_BUFF_SIZE - (2 * (sizeof(sockaddr_in  ) + 16)),
							sizeof(sockaddr_in  ) + 16, sizeof(sockaddr_in  ) + 16,
							(SOCKADDR**)&sockLocalAdd,&length,
							(SOCKADDR**)&sockRemoteAdd,&length);
	

				SetEvent(::acceptEvent);
				g_hIOCP = CreateIoCompletionPort((HANDLE)lpIOContext->activeSocket, g_hIOCP, (DWORD_PTR)lpPerSocketContext, 0);
				if(g_hIOCP == NULL) {
						cout << "::CreateIOCompletionPort Failed For Accept Socket::Socket Descriptor::"<< lpIOContext->activeSocket << endl;
				}

				lpIOContext->opCode = IOWrite;
				
				// Copy client's relevant data into a Temporar Buffer.
				CopyMemory(szTemp,lpIOContext->Buffer, MAX_BUFF_SIZE - (2 * (sizeof(sockaddr_in  ) + 16)));
				revString = _strrev(szTemp);

				ZeroMemory(lpIOContext->Buffer,MAX_BUFF_SIZE);
				lpIOContext->nTotalBytes  = strlen(revString);
				lpIOContext->nSentBytes   = 0;
				lpIOContext->wsabuf.len   = strlen(revString);
			
				// Copy your data which needs to be send to Client socket.
				CopyMemory(lpIOContext->Buffer,revString,strlen(revString));

				// Send Data back to Client after your processing. In our case, we have 
				// reversed client's string.
				nRet = WSASend(
							  lpIOContext->activeSocket,
							  &lpIOContext->wsabuf, 1,
							  &dwSendNumBytes,
							  0,
							  &(lpIOContext->Overlapped), NULL);

				if( nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()) ) {
					cout << "Error Occured WSASend::"<< endl;				
				}
				break;

			case IOWrite:
				// A Write Operation has completed on a Socket.
				lpIOContext->nSentBytes  += dwIoSize;
				dwFlags = 0;
				if( lpIOContext->nSentBytes < lpIOContext->nTotalBytes ) {
					lpIOContext->opCode = IOWrite;
					// A Write operation has not completed yet, so post another
					// Write operation to post remaining data.
					buffSend.buf = lpIOContext->Buffer + lpIOContext->nSentBytes;
					buffSend.len = lpIOContext->nTotalBytes - lpIOContext->nSentBytes;
					nRet = WSASend (
								   lpIOContext->activeSocket,
								   &buffSend, 1, &dwSendNumBytes,
								   dwFlags,
								   &(lpIOContext->Overlapped), NULL);

					if( nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()) ) {
					
					
					}
				} else {

					// Write operation completed, so post Read operation.
					lpIOContext->opCode = IORead; 
					dwRecvNumBytes = 0;
					dwFlags = 0;
					lpIOContext->wsabuf.buf = lpIOContext->Buffer,
					ZeroMemory(lpIOContext->wsabuf.buf,MAX_BUFF_SIZE);
					lpIOContext->Overlapped.Internal = 0;
					lpIOContext->Overlapped.InternalHigh = 0;
					lpIOContext->Overlapped.Offset = 0;
					lpIOContext->Overlapped.OffsetHigh = 0;
					lpIOContext->Overlapped.hEvent = NULL;
					lpIOContext->wsabuf.len = MAX_BUFF_SIZE;
					nRet = WSARecv(
								  lpIOContext->activeSocket,
								  &lpIOContext->wsabuf, 1, &dwRecvNumBytes,
								  &dwFlags,
								  &lpIOContext->Overlapped, NULL);
					if( nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()) ) {
				
					} 
				}
				break;

			case IORead:
				// A Read Operation completed on a Socket.
				CopyMemory(szTemp,lpIOContext->Buffer, MAX_BUFF_SIZE - (2 * (sizeof(sockaddr_in  ) + 16)));
				revString = _strrev(szTemp);

				ZeroMemory(lpIOContext->Buffer,MAX_BUFF_SIZE);
				lpIOContext->nTotalBytes  = strlen(revString);
				lpIOContext->nSentBytes   = 0;
				lpIOContext->wsabuf.len   = strlen(revString);
				
				// Copy your data which needs to be send to Client socket.
				CopyMemory(lpIOContext->Buffer,revString,strlen(revString));
				
				lpIOContext->opCode = IOWrite;
				dwFlags = 0;
				nRet = WSASend(
							  lpIOContext->activeSocket,
							  &lpIOContext->wsabuf, 1, &dwSendNumBytes,
							  dwFlags,
							  &(lpIOContext->Overlapped), NULL);
				if( nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()) ) {
			
				}
				break;

		}
	
	} //while
	return(0);
} 