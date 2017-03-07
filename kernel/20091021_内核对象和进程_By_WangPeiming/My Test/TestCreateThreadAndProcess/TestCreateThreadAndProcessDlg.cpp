// TestCreateThreadAndProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestCreateThreadAndProcess.h"
#include "TestCreateThreadAndProcessDlg.h"
#include "TraceOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE g_hMutex;
HANDLE g_hProcess;

DWORD WINAPI NewThread ( LPVOID lParam )
{
    TRACEOUT( _T("New thread is running!"));
    return 1;
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCreateThreadAndProcessDlg dialog

CTestCreateThreadAndProcessDlg::CTestCreateThreadAndProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCreateThreadAndProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestCreateThreadAndProcessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCreateThreadAndProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestCreateThreadAndProcessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestCreateThreadAndProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CTestCreateThreadAndProcessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnCreateNewThread)
	ON_BN_CLICKED(IDC_BUTTON2, OnCreateNewProcess)
	ON_BN_CLICKED(IDC_BUTTON3, OnTryToLockTheMutex)
	ON_BN_CLICKED(IDC_BUTTON4, OnReleaseMutex)
	ON_BN_CLICKED(IDC_BUTTON5, OnTestCPUTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCreateThreadAndProcessDlg message handlers

BOOL CTestCreateThreadAndProcessDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestCreateThreadAndProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestCreateThreadAndProcessDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestCreateThreadAndProcessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestCreateThreadAndProcessDlg::OnCreateNewThread() 
{
    DWORD dThreadID;
	HANDLE hThreadHandle = 
        CreateThread( NULL, 0, NewThread, NULL, 0, &dThreadID );

    WaitForSingleObject( hThreadHandle, INFINITE );

    CloseHandle( hThreadHandle );
}

void CTestCreateThreadAndProcessDlg::OnCreateNewProcess() 
{
    DWORD dTempID = GetCurrentThreadId();
    SECURITY_ATTRIBUTES saMutex;
    saMutex.nLength = sizeof( saMutex );
    saMutex.bInheritHandle = TRUE;
            //标志这该对象句柄是否允许被继承
    saMutex.lpSecurityDescriptor = NULL;

	g_hMutex = CreateMutex( &saMutex, FALSE, _T( "TestMutex" )); 
            // Mutex 一种锁，可以保护部分资源只能被一个线程所访问。

    TCHAR szCommandLine[ 10 ];
    _itot( int(g_hMutex), szCommandLine, 10 );
    STARTUPINFO si;
    ::memset( &si, 0, sizeof( si ));
    si.cb = sizeof( si );
    PROCESS_INFORMATION pi;
    CreateProcess( 
        _T( "NewProcess.exe" ), 
        szCommandLine, NULL, NULL, 
        TRUE, 
            // 标志着该子进程是否可以继承父进程的句柄
        0, NULL, NULL, &si, &pi );

    g_hProcess = pi.hProcess;

//     CreateProcess( 
//         NULL, 
//         _T( "notepad" ), NULL, NULL, 
//         TRUE, 
//         0, NULL, NULL, &si, &pi );

//     CreateProcess( 
//         _T( "notepad.exe" ), 
//         NULL, NULL, NULL, 
//         TRUE, 
//         0, NULL, NULL, &si, &pi );

//     CreateProcess( 
//         _T( "C:\\WINDOWS\\system32\\notepad.exe" ), 
//         NULL, NULL, NULL, 
//         TRUE, 
//         0, NULL, NULL, &si, &pi );

//     CreateProcess( 
//         _T( "C:\\WINDOWS\\system32\\notepad.exe" ), 
//         _T( "WORDPAD ReadMe.txt" ), NULL, NULL, 
//         TRUE, 
//         0, NULL, NULL, &si, &pi );
}

void CTestCreateThreadAndProcessDlg::OnTryToLockTheMutex() 
{
    DWORD dTempID = GetCurrentThreadId();
    TRACEOUT( _T( "Parent process Try to lock the Mutex!" ));
	WaitForSingleObject( g_hMutex, INFINITE );
        // 锁住这把锁
    TRACEOUT( _T( "Parent process Successfully lock the Mutex!" ));
}

void CTestCreateThreadAndProcessDlg::OnReleaseMutex() 
{
	ReleaseMutex( g_hMutex );
        // 释放这把锁
}

void CTestCreateThreadAndProcessDlg::OnTestCPUTime() 
{
    FILETIME CreationTime;  //千万分之一秒
    CreationTime.dwHighDateTime = 0;
    CreationTime.dwLowDateTime = 0;
    FILETIME ExitTime;
    ExitTime.dwHighDateTime = 0;
    ExitTime.dwLowDateTime = 0;
    FILETIME KernelTime;
    KernelTime.dwHighDateTime = 0;
    KernelTime.dwLowDateTime = 0;
    FILETIME UserTime;
    UserTime.dwHighDateTime = 0;
    UserTime.dwLowDateTime = 0;

    int a = 0;

    GetProcessTimes(
        g_hProcess,           // handle to process
        &CreationTime, // process creation time
        &ExitTime,     // process exit time
        &KernelTime,   // process kernel-mode time
        &UserTime      // process user-mode time
    );
}
