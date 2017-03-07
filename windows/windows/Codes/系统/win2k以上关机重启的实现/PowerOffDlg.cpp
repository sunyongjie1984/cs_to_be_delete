// PowerOffDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerOff.h"
#include "PowerOffDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPowerOffDlg dialog

CPowerOffDlg::CPowerOffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerOffDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPowerOffDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPowerOffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPowerOffDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPowerOffDlg, CDialog)
	//{{AFX_MSG_MAP(CPowerOffDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK2, OnOk2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerOffDlg message handlers

BOOL CPowerOffDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPowerOffDlg::OnPaint() 
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
HCURSOR CPowerOffDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPowerOffDlg::OnOK() 
{
	CDialog::OnOK();
    TOKEN_PRIVILEGES tp;
    HANDLE hToken; 
    LUID luid; 
    LPTSTR MachineName=NULL; 
    if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken ))
	{
       // PERR("OpenProcessToken",GetLastError());
        return ;
	}
    if(!LookupPrivilegeValue(MachineName, SE_SHUTDOWN_NAME, &luid))
	{
      //  PERR("LookupPrivilegeValue", GetLastError());
        return ; 
	}
    tp.PrivilegeCount = 1; 
    tp.Privileges[0].Luid = luid; 
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
    AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),NULL, NULL ); //到这里,是取得权限///
    ExitWindowsEx(EWX_POWEROFF,EWX_FORCE);	
	
}

void CPowerOffDlg::OnOk2() 
{
	// TODO: Add your control notification handler code here
	//EWX_REBOOT
	CDialog::OnOK();
    TOKEN_PRIVILEGES tp;
    HANDLE hToken; 
    LUID luid; 
    LPTSTR MachineName=NULL; 
    if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken ))
	{
       // PERR("OpenProcessToken",GetLastError());
        return ;
	}
    if(!LookupPrivilegeValue(MachineName, SE_SHUTDOWN_NAME, &luid))
	{
      //  PERR("LookupPrivilegeValue", GetLastError());
        return ; 
	}
    tp.PrivilegeCount = 1; 
    tp.Privileges[0].Luid = luid; 
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
    AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),NULL, NULL ); //到这里,是取得权限///
    ExitWindowsEx(EWX_REBOOT,EWX_FORCE);
}
