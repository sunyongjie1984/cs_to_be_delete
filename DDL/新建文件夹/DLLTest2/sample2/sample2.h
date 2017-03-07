// sample2.h : main header file for the SAMPLE2 DLL
//

#if !defined(AFX_SAMPLE2_H__C163D1D2_A333_4F73_A8F8_6FF21E1CA33A__INCLUDED_)
#define AFX_SAMPLE2_H__C163D1D2_A333_4F73_A8F8_6FF21E1CA33A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSample2App
// See sample2.cpp for the implementation of this class
//

class CSample2App : public CWinApp
{
public:
	CSample2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSample2App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSample2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE2_H__C163D1D2_A333_4F73_A8F8_6FF21E1CA33A__INCLUDED_)
