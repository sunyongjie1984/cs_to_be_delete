// SDF.h : main header file for the SDF application
//

#if !defined(AFX_SDF_H__72590792_05F6_47F5_A2E7_0470D1BCDE0D__INCLUDED_)
#define AFX_SDF_H__72590792_05F6_47F5_A2E7_0470D1BCDE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSDFApp:
// See SDF.cpp for the implementation of this class
//

class CSDFApp : public CWinApp
{
public:
	CSDFApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDFApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSDFApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDF_H__72590792_05F6_47F5_A2E7_0470D1BCDE0D__INCLUDED_)
