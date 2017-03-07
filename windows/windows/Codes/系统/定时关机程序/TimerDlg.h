// TimerDlg.h : header file
//

#if !defined(AFX_TIMERDLG_H__AFE9AB6F_CFAB_46F8_9399_7A24C4132ECF__INCLUDED_)
#define AFX_TIMERDLG_H__AFE9AB6F_CFAB_46F8_9399_7A24C4132ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define WM_NOTIFYICON	WM_USER+5
#define IDI_TIMER        0x5

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog

class CTimerDlg : public CDialog
{
// Construction
public:
	CTimerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTimerDlg)
	enum { IDD = IDD_TIMER_DIALOG };
	CString	m_curTime;
	UINT	m_iShut;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_nd;

	// Generated message map functions
	//{{AFX_MSG(CTimerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnShutdown();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnApply();
	afx_msg void OnAbout();
	afx_msg void OnClose();
	//}}AFX_MSG
    afx_msg  LRESULT OnTaskBarCreated(WPARAM wp, LPARAM lp);
	afx_msg void OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnQueryEndSession();
	DECLARE_MESSAGE_MAP()

private:
	UINT m_iNow;
	UINT m_iSecond;
	BOOL m_bCalc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDLG_H__AFE9AB6F_CFAB_46F8_9399_7A24C4132ECF__INCLUDED_)
