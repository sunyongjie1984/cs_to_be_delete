// SenderView.h : interface of the CSenderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENDERVIEW_H__28F3BF50_FDE3_45D0_A513_E1556BC8E1E0__INCLUDED_)
#define AFX_SENDERVIEW_H__28F3BF50_FDE3_45D0_A513_E1556BC8E1E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSenderView : public CView
{
protected: // create from serialization only
	CSenderView();
	DECLARE_DYNCREATE(CSenderView)

// Attributes
public:
	CSenderDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSenderView)
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
	virtual ~CSenderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSenderView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SenderView.cpp
inline CSenderDoc* CSenderView::GetDocument()
   { return (CSenderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDERVIEW_H__28F3BF50_FDE3_45D0_A513_E1556BC8E1E0__INCLUDED_)
