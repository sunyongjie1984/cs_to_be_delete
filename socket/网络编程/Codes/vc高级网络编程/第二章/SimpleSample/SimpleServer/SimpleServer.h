// SimpleServer.h : main header file for the SIMPLESERVER application
//

#if !defined(AFX_SIMPLESERVER_H__9B0F6115_D054_49C6_8D64_4C07B310706C__INCLUDED_)
#define AFX_SIMPLESERVER_H__9B0F6115_D054_49C6_8D64_4C07B310706C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleServerApp:
// See SimpleServer.cpp for the implementation of this class
//

class CSimpleServerApp : public CWinApp
{
public:
	CSimpleServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSimpleServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLESERVER_H__9B0F6115_D054_49C6_8D64_4C07B310706C__INCLUDED_)
