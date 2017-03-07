#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

using std::cout;
using std::endl;
using std::cin;

int main()
{
	//加载Socket动态链接库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		cout<<"Tell the user that we could not find a usable"<<endl; 
		return 1;
	}
	
	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */
	
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		  HIBYTE( wsaData.wVersion ) != 2 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		cout<<"Tell the user that we could not find a usable"<<endl;
		WSACleanup( );
		return 1; 
	}
	
	/* The WinSock DLL is acceptable. Proceed. */

	//1.创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == WSAGetLastError())
		MessageBox(NULL, "Create Socket failed!", "Error", MB_OK);

	//2.绑定套接字到指定的端口
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if(SOCKET_ERROR == WSAGetLastError())
		MessageBox(NULL, "bind fuction failed!", "Error", MB_OK);

	//3.等待接收数据
	char recvBuf[100];
	SOCKADDR_IN addrClient;
	int fromLen = 100;
	recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &fromLen);
	if(SOCKET_ERROR == WSAGetLastError())
		MessageBox(NULL, "recvfrom fuction failed!", "Error", MB_OK);
	printf("%s\n", recvBuf);

	//4.关闭套接字
	closesocket(sockSrv);
	WSACleanup();
	
	return 0;
	

	//the example in MSDN
/*	WSADATA wsaData;
	SOCKET RecvSocket;
	sockaddr_in RecvAddr;
	int Port = 27015;
	char RecvBuf[1024];
	int  BufLen = 1024;
	sockaddr_in SenderAddr;
	int SenderAddrSize = sizeof(SenderAddr);
	
	//-----------------------------------------------
	// Initialize Winsock
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	//-----------------------------------------------
	// Create a receiver socket to receive datagrams
	RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	//-----------------------------------------------
	// Bind the socket to any address and the specified port.
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(RecvSocket, (SOCKADDR *) &RecvAddr, sizeof(RecvAddr));
	
	//-----------------------------------------------
	// Call the recvfrom function to receive datagrams
	// on the bound socket.
	printf("Receiving datagrams...\n");
	recvfrom(RecvSocket, 
		RecvBuf, 
		BufLen, 
		0, 
		(SOCKADDR *)&SenderAddr, 
		&SenderAddrSize);
	
	//-----------------------------------------------
	// Close the socket when finished receiving datagrams
	printf("Finished receiving. Closing socket.\n");
	closesocket(RecvSocket);
	
	//-----------------------------------------------
	// Clean up and exit.
	printf("Exiting.\n");
	WSACleanup();

	return 0;
*/
}