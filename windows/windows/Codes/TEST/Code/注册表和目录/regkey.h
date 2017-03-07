// regkey.h : main header file for the REGKEY application
//

#if !defined(AFX_REGKEY_H__84EA826B_33AC_484D_BD51_47644AF4DE98__INCLUDED_)
#define AFX_REGKEY_H__84EA826B_33AC_484D_BD51_47644AF4DE98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegkeyApp:
// See regkey.cpp for the implementation of this class
//

class CRegkeyApp : public CWinApp
{
public:
	CRegkeyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegkeyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRegkeyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGKEY_H__84EA826B_33AC_484D_BD51_47644AF4DE98__INCLUDED_)
