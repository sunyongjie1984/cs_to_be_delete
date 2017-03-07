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


#ifndef UNICODE
#define UNICODE
#endif





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
	m_value1 = 0;
	m_findaccounts = _T("");
	m_servername = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	 pBuf = NULL;
	
	 dwLevel = 0;
	 dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	 dwEntriesRead = 0;
	 dwTotalEntries = 0;
	 dwResumeHandle = 0;
	 
	 dwTotalCount = 0;
     b=0;
}

void CFffffffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFffffffDlg)
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Text(pDX, IDC_EDIT2, m_value1);
	DDX_Text(pDX, IDC_EDIT3, m_findaccounts);
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

/////////////////////////////////////////////////////////////////////////////
// CFffffffDlg message handlers

BOOL CFffffffDlg::OnInitDialog()
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

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
HCURSOR CFffffffDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//////////////////////////////////////////////////////////////////
void CFffffffDlg::OnButton1() 
{
	UpdateData();
//	m_listbox.ResetContent();
	// TODO: Add your control notification handler code here
	   //do // begin do
	   //{
#ifndef UNICODE
#define UNICODE
#endif
{


   // The server is not the default local computer.
   //LPTSTR
   
      pszServerName = m_servername.GetBuffer(0) ;
//      m_value2=pszServerName;
		 
   //
   // Call the NetUserEnum function, specifying level 0; 
   //   enumerate global user account types only.
   //
   do // begin do  
   {
	 // const char * szp = pszServerName;
      nStatus = NetUserEnum((const unsigned short *)pszServerName,
                            dwLevel,
                            //FILTER_SERVER_TRUST_ACCOUNT, // global users
                           FILTER_NORMAL_ACCOUNT,
                            ///FILTER_TEMP_DUPLICATE_ACCOUNT,
							//FILTER_WORKSTATION_TRUST_ACCOUNT,


                            (LPBYTE*)&pBuf,
                            dwPrefMaxLen,
                            &dwEntriesRead,
                            &dwTotalEntries,                            
							&dwResumeHandle);
      //
      // If the call succeeds,
      //

	//use for debug
//	  int i,j,k;
//	  switch(nStatus) {
//	  case ERROR_ACCESS_DENIED:
//		   i = 0;
//	  	break;
//	  case NERR_InvalidComputer:
//		   j = 0;
//	  	break;
//	  case ERROR_MORE_DATA:
//		   k = 0;
//		  break;
		  
//	  default:
//		  break;
//	  }
      if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
      {
         if ((pTmpBuf = pBuf) != NULL)
         {
            //
            // Loop through the entries.
            //
            for (i = 0; (i < dwEntriesRead); i++)
            {
               assert(pTmpBuf != NULL);

               if (pTmpBuf == NULL)
               {
				  
                  AfxMessageBox("An access violation has occurred" );
                  break;
               }
               //
               //  Print the name of the user account.
               //
			   CString csFmt;
			  CString csFmtcompare;
			   csFmt.Format("%S",pTmpBuf->usri0_name);
			   
             // m_listbox.AddString((/*const unsigned short **/LPTSTR)pTmpBuf->usri0_name) ;
			   csFmtcompare=m_findaccounts.GetBuffer(0) ;
               if(csFmtcompare.Compare(csFmt.GetBuffer(0))!=1)
			   {
				 
				   AfxMessageBox("find accounts");
		    	   break;
			   }
			   m_listbox.AddString(csFmt.GetBuffer(0)) ;
			   csFmtcompare=m_findaccounts.GetBuffer(0) ;

               pTmpBuf++;
               dwTotalCount++;
            }
         }
      }
      //
      // Otherwise, print the system error.
      //
      else
       //  fprintf(stderr, "A system error has occurred: %d\n", nStatus);
      //
	  m_value1=nStatus;
      // Free the allocated buffer.
      //
      if (pBuf != NULL)
      {
         NetApiBufferFree(pBuf);
         pBuf = NULL;
      }
   }
   // Continue to call NetUserEnum while 
   //  there are more entries. 
   // 
   while (nStatus == ERROR_MORE_DATA); // end do
   //
   // Check again for allocated memory.
   //
   if (pBuf != NULL)
      NetApiBufferFree(pBuf);
   //
   // Print the final count of users enumerated.
   //
   fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);

  
}
}
