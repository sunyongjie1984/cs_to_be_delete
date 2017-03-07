// RegularDLLTest.h : main header file for the REGULARDLLTEST DLL
//

#if !defined(AFX_REGULARDLLTEST_H__13203D53_E83E_48AE_AC3E_5262A7CB1E05__INCLUDED_)
#define AFX_REGULARDLLTEST_H__13203D53_E83E_48AE_AC3E_5262A7CB1E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegularDLLTestApp
// See RegularDLLTest.cpp for the implementation of this class
//

class CRegularDLLTestApp : public CWinApp
{
public:
	CRegularDLLTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegularDLLTestApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CRegularDLLTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGULARDLLTEST_H__13203D53_E83E_48AE_AC3E_5262A7CB1E05__INCLUDED_)
