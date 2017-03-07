// WhoSLockingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WhoSLocking.h"
#include "WhoSLockingDlg.h"

#include "GetServiceName.h"

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
// CWhoSLockingDlg dialog

CWhoSLockingDlg::CWhoSLockingDlg(CWnd* pParent /*=NULL*/, LPCTSTR lpszDefaultFilePath /*=NULL*/)
	: CDialog(CWhoSLockingDlg::IDD, pParent)
    , m_szDefaultFileName(lpszDefaultFilePath)
{
	//{{AFX_DATA_INIT(CWhoSLockingDlg)
	m_szMessageText = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWhoSLockingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWhoSLockingDlg)
	DDX_Control(pDX, IDC_MESSAGE_TEXT, m_oMessageText);
	DDX_Control(pDX, IDC_FRAME_LIST_PROCESS, m_oFrameListProcess);
	DDX_Control(pDX, IDC_FRAME_DLL_MODULE, m_oFrameDLLModule);
	DDX_Control(pDX, IDC_BROWSE_DLL_NAME, m_oBrowseDLLButton);
	DDX_Control(pDX, IDC_EDIT_MODULE_NAME, m_oModuleNameEdit);
	DDX_Control(pDX, IDOK, m_oOKButton);
	DDX_Control(pDX, IDC_REFRESH, m_oRefreshButton);
	DDX_Control(pDX, IDC_LIST_PROCESSES, m_oListOfProcesses);
	DDX_Text(pDX, IDC_MESSAGE_TEXT, m_szMessageText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWhoSLockingDlg, CDialog)
	//{{AFX_MSG_MAP(CWhoSLockingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE_DLL_NAME, OnBrowseDllName)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhoSLockingDlg message handlers

BOOL CWhoSLockingDlg::OnInitDialog()
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
	
	// Extra initialization
    (GetDlgItem(IDC_EDIT_MODULE_NAME))->SetWindowText(m_szDefaultFileName);

	m_oListOfProcesses.DeleteAllItems();
    m_oListOfProcesses.AddColumn(PROCESS_LIST_HEADER_COLUMN_0,0);
	m_oListOfProcesses.AddColumn(PROCESS_LIST_HEADER_COLUMN_1,1);
	m_oListOfProcesses.AddColumn(PROCESS_LIST_HEADER_COLUMN_2,2);
	m_oListOfProcesses.AddColumn(PROCESS_LIST_HEADER_COLUMN_3,3);

    if (m_szDefaultFileName == "") {
        (GetDlgItem(IDC_MESSAGE_TEXT))->SetWindowText("Please type (or browse to) a DLL path to examine.");
    } else {
        OnRefresh();
    }

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWhoSLockingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWhoSLockingDlg::OnPaint() 
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
HCURSOR CWhoSLockingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWhoSLockingDlg::OnBrowseDllName() 
{
    CFileDialog oFileDialog(TRUE, // Open...
							NULL, // default filename extension
							GetDefaultFileName(), // initial filename
							OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, // options
							"Executable Files (*.exe;*.dll;*.ocx)|*.exe; *.dll; *.ocx|All Files (*.*)|*.*||", // two filters for modules
							this);
    if ( oFileDialog.DoModal() == IDOK ) {

        CString szModuleName=oFileDialog.GetPathName();

        SetDefaultFileName(szModuleName);

        (GetDlgItem(IDC_EDIT_MODULE_NAME))->SetWindowText(m_szDefaultFileName);

        // Force refresh list
        OnRefresh();
    }
}

void CWhoSLockingDlg::OnRefresh() 
{
    // Store filename for next call
    (GetDlgItem(IDC_EDIT_MODULE_NAME))->GetWindowText(m_szDefaultFileName);
    CString szModuleName = m_szDefaultFileName;

    // Find list of processes which loaded this module
    DWORD dwFoundPID = 0;
    int nRecords =0;
    int nItemPosition = -1;
    if (szModuleName.GetLength()) {

	    CMapStringToString PIDNameMap;

        // Refresh GUI
	    m_oListOfProcesses.DeleteAllItems();

        (GetDlgItem(IDC_MESSAGE_TEXT))->SetWindowText("Searching for process(es)...");
        CWaitCursor oWaiting;
		if (m_oProcessAPI.BuildProcessList(PIDNameMap)) {

			// Find this module in all processes
			CMapStringToString oLoadingProcessMap;

			if (m_oProcessAPI.GetProcessesLockingModule(szModuleName, PIDNameMap, oLoadingProcessMap)) {

				POSITION hProcessPosition = NULL;
				CString ProcessName;
				CString PIDString;
				CString szExecutablePath;
				CString szServiceName;

				hProcessPosition = oLoadingProcessMap.GetStartPosition();

				while ( hProcessPosition != NULL ) {

					// Get key ( PIDString ) and value ( ProcessName )
					oLoadingProcessMap.GetNextAssoc( hProcessPosition, PIDString, ProcessName );

					// Get executable path
					szExecutablePath = m_oProcessAPI.GetProcessExecutableName(atol(PIDString));

					// Get service name (if applicable)
					szServiceName = GetServiceName(szExecutablePath);

					// Add process entry in the listbox
					nItemPosition = m_oListOfProcesses.AddItem(nRecords,0,ProcessName);
					if (nItemPosition != -1) {
						m_oListOfProcesses.AddItem(nItemPosition,1,PIDString);
						m_oListOfProcesses.AddItem(nItemPosition,2,szExecutablePath);
						m_oListOfProcesses.AddItem(nItemPosition,3,szServiceName);
					}

					nRecords++;
				}

			}

		} else {

				AfxMessageBox("Fatal error: cannot build list of processes", 
							  MB_OK|MB_ICONERROR);

		}

        CString szMessageText;
        if (nRecords == 0) {
            szMessageText = "No process found: This DLL is not locked.";
        } else {
            szMessageText.Format("%d process%s found.", nRecords, (nRecords<2?"":"es"));
        }
        (GetDlgItem(IDC_MESSAGE_TEXT))->SetWindowText(szMessageText);

    }
}

void CWhoSLockingDlg::OnOK() 
{
    // Simply exit the dialog
	CDialog::OnOK();
}

CString CWhoSLockingDlg::GetDefaultFileName()
{
    return(m_szDefaultFileName);
}

void CWhoSLockingDlg::SetDefaultFileName(LPCTSTR lpszDefaultFileName)
{
    m_szDefaultFileName = lpszDefaultFileName;
}

void CWhoSLockingDlg::OnSize(UINT nType, int cx, int cy) 
{
	TRACE3("CWhoSLockingDlg::OnSize(%u, %d, %d)\n", nType, cx, cy);
	CDialog::OnSize(nType, cx, cy);

    RECT oDialogRect;
    GetClientRect(&oDialogRect);
	TRACE1("oDialogRect.bottom = %d\n", oDialogRect.bottom);
	TRACE1("oDialogRect.top    = %d\n", oDialogRect.top);
	TRACE1("oDialogRect.left   = %d\n", oDialogRect.left);
	TRACE1("oDialogRect.right = %d\n", oDialogRect.right);

    // Define border size
    int nBorder=10;
    int nTextHeight=16; 
    // Compute text height, based on the text in a frame 
    // It's used to shift the y position of controls INSIDE the frame.
    if (m_oFrameDLLModule.m_hWnd) {
        CDC *pCDC = m_oFrameDLLModule.GetDC();
        if (pCDC) {
            CString szTheString;
            m_oFrameDLLModule.GetWindowText(szTheString);
            CSize oTextSize = pCDC->GetTextExtent(szTheString);
            nTextHeight = oTextSize.cy;
        }
    }
    CRect oOKButtonRect;
    CRect oRefreshButtonRect;
    CRect oDLLFrameRect;
    CRect oProcessFrameRect;
    CRect oProcessListRect;
    CRect oBrowseDLLButtonRect;
    CRect oDLLEditRect;
    CRect oMessageTextRect;

    // Move the OK button (x: centered, y: bottom minus border, w/h: unchanged)
    if (m_oOKButton.m_hWnd) {
        m_oOKButton.GetClientRect(&oOKButtonRect);
        oOKButtonRect.OffsetRect(cx/2 - oOKButtonRect.Width()/2 , cy - nBorder - oOKButtonRect.Height());
        m_oOKButton.MoveWindow(oOKButtonRect);
    }

    // Move the DLL Frame (width: full dialog size, height: unchanged?)
    if (m_oFrameDLLModule.m_hWnd) {
        m_oFrameDLLModule.GetClientRect(&oDLLFrameRect);
        oDLLFrameRect.SetRect(nBorder, oDLLFrameRect.top, cx - nBorder, oDLLFrameRect.bottom);
        m_oFrameDLLModule.MoveWindow(oDLLFrameRect);
    }

    // Move the DLL Browse button (x: DLL frame right - border - own width, y: DLL frame top + border + nTextHeight/2, w/h unchanged)
    if (m_oBrowseDLLButton.m_hWnd) {
        m_oBrowseDLLButton.GetClientRect(&oBrowseDLLButtonRect);
        oBrowseDLLButtonRect.OffsetRect(oDLLFrameRect.right - nBorder - oBrowseDLLButtonRect.Width(), oDLLFrameRect.top + nBorder +nTextHeight/2);
        m_oBrowseDLLButton.MoveWindow(oBrowseDLLButtonRect);
    }

    // Move the DLL Edit (between DLL Frame and Browse button)
    if (m_oModuleNameEdit.m_hWnd) {
        m_oModuleNameEdit.GetClientRect(&oDLLEditRect);
        int nEditHeight = oBrowseDLLButtonRect.Height();
        oDLLEditRect.SetRect(oDLLFrameRect.left + nBorder, oBrowseDLLButtonRect.top, oBrowseDLLButtonRect.left - nBorder, oBrowseDLLButtonRect.top + nEditHeight);
        m_oModuleNameEdit.MoveWindow(oDLLEditRect);
    }

    // Move the Refresh button (x: centered, y: DLL Frame bottom - border - button height, w/h: unchanged)
    if (m_oRefreshButton.m_hWnd) {
        m_oRefreshButton.GetClientRect(&oRefreshButtonRect);
        oRefreshButtonRect.OffsetRect(cx/2 - oRefreshButtonRect.Width()/2 , oDLLFrameRect.bottom - nBorder - oRefreshButtonRect.Height());
        m_oRefreshButton.MoveWindow(oRefreshButtonRect);
    }

    // Move the Process List Frame (between upper frame and OK button, width: full dialog size)
    if (m_oFrameListProcess.m_hWnd) {
        m_oFrameListProcess.GetClientRect(&oProcessFrameRect);
        oProcessFrameRect.SetRect(nBorder, oDLLFrameRect.bottom+nBorder, cx - nBorder, oOKButtonRect.top - nBorder);
        m_oFrameListProcess.MoveWindow(oProcessFrameRect);
    }
    // Move the Message Text static (Process Frame bottom - border, width: full dialog size)
    if (m_oMessageText.m_hWnd) {
        m_oMessageText.GetClientRect(&oMessageTextRect);
        oMessageTextRect.SetRect(oProcessFrameRect.left + nBorder, oProcessFrameRect.bottom-nBorder-oMessageTextRect.Height(), oProcessFrameRect.right - nBorder, oProcessFrameRect.bottom-nBorder);
        m_oMessageText.MoveWindow(oMessageTextRect);
    }

    // Move the Process List Control (within Process List Frame, with border, above Message Text)
    if (m_oListOfProcesses.m_hWnd) {
        m_oListOfProcesses.GetClientRect(&oProcessListRect);
        oProcessListRect.SetRect(oProcessFrameRect.left + nBorder, oProcessFrameRect.top + nBorder + nTextHeight/2, oProcessFrameRect.right - nBorder, oMessageTextRect.top - nBorder);
        m_oListOfProcesses.MoveWindow(oProcessListRect, TRUE);
    }

}

void CWhoSLockingDlg::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI )
{
    // Force minimum size
    lpMMI->ptMinTrackSize.x = 320;
    lpMMI->ptMinTrackSize.y = 300;
    CWnd::OnGetMinMaxInfo(lpMMI);
}

