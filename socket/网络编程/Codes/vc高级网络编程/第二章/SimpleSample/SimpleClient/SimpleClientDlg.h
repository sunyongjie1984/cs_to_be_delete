// SimpleClientDlg.h : header file
//

#if !defined(AFX_SIMPLECLIENTDLG_H__C76E63E6_95B9_485C_BAFA_484EF2D3E381__INCLUDED_)
#define AFX_SIMPLECLIENTDLG_H__C76E63E6_95B9_485C_BAFA_484EF2D3E381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "winsock.h"
#pragma comment(lib, "wsock32")

/////////////////////////////////////////////////////////////////////////////
// CSimpleClientDlg dialog

class CSimpleClientDlg : public CDialog
{
// Construction
public:
	void CleanUp();
	void StartUp();
	CSimpleClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSimpleClientDlg)
	enum { IDD = IDD_SIMPLECLIENT_DIALOG };
	CString	m_strPass;
	UINT	m_nPort;
	CString	m_strServer;
	CString	m_strUser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	SOCKET m_hSocket;
	SOCKADDR_IN m_addr;

	// Generated message map functions
	//{{AFX_MSG(CSimpleClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLECLIENTDLG_H__C76E63E6_95B9_485C_BAFA_484EF2D3E381__INCLUDED_)
