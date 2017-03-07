//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_TESTDIALOG_H__C19ABB71_F3CB_4DAB_87B2_B712D87D0C87__INCLUDED_)
#define AFX_TESTDIALOG_H__C19ABB71_F3CB_4DAB_87B2_B712D87D0C87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog

class CTestDialog : public CDialog
{
// Construction
public:
	CTestDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDialog)
	enum { IDD = IDD_DIALOG_TEST };
	CEdit	m_Edit;
	CMSFlexGrid	m_Grid;
	CString	m_sEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDialog)
	afx_msg void OnClickMsflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIALOG_H__C19ABB71_F3CB_4DAB_87B2_B712D87D0C87__INCLUDED_)
