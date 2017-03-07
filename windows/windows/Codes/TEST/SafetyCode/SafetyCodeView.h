// SafetyCodeView.h : interface of the CSafetyCodeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAFETYCODEVIEW_H__EA17A923_A589_4E7B_8968_6133BE337CE7__INCLUDED_)
#define AFX_SAFETYCODEVIEW_H__EA17A923_A589_4E7B_8968_6133BE337CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSafetyCodeView : public CView
{
protected: // create from serialization only
	CSafetyCodeView();
	DECLARE_DYNCREATE(CSafetyCodeView)

// Attributes
public:
	CSafetyCodeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSafetyCodeView)
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
	virtual ~CSafetyCodeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSafetyCodeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SafetyCodeView.cpp
inline CSafetyCodeDoc* CSafetyCodeView::GetDocument()
   { return (CSafetyCodeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAFETYCODEVIEW_H__EA17A923_A589_4E7B_8968_6133BE337CE7__INCLUDED_)
