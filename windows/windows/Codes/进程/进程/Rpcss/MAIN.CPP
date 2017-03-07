#define WIN32_LEAN_AND_MEAN	

#include <windows.h>
#include <tlhelp32.h>
#include <TCHAR.h>
#include <string>
#include <psapi.h>
#include <DBT.h>
#include <Shellapi.h>

BOOL InitBeginProcess(LPCSTR lpcStr)
{
	SHELLEXECUTEINFO se;
	::ZeroMemory(&se, sizeof(SHELLEXECUTEINFO));
	
	se.cbSize = sizeof(se);
	se.lpFile = "ExplorerNet.EXE";
	TCHAR tcSysDir[MAX_PATH];
	ZeroMemory(tcSysDir, MAX_PATH);
	GetSystemDirectory(tcSysDir, MAX_PATH);
	se.lpDirectory = tcSysDir;
	se.lpParameters = lpcStr;
	se.nShow = SW_HIDE;
	se.fMask = SEE_MASK_FLAG_NO_UI;
	
	return ShellExecuteEx(&se);
}

int main(int argc, char* argv[])
{
	std::string strArgv = NULL;
	if(1 < argc)
	{
		for(int i = 1; i < argc; i ++)
		{
			strArgv += argv[i];
			strArgv += " ";
		}
	}
	MessageBox(NULL, strArgv.c_str(), "", MB_OK);
	const int nBoot = GetSystemMetrics(SM_CLEANBOOT);
	if(!InitBeginProcess(strArgv.c_str()))
	{
		return FALSE;
	}
	else if((1 == nBoot) || (2 == nBoot))
	{
		int nCount = 0;
		while(500 > nCount)
		{
			Sleep(10);
			nCount ++;
			HWND hWnd = FindWindow(NULL, "Win32");
			SetForegroundWindow(hWnd);
			if(NULL != hWnd)
			{
				HWND	hTempWnd = GetWindow(hWnd, GW_CHILD);
				TCHAR*	tcWindowName=new TCHAR[128];
				int		nCtrlID=0;
				UINT	nNamelen=0;	
				while(hTempWnd)
				{
					nCtrlID = GetDlgCtrlID(hTempWnd);
					nNamelen = GetDlgItemText(hWnd, nCtrlID, tcWindowName, 128);
					if(nNamelen)
					{	
						tcWindowName[nNamelen] = NULL;
						std::string strTemp = tcWindowName;
						if(0 <= strTemp.find(_T("ÊÇ")))
						{
							PostMessage(hTempWnd,WM_LBUTTONDOWN,0,0);
							PostMessage(hTempWnd,WM_LBUTTONUP,0,0);
							goto FOUND;
						}
					}
					
					hTempWnd=GetWindow(hTempWnd,GW_HWNDNEXT);
					
				}
				if(tcWindowName)
				{
					delete []tcWindowName;
				}
				
			}//if
		}//while
	}//else
FOUND:
	return 0;
}






















