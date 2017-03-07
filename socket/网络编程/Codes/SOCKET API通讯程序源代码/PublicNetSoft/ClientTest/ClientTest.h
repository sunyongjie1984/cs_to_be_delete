// ClientTest.h : main header file for the CLIENTTEST application
//

#if !defined(AFX_CLIENTTEST_H__6C96BD18_8966_436A_8415_748E9D41042F__INCLUDED_)
#define AFX_CLIENTTEST_H__6C96BD18_8966_436A_8415_748E9D41042F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientTestApp:
// See ClientTest.cpp for the implementation of this class
//

class CClientTestApp : public CWinApp
{
public:
	CClientTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTTEST_H__6C96BD18_8966_436A_8415_748E9D41042F__INCLUDED_)
