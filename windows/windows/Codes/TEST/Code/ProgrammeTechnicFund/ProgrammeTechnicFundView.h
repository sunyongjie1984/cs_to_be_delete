// ProgrammeTechnicFundView.h : interface of the CProgrammeTechnicFundView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAMMETECHNICFUNDVIEW_H__EC43644C_7AAC_45AC_895A_9AE6E9C3A85E__INCLUDED_)
#define AFX_PROGRAMMETECHNICFUNDVIEW_H__EC43644C_7AAC_45AC_895A_9AE6E9C3A85E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SortListCtrl.h"

class CProgrammeTechnicFundView : public CView
{
public:
	CSortListCtrl m_SortListCtrl;
	
public:
	VOID InsertListColumn( CSortListCtrl * sortListCtrl );

protected: // create from serialization only
	CProgrammeTechnicFundView();
	DECLARE_DYNCREATE(CProgrammeTechnicFundView)

// Attributes
public:
	CProgrammeTechnicFundDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgrammeTechnicFundView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgrammeTechnicFundView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProgrammeTechnicFundView)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ProgrammeTechnicFundView.cpp
inline CProgrammeTechnicFundDoc* CProgrammeTechnicFundView::GetDocument()
   { return (CProgrammeTechnicFundDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAMMETECHNICFUNDVIEW_H__EC43644C_7AAC_45AC_895A_9AE6E9C3A85E__INCLUDED_)
