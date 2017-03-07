// ttrreerDlg.h : header file
//

#if !defined(AFX_TTRREERDLG_H__87F6BCE6_F27F_4B75_8EDC_14D977A293CC__INCLUDED_)
#define AFX_TTRREERDLG_H__87F6BCE6_F27F_4B75_8EDC_14D977A293CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTtrreerDlg dialog
class IsClientEnterDomain;
class CTtrreerDlg : public CDialog
{
// Construction
public:
	CTtrreerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTtrreerDlg)
	enum { IDD = IDD_TTRREER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTtrreerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTtrreerDlg)
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

#endif // !defined(AFX_TTRREERDLG_H__87F6BCE6_F27F_4B75_8EDC_14D977A293CC__INCLUDED_)
