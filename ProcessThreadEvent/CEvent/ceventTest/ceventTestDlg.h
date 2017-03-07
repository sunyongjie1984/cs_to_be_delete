// ceventTestDlg.h : header file
//

#if !defined(AFX_CEVENTTESTDLG_H__5392B160_5F40_4C8F_BD92_B072FD16A5CE__INCLUDED_)
#define AFX_CEVENTTESTDLG_H__5392B160_5F40_4C8F_BD92_B072FD16A5CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCeventTestDlg dialog
#include "afxmt.h"

class CCeventTestDlg : public CDialog
{
// Construction
public:
	CCeventTestDlg(CWnd* pParent = NULL);	// standard constructor
	HANDLE  m_hThread;

// Dialog Data
	//{{AFX_DATA(CCeventTestDlg)
	enum { IDD = IDD_CEVENTTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCeventTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCeventTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEVENTTESTDLG_H__5392B160_5F40_4C8F_BD92_B072FD16A5CE__INCLUDED_)
