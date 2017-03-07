// ProgrammeTechnicAccumulateView.h : interface of the CProgrammeTechnicAccumulateView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAMMETECHNICACCUMULATEVIEW_H__C637AD1A_2E20_4129_86ED_2B9D88CC65DF__INCLUDED_)
#define AFX_PROGRAMMETECHNICACCUMULATEVIEW_H__C637AD1A_2E20_4129_86ED_2B9D88CC65DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CProgrammeTechnicAccumulateView : public CView
{
protected: // create from serialization only
	CProgrammeTechnicAccumulateView();
	DECLARE_DYNCREATE(CProgrammeTechnicAccumulateView)

// Attributes
public:
	CProgrammeTechnicAccumulateDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgrammeTechnicAccumulateView)
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
	virtual ~CProgrammeTechnicAccumulateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProgrammeTechnicAccumulateView)
	afx_msg void OnMenuGraphicsProgramme();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ProgrammeTechnicAccumulateView.cpp
inline CProgrammeTechnicAccumulateDoc* CProgrammeTechnicAccumulateView::GetDocument()
   { return (CProgrammeTechnicAccumulateDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAMMETECHNICACCUMULATEVIEW_H__C637AD1A_2E20_4129_86ED_2B9D88CC65DF__INCLUDED_)
