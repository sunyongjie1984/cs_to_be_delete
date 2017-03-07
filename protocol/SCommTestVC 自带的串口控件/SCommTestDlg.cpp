// SCommTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SCommTest.h"
#include "SCommTestDlg.h"

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
// CSCommTestDlg dialog

CSCommTestDlg::CSCommTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSCommTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSCommTestDlg)
	m_strEditRXData = _T("");
	m_strEditTXData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSCommTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSCommTestDlg)
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strEditRXData);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strEditTXData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSCommTestDlg, CDialog)
	//{{AFX_MSG_MAP(CSCommTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCommTestDlg message handlers

BOOL CSCommTestDlg::OnInitDialog()
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
	m_ctrlComm.SetCommPort(4); // Ñ¡Ôñcom4
	m_ctrlComm.SetInputMode(1); 
	m_ctrlComm.SetInBufferSize(1024);
	m_ctrlComm.SetOutBufferSize(512);
	m_ctrlComm.SetSettings("19200, n, 8, 1");
	if (!m_ctrlComm.GetPortOpen())
		m_ctrlComm.SetPortOpen(TRUE);
	m_ctrlComm.SetRThreshold(1);
	m_ctrlComm.SetInputLen(0);
	m_ctrlComm.GetInput();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSCommTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSCommTestDlg::OnPaint() 
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
HCURSOR CSCommTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CSCommTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSCommTestDlg)
	ON_EVENT(CSCommTestDlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSCommTestDlg::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[2048];
	CString strtemp;
	if (m_ctrlComm.GetCommEvent() == 2)
	{
		variant_inp = m_ctrlComm.GetInput();
		safearray_inp = variant_inp;
		len = safearray_inp.GetOneDimSize();
		for (k = 0; k < len; k++)
			safearray_inp.GetElement(&k, rxdata + k);
		for (k = 0; k < len; k++)
		{
			BYTE bt = *(char*)(rxdata + k);
			strtemp.Format("%C", bt);
			m_strEditRXData += strtemp;
		}
	}
	UpdateData(FALSE);
}

void CSCommTestDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ctrlComm.SetOutput(COleVariant(m_strEditTXData));
}
