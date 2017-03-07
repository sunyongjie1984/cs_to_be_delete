#if !defined(AFX_ABOUTTAB_H__D20E9E5B_017A_4FB1_B131_1A3962DAB486__INCLUDED_)
#define AFX_ABOUTTAB_H__D20E9E5B_017A_4FB1_B131_1A3962DAB486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutTab dialog

#include "TabPageSSL.h"
#include "ButtonSSL.h"

class CAboutTab : public CTabPageSSL
{
// Construction
public:
	CAboutTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutTab)
	enum { IDD = IDD_FORMVIEW };
	CButtonSSL	m_btnEmail;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutTab)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTTAB_H__D20E9E5B_017A_4FB1_B131_1A3962DAB486__INCLUDED_)
