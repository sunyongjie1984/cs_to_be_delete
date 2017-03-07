// TestLanguageConversion.h : main header file for the TESTLANGUAGECONVERSION application
//

#if !defined(AFX_TESTLANGUAGECONVERSION_H__79E6B2B4_5CB9_46A0_A71A_AE543D4DF869__INCLUDED_)
#define AFX_TESTLANGUAGECONVERSION_H__79E6B2B4_5CB9_46A0_A71A_AE543D4DF869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestLanguageConversionApp:
// See TestLanguageConversion.cpp for the implementation of this class
//

class CTestLanguageConversionApp : public CWinApp
{
public:
	CTestLanguageConversionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestLanguageConversionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestLanguageConversionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLANGUAGECONVERSION_H__79E6B2B4_5CB9_46A0_A71A_AE543D4DF869__INCLUDED_)
