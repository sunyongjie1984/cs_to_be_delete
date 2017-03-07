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
// fco_campos@tutopia.com													 //
//-----------------------------------------------------------------------//


#if !defined(AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_)
#define AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabWnd window

#include "GuiLib.h"
#include "GuiDrawlayer.h"
#include "GuiBasetab.h"
//#include "NewMenu.h"

//*********************************************************
class GUILIBDLLEXPORT  CGuiTabWnd : public CWnd
{
// Construction

public:

	//************************************************
	CGuiTabWnd();
	virtual ~CGuiTabWnd();
	//************************************************

	enum Style{S3D=0,FLAT=1,SHADOW=2};
	enum AlingTab{ALN_TOP=0,ALN_BOTTOM=1};
	enum TypeTab{TYPE_NORMAL=0,TYPE_MDI=1};

public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

public:
	//***********************************************************************	
	void	SetStyle(Style estyle);
	void    SetTypeTab(TypeTab Type=TYPE_NORMAL);
	void	virtual Drawtabs(CDC* dc);
	void	Addtab(CWnd* pParent,CString lpMsg,UINT uIcon);
	void	SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void	RecalLayout();
	virtual void AjustTabs();
	void    SetCurtab(int m_numtab);
	int     GetCurtab();
	void    DeleteTab(int m_numTab);
	void	ShowTitle(CString m_Caption);
	CWnd*   GetActiveWnd () const;
	CWnd*   GetNumWnd(int m_numtab)  const;
	int     GetCount(){return m_Numtabs;}
	void	SetActualTitle(BOOL bActual);
	void    SetALingTabs(AlingTab alnTab);
	BOOL	FindItem(HWND hWnd);
	int		FindHwnd(HWND hWnd);
	void    UpdateCaption(CWnd* pWnd,CString m_Title);
	//***********************************************************************
	CGuiTab* GetCurTabWnd(CWnd *pParent);
	void SetCurTabWnd(CGuiTab *ptab);
	
protected:
	TypeTab			m_TypeTab;
	BOOL			m_ActualTitle;
	CPtrArray		m_pArray;
	CSize			m_sizeImag;
	int				m_Numtabs;
	int				m_iMinValRec;
	int				m_ActualVar;
	int				m_iSelectTab;
	CRect			m_rectCliente;
	CRect			m_rectTab;
	CToolTipCtrl	CToolTip;
	CImageList		Image;
	CFont			m_cfont;
	BOOL			m_style;
	GuiDrawLayer	m_wd;
	CWnd*			pParent;
	AlingTab		m_alnTab;

	CGuiTab* m_tab;
//	CNewMenu *m_nmenu;
protected:

	//{{AFX_MSG(CGuiTabWnd)
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnPaint();
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnSysColorChange( );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	int GetCurWnd(CWnd* pw);
	afx_msg void OnDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_)
