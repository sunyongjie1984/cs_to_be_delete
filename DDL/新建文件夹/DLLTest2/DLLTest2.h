// DLLTest2.h : main header file for the DLLTEST2 application
//

#if !defined(AFX_DLLTEST2_H__F7257153_F23D_491C_9461_473D618E158F__INCLUDED_)
#define AFX_DLLTEST2_H__F7257153_F23D_491C_9461_473D618E158F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDLLTest2App:
// See DLLTest2.cpp for the implementation of this class
//

class CDLLTest2App : public CWinApp
{
public:
	CDLLTest2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLTest2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDLLTest2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLTEST2_H__F7257153_F23D_491C_9461_473D618E158F__INCLUDED_)
