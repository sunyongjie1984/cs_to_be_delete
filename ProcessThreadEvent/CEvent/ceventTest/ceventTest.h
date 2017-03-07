// ceventTest.h : main header file for the CEVENTTEST application
//

#if !defined(AFX_CEVENTTEST_H__0AA034B7_D22F_4DB3_A78F_3FBBB14A8C65__INCLUDED_)
#define AFX_CEVENTTEST_H__0AA034B7_D22F_4DB3_A78F_3FBBB14A8C65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCeventTestApp:
// See ceventTest.cpp for the implementation of this class
//

class CCeventTestApp : public CWinApp
{
public:
	CCeventTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCeventTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCeventTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEVENTTEST_H__0AA034B7_D22F_4DB3_A78F_3FBBB14A8C65__INCLUDED_)
