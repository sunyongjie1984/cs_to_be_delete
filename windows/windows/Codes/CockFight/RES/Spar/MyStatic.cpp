// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "Spar.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers

void CMyStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CARD);
	SetBitmap(bmp);
	// Do not call CStatic::OnPaint() for painting messages
}

UINT CMyStatic::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CStatic::OnNcHitTest(point);
}
