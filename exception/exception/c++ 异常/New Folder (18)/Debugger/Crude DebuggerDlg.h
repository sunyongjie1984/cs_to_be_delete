// Crude DebuggerDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCrudeDebuggerDlg dialog
class CCrudeDebuggerDlg : public CDialog
{

	// Debug Event Counts
	int TotalEvents;
	int ThreadCount, DLLCount, ExceptionCount, OutputDebugCount;	// Including Breakpoints 

	

	HANDLE m_hDebugThread;
	bool m_bIsDebugging;

public:
	CCrudeDebuggerDlg(CWnd* pParent = NULL);	// standard constructor

	// Enables or disables appropriate controls of Debugging status.
	void SetDebuggingModeUI(bool bDebug);

	CString ProcessNameToDebug;

	void DebuggerThreadProc();

// Dialog Data
	enum { IDD = IDD_CRUDEDEBUGGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	LRESULT OnDebugEventMessage(WPARAM, LPARAM);


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartDebugging();
	afx_msg void OnBnClickedBrowse();
	CListCtrl m_cDebugEvents;
	CStatic m_cThreadCount;
	CStatic m_cDLLCount;
	CStatic m_cTotalEvents;
	CStatic m_cOutputDebug;
	CStatic m_cExceptionCount;
};
