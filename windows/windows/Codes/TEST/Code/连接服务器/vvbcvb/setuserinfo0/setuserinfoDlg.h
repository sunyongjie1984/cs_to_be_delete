// setuserinfoDlg.h : header file
//

#if !defined(AFX_SETUSERINFODLG_H__E9EA210A_4EE7_44E3_9858_231E89761136__INCLUDED_)
#define AFX_SETUSERINFODLG_H__E9EA210A_4EE7_44E3_9858_231E89761136__INCLUDED_

#include "stdafx.h"


#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSetuserinfoDlg dialog

class CSetuserinfoDlg : public CDialog
{
// Construction
public:
	CSetuserinfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSetuserinfoDlg)
	enum { IDD = IDD_SETUSERINFO_DIALOG };
	CString	m_serverName;
	CString	m_userName;
	CString	m_scriptpath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetuserinfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSetuserinfoDlg)
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

#endif // !defined(AFX_SETUSERINFODLG_H__E9EA210A_4EE7_44E3_9858_231E89761136__INCLUDED_)
