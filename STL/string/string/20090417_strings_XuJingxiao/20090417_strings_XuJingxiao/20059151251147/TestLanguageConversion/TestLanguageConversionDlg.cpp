// TestLanguageConversionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestLanguageConversion.h"
#include "TestLanguageConversionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestLanguageConversionDlg dialog

CTestLanguageConversionDlg::CTestLanguageConversionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestLanguageConversionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestLanguageConversionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestLanguageConversionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestLanguageConversionDlg)
	DDX_Control(pDX, IDC_BUTTON_KR, m_btn_KR);
	DDX_Control(pDX, IDC_BUTTON_JP, m_btn_JP);
	DDX_Control(pDX, IDC_BUTTON_EN, m_btn_EN);
	DDX_Control(pDX, IDC_BUTTON_CN, m_btn_CN);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestLanguageConversionDlg, CDialog)
	//{{AFX_MSG_MAP(CTestLanguageConversionDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CN, OnButtonCn)
	ON_BN_CLICKED(IDC_BUTTON_JP, OnButtonJp)
	ON_BN_CLICKED(IDC_BUTTON_KR, OnButtonKr)
	ON_BN_CLICKED(IDC_BUTTON_EN, OnButtonEn)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestLanguageConversionDlg message handlers

BOOL CTestLanguageConversionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Localize();
	m_btn_CN.DrawBorder(1,0);
	m_btn_CN.SetPushLike(1,0);
	//m_btn_CN.SetColor(BTNST_COLOR_BK_IN,RGB(255,0,0),0);
	m_btn_CN.SetIcon(IDI_CN,0);

	m_btn_EN.DrawBorder(1,0);
	m_btn_EN.SetPushLike(1,0);
	//m_btn_EN.SetColor(BTNST_COLOR_BK_IN,RGB(0,255,0),0);
	m_btn_EN.SetIcon(IDI_EN,0);

	m_btn_JP.DrawBorder(1,0);
	m_btn_JP.SetPushLike(1,0);
	//m_btn_JP.SetColor(BTNST_COLOR_BK_IN,RGB(0,0,255),0);
	m_btn_JP.SetIcon(IDI_JP,0);

	m_btn_KR.DrawBorder(1,0);
	m_btn_KR.SetPushLike(1,0);
	//m_btn_KR.SetColor(BTNST_COLOR_BK_IN,RGB(255,255,255),0);
	m_btn_KR.SetIcon(IDI_KR,0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestLanguageConversionDlg::OnPaint() 
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
HCURSOR CTestLanguageConversionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestLanguageConversionDlg::OnButtonCn() 
{
	if(!SetThreadLocale(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED)))
	{
		MessageBox(_T("No Cn"));
		return;
	}
	Localize();	
}

void CTestLanguageConversionDlg::OnButtonJp() 
{
	if(!SetThreadLocale(0x0411))
	{
		MessageBox(_T("No Jp"));
		return;
	}
	Localize();
}

void CTestLanguageConversionDlg::OnButtonKr() 
{
	if(!SetThreadLocale(MAKELANGID(LANG_KOREAN,SUBLANG_DEFAULT)))
	{
		MessageBox(_T("No Kr"));
		return;
	}
	Localize();
}
void CTestLanguageConversionDlg::OnButtonEn() 
{
	if(!SetThreadLocale(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT)))
	{
		MessageBox(_T("No En"));
		return;
	}
	Localize();
}

void CTestLanguageConversionDlg::Localize()
{
	CString s;
	s.LoadString(IDS_STR_PROMPT);
	GetDlgItem(IDC_STATIC_PROMPT)->SetWindowText(s);
	s.LoadString(IDS_STR_TITLE);
	SetWindowText(s);
}

void CTestLanguageConversionDlg::PopupMenu(CPoint point)
{
	CString s;
	CImageList* pil;
	pil=new CImageList;
	pil->Create(16,16,ILC_COLOR8|ILC_MASK,0,0);
	pil->Add(LoadIcon(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1)));
	pil->Add(LoadIcon(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2)));

	CMenu *m,*msub;
	m=new CMenu;
	m->LoadMenu(IDR_MENU_POP);
	msub=m->GetSubMenu(0);
	TCHAR * p;
	p=new TCHAR[50];

	#define ZERO(x) memset(x,0,50)	 
	BCMenu *bm;
	bm=new BCMenu;
	bm->CreatePopupMenu();
	
	UINT iCount=msub->GetMenuItemCount();

	ZERO(p);
	s.LoadString(IDS_STR_TITLE);
	memcpy(p,s,s.GetLength());
	bm->AppendMenu(0,IDM_ITEM1,p,pil,0);

	ZERO(p);
	s.LoadString(IDS_STR_PROMPT);
	memcpy(p,s,s.GetLength());
	bm->AppendMenu(0,IDM_ITEM1,p,pil,1);



	bm->SetMenuDrawMode(1);
	ClientToScreen(&point);
	bm->TrackPopupMenu(0,point.x,point.y,this,0);

	memset(p,0,50);
	delete p;
	
	bm->DeleteTempMap();
	bm->DestroyMenu();
	delete bm;
	
	m->DeleteTempMap();
	m->DestroyMenu();
	delete m;

	pil->DeleteTempMap();
	pil->DeleteImageList();
	delete pil;
}

void CTestLanguageConversionDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	PopupMenu(point);
	CDialog::OnRButtonUp(nFlags, point);
}
