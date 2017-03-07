// EurekaDlg.cpp : implementation file
//

// ***************************************************************************
// Bug Fix and Enhancement History
// ***************************************************************************
// Version 1.1 bugs/fixes and enhancements
// ***************************************************************************
//		1. Although the checkbox for Always On Top was checked when
//			when the app started, the style was not set until
//			the end-user checked it off and then on again. 
//		2. Hitting escape while searching for a password edit caused the 
//			dialog to close. Now I catch that event and don't close the dlg if
//			the end-user is in the middle of a search. Instead, I simply
//			stop the search.
//		3. Thanks to Christopher Duncan, who provided a much better 
//			magnifying glass icon and cursor.
// ***************************************************************************
// Future enhancement ideas
//		1.	Doesn't work with MS Inet email
//		2.	Doesn't work with MS NT User Admin
// ***************************************************************************

#include "stdafx.h"
#include "Eureka.h"
#include "EurekaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CEurekaDlg dialog

CEurekaDlg::CEurekaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEurekaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEurekaDlg)
	m_strXYPos = _T("");
	m_strHwnd = _T("");
	m_strWndClass = _T("");
	m_strIsPassword = _T("");
	m_strPassword = _T("");
	m_bAlwaysOnTop = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bIsCapturing = FALSE;
}

void CEurekaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEurekaDlg)
	DDX_Control(pDX, IDC_STC_MAG_GLASS, m_stcMagnifyingGlass);
	DDX_Text(pDX, IDC_EDT_XYPOS, m_strXYPos);
	DDX_Text(pDX, IDC_EDT_HWND, m_strHwnd);
	DDX_Text(pDX, IDC_EDT_WND_CLASS, m_strWndClass);
	DDX_Text(pDX, IDC_EDT_IS_PASSWORD, m_strIsPassword);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_strPassword);
	DDX_Check(pDX, IDC_BTN_ALWAYS_ON_TOP, m_bAlwaysOnTop);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEurekaDlg, CDialog)
	//{{AFX_MSG_MAP(CEurekaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_ALWAYS_ON_TOP, OnBtnAlwaysOnTop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEurekaDlg message handlers

BOOL CEurekaDlg::OnInitDialog()
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
	CWinApp* pApp = AfxGetApp();
	ASSERT(pApp);
	if (pApp)
	{
		VERIFY(m_hMagGlassCursor = pApp->LoadCursor(IDC_MAG_GLASS));

		VERIFY(m_hMagGlassIcon = AfxGetApp()->LoadIcon(IDI_MAG_GLASS));
		VERIFY(m_hMagGlassBlank = AfxGetApp()->LoadIcon(IDI_MAG_GLASS_BLANK));
	}
	
	OnBtnAlwaysOnTop();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEurekaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEurekaDlg::OnPaint() 
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
HCURSOR CEurekaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEurekaDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd* pWnd = ChildWindowFromPoint(point);
	if (pWnd && pWnd->GetSafeHwnd() == m_stcMagnifyingGlass.GetSafeHwnd())
	{
		SetCapture();
		SetCursor(m_hMagGlassCursor);
		m_stcMagnifyingGlass.SetIcon(m_hMagGlassBlank);

		m_bIsCapturing = TRUE;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CEurekaDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bIsCapturing)
	{
		StopCapture();
	}
}

void CEurekaDlg::StopCapture()
{
	if (m_bIsCapturing)
	{
		ReleaseCapture();
		m_bIsCapturing = FALSE;

		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		m_stcMagnifyingGlass.SetIcon(m_hMagGlassIcon);
	}
}

void CEurekaDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bIsCapturing)
	{
		ClientToScreen(&point);

		m_strXYPos.Format("X=%ld, Y=%ld", point.x, point.y);
		m_strHwnd = _T("");
		m_strWndClass = _T("");
		m_strIsPassword = _T("");
		m_strPassword = _T("");

		CWnd* pWnd = CWnd::WindowFromPoint(point);
		if (pWnd)
		{
			HWND hwndCurr = pWnd->GetSafeHwnd();

			// Make sure that the window doesn't 'belong' to us
			if ((::GetWindowThreadProcessId (GetSafeHwnd(), NULL)) 
			!= (::GetWindowThreadProcessId (hwndCurr, NULL))) 
			{
				m_strHwnd.Format("%ld", hwndCurr);
				m_strIsPassword = gc_PasswordNo;

				// Get the class name
				char lpClassName[255];
				if (::GetClassName(hwndCurr, lpClassName, 255))
				{
					m_strWndClass = lpClassName;

					// Is this an Edit control
					if (0 == m_strWndClass.CompareNoCase("EDIT"))
					{
						// Get the window's style
						LONG lStyle = ::GetWindowLong(hwndCurr, GWL_STYLE);
						if (lStyle & ES_PASSWORD)
						{
							m_strIsPassword = gc_PasswordYes;

							char szText[255];
							::SendMessage(hwndCurr, WM_GETTEXT, 255, (LPARAM)szText);
							m_strPassword = szText;
						}
					}
				}
			}
		}

		UpdateData(FALSE);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CEurekaDlg::OnBtnAlwaysOnTop() 
{
	UpdateData();

	if (m_bAlwaysOnTop)
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | WS_EX_TOPMOST);
	}
	else
	{
		::SetWindowPos(GetSafeHwnd(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

BOOL CEurekaDlg::PreTranslateMessage(MSG* pMsg) 
{
	BOOL bHandledMsg = FALSE;

	switch (pMsg->message)
	{                      
		case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
				// hitting escape while searching for password edits
				// should only stop the search for password edits and 
				// not kill app 
				case VK_ESCAPE:
					if (m_bIsCapturing)
					{
						StopCapture();
						bHandledMsg = TRUE;
					}
				break;
				
				default: break;
			} // switch (pMsg->wParam)
		}
		break;
		
		default: break;			
	} // switch (pMsg->message)                  

	return (bHandledMsg ? TRUE : CDialog::PreTranslateMessage(pMsg));
}
