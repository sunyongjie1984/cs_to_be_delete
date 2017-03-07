#include <stdio.h>
#include "winsock2.h"


#pragma comment(lib, "Ws2_32.lib")


void main()
{
	WSADATA wsaData;
	SOCKET SendSocket;
	sockaddr_in RecvAddr;
	int Port = 27015;
	char SendBuf[1024];
	int BufLen = 1024;
	
	//---------------------------------------------
	// Initialize Winsock
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	//---------------------------------------------
	// Create a socket for sending data
	SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	//---------------------------------------------
	// Set up the RecvAddr structure with the IP address of
	// the receiver (in this example case "123.456.789.1")
	// and the specified port number.
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = inet_addr("193.168.11.56");
	
	//---------------------------------------------
	// Send a datagram to the receiver
	printf("Sending a datagram to the receiver...\n");
	sendto(SendSocket, 
		SendBuf, 
		BufLen, 
		0, 
		(SOCKADDR *) &RecvAddr, 
		sizeof(RecvAddr));
	
	//---------------------------------------------
	// When the application is finished sending, close the socket.
	printf("Finished sending. Closing socket.\n");
	closesocket(SendSocket);
	
	//---------------------------------------------
	// Clean up and quit.
	printf("Exiting.\n");
	WSACleanup();
	return;
}
