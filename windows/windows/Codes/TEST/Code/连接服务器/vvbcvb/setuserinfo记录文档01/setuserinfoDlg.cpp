// setuserinfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setuserinfo.h"
#include "setuserinfoDlg.h"

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
// CSetuserinfoDlg dialog

CSetuserinfoDlg::CSetuserinfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetuserinfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetuserinfoDlg)
	m_serverName = _T("");
	m_userName = _T("");
	m_scriptpath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_serverName = "\\\\192.168.0.206";
	m_userName = "test";
}

void CSetuserinfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetuserinfoDlg)
	DDX_Text(pDX, IDC_EDIT1, m_serverName);
	DDX_Text(pDX, IDC_EDIT2, m_userName);
	DDX_Text(pDX, IDC_EDIT3, m_scriptpath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetuserinfoDlg, CDialog)
	//{{AFX_MSG_MAP(CSetuserinfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetuserinfoDlg message handlers

BOOL CSetuserinfoDlg::OnInitDialog()
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

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSetuserinfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSetuserinfoDlg::OnPaint() 
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
HCURSOR CSetuserinfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSetuserinfoDlg::OnButton1() 
{
	
	// TODO: Add your control notification handler code here

	UpdateData();

	DWORD dwLevel = 1052;////////////////////////////////
	USER_INFO_1052 dbuf;////////////////////////////
	NET_API_STATUS nStatus;

	CString errormsg02;
	
	WCHAR dservername[MAX_PATH] = {0}; 
	WCHAR dusername[MAX_PATH] = {0};
	WCHAR dusri1009_script_path[MAX_PATH]={0};

	char servername[MAX_PATH];
	char username[MAX_PATH];
	char scriptpath[MAX_PATH];

	strcpy(servername, m_serverName.GetBuffer(0));
	strcpy(username, m_userName.GetBuffer(0));
	strcpy(scriptpath,m_scriptpath.GetBuffer(0));
// 	   MessageBox(servername);
	   DWORD rc = MultiByteToWideChar(CP_ACP, 
		                              0, 
		                              servername,
		                              -1,	
		                              dservername,
		                              sizeof(dservername));
	   DWORD hc = MultiByteToWideChar(CP_ACP, 
		                              0, 
		                              username,
		                              -1,	
		                              dusername,
		                              sizeof(dusername));
	   DWORD kc = MultiByteToWideChar(CP_ACP, //////////////////////
		                              0, /////////////////////////////////
		                              scriptpath,///////////////
		                              -1,	////////////////////////
		                              dusri1009_script_path,///////////////
		                              sizeof(dusri1009_script_path));//////////
	   dbuf.usri1052_profile=dusri1009_script_path;


	nStatus = NetUserSetInfo(/*L"\\\\192.168.0.206"*/dservername,
		                     L"administrator",
		                     dwLevel,
		                     (LPBYTE)&dbuf,
		                     NULL);
	if (nStatus == NERR_Success)
		AfxMessageBox("User account  ");
	else
	{	
	    errormsg02.Format("%d",nStatus);
		CString errormsg="A system error has occurred:  "+errormsg02;
		AfxMessageBox(errormsg);
	}
	
}
