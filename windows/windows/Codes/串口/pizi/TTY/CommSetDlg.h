#if !defined(AFX_COMMSETDLG_H__6BA42D30_18C7_4992_93C1_2E1DB58CD346__INCLUDED_)
#define AFX_COMMSETDLG_H__6BA42D30_18C7_4992_93C1_2E1DB58CD346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommSetDlg dialog

class CCommSetDlg : public CDialog
{
// Construction
public:
	CCommSetDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bConnected;
	
	int m_nParity;//校验位
	int m_nStopBits;//停止位
// Dialog Data
	//{{AFX_DATA(CCommSetDlg)
	enum { IDD = IDD_COMMDLG };
	CComboBox	m_ctrlStopBits;
	CComboBox	m_ctrlParity;
	CComboBox	m_ctrlPort;
	CComboBox	m_ctrlDataBits;
	CComboBox	m_ctrlBaud;
	CString	m_sBaud;
	CString	m_sDataBits;
	BOOL	m_bEcho;
	BOOL	m_bNewLine;
	CString	m_sPort;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommSetDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif 

// !defined(AFX_COMMSETDLG_H__6BA42D30_18C7_4992_93C1_2E1DB58CD346__INCLUDED_)
