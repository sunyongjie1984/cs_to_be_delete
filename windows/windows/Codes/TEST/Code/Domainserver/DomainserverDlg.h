// DomainserverDlg.h : header file
//

#if !defined(AFX_DOMAINSERVERDLG_H__A3B822D9_9FAC_431C_8A6B_790B499F13C7__INCLUDED_)
#define AFX_DOMAINSERVERDLG_H__A3B822D9_9FAC_431C_8A6B_790B499F13C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define JOIN_GROUP 1
#define JOIN_DOMAIN 2
#define NOT_JOIN 0
/////////////////////////////////////////////////////////////////////////////
// CDomainserverDlg dialog

class CDomainserverDlg : public CDialog
{
// Construction
public:
	CString	m_user_name;
	CString	m_password;

	int GetGroupInfo(LPSTR strServerName,UINT* uType);
	CDomainserverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDomainserverDlg)
	enum { IDD = IDD_DOMAINSERVER_DIALOG };
	CString	m_servername;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDomainserverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDomainserverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOMAINSERVERDLG_H__A3B822D9_9FAC_431C_8A6B_790B499F13C7__INCLUDED_)
