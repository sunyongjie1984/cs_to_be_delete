#include <winsock2.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	WSADATA  wsa;
	SOCKET   sock;
	struct   sockaddr_in sin;
	char     msg[25]="i am TOo2y";
	int      iret;

	printf("===[ Test for SPI BackDoor ]===\n");
	printf("===[ TOo2y  at  11-3-2002  ]===\n\n");

	if(WSAStartup(MAKEWORD(2,2),&wsa))
	{
		printf("WSAStartup Error: %d\n",WSAGetLastError());
		getche();
		return -1;
	}

	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
	{
		printf("Socket Error: %d\n",WSAGetLastError());
		getche();
		return -1;
	}

	sin.sin_addr.s_addr=inet_addr("127.0.0.1");
	sin.sin_family=AF_INET;
	sin.sin_port=htons(12345);

	if(connect(sock,(struct sockaddr *)&sin,sizeof(sin))==SOCKET_ERROR)
	{
		printf("Connect Error: %d\n",WSAGetLastError());
		getche();
		return -1;
	}

    if((iret=send(sock,msg,sizeof(msg),0))==SOCKET_ERROR)
	{
		printf("Send Error: %d\n",WSAGetLastError());
		getche();
		return -1;
	}

	memset(msg,0,sizeof(msg));
	if((iret=recv(sock,msg,sizeof(msg),0))==SOCKET_ERROR)
	{
		printf("Recv Error: %d\n",WSAGetLastError());
		getche();
		return -1;
	}
	printf("Re: ");
    printf(msg);

	closesocket(sock);
	WSACleanup();
	getche();
	return 0;
}