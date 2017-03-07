#if !defined(AFX_SETUPDLG_H__C10266B6_50F4_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_SETUPDLG_H__C10266B6_50F4_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUPADDR };
	CComboBox	m_ctrlType;
	CString	m_strPass;
	UINT	m_uPort;
	CString	m_strProxy;
	CString	m_strServer;
	CString	m_strUser;
	CString	m_strProxyPass;
	CString	m_strProxyUser;
	UINT	m_uProxPort;
	//}}AFX_DATA

	UINT    m_uType;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProxytype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__C10266B6_50F4_11D5_B587_00E04C39B036__INCLUDED_)
