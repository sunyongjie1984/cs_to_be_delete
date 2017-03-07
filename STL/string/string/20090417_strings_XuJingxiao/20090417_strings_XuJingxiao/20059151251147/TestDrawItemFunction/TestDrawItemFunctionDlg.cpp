// TestDrawItemFunctionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDrawItemFunction.h"
#include "TestDrawItemFunctionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDrawItemFunctionDlg dialog

CTestDrawItemFunctionDlg::CTestDrawItemFunctionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDrawItemFunctionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDrawItemFunctionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDrawItemFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDrawItemFunctionDlg)
	DDX_Control(pDX, IDC_LIST_TEST, m_lc_test);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDrawItemFunctionDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDrawItemFunctionDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDrawItemFunctionDlg message handlers

BOOL CTestDrawItemFunctionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	static CImageList il;
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_DOG);
	il.Create(120,120,ILC_COLOR16,0,0);
	il.Add(&bitmap,(RGB(0,0,0)));
	m_lc_test.SetImageList(&il,LVSIL_SMALL);
	m_lc_test.InsertColumn(0,"Head1");m_lc_test.SetColumnWidth(0,300);
	m_lc_test.InsertColumn(1,"Head2");m_lc_test.SetColumnWidth(1,100);

	m_lc_test.InsertItem(0,"Item1",0);m_lc_test.SetItemText(0,1,"Item11");
	m_lc_test.InsertItem(0,"Item2",0);m_lc_test.SetItemText(0,1,"Item22");
	m_lc_test.InsertItem(0,"Item3",0);m_lc_test.SetItemText(0,1,"Item33");
	m_lc_test.InsertItem(0,"Item4",0);m_lc_test.SetItemText(0,1,"Item44");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDrawItemFunctionDlg::OnPaint() 
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
HCURSOR CTestDrawItemFunctionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDrawItemFunctionDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ListBox.ResetContent();
	CDialog::OnRButtonUp(nFlags, point);
}
