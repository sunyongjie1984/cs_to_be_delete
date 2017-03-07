#if !defined(AFX_PROXYDLG_H__D6F12D93_A8D8_47DE_924C_DD6CC81E398B__INCLUDED_)
#define AFX_PROXYDLG_H__D6F12D93_A8D8_47DE_924C_DD6CC81E398B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProxyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProxyDlg dialog

class CProxyDlg : public CDialog
{
// Construction
public:
	CProxyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProxyDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_strProxy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProxyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProxyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROXYDLG_H__D6F12D93_A8D8_47DE_924C_DD6CC81E398B__INCLUDED_)
