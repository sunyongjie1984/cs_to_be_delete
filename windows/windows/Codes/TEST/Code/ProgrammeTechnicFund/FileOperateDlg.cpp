// FileOperateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "FileOperateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileOperateDlg dialog
CFileOperateDlg::CFileOperateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileOperateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileOperateDlg)
	m_strMessage = _T("");
	m_strFileName = _T("");
	m_strIpAddress = _T("");
	m_nCommunicationPort = 0;
	m_nInsertRecordcount = 0;
	m_nInsertRecordTimeAlternation = 0;
	m_strUserName = _T("");
	m_strPassWord = _T("");
	m_strDescribe = _T("");
	m_strComputerName = _T("");
	//}}AFX_DATA_INIT
}


void CFileOperateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileOperateDlg)
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_IPADDRESS, m_strIpAddress);
	DDX_Text(pDX, IDC_EDIT_LONG_DISTANCE_COMPUTER_PORT, m_nCommunicationPort);
	DDX_Text(pDX, IDC_EDIT_INSERT_RECORD_COUNT, m_nInsertRecordcount);
	DDX_Text(pDX, IDC_EDIT_INSERT_RECORD_TIME_ALTERNATION, m_nInsertRecordTimeAlternation);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassWord);
	DDX_Text(pDX, IDC_EDIT_DESCRIBE, m_strDescribe);
	DDX_Text(pDX, IDC_EDIT_COMPUTERNAME, m_strComputerName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileOperateDlg, CDialog)
	//{{AFX_MSG_MAP(CFileOperateDlg)
	ON_BN_CLICKED(IDC_BUTTON_UDP_SEND, OnButtonUdpSend)
	ON_BN_CLICKED(IDC_BUTTON_UDP_RECEIVE, OnButtonUdpReceive)
	ON_BN_CLICKED(IDC_BUTTON_TCP_SEND, OnTcpSend)
	ON_BN_CLICKED(IDC_BUTTON_UDP_SEND_FILE, OnButtonUdpSendFile)
	ON_BN_CLICKED(IDC_TEST_EVENT, OnTestEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileOperateDlg message handlers
typedef struct _FILEINFO
{
	
	int fileLength;
	char fileName[100];
	
}FILEINFO, *PFILEINFO;

#define SIZEFILE 1024

static unsigned __stdcall ReceiveTask(LPVOID param)
{
	PNETWORK_FILE pCommuntication = (PNETWORK_FILE)param;
	
	sockaddr_in client;			// 发送数据过来的地址
	int         len = sizeof(client);

	CFileDialog dlg(false);	//另存文件
	
	FILEINFO myFileInfo;

	int result = recvfrom( pCommuntication->receiveSocket,
						   (PCHAR)&myFileInfo,
						   sizeof(FILEINFO),
						   0,
						   (sockaddr*)&client,
						   (int*)&len);

	if ( IDOK == dlg.DoModal() )
	{	
		CString fname=dlg.GetPathName();

		CFile fFile( fname, CFile::modeCreate | CFile::modeWrite );
		
		char buf[1024] = {0};

		while( TRUE )
		{
			int result = recvfrom( pCommuntication->receiveSocket,
								   buf,
								   sizeof(buf)-1,
								   0,
								   (sockaddr*)&client,
								   (int*)&len);

			if( 0 == result )		//0表示结束
			{
				fflush(0);
				break;		//接受完毕
			}
			fFile.Write( buf, result );
		}
	}
	
	return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
DWORD		g_dwTestGlobal = 0;		/////用于测试全局变量在不同文件之间的访问

char		g_szTestGlobal[MAX_PATH] = {0};
/////用于测试全局变量在不同文件之间的访问
HANDLE		g_hTestEvent   = CreateEvent( NULL,
										  FALSE,			//用于指明该事件是个自动重置的事件还是一个人工重置的事件的布尔值.当人工重置的事件得到通知时（TRUE），等待该事件的所有线程均变为可调度线程。当一个自动重置的事件得到通知时（FALSE），等待该事件的线程中只有一个线程变为可调度线程。
										  FALSE,			//用于指明该事件处于已通知状态(TRUE)还是未通知状态的布尔值(FALSE)
										  "TestEvent" );


void CFileOperateDlg::OnTestEvent()
{
	strcpy( g_szTestGlobal, "TESTA" );

	::MessageBox( NULL, g_szTestGlobal, "OnTestEvent()", MB_OK );

	SetEvent( g_hTestEvent );	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int CFileOperateDlg::ReceiveFile()
{
	WSADATA wsaData;
	
	int nResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	
	if ( NO_ERROR != nResult )
	{
		
	}

	UdpSocket = socket(PF_INET, SOCK_DGRAM, 0);
	
	if ( UdpSocket == INVALID_SOCKET )
	{
		return -1;
	}
	
	sockaddr_in srv;
	
	srv.sin_family		= PF_INET;
	srv.sin_addr.s_addr = htonl( INADDR_ANY );	// 任何地址
	srv.sin_port		= htons( 1111 );
	
	if ( 0 != bind( UdpSocket,
		(struct sockaddr *)&srv,
		sizeof(srv) ) )
	{
		closesocket( UdpSocket );
		return false;
	}

	receiveSocket.receiveSocket = UdpSocket;

	UINT uThreadId = 0;
	
	HANDLE hThreadHandle = (HANDLE) _beginthreadex( NULL,
													0,
													ReceiveTask,
													(LPVOID)&receiveSocket,
													0,
													&uThreadId );
	
	if ( INVALID_HANDLE_VALUE == hThreadHandle )
	{
		//LogError
	}
	
	CloseHandle( hThreadHandle );

	return 0;
}


BOOL CFileOperateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	ReceiveFile();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileOperateDlg::OnButtonUdpSend() 
{
	char	buffer[4096] = {0};		        // buffer we'll use to store msg read in from stdin
	short	destport;		     	    // port to send to
	CHAR    desthost[20] = {0};			// address of destination machine
	
	UpdateData();

	destport = m_nCommunicationPort;
	strcpy( buffer, m_strMessage.GetBuffer(0) );
	strcpy( desthost,m_strIpAddress.GetBuffer(0) );
	
	m_UdpCommuntication.SendMsg( buffer,
								 strlen(buffer),
								 desthost,
								 destport );
}

void CFileOperateDlg::OnButtonUdpReceive() 
{
	m_UdpCommuntication.CreateReceiveTask();	
}


BOOL SendMessageToLong_distanceComputer( NETWORKMESSAGE connectionData )
{
	WSADATA wsaData;
	
	int iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	
	if ( NO_ERROR != iResult )
	{
		return FALSE;
	}
	
	// Create a socket.
	SOCKET connectionSocket;
	
	connectionSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	
	sockaddr_in clientService;
	
	clientService.sin_family		= AF_INET;
	clientService.sin_addr.s_addr	= inet_addr( connectionData.szLong_distanceComputerIP );
	clientService.sin_port			= htons( connectionData.dwPort );
	
	//connect server
	if ( SOCKET_ERROR == connect( connectionSocket,
		 (SOCKADDR*) &clientService,
		 sizeof(clientService) ) )
	{
		WSACleanup();
		
		return FALSE;
	}
	
	int  bytesSent;
	int  bytesRecv							= SOCKET_ERROR;

	COMMUNICATION_DATA iSendBuffer;
	
	char szCommunicationBuffer[1024]        = {0};
	
	strcpy( iSendBuffer.szMsg,
						connectionData.szSendMessage );
	
//	int nLength = strlen(szCommunicationBuffer);
	int nLength = sizeof (COMMUNICATION_DATA);
	bytesSent = send( connectionSocket,
					  (PCHAR)&iSendBuffer,
					  sizeof (COMMUNICATION_DATA),
					  0 );
	
//	char szReceiceBuffer[10] = {0};
//	
//	recv( connectionSocket, szReceiceBuffer, 9, 0 );
//	
//	::MessageBox( NULL, szReceiceBuffer, "", 0 );

	
	closesocket(connectionSocket);
	
	return TRUE;
}


void CFileOperateDlg::OnTcpSend() 
{
//	for ( int i = 0; i < 200; i++ )
	{
		NETWORKMESSAGE connectionData;
		UpdateData();
		connectionData.dwPort = m_nCommunicationPort;
		strcpy( connectionData.szSendMessage, m_strMessage );
		strcpy( connectionData.szLong_distanceComputerIP, m_strIpAddress );
		
		SendMessageToLong_distanceComputer( connectionData );
		Sleep(100);
	}
}

bool SendMsg( PCHAR	host, short	port )
{
	WSADATA wsaData;
	
	int nResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	
	if ( NO_ERROR != nResult )
	{
		
	}

	SOCKET m_UdpSocket = socket(PF_INET, SOCK_DGRAM, 0);
	
	if ( m_UdpSocket == INVALID_SOCKET )
	{
		return false;
	}

	signed int		 Sent;
	hostent			*hostdata;
	sockaddr_in      dest;	// 发送目标地址
	
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

	dest.sin_family  = PF_INET;
	dest.sin_addr	 = *(in_addr *)(hostdata->h_addr_list[0]);
	dest.sin_port	 = htons( port );
	
/*
		if ( 0 != bind( m_UdpSocket,
						(struct sockaddr *)&dest,
						sizeof(dest) ) )
		{
			closesocket( m_UdpSocket );
			return false;
		}*/
	
	

	
	CFileDialog dlg(true);
	
	if(dlg.DoModal()==IDOK)
	{
		CString strFileName=dlg.GetPathName();
		
		FILEINFO myFileInfo;
		
		CFile myFile;
		
		if( !myFile.Open( strFileName, CFile::modeRead | CFile::typeBinary ) )
		{
			return false;
		}
		
		myFileInfo.fileLength=myFile.GetLength();		//得到文件大小
		
		strcpy(myFileInfo.fileName,myFile.GetFileName());//得到文件名称
		
		//数据发送
		Sent = sendto( m_UdpSocket,
					   (PCHAR)&myFileInfo,
					   sizeof(FILEINFO),
					   0,
					   (sockaddr *)&dest,
					   sizeof(sockaddr_in) );

		myFile.Seek(0,CFile::begin);
		
		char m_buf[SIZEFILE]={0};
		int  num=0;
		
		while ( TRUE )
		{
			num=myFile.Read(m_buf, SIZEFILE);
			
			if(num==0)
			{
				break;
			}
			//数据发送
			Sent = sendto( m_UdpSocket,
						   m_buf,
						   strlen(m_buf),
						   0,
						   (sockaddr *)&dest,
						   sizeof(sockaddr_in) );
			
			if ( Sent != strlen(m_buf) )
			{
				fflush(0);
				return false;
			}
		}
		
		myFile.Close();
	}	
	return true;
}


void CFileOperateDlg::OnButtonUdpSendFile() 
{
	short	destport;		     	    // port to send to
	CHAR    desthost[20] = {0};			// address of destination machine
	
	UpdateData();
	
	destport = m_nCommunicationPort;

	strcpy( desthost, m_strIpAddress.GetBuffer(0) );

	SendMsg( desthost, destport );
}
