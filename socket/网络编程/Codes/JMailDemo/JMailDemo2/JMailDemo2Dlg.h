// JMailDemo2Dlg.h : header file
//

#if !defined(AFX_JMAILDEMO2DLG_H__2EE326F6_DF38_46BC_8ABB_BF39BA9F905C__INCLUDED_)
#define AFX_JMAILDEMO2DLG_H__2EE326F6_DF38_46BC_8ABB_BF39BA9F905C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo2Dlg dialog

class CJMailDemo2Dlg : public CDialog
{
// Construction
public:
	CJMailDemo2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CJMailDemo2Dlg)
	enum { IDD = IDD_JMAILDEMO2_DIALOG };
	CString	m_strBody;
	CString	m_strMailServer;
	CString	m_strRecipients;
	CString	m_strSender;
	CString	m_strSubject;
	CString	m_strUserName;
	CString	m_strKey;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMailDemo2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CJMailDemo2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMAILDEMO2DLG_H__2EE326F6_DF38_46BC_8ABB_BF39BA9F905C__INCLUDED_)
