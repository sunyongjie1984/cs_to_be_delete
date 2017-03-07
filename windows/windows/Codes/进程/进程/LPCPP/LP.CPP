//////////////////////////////////////////////////////////////// 
// MSDN Magazine -- July 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 and Visual Studio .NET
// Runs in Windows XP and probably Windows 2000 too.
//
// lp -- list processes from command line.
// Illustrates how to use the various iterator classes in EnunmProc.h/cpp
//
#include "stdafx.h"
#include "EnumProc.h"

#define tpf _tprintf	// to hide ugly underbars

// pre-declare functions
void help();

// global switches
BOOL bClassName=FALSE;		// show window classname
BOOL bTitle=FALSE;			// show window title
BOOL bBare=FALSE;				// no header

// check for switch: / or -
inline BOOL isswitch(TCHAR c) { return c==L'/' || c==L'-'; }

//////////////////
// Main entry point
//
int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	// Parse command line. Switches can come in any order.
	//
	for (int i=1; i<argc; i++) {
		if (isswitch(argv[i][0])) {
			for (UINT j=1; j<_tcslen(argv[i]); j++) {
				switch(tolower(argv[i][j])) {
				case 'c':
					bClassName=TRUE;
					break;
				case 't':
					bTitle=TRUE;
					break;
				case 'b':
					bBare=TRUE;
					break;
				case '?':
				default:
					help();
					return 0;
				}
			}
		} else {
			help();
			return 0;
		}
	}

	// Iterate over all processes
	//
	int count=0;
	BOOL bFirstModule = TRUE;
	CProcessIterator itp;
	for (DWORD pid=itp.First(); pid; pid=itp.Next()) {
		// Note: first module in CProcessModuleIterator is EXE for this process
		//
		TCHAR modname[_MAX_PATH];
		CProcessModuleIterator itm(pid);
		HMODULE hModule = itm.First(); // .EXE
		if (hModule) {
			GetModuleBaseName(itm.GetProcessHandle(),
				hModule, modname, _MAX_PATH);

			// Iterate over all top-level windows in process
			//
			BOOL bFirstWindow = TRUE;
			CMainWindowIterator itw(pid);
			for (HWND hwnd = itw.First(); hwnd; hwnd=itw.Next()) {
				if (bFirstModule) {
					if (!bBare) {
						tpf(_T("进程ID  %-13s%-8s %s%s%s\n"),_T("模块名"),_T("窗口句柄"),
							bClassName ? _T("类名") : _T(""),
							bClassName && bTitle ? _T("/") : _T(""),
							bTitle ? _T("窗口标题") : _T(""));
						tpf(_T("------  ------------ -------- ----------------\n"));
					}
					bFirstModule = FALSE;
				}
				if (bFirstWindow) {
					tpf(_T("%06x  %-13s"), pid, modname);
					bFirstWindow = FALSE;
				} else {
					tpf(_T("%21s"),_T(" "));
				}
				char classname[256],title[256];
				GetClassName(hwnd,classname,sizeof(classname));
				GetWindowText(hwnd,title,sizeof(title));
				tpf(_T("%08x %s %s\n"), hwnd,
					bClassName ? classname : _T(""),
					bTitle ? title : _T(""));
			}
			bFirstWindow || count++;
		}
	}
	if (!bBare) {
		tpf(_T("----\n"));
		tpf(_T("%d processes found.\n"),count);
	}
	return 0;
}

void help()
{
	tpf(_T("lp:        List top-level proceses.\n"));
	tpf(_T("           Copyright 2002 Paul DiLascia.\n\n"));
	tpf(_T("Format:    lp [/bct?]\n\n"));
	tpf(_T("Options:\n"));
   tpf(_T(" /b(are)   no header\n"));
   tpf(_T(" /c(lass)  show window class names\n"));
   tpf(_T(" /t(itle)  show window titles\n"));
   tpf(_T("\n"));
}
