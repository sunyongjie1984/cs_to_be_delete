// usingdll.h : main header file for the USINGDLL application
//

#if !defined(AFX_USINGDLL_H__269F218C_465D_4C82_9AE7_619EBA3E799E__INCLUDED_)
#define AFX_USINGDLL_H__269F218C_465D_4C82_9AE7_619EBA3E799E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUsingdllApp:
// See usingdll.cpp for the implementation of this class
//

class CUsingdllApp : public CWinApp
{
public:
	CUsingdllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingdllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUsingdllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGDLL_H__269F218C_465D_4C82_9AE7_619EBA3E799E__INCLUDED_)
