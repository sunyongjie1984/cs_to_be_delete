// MyCard.cpp : implementation file
//

#include "stdafx.h"
#include "Spar.h"
#include "MyCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCard

CMyCard::CMyCard()
{
	bDown = FALSE;
	bOn = FALSE;
}

CMyCard::~CMyCard()
{
}


BEGIN_MESSAGE_MAP(CMyCard, CStatic)
	//{{AFX_MSG_MAP(CMyCard)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCard message handlers



void CMyCard::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->GetCaretPos();
	CStatic::OnLButtonDblClk(nFlags, point);
}



UINT CMyCard::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	return CStatic::OnNcHitTest(point);
}







void CMyCard::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
		bDown = TRUE;
		SetCapture();
		pointT = point;

		
	CStatic::OnLButtonDown(nFlags, point);
}

void CMyCard::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(bDown)
	{
		CPoint p;
		GetCursorPos(&p);
		GetParent() ->ScreenToClient(&p);
		p -= pointT;

		CRect rect(p.x,p.y,p.x+70,p.y+90);
		MoveWindow(rect,TRUE);
	
		Invalidate(FALSE);
		bDown = FALSE;
	
		ReleaseCapture();
	}
	CStatic::OnLButtonUp(nFlags, point);
}

void CMyCard::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(bDown)
	{	
		CPoint p;
		GetCursorPos(&p);
		GetParent() ->ScreenToClient(&p);
		p -= pointT;
		CRect rect(p.x,p.y,p.x+70,p.y+90);
		MoveWindow(rect,TRUE);
		Invalidate(FALSE);
	}
	TRACE("(%d, %d)",point.x,point.y);

	CStatic::OnMouseMove(nFlags, point);
}
