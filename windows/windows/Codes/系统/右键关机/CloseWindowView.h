// CloseWindowView.h : interface of the CCloseWindowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLOSEWINDOWVIEW_H__C9590E7C_4C63_47BF_9365_CA52D26CEFCB__INCLUDED_)
#define AFX_CLOSEWINDOWVIEW_H__C9590E7C_4C63_47BF_9365_CA52D26CEFCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCloseWindowView : public CView
{
protected: // create from serialization only
	CCloseWindowView();
	DECLARE_DYNCREATE(CCloseWindowView)

// Attributes
public:
	CCloseWindowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseWindowView)
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
	void CloseWindow();
	virtual ~CCloseWindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCloseWindowView)
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CloseWindowView.cpp
inline CCloseWindowDoc* CCloseWindowView::GetDocument()
   { return (CCloseWindowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEWINDOWVIEW_H__C9590E7C_4C63_47BF_9365_CA52D26CEFCB__INCLUDED_)
