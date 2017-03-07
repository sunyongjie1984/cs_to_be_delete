//宝石软体 自动关机服务程序 Bosssoft Automatic Shutdown Ver 1.0
//Designed for 9zi.com Server
//参考代码 codeguru Anish C.V.
//shutdown.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Windows.h"
#include "Winsvc.h"
#include "time.h"

#define  defSERVICENAME			"Bosssoft Automatic Shutdown"
#define  defVER					"1.0.0727"
#define  defSERVICEDISPLAYNAME	"Automatic Shutdown"
#define  defCOMMANDHELP			"\nshutdown [-i | -u]\n\n   -i    Install Service\n   -u    Uninstall Service\n   -s    Power Off\n   -r    Reboot\n   -l    Log Off\n   -a    Abort Shutdown"
#define  defDEFAULTDELAY        10

typedef enum {
	eSHUTDOWN = 0,	//关机
	eREBOOT,		//重起
	eLOGOFF,		//注销
	eMORE
}ESHUTDOWN_PARAMETER;

SERVICE_STATUS g_ServiceStatus;
SERVICE_STATUS_HANDLE g_ServiceStatusHandle;
BOOL g_bRunning=true;
char g_strINIDir[MAX_PATH] = {0};

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
void WINAPI ServiceCtrlHandler(DWORD Opcode);
BOOL InstallService();
BOOL DeleteService();
BOOL Shutdown(ESHUTDOWN_PARAMETER eParam);
BOOL AbordShutdown();
int IsTimeNow();//时间到了返回１，没到返回０，用户没有设置，就返回－１指示程序退出
BOOL setPathToReg(LPSTR lpPath);

void test();
int main(int argc, char* argv[])
{
	printf("\n%s [Ver: %s]\n", defSERVICENAME, defVER);
	if(argc>1)
	{
		if(strcmp(argv[1],"-I")==0 || strcmp(argv[1], "-i")==0)
		{
			if(InstallService())
				printf("\nService Installed Successfully!");
			else
				printf("\nError Installing Service!");
		}
		else if(strcmp(argv[1],"-U")==0 || strcmp(argv[1], "-u")==0)
		{
			if(DeleteService())
				printf("\nService UnInstalled Sucessfully!");
			else
				printf("\nError UnInstalling Service!");
		}
		else if(strcmp(argv[1],"-S")==0 || strcmp(argv[1], "-s")==0)
		{
			Shutdown(eSHUTDOWN);
		}
		else if(strcmp(argv[1],"-R")==0 || strcmp(argv[1], "-r")==0)
		{
			Shutdown(eREBOOT);
		}
		else if(strcmp(argv[1],"-L")==0 || strcmp(argv[1], "-l")==0)
		{
			Shutdown(eLOGOFF);
		}
		else if(strcmp(argv[1],"-A")==0 || strcmp(argv[1], "-a")==0)
		{
			AbordShutdown();
		}
		else
		{
			printf("\nUnknown Switch Usage\n%s", defCOMMANDHELP);
		}
	}
	else
	{
		printf("%s", defCOMMANDHELP);
		SERVICE_TABLE_ENTRY DispatchTable[]={{defSERVICENAME,ServiceMain},{NULL,NULL}};  
		StartServiceCtrlDispatcher(DispatchTable); 
	}
	printf("\n");
	return 0;
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
//	DWORD status; 
//	DWORD specificError; 
	g_ServiceStatus.dwServiceType        = SERVICE_WIN32; 
	g_ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
	g_ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP; 
	g_ServiceStatus.dwWin32ExitCode      = 0; 
	g_ServiceStatus.dwServiceSpecificExitCode = 0; 
	g_ServiceStatus.dwCheckPoint         = 0; 
	g_ServiceStatus.dwWaitHint           = 0; 

	g_ServiceStatusHandle = RegisterServiceCtrlHandler(defSERVICENAME,ServiceCtrlHandler);  
	if (g_ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0) 
	{ 
		return; 
	}

	g_ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
	g_ServiceStatus.dwCheckPoint         = 0; 
	g_ServiceStatus.dwWaitHint           = 0;  
	if (!SetServiceStatus (g_ServiceStatusHandle, &g_ServiceStatus)) 
	{ //失败

	} 
	g_bRunning=true;
	while(g_bRunning)
	{
		int nRe = IsTimeNow();
		if(nRe == -1)//错误设置时间，退出
			break;
		if(nRe == 1)
			Shutdown(eSHUTDOWN);
		Sleep(950);//小于1秒钟timer一次
	}
	return; 
}

void WINAPI ServiceCtrlHandler(DWORD Opcode)
{
	switch(Opcode) 
	{ 
	case SERVICE_CONTROL_PAUSE: 
		g_ServiceStatus.dwCurrentState = SERVICE_PAUSED; 
		break; 

	case SERVICE_CONTROL_CONTINUE: 
		g_ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
		break; 

	case SERVICE_CONTROL_STOP: 
		g_ServiceStatus.dwWin32ExitCode = 0; 
		g_ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
		g_ServiceStatus.dwCheckPoint    = 0; 
		g_ServiceStatus.dwWaitHint      = 0; 

		SetServiceStatus (g_ServiceStatusHandle,&g_ServiceStatus);
		g_bRunning=false;
		break;

	case SERVICE_CONTROL_INTERROGATE: 
		break; 
	}      
	return; 
}

BOOL InstallService()
{

	char strDir[MAX_PATH];
	SC_HANDLE schSCManager,schService;
	
	GetCurrentDirectory(sizeof(strDir),strDir);

	if(!setPathToReg(strDir))//安装到注册表中
		return FALSE;


	strcat(strDir,"\\shutdown.exe"); 

	schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS); 

	if (schSCManager == NULL) 
		return false;

	LPCTSTR lpszBinaryPathName=strDir;

	schService = CreateService(schSCManager,defSERVICENAME, defSERVICEDISPLAYNAME,// service name to display 
		SERVICE_ALL_ACCESS,        // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 
		SERVICE_AUTO_START,      // start type 自动执行
		SERVICE_ERROR_NORMAL,      // error control type 
		lpszBinaryPathName,        // service's binary 
		NULL,                      // no load ordering group 
		NULL,                      // no tag identifier 
		NULL,                      // no dependencies 
		NULL,                      // LocalSystem account 
		NULL);                     // no password 

	if (schService == NULL) 
		return false;  

	StartService(schService, 0, NULL);//自动开始

	CloseServiceHandle(schService); 
	return true;
}

BOOL DeleteService()
{
	SC_HANDLE schSCManager;
	SC_HANDLE hService;

	schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	if (schSCManager == NULL) 
		return false;	

	hService=OpenService(schSCManager,defSERVICENAME,SERVICE_ALL_ACCESS);

	if (hService == NULL) 
		return false;

	if(DeleteService(hService)==0)
		return false;

	if(CloseServiceHandle(hService)==0)
		return false;
	else
		return true;
}

void ErrorHandler(LPSTR pszMsg)
{
	printf(pszMsg);
}

#define BUFSIZE 80

BOOL setPathToReg(LPSTR lpPath)
{
	HKEY hKey;
	LONG lRet;

	lRet = RegCreateKey( HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Bosssoft\\BossShutdown",&hKey );
	if( lRet != ERROR_SUCCESS )
		return FALSE;

	lRet = RegSetValueEx( hKey, "Path", NULL, REG_SZ,
		(LPBYTE) lpPath, lstrlen(lpPath));
	if( (lRet != ERROR_SUCCESS))
		return FALSE;
	return TRUE;
}

char *getIniFileName()//得到INI文件地址，如果第一次生成，则自动得到当前文件名
{
	if(g_strINIDir[0] == 0)
	{
		HKEY hKey;
		char  szPath[BUFSIZE];
		DWORD dwBufLen=BUFSIZE;
		LONG lRet;

		lRet = RegOpenKey(HKEY_LOCAL_MACHINE,
			"SOFTWARE\\Bosssoft\\BossShutdown",
			&hKey );
		if( lRet != ERROR_SUCCESS )
			return NULL;

		lRet = RegQueryValueEx( hKey, "Path", NULL, NULL,
			(LPBYTE) szPath, &dwBufLen);
		if( (lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE) )
			return NULL;
		strcpy(g_strINIDir, szPath);
		strcat(g_strINIDir, "\\shutdown.ini");
	}
	return g_strINIDir;
}


BOOL Shutdown(ESHUTDOWN_PARAMETER eParam)
{
	if(eParam == eSHUTDOWN || eParam == eREBOOT)//需要延迟计数的
	{
		UINT nDelay = ::GetPrivateProfileInt(_T("Config"), _T("AlertDelay"), defDEFAULTDELAY, getIniFileName());//取延长时间
		//从注册表中读取延迟时间
		::WritePrivateProfileString(_T("Config"), _T("AbortFlag"), "FALSE", getIniFileName());
		//初始化，强行设置终止标志为FALSE;
		while(nDelay>0)
		{
			nDelay --;

			if(nDelay > 0)
				Beep(1000, 100); //每次1秒钟
			else
				Beep(2000, 200);
			Sleep(900);

			char buf[_MAX_PATH] = {0};
			::GetPrivateProfileString(_T("Config"), _T("AbortFlag"), "FALSE" , buf, sizeof(buf), getIniFileName());
			if(strcmp(buf, "TRUE") == 0)//用户终止设置
				return FALSE;
		}
	}

	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	// Get a token for this process. 
	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		return( FALSE ); 
	// Get the LUID for the shutdown privilege. 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
		&tkp.Privileges[0].Luid); 

	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

	// Get the shutdown privilege for this process. 

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
		(PTOKEN_PRIVILEGES)NULL, 0); 

	if (GetLastError() != ERROR_SUCCESS) 
		return FALSE; 

	// Shut down the system and force all applications to close. 

	UINT nShutdownCode = EWX_SHUTDOWN;
	switch(eParam) {
	case eSHUTDOWN:
		//nShutdownCode = EWX_SHUTDOWN;
		break;
	case eREBOOT:
		nShutdownCode = EWX_REBOOT;
		break;
	case eLOGOFF:
		nShutdownCode = EWX_LOGOFF;
		break;
	default:
		break;
	}
	if (!ExitWindowsEx(nShutdownCode | EWX_FORCE, 0)) 
		return FALSE; 

	return TRUE;
}

BOOL Shutdown2(ESHUTDOWN_PARAMETER eParam)
{
	HANDLE hToken; // handle to process token 
	TOKEN_PRIVILEGES tkp; // pointer to token structure 
	BOOL fResult; // system shutdown flag 

	// Get the current process token handle so we can get shutdown 
	// privilege. 
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		ErrorHandler("OpenProcessToken failed."); 
		return FALSE;
	}

	// Get the LUID for shutdown privilege. 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1; // one privilege to set 
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	// Get shutdown privilege for this process. 

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
	// Cannot test the return value of AdjustTokenPrivileges. 

	if (GetLastError() != ERROR_SUCCESS)
	{
		ErrorHandler("AdjustTokenPrivileges enable failed."); 
		return FALSE;
	}

	// Display the shutdown dialog box and start the time-out countdown. 
	fResult = InitiateSystemShutdown( NULL, // shut down local computer 
		"宝石软体自动关机\n正在准备自动关机\n请输入shutdown -a终止关机", // message to user 
		40, // time-out period 
		FALSE, // ask user to close apps 
		TRUE); // reboot after shutdown 

	if (!fResult) 
	{
		ErrorHandler("InitiateSystemShutdown failed."); 
		return FALSE;
	} 
	// Disable shutdown privilege. 
	tkp.Privileges[0].Attributes = 0; 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
	if (GetLastError() != ERROR_SUCCESS) 
	{
		ErrorHandler("AdjustTokenPrivileges disable failed."); 
		return FALSE;
	} 
	return TRUE;
}


BOOL AbordShutdown()
{
	::WritePrivateProfileString(_T("Config"), _T("AbortFlag"), "TRUE", getIniFileName());//设置终止标志
	return TRUE;
}
BOOL AbordShutdown2()
{
	HANDLE hToken; // handle to process token 
	TOKEN_PRIVILEGES tkp; // pointer to token structure 
	BOOL fResult; // system shutdown flag 

	// Get the current process token handle so we can get shutdown 
	// privilege. 
	if (!OpenProcessToken(GetCurrentProcess(), 	TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		ErrorHandler("OpenProcessToken failed.");
		return FALSE;
	}
	// Get the LUID for shutdown privilege. 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
	tkp.PrivilegeCount = 1; // one privilege to set 
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	// Get shutdown privilege for this process. 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 
	// Cannot test the return value of AdjustTokenPrivileges. 
	if (GetLastError() != ERROR_SUCCESS) 
	{
		ErrorHandler("AdjustTokenPrivileges enable failed.");
		return FALSE;
	}
	// Prevent the system from shutting down. 
	fResult = AbortSystemShutdown(NULL); 
	if (!fResult) 
	{ 
		ErrorHandler("AbortSystemShutdown failed.");
		return FALSE;
	} 
	// Disable shutdown privilege. 
	tkp.Privileges[0].Attributes = 0; 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
	if (GetLastError() != ERROR_SUCCESS) 
	{
		ErrorHandler("AdjustTokenPrivileges disable failed.");
		return FALSE;
	}
	return TRUE;
}



BOOL g_bInited = FALSE;
int  g_nHour = 0;
int  g_nMin  = 0;
int  g_nSec  = 0;

BOOL getUserTime()//得到用户输入的关机时间
{
	char buf[_MAX_PATH] = {0};
	DWORD dwSize= ::GetPrivateProfileString(_T("Config"), _T("ShutdownTime"), "" , buf, sizeof(buf), getIniFileName());
	if(dwSize == 0)//用户没设置
		return FALSE;
	char szHour[100] = {0};
	char szMin[100]  = {0};
	char szSec[100]  = {0};

	int nCount = 0;
	int nTokey = 0;//0->hour, 1->min, 2->Sec
	for(DWORD i=0; i<dwSize; i++)
	{
		if(nCount >= 100)//谁那么无聊啊，输那么长
		{
			g_bInited = FALSE;		
			return FALSE;
		}
		if(buf[i] == ':')
		{
			nCount = 0;		
			nTokey ++;
			if(nTokey>2)
				break;
		}
		else if(buf[i] >= '0' && buf[i] <= '9')
		{
			switch(nTokey) {
			case 0:
				szHour[nCount] = buf[i];
				break;
			case 1:
				szMin[nCount] = buf[i];
				break;
			case 2:
				szSec[nCount] = buf[i];
				break;
			default:
				break;
			}
			nCount ++;
		}
		else if(buf[i] == ' ')//跳过空格
			nCount ++;
		else//非需要的数字
		{
			g_bInited = FALSE;
			return FALSE;
		}
	}
	g_nHour = atoi(szHour);
	g_nMin  = atoi(szMin);
	g_nSec  = atoi(szSec);
	g_bInited = TRUE;
	return TRUE;
}


int IsTimeNow()//时间到了返回１，没到返回０，用户没有设置，就返回－１指示程序退出
{
	if(!g_bInited)
	{
		if(!getUserTime())//没取出来失败
			return -1;
	}

	__time64_t long_time_now;
	_time64( &long_time_now );                /* Get time as long integer. */
	struct tm *pnow = _localtime64( &long_time_now ); /* Convert to local time. */
	if(pnow->tm_hour == g_nHour && pnow->tm_min == g_nMin && pnow->tm_sec == g_nSec)
		return 1;//时间正确，关机

    return 0;
}

void test()
{
	while(g_bRunning)
	{
		//循环逻辑，判断时间是否正确
		int nRe = IsTimeNow();
		if(nRe == -1)//错误设置时间，退出
			return;
		if(nRe == 1)
			Shutdown(eSHUTDOWN);
		Sleep(950);//小于1秒钟timer一次
		//if(is time now)
		//shutdown delay waiting for user stop.
		//
	}
}