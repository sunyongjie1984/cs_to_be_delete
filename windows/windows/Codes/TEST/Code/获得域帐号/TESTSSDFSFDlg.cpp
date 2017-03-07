// TESTSSDFSFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TESTSSDFSF.h"
#include "TESTSSDFSFDlg.h"

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
// CTESTSSDFSFDlg dialog

CTESTSSDFSFDlg::CTESTSSDFSFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTESTSSDFSFDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTESTSSDFSFDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTESTSSDFSFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTESTSSDFSFDlg)
	DDX_Control(pDX, IDC_LIST1, m_listuserinfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTESTSSDFSFDlg, CDialog)
	//{{AFX_MSG_MAP(CTESTSSDFSFDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTESTSSDFSFDlg message handlers

BOOL CTESTSSDFSFDlg::OnInitDialog()
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
	
	m_listuserinfo.InsertColumn(0,"用户名称",LVCFMT_LEFT,100);	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTESTSSDFSFDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTESTSSDFSFDlg::OnPaint() 
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
HCURSOR CTESTSSDFSFDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTESTSSDFSFDlg::OnButton1() 
{
	DWORD i;
	DWORD dwResumeHandle=0;
	DWORD dwTotalCount=0;
	
	CString csFmtname;
	
	///////////////////////////////////////////////////
	   PGROUP_USERS_INFO_0 pBuf = NULL;
	   PGROUP_USERS_INFO_0 pTmpBuf = NULL;
	   DWORD dwLevel = 0;
	   DWORD dwPrefMaxLen = -1;
	   DWORD dwEntriesRead = 0;
	   DWORD dwTotalEntries = 0;
	   NET_API_STATUS nStatus;
	   
	   WCHAR pszServerName[MAX_PATH] = {0};   
       WCHAR pszgroupname[MAX_PATH]={0};
	   
	   char servername[MAX_PATH];
	   char groupname[MAX_PATH]={"Domain Users"};
	   CString m_serverName("\\\\192.168.0.206");
	   strcpy(servername, m_serverName.GetBuffer(0));
	   DWORD rc = MultiByteToWideChar(CP_ACP, 
		   0, 
		   servername,
		   -1,	
		   pszServerName,
		   sizeof(pszServerName));
	   DWORD Fc = MultiByteToWideChar(CP_ACP, 
		   0, 
		   groupname,
		   -1,	
		   pszgroupname,
		   sizeof(pszgroupname));
	   
	   
	   if(rc == 0)
	   {
		   int ret = GetLastError();
		   CString csError;
		   csError.Format("MultiByteToWideChar error %d",ret);
		   AfxMessageBox(csError);
		   
	   }
	   do
	   {  
		   nStatus =NetGroupGetUsers(NULL,//pszServerName,//指定远程服务的域服务器或网络输入输出系统名
			   pszgroupname,//列出指定全局组名列表
			   dwLevel,              
			   (LPBYTE *)&pBuf,           
			   dwPrefMaxLen,         
			   &dwEntriesRead,      
			   &dwTotalEntries,     
			   &dwResumeHandle);
		   if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		   {
			   if ((pTmpBuf = pBuf) != NULL)
			   {			
				   for (i = 0; (i < dwEntriesRead); i++)
				   {
					   assert(pTmpBuf != NULL);
					   if (pTmpBuf == NULL)
					   {				  
						   AfxMessageBox("An access violation has occurred" );
						   break;
					   } 
					   csFmtname.Format("%S", pTmpBuf->grui0_name);
					   m_listuserinfo.InsertItem(i,csFmtname);//插入项目到列表视图
					   pTmpBuf++;
					   dwTotalCount++;
				   }
			   }
		   }	
           else
			   if (pBuf != NULL)
			   {
				   NetApiBufferFree(pBuf);
				   pBuf = NULL;
			   }
	   }
       while (nStatus == ERROR_MORE_DATA); 	
}
