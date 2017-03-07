#if !defined(AFX_GETIP_H__4559702A_92CF_45B5_94C2_5F9C69605669__INCLUDED_)
#define AFX_GETIP_H__4559702A_92CF_45B5_94C2_5F9C69605669__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetIP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetIP dialog

class CGetIP : public CDialog
{
// Construction
public:
	CGetIP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetIP)
	enum { IDD = IDD_DIALOG_GETIP };
	CIPAddressCtrl	ip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetIP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	public:
		CString ipstr;
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetIP)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETIP_H__4559702A_92CF_45B5_94C2_5F9C69605669__INCLUDED_)
