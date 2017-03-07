#if !defined(AFX_ONLINEBAR_H__EEF848ED_E0D7_4254_BA38_52204982BFBC__INCLUDED_)
#define AFX_ONLINEBAR_H__EEF848ED_E0D7_4254_BA38_52204982BFBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnlineBar.h : header file
//
#include "OnlineList.h"

/////////////////////////////////////////////////////////////////////////////
// COnlineBar dialog

class COnlineBar : public CDialogBar
{
// Construction
public:
	COnlineList* m_ListCtrl;
	COnlineBar();   // standard constructor
	~COnlineBar();
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COnlineBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddExStyle(DWORD dwNewStyle);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONLINEBAR_H__EEF848ED_E0D7_4254_BA38_52204982BFBC__INCLUDED_)
