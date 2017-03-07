// ReceiverView.cpp : implementation of the CReceiverView class
//

#include "stdafx.h"
#include "Receiver.h"

#include "ReceiverDoc.h"
#include "ReceiverView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReceiverView

IMPLEMENT_DYNCREATE(CReceiverView, CView)

BEGIN_MESSAGE_MAP(CReceiverView, CView)
	//{{AFX_MSG_MAP(CReceiverView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReceiverView construction/destruction

CReceiverView::CReceiverView()
{
	// TODO: add construction code here

}

CReceiverView::~CReceiverView()
{
}

BOOL CReceiverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CReceiverView drawing

void CReceiverView::OnDraw(CDC* pDC)
{
	CReceiverDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CReceiverView printing

BOOL CReceiverView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReceiverView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReceiverView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CReceiverView diagnostics

#ifdef _DEBUG
void CReceiverView::AssertValid() const
{
	CView::AssertValid();
}

void CReceiverView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReceiverDoc* CReceiverView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReceiverDoc)));
	return (CReceiverDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReceiverView message handlers
