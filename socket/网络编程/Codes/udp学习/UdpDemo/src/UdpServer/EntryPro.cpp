#include <stdio.h>
#include "winsock2.h"


#pragma comment(lib, "Ws2_32.lib")


void main()
{
	WSADATA wsaData;
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
	return;
}
