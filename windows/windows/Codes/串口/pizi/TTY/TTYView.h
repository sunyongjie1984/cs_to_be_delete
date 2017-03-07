// TTYView.h : interface of the CTTYView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTYVIEW_H__924288D0_EDB0_48F0_810F_28332DF7A34A__INCLUDED_)
#define AFX_TTYVIEW_H__924288D0_EDB0_48F0_810F_28332DF7A34A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CTTYView : public CEditView
{
protected: // create from serialization only
	CTTYView();
	DECLARE_DYNCREATE(CTTYView)

// Attributes
public:
	CTTYDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYView)
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
	virtual ~CTTYView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTTYView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnCommNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TTYView.cpp
inline CTTYDoc* CTTYView::GetDocument()
   { return (CTTYDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTYVIEW_H__924288D0_EDB0_48F0_810F_28332DF7A34A__INCLUDED_)
