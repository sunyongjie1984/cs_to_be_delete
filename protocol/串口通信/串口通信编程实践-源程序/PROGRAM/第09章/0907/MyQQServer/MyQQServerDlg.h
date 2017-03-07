// MyQQServerDlg.h : header file
//

#if !defined(AFX_20043155MYQQSERVER05DLG_H__F1B609E9_19C2_4E8E_8BFC_74AB50A8E35C__INCLUDED_)
#define AFX_20043155MYQQSERVER05DLG_H__F1B609E9_19C2_4E8E_8BFC_74AB50A8E35C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ServerSocket.h"
#include "Message.h"
#include "Typedef.h"

/////////////////////////////////////////////////////////////////////////////
// CMyMyQQServerDlg dialog

class CMyMyQQServerDlg : public CDialog
{
// Construction
public:
	CMyMyQQServerDlg(CWnd* pParent = NULL);	// standard constructor
	ServerSocket m_ServerSocket;
// Dialog Data
	//{{AFX_DATA(CMyMyQQServerDlg)
	enum { IDD = IDD_MY20043155MYQQSERVER05_DIALOG };
	CComboBox	m_SendNameCtrl;
	CListBox	m_ClientList;
	int		m_port;
	CString	m_Message;
	CString	m_SendName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMyQQServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyMyQQServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpensocket();
	afx_msg void OnClosesocket();
	afx_msg void OnSend();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_20043155MYQQSERVER05DLG_H__F1B609E9_19C2_4E8E_8BFC_74AB50A8E35C__INCLUDED_)
