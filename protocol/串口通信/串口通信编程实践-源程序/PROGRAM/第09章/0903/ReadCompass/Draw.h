#if !defined(AFX_DRAW_H__9C656872_5508_42FF_B1BD_C99C1143E019__INCLUDED_)
#define AFX_DRAW_H__9C656872_5508_42FF_B1BD_C99C1143E019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Draw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDraw view

class CDraw : public CView
{
protected:
	CDraw();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDraw)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDraw)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDraw();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDraw)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAW_H__9C656872_5508_42FF_B1BD_C99C1143E019__INCLUDED_)
