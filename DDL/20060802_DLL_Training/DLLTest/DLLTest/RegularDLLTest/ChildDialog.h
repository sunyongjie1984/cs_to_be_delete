#if !defined(AFX_CHILDDIALOG_H__4C695981_2A8F_4D09_858D_4548DBEB0643__INCLUDED_)
#define AFX_CHILDDIALOG_H__4C695981_2A8F_4D09_858D_4548DBEB0643__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildDialog.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CChildDialog dialog

class CChildDialog : public CDialog
{
// Construction
public:
	CChildDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChildDialog)
	enum { IDD = IDD_CHILD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChildDialog)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDDIALOG_H__4C695981_2A8F_4D09_858D_4548DBEB0643__INCLUDED_)
