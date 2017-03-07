// ExtensionDLLTestExeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtensionDLLTestExe.h"
#include "ExtensionDLLTestExeDlg.h"

#include "../Include/ExtensionDLLTest/ExportDialog.h"

#ifdef _DEBUG
#pragma comment( lib, "ExtensionDLLTestd.lib" )
#else
#pragma comment( lib, "ExtensionDLLTest.lib" )
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CExtensionDLLTestExeDlg dialog
//
CExtensionDLLTestExeDlg::CExtensionDLLTestExeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtensionDLLTestExeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtensionDLLTestExeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtensionDLLTestExeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtensionDLLTestExeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtensionDLLTestExeDlg, CDialog)
	//{{AFX_MSG_MAP(CExtensionDLLTestExeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXTDLL_TEST, OnBtnExtDllTest)
	ON_BN_CLICKED(IDC_BTN_EXPORT_MFCCLASS_TEST, OnBtnExportClassTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//
// CExtensionDLLTestExeDlg message handlers

BOOL CExtensionDLLTestExeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	
	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CExtensionDLLTestExeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

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
HCURSOR CExtensionDLLTestExeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExtensionDLLTestExeDlg::OnBtnExtDllTest() 
{
	CString csMessage;
	csMessage.LoadString( IDS_TESTMESSAGE );

	MessageBox( csMessage );
}

void CExtensionDLLTestExeDlg::OnBtnExportClassTest() 
{
	CExportDialog dlg;
	dlg.DoModal();
}
