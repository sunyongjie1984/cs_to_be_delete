// PowerOffDlg.h : header file
//

#if !defined(AFX_POWEROFFDLG_H__245EA3BD_84F6_4DEC_82DC_8A168E68CB0A__INCLUDED_)
#define AFX_POWEROFFDLG_H__245EA3BD_84F6_4DEC_82DC_8A168E68CB0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPowerOffDlg dialog

class CPowerOffDlg : public CDialog
{
// Construction
public:
	CPowerOffDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPowerOffDlg)
	enum { IDD = IDD_POWEROFF_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerOffDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPowerOffDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnOk2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWEROFFDLG_H__245EA3BD_84F6_4DEC_82DC_8A168E68CB0A__INCLUDED_)
