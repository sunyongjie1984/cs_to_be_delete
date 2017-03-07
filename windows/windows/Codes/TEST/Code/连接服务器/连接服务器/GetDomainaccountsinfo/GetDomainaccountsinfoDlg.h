// GetDomainaccountsinfoDlg.h : header file
//

#if !defined(AFX_GETDOMAINACCOUNTSINFODLG_H__6827975B_3451_4E3B_A5B0_BC35A34B789A__INCLUDED_)
#define AFX_GETDOMAINACCOUNTSINFODLG_H__6827975B_3451_4E3B_A5B0_BC35A34B789A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GetDomainAccountsInfo1.h"
/////////////////////////////////////////////////////////////////////////////
// CGetDomainaccountsinfoDlg dialog

class CGetDomainaccountsinfoDlg : public CDialog
{
// Construction
public:
	CGetDomainaccountsinfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetDomainaccountsinfoDlg)
	enum { IDD = IDD_GETDOMAINACCOUNTSINFO_DIALOG };
	CListCtrl	m_usersinfo;
	CString	m_edit;
	CString	m_editp;
	CString	m_editu;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetDomainaccountsinfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetDomainaccountsinfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETDOMAINACCOUNTSINFODLG_H__6827975B_3451_4E3B_A5B0_BC35A34B789A__INCLUDED_)
