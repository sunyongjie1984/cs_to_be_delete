// usingdllDlg.h : header file
//

#if !defined(AFX_USINGDLLDLG_H__D61FFD8C_E536_4EBF_AB40_ACF77AFFF947__INCLUDED_)
#define AFX_USINGDLLDLG_H__D61FFD8C_E536_4EBF_AB40_ACF77AFFF947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUsingdllDlg dialog

class CUsingdllDlg : public CDialog
{
// Construction
public:
	CUsingdllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUsingdllDlg)
	enum { IDD = IDD_USINGDLL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingdllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUsingdllDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGDLLDLG_H__D61FFD8C_E536_4EBF_AB40_ACF77AFFF947__INCLUDED_)
