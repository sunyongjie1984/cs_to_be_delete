// SimpleServerDlg.h : header file
//

#if !defined(AFX_SIMPLESERVERDLG_H__31AED04A_0740_4B26_BDD1_9921CCD6A64E__INCLUDED_)
#define AFX_SIMPLESERVERDLG_H__31AED04A_0740_4B26_BDD1_9921CCD6A64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "winsock.h"
#pragma comment(lib, "wsock32")

/////////////////////////////////////////////////////////////////////////////
// CSimpleServerDlg dialog

class CSimpleServerDlg : public CDialog
{
// Construction
public:
	void CleanUp();
	void StartUp();
	CSimpleServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSimpleServerDlg)
	enum { IDD = IDD_SIMPLESERVER_DIALOG };
	UINT	m_nPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	SOCKET m_hSocket;
	SOCKADDR_IN m_addr;

	// Generated message map functions
	//{{AFX_MSG(CSimpleServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLESERVERDLG_H__31AED04A_0740_4B26_BDD1_9921CCD6A64E__INCLUDED_)
