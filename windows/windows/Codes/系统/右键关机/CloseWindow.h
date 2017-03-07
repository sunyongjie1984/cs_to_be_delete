// CloseWindow.h : main header file for the CLOSEWINDOW application
//

#if !defined(AFX_CLOSEWINDOW_H__A78B7664_41F6_463D_859E_41AF299070B3__INCLUDED_)
#define AFX_CLOSEWINDOW_H__A78B7664_41F6_463D_859E_41AF299070B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowApp:
// See CloseWindow.cpp for the implementation of this class
//

class CCloseWindowApp : public CWinApp
{
public:
	CCloseWindowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseWindowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCloseWindowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEWINDOW_H__A78B7664_41F6_463D_859E_41AF299070B3__INCLUDED_)
