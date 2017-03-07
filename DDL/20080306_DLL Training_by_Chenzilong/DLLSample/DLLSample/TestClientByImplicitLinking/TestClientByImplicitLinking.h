// TestClientByImplicitLinking.h : main header file for the TESTCLIENTBYIMPLICITLINKING application
//

#if !defined(AFX_TESTCLIENTBYIMPLICITLINKING_H__C1D6253C_F02E_417E_ABFE_250551F4DEEB__INCLUDED_)
#define AFX_TESTCLIENTBYIMPLICITLINKING_H__C1D6253C_F02E_417E_ABFE_250551F4DEEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestClientByImplicitLinkingApp:
// See TestClientByImplicitLinking.cpp for the implementation of this class
//

class CTestClientByImplicitLinkingApp : public CWinApp
{
public:
	CTestClientByImplicitLinkingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestClientByImplicitLinkingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestClientByImplicitLinkingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCLIENTBYIMPLICITLINKING_H__C1D6253C_F02E_417E_ABFE_250551F4DEEB__INCLUDED_)
