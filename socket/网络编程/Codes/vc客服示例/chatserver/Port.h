#if !defined(AFX_PORT_H__96A79FB8_A968_4BB1_B19E_97CD5C3F0830__INCLUDED_)
#define AFX_PORT_H__96A79FB8_A968_4BB1_B19E_97CD5C3F0830__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Port.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPort dialog

class CPort : public CDialog
{
// Construction
public:
	CPort(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPort)
	enum { IDD = IDD_DIALOG1 };
	long	m_port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPort)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPort)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORT_H__96A79FB8_A968_4BB1_B19E_97CD5C3F0830__INCLUDED_)
