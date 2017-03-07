// SDFDlg.h : header file
//

#if !defined(AFX_SDFDLG_H__A65319F6_B758_4BC0_987A_CF39F4FC1C30__INCLUDED_)
#define AFX_SDFDLG_H__A65319F6_B758_4BC0_987A_CF39F4FC1C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSDFDlg dialog

class CSDFDlg : public CDialog
{
// Construction
public:
	CSDFDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSDFDlg)
	enum { IDD = IDD_SDF_DIALOG };
	CButton	m_check;
	CString	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDFDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSDFDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDFDLG_H__A65319F6_B758_4BC0_987A_CF39F4FC1C30__INCLUDED_)
