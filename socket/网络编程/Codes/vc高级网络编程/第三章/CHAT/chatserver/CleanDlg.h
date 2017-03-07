#if !defined(AFX_CLEANDLG_H__573A89A1_83F4_11D4_BED1_0000B491CAB6__INCLUDED_)
#define AFX_CLEANDLG_H__573A89A1_83F4_11D4_BED1_0000B491CAB6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CleanDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCleanDlg dialog

class CCleanDlg : public CDialog
{
// Construction
public:
	CCleanDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCleanDlg)
	enum { IDD = IDD_CLEANSB };
	CListBox	m_cleanlist;
	CString	m_cleanname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCleanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCleanDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEANDLG_H__573A89A1_83F4_11D4_BED1_0000B491CAB6__INCLUDED_)
