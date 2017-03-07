// testiocp.h : main header file for the TESTIOCP application
//

#if !defined(AFX_TESTIOCP_H__43925B22_6329_4E7E_B19C_6E2D277B60D6__INCLUDED_)
#define AFX_TESTIOCP_H__43925B22_6329_4E7E_B19C_6E2D277B60D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestiocpApp:
// See testiocp.cpp for the implementation of this class
//

class CTestiocpApp : public CWinApp
{
public:
	CTestiocpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestiocpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestiocpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTIOCP_H__43925B22_6329_4E7E_B19C_6E2D277B60D6__INCLUDED_)
