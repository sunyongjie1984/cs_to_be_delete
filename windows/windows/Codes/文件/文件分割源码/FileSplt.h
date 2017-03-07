// FileSplt.h : main header file for the FILESPLT application
//

#if !defined(AFX_FILESPLT_H__7FE4F384_019A_11D5_9005_D288FBFBF7E1__INCLUDED_)
#define AFX_FILESPLT_H__7FE4F384_019A_11D5_9005_D288FBFBF7E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileSpltApp:
// See FileSplt.cpp for the implementation of this class
//

class CFileSpltApp : public CWinApp
{
public:
	CFileSpltApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSpltApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileSpltApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESPLT_H__7FE4F384_019A_11D5_9005_D288FBFBF7E1__INCLUDED_)
