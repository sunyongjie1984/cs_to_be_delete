#if !defined(AFX_LOGINLOAD_H__DE8E63A2_97A8_4BE7_B2A6_19B43C03D23F__INCLUDED_)
#define AFX_LOGINLOAD_H__DE8E63A2_97A8_4BE7_B2A6_19B43C03D23F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginLoad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginLoad dialog

class CLoginLoad : public CDialog
{
// Construction
public:
	CLoginLoad(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginLoad)
	enum { IDD = IDD_LOGINLOAD_DIALOG };
	CString	m_name;
	CString	m_Server;
	int		m_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginLoad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginLoad)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINLOAD_H__DE8E63A2_97A8_4BE7_B2A6_19B43C03D23F__INCLUDED_)
