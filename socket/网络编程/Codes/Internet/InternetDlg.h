// InternetDlg.h : header file
//

#if !defined(AFX_INTERNETDLG_H__65D7EACB_1C60_467A_A0E9_4E5A0FA8BE36__INCLUDED_)
#define AFX_INTERNETDLG_H__65D7EACB_1C60_467A_A0E9_4E5A0FA8BE36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxinet.h>
/////////////////////////////////////////////////////////////////////////////
// CInternetDlg dialog
void GetCurrentPath(CString &strPath);

class CInternetDlg : public CDialog
{   
// Construction
public:
	CString m_strPassWord;
	CString m_strUserName;
	CString m_strApAddress;
	CString m_strUserAndPwd;
	
	CInternetDlg(CWnd* pParent = NULL);	// standard constructor
	CInternetSession *m_Session;
	CHttpConnection *m_httpConnect;


// Dialog Data
	//{{AFX_DATA(CInternetDlg)
	enum { IDD = IDD_INTERNET_DIALOG };
	CIPAddressCtrl	m_SetApAddress;
	CIPAddressCtrl	m_ApAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInternetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERNETDLG_H__65D7EACB_1C60_467A_A0E9_4E5A0FA8BE36__INCLUDED_)
