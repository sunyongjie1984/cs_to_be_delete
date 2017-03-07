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
	
	m_listuserinfo.InsertColumn(0,"”√ªß√˚≥∆",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(1,"µ«¬ºΩ≈±æ",LVCFMT_LEFT,100);
	
	m_listuserinfo.InsertColumn(2,"√Ë ˆ01",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(3,"√Ë ˆ02",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(4,"√‹¬Î",LVCFMT_LEFT,100);
    m_listuserinfo.InsertColumn(5,"√Ë ˆ04",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(6,"√Ë ˆ05",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(7,"√Ë ˆ06",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(8,"√Ë ˆ07",LVCFMT_LEFT,100);

	m_listuserinfo.InsertColumn(9,"”√ªß√˚≥∆",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(10,"µ«¬ºΩ≈±æ",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(11,"”√ªß√˚≥∆",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(12,"µ«¬ºΩ≈±æ",LVCFMT_LEFT,100);	
	m_listuserinfo.InsertColumn(13,"√Ë ˆ01",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(14,"√Ë ˆ02",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(15,"√‹¬Î",LVCFMT_LEFT,100);
    m_listuserinfo.InsertColumn(16,"√Ë ˆ04",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(17,"√Ë ˆ05",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(18,"√Ë ˆ06",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(19,"√Ë ˆ07",LVCFMT_LEFT,100);	
	m_listuserinfo.InsertColumn(20,"√Ë ˆ01",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(21,"√Ë ˆ02",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(22,"√‹¬Î",LVCFMT_LEFT,100);
    m_listuserinfo.InsertColumn(23,"√Ë ˆ04",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(24,"√Ë ˆ05",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(25,"√Ë ˆ06",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(26,"√Ë ˆ07",LVCFMT_LEFT,100);
	
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
   CString csFmtlogon_server;
   CString csFmtusri2_password_age;  //////////////
   CString csFmtusri2_priv;
   CString csFmtusri2_flags; 
   CString csFmtusri2_auth_flags;/////////////// 
   CString csFmtusri2_last_logon;  
   CString csFmtusri2_last_logoff;  
   CString csFmtusri2_acct_expires;  
   CString csFmtusri2_max_storage;  
   CString csFmtusri2_units_per_week;  
   CString csFmtusri2_logon_hours;  
   CString csFmtusri2_bad_pw_count;  
   CString csFmtusri2_num_logons;    
   CString csFmtusri2_country_code;  
   CString csFmtusri2_code_page;
   CString csFmtusri2_workstations;
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
			   csFmtusri2_password_age.Format("%d",pTmpBuf->usri2_password_age);  
			   csFmtusri2_priv.Format("%d",pTmpBuf->usri2_priv);
			   csFmtusri2_flags.Format("%d",pTmpBuf->usri2_flags); 
			   csFmtusri2_auth_flags.Format("%d",pTmpBuf->usri2_auth_flags); 
			   csFmtusri2_last_logon.Format("%d",pTmpBuf->usri2_last_logon);  
			   csFmtusri2_last_logoff.Format("%d",pTmpBuf->usri2_last_logoff);  
			   csFmtusri2_acct_expires.Format("%d",pTmpBuf->usri2_acct_expires);  
			   csFmtusri2_max_storage.Format("%d",pTmpBuf->usri2_max_storage);  
			   csFmtusri2_units_per_week.Format("%d",pTmpBuf->usri2_units_per_week);  
			   csFmtusri2_logon_hours.Format("%d",pTmpBuf->usri2_logon_hours);  
			   csFmtusri2_bad_pw_count.Format("%d",pTmpBuf->usri2_bad_pw_count);  
			   csFmtusri2_num_logons.Format("%d",pTmpBuf->usri2_num_logons);    
			   csFmtusri2_country_code.Format("%d",pTmpBuf->usri2_country_code);  
			   csFmtusri2_code_page.Format("%d",pTmpBuf->usri2_code_page);
			   
			   csFmtname = pTmpBuf->usri2_name;
			   csFmtscript_path.Format("%S",pTmpBuf->usri2_script_path);
			   csFmthome_dir.Format("%S",pTmpBuf->usri2_home_dir);
			   csFmtcomment.Format("%S",pTmpBuf->usri2_comment);
			
			   csFmtpassword.Format("%S",pTmpBuf->usri2_password);
			   csFmtfull_name.Format("%S",pTmpBuf->usri2_full_name);
			   csFmtusr_comment.Format("%S",pTmpBuf->usri2_usr_comment);
			   csFmtparms.Format("%S",pTmpBuf->usri2_parms);
			   csFmtlogon_server.Format("%S",pTmpBuf->usri2_logon_server);
			   csFmtusri2_workstations.Format("%S",pTmpBuf->usri2_workstations);

			   m_listuserinfo.InsertItem(i,csFmtname);//≤Â»ÎœÓƒøµΩ¡–±Ì ”Õº
			   
               m_listuserinfo.SetItemText(i,1,csFmtscript_path);
			   m_listuserinfo.SetItemText(i,2,csFmthome_dir);
			   m_listuserinfo.SetItemText(i,3,csFmtcomment);
			   m_listuserinfo.SetItemText(i,4,csFmtpassword);
			   //
			   m_listuserinfo.SetItemText(i,5,csFmtfull_name);
			   m_listuserinfo.SetItemText(i,6,csFmtusr_comment);
			   m_listuserinfo.SetItemText(i,7,csFmtparms);
			   m_listuserinfo.SetItemText(i,8,csFmtlogon_server);
			   			   
			   m_listuserinfo.SetItemText(i,9,csFmtusri2_password_age);  //////////////
			   m_listuserinfo.SetItemText(i,10,csFmtusri2_priv);
			   m_listuserinfo.SetItemText(i,11,csFmtusri2_flags); 
			   m_listuserinfo.SetItemText(i,12,csFmtusri2_auth_flags);/////////////// 
			   m_listuserinfo.SetItemText(i,13,csFmtusri2_last_logon);  
			   m_listuserinfo.SetItemText(i,14,csFmtusri2_last_logoff);  
			   m_listuserinfo.SetItemText(i,15,csFmtusri2_acct_expires);  
			   m_listuserinfo.SetItemText(i,16,csFmtusri2_max_storage);  
			   m_listuserinfo.SetItemText(i,17,csFmtusri2_units_per_week);  
			   m_listuserinfo.SetItemText(i,18,csFmtusri2_logon_hours);  
			   m_listuserinfo.SetItemText(i,19,csFmtusri2_bad_pw_count);  
			   m_listuserinfo.SetItemText(i,20,csFmtusri2_num_logons);    
			   m_listuserinfo.SetItemText(i,21,csFmtusri2_country_code);  
			   m_listuserinfo.SetItemText(i,22,csFmtusri2_code_page);			   			   
			   m_listuserinfo.SetItemText(i,23,csFmtusri2_workstations);
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

