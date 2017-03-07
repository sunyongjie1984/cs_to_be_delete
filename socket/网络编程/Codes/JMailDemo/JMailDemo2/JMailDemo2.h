// JMailDemo2.h : main header file for the JMAILDEMO2 application
//

#if !defined(AFX_JMAILDEMO2_H__DF50A12A_F5E4_457F_9E0D_8293EAB5B2D0__INCLUDED_)
#define AFX_JMAILDEMO2_H__DF50A12A_F5E4_457F_9E0D_8293EAB5B2D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo2App:
// See JMailDemo2.cpp for the implementation of this class
//

class CJMailDemo2App : public CWinApp
{
public:
	CJMailDemo2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMailDemo2App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJMailDemo2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMAILDEMO2_H__DF50A12A_F5E4_457F_9E0D_8293EAB5B2D0__INCLUDED_)
