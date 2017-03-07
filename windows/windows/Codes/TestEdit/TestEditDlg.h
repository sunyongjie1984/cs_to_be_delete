// TestEditDlg.h : header file
//

#if !defined(AFX_TESTEDITDLG_H__0EA15B0A_B9F2_432C_88A7_B628D765C465__INCLUDED_)
#define AFX_TESTEDITDLG_H__0EA15B0A_B9F2_432C_88A7_B628D765C465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestEditDlg dialog

class CTestEditDlg : public CDialog
{
// Construction
public:
	CTestEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestEditDlg)
	enum { IDD = IDD_TESTEDIT_DIALOG };
	int		m_nTestSize;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTEDITDLG_H__0EA15B0A_B9F2_432C_88A7_B628D765C465__INCLUDED_)
