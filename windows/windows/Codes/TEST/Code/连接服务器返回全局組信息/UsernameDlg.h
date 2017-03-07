#if !defined(AFX_USERNAMEDLG_H__DE6453AC_C19C_4B4B_A711_F54C228E2A14__INCLUDED_)
#define AFX_USERNAMEDLG_H__DE6453AC_C19C_4B4B_A711_F54C228E2A14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsernameDlg.h : header file
//
#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>
#include "Lmaccess.h"
#pragma comment(lib,"ActiveDS.lib")

#include "StationscriptDlg.h"
#include "netDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CUsernameDlg dialog

class CUsernameDlg : public CDialog
{
// Construction
public:
	CUsernameDlg(CString &csName, CWnd* pParent = NULL);   // standard constructor

	CString m_serverName;	
// Dialog Data
	//{{AFX_DATA(CUsernameDlg)
	enum { IDD = IDD_DIALOG };
	CListCtrl	m_listuserinfo;
	CString	m_username;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsernameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUsernameDlg)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERNAMEDLG_H__DE6453AC_C19C_4B4B_A711_F54C228E2A14__INCLUDED_)
