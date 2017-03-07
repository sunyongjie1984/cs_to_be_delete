// WhoSLocking.h : main header file for the WHOSLOCKING application
//

#if !defined(AFX_WHOSLOCKING_H__285A0381_A959_11D3_BFE4_0010E3B966CE__INCLUDED_)
#define AFX_WHOSLOCKING_H__285A0381_A959_11D3_BFE4_0010E3B966CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWhoSLockingApp:
// See WhoSLocking.cpp for the implementation of this class
//

class CWhoSLockingApp : public CWinApp
{
public:
	BOOL ShellRegister(LPCTSTR lpszApplicationName, LPCTSTR lpszRegistryClass, LPCTSTR lpszFileDescription = NULL, LPCTSTR lpszFileExtension = NULL, LPCTSTR lpszMimeType = NULL, LPCTSTR lpszDefaultIcon = NULL);
	CWhoSLockingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhoSLockingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWhoSLockingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHOSLOCKING_H__285A0381_A959_11D3_BFE4_0010E3B966CE__INCLUDED_)
