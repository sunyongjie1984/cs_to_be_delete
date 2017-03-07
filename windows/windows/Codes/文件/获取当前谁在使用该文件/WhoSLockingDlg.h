// WhoSLockingDlg.h : header file
//

#if !defined(AFX_WHOSLOCKINGDLG_H__285A0383_A959_11D3_BFE4_0010E3B966CE__INCLUDED_)
#define AFX_WHOSLOCKINGDLG_H__285A0383_A959_11D3_BFE4_0010E3B966CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CListCtrlEx.h"
#include "SimpleProcessAPI.h"

#define PROCESS_LIST_HEADER_COLUMN_0 "Name                   "
#define PROCESS_LIST_HEADER_COLUMN_1 "PID         "
#define PROCESS_LIST_HEADER_COLUMN_2 "Executable Path                                          "
#define PROCESS_LIST_HEADER_COLUMN_3 "Service Name (if applicable)          "

/////////////////////////////////////////////////////////////////////////////
// CWhoSLockingDlg dialog

class CWhoSLockingDlg : public CDialog
{
// Construction
public:
	void SetDefaultFileName(LPCTSTR lpszDefaultFileName);
	CString GetDefaultFileName(void);
	CWhoSLockingDlg(CWnd* pParent = NULL, LPCTSTR lpszDefaultFileName = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWhoSLockingDlg)
	enum { IDD = IDD_WHOSLOCKING_DIALOG };
	CStatic	m_oMessageText;
	CButton	m_oFrameListProcess;
	CButton	m_oFrameDLLModule;
	CButton	m_oBrowseDLLButton;
	CEdit	m_oModuleNameEdit;
	CButton	m_oOKButton;
	CButton	m_oRefreshButton;
	CListCtrlEx	m_oListOfProcesses;
	CString	m_szMessageText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhoSLockingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_szDefaultFileName;
	HICON m_hIcon;
    CSimpleProcessAPI m_oProcessAPI;

	// Generated message map functions
	//{{AFX_MSG(CWhoSLockingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowseDllName();
	afx_msg void OnRefresh();
	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHOSLOCKINGDLG_H__285A0383_A959_11D3_BFE4_0010E3B966CE__INCLUDED_)
