// SendTimeDlg.h : header file
//

#if !defined(AFX_SENDTIMEDLG_H__C8401A10_320C_4932_BA5C_BECEF1AEF6B2__INCLUDED_)
#define AFX_SENDTIMEDLG_H__C8401A10_320C_4932_BA5C_BECEF1AEF6B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma comment( lib, "Ws2_32" )
/////////////////////////////////////////////////////////////////////////////
// CSendTimeDlg dialog

class CSendTimeDlg : public CDialog
{
// Construction
public:
	CSendTimeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSendTimeDlg)
	enum { IDD = IDD_SENDTIME_DIALOG };
	CString	m_strIP;
	int	m_nTime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSendTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDTIMEDLG_H__C8401A10_320C_4932_BA5C_BECEF1AEF6B2__INCLUDED_)
