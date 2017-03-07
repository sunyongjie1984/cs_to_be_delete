// NewProcessDlg.h : header file
//

#if !defined(AFX_NEWPROCESSDLG_H__1C6EAA7D_01BF_41DA_A84A_0C8FE0BAF434__INCLUDED_)
#define AFX_NEWPROCESSDLG_H__1C6EAA7D_01BF_41DA_A84A_0C8FE0BAF434__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNewProcessDlg dialog

class CNewProcessDlg : public CDialog
{
// Construction
public:
	CNewProcessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNewProcessDlg)
	enum { IDD = IDD_NEWPROCESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNewProcessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLockMutex();
	afx_msg void OnReleaseMutex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROCESSDLG_H__1C6EAA7D_01BF_41DA_A84A_0C8FE0BAF434__INCLUDED_)
