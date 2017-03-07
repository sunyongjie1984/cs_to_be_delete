// NewTabDlg.h : header file
//

#if !defined(AFX_NEWTABDLG_H__9D8059EC_E909_4DC8_8122_D98F7B9710B7__INCLUDED_)
#define AFX_NEWTABDLG_H__9D8059EC_E909_4DC8_8122_D98F7B9710B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabCtrlSSL.h"
#include "DialogEntropy.h"
#include "DialogRelation.h"
#include "AboutTab.h"

/////////////////////////////////////////////////////////////////////////////
// CNewTabDlg dialog

class CNewTabDlg : public CDialog
{
// Construction
public:
	CNewTabDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNewTabDlg)
	enum { IDD = IDD_NEWTAB_DIALOG };
	CTabCtrlSSL	m_tabCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewTabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNewTabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDialogRelation m_tabRelation;
	CDialogEntropy m_tabEntropy;
	CAboutTab m_aboutTab;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTABDLG_H__9D8059EC_E909_4DC8_8122_D98F7B9710B7__INCLUDED_)
