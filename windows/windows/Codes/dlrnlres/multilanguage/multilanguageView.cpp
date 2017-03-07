// multilanguageView.cpp : implementation of the CMultilanguageView class
//

#include "stdafx.h"
#include "multilanguage.h"

#include "multilanguageDoc.h"
#include "multilanguageView.h"

#include "TestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageView

IMPLEMENT_DYNCREATE(CMultilanguageView, CView)

BEGIN_MESSAGE_MAP(CMultilanguageView, CView)
	//{{AFX_MSG_MAP(CMultilanguageView)
	ON_COMMAND(ID_MENU_TEST, OnMenuTest)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageView construction/destruction

CMultilanguageView::CMultilanguageView()
{
	// TODO: add construction code here

}

CMultilanguageView::~CMultilanguageView()
{
}

BOOL CMultilanguageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageView drawing

void CMultilanguageView::OnDraw(CDC* pDC)
{
	CMultilanguageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageView printing

BOOL CMultilanguageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMultilanguageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMultilanguageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageView diagnostics

#ifdef _DEBUG
void CMultilanguageView::AssertValid() const
{
	CView::AssertValid();
}

void CMultilanguageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultilanguageDoc* CMultilanguageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultilanguageDoc)));
	return (CMultilanguageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultilanguageView message handlers

void CMultilanguageView::OnMenuTest() 
{
	CTestDialog	dlg;
	dlg.DoModal();
}
