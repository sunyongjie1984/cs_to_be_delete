#if !defined(AFX_MYCARD_H__24AD9907_F7ED_4E0F_B93B_A7614420464C__INCLUDED_)
#define AFX_MYCARD_H__24AD9907_F7ED_4E0F_B93B_A7614420464C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyCard window

class CMyCard : public CStatic
{
// Construction
public:
	CMyCard();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCard)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint pointT;
	BOOL bOn;
	BOOL bDown;
	virtual ~CMyCard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyCard)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCARD_H__24AD9907_F7ED_4E0F_B93B_A7614420464C__INCLUDED_)
