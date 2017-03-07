// PowerOff.h : main header file for the POWEROFF application
//

#if !defined(AFX_POWEROFF_H__B9D80FA6_5C5B_4F7D_9DEB_187789EE8F55__INCLUDED_)
#define AFX_POWEROFF_H__B9D80FA6_5C5B_4F7D_9DEB_187789EE8F55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPowerOffApp:
// See PowerOff.cpp for the implementation of this class
//

class CPowerOffApp : public CWinApp
{
public:
	CPowerOffApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerOffApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPowerOffApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWEROFF_H__B9D80FA6_5C5B_4F7D_9DEB_187789EE8F55__INCLUDED_)
