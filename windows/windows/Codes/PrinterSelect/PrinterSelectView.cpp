// PrinterSelectView.cpp : implementation of the CPrinterSelectView class
//

#include "stdafx.h"
#include "PrinterSelect.h"

#include "PrinterSelectDoc.h"
#include "PrinterSelectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectView

IMPLEMENT_DYNCREATE(CPrinterSelectView, CFormView)

BEGIN_MESSAGE_MAP(CPrinterSelectView, CFormView)
	//{{AFX_MSG_MAP(CPrinterSelectView)
	ON_CBN_SELCHANGE(IDC_PRINTER_LIST, OnSelchangePrinterList)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectView construction/destruction

CPrinterSelectView::CPrinterSelectView()
	: CFormView(CPrinterSelectView::IDD)
{
	//{{AFX_DATA_INIT(CPrinterSelectView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CPrinterSelectView::~CPrinterSelectView()
{
}

void CPrinterSelectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrinterSelectView)
	DDX_Control(pDX, IDC_PRINTER_LIST, m_PrinterList);
	//}}AFX_DATA_MAP
}

BOOL CPrinterSelectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CPrinterSelectView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	// setup the list of printers
	m_PrinterList.ResetContent() ;
	CWinApp	*pApp = AfxGetApp() ;
	CPrinterSelectApp *pOurApp = static_cast<CPrinterSelectApp*>(pApp) ;
	ASSERT(pOurApp) ;
	for (int i = 0 ; i < pOurApp->m_PrinterControl.GetPrinterCount() ; i++)
		{
		m_PrinterList.AddString(pOurApp->m_PrinterControl.GetPrinterName(i)) ;
		}
	// select the current default printer
	CString	current ;
	current = pOurApp->GetDefaultPrinter() ;
	m_PrinterList.SetCurSel(m_PrinterList.FindString(0, current)) ;

}

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectView printing

BOOL CPrinterSelectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	ASSERT(pInfo) ;
	// for our example, we set the number of pages in the document to 2
	// to allow testing
	pInfo->SetMaxPage(2) ;
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPrinterSelectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrinterSelectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPrinterSelectView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(pDC) ;
	ASSERT(pInfo) ;
	// do some default output onto the page
	CString	text ;
	CSize	csText ;
	CFont	*pOldFont ;
	CFont	myFont ;

	int fontSize = -MulDiv(18, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	VERIFY(myFont.CreateFont(fontSize * 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
							DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
							FF_ROMAN, "Arial")) ;
	pOldFont = pDC->SelectObject(&myFont) ;
	pDC->Rectangle(pInfo->m_rectDraw) ;
	pDC->Ellipse(pInfo->m_rectDraw) ;
	text.Format("PAGE %1d of %1d", pInfo->m_nCurPage, pInfo->GetMaxPage()) ;
	csText = pDC->GetTextExtent(text) ;
	pDC->TextOut(pInfo->m_rectDraw.left + (pInfo->m_rectDraw.Width() - csText.cx) / 2, 
				 pInfo->m_rectDraw.top + (pInfo->m_rectDraw.Height() - csText.cy) / 2, text) ;
	pDC->SelectObject(pOldFont) ;
	VERIFY(myFont.DeleteObject()) ;
}

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectView diagnostics

#ifdef _DEBUG
void CPrinterSelectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPrinterSelectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPrinterSelectDoc* CPrinterSelectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrinterSelectDoc)));
	return (CPrinterSelectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectView message handlers

void CPrinterSelectView::OnSelchangePrinterList() 
{
	// the printer selection has changed, swap to it
	CWinApp	*pApp = AfxGetApp() ;
	CPrinterSelectApp *pOurApp = static_cast<CPrinterSelectApp*>(pApp) ;
	ASSERT(pOurApp) ;
	int		sel = m_PrinterList.GetCurSel() ;
	if (sel != CB_ERR)
		{
		pOurApp->SetNewPrinter(sel) ;
		}
}
