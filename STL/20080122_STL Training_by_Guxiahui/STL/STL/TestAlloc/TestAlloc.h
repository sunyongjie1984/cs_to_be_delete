// TestAlloc.h : main header file for the TESTALLOC application
//

#if !defined(AFX_TESTALLOC_H__379C6099_FA6B_4B5D_A28F_D48BCB44A526__INCLUDED_)
#define AFX_TESTALLOC_H__379C6099_FA6B_4B5D_A28F_D48BCB44A526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestAllocApp:
// See TestAlloc.cpp for the implementation of this class
//

class CTestAllocApp : public CWinApp
{
public:
	CTestAllocApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAllocApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestAllocApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTALLOC_H__379C6099_FA6B_4B5D_A28F_D48BCB44A526__INCLUDED_)
