// Calculator.h : main header file for the CALCULATOR DLL
//

#if !defined(AFX_CALCULATOR_H__6FE09D1E_E2B4_404A_8D4E_CC18605584DD__INCLUDED_)
#define AFX_CALCULATOR_H__6FE09D1E_E2B4_404A_8D4E_CC18605584DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalculatorApp
// See Calculator.cpp for the implementation of this class
//

class CCalculatorApp : public CWinApp
{
public:
	CCalculatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCalculatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATOR_H__6FE09D1E_E2B4_404A_8D4E_CC18605584DD__INCLUDED_)
