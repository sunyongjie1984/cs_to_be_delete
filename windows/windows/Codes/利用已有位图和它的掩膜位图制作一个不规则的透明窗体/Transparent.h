// Transparent.h : main header file for the TRANSPARENT application
//

#if !defined(AFX_TRANSPARENT_H__0310EC95_8874_11D2_8313_00001C1A90C9__INCLUDED_)
#define AFX_TRANSPARENT_H__0310EC95_8874_11D2_8313_00001C1A90C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransparentApp:
// See Transparent.cpp for the implementation of this class
//

class CTransparentApp : public CWinApp
{
public:
	CTransparentApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CTransparentApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENT_H__0310EC95_8874_11D2_8313_00001C1A90C9__INCLUDED_)
