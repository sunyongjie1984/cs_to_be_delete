#if !defined(AFX_CONFIGCONNECTORTESTDLG_H__F4650368_F431_47A5_A117_321A79C64E04__INCLUDED_)
#define AFX_CONFIGCONNECTORTESTDLG_H__F4650368_F431_47A5_A117_321A79C64E04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigConnectorTestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigConnectorTestDlg dialog

class CConfigConnectorTestDlg : public CDialog
{
// Construction
public:
	CConfigConnectorTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigConnectorTestDlg)
	enum { IDD = IDD_DLG_CONFIG_CONNECTOR_TEST };
	CString	m_ipAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigConnectorTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigConnectorTestDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCONNECTORTESTDLG_H__F4650368_F431_47A5_A117_321A79C64E04__INCLUDED_)
