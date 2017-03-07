// NewTab.h : main header file for the NEWTAB application
//

#if !defined(AFX_NEWTAB_H__349A5602_2241_40F4_BA71_6A3A2EDC351B__INCLUDED_)
#define AFX_NEWTAB_H__349A5602_2241_40F4_BA71_6A3A2EDC351B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNewTabApp:
// See NewTab.cpp for the implementation of this class
//

class CNewTabApp : public CWinApp
{
public:
	CNewTabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewTabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNewTabApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTAB_H__349A5602_2241_40F4_BA71_6A3A2EDC351B__INCLUDED_)
