// SafetyCodeView.cpp : implementation of the CSafetyCodeView class
//

#include "stdafx.h"
#include "SafetyCode.h"

#include "SafetyCodeDoc.h"
#include "SafetyCodeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeView

IMPLEMENT_DYNCREATE(CSafetyCodeView, CView)

BEGIN_MESSAGE_MAP(CSafetyCodeView, CView)
	//{{AFX_MSG_MAP(CSafetyCodeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeView construction/destruction

CSafetyCodeView::CSafetyCodeView()
{
	// TODO: add construction code here

}

CSafetyCodeView::~CSafetyCodeView()
{
}

BOOL CSafetyCodeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeView drawing

void CSafetyCodeView::OnDraw(CDC* pDC)
{
	CSafetyCodeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeView printing

BOOL CSafetyCodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSafetyCodeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSafetyCodeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeView diagnostics

#ifdef _DEBUG
void CSafetyCodeView::AssertValid() const
{
	CView::AssertValid();
}

void CSafetyCodeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSafetyCodeDoc* CSafetyCodeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSafetyCodeDoc)));
	return (CSafetyCodeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeView message handlers
