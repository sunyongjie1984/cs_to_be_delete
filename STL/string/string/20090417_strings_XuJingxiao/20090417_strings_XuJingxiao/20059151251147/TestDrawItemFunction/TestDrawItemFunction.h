// TestDrawItemFunction.h : main header file for the TESTDRAWITEMFUNCTION application
//

#if !defined(AFX_TESTDRAWITEMFUNCTION_H__EBD72BF2_D33D_44A6_B49B_B680075FF701__INCLUDED_)
#define AFX_TESTDRAWITEMFUNCTION_H__EBD72BF2_D33D_44A6_B49B_B680075FF701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDrawItemFunctionApp:
// See TestDrawItemFunction.cpp for the implementation of this class
//

class CTestDrawItemFunctionApp : public CWinApp
{
public:
	CTestDrawItemFunctionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDrawItemFunctionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDrawItemFunctionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDRAWITEMFUNCTION_H__EBD72BF2_D33D_44A6_B49B_B680075FF701__INCLUDED_)
