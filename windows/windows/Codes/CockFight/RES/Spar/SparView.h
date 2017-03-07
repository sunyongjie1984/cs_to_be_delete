// SparView.h : interface of the CSparView class
//
#include "MyCard.h"
#include "MyButton.h"
#include "MyStatic.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPARVIEW_H__0FF3F7FA_04AA_43B5_9059_86DE2E6B71F3__INCLUDED_)
#define AFX_SPARVIEW_H__0FF3F7FA_04AA_43B5_9059_86DE2E6B71F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define ID_CARD 20000
class CSparView : public CView
{
protected: // create from serialization only
	CSparView();
	DECLARE_DYNCREATE(CSparView)

// Attributes
public:
	CSparDoc* GetDocument();

// Operations
public:
		CBitmap bmp;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSparView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CMyStatic myStatic;
	CMyButton myButton;
	CBitmap bmpCard;
	CMyCard myCard;
	virtual ~CSparView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSparView)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SparView.cpp
inline CSparDoc* CSparView::GetDocument()
   { return (CSparDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPARVIEW_H__0FF3F7FA_04AA_43B5_9059_86DE2E6B71F3__INCLUDED_)
