// SparView.cpp : implementation of the CSparView class
//

#include "stdafx.h"
#include "Spar.h"

#include "SparDoc.h"
#include "SparView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSparView

IMPLEMENT_DYNCREATE(CSparView, CView)

BEGIN_MESSAGE_MAP(CSparView, CView)
	//{{AFX_MSG_MAP(CSparView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSparView construction/destruction

CSparView::CSparView()
{
	// TODO: add construction code here

}

CSparView::~CSparView()
{
}

BOOL CSparView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSparView drawing

void CSparView::OnDraw(CDC* pDC)
{
	CSparDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here



	
	
}

/////////////////////////////////////////////////////////////////////////////
// CSparView printing

BOOL CSparView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSparView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSparView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSparView diagnostics

#ifdef _DEBUG
void CSparView::AssertValid() const
{
	CView::AssertValid();
}

void CSparView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSparDoc* CSparView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSparDoc)));
	return (CSparDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSparView message handlers

void CSparView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
	CRect rect1(300,100,375,195);
	myCard.Create("11",SS_NOTIFY|WS_CHILD |WS_VISIBLE|SS_BITMAP,rect1,this,ID_CARD);
	bmpCard.LoadBitmap(IDB_CARD);
	myCard.SetBitmap(bmpCard);
/*	myButton.Create("My Button",WS_CHILD |WS_VISIBLE|SS_ICON,rect1,this,ID_CARD);
	CIcon icon;
	
	myButton.SetIcon(icon,TRUE);

*/


}

void CSparView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	

}



