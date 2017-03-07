// fffffffDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fffffff.h"
#include "fffffffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#include "stdafx.h"

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
// CFffffffDlg dialog

CFffffffDlg::CFffffffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFffffffDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFffffffDlg)
	m_servername = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFffffffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFffffffDlg)
	DDX_Control(pDX, IDC_LIST2, m_listuserinfo);
	DDX_Text(pDX, IDC_EDIT1, m_servername);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFffffffDlg, CDialog)
	//{{AFX_MSG_MAP(CFffffffDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CFffffffDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	m_listuserinfo.InsertColumn(1,"类型",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(2,"描述01",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(3,"描述02",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(4,"描述03",LVCFMT_LEFT,100);
    m_listuserinfo.InsertColumn(5,"描述04",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(6,"描述05",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(7,"描述06",LVCFMT_LEFT,100);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFffffffDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFffffffDlg::OnPaint() 
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CFffffffDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//////////////////////////////////////////////////////////////////
void CFffffffDlg::OnButton1() 
{
   DWORD i;
   LPUSER_INFO_2 pBuf= NULL;
   LPUSER_INFO_2 pTmpBuf = NULL;
   DWORD dwLevel=0;
   DWORD dwPrefMaxLen= MAX_PREFERRED_LENGTH;
   DWORD dwEntriesRead=0;
   DWORD dwTotalEntries=0;
   DWORD dwResumeHandle=0;
   DWORD dwTotalCount=0;

   CString csFmtname;
   CString csFmtpassword;
   CString csFmthome_dir;
   CString csFmtcomment;
   CString csFmtscript_path;
   CString csFmtfull_name;
   CString csFmtusr_comment;
   CString csFmtparms;
   
   NET_API_STATUS nStatus;
   LPTSTR pszServerName;
   pszServerName = m_servername.GetBuffer(0) ;
   do 
   {
      nStatus = NetUserEnum((const unsigned short *)pszServerName,
                            2,
                            //FILTER_SERVER_TRUST_ACCOUNT, // global users
                            FILTER_NORMAL_ACCOUNT,
                            //FILTER_TEMP_DUPLICATE_ACCOUNT,
							//FILTER_WORKSTATION_TRUST_ACCOUNT,
                            (LPBYTE*)&pBuf,
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
			   csFmtname.Format("%S",pTmpBuf->usri2_name);
			   csFmtpassword.Format("%S",pTmpBuf->usri2_password);
			   csFmthome_dir.Format("%S",pTmpBuf->usri2_home_dir);
			   csFmtcomment.Format("%S",pTmpBuf->usri2_comment);
			   csFmtscript_path.Format("%S",pTmpBuf->usri2_script_path);
			   csFmtfull_name.Format("%S",pTmpBuf->usri2_full_name);
			   csFmtusr_comment.Format("%S",pTmpBuf->usri2_usr_comment);
			   csFmtparms.Format("%S",pTmpBuf->usri2_parms);
			  
			   m_listuserinfo.InsertItem(i,csFmtname);//插入项目到列表视图
			   m_listuserinfo.SetItemText(i,1,csFmtpassword);
			   m_listuserinfo.SetItemText(i,2,csFmthome_dir);
			   m_listuserinfo.SetItemText(i,3,csFmtcomment);
			   m_listuserinfo.SetItemText(i,4,csFmtscript_path);
			   m_listuserinfo.SetItemText(i,5,csFmtfull_name);
			   m_listuserinfo.SetItemText(i,6,csFmtusr_comment);
			   m_listuserinfo.SetItemText(i,7,csFmtparms);
			   
               pTmpBuf++;
               dwTotalCount++;
            }
         }
      }

      else
//	     m_value1=nStatus;

      if (pBuf != NULL)
      {
         NetApiBufferFree(pBuf);
         pBuf = NULL;
      }
   }

   while (nStatus == ERROR_MORE_DATA); // end do

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);
  
}

