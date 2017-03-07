// MFCLeakTestView.cpp : implementation of the CMFCLeakTestView class
//

#include "stdafx.h"
#include "MFCLeakTest.h"

#include "MFCLeakTestDoc.h"
#include "MFCLeakTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCLeakTestView

IMPLEMENT_DYNCREATE(CMFCLeakTestView, CView)

BEGIN_MESSAGE_MAP(CMFCLeakTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCLeakTestView construction/destruction

CMFCLeakTestView::CMFCLeakTestView()
{
	// TODO: add construction code here

}

CMFCLeakTestView::~CMFCLeakTestView()
{
}

BOOL CMFCLeakTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCLeakTestView drawing

void CMFCLeakTestView::OnDraw(CDC* /*pDC*/)
{
	CMFCLeakTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CMFCLeakTestView printing

BOOL CMFCLeakTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCLeakTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCLeakTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCLeakTestView diagnostics

#ifdef _DEBUG
void CMFCLeakTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCLeakTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCLeakTestDoc* CMFCLeakTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCLeakTestDoc)));
	return (CMFCLeakTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCLeakTestView message handlers
