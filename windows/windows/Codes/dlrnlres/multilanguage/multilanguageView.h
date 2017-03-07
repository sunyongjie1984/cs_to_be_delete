// multilanguageView.h : interface of the CMultilanguageView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTILANGUAGEVIEW_H__D942F872_B2AF_43DA_A10F_8D1142D66F39__INCLUDED_)
#define AFX_MULTILANGUAGEVIEW_H__D942F872_B2AF_43DA_A10F_8D1142D66F39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMultilanguageView : public CView
{
protected: // create from serialization only
	CMultilanguageView();
	DECLARE_DYNCREATE(CMultilanguageView)

// Attributes
public:
	CMultilanguageDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultilanguageView)
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
	virtual ~CMultilanguageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultilanguageView)
	afx_msg void OnMenuTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in multilanguageView.cpp
inline CMultilanguageDoc* CMultilanguageView::GetDocument()
   { return (CMultilanguageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILANGUAGEVIEW_H__D942F872_B2AF_43DA_A10F_8D1142D66F39__INCLUDED_)
