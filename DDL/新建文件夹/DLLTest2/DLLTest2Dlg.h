// DLLTest2Dlg.h : header file
//

#if !defined(AFX_DLLTEST2DLG_H__A5F46FC9_DD54_4F9C_8B8F_B4EC15ECB9DC__INCLUDED_)
#define AFX_DLLTEST2DLG_H__A5F46FC9_DD54_4F9C_8B8F_B4EC15ECB9DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDLLTest2Dlg dialog

class CDLLTest2Dlg : public CDialog
{
// Construction
public:
	CDLLTest2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDLLTest2Dlg)
	enum { IDD = IDD_DLLTEST2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLTest2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDLLTest2Dlg)
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

#endif // !defined(AFX_DLLTEST2DLG_H__A5F46FC9_DD54_4F9C_8B8F_B4EC15ECB9DC__INCLUDED_)
