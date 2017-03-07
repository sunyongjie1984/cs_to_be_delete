// ThreadTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadTest.h"
#include "ThreadTestDlg.h"
#include "NewThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE g_hEvent = NULL;
bool g_bSignal = false;
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
// CThreadTestDlg dialog

CThreadTestDlg::CThreadTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThreadTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pThread = NULL;
}

void CThreadTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThreadTestDlg)
	DDX_Control(pDX, IDC_BUTTON7, m_btnB);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CThreadTestDlg, CDialog)
	//{{AFX_MSG_MAP(CThreadTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnTest1)
	ON_BN_CLICKED(IDC_BUTTON2, OnTest2)
	ON_BN_CLICKED(IDC_BUTTON3, OnTest3)
	ON_BN_CLICKED(IDC_BUTTON4, OnTest4)
	ON_BN_CLICKED(IDC_BUTTON7, OnButtonB)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonA1)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonA2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadTestDlg message handlers

BOOL CThreadTestDlg::OnInitDialog()
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
    m_pThread = AfxBeginThread( RUNTIME_CLASS(NewThread));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreadTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThreadTestDlg::OnPaint() 
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
HCURSOR CThreadTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CThreadTestDlg::OnTest1() 
{
	// TODO: Add your control notification handler code here
    g_bSignal = false;
	DoSomething();
    if ( g_bSignal )
    {
        AfxMessageBox(_T("Finish Test1!"));
    }
}

void CThreadTestDlg::DoSomething()
{
    for ( int i = 0; i < 10000; ++i )
    {
        for ( int j = 0; j < 100000; ++j )
        {
        }
    }
    g_bSignal = true;
}

void CThreadTestDlg::OnTest2() 
{
	// TODO: Add your control notification handler code here
    g_bSignal = false;
	m_pThread->PostThreadMessage( THREAD_MESSAGE1, NULL, (LPARAM)this );
    if ( g_bSignal )
    {
        AfxMessageBox(_T("Finish Test2!"));
    }
}

void CThreadTestDlg::OnTest3() 
{
	// TODO: Add your control notification handler code here
    g_bSignal = false;

    if ( NULL != g_hEvent )
    {
        CloseHandle( g_hEvent );
        g_hEvent = NULL;
    }
    g_hEvent = ::CreateEvent( NULL, FALSE, FALSE, NULL );

	m_pThread->PostThreadMessage( THREAD_MESSAGE2, NULL, (LPARAM)this );

    if ( WAIT_OBJECT_0 != WaitForSingleObject( g_hEvent, INFINITE ))
    {
        return;
    }

    if ( g_bSignal )
    {
        AfxMessageBox(_T("Finish Test3!"));
    }
}

void CThreadTestDlg::OnTest4() 
{
	// TODO: Add your control notification handler code here
    g_bSignal = false;

    if ( NULL != g_hEvent )
    {
        CloseHandle( g_hEvent );
        g_hEvent = NULL;
    }
    g_hEvent = ::CreateEvent( NULL, FALSE, FALSE, NULL );

	m_pThread->PostThreadMessage( THREAD_MESSAGE2, NULL, (LPARAM)this );

    while ( WAIT_OBJECT_0 != MsgWaitForMultipleObjectsEx( 1, &g_hEvent, INFINITE,
        QS_ALLEVENTS, 0 ))
    {
        MSG msg;
        if ( ::PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE ))
        {
            ::DispatchMessage( &msg );    
        }
    }
    if ( g_bSignal )
    {
        AfxMessageBox(_T("Finish Test4!"));
    }
}

void CThreadTestDlg::OnButtonB() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T( "Button B is clicked" ));
}

void CThreadTestDlg::OnButtonA1() 
{
	// TODO: Add your control notification handler code here
    m_btnB.EnableWindow( FALSE );
    DoSomething();
    m_btnB.EnableWindow( TRUE);
	
}

void CThreadTestDlg::OnButtonA2() 
{
	// TODO: Add your control notification handler code here
	m_pThread->PostThreadMessage( THREAD_MESSAGE3, NULL, (LPARAM)this );
	
}
