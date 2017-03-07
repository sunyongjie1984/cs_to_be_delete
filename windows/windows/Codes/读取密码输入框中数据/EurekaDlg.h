// EurekaDlg.h : header file
//

#if !defined(AFX_EUREKADLG_H__7C4CA3BA_4E1F_11D1_BDB6_0060970F880E__INCLUDED_)
#define AFX_EUREKADLG_H__7C4CA3BA_4E1F_11D1_BDB6_0060970F880E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CEurekaDlg dialog

const CString gc_PasswordYes = "Yes";
const CString gc_PasswordNo = "No";

class CEurekaDlg : public CDialog
{
// Construction
public:
	CEurekaDlg(CWnd* pParent = NULL);	// standard constructor

protected:
	BOOL m_bIsCapturing;
protected:
	void StopCapture();

protected:
	HCURSOR m_hMagGlassCursor;
	HICON m_hMagGlassIcon;
	HICON m_hMagGlassBlank;


// Dialog Data
	//{{AFX_DATA(CEurekaDlg)
	enum { IDD = IDD_EUREKA_DIALOG };
	CStatic	m_stcMagnifyingGlass;
	CString	m_strXYPos;
	CString	m_strHwnd;
	CString	m_strWndClass;
	CString	m_strIsPassword;
	CString	m_strPassword;
	BOOL	m_bAlwaysOnTop;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEurekaDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEurekaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnAlwaysOnTop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EUREKADLG_H__7C4CA3BA_4E1F_11D1_BDB6_0060970F880E__INCLUDED_)
