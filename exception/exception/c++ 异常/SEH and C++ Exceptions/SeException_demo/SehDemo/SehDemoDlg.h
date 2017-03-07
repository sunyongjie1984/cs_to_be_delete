// SehDemoDlg.h : header file
//

#if !defined(AFX_SEHDEMODLG_H__5E0D0699_113F_11D3_AFC2_0080ADB99E81__INCLUDED_)
#define AFX_SEHDEMODLG_H__5E0D0699_113F_11D3_AFC2_0080ADB99E81__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSehDemoDlg dialog

class CSehDemoDlg : public CDialog
{
// Construction
public:
	CSehDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSehDemoDlg)
	enum { IDD = IDD_SEHDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSehDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSehDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreateException();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEHDEMODLG_H__5E0D0699_113F_11D3_AFC2_0080ADB99E81__INCLUDED_)
