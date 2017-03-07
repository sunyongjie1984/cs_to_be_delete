// ThreadTestDlg.h : header file
//

#if !defined(AFX_THREADTESTDLG_H__36912D33_BF5B_4BBE_8470_6360C1E295E9__INCLUDED_)
#define AFX_THREADTESTDLG_H__36912D33_BF5B_4BBE_8470_6360C1E295E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CThreadTestDlg dialog

class CThreadTestDlg : public CDialog
{
// Construction
public:
	CThreadTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CThreadTestDlg)
	enum { IDD = IDD_THREADTEST_DIALOG };
	CButton	m_btnB;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:

    void DoSomething();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CThreadTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest1();
	afx_msg void OnTest2();
	afx_msg void OnTest3();
	afx_msg void OnTest4();
	afx_msg void OnButtonB();
	afx_msg void OnButtonA1();
	afx_msg void OnButtonA2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CWinThread* m_pThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREADTESTDLG_H__36912D33_BF5B_4BBE_8470_6360C1E295E9__INCLUDED_)
