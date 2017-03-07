// testGDIDlg.cpp : implementation file
//

#include "stdafx.h"

#include <locale.h>

#include "TestCharacterSet.h"
#include "TestCharacterSetDlg.h"

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
// TestCharacterSetDlg dialog

TestCharacterSetDlg::TestCharacterSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TestCharacterSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(TestCharacterSetDlg)
	m_csFontName = _T("Arial");
	m_nAPIType = 0;
	m_csCodePageSet = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void TestCharacterSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TestCharacterSetDlg)
	DDX_Control(pDX, IDC_EDIT_CODE_PAGE, m_editCodePage);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_staticText);
	DDX_Text(pDX, IDC_EDIT_FONT_NAME, m_csFontName);
	DDX_Radio(pDX, IDC_RADIO_API_TYPE, m_nAPIType);
	DDX_Text(pDX, IDC_EDIT_CODE_PAGE_SET, m_csCodePageSet);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(TestCharacterSetDlg, CDialog)
	//{{AFX_MSG_MAP(TestCharacterSetDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_CODEPAGE, OnButtonQueryCodePage)
	ON_BN_CLICKED(IDC_BUTTON_SET_CODE_PAGE, OnButtonSetCodePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TestCharacterSetDlg message handlers

BOOL TestCharacterSetDlg::OnInitDialog()
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
    TCHAR szMyName[MAX_PATH] = _T("");
    ::GetModuleFileName(NULL, szMyName, MAX_PATH - 1);
    TCHAR* pName = ::_tcsrchr(szMyName, _T('\\'));
    this->SetWindowText(pName+1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void TestCharacterSetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void TestCharacterSetDlg::OnPaint() 
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
HCURSOR TestCharacterSetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
HFONT CreateMyFont(LPCTSTR lpszFontName, int nFontSize)
{
    LOGFONT logFont;
    ::memset(&logFont, 0, sizeof(logFont));

    logFont.lfHeight = nFontSize;
    logFont.lfQuality = DEFAULT_QUALITY;
    logFont.lfCharSet = DEFAULT_CHARSET;// DEFAULT_CHARSET;//GB2312_CHARSET;
    logFont.lfWeight = FW_NORMAL;
    ::_tcsncpy(logFont.lfFaceName, lpszFontName, LF_FACESIZE-1);

    HFONT hFont = NULL;
    hFont = ::CreateFontIndirect(&logFont);

    return hFont;
}


void TestCharacterSetDlg::DrawMyText( LPCTSTR lpszFontName, LPCTSTR lpszText )
{
    HDC hdc = ::GetDC(this->m_hWnd);

    RECT stRect;
    stRect.left = 10;
    stRect.top = 10;
    stRect.right = 500;
    stRect.bottom = 50;
    
    int nFontSize = 5;
    for (int i = 0; i < 1000; ++i)
    {
        nFontSize += 1;

        CFont oFont;
        oFont.CreatePointFont(nFontSize*10, lpszFontName);
        
        HFONT hFont = (HFONT)(oFont.m_hObject)/*CreateMyFont(lpszFontName, nFontSize)*/;
        HFONT hOldFont = (HFONT)::SelectObject(hdc, hFont);
        
        if (0 == m_nAPIType)
        {
            ::TextOut(hdc, 0, 0, lpszText, ::_tcslen(lpszText));
        }
        else
        {
            ::SetWindowText(m_staticText.m_hWnd, lpszText);
        }

        
        ::SelectObject(hdc, hOldFont);
        ::DeleteObject(hFont);
    }
    
    ::ReleaseDC(this->m_hWnd, hdc);
    
    this->RedrawWindow();
}

//////////////////////////////////////////////////////////////////////////
void TestCharacterSetDlg::OnButton1() 
{
    UpdateData(TRUE);

    LPCTSTR lpszFontName = m_csFontName.operator LPCTSTR();
    LPCTSTR lpszText = _T("我们是中国人！");
    
    DrawMyText(lpszFontName, lpszText);
}

void TestCharacterSetDlg::OnButton2() 
{
    UpdateData(TRUE);
    LPCTSTR lpszFontName = m_csFontName.operator LPCTSTR();
    LPCTSTR lpszText = _T("ABC");
    
    DrawMyText(lpszFontName, lpszText);
}

void TestCharacterSetDlg::OnButton3() 
{
    UpdateData(TRUE);

    LPCTSTR lpszFontName = m_csFontName.operator LPCTSTR();
    LPCTSTR lpszText = _T("にほん");
	
    DrawMyText(lpszFontName, lpszText);
}


void TestCharacterSetDlg::OnButtonSetCodePage() 
{
    UpdateData(TRUE);

    ::_tsetlocale(LC_ALL, m_csCodePageSet);
}

void TestCharacterSetDlg::OnButtonQueryCodePage() 
{
    TCHAR* pLocal = ::_tsetlocale(LC_ALL, NULL);

    m_editCodePage.SetWindowText(pLocal);
}
