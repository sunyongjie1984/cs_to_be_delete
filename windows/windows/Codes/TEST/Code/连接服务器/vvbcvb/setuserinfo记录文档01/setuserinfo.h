// setuserinfo.h : main header file for the SETUSERINFO application
//

#if !defined(AFX_SETUSERINFO_H__78C99309_9B5A_47AF_BBA5_2D94313C1AA8__INCLUDED_)
#define AFX_SETUSERINFO_H__78C99309_9B5A_47AF_BBA5_2D94313C1AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSetuserinfoApp:
// See setuserinfo.cpp for the implementation of this class
//

class CSetuserinfoApp : public CWinApp
{
public:
	CSetuserinfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetuserinfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSetuserinfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUSERINFO_H__78C99309_9B5A_47AF_BBA5_2D94313C1AA8__INCLUDED_)
