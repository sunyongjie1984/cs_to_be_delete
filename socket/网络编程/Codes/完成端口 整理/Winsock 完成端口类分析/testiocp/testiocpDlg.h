// testiocpDlg.h : header file
//

#if !defined(AFX_TESTIOCPDLG_H__5B0C984E_B8EB_48D7_AF79_7651818C9F3A__INCLUDED_)
#define AFX_TESTIOCPDLG_H__5B0C984E_B8EB_48D7_AF79_7651818C9F3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestiocpDlg dialog
#include "NetCompletionPort.h"


class CTestiocpDlg : public CDialog
{
// Construction
public:
	CTestiocpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestiocpDlg)
	enum { IDD = IDD_TESTIOCP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestiocpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestiocpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTIOCPDLG_H__5B0C984E_B8EB_48D7_AF79_7651818C9F3A__INCLUDED_)
