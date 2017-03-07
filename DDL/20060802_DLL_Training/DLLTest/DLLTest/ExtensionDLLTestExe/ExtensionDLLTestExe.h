// ExtensionDLLTestExe.h : main header file for the EXTENSIONDLLTESTEXE application
//

#if !defined(AFX_EXTENSIONDLLTESTEXE_H__4429706B_913D_40CC_9229_57E024F4A578__INCLUDED_)
#define AFX_EXTENSIONDLLTESTEXE_H__4429706B_913D_40CC_9229_57E024F4A578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../Include/ExtensionDLLTest/resource.h"		// main symbols

// CExtensionDLLTestExeApp:
// See ExtensionDLLTestExe.cpp for the implementation of this class
//

class CExtensionDLLTestExeApp : public CWinApp
{
public:
	CExtensionDLLTestExeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtensionDLLTestExeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExtensionDLLTestExeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENSIONDLLTESTEXE_H__4429706B_913D_40CC_9229_57E024F4A578__INCLUDED_)
