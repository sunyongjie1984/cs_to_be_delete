// netDlg.h : header file
//

#if !defined(AFX_NETDLG_H__D0FEC67A_8E0D_4E2D_A8DD_C4092C872A32__INCLUDED_)
#define AFX_NETDLG_H__D0FEC67A_8E0D_4E2D_A8DD_C4092C872A32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Winnetwk.h"
#pragma comment(lib,"Mpr.lib")

/////////////////////////////////////////////////////////////////////////////
// CNetDlg dialog

class CNetDlg : public CDialog
{
// Construction
public:
	CNetDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNetDlg)
	enum { IDD = IDD_NET_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;



	// Generated message map functions
	//{{AFX_MSG(CNetDlg)
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

#endif // !defined(AFX_NETDLG_H__D0FEC67A_8E0D_4E2D_A8DD_C4092C872A32__INCLUDED_)
