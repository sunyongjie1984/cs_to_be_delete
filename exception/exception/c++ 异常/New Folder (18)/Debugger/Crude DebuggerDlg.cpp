// Crude DebuggerDlg.cpp : implementation file
//

#include "stdafx.h"
#include <map>
#include<Dbghelp.h>
#include <psapi.h>

#include "shlwapi.h"
#include "Crude Debugger.h"
#include "Crude DebuggerDlg.h"

#define BUFSIZE 512

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// For thread messaging
#define DEBUG_EVENT_MESSAGE		WM_APP + 0x100

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCrudeDebuggerDlg dialog
CCrudeDebuggerDlg::CCrudeDebuggerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCrudeDebuggerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CCrudeDebuggerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEBUG_EVENTS, m_cDebugEvents);
	DDX_Control(pDX, IDC_THREAD_COUNT, m_cThreadCount);
	DDX_Control(pDX, IDC_DLL_COUNT, m_cDLLCount);
	DDX_Control(pDX, IDC_TOTAL_EVENTS, m_cTotalEvents);
	DDX_Control(pDX, IDC_OUTPUTDEBUG_COUNT, m_cOutputDebug);
	DDX_Control(pDX, IDC_EXCEPTION_COUNT, m_cExceptionCount);
}

BEGIN_MESSAGE_MAP(CCrudeDebuggerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START_DEBUGGING, &CCrudeDebuggerDlg::OnBnClickedStartDebugging)

	ON_MESSAGE(DEBUG_EVENT_MESSAGE, OnDebugEventMessage)
END_MESSAGE_MAP()


// CCrudeDebuggerDlg message handlers
BOOL CCrudeDebuggerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	m_cDebugEvents.InsertColumn(0,L"Debug Event", LVCFMT_LEFT, 640);
	m_cDebugEvents.SetExtendedStyle(m_cDebugEvents.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	SetDebuggingModeUI(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCrudeDebuggerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCrudeDebuggerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCrudeDebuggerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// This function is optimized!
CString GetFileNameFromHandle(HANDLE hFile) 
{
	BOOL bSuccess = FALSE;
	TCHAR pszFilename[MAX_PATH+1];
	HANDLE hFileMap;

	CString strFilename;

	// Get the file size.
	DWORD dwFileSizeHi = 0;
	DWORD dwFileSizeLo = GetFileSize(hFile, &dwFileSizeHi); 

	if( dwFileSizeLo == 0 && dwFileSizeHi == 0 )
	{     
		return FALSE;
	}

	// Create a file mapping object.
	hFileMap = CreateFileMapping(hFile, 
		NULL, 
		PAGE_READONLY,
		0, 
		1,
		NULL);

	if (hFileMap) 
	{
		// Create a file mapping to get the file name.
		void* pMem = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);

		if (pMem) 
		{
			if (GetMappedFileName (GetCurrentProcess(), 
				pMem, 
				pszFilename,
				MAX_PATH)) 
			{

				// Translate path with device name to drive letters.
				TCHAR szTemp[BUFSIZE];
				szTemp[0] = '\0';

				if (GetLogicalDriveStrings(BUFSIZE-1, szTemp)) 
				{
					TCHAR szName[MAX_PATH];
					TCHAR szDrive[3] = TEXT(" :");
					BOOL bFound = FALSE;
					TCHAR* p = szTemp;

					do 
					{
						// Copy the drive letter to the template string
						*szDrive = *p;

						// Look up each device name
						if (QueryDosDevice(szDrive, szName, MAX_PATH))
						{
							size_t uNameLen = _tcslen(szName);

							if (uNameLen < MAX_PATH) 
							{
								bFound = _tcsnicmp(pszFilename, szName, 
									uNameLen) == 0;

								if (bFound) 
								{
									strFilename.Format(L"%s%s",szDrive, pszFilename+uNameLen);
								}
							}
						}

						// Go to the next NULL character.
						while (*p++);
					} while (!bFound && *p); // end of string
				}
			}
			bSuccess = TRUE;
			UnmapViewOfFile(pMem);
		} 

		CloseHandle(hFileMap);
	}

	return(strFilename);
}


//// ------------------------------------------------------------------------------------------------
//// --------------------- Main Debugger code starts here -------------------------------------------
//// ------------------------------------------------------------------------------------------------


void CCrudeDebuggerDlg::SetDebuggingModeUI(bool bDebug)
{
	// m_cDebugEvents.EnableWindow(bDebug);
	m_cThreadCount.EnableWindow(bDebug);
	m_cDLLCount.EnableWindow(bDebug);
	m_cTotalEvents.EnableWindow(bDebug);
	m_cExceptionCount.EnableWindow(bDebug);
	m_cOutputDebug.EnableWindow(bDebug);

	CWnd* pStartStopButton = GetDlgItem(IDC_START_DEBUGGING);

	if(!bDebug)
		pStartStopButton->SetWindowText(_T("&Start Debugging...") );
	else
		pStartStopButton->SetWindowText(_T("&Stop Debugging") );

	m_bIsDebugging = bDebug;

}


DWORD WINAPI DebuggerThread(void* pParam)
{
	CCrudeDebuggerDlg *pThis = static_cast<CCrudeDebuggerDlg*>(pParam);

	pThis->DebuggerThreadProc();

	return 0;
}


void CCrudeDebuggerDlg::OnBnClickedStartDebugging()
{
	if(m_bIsDebugging)
	{
		// Just terminate!
		TerminateThread(m_hDebugThread, 0xDEAD);

		m_cDebugEvents.InsertItem(TotalEvents, _T("*** Debugging Terminated by user *** ") );
		m_cDebugEvents.EnsureVisible(TotalEvents,false);

		SetDebuggingModeUI(false);
		return;
	}

	CFileDialog fdProcess(true, L"EXE", 0, 6, L"Executables|*.exe||");

	if( IDCANCEL==fdProcess.DoModal())
		return;


	ProcessNameToDebug = fdProcess.GetPathName();

	m_cDebugEvents.DeleteAllItems();
	TotalEvents=0;
	ThreadCount=1;	// The process considered as 1 thread.
	DLLCount=0;
	ExceptionCount=0;
	OutputDebugCount=0;

	m_hDebugThread = CreateThread(0,0, DebuggerThread, this, 0, 0);
	if(m_hDebugThread == NULL)
	{
		AfxMessageBox(_T("Failed to start debugging.") );
	}

	SetDebuggingModeUI(true); 
}

void CCrudeDebuggerDlg::DebuggerThreadProc()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );


	CreateProcess(ProcessNameToDebug, NULL, NULL, NULL, false, DEBUG_ONLY_THIS_PROCESS,
		NULL,NULL, &si, &pi);


	CString strEventMessage;
	std::map<LPVOID, CString> DllNameMap;


	DEBUG_EVENT debug_event ={0};

	bool bContinueDebugging = true;

	DWORD dwContinueStatus = DBG_CONTINUE;

	while(bContinueDebugging)
	{ 
		if (!WaitForDebugEvent(&debug_event, INFINITE))
			return;

		switch(debug_event.dwDebugEventCode)
		{
		case CREATE_PROCESS_DEBUG_EVENT:
			{
				strEventMessage = GetFileNameFromHandle(debug_event.u.CreateProcessInfo.hFile);			
			}
			break;

		case CREATE_THREAD_DEBUG_EVENT:
			strEventMessage.Format(L"Thread 0x%x (Id: %d) created at: 0x%x",  
				debug_event.u.CreateThread.hThread,
				debug_event.dwThreadId,
				debug_event.u.CreateThread.lpStartAddress); // Thread 0xc (Id: 7920) created at: 0x77b15e58

			break;
		case EXIT_THREAD_DEBUG_EVENT:

			strEventMessage.Format(L"The thread %d exited with code: %d", 	
				debug_event.dwThreadId,			
				debug_event.u.ExitThread.dwExitCode);	// The thread 2760 exited with code: 0

			break;

		case EXIT_PROCESS_DEBUG_EVENT:
			strEventMessage.Format(L"0x%x", debug_event.u.ExitProcess.dwExitCode);
			bContinueDebugging=false;
			break;

		case LOAD_DLL_DEBUG_EVENT:
			{
				strEventMessage = GetFileNameFromHandle(debug_event.u.LoadDll.hFile);

				DllNameMap.insert( 
					std::make_pair( debug_event.u.LoadDll.lpBaseOfDll, strEventMessage)	);

				strEventMessage.AppendFormat(L"%x", debug_event.u.LoadDll.lpBaseOfDll);
			}		
			break;

		case UNLOAD_DLL_DEBUG_EVENT:
			strEventMessage.Format(L"%s",  DllNameMap[debug_event.u.UnloadDll.lpBaseOfDll] );			
			break;

		case OUTPUT_DEBUG_STRING_EVENT: 
			{				
				OUTPUT_DEBUG_STRING_INFO & DebugString = debug_event.u.DebugString;
				// LPSTR p = ;

				WCHAR *msg=new WCHAR[DebugString.nDebugStringLength];			
				ZeroMemory(msg, DebugString.nDebugStringLength);

				ReadProcessMemory(pi.hProcess, DebugString.lpDebugStringData, msg, DebugString.nDebugStringLength, NULL);

				if ( DebugString.fUnicode )
					strEventMessage = msg;
				else
					strEventMessage = (LPSTR)msg;

				delete []msg;
			}

			break;

		case EXCEPTION_DEBUG_EVENT:
			{
				EXCEPTION_DEBUG_INFO& exception = debug_event.u.Exception;
				switch( exception.ExceptionRecord.ExceptionCode)
				{
				case STATUS_BREAKPOINT:
					strEventMessage= "Break point";
					break;

				default:
					if(exception.dwFirstChance == 1)
					{				
						strEventMessage.Format(L"First chance exception at %x, exception-code: 0x%08x", 
							exception.ExceptionRecord.ExceptionAddress,
							exception.ExceptionRecord.ExceptionCode);
					}
					// else
					// { Let the OS handle }


					// There are cases where OS ignores the dwContinueStatus, 
					// and executes the process in its own way.
					// For first chance exceptions, this parameter is not-important
					// but still we are saying that we have NOT handled this event.

					// Changing this to DBG_CONTINUE (for 1st chance exception also), 
					// may cause same debugging event to occur continously.
					// In short, this debugger does not handle debug exception events
					// efficiently, and let's keep it simple for a while!
					dwContinueStatus = DBG_EXCEPTION_NOT_HANDLED;			
				}

				break;
			}
		}

		SendMessage(DEBUG_EVENT_MESSAGE, (WPARAM) &strEventMessage, debug_event.dwDebugEventCode);

		ContinueDebugEvent(debug_event.dwProcessId, 
			debug_event.dwThreadId, 
			dwContinueStatus);

		// Reset
		dwContinueStatus = DBG_CONTINUE;
	}
}

// Runs in GUI thread
LRESULT CCrudeDebuggerDlg::OnDebugEventMessage(WPARAM wParam, LPARAM lParam)
{
	CString* pMessage = (CString*)wParam;

	switch(lParam)
	{
	case CREATE_PROCESS_DEBUG_EVENT:
		m_cDebugEvents.InsertItem(TotalEvents, L"Process started: " + *pMessage);
		break;

	case CREATE_THREAD_DEBUG_EVENT:
		m_cDebugEvents.InsertItem(TotalEvents, *pMessage); //L"Thread created.");
		ThreadCount++;

		break;

	case EXIT_THREAD_DEBUG_EVENT:
		m_cDebugEvents.InsertItem(TotalEvents, *pMessage); // L"Thread Exited.");
		ThreadCount--;
		break;

	case EXIT_PROCESS_DEBUG_EVENT:
		m_cDebugEvents.InsertItem(TotalEvents, L"Process exited with code: " + *pMessage);
		break;

	case LOAD_DLL_DEBUG_EVENT:
		m_cDebugEvents.InsertItem(TotalEvents, L"DLL Loaded: " +*pMessage );
		DLLCount++;
		break;

	case UNLOAD_DLL_DEBUG_EVENT:
		m_cDebugEvents.InsertItem(TotalEvents, L"DLL Unloaded: " + *pMessage) ;
		DLLCount--;
		break;

	case OUTPUT_DEBUG_STRING_EVENT: 
		m_cDebugEvents.InsertItem(TotalEvents, L"Debug Message: " + *pMessage);
		OutputDebugCount++;
		break;

	case EXCEPTION_DEBUG_EVENT:
		m_cDebugEvents.InsertItem(TotalEvents, L"DebugException: " +*pMessage);
		ExceptionCount++;
		break;
	}

	CString strCount;

	m_cDebugEvents.EnsureVisible(TotalEvents,false);
	TotalEvents++;

	strCount.Format(L"Total Debugging events: %d", TotalEvents);
	m_cTotalEvents.SetWindowText(strCount);

	strCount.Format(L"Threads: %d", ThreadCount);
	m_cThreadCount.SetWindowText(strCount);

	strCount.Format(L"DLLs: %d", DLLCount);
	m_cDLLCount.SetWindowText(strCount);

	strCount.Format(L"Exceptions: %d", ExceptionCount);
	m_cExceptionCount.SetWindowText(strCount);

	strCount.Format(L"OutputDebugs: %d", OutputDebugCount);
	m_cOutputDebug.SetWindowText(strCount);
	//m_cDLLCount.SetWindowText(strCount);

	if(lParam == EXIT_PROCESS_DEBUG_EVENT)
		SetDebuggingModeUI(false);

	return 0;
}
