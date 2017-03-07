// printerDlg.h : header file
//

#if !defined(AFX_PRINTERDLG_H__51C7D140_0F72_4DEA_AE62_D6EB18643AED__INCLUDED_)
#define AFX_PRINTERDLG_H__51C7D140_0F72_4DEA_AE62_D6EB18643AED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPrinterDlg dialog
class CAboutDlg;
class CPrinterDlg : public CDialog
{
// Construction
public:
	CPrinterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPrinterDlg)
	enum { IDD = IDD_PRINTER_DIALOG };
	CString	m_csPath;
	CString	m_csUser;
	CString	m_csPass;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CAboutDlg* m_pAboutDlg;

	// Generated message map functions
	//{{AFX_MSG(CPrinterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnGetPtInfo();
	afx_msg void OnAdd();
	afx_msg void OnAddPrinter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERDLG_H__51C7D140_0F72_4DEA_AE62_D6EB18643AED__INCLUDED_)
