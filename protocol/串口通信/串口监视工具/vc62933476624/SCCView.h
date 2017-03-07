#if !defined(AFX_SCCVIEW_H__DF699BBF_7A24_424F_BBD9_1E9E76410BC4__INCLUDED_)
#define AFX_SCCVIEW_H__DF699BBF_7A24_424F_BBD9_1E9E76410BC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SCCView.h : header file
//
#include "XRichEditView.h"
/////////////////////////////////////////////////////////////////////////////
// CSCCView view

class CSCCView : public CXRichEditView
{
protected:
	CSCCView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSCCView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCCView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSCCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSCCView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCCVIEW_H__DF699BBF_7A24_424F_BBD9_1E9E76410BC4__INCLUDED_)
