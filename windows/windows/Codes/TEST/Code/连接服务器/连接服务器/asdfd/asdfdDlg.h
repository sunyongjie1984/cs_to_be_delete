// asdfdDlg.h : header file
//

#if !defined(AFX_ASDFDDLG_H__1B99A3B4_EFD7_489B_84BE_1243C64020C3__INCLUDED_)
#define AFX_ASDFDDLG_H__1B99A3B4_EFD7_489B_84BE_1243C64020C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAsdfdDlg dialog

class CAsdfdDlg : public CDialog
{
// Construction
public:
	CAsdfdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAsdfdDlg)
	enum { IDD = IDD_ASDFD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsdfdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAsdfdDlg)
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

#endif // !defined(AFX_ASDFDDLG_H__1B99A3B4_EFD7_489B_84BE_1243C64020C3__INCLUDED_)
