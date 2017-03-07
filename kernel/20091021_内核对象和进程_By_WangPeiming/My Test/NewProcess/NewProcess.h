// NewProcess.h : main header file for the NEWPROCESS application
//

#if !defined(AFX_NEWPROCESS_H__FCB8834C_0DDA_4C45_AC0D_3980881F1079__INCLUDED_)
#define AFX_NEWPROCESS_H__FCB8834C_0DDA_4C45_AC0D_3980881F1079__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNewProcessApp:
// See NewProcess.cpp for the implementation of this class
//

class CNewProcessApp : public CWinApp
{
public:
	CNewProcessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProcessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNewProcessApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROCESS_H__FCB8834C_0DDA_4C45_AC0D_3980881F1079__INCLUDED_)
