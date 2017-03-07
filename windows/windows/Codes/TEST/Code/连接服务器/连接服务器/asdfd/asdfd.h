// asdfd.h : main header file for the ASDFD application
//

#if !defined(AFX_ASDFD_H__F2E69FE8_8445_4DB4_900B_DD111CD46240__INCLUDED_)
#define AFX_ASDFD_H__F2E69FE8_8445_4DB4_900B_DD111CD46240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAsdfdApp:
// See asdfd.cpp for the implementation of this class
//

class CAsdfdApp : public CWinApp
{
public:
	CAsdfdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsdfdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAsdfdApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASDFD_H__F2E69FE8_8445_4DB4_900B_DD111CD46240__INCLUDED_)
