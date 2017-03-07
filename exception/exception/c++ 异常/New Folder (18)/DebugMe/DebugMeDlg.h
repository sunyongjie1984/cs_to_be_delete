// DebugMeDlg.h : header file
//

#pragma once


// CDebugMeDlg dialog
class CDebugMeDlg : public CDialog
{
// Construction
public:
	CDebugMeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DEBUGME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBreak();
	afx_msg void OnBnClickedOutput();
	afx_msg void OnBnClickedRaiseAV();
};
