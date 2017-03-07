#ifndef __GETMAIL_H__
#define __GETMAIL_H__

#include "SystemTray.h"

class CGetMailDlg : public CDialog
{
public:
	void SetInfo(CString strInfo, BOOL bOk = TRUE);
	CGetMailDlg(CWnd* pParent = NULL);

public:
	CString m_strPop3;
	CString m_strUser;
	CString m_strPass;
	UINT    m_nTime;
	//{{AFX_DATA(CGetMailDlg)
	enum { IDD = IDD_GETMAIL_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CGetMailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
protected:
	HICON m_hIcon;
	BOOL  m_bStart;
	int   m_nMailCount;
	CSystemTray m_cSystray;
	//{{AFX_MSG(CGetMailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnHide();
	afx_msg void OnShow();
	afx_msg void OnAbout();
	afx_msg void OnUpdateHide(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShow(CCmdUI* pCmdUI);
	afx_msg void OnExit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __GETMAIL_H__
