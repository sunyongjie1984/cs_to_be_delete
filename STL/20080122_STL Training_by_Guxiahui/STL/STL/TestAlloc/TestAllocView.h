// TestAllocView.h : interface of the CTestAllocView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTALLOCVIEW_H__2442AD43_DA93_4571_B002_7CF31673076F__INCLUDED_)
#define AFX_TESTALLOCVIEW_H__2442AD43_DA93_4571_B002_7CF31673076F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TestAllocDoc.h"
class CTestAllocView : public CScrollView
{
protected: // create from serialization only
	CTestAllocView();
	DECLARE_DYNCREATE(CTestAllocView)

// Attributes
public:
	CTestAllocDoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAllocView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestAllocView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	 void OnSetMalloc(WPARAM wParam,LPARAM lParam);
// Generated message map functions
protected:
	//{{AFX_MSG(CTestAllocView)
	afx_msg void OnPOOLMENU();
	afx_msg void OnMENUMACRO();
	afx_msg void OnMENUNORMAL();
	afx_msg void OnMENUPOOLMACRO();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nMemUsed;
	int m_naHead[500];
	int m_nPos;
};

#ifndef _DEBUG  // debug version in TestAllocView.cpp
inline CTestAllocDoc* CTestAllocView::GetDocument()
   { return (CTestAllocDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTALLOCVIEW_H__2442AD43_DA93_4571_B002_7CF31673076F__INCLUDED_)
