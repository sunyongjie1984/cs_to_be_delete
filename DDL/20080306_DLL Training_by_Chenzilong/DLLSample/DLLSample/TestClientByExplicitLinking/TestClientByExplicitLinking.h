// TestClientByExplicitLinking.h : main header file for the TESTCLIENTBYEXPLICITLINKING application
//

#if !defined(AFX_TESTCLIENTBYEXPLICITLINKING_H__AD80D588_546B_4754_B44D_25A3C13FF6B7__INCLUDED_)
#define AFX_TESTCLIENTBYEXPLICITLINKING_H__AD80D588_546B_4754_B44D_25A3C13FF6B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestClientByExplicitLinkingApp:
// See TestClientByExplicitLinking.cpp for the implementation of this class
//

class CTestClientByExplicitLinkingApp : public CWinApp
{
public:
	CTestClientByExplicitLinkingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestClientByExplicitLinkingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestClientByExplicitLinkingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCLIENTBYEXPLICITLINKING_H__AD80D588_546B_4754_B44D_25A3C13FF6B7__INCLUDED_)
