#if !defined(AFX_INFOVIEW_H__8858BB76_EDCC_4DC6_B745_2243BD2BBAEB__INCLUDED_)
#define AFX_INFOVIEW_H__8858BB76_EDCC_4DC6_B745_2243BD2BBAEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoView view

class CInfoView : public CEditView
{
protected:
	CInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInfoView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_NewFont;
	virtual ~CInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOVIEW_H__8858BB76_EDCC_4DC6_B745_2243BD2BBAEB__INCLUDED_)
