// property, debugging, command line agrument 192.168.113.129
#include <winsock2.h>
#include <stdio.h>

void main(int argc, char **argv)
{
    WSADATA              wsaData;
    SOCKET               s;
    SOCKADDR_IN          ServerAddr;
    int                  Port = 13;
    int                  Ret;

    if (argc <= 1)
    {
        printf("USAGE: tcpclient <Server IP address>.\n");
        return;
    }

    // Initialize Winsock version 2.2

    if ((Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
    {
        // NOTE: Since Winsock failed to load we cannot use WSAGetLastError 
        // to determine the error code as is normally done when a Winsock 
        // API fails. We have to report the return status of the function.

        printf("WSAStartup failed with error %d\n", Ret);
        return;
    }

    // Create a new socket to make a client connection.

    if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
            == INVALID_SOCKET)
    {
        printf("socket failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // Setup a SOCKADDR_IN structure that will be used to connect
    // to a listening server on port 5150. For demonstration
    // purposes, we required the user to supply an IP address
    // on the command line and we filled this field in with the 
    // data from the user.

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port); 
    ServerAddr.sin_addr.s_addr = inet_addr(argv[1]);

    // Make a connection to the server with socket s.

    printf("We are trying to connect to %s:%d...\n",
            inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));

    if (connect(s, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr)) 
            == SOCKET_ERROR)
    {
        printf("connect failed with error %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    printf("Our connection succeeded.\n");

    int n = 0;
    const int LENGTH = 200;
    char recvline[LENGTH];
    while ((n = recv(s, recvline, LENGTH, 0)) > 0)
    {
        recvline[n] = 0; // null terminate
        printf("%s", recvline);
    }

    // When you are finished sending and receiving data on socket s,
    // you should close the socket.

    printf("We are closing the connection.\n");

    closesocket(s);

    // When your application is finished handling the connection, call
    // WSACleanup.

    WSACleanup();
}

