// SimpleServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleServer.h"
#include "SimpleServerDlg.h"

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
// CSimpleServerDlg dialog

CSimpleServerDlg::CSimpleServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleServerDlg)
	m_nPort = 2350;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hSocket = NULL;
}

void CSimpleServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleServerDlg)
	DDX_Text(pDX, IDC_PORT, m_nPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleServerDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleServerDlg message handlers

BOOL CSimpleServerDlg::OnInitDialog()
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
	
	StartUp();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimpleServerDlg::OnPaint() 
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
HCURSOR CSimpleServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSimpleServerDlg::OnOK() 
{
	if(m_hSocket != NULL){
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
	if(m_hSocket == NULL){
		m_hSocket = socket(AF_INET, SOCK_STREAM,0);
		ASSERT(m_hSocket != NULL);
	}
	UpdateData();

	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	m_addr.sin_port = htons(m_nPort);

	int ret = 0;
	int error = 0;
	ret = bind(m_hSocket, (LPSOCKADDR)&m_addr, sizeof(m_addr));
	if(ret == SOCKET_ERROR){
		TRACE("Bind Error: %d \n", (error = WSAGetLastError()));
		return ;
	}
	ret = listen(m_hSocket, 2);
	if(ret == SOCKET_ERROR){
		TRACE("Listen Error: %d \n", (error = WSAGetLastError()));
		return ;
	}
	SOCKET s = accept(m_hSocket, NULL, NULL);
	if(s == SOCKET_ERROR){
		TRACE("Accept Error: %d \n", (error = WSAGetLastError()));
		return ;
	}

	char buff[256];
	ret = recv(s, buff, 256, 0);
	if(ret == 0 || ret == SOCKET_ERROR ){
		TRACE("Recv data error: %d\n", WSAGetLastError());
		return ;
	}
	char* name = NULL;
	char* pass = NULL;
	int len = 0;
	len = buff[0];
	name = new char[len + 1];
	for(int i = 0; i < len; i++)
		name[i] = buff[i+1];
	int len2 = buff[len + 1];
	pass = new char[len2 + 1];
	for(i = 0; i < len2; i++)
		pass[i] = buff[i + 2 + len];
	pass[len2] = '\0';
	name[len] = '\0';

	CString str;
	if(strcmp(name, "ware") != 0){
		str = _T("用户名不正确！");
		TRACE(_T("用户名不正确！\n"));
	}
	else{
		if(strcmp(pass, "11111") != 0){
			str = _T("用户密码不正确！");
			TRACE(_T("用户密码不正确！\n"));
		}
	}
	if(str.IsEmpty())
		str = _T("你的帐号还有：20.325元");
	char* buf = str.GetBuffer(0);
	ret = send(s, buf, str.GetLength(), 0);
	if(ret != str.GetLength()){
		TRACE("Send data error: %d\n", WSAGetLastError());
		return ;
	}
	delete [] name;
	delete [] pass;
}

void CSimpleServerDlg::StartUp()
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);
	if(ret != 0)
		TRACE("Initilize Error!\n");
}

void CSimpleServerDlg::CleanUp()
{
	if (WSACleanup() != 0){
		TRACE("UnInitilize Error:%d\n", WSAGetLastError());
	}
}

void CSimpleServerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CleanUp();	
}
