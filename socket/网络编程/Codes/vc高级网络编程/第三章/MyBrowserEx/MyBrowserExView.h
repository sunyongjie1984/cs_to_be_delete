// MyBrowserExView.h : interface of the CMyBrowserExView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYBROWSEREXVIEW_H__C756DDD7_BFAF_45D4_B8DE_C025013EACB7__INCLUDED_)
#define AFX_MYBROWSEREXVIEW_H__C756DDD7_BFAF_45D4_B8DE_C025013EACB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ithread.h"

class CMyBrowserExView : public CEditView
{
protected: // create from serialization only
	CMyBrowserExView();
	DECLARE_DYNCREATE(CMyBrowserExView)
    
// Attributes
public:
	CMyBrowserExDoc* GetDocument();
    CString m_strServer ;
    CString m_strPath ;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBrowserExView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	afx_msg LRESULT OnReadFileCompleted(WPARAM wParam, LPARAM lParam) ;
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Connect();
	virtual ~CMyBrowserExView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
   CInternetThread m_InternetThread;
// Generated message map functions
protected:
	//{{AFX_MSG(CMyBrowserExView)
	afx_msg void OnDefault();
	afx_msg void OnUpdateDefault(CCmdUI* pCmdUI);
	afx_msg void OnProxy();
	afx_msg void OnUpdateProxy(CCmdUI* pCmdUI);
	afx_msg void OnHost();
	afx_msg void OnUpdateHost(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnNewAddress();
	afx_msg void OnNewAddressEnter();
	DECLARE_MESSAGE_MAP()
private:
	CString m_strAddress;
	int m_dwAccessType;

};

#ifndef _DEBUG  // debug version in MyBrowserExView.cpp
inline CMyBrowserExDoc* CMyBrowserExView::GetDocument()
   { return (CMyBrowserExDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBROWSEREXVIEW_H__C756DDD7_BFAF_45D4_B8DE_C025013EACB7__INCLUDED_)
