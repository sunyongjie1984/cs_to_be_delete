// SimpleClient.h : main header file for the SIMPLECLIENT application
//

#if !defined(AFX_SIMPLECLIENT_H__5190B471_074D_4564_A369_9AF7AF43C6D4__INCLUDED_)
#define AFX_SIMPLECLIENT_H__5190B471_074D_4564_A369_9AF7AF43C6D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleClientApp:
// See SimpleClient.cpp for the implementation of this class
//

class CSimpleClientApp : public CWinApp
{
public:
	CSimpleClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSimpleClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLECLIENT_H__5190B471_074D_4564_A369_9AF7AF43C6D4__INCLUDED_)
