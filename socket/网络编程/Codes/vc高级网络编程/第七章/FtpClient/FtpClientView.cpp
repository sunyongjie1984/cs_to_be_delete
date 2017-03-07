// xiongFtpView.cpp : implementation of the CFtpClientView class
//

#include "stdafx.h"
#include "FtpClient.h"

#include "FtpClientDoc.h"
#include "FtpClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFtpClientView

IMPLEMENT_DYNCREATE(CFtpClientView, CListView)

BEGIN_MESSAGE_MAP(CFtpClientView, CListView)
	//{{AFX_MSG_MAP(CFtpClientView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpClientView construction/destruction

CFtpClientView::CFtpClientView()
{
	// TODO: add construction code here

}

CFtpClientView::~CFtpClientView()
{
}

BOOL CFtpClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFtpClientView drawing

void CFtpClientView::OnDraw(CDC* pDC)
{
	CFtpClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CFtpClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CFtpClientView printing

BOOL CFtpClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFtpClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFtpClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFtpClientView diagnostics

#ifdef _DEBUG
void CFtpClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CFtpClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFtpClientDoc* CFtpClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFtpClientDoc)));
	return (CFtpClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFtpClientView message handlers
