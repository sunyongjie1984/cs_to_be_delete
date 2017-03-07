// ReceiverView.h : interface of the CReceiverView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECEIVERVIEW_H__81573580_C30E_408E_B272_146D75E2319A__INCLUDED_)
#define AFX_RECEIVERVIEW_H__81573580_C30E_408E_B272_146D75E2319A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CReceiverView : public CView
{
protected: // create from serialization only
	CReceiverView();
	DECLARE_DYNCREATE(CReceiverView)

// Attributes
public:
	CReceiverDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReceiverView)
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
	virtual ~CReceiverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReceiverView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ReceiverView.cpp
inline CReceiverDoc* CReceiverView::GetDocument()
   { return (CReceiverDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVERVIEW_H__81573580_C30E_408E_B272_146D75E2319A__INCLUDED_)
