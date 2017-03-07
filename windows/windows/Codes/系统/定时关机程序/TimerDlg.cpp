// TimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Timer.h"
#include "TimerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

const UINT WM_TASKBARCREATED = 
    ::RegisterWindowMessage(_T("TaskbarCreated"));

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
// CTimerDlg dialog

CTimerDlg::CTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimerDlg)
	m_curTime = _T("");
	m_iShut = 30;
	m_bCalc = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimerDlg)
	DDX_Text(pDX, IDC_CURTIME, m_curTime);
	DDX_Text(pDX, IDC_EDIT1, m_iShut);
	DDV_MinMaxUInt(pDX, m_iShut, 0, 150);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialog)
	//{{AFX_MSG_MAP(CTimerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHUTDOWN, OnShutdown)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_COMMAND(ID_CLOSE, OnClose)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_NOTIFYICON, OnNotifyIcon)
	ON_WM_QUERYENDSESSION( )
	ON_REGISTERED_MESSAGE(WM_TASKBARCREATED, 
                          OnTaskBarCreated)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg message handlers

BOOL CTimerDlg::OnInitDialog()
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CDialog::OnInitDialog();

	CSpinButtonCtrl * pSpin;
	pSpin = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN);
	pSpin->SetRange(1,150);
	//m_Interval = 30;
	CDialog::OnInitDialog();
	
	// 设置定时器，每秒一次心跳
	SetTimer(1, 1000, NULL);
	
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
 
	m_nd.cbSize	= sizeof (NOTIFYICONDATA);
	m_nd.hWnd	= m_hWnd;
	m_nd.uID	= IDI_TIMER;
	m_nd.uFlags	= NIF_ICON|NIF_MESSAGE|NIF_TIP;
	m_nd.uCallbackMessage	= WM_NOTIFYICON;
	m_nd.hIcon	= m_hIcon;
	strcpy(m_nd.szTip, "我的闹钟");
	
	Shell_NotifyIcon(NIM_ADD, &m_nd);
	// TODO: Add extra initialization here
	SetTimer(1, 1000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	// 屏蔽最大化(MFC Bug)，将最小化重定向至隐藏窗口
	if (nID == SC_MAXIMIZE)
		return;
	if (nID == SC_MINIMIZE)
		ShowWindow(SW_HIDE);
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimerDlg::OnPaint() 
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
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

afx_msg void CTimerDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	// 响应在托盘图标上的单击
	if ((wParam == IDI_TIMER)&&(lParam == WM_LBUTTONDOWN))
		ShowWindow(SW_SHOWNORMAL);
	if((wParam == IDI_TIMER) &&(lParam == WM_RBUTTONDOWN))
	{
		CMenu menu;
		if (!menu.LoadMenu(IDR_MENU_TEST))
		return ;
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (!pSubMenu) 
			return ;

		// Make first menu item the default (bold font)
		::SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE);

		// Display the menu at the current mouse location. There's a "bug"
		// (Microsoft calls it a feature) in Windows 95 that requires calling
		// SetForegroundWindow. To find out more, search for Q135788 in MSDN.
		//
		CPoint mouse;
		GetCursorPos(&mouse);
		::SetForegroundWindow(m_nd.hWnd);	
		::TrackPopupMenu(pSubMenu->m_hMenu, TPM_RIGHTALIGN, mouse.x, mouse.y, 0,
			m_nd.hWnd, NULL);
	}
}

void CTimerDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(1);
	Shell_NotifyIcon(NIM_DELETE, &m_nd);
	CDialog::OnCancel();
}

void CTimerDlg::OnShutdown() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	DWORD dwVersion = GetVersion();
	if(dwVersion < 0x80000000)    //是NT系列操作系统
	{ 
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;

		OpenProcessToken(GetCurrentProcess(),
				TOKEN_ADJUST_PRIVILEGES 
				| TOKEN_QUERY,
				&hToken);
		LookupPrivilegeValue(NULL,
				SE_SHUTDOWN_NAME,
				&tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		//提升权限，以便关闭系统
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
		
		//重启
		ExitWindowsEx(EWX_SHUTDOWN, 0); 
	} 
	else    //是9X系列操作系统 
	ExitWindowsEx(EWX_SHUTDOWN,0); 
}

BOOL CTimerDlg::OnQueryEndSession()
{
	// 在用户退出Windows时自动退出应用
	CTimerDlg::OnCancel();
	return TRUE;
}

void CTimerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static CString	strTemp;
	static int		Count = 0;
	COleDateTime	dtTime;
    
	SYSTEMTIME st;
        GetLocalTime(&st);
	// 刷新时间
	strTemp.Format("现在时间 %02i:%02i:%02i ",st.wHour,st.wMinute,st.wSecond);
	GetDlgItem(IDC_CURTIME)->SetWindowText(strTemp);

	if (m_bCalc) 
	{
		m_iNow++;
		strTemp.Format("离关机还差 %i 秒", m_iSecond - m_iNow);
		GetDlgItem(IDC_SHUT_TIME)->SetWindowText(strTemp);
		if(m_iNow == m_iSecond)
		{
			//KillTimer(1);
			OnShutdown();
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CTimerDlg::OnApply() 
{
	UpdateData();
	m_bCalc = TRUE;
	m_iSecond = m_iShut*60;
	m_iNow = 0;
	// TODO: Add your control notification handler code here
	
}

void CTimerDlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CTimerDlg::OnClose() 
{
	// TODO: Add your command handler code here
	OnCancel();
}
LRESULT CTimerDlg::OnTaskBarCreated(WPARAM wp, LPARAM lp)
{
    m_nd.cbSize	= sizeof (NOTIFYICONDATA);
	m_nd.hWnd	= m_hWnd;
	m_nd.uID	= IDI_TIMER;
	m_nd.uFlags	= NIF_ICON|NIF_MESSAGE|NIF_TIP;
	m_nd.uCallbackMessage	= WM_NOTIFYICON;
	m_nd.hIcon	= m_hIcon;
	strcpy(m_nd.szTip, "我的闹钟");
	
	Shell_NotifyIcon(NIM_ADD, &m_nd);
    return 0;
}
