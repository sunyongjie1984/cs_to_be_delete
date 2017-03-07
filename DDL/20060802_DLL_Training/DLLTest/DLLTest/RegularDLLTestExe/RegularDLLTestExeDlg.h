// RegularDLLTestExeDlg.h : header file
//

#if !defined(AFX_REGULARDLLTESTEXEDLG_H__3F947D9D_3FC2_4231_BBA9_76C1A8B3C65F__INCLUDED_)
#define AFX_REGULARDLLTESTEXEDLG_H__3F947D9D_3FC2_4231_BBA9_76C1A8B3C65F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRegularDLLTestExeDlg dialog

class CRegularDLLTestExeDlg : public CDialog
{
// Construction
public:
	CRegularDLLTestExeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegularDLLTestExeDlg)
	enum { IDD = IDD_REGULARDLLTESTEXE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegularDLLTestExeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegularDLLTestExeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnShowMessageTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGULARDLLTESTEXEDLG_H__3F947D9D_3FC2_4231_BBA9_76C1A8B3C65F__INCLUDED_)
