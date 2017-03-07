#define _WIN32_WINNT 0x0500 
#include <winsock2.h>
#include <mswsock.h>
#include <windows.h>
#include <Ws2tcpip.h>
#include <list>

#include <iostream>
using namespace std;

#define MAX_PENDING_CONNECTIONS		10

// Maximum Buffer Size
#define MAX_BUFF_SIZE				8192

// No of Threads which can work simultaneously
#define MAX_WORKER_THREAD   16


// This is to store the attributes of a Server Socket, a listening 
// Socket.
struct ServerSocket {
	char		szHostName[256];
	char		szPortNumber[10];
	int			ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
    int			ai_family;      // PF_xxx
	int			ai_socktype;    // SOCK_xxx
	int			ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6

	// Associate an Event object with Network Event FD-ACCEPT.
	// This event object will be signalled when a connection is 
	// pending to be accepted.
	WSAEVENT	wsaEvent; 

	ServerSocket()
	{
		memset(szHostName,'\0',256);
		memset(szPortNumber,'\0',10);
		
		strcpy(szHostName,"localhost");
		strcpy(szPortNumber,"5001");
		ai_flags  = AI_PASSIVE;
		ai_family = AF_INET;
		ai_socktype = SOCK_STREAM;
		ai_protocol = IPPROTO_IP;

		// By Default, It non-Signalled Network Event
		wsaEvent = WSACreateEvent();
	}
    
};

// Different Types of operation performed on a Socket.
enum IO_OPERATION {
    IOAccept,
    IORead,
    IOWrite
};

// This structure is to store a Socket Attributes.
typedef struct __PER_SOCKET_DATA
{
	SOCKET		listenSocket;
	SOCKET		acceptSocket; 		
	__PER_SOCKET_DATA()
	{
		listenSocket = INVALID_SOCKET;
		acceptSocket = INVALID_SOCKET;
	}

} PER_SOCKET_DATA,* PPER_SOCKET_DATA;


// This structure is to store an attributes of multiple
// IO operations performed on a single Socket.
typedef struct __PER_IO_DATA {
    WSAOVERLAPPED               Overlapped;
    char                        Buffer[MAX_BUFF_SIZE];
    WSABUF                      wsabuf;
    int                         nTotalBytes;
    int                         nSentBytes;
    IO_OPERATION                opCode;
    SOCKET                      activeSocket; 
	int							_indexPos;
    
} PER_IO_DATA, * PPER_IO_DATA;


extern ServerSocket socketInfo;

extern BOOL CreateServerSocket(void) ;

extern DWORD WINAPI waitForNetworkEvent(LPVOID lpParameter);

extern DWORD WINAPI queueAccept(LPVOID lpParameter);

extern SOCKET CreateSocket(PPER_SOCKET_DATA pSocketInfo);

PPER_IO_DATA AllocateIOData(SOCKET sd, IO_OPERATION ClientIO);

DWORD WINAPI WorkerThread (LPVOID WorkThreadContext);