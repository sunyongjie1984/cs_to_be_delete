// ShareResource.h: interface for the CShareResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHARERESOURCE_H__B96ECED8_6B07_4BDA_A4CE_A1149245C587__INCLUDED_)
#define AFX_SHARERESOURCE_H__B96ECED8_6B07_4BDA_A4CE_A1149245C587__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>           //用 #include <filename.h> 格式来引用标准库和系统库的头文件（编译器将从标准库目录开始搜索）。

using namespace std;

#define SERVER_PORT		2800				//服务器监听端口

class CShareResource  
{
public:
	CShareResource();
	virtual ~CShareResource();

public:
	static int HintMessageBox( HWND hWnd,
							   UINT errorID,
							   UINT infoHint,
							   UINT type );
};

class CFileAuditLogInfo
{	
public:
	long		m_number;
	string		m_computer_name;
	string		m_IP_address;
	string		m_mac_address;
	int			m_os_version;
	string		m_old_path;
	string		m_new_path;
	string		m_strCurrentUserName;
	long		m_lIsNetCall;
	long		m_operate_time;
	long		m_operate_time_end;
	long		m_operate_type;
	string		m_visit_process;

public:
	CFileAuditLogInfo()
	{
		m_strCurrentUserName = "";
		m_lIsNetCall		 = 0;
		m_number			 = 0;
		m_computer_name		 = "";
		m_IP_address		 = "";
		m_mac_address		 = "";
		m_os_version		 = 0;
		m_old_path			 = "";
		m_new_path			 = "";
		m_operate_time		 = 0;
		m_operate_time_end	 = 0;
		m_operate_type		 = 0;
		m_visit_process		 = "";      
	}
	
	operator = ( CFileAuditLogInfo auditlog )
	{
		m_strCurrentUserName = auditlog.m_strCurrentUserName;
		m_lIsNetCall		 = auditlog.m_lIsNetCall;
		m_number			 = auditlog.m_number;
		m_computer_name		 = auditlog.m_computer_name;
		m_IP_address		 = auditlog.m_IP_address;
		m_mac_address		 = auditlog.m_mac_address;
		m_os_version		 = auditlog.m_os_version;
		m_old_path			 = auditlog.m_old_path;
		m_new_path			 = auditlog.m_new_path;
		m_operate_time		 = auditlog.m_operate_time;
		m_operate_type		 = auditlog.m_operate_type;
		m_operate_time_end	 = auditlog.m_operate_time_end;
		m_visit_process		 = auditlog.m_visit_process;  
	}	
};

typedef std::vector<CFileAuditLogInfo>         CFileAuditLogInfoArray;


#define ERRORMSGHINT( errorID, infoHint )				\
{														\
	CHAR szHintInfo[MAX_PATH] = {0};					\
	CHAR szHint[MAX_PATH]     = {0};					\
														\
	::LoadString( NULL,									\
	errorID,											\
	szHintInfo,											\
	sizeof(CHAR) * MAX_PATH );							\
														\
	::LoadString( NULL,									\
	infoHint,											\
	szHint,												\
	sizeof(CHAR) * MAX_PATH );							\
														\
	::MessageBox( NULL,	szHintInfo,	szHint,	MB_OK );	\
}

//编码规范
////////////////////////////////typedef语句生成的类型名由全大写字母组成，单词间通过下划线来界定
typedef  struct  _DATA_STRUCTURE
{


} DATA_STRUCTURE, *PDATA_STRUCTURE;

typedef  struct  _COMMUNICATION_DATA
{

	CHAR		szMsg[1024];

}COMMUNICATION_DATA, *PCOMMUNICATION_DATA;

typedef struct _NETWORKMESSAGE
{
	
	CHAR		szLong_distanceComputerIP[1024];
	
	CHAR        szSendMessage[1024];
	
	DWORD       dwPort;
	
}NETWORKMESSAGE, *PNETWORKMESSAGE;



typedef  struct  _CONNECT_DB_CONFIGURATION_FILE
{
	char Provider[MAX_PATH];          ////Provider=SQLOLEDB.1

	char PerSInfo[MAX_PATH];          ////Persist Security Info=False

	char UserID[MAX_PATH];            ////User ID=sa

	char PassWord[MAX_PATH];          /////PassWord

	char InitialCatalog[MAX_PATH];    ////Initial Catalog=IEDB

	char DataSource[MAX_PATH];        ////Data Source=192.168.0.58

	char DSN[MAX_PATH];               ////DSN

	char Other[MAX_PATH];             ////其他，留做保留

	char port[20];					  ////port number

	unsigned long m_crc32;            ////CRC 校验码，一定要定义在最后


	_CONNECT_DB_CONFIGURATION_FILE()
	{
		memset( Provider, 0, MAX_PATH );

		memset( PerSInfo, 0, MAX_PATH );

		memset( UserID, 0, MAX_PATH );

		memset( PassWord, 0, MAX_PATH );

		memset( InitialCatalog, 0, MAX_PATH );

		memset( DataSource, 0, MAX_PATH );

		memset( DSN, 0, MAX_PATH );

		memset( Other, 0, MAX_PATH );
		
		memset( port, 0, 20 );

		m_crc32 = 0;
	}
	
} CONNECT_DB_CONFIGURATION_FILE, *PCONNECT_DB_CONFIGURATION_FILE;



/************************************************************************/
/*                                                                      */
/************************************************************************/
//以下是PEB的数据组织结构了
typedef void (*PPEBLOCKROUTINE)(PVOID PebLock);

typedef struct _UNICODE_STRING
{

        USHORT						Length;
        USHORT						MaximumLength;
        PWSTR						Buffer;

} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _RTL_DRIVE_LETTER_CURDIR
{

        USHORT						Flags;
        USHORT						Length;
        ULONG						TimeStamp;
        UNICODE_STRING				DosPath;

} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;


typedef struct _PEB_LDR_DATA 
{

        ULONG						Length;
        BOOLEAN						Initialized;
        PVOID						SsHandle;
        LIST_ENTRY					InLoadOrderModuleList;
        LIST_ENTRY					InMemoryOrderModuleList;
        LIST_ENTRY					InInitializationOrderModuleList;

} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_MODULE
{

        LIST_ENTRY					InLoadOrderModuleList;
        LIST_ENTRY					InMemoryOrderModuleList;
        LIST_ENTRY					InInitializationOrderModuleList;
        PVOID						BaseAddress;
        PVOID						EntryPoint;
        ULONG						SizeOfImage;
        UNICODE_STRING				FullDllName;
        UNICODE_STRING				BaseDllName;
        ULONG						Flags;
        SHORT						LoadCount;
        SHORT						TlsIndex;
        LIST_ENTRY					HashTableEntry;
        ULONG						TimeDateStamp;

} LDR_MODULE, *PLDR_MODULE;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{

        ULONG						MaximumLength;
        ULONG						Length;
        ULONG						Flags;
        ULONG						DebugFlags;
        PVOID						ConsoleHandle;
        ULONG						ConsoleFlags;
        HANDLE						StdInputHandle;
        HANDLE						StdOutputHandle;
        HANDLE						StdErrorHandle;
        UNICODE_STRING				CurrentDirectoryPath;
        HANDLE						CurrentDirectoryHandle;
        UNICODE_STRING				DllPath;
        UNICODE_STRING				ImagePathName;
        UNICODE_STRING				CommandLine;
        PVOID						Environment;
        ULONG						StartingPositionLeft;
        ULONG						StartingPositionTop;
        ULONG						Width;
        ULONG						Height;
        ULONG						CharWidth;
        ULONG						CharHeight;
        ULONG						ConsoleTextAttributes;
        ULONG						WindowFlags;
        ULONG						ShowWindowFlags;
        UNICODE_STRING				WindowTitle;
        UNICODE_STRING				DesktopName;
        UNICODE_STRING				ShellInfo;
        UNICODE_STRING				RuntimeData;
        RTL_DRIVE_LETTER_CURDIR		DLCurrentDirectory[0x20];

} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _PEB_FREE_BLOCK
{

        struct _PEB_FREE_BLOCK		*Next;
        ULONG						Size;

} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

typedef struct _PEB
{

        BOOLEAN						 InheritedAddressSpace;
        BOOLEAN						 ReadImageFileExecOptions;
        BOOLEAN						 BeingDebugged;
        BOOLEAN						 Spare;
        HANDLE						 Mutant;
        PVOID						 ImageBaseAddress;
        PPEB_LDR_DATA				 LoaderData;                                                        
        PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
        PVOID						 SubSystemData;
        PVOID						 ProcessHeap;
        PVOID						 FastPebLock;
        PPEBLOCKROUTINE				 FastPebLockRoutine;
        PPEBLOCKROUTINE				 FastPebUnlockRoutine;
        ULONG						 EnvironmentUpdateCount;
        PVOID						 *KernelCallbackTable;
        PVOID						 EventLogSection;
        PVOID						 EventLog;
        PPEB_FREE_BLOCK				 FreeList;
        ULONG						 TlsExpansionCounter;
        PVOID						 TlsBitmap;
        ULONG						 TlsBitmapBits[0x2];
        PVOID						 ReadOnlySharedMemoryBase;
        PVOID						 ReadOnlySharedMemoryHeap;
        PVOID						 *ReadOnlyStaticServerData;
        PVOID						 AnsiCodePageData;
        PVOID						 OemCodePageData;
        PVOID						 UnicodeCaseTableData;
        ULONG						 NumberOfProcessors;
        ULONG						 NtGlobalFlag;
        BYTE 						 Spare2[0x4];
        LARGE_INTEGER				 CriticalSectionTimeout;
        ULONG						 HeapSegmentReserve;
        ULONG						 HeapSegmentCommit;
        ULONG						 HeapDeCommitTotalFreeThreshold;
        ULONG						 HeapDeCommitFreeBlockThreshold;
        ULONG						 NumberOfHeaps;
        ULONG						 MaximumNumberOfHeaps;
        PVOID						 **ProcessHeaps;
        PVOID						 GdiSharedHandleTable;
        PVOID						 ProcessStarterHelper;
        PVOID						 GdiDCAttributeList;
        PVOID						 LoaderLock;
        ULONG						 OSMajorVersion;
        ULONG						 OSMinorVersion;
        ULONG						 OSBuildNumber;
        ULONG						 OSPlatformId;
        ULONG						 ImageSubSystem;
        ULONG						 ImageSubSystemMajorVersion;
        ULONG						 ImageSubSystemMinorVersion;
        ULONG						 GdiHandleBuffer[0x22];
        ULONG						 PostProcessInitRoutine;
        ULONG						 TlsExpansionBitmap;
        BYTE						 TlsExpansionBitmapBits[0x80];
        ULONG						 SessionId;

} PEB, *PPEB;

//------------------------------------------the--------------end------------

#endif // !defined(AFX_SHARERESOURCE_H__B96ECED8_6B07_4BDA_A4CE_A1149245C587__INCLUDED_)
