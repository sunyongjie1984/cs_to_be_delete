
// eeeView.cpp : implementation of the CeeeView class
//

#include "stdafx.h"
#include "eee.h"

#include "eeeDoc.h"
#include "eeeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern "C" __declspec(dllimport) int fun(int x1,int x2,int x3);

// CeeeView

IMPLEMENT_DYNCREATE(CeeeView, CView)

BEGIN_MESSAGE_MAP(CeeeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CeeeView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CeeeView construction/destruction

CeeeView::CeeeView()
{
	// TODO: add construction code here

}

CeeeView::~CeeeView()
{
}

BOOL CeeeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CeeeView drawing

void CeeeView::OnDraw(CDC *pDC)
{
	CeeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	int x=fun(1, 2, 3);
	CString str;
	str.Format(L"%d", x);
	pDC->TextOut(10, 10, str);

}


// CeeeView printing


void CeeeView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CeeeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CeeeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CeeeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CeeeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CeeeView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CeeeView diagnostics

#ifdef _DEBUG
void CeeeView::AssertValid() const
{
	CView::AssertValid();
}

void CeeeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CeeeDoc* CeeeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CeeeDoc)));
	return (CeeeDoc*)m_pDocument;
}
#endif //_DEBUG


// CeeeView message handlers
