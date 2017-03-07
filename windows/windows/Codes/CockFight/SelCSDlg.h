#if !defined(AFX_SELCSDLG_H__EA743E8D_3304_4D0E_9029_CEB4AD6B412B__INCLUDED_)
#define AFX_SELCSDLG_H__EA743E8D_3304_4D0E_9029_CEB4AD6B412B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelCSDlg.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CSelCSDlg dialog

class CSelCSDlg : public CDialog
{
// Construction
public:
	int m_nIndex;
	CSelCSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelCSDlg)
	enum { IDD = IDD_DLG_CS };
	CComboBox	m_cmbPic;
	CComboBox	m_cmbSelCS;
	int		m_nPort;
	CString	m_strSvrName;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelCSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelCSDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELCSDLG_H__EA743E8D_3304_4D0E_9029_CEB4AD6B412B__INCLUDED_)
