// SCCView.cpp : implementation file
//

#include "stdafx.h"
#include "SCCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSCCView

IMPLEMENT_DYNCREATE(CSCCView, CXRichEditView)

CSCCView::CSCCView()
{
}

CSCCView::~CSCCView()
{
}


BEGIN_MESSAGE_MAP(CSCCView, CXRichEditView)
	//{{AFX_MSG_MAP(CSCCView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCCView drawing

void CSCCView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSCCView diagnostics

#ifdef _DEBUG
void CSCCView::AssertValid() const
{
	CXRichEditView::AssertValid();
}

void CSCCView::Dump(CDumpContext& dc) const
{
	CXRichEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSCCView message handlers
