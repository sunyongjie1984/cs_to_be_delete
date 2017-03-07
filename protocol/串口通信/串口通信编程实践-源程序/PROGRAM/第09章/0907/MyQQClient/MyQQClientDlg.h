// MyQQClientDlg.h : header file
//

#if !defined(AFX_20043155MYQQCLIENT05DLG_H__113391B3_2405_4F14_9207_1A1F823033D5__INCLUDED_)
#define AFX_20043155MYQQCLIENT05DLG_H__113391B3_2405_4F14_9207_1A1F823033D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CMyMyQQClientDlg dialog

class CMyMyQQClientDlg : public CDialog
{
// Construction
public:
	CMainSocket m_skMainSocket;

	void DisplayMessage(CString UserName,CString strChatMessage);
	void OnReceiveMessage(WPARAM wParam,LPARAM lParam);

	CMyMyQQClientDlg(CWnd* pParent = NULL);	// standard constructor

	CString m_ClientName;
	CString m_UserName;
// Dialog Data
	//{{AFX_DATA(CMyMyQQClientDlg)
	enum { IDD = IDD_MY20043155MYQQCLIENT05_DIALOG };
	CEdit	m_send;
	CEdit	m_ReceiveCtrl;
	CComboBox	m_UserList;
	CString	m_receive;
	CString	m_SendName;
	CString	m_message;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMyQQClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyMyQQClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_20043155MYQQCLIENT05DLG_H__113391B3_2405_4F14_9207_1A1F823033D5__INCLUDED_)
