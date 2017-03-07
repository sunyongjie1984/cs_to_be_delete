#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	//加载Socket动态链接库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	cout<<"srv:load socket dll"<<endl;
	if ( err != 0 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		cout<<"server:Tell the user that we could not find a usable"<<endl;
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
		
		cout<<"server:Tell the user that we could not find a usable"<<endl;
		WSACleanup( );
		return 1; 
	}
	
	/* The WinSock DLL is acceptable. Proceed. */

	//1.创建套接字
	cout<<"server:create socket"<<endl;
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == WSAGetLastError())
		MessageBox(NULL, "Create Socket failed!", "Error", MB_OK);

	//2.绑定套接字到一个端口号
	cout<<"server:bind a port"<<endl;
	SOCKADDR_IN addrSrv;
	memset(&addrSrv, 0, sizeof(addrSrv));
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//3.设置套接字为监听模式
	cout<<"server:set socket listen"<<endl;
	listen(sockSrv, /*SOMAXCONN*/ 5);

	//4.等待用户的连接到来
	cout<<"srv:wait....."<<endl;
	SOCKADDR_IN addrClient;
	int sockLen = sizeof(SOCKADDR);
	while(1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &sockLen);
		if(INVALID_SOCKET == WSAGetLastError())
			MessageBox(NULL, "Connect client failed!", "Error", MB_OK);

		//5.用返回的套接字和用户通信，发送数据或是接受数据
		cout<<"server:use returned socket to transfor with other user"<<endl;
		char sendBuf[100];
		wsprintf(sendBuf, "welcome %s to my computer",
				inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, sizeof(sendBuf) + 1, 0);
		if(SOCKET_ERROR == WSAGetLastError())
			MessageBox(NULL, "Server send data failed!", "Error", MB_OK);
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);
		if(SOCKET_ERROR == WSAGetLastError())
			MessageBox(NULL, "Server recieve data failed!", "Error", MB_OK);
		printf("%s\n", recvBuf);

		//6.关闭申请的套接字资源
		cout<<"server:close socket"<<endl;
		closesocket(sockConn);
	}

	return 0;
}