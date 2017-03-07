// TestDrawItemFunctionDlg.h : header file
//

#if !defined(AFX_TESTDRAWITEMFUNCTIONDLG_H__A7B79D6F_44D1_4C40_91FF_89FFB56E6F41__INCLUDED_)
#define AFX_TESTDRAWITEMFUNCTIONDLG_H__A7B79D6F_44D1_4C40_91FF_89FFB56E6F41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDrawItemFunctionDlg dialog
#include "NL_Button_Test.h"
#include "NL_ListCtrl_Test.h"

class CTestDrawItemFunctionDlg : public CDialog
{
// Construction
public:
	CTestDrawItemFunctionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDrawItemFunctionDlg)
	enum { IDD = IDD_TESTDRAWITEMFUNCTION_DIALOG };
	NL_ListCtrl_Test	m_lc_test;
	//CListCtrl	m_lc_test;
	CListBox	m_ListBox;
	NL_Button_Test	m_btn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDrawItemFunctionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDrawItemFunctionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDRAWITEMFUNCTIONDLG_H__A7B79D6F_44D1_4C40_91FF_89FFB56E6F41__INCLUDED_)
