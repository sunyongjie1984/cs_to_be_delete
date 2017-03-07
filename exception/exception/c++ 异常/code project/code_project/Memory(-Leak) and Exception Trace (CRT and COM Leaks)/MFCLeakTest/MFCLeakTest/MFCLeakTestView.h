// MFCLeakTestView.h : interface of the CMFCLeakTestView class
//


#pragma once


class CMFCLeakTestView : public CView
{
protected: // create from serialization only
	CMFCLeakTestView();
	DECLARE_DYNCREATE(CMFCLeakTestView)

// Attributes
public:
	CMFCLeakTestDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCLeakTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCLeakTestView.cpp
inline CMFCLeakTestDoc* CMFCLeakTestView::GetDocument() const
   { return reinterpret_cast<CMFCLeakTestDoc*>(m_pDocument); }
#endif

