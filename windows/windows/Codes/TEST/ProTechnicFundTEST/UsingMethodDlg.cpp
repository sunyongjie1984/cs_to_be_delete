// UsingMethodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "UsingMethodDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsingMethodDlg dialog


CUsingMethodDlg::CUsingMethodDlg(CWnd* pParent /*=NULL*/)
				: CDialog(CUsingMethodDlg::IDD, pParent)
				
{
	//{{AFX_DATA_INIT(CUsingMethodDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUsingMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsingMethodDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsingMethodDlg, CDialog)
	//{{AFX_MSG_MAP(CUsingMethodDlg)
	ON_BN_CLICKED(IDC_USING_CSTRINGARRAY, OnUsingCstringarray)
	ON_BN_CLICKED(IDC_WRITE_FILE, OnWriteFile)
	ON_BN_CLICKED(ID_STATIC_INSTANCE_CLASS, OnStaticInstanceClass)
	ON_BN_CLICKED(ID_WRITE_RECORD_INTO_DB, OnWriteRecordIntoDb)
	ON_BN_CLICKED(ID_READ_CONNECT_DB_CONFIGURATION_FILE, OnReadConnectDbConfigurationFile)
	ON_BN_CLICKED(IDC_NUMBER_AND_CHARACTER_STRING_CONVERSION, OnNumberAndCharacterStringConversion)
	ON_BN_CLICKED(IDC_CONNECT_PROCESS_COMMUNICATION, OnConnectProcessCommunication)
	ON_BN_CLICKED(ID_READ_RECORD_IN_DB, OnReadRecordInDb)
	ON_BN_CLICKED(ID_DELETE_RECORD_FROM_DB, OnDeleteRecordFromDb)
	ON_BN_CLICKED(ID_TEST_ARRAY_SLOP_OVER, OnTestArraySlopOver)
	ON_BN_CLICKED(IDC_CREATE_SPECIFY_REGEDIT_KEY, OnCreateSpecifyRegeditKey)
	ON_BN_CLICKED(IDC_READ_SPECIFY_REGEDIT_KEY, OnReadSpecifyRegeditKey)
	ON_BN_CLICKED(IDC_LONG_DISTANCE_CLOSE_COMPETER, OnLongDistanceCloseCompeter)
	ON_BN_CLICKED(IDC_UDP_CONNECT_COMMUNICATION, OnUdpConnectCommunication)
	ON_BN_CLICKED(ID_TEST_LOAD_RESOURCE, OnTestLoadResource)
	ON_BN_CLICKED(IDC_GET_HOST_COMPUTER_INFO, OnGetHostComputerInfo)
	ON_BN_CLICKED(IDC_TEST_ACE_COMMUNICATION, OnTestAceCommunication)
	ON_BN_CLICKED(ID_TEST_USING_POINT, OnTestUsingPoint)
	ON_BN_CLICKED(IDC_GET_COMPUTER_NAME, OnGetComputerName)
	ON_BN_CLICKED(IDC_TEST_ACE_SEND, OnTestAceSend)
	ON_BN_CLICKED(ID_TEST_GLOBAL_VARIABLE, OnTestGlobalVariable)
	ON_BN_CLICKED(ID_EMS_MEMORY_LEAK, OnEmsMemoryLeak)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsingMethodDlg message handlers

void CUsingMethodDlg::OnUsingCstringarray() 
{
	CStringArray strTestArray;
	CString      strTest = "Ares";
	
	for ( int m = 0; m < 10; m++ )
	{
		strTestArray.Add(strTest);
	}
	for ( int n = 0; n < 10; n++ )
	{
		strTest += strTestArray[n] + "\n";
	}
	::MessageBox( this->m_hWnd, strTest, "", MB_OK );	
}

void CUsingMethodDlg::OnWriteFile() 
{
	//先用软盘创建.img镜像然后把boot.bin写入boot.img再用虚拟机创建.vhd镜像然后把boot.img写入.vhd
	HANDLE hFile = CreateFile( "F:\\CODE\\BOOT.img",
							   GENERIC_WRITE | GENERIC_READ,
							   0,
							   NULL,
							   OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,
							   NULL);

	BYTE bt[512];

	memset(bt,0,512);

	DWORD dwRead;

	ReadFile( hFile,
			  bt,
			  512,
			  &dwRead,
			  NULL );
	
	CloseHandle(hFile);
	
	HANDLE rFile = CreateFile( "F:\\CODE\\a.vhd",
							   GENERIC_WRITE | GENERIC_READ,
							   0,
							   NULL,
							   OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,
							   NULL );

	WriteFile( rFile,
			   bt,
			   512,
			   &dwRead,
			   NULL );
	
	CloseHandle(rFile);
	
/*	
	unsigned char szBuffer[1024];

	memset( szBuffer, 0, sizeof(char)*1024 );

	UINT uSize = 512;
	CFileOperateClass::ReadFile( szBuffer, uSize, "F:\\CODE\\boot.bin");

	CFileOperateClass::WriteFile( szBuffer, uSize, "F:\\CODE\\BOOT.IMA");
	*/
}

void CUsingMethodDlg::OnStaticInstanceClass() 
{
	// TODO: Add your control notification handler code here
	
}

void CUsingMethodDlg::OnWriteRecordIntoDb() 
{
	CVisitDatabaseInterface * pVisitDB = CVisitDatabaseInterface::Instance();

	if ( NULL == pVisitDB )
	{
		return;
	}

	CFileAuditLogInfo       auditRecord;
	CFileAuditLogInfoArray  auditRecordArray;

	CFileOperateDlg dlg( this );

	if ( IDOK == dlg.DoModal() )
	{
		int nLoopCount = dlg.m_nInsertRecordcount;
		
		for ( int m = 0; m < nLoopCount; m++ )
		{
			for ( int n = 0; n < 100; n++ )
			{
				auditRecord.m_computer_name = "TEST1_1";
				auditRecord.m_lIsNetCall    = 1;
				auditRecord.m_new_path      = "C:\\TEST";
				auditRecord.m_old_path      = "D:\\TEST";
				auditRecord.m_operate_time  = 11212333;
				auditRecord.m_operate_type  = 2;
				auditRecord.m_os_version    = 6;
				auditRecord.m_strCurrentUserName = "TESTA";
				
				auditRecordArray.push_back( auditRecord );
			}
			
			if ( -1 == pVisitDB->RecordWriteIntoDatabase( auditRecordArray ) )
			{
				
			}
			
			::Sleep( 1000 * dlg.m_nInsertRecordTimeAlternation );
		}
	}	
}


BOOL FileNameWhetherEmpty ( PCHAR szFileName )				/////保存第一个字符的位置
{
	PCHAR lpTest = strchr( szFileName, '.' );				/////得到要找的字符的位置

	int nPos = lpTest - szFileName;							/////获得所得字符在字符串中的位置
	
	/////判断是否输入的是"."开头的文件名（系统认为"."开头的文件名是没有输入文件名--与系统保持一致）
	if ( 0 == nPos )
	{
		/////判断是否输入的是"."开头的文件名
		CShareResource::HintMessageBox( NULL,
										IDS_FILE_NAME_CANNOT_EMPTY,
										IDS_HINT,
										MB_OK );
		
		return TRUE;
	}

	return FALSE;
}

BOOL FileNameWhetherNonlicet( PCHAR szFileName )
{	
	//-----------------------判断是否输入的是"."开头的文件名----------------------------------//
	BOOL bResult = FileNameWhetherEmpty ( szFileName );

	if ( bResult )
	{
		return TRUE;
	}

	PCHAR lpTest = NULL;
		
	//------------在字符串中查找指定字符判断是否输入的是非法文件名---------------------------------//
	char szNonlicetCharacter[] = { '/', '<', '>', '?', ':', '*', '|', '\\' };	/////指定查找的字符
	
	for ( int i = 0; i < strlen( szNonlicetCharacter ); i++ )
	{
		lpTest = strchr( szFileName, szNonlicetCharacter[i] );		/////得到要找的字符的位置

		if ( NULL != lpTest )
		{
			CShareResource::HintMessageBox( NULL,
											IDS_HINT_FILE_NAME_BE_OUTSIDE_THE_LAW,
											IDS_HINT,
											MB_OK );
			
			return TRUE;
		}
	}
	
	return FALSE;
}

void CUsingMethodDlg::OnReadConnectDbConfigurationFile() 
{
	CFileOperateDlg dlg( this );
	
	if ( IDOK == dlg.DoModal() )
	{
		CHAR szFileFullPathName[MAX_PATH] = {0};
		
		//是否是合法文件名判断
		BOOL bResult = FileNameWhetherNonlicet( dlg.m_strFileName.GetBuffer(0) );

		if ( bResult )
		{
			//文件名不合法
			return;
		}
		::MessageBox( NULL, "SUCCESS", "", MB_OK );
		return;
		//-------------------------------------------------------------------------------------------//
		strcpy( szFileFullPathName, dlg.m_strFileName );
		
		CFileOperateClass::GetFilePath( szFileFullPathName );
		
#ifdef _DEBUG
		CString strFilePath;
		
		strFilePath.LoadString( IDS_FILE_PATH );
		
		::MessageBox( this->m_hWnd, szFileFullPathName, strFilePath, MB_OK );
		
		//		OutputDebugString( strFileFullPathName.c_str() );
#endif
		
		string strConnectStr;
		string strUseID;
		string strPassWord;
		string strIp;
		
		int nStatus =
			CFileOperateClass::ParseConnectDbConfigurationFile(
														strConnectStr,
														strUseID,
														strPassWord,
														strIp,
														szFileFullPathName );
		if ( -1 == nStatus )
		{
			return;
		}
	}	
}

void CUsingMethodDlg::OnNumberAndCharacterStringConversion() 
{
	string strTest = "9";
	int nTest = 0;
	nTest = atoi( strTest.c_str() );
	strTest = "";
	char szTest[1] = {0};
	sprintf(szTest,"%d",nTest);
	::MessageBox(0,szTest,"",0);
}

void CUsingMethodDlg::OnConnectProcessCommunication() 
{
	CTCP_SocketCommuntication::StartNetWorkListenTask();
	CFileOperateDlg dlg( this );
	
	if ( IDOK == dlg.DoModal() )
	{

	}
}

void CUsingMethodDlg::OnReadRecordInDb() 
{
	m_iVisitDBTask.activate();
}

void CUsingMethodDlg::OnDeleteRecordFromDb() 
{
	ACE_Process_Mutex	m_FileOpeateProcessMutex("SC_FILEMANAGE_MUTEX");
	
//	ACE_GUARD_RETURN( ACE_Process_Mutex, obj, m_FileOpeateProcessMutex, ; );

	CVisitDatabaseInterface * pVisitDB = CVisitDatabaseInterface::Instance();
	
	if ( NULL == pVisitDB )
	{
		return;
	}

	if ( NULL != pVisitDB->m_pRecord )
	{
		if ( adStateClosed == pVisitDB->m_pRecord->State )
		{
			return;
		}
		pVisitDB->m_pRecord->Close();
	}
	
//	pVisitDB->m_pRecord->adoEOF;//关闭记录集指针后使用报错

	while ( TRUE )
	{
//		Sleep( 1000*20 );
		break;
	}
	if ( -1 == pVisitDB->DeleteAuditLogFromDB() )
	{
		
	}	
}

void CUsingMethodDlg::OnTestArraySlopOver() 
{	
	PCOMMUNICATION_DATA iReceive  = NULL;
	
	memset( iReceive, 0, sizeof(COMMUNICATION_DATA) );
	
	CHAR szTestMemsetArray[1024];

	memset( szTestMemsetArray, 0, sizeof(szTestMemsetArray) );

	strcpy( szTestMemsetArray,
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

	::MessageBox( this->m_hWnd, szTestMemsetArray, "", MB_OK );

	CHAR szTestArray[1024] = {0};

	strcpy( szTestArray,
			"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" );

	::MessageBox( this->m_hWnd, szTestArray, "", MB_OK );

	CHAR szTestSizeofArray[1024];

	memset( szTestSizeofArray, 0, sizeof(CHAR)*1024 );

	strcpy( szTestSizeofArray,
			"cccccccccccccccccccccccccccccccccccccccccc" );

	::MessageBox( NULL, szTestSizeofArray, "", MB_OK );

	CHAR szTestSlop_Over[10] = {0};

	strcpy( szTestSlop_Over, "1234567891011121314" );

	CHAR szTest[50];
	
	int nlength = sizeof( CHAR );
	memset( szTest, 0, 50 * nlength );

	strcpy( szTest,
			"rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr");

	memset( szTest, 0, 20 );
}

void CUsingMethodDlg::OnCreateSpecifyRegeditKey() 
{
	DWORD dwData = EVENTLOG_ERROR_TYPE |
				   EVENTLOG_WARNING_TYPE |
				   EVENTLOG_INFORMATION_TYPE;
	
	CControlRegedit::CreateSpecifyRegeditKey( HKEY_LOCAL_MACHINE,
											  "SOFTWARE\\JiangMin\\KV2004\\Install",
											  "test",
											  dwData );
}

void CUsingMethodDlg::OnReadSpecifyRegeditKey() 
{
	DWORD dwKeyValue = 0;

	CControlRegedit::ReadSpecifyRegeditKeyValue( HKEY_LOCAL_MACHINE,
											     "SOFTWARE\\JiangMin\\KV2004\\Install",
												 "test",
												 dwKeyValue );
	
	CHAR szTestRegeditKeyValue[2];

	memset( szTestRegeditKeyValue, 0, (sizeof( CHAR ) * 2) );

	sprintf( szTestRegeditKeyValue, "%x", dwKeyValue );

	::MessageBox( this->m_hWnd, szTestRegeditKeyValue, "", MB_OK );
}

void CUsingMethodDlg::OnLongDistanceCloseCompeter() 
{
	
}

void CUsingMethodDlg::OnUdpConnectCommunication() 
{
	CFileOperateDlg dlg( this );

	if ( IDOK == dlg.DoModal() )
	{
	}
}

void CUsingMethodDlg::OnTestLoadResource() 
{
	int nTest = CShareResource::HintMessageBox( this->m_hWnd,
												IDS_CONFIGURATION_ERROR_HINT,
												IDS_HINT,
												MB_OK );
}

void CUsingMethodDlg::OnGetHostComputerInfo() 
{
	CHAR szName[MAX_PATH] = {0};

	////得到主机名
	int nStatus = gethostname( szName, sizeof(char)*MAX_PATH );

	if ( 0 != nStatus )
	{
		AfxMessageBox(" fail ");
		return;
	}

	struct hostent * pHost;

	CHAR szIP[MAX_PATH] = {0};

	CHAR szType[MAX_PATH] = {0};

	pHost = gethostbyname( szName );

	for ( int i = 0; ( (NULL != pHost) && (NULL != pHost->h_addr_list[i]) ); i++ )
	{
		int test = pHost->h_addrtype;			///// 返回地址的类型对于winsock,这个域是AF_INET						
		int nAddrLength = pHost->h_length;		///// 每个地址的长度，对应AF_INET这个域为4
		strcpy( szName, pHost->h_name);			///// 正规主机名
//		strcpy( szType, pHost->h_aliases[i] );	///// 可选主机名队列
		strcpy( szIP, inet_ntoa( *(struct in_addr *)pHost->h_addr_list[0] ) );
	}
}

void CUsingMethodDlg::OnTestAceCommunication() 
{
	ACE_Server::ServerStart();	
}

void CUsingMethodDlg::OnTestUsingPoint() 
{
	PCHAR	pChar = NULL;
	strcpy( pChar, "haha" );	
}

void CUsingMethodDlg::OnGetComputerName() 
{
	CHAR szComputerName[MAX_PATH] = {0};

	DWORD dwSize = MAX_PATH;

	::GetComputerName( szComputerName, &dwSize );

	::MessageBox( NULL, szComputerName, "", MB_OK );

	// UpdateData(FALSE);
}

void CUsingMethodDlg::OnTestAceSend() 
{
	//获得IP地址
	string_list strIpArr = HelpTools::get_server_ip( "192.168.0.206" );

	//连接服务端
	ACE_SOCK_Stream iStream;
	
	int nResult = -1;

	while ( TRUE )
	{
		nResult = HelpTools::connect( iStream, strIpArr, 2800 );
		
		if ( -1 == nResult )
		{
			::MessageBox( NULL, "fail", "connect", MB_OK );
		}
		else
		{
			break;
		}
	}
	
	//发送消息头
	CHAR szHeaderMsg[1024] = "send to";

	ssize_t sendResult = iStream.send_n( (PCHAR)szHeaderMsg, (sizeof(char) * 1024) );

	if ( -1 == sendResult )
	{
		iStream.close();
		::MessageBox( NULL, "fail", "send", MB_OK );
	}
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
extern DWORD  g_dwTestGlobal;		/////用于测试全局变量在不同文件之间的访问

extern HANDLE g_hTestEvent;			/////用于测试全局事件变量在不同文件之间的访问
/*
extern char	* g_szTestGlobal;
*/
extern char	  g_szTestGlobal[];

static unsigned _stdcall TestTaskA(LPVOID param)
{
	DWORD dwStatus = 0;

	while (TRUE)
	{
		dwStatus = WaitForSingleObject( g_hTestEvent, 1 );
		
		if ( WAIT_OBJECT_0 == dwStatus )
		{
			MessageBox( NULL, "TestTaskA", "", MB_OK );
			break;			
		}
	}
	
	return 0;
}

static unsigned _stdcall TestTaskB(LPVOID param)
{
	DWORD dwStatus = 0;
	
	while (TRUE)
	{
		dwStatus = WaitForSingleObject( g_hTestEvent, 1 );
		
		if ( WAIT_OBJECT_0 == dwStatus )
		{
			MessageBox( NULL, "TestTaskB", "", MB_OK );
			break;			
		}
	}
	
	return 0;
}

void CUsingMethodDlg::OnTestGlobalVariable()
{
	for ( int i = 0; i < 2; i++ )
	{
		UINT uThreadid = 0;
		
		HANDLE hReceiveThread = (HANDLE)_beginthreadex( NULL,
														0,
														TestTaskA,
														NULL,
														0,
														&uThreadid );
		
		if ( INVALID_HANDLE_VALUE == hReceiveThread )
		{		
			return;
		}
		
		CloseHandle( hReceiveThread );		
	}

	UINT uThreadid = 0;
	
	HANDLE hReceiveThread = (HANDLE)_beginthreadex( NULL,
													0,
													TestTaskB,
													NULL,
													0,
													&uThreadid );
	
	if ( INVALID_HANDLE_VALUE == hReceiveThread )
	{		
		return;
	}
	
	CloseHandle( hReceiveThread );

	CHAR szTestGlobal[MAX_PATH];

	g_dwTestGlobal = 8;
	
	memset( szTestGlobal, 0, sizeof(char) * MAX_PATH );

	sprintf( szTestGlobal, "%d", g_dwTestGlobal );

	::MessageBox( NULL, szTestGlobal, "", MB_OK );

	::MessageBox( NULL, g_szTestGlobal, "OnTestGlobalVariable()", MB_OK );
}
//-------------------------------------------------------------------------------//

void CUsingMethodDlg::OnEmsMemoryLeak() 
{
	CFile file;
	file.Open( "", "rb" );
	CString strFileName = file.GetFileName();
	PCHAR szTest = new char [sizeof(10000)];
	// 程序退出时加入以下函数：	
	_CrtDumpMemoryLeaks();
}
