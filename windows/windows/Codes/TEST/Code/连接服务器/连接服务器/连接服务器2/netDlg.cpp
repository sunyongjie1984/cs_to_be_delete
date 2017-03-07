// netDlg.cpp : implementation file
//

#include "stdafx.h"
#include "net.h"
#include "netDlg.h"

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
// CNetDlg dialog

CNetDlg::CNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetDlg)
	m_servername = _T("");
	m_password = _T("");
	m_user_name = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
/*
	lpNetResource1->dwType=RESOURCETYPE_DISK;
	lpNetResource1->lpLocalName=NULL;*/

	
}

void CNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetDlg)
	DDX_Text(pDX, IDC_EDIT1, m_servername);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT3, m_user_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetDlg, CDialog)
	//{{AFX_MSG_MAP(CNetDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetDlg message handlers

BOOL CNetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
/*
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
*/

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);


		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CNetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNetDlg::OnButton1() 
{
	UpdateData();

	m_servername = "\\\\"+m_servername;
	NETRESOURCE lpNetResource1;
	DWORD dwFlags1 = CONNECT_UPDATE_PROFILE;
	DWORD hr = 0;

	
	lpNetResource1.dwType =	RESOURCETYPE_ANY;
	lpNetResource1.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
	lpNetResource1.dwScope = RESOURCE_GLOBALNET;
	lpNetResource1.dwUsage = RESOURCEUSAGE_CONNECTABLE;
	lpNetResource1.lpComment = NULL;
	lpNetResource1.lpLocalName = NULL;
	lpNetResource1.lpProvider = NULL;
	lpNetResource1.lpRemoteName = m_servername.GetBuffer(0);

	hr=WNetAddConnection2( &lpNetResource1,  // connection details
		                   m_password,           //password
		                   m_user_name,           // user name
		                   dwFlags1 );                 // connection options
		   
	if( NO_ERROR == hr )
	{

		dlg.DoModal();
	}
	else
	{
        AfxMessageBox( "¡¨Ω” ß∞‹£°" );
	}

}
