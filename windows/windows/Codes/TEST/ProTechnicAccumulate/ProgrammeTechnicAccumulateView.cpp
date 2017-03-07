// ProgrammeTechnicAccumulateView.cpp : implementation of the CProgrammeTechnicAccumulateView class
//

#include "stdafx.h"
#include "ProgrammeTechnicAccumulate.h"

#include "ProgrammeTechnicAccumulateDoc.h"
#include "ProgrammeTechnicAccumulateView.h"

#include "GraphicsProgrammeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateView

IMPLEMENT_DYNCREATE(CProgrammeTechnicAccumulateView, CView)

BEGIN_MESSAGE_MAP(CProgrammeTechnicAccumulateView, CView)
	//{{AFX_MSG_MAP(CProgrammeTechnicAccumulateView)
	ON_COMMAND(ID_MENU_GRAPHICS_PROGRAMME, OnMenuGraphicsProgramme)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateView construction/destruction

CProgrammeTechnicAccumulateView::CProgrammeTechnicAccumulateView()
{
	// TODO: add construction code here

}

CProgrammeTechnicAccumulateView::~CProgrammeTechnicAccumulateView()
{
}

BOOL CProgrammeTechnicAccumulateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateView drawing

void CProgrammeTechnicAccumulateView::OnDraw(CDC* pDC)
{
	CProgrammeTechnicAccumulateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateView printing

BOOL CProgrammeTechnicAccumulateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProgrammeTechnicAccumulateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProgrammeTechnicAccumulateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateView diagnostics

#ifdef _DEBUG
void CProgrammeTechnicAccumulateView::AssertValid() const
{
	CView::AssertValid();
}

void CProgrammeTechnicAccumulateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProgrammeTechnicAccumulateDoc* CProgrammeTechnicAccumulateView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProgrammeTechnicAccumulateDoc)));
	return (CProgrammeTechnicAccumulateDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgrammeTechnicAccumulateView message handlers

void CProgrammeTechnicAccumulateView::OnMenuGraphicsProgramme() 
{
	CGraphicsProgrammeDlg iGraphicsProgrammeDlg( this );
	
	int nDlgStatus = iGraphicsProgrammeDlg.DoModal();
	
	if ( IDOK == nDlgStatus )
	{

	}	
}
