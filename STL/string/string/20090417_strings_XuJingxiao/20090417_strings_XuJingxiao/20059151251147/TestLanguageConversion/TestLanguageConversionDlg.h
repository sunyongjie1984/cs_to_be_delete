// TestLanguageConversionDlg.h : header file
//

#if !defined(AFX_TESTLANGUAGECONVERSIONDLG_H__CD3A108C_D0CD_4149_B67B_A5D91F3FA337__INCLUDED_)
#define AFX_TESTLANGUAGECONVERSIONDLG_H__CD3A108C_D0CD_4149_B67B_A5D91F3FA337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestLanguageConversionDlg dialog
#include "BtnST.h"
#include "BCMenu.h"

class CTestLanguageConversionDlg : public CDialog
{
// Construction
public:
	void PopupMenu(CPoint point);
	void Localize();
	CTestLanguageConversionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestLanguageConversionDlg)
	enum { IDD = IDD_TESTLANGUAGECONVERSION_DIALOG };
	CButtonST	m_btn_KR;
	CButtonST	m_btn_JP;
	CButtonST	m_btn_EN;
	CButtonST	m_btn_CN;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestLanguageConversionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestLanguageConversionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCn();
	afx_msg void OnButtonJp();
	afx_msg void OnButtonKr();
	afx_msg void OnButtonEn();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLANGUAGECONVERSIONDLG_H__CD3A108C_D0CD_4149_B67B_A5D91F3FA337__INCLUDED_)
