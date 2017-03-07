// Spar.h : main header file for the SPAR application
//

#if !defined(AFX_SPAR_H__B0257A0F_3EC2_41A9_82DF_2B2B7FD3D120__INCLUDED_)
#define AFX_SPAR_H__B0257A0F_3EC2_41A9_82DF_2B2B7FD3D120__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSparApp:
// See Spar.cpp for the implementation of this class
//

class CSparApp : public CWinApp
{
public:
	CSparApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSparApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSparApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPAR_H__B0257A0F_3EC2_41A9_82DF_2B2B7FD3D120__INCLUDED_)
