// fffffffDlg.h : header file
//

#if !defined(AFX_FFFFFFFDLG_H__6F162C0D_45F5_453C_999A_35C8564E8185__INCLUDED_)
#define AFX_FFFFFFFDLG_H__6F162C0D_45F5_453C_999A_35C8564E8185__INCLUDED_

#ifndef UNICODE
#define UNICODE
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>
#include "Lmaccess.h"
#pragma comment(lib,"ActiveDS.lib")

/////////////////////////////////////////////////////////////////////////////
// CFffffffDlg dialog

class CFffffffDlg : public CDialog
{
// Construction
public:
	int b;
	CFffffffDlg(CWnd* pParent = NULL);	// standard constructor
	LPUSER_INFO_0 pBuf;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel;
	DWORD dwPrefMaxLen;
	DWORD dwEntriesRead;
	DWORD dwTotalEntries;
	DWORD dwResumeHandle;
	DWORD i;
	DWORD dwTotalCount;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName;
//	LPTSTR csFmtcompare;

// Dialog Data
	//{{AFX_DATA(CFffffffDlg)
	enum { IDD = IDD_FFFFFFF_DIALOG };
	CListCtrl	m_listuserinfo;
	CListBox	m_listbox;
	int		m_value1;
	CString	m_findaccounts;
	CString	m_servername;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFffffffDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFffffffDlg)
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

#endif // !defined(AFX_FFFFFFFDLG_H__6F162C0D_45F5_453C_999A_35C8564E8185__INCLUDED_)
