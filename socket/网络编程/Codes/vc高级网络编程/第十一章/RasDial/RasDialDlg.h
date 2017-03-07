// RasDialDlg.h : header file
//

#if !defined(AFX_RASDIALDLG_H__C8302E63_3DE8_46A4_8F26_F5852798D1AB__INCLUDED_)
#define AFX_RASDIALDLG_H__C8302E63_3DE8_46A4_8F26_F5852798D1AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ras.h"

/////////////////////////////////////////////////////////////////////////////
// CRasDialDlg dialog

class CRasDialDlg : public CDialog
{
// Construction
public:
	void TextOut(CString strOut);
	CRasDialDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRasDialDlg)
	enum { IDD = IDD_RASDIAL_DIALOG };
	CEdit	m_ctrlEdit;
	CString	m_strDomain;
	CString	m_strPass;
	CString	m_strPhone;
	CString	m_strUser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRasDialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CRas* m_ras;
	// Generated message map functions
	//{{AFX_MSG(CRasDialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RASDIALDLG_H__C8302E63_3DE8_46A4_8F26_F5852798D1AB__INCLUDED_)
