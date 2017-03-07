// TestCreateThreadAndProcess.h : main header file for the TESTCREATETHREADANDPROCESS application
//

#if !defined(AFX_TESTCREATETHREADANDPROCESS_H__57C49AC9_5593_4785_A050_55DBE2A9966E__INCLUDED_)
#define AFX_TESTCREATETHREADANDPROCESS_H__57C49AC9_5593_4785_A050_55DBE2A9966E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCreateThreadAndProcessApp:
// See TestCreateThreadAndProcess.cpp for the implementation of this class
//

class CTestCreateThreadAndProcessApp : public CWinApp
{
public:
	CTestCreateThreadAndProcessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCreateThreadAndProcessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestCreateThreadAndProcessApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCREATETHREADANDPROCESS_H__57C49AC9_5593_4785_A050_55DBE2A9966E__INCLUDED_)
