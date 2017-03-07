// JMailDemo1Dlg.h : header file
//

#if !defined(AFX_JMAILDEMO1DLG_H__4A97D972_2819_412D_BC09_87AC14535033__INCLUDED_)
#define AFX_JMAILDEMO1DLG_H__4A97D972_2819_412D_BC09_87AC14535033__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo1Dlg dialog

class CJMailDemo1Dlg : public CDialog
{
// Construction
public:
	CJMailDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CJMailDemo1Dlg)
	enum { IDD = IDD_JMAILDEMO1_DIALOG };
	CListCtrl	m_ctlMessagesList;
	CString	m_strMailServer;
	CString	m_strPassword;
	CString	m_strUserid;
	CString	m_strBody;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMailDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CStringArray m_strBodyArray;

	// Generated message map functions
	//{{AFX_MSG(CJMailDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnReceive();
	afx_msg void OnShowBody(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMAILDEMO1DLG_H__4A97D972_2819_412D_BC09_87AC14535033__INCLUDED_)
