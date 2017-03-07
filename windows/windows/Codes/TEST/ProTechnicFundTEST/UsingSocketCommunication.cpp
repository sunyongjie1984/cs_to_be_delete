// UsingSocketCommunication.cpp: implementation of the CUsingSocketCommunication class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "UsingSocketCommunication.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsingSocketCommunication::CUsingSocketCommunication()
{
#ifdef _WIN32	// 如果是win32系统

	WSADATA wsaData;
	
	int nResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	
	if ( NO_ERROR != nResult )
	{

	}
	
#endif
}

CUsingSocketCommunication::~CUsingSocketCommunication()
{

#ifdef _WIN32	// 调用WSACleanup

	WSACleanup();

#endif

}
int HintMsg( IN	 HWND		hWnd,
			 IN	 string		strHintMsg,
			 IN	 string		strPlaceHint,
			 IN	 UINT		uType )
{
	//获得错误数
	int nError = WSAGetLastError();

	//转换错误数为字符
	CHAR szError[MAX_PATH] = {0};
	sprintf( szError, "%d", nError );

	CHAR szErrorHint[MAX_PATH] = {0};
	
	strcpy( szErrorHint, strHintMsg.c_str() );
	strcat( szErrorHint, szError );
	
	int nResult = ::MessageBox( hWnd,
								szErrorHint,
								strPlaceHint.c_str(),
								uType );
	
	return nResult;
}

////////////////////////////////////////////
CTCP_SocketCommuntication::CTCP_SocketCommuntication()
{

}

CTCP_SocketCommuntication::~CTCP_SocketCommuntication()
{
	WSACleanup();//创建套接字失败，结束Winsock库，而且不再需要调用任何Winsock函数时，附带例程会卸载这个库，并释放资源。	
}

int CTCP_SocketCommuntication::InitializeSocket( IN	SOCKET		&sockCommunication,
											 	 IN	u_short		 dwCommunicationPort )
{
	//加载Winsock DLL的相应版本。如果调用Winsock之前，没有加载Winsock库，这个函数就会返回一个SOCKET_ERROR，错误信息是WSANOTINITIALISE
	WSADATA		wsaData;
	WORD		wVersionRequired = MAKEWORD(2,2);//wVersionRequested参数用于指定准备加载的Winsock库的版本。
												 //高位字节指定所需要的Winsock库的副版本，而低位字节则是主版本。
												 //用宏MAKEWORD( X , Y )（其中，x是高位字节， y是低位字节）

	int nResult = WSAStartup( wVersionRequired, &wsaData );//WSAStartup用其加载的库版本有关的信息填在WSADATA结构中：

	if ( 0 != nResult )
	{
		HintMsg( NULL,
				 "ERROR HINT : WSAStartup FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::InitializeSocket()",
				 MB_OK );

		return -1;
	}

	//创建套接字
	sockCommunication = WSASocket( AF_INET,			//是协议的地址家族.如果想建立一个UDP或TCP套接字，可用常量AF_INET来指代互联网协议（IP）它指定准备使用哪种协议
								   SOCK_STREAM,		//是协议的套接字类型
								   IPPROTO_IP,		//。指定的地址家族和套接字类型有多个条目时，就可用这个字段来限定使用特定传输。
								   NULL,
								   0,
								   SOCK_STREAM );

	if ( SOCKET_ERROR == sockCommunication )
	{
		HintMsg( NULL,
				 "ERROR HINT : WSASocket FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::InitializeSocket()",
				 MB_OK );

		return -1;
	}

	//将指定协议的套接字与本地接口的IP地址和端口编号绑定。为某种特定协议创建了套接字，就必须将套接字绑定到一个已知地址。bind函数可将指定的套接字同一个已知地址绑定到一起
	sockaddr_in service;

	service.sin_addr.s_addr	= htonl(INADDR_ANY);
	service.sin_port		= htons( dwCommunicationPort );
	service.sin_family		= AF_INET;

	int nStatus = bind( sockCommunication,		//等待客户机连接的那个套接字
						(SOCKADDR*) &service,
						sizeof(service) );		//要传递的、由协议决定的地址的长度。
	
	if ( SOCKET_ERROR == nStatus )
	{
		closesocket( sockCommunication );	//关闭套接字
		
		HintMsg( NULL,
				 "ERROR HINT : bind FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::InitializeSocket()",
				 MB_OK );

		return -1;
	}

	return 0;
}

///// __stdcall调用约定(即函数的参数自右向左通过栈传递，被调用的函数在返回前清理传送参数的内存栈)
unsigned __stdcall CTCP_SocketCommuntication::__RunNetWorkListenTask( LPVOID param )
{
	//初始化socket
	SOCKET sockListen;

	int nResult = InitializeSocket( sockListen, 1982 );

	if ( 0 != nResult )
	{
		closesocket( sockListen );

		HintMsg( NULL,
				 "ERROR HINT : InitializeSocket FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
				 MB_OK );

		return -1;
	}

	//侦听端口
	nResult = listen( sockListen, SOMAXCONN );

	if ( SOCKET_ERROR == nResult )
	{
		closesocket( sockListen );

		HintMsg( NULL,
				 "ERROR HINT : listen FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
				 MB_OK );

		return -1;
	}

	//接收连接
	SOCKET sockReceive = SOCKET_ERROR;

	sockaddr_in  client;
	int			 nAddrSize = sizeof(client);

	while ( TRUE )
	{
		sockReceive = accept( sockListen,
							  (struct sockaddr*)&client,
							  &nAddrSize );
		
		if ( INVALID_SOCKET == sockReceive )
		{
			HintMsg( NULL,
					 "ERROR HINT : accept FAIL ## error = ",
					 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
					 MB_OK );

			break;
		}
		
		COMMUNICATION iCommunication;
		
		iCommunication.AcceptSocket = sockReceive;
		
		//接收数据
		UINT uThreadid = 0;

		HANDLE hReceiveThread = (HANDLE)_beginthreadex( NULL,
														0,
														ReceiveControlMsgTask,
														(LPVOID)&iCommunication,
														0,
														&uThreadid );

		if ( INVALID_HANDLE_VALUE == hReceiveThread )
		{
			HintMsg( NULL,
					 "ERROR HINT : _beginthreadex FAIL ## error = ",
					 "PLACE : CTCP_SocketCommuntication::__RunNetWorkListenTask",
					 MB_OK );
			
			return -1;
		}

		CloseHandle( hReceiveThread );
	}
	
	closesocket( sockListen );

	return 0;
}

ACE_Thread_Mutex CTCP_SocketCommuntication::m_mutex;

unsigned _stdcall CTCP_SocketCommuntication::ReceiveControlMsgTask(LPVOID param)
{
	//	ACE_GUARD_RETURN(ACE_Thread_Mutex, lock, m_mutex, -1);
	
	PCOMMUNICATION pCommunication = (PCOMMUNICATION)param;

	COMMUNICATION_DATA iReceive;

	memset( &iReceive, 0, sizeof(COMMUNICATION_DATA) );

	int nResult = recv( pCommunication->AcceptSocket,
						(PCHAR)&iReceive,
						sizeof(COMMUNICATION_DATA),
						0 );

	if ( SOCKET_ERROR == nResult )
	{
		HintMsg( NULL,
				 "ERROR HINT : recv FAIL ## error = ",
				 "PLACE : CTCP_SocketCommuntication::ReceiveControlMsgTask",
				 MB_OK );
		
		return -1;
	}

	DWORD dwThreadId = ::GetCurrentThreadId();

	CHAR szThreadid[1024] = {0};

	sprintf( szThreadid, "%d", dwThreadId );

	::MessageBox( NULL, iReceive.szMsg, szThreadid, MB_OK );
	
	closesocket( pCommunication->AcceptSocket );

	return 0;
}

BOOL CTCP_SocketCommuntication::StartNetWorkListenTask()
{
	UINT uThreadId = 0;

	HANDLE hThread = (HANDLE)_beginthreadex( NULL,
											 0,
											 __RunNetWorkListenTask,
											 0,
											 0,
											 &uThreadId );

	if ( INVALID_HANDLE_VALUE == hThread )
	{
		HintMsg( NULL,
				 "ERROR HINT : _beginthreadex",
				 "PLACE : CTCP_SocketCommuntication::StartNetWorkListenTask()",
				 MB_OK );
		
		return FALSE;
	}

	CloseHandle( hThread );

	return TRUE;
}
//////////////////////////////////////////// UDP通讯类
CUDP_SocketCommuntication::CUDP_SocketCommuntication()
{
	m_UdpSocket = socket(PF_INET, SOCK_DGRAM, 0);
	
	if ( m_UdpSocket == INVALID_SOCKET )
	{

	}
}

CUDP_SocketCommuntication::~CUDP_SocketCommuntication()
{
	closesocket( m_UdpSocket );
}

int CUDP_SocketCommuntication::CreateReceiveTask()
{	
	sockaddr_in srv;
	
	srv.sin_family		= PF_INET;
	srv.sin_addr.s_addr = htonl( INADDR_ANY );	// 任何地址
	srv.sin_port		= htons( 1111 );
	
	if ( 0 != bind( m_UdpSocket,
		       (struct sockaddr *)&srv,
		       sizeof(srv) ) )
	{
		closesocket( m_UdpSocket );
		return false;
	}
	
	UINT uThreadId = 0;
	
	HANDLE hThreadHandle = (HANDLE) _beginthreadex( NULL,
													0,
													__ReceiveTask,
													(LPVOID)this,
													0,
													&uThreadId );
	
	if ( INVALID_HANDLE_VALUE == hThreadHandle )
	{
		//LogError
	}
	
	CloseHandle( hThreadHandle );

	return 0;
}

unsigned __stdcall CUDP_SocketCommuntication::__ReceiveTask(LPVOID param)
{
	CUDP_SocketCommuntication *pCommuntication =
									(CUDP_SocketCommuntication*)param;

	char        buf[4096] = {0};
	sockaddr_in client;			// 发送数据过来的地址
	int         len = sizeof(client);

	while( TRUE )
	{
		int result = recvfrom( pCommuntication->m_UdpSocket,
							   buf,
							   sizeof(buf)-1,
							   0,
							   (sockaddr*)&client,
							   (int*)&len);
		
		if ( result > 0 )
		{
			fflush(0);
		}
		::MessageBox( NULL, buf, "", MB_OK );
	}

	return 0;
}


bool CUDP_SocketCommuntication::SendMsg( PCHAR		Msg,
										 int		Len,
										 PCHAR		host,
										 short		port )
{
	signed int		 Sent;
	hostent			*hostdata;

	if ( atoi(host) )	// 是否IP地址为标准形式
	{
		u_long ip = inet_addr( host );
		hostdata  = gethostbyaddr( (PCHAR)&ip,
								   sizeof(ip),
								   PF_INET );
	}
	else	// 否则则可能是机器名
	{
		hostdata = gethostbyname( host );
	}
	
	if ( !hostdata )
	{
		fflush(0);
		return false;
	}
	
	sockaddr_in dest;	// 发送目标地址
	
	dest.sin_family  = PF_INET;
	dest.sin_addr	 = *(in_addr *)(hostdata->h_addr_list[0]);
	dest.sin_port	 = htons( port );

	//数据发送
	Sent = sendto( m_UdpSocket,
				   Msg,
				   Len,
				   0,
				   (sockaddr *)&dest,
				   sizeof(sockaddr_in) );
	
	if ( Sent != Len )
	{
		fflush(0);
		return false;
	}
	
	return true;
}
