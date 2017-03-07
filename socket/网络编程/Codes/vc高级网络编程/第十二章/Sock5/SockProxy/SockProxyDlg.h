// SockProxyDlg.h : header file
//

#if !defined(AFX_SOCKPROXYDLG_H__F1A524A7_55AE_11D5_B587_00E04C39B036__INCLUDED_)
#define AFX_SOCKPROXYDLG_H__F1A524A7_55AE_11D5_B587_00E04C39B036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "proxysocket.h"
#include "asyncproxysocket.h"

/////////////////////////////////////////////////////////////////////////////
// CSockProxyDlg dialog

class CSockProxyDlg : public CDialog
{
// Construction
public:
	CSockProxyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSockProxyDlg)
	enum { IDD = IDD_SOCKPROXY_DIALOG };
	CString	m_strPass;
	CString	m_strServer;
	UINT	m_nPort;
	CString	m_strUser;
	CString	m_strDest;
	UINT	m_nPort2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockProxyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CProxySocket m_socket;
	CProxySocket m_socket1;
	CAsyncProxySocket udp;
	// Generated message map functions
	//{{AFX_MSG(CSockProxyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKPROXYDLG_H__F1A524A7_55AE_11D5_B587_00E04C39B036__INCLUDED_)
