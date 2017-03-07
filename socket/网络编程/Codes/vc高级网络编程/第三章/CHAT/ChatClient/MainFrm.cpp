// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ChatClient.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_ADDLIST, OnAddMember)
	ON_MESSAGE(WM_ADDLIST + 1, OnRemoveMember)
	ON_MESSAGE(WM_DBCLICKITEM, OnDblClickItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndSend.Create(this, IDD_SENDDLG, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, IDD_SENDDLG))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndOnline.Create(this, IDD_ONLINEDLG, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, IDD_ONLINEDLG))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndSend.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndSend, AFX_IDW_DOCKBAR_BOTTOM);
	m_wndSend.SetWindowText(_TEXT("发送窗口"));

	m_wndOnline.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndOnline, AFX_IDW_DOCKBAR_LEFT);
	m_wndOnline.SetWindowText(_TEXT("在线列表"));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_SIZEBOX;
	cs.cx = 640;
	cs.cy = 480;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	CComboBox* pType = (CComboBox*)m_wndSend.GetDlgItem(IDC_TYPE);
	
	pType->ResetContent();
	CString str;
	for(int i = 0; i <= 32; i++)
    {
        str.LoadString(IDS_S0 + i);
        pType->AddString(str);
    }
    pType->SetCurSel(0);
}

void CMainFrame::OnAddMember(WPARAM wParam, LPARAM lParam)
{
	CString* pStr = (CString*)wParam;
	m_wndOnline.m_ListCtrl->AddItem((short)lParam, pStr->GetBuffer(0), NULL);
	pStr->ReleaseBuffer();
}

CMainFrame::OnRemoveMember(WPARAM wParam, LPARAM lParam)
{
	CString* pStr = (CString*)wParam;
	if(!pStr->CompareNoCase("DUMP"))
		m_wndOnline.m_ListCtrl->DeleteAllItems();
	else
		m_wndOnline.m_ListCtrl->Remove(pStr->GetBuffer(0));
	pStr->ReleaseBuffer();
}

void CMainFrame::OnDblClickItem(WPARAM wParam, LPARAM lParam)
{
	CString* pStr = (CString*)lParam;

	CComboBox* pTo = (CComboBox*)m_wndSend.GetDlgItem(IDC_TO);
	pTo->AddString(*pStr);
	pTo->SetWindowText(*pStr);
}
