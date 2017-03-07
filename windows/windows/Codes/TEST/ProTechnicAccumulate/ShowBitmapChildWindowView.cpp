// ShowBitmapChildWindowView.cpp : implementation file
//

#include "stdafx.h"
#include "ProgrammeTechnicAccumulate.h"
#include "ShowBitmapChildWindowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowView

IMPLEMENT_DYNCREATE(CShowBitmapChildWindowView, CView)

CShowBitmapChildWindowView::CShowBitmapChildWindowView()
{
}

CShowBitmapChildWindowView::~CShowBitmapChildWindowView()
{
}


BEGIN_MESSAGE_MAP(CShowBitmapChildWindowView, CView)
	//{{AFX_MSG_MAP(CShowBitmapChildWindowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowView drawing

void CShowBitmapChildWindowView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	
	RECT rect;

	GetClientRect( &rect );		/////取得窗口大小

	HBITMAP hNewBitmap = NULL;

	hNewBitmap = ( HBITMAP ) ::LoadImage( NULL,
										  "E:\\01.BMP",
										  IMAGE_BITMAP,
										  rect.right,
										  rect.bottom,
										  LR_LOADFROMFILE );

	
	HDC	hdc = CreateCompatibleDC( pDC->m_hDC );

	HBITMAP hOldBitmap = NULL;

	hOldBitmap = ( HBITMAP ) SelectObject( hdc, hNewBitmap );

	BitBlt( pDC->m_hDC,
			0,
			0,
			rect.right,
			rect.bottom,
			hdc,
			0,
			0,
			SRCCOPY );

	SelectObject( hdc, hOldBitmap );
}

/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowView diagnostics

#ifdef _DEBUG
void CShowBitmapChildWindowView::AssertValid() const
{
	CView::AssertValid();
}

void CShowBitmapChildWindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowView message handlers
