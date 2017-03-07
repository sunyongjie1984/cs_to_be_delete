// SehDemo.h : main header file for the SEHDEMO application
//

#if !defined(AFX_SEHDEMO_H__5E0D0697_113F_11D3_AFC2_0080ADB99E81__INCLUDED_)
#define AFX_SEHDEMO_H__5E0D0697_113F_11D3_AFC2_0080ADB99E81__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSehDemoApp:
// See SehDemo.cpp for the implementation of this class
//

class CSehDemoApp : public CWinApp
{
public:
	CSehDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSehDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSehDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEHDEMO_H__5E0D0697_113F_11D3_AFC2_0080ADB99E81__INCLUDED_)
