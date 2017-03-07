#if !defined(AFX_SHOWBITMAPCHILDWINDOWFRAME_H__0D49ABE8_5719_479E_AE04_9071B8F8A578__INCLUDED_)
#define AFX_SHOWBITMAPCHILDWINDOWFRAME_H__0D49ABE8_5719_479E_AE04_9071B8F8A578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowBitmapChildWindowFrame.h : header file
//
#include "ShowBitmapChildWindowView.h"
/////////////////////////////////////////////////////////////////////////////
// CShowBitmapChildWindowFrame frame

class CShowBitmapChildWindowFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CShowBitmapChildWindowFrame)

public:
	CShowBitmapChildWindowView * m_pShowBmpView;
	
public:
	CShowBitmapChildWindowFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	int		CreateShowBmpView();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowBitmapChildWindowFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowBitmapChildWindowFrame();

	// Generated message map functions
	//{{AFX_MSG(CShowBitmapChildWindowFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWBITMAPCHILDWINDOWFRAME_H__0D49ABE8_5719_479E_AE04_9071B8F8A578__INCLUDED_)
