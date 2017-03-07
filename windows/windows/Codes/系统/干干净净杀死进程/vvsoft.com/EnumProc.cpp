////////////////////////////////////////////////////////////////
// MSDN Magazine -- August 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 on Windows XP.
//
#include "stdafx.h"
#include "EnumProc.h"
//#if(WINVER >= 0x0500)
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
//#endif /* WINVER >= 0x0500 */

////////////////////////////////////////////////////////////////
// CProcessIterator - Iterates all processes
//
CProcessIterator::CProcessIterator()
{
	m_pids = NULL;
}

CProcessIterator::~CProcessIterator()
{
	delete [] m_pids;
}

//////////////////
// Get first process: Call EnumProcesses to init array. Return first one.
//
DWORD CProcessIterator::First()
{
	m_current = (DWORD)-1;
	m_count = 0;
	DWORD nalloc = 1024;
	do {
		delete [] m_pids;
		m_pids = new DWORD [nalloc];
		if (EnumProcesses(m_pids, nalloc*sizeof(DWORD), &m_count)) {
			m_count /= sizeof(DWORD);
			m_current = 1;						 // skip IDLE process
		}
	} while (nalloc <= m_count);

	return Next();
}

////////////////////////////////////////////////////////////////
// CProcessModuleIterator - Iterates all modules in a process
//
CProcessModuleIterator::CProcessModuleIterator(DWORD pid)
{
	m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE, pid);
}

CProcessModuleIterator::~CProcessModuleIterator()
{
	CloseHandle(m_hProcess);
	delete [] m_hModules;
}

//////////////////
// Get first module in process. Call EnumProcesseModules to
// initialize entire array, then return first module.
//
HMODULE CProcessModuleIterator::First()
{
	m_count = 0;
	m_current = (DWORD)-1; 
	m_hModules = NULL;
	if (m_hProcess) {
		DWORD nalloc = 1024;
		do {
			delete [] m_hModules;
			m_hModules = new HMODULE [nalloc];
			if (EnumProcessModules(m_hProcess, m_hModules,
				nalloc*sizeof(DWORD), &m_count)) {
				m_count /= sizeof(HMODULE);
				m_current = 0;
			}
		} while (nalloc <= m_count);
	}
	return Next();
}

////////////////////////////////////////////////////////////////
// CWindowIterator - Iterates all top-level windows (::EnumWindows)
//
CWindowIterator::CWindowIterator(DWORD nAlloc)
	: m_current(0), m_count(0)
{
	assert(nAlloc>0);
	m_hwnds = new HWND [nAlloc];
	m_nAlloc = nAlloc;
}

CWindowIterator::~CWindowIterator()
{
	delete [] m_hwnds;
}

// callback passes to virtual fn
BOOL CALLBACK CWindowIterator::EnumProc(HWND hwnd, LPARAM lp)
{
	return ((CWindowIterator*)lp)->OnEnumProc(hwnd);
}

//////////////////
// Virtual enumerator proc: add HWND to array if OnWindows is TRUE.
// You can override OnWindow to filter windows however you like.
//
BOOL CWindowIterator::OnEnumProc(HWND hwnd)
{
	if (OnWindow(hwnd)) {
		if (m_count < m_nAlloc)
			m_hwnds[m_count++] = hwnd;
	}
	return TRUE; // keep looking
}

////////////////////////////////////////////////////////////////
// CMainWindowIterator - Iterates the main windows of a process.
// Overrides CWindowIterator::OnWindow to filter.
//
CMainWindowIterator::CMainWindowIterator(DWORD pid, BOOL bVis,
	DWORD nAlloc) : CWindowIterator(nAlloc), m_pid(pid), m_bVisible(bVis)
{
}

CMainWindowIterator::~CMainWindowIterator()
{
}

//////////////////
// OnWindow:: Is window's process ID the one i'm looking for?
// Set m_bVisible=FALSE to find invisible windows too.
//
BOOL CMainWindowIterator::OnWindow(HWND hwnd)
{
	if (!m_bVisible || (GetWindowLong(hwnd,GWL_STYLE) & WS_VISIBLE)) {
		DWORD pidwin;
		GetWindowThreadProcessId(hwnd, &pidwin);
		if (pidwin==m_pid)
			return TRUE;
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////
// CFindKillProcess - to find/kill a process by module name.
//
CFindKillProcess::CFindKillProcess()
{
}

CFindKillProcess::~CFindKillProcess()
{
}

//////////////////
// Search for process whose module name matches parameter.
// Finds "foo" or "foo.exe"
//
DWORD CFindKillProcess::FindProcess(LPCTSTR modname, BOOL bAddExe)
{
	CProcessIterator itp;
	for (DWORD pid=itp.First(); pid; pid=itp.Next()) {
		TCHAR name[_MAX_PATH];
		CProcessModuleIterator itm(pid);
		HMODULE hModule = itm.First(); // .EXE
		if (hModule) {
			GetModuleBaseName(itm.GetProcessHandle(),
				hModule, name, _MAX_PATH);

			string sModName = modname;
			if (strcmpi(sModName.c_str(),name)==0)
				return pid;
			sModName += ".exe";
			if (bAddExe && strcmpi(sModName.c_str(),name)==0)
				return pid;
		}
	}
	return 0;
}

//////////////////
// Kill a process cleanly: Close main windows and wait.
// bZap=TRUE to force kill.
//
BOOL CFindKillProcess::KillProcess(DWORD pid, BOOL bZap)
{
	CMainWindowIterator itw(pid);
	for (HWND hwnd=itw.First(); hwnd; hwnd=itw.Next()) {
		DWORD bOKToKill = FALSE;
		SendMessageTimeout(hwnd, WM_QUERYENDSESSION, 0, 0,
			SMTO_ABORTIFHUNG|SMTO_NOTIMEOUTIFNOTHUNG, 100, &bOKToKill);
		if (!bOKToKill)
			return FALSE;  // window doesn't want to die: abort
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}

	// I've closed the main windows; now wait for process to die. 
	BOOL bKilled = TRUE;
	HANDLE hp=OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE,FALSE,pid);
	if (hp) {
		if (WaitForSingleObject(hp, 5000) != WAIT_OBJECT_0) {
			if (bZap) { // didn't die: force kill it if zap requested
				TerminateProcess(hp,0);
			} else {
				bKilled = FALSE;
			}
		}
		CloseHandle(hp);
	}
	return bKilled;
}

