// ApiCommDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ApiComm.h"
#include "ApiCommDlg.h"

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
// CApiCommDlg dialog

CApiCommDlg::CApiCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CApiCommDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CApiCommDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApiCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CApiCommDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CApiCommDlg, CDialog)
	//{{AFX_MSG_MAP(CApiCommDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApiCommDlg message handlers

BOOL CApiCommDlg::OnInitDialog()
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

	m_hCom=CreateFile("COM2", GENERIC_READ|GENERIC_WRITE, 0, NULL ,OPEN_EXISTING, 0,NULL);
	if (m_hCom==INVALID_HANDLE_VALUE) 
	{
		AfxMessageBox("fail");
	     return false;
	}
     else 
	 {
		 DCB dcb;
		 GetCommState(m_hCom,&dcb);
		 dcb.BaudRate=9600;
		 dcb.ByteSize = 8; 
		 dcb.Parity=NOPARITY;
		 dcb.StopBits=ONESTOPBIT;
		 dcb.fOutxCtsFlow = 0;
         dcb.fRtsControl = RTS_CONTROL_ENABLE ;
		 SetCommState(m_hCom,&dcb);
//		 PurgeComm(m_hCom,PURGE_TXCLEAR);/////清空缓冲区		
	 }

//	SetupComm(m_hCom,4096,4096);////不要也可以
//	SetCommMask(m_hCom, EV_RXCHAR| EV_TXEMPTY);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CApiCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CApiCommDlg::OnPaint() 
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
HCURSOR CApiCommDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CApiCommDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	DWORD length;
	CString strTemp;
	strTemp="1234";  //长度为4的字符串，所以下面一行中的长度为4
	WriteFile(m_hCom,strTemp,4,&length,NULL);
	//为重叠写创建事件对象，手工重置，初始化为无信号的
	//如果初始化时设置为重叠读写，用下面代码
	//if((m_osWrite.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL))==NULL)
	//	return FALSE;
		//WriteFile(m_hCom,"a",1,&length,&m_osWrite); 
}
