// ClientTestDlg.h : header file
//

#if !defined(AFX_CLIENTTESTDLG_H__75C02DA2_C1D6_40E0_AEDF_9F64F5D379F8__INCLUDED_)
#define AFX_CLIENTTESTDLG_H__75C02DA2_C1D6_40E0_AEDF_9F64F5D379F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientTestDlg dialog

#include "GetIP.h"

class CClientTestDlg : public CDialog
{
// Construction
public:
	CClientTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientTestDlg)
	enum { IDD = IDD_CLIENTTEST_DIALOG };
	CListBox	list;
	CString	str;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientTestDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	LRESULT OnReadClose(WPARAM wParam,LPARAM lParam);
// Implementation

public:

	SOCKET ServerSocket;                 //SOCKET 
	SOCKADDR_IN sockStruct;          //SOCKET ½á¹¹

	BOOL IsTrue;

	Msg msg;

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTTESTDLG_H__75C02DA2_C1D6_40E0_AEDF_9F64F5D379F8__INCLUDED_)
