// TestCreateThreadAndProcessDlg.h : header file
//

#if !defined(AFX_TESTCREATETHREADANDPROCESSDLG_H__F1704FD2_CFC4_4175_8562_A3CA53089ED1__INCLUDED_)
#define AFX_TESTCREATETHREADANDPROCESSDLG_H__F1704FD2_CFC4_4175_8562_A3CA53089ED1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestCreateThreadAndProcessDlg dialog

class CTestCreateThreadAndProcessDlg : public CDialog
{
// Construction
public:
	CTestCreateThreadAndProcessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestCreateThreadAndProcessDlg)
	enum { IDD = IDD_TESTCREATETHREADANDPROCESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCreateThreadAndProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestCreateThreadAndProcessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreateNewThread();
	afx_msg void OnCreateNewProcess();
	afx_msg void OnTryToLockTheMutex();
	afx_msg void OnReleaseMutex();
	afx_msg void OnTestCPUTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCREATETHREADANDPROCESSDLG_H__F1704FD2_CFC4_4175_8562_A3CA53089ED1__INCLUDED_)
