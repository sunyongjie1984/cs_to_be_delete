// JMailDemo1.h : main header file for the JMAILDEMO1 application
//

#if !defined(AFX_JMAILDEMO1_H__86691D45_82F3_4D64_ADE6_80DE3364D461__INCLUDED_)
#define AFX_JMAILDEMO1_H__86691D45_82F3_4D64_ADE6_80DE3364D461__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJMailDemo1App:
// See JMailDemo1.cpp for the implementation of this class
//

class CJMailDemo1App : public CWinApp
{
public:
	CJMailDemo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMailDemo1App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJMailDemo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMAILDEMO1_H__86691D45_82F3_4D64_ADE6_80DE3364D461__INCLUDED_)
