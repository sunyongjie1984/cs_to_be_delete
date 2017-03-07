//-----------------------------------------------------------------------//
// This is a part of the GuiLib MFC Extention.							 //	
// Autor  :  Francisco Campos											 //
// (C) 2002 Francisco Campos <www.beyondata.com> All rights reserved     //
// This code is provided "as is", with absolutely no warranty expressed  //
// or implied. Any use is at your own risk.								 //		
// You must obtain the author's consent before you can include this code //
// in a software library.												 //
// If the source code in  this file is used in any application			 //
// then acknowledgement must be made to the author of this program		 //	
// fco_campos@tutopia.com												 //
//-----------------------------------------------------------------------//
#pragma once

#include <afxpriv.h>
// CGuiMiniFrame frame
#include "GuiLib.h" 
#include "GuiMiniFrame.h" 
#include "GuiDrawLayer.h" 

class GUILIBDLLEXPORT CGuiMiniFrame : public CMiniDockFrameWnd
{
	DECLARE_DYNCREATE(CGuiMiniFrame)

protected:
	BOOL IsGuiControlBar;
	CGuiControlBarButton m_btn;
	CRect m_rcCloseBtn;
	int		m_stateBtn;
	BOOL IsMenuBar;
public:
// Construction
	CGuiMiniFrame();
	

// Operations
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);
	void DrawGripper(CDC* pDC,CRect* rc);
	void TypeBar();
	CWnd* GetChildWnd();
// Implementation
public:
//	CDockBar m_wndDockBar;

	//{{AFX_MSG(CMiniFrameWnd)
	afx_msg void OnClose();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nHitTest, CPoint point);
	//}}AFX_MSG
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);

};


