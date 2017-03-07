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

#if !defined(AFX_GUIVIEW_H__31B23C60_1C0D_4F04_AA25_AA6D8FE19985__INCLUDED_)
#define AFX_GUIVIEW_H__31B23C60_1C0D_4F04_AA25_AA6D8FE19985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiView view
#include "guilib.h"

class GUILIBDLLEXPORT CGuiView : public CView
{
protected:
	CGuiView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGuiView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGuiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiView)
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIVIEW_H__31B23C60_1C0D_4F04_AA25_AA6D8FE19985__INCLUDED_)
