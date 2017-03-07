// TESTSSDFSFDlg.h : header file
//

#if !defined(AFX_TESTSSDFSFDLG_H__E70E0319_E591_422C_9C39_ADFC83ABB4D5__INCLUDED_)
#define AFX_TESTSSDFSFDLG_H__E70E0319_E591_422C_9C39_ADFC83ABB4D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Winnetwk.h"
#pragma comment(lib,"Mpr.lib")
#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>
#include "Lmaccess.h"
#pragma comment(lib,"ActiveDS.lib")
#pragma comment(lib,"Netapi32.lib ")
/////////////////////////////////////////////////////////////////////////////
// CTESTSSDFSFDlg dialog

class CTESTSSDFSFDlg : public CDialog
{
// Construction
public:
	CTESTSSDFSFDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTESTSSDFSFDlg)
	enum { IDD = IDD_TESTSSDFSF_DIALOG };
	CListCtrl	m_listuserinfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTESTSSDFSFDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTESTSSDFSFDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSSDFSFDLG_H__E70E0319_E591_422C_9C39_ADFC83ABB4D5__INCLUDED_)
