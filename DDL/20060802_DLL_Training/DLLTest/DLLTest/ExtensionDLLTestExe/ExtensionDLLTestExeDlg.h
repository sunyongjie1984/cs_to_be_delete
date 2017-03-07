// ExtensionDLLTestExeDlg.h : header file
//

#if !defined(AFX_EXTENSIONDLLTESTEXEDLG_H__B55CB927_8DFA_403D_A91D_2BF6726DD984__INCLUDED_)
#define AFX_EXTENSIONDLLTESTEXEDLG_H__B55CB927_8DFA_403D_A91D_2BF6726DD984__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CExtensionDLLTestExeDlg dialog
//
class CExtensionDLLTestExeDlg : public CDialog
{
// Construction
public:
	CExtensionDLLTestExeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExtensionDLLTestExeDlg)
	enum { IDD = IDD_MAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtensionDLLTestExeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExtensionDLLTestExeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnExtDllTest();
	afx_msg void OnBtnExportClassTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENSIONDLLTESTEXEDLG_H__B55CB927_8DFA_403D_A91D_2BF6726DD984__INCLUDED_)
