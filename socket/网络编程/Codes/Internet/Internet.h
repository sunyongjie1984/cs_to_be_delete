// Internet.h : main header file for the INTERNET application
//

#if !defined(AFX_INTERNET_H__58AE3702_C7D3_4ADA_9F9A_D156FA55574C__INCLUDED_)
#define AFX_INTERNET_H__58AE3702_C7D3_4ADA_9F9A_D156FA55574C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInternetApp:
// See Internet.cpp for the implementation of this class
//

class CInternetApp : public CWinApp
{
public:
	CInternetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInternetApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERNET_H__58AE3702_C7D3_4ADA_9F9A_D156FA55574C__INCLUDED_)
