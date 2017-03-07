// SockProxyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SockProxy.h"
#include "SockProxyDlg.h"

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
// CSockProxyDlg dialog

CSockProxyDlg::CSockProxyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSockProxyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSockProxyDlg)
	m_strPass = _T("231whoami");
	m_strServer = _T("10.10.2.51");
	m_nPort = 1080;
	m_strUser = _T("chenwei");
	m_strDest = _T("10.12.11.74");
	m_nPort2 = 23;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSockProxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSockProxyDlg)
	DDX_Text(pDX, IDC_PASS, m_strPass);
	DDX_Text(pDX, IDC_SERVER, m_strServer);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Text(pDX, IDC_USER, m_strUser);
	DDX_Text(pDX, IDC_DEST, m_strDest);
	DDX_Text(pDX, IDC_PORT2, m_nPort2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSockProxyDlg, CDialog)
	//{{AFX_MSG_MAP(CSockProxyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockProxyDlg message handlers

BOOL CSockProxyDlg::OnInitDialog()
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

void CSockProxyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSockProxyDlg::OnPaint() 
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
HCURSOR CSockProxyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSockProxyDlg::OnTest() 
{
	if(m_socket.m_hSocket)
		m_socket.Close();
	m_socket.Create();
	UpdateData(TRUE);
	if(m_socket.ProxyConnect(m_strDest, m_nPort2, 
			m_strServer, m_nPort, m_strUser, m_strPass, CMD_CONNECT))
		TRACE("Has successed establishing the connect to the remote!\n");
	
	char buf[1024];
	memset(buf, 0, 1024);

	int n = m_socket.Receive(buf, 1024);
	AfxMessageBox(buf);
	m_socket.Close();
	if(m_socket1.m_hSocket != NULL)
		m_socket1.Close();
	m_socket1.Create();
//	if(m_socket1.ProxyConnect(m_strDest, 1230, 
//			m_strServer, m_nPort, m_strUser, m_strPass, CMD_UDP))
//		TRACE("Has successed establishing the connect to the remote!\n");
//	m_socket1.ProxyAccept(udp);
	sprintf(buf, "USER %s\r\n","chenwei");
//	udp.UDPSend(buf, strlen(buf));
	CSocket t ;
	t.Create();
	t.SendTo(buf, strlen(buf), 1230, m_strDest);
//	n = m_socket.Send(buf, strlen(buf));
}

void CSockProxyDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(m_socket.m_hSocket != NULL)
		m_socket.Close();
}
