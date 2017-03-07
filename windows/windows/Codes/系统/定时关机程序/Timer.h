// Timer.h : main header file for the TIMER application
//

#if !defined(AFX_TIMER_H__8407C74A_DDF0_4BEF_A4EC_302A28E42F02__INCLUDED_)
#define AFX_TIMER_H__8407C74A_DDF0_4BEF_A4EC_302A28E42F02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTimerApp:
// See Timer.cpp for the implementation of this class
//

class CTimerApp : public CWinApp
{
public:
	CTimerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTimerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMER_H__8407C74A_DDF0_4BEF_A4EC_302A28E42F02__INCLUDED_)
