#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

//using namespace std::cout;
//using namespace std::endl;
//using namespace std::cin;
using namespace std;


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
		cout<<"client:Tell the user that we could not find a usable"<<endl;
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
		cout<<"client:Tell the user that we could not find a usable"<<endl;
		WSACleanup( );
		return 1; 
	}
	
	/* The WinSock DLL is acceptable. Proceed. */

	//1.创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == WSAGetLastError())
		MessageBox(NULL, "Create Socket failed!", "Error", MB_OK);
	
	//2.向服务器发送数据
	char sendBuf[100] = "UDP Server, Good evening!";
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5000);
	int toLen = 100;
	sendto(sockClient, sendBuf, sizeof(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, toLen);

	//3.关闭套接字
	closesocket(sockClient);
	WSACleanup();

	return 0;
}
