// DCdomainDlg.h : header file
//

#if !defined(AFX_DCDOMAINDLG_H__BD237050_E4A5_47EA_B460_9BCC5B0CF0CE__INCLUDED_)
#define AFX_DCDOMAINDLG_H__BD237050_E4A5_47EA_B460_9BCC5B0CF0CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Winbase.h"
#include "Windows.h"
#include "Winnt.h"
#define JOIN_GROUP 1
#define JOIN_DOMAIN 2
#define NOT_JOIN 0
/////////////////////////////////////////////////////////////////////////////
// CDCdomainDlg dialog

class CDCdomainDlg : public CDialog
{
// Construction
public:
	int GetGroupInfo(LPSTR strServerName, UINT *uType);
	BOOL Is_Win2000_DomainController ();
	CDCdomainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDCdomainDlg)
	enum { IDD = IDD_DCDOMAIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCdomainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDCdomainDlg)
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

#endif // !defined(AFX_DCDOMAINDLG_H__BD237050_E4A5_47EA_B460_9BCC5B0CF0CE__INCLUDED_)
