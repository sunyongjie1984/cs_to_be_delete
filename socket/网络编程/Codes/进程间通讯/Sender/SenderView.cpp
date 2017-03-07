// SenderView.cpp : implementation of the CSenderView class
//

#include "stdafx.h"
#include "Sender.h"

#include "SenderDoc.h"
#include "SenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSenderView

IMPLEMENT_DYNCREATE(CSenderView, CView)

BEGIN_MESSAGE_MAP(CSenderView, CView)
	//{{AFX_MSG_MAP(CSenderView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSenderView construction/destruction

CSenderView::CSenderView()
{
	// TODO: add construction code here

}

CSenderView::~CSenderView()
{
}

BOOL CSenderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSenderView drawing

void CSenderView::OnDraw(CDC* pDC)
{
	CSenderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSenderView printing

BOOL CSenderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSenderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSenderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSenderView diagnostics

#ifdef _DEBUG
void CSenderView::AssertValid() const
{
	CView::AssertValid();
}

void CSenderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSenderDoc* CSenderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSenderDoc)));
	return (CSenderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSenderView message handlers
