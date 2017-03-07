// TestClientByImplicitLinkingDlg.h : header file
//

#if !defined(AFX_TESTCLIENTBYIMPLICITLINKINGDLG_H__18EE03E3_B2EA_4D46_9547_777DD8D0BA12__INCLUDED_)
#define AFX_TESTCLIENTBYIMPLICITLINKINGDLG_H__18EE03E3_B2EA_4D46_9547_777DD8D0BA12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestClientByImplicitLinkingDlg dialog

class CTestClientByImplicitLinkingDlg : public CDialog
{
// Construction
public:
	CTestClientByImplicitLinkingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestClientByImplicitLinkingDlg)
	enum { IDD = IDD_TESTCLIENTBYIMPLICITLINKING_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestClientByImplicitLinkingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestClientByImplicitLinkingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCLIENTBYIMPLICITLINKINGDLG_H__18EE03E3_B2EA_4D46_9547_777DD8D0BA12__INCLUDED_)
