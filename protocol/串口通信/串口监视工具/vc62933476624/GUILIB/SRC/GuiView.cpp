//-----------------------------------------------------------------------//
// This is a part of the GuiLib MFC Extention.							 //	
// Autor  :  Ernesto garcia												//
// (C) 2002 <www.beyondata.com> All rights reserved						//
// This code is provided "as is", with absolutely no warranty expressed  //
// or implied. Any use is at your own risk.								 //		
// You must obtain the author's consent before you can include this code //
// in a software library.												 //
// If the source code in  this file is used in any application			 //
// then acknowledgement must be made to the author of this program		 //	
//-----------------------------------------------------------------------//

#include "stdafx.h"
#include "..\header\guilib.h"
#include "..\header\GuiView.h"
#include "..\header\newmenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiView

IMPLEMENT_DYNCREATE(CGuiView, CView)

CGuiView::CGuiView()
{
}

CGuiView::~CGuiView()
{
}


BEGIN_MESSAGE_MAP(CGuiView, CView)
	//{{AFX_MSG_MAP(CGuiView)
	ON_WM_INITMENUPOPUP()
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiView drawing

void CGuiView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CGuiView diagnostics

#ifdef _DEBUG
void CGuiView::AssertValid() const
{
	CView::AssertValid();
}

void CGuiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGuiView message handlers

void CGuiView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
    CView::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
    CNewMenu::OnInitMenuPopup(m_hWnd,pPopupMenu, nIndex, bSysMenu);
}

void CGuiView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
    if(!CNewMenu::OnMeasureItem(GetCurrentMessage()))
    {
      CView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
    }
}


LRESULT CGuiView::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
    LRESULT lresult;
    if( DYNAMIC_DOWNCAST(CNewMenu,pMenu) )
      lresult=CNewMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
    else
      lresult=CView::OnMenuChar(nChar, nFlags, pMenu);
    return lresult;
}
