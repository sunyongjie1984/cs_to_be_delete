#if !defined(AFX_SHOWBITMAPCHILDWINDOWVIEW_H__5076EC8B_2204_4DFA_BDF0_BD1F2C88E860__INCLUDED_)
#define AFX_SHOWBITMAPCHILDWINDOWVIEW_H__5076EC8B_2204_4DFA_BDF0_BD1F2C88E860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowBitmapChildWindowView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowView view

class CShowBitmapChildWindowView : public CView
{
protected:
	CShowBitmapChildWindowView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CShowBitmapChildWindowView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowBitmapChildWindowView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CShowBitmapChildWindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CShowBitmapChildWindowView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWBITMAPCHILDWINDOWVIEW_H__5076EC8B_2204_4DFA_BDF0_BD1F2C88E860__INCLUDED_)
