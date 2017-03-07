////////////////////////////////////////////////////////////////
// MSDN Magazine -- August 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 on Windows XP.
//
// kp -- kill process
//
#include "stdafx.h"
#include "EnumProc.h"

#define tpf _tprintf	// to save typing

typedef list<string> CStringList;		 // like MFC, but with STL

// pre-declare functions
int  help();

// check for switch: / or -
inline BOOL isswitch(TCHAR c) { return c==L'/' || c==L'-'; }

int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	CStringList cmdargs;		 // command-line args (processes to kill)
	BOOL bDisplayOnly=FALSE; // don't kill, just show results
	BOOL bQuiet=FALSE;		 // suppress error messages
	BOOL bZap=FALSE;			 // force-kill process

	// Parse command line. Switches can come in any order.
	for (int i=1; i<argc; i++) {
		if (isswitch(argv[i][0])) {
			for (UINT j=1; j<strlen(argv[i]); j++) {
				switch(tolower(argv[i][j])) {
				case '?':	help();	return 0;
				case 'n':	bDisplayOnly=TRUE; break;
				case 'q':	bQuiet=TRUE;       break;
				case 'z':	bZap=TRUE;			 break;
				default:
					return help();
				}
			}
		} else {
			cmdargs.push_back(argv[i]);	 // got a non-switch arg: add to list
		}
	}
	if (cmdargs.size()<=0)
		help();

	// Now iterate args (module names), killing each one
	CStringList::iterator it;
	for (it=cmdargs.begin(); it!=cmdargs.end(); it++) {
		CFindKillProcess fkp;
		DWORD pid = fkp.FindProcess(it->c_str());
		if (pid) {
			if (bDisplayOnly) {
				tpf(_T("Kill process %d(0x%08x)\n"),pid,pid);
			} else {
				fkp.KillProcess(pid, bZap);
			}
		} else if (!bQuiet) {
			tpf(_T("Error: Can't find process '%s'.\n"),it->c_str());
		}
	}
	return 0;
}

int help()
{
	tpf(_T("kp: Kill process from command line.\n"));
	tpf(_T("    Copyright 2002 Paul DiLascia.\n\n"));
	tpf(_T("    kp [/nqz?] modname1 [modname2....]\n"));
   tpf(_T("    where modnameN is a module name; eg foo or foo.exe\n"));
   tpf(_T("\n"));
   tpf(_T("    /n(othing) don't kill, just show results\n"));
   tpf(_T("    /q(uiet)   don't show errors\n"));
   tpf(_T("    /z(ap)     force kill (ignore WM_QUERYENDSESSION)\n"));
   tpf(_T("\n"));
	return 0;
}
