// TTY.h : main header file for the TTY application
//

#if !defined(AFX_TTY_H__847418E6_D6D8_4354_8415_E8D327A7D4BC__INCLUDED_)
#define AFX_TTY_H__847418E6_D6D8_4354_8415_E8D327A7D4BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTTYApp:
// See TTY.cpp for the implementation of this class
//

class CTTYApp : public CWinApp
{
public:
	CTTYApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTTYApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTY_H__847418E6_D6D8_4354_8415_E8D327A7D4BC__INCLUDED_)
