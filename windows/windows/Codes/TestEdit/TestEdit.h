// TestEdit.h : main header file for the TESTEDIT application
//

#if !defined(AFX_TESTEDIT_H__33B1B48D_3B5F_47A2_AFBF_6406D3E81426__INCLUDED_)
#define AFX_TESTEDIT_H__33B1B48D_3B5F_47A2_AFBF_6406D3E81426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestEditApp:
// See TestEdit.cpp for the implementation of this class
//

class CTestEditApp : public CWinApp
{
public:
	CTestEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTEDIT_H__33B1B48D_3B5F_47A2_AFBF_6406D3E81426__INCLUDED_)
