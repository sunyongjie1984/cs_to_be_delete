// DemoDlg.h : header file
//

#pragma once


// CDemoDlg dialog
class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DEMO_DIALOG };

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
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedFrameStd();
	afx_msg void OnBnClickedFrameCust();
	afx_msg void OnBnClickedThrowStd();
	afx_msg void OnBnClickedThrowCust();
	afx_msg void OnBnClickedTstSpeed();
	afx_msg void OnBnClickedTstDtor();
	afx_msg void OnBnClickedTstInline();
	afx_msg void OnBnClickedTstNoncpp();
	afx_msg void OnBnClickedTstStopexc();
};
