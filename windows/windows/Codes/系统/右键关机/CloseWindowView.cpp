// CloseWindowView.cpp : implementation of the CCloseWindowView class
//

#include "stdafx.h"
#include "CloseWindow.h"

#include "CloseWindowDoc.h"
#include "CloseWindowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowView

IMPLEMENT_DYNCREATE(CCloseWindowView, CView)

BEGIN_MESSAGE_MAP(CCloseWindowView, CView)
	//{{AFX_MSG_MAP(CCloseWindowView)
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowView construction/destruction

CCloseWindowView::CCloseWindowView()
{
	// TODO: add construction code here

}

CCloseWindowView::~CCloseWindowView()
{
}

BOOL CCloseWindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowView drawing

void CCloseWindowView::OnDraw(CDC* pDC)
{
	CCloseWindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowView printing

BOOL CCloseWindowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCloseWindowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCloseWindowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowView diagnostics

#ifdef _DEBUG
void CCloseWindowView::AssertValid() const
{
	CView::AssertValid();
}

void CCloseWindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCloseWindowDoc* CCloseWindowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCloseWindowDoc)));
	return (CCloseWindowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowView message handlers

void CCloseWindowView::CloseWindow()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	//取得当前进程存权令牌的句柄
    if(!OpenProcessToken(GetCurrentProcess(),
		 TOKEN_ADJUST_PRIVILEGES,&hToken))
	{
		MessageBox("无法关机");
		return;
	}
	//得到关机特权的LUID
	LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,
		    &tkp.Privileges[0].Luid);
	//使进程据有关机特权
    tkp.PrivilegeCount=1;
	tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken,FALSE,&tkp,0,
		 (PTOKEN_PRIVILEGES)NULL,0);
	if(GetLastError()!=ERROR_SUCCESS)
	{
		MessageBox("无法关机！");
	}
	//关机
	if(!ExitWindowsEx(EWX_POWEROFF,0))
	{
		MessageBox("无法关机！");
	}
}

void CCloseWindowView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CloseWindow();
	CView::OnRButtonDblClk(nFlags,point);
	
	CView::OnRButtonDblClk(nFlags, point);
}
