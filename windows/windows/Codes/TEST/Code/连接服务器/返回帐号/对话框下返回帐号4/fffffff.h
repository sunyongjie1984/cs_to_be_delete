// fffffff.h : main header file for the FFFFFFF application
//

#if !defined(AFX_FFFFFFF_H__FE7E79C5_960B_4BB1_A91F_94ECC0E7F249__INCLUDED_)
#define AFX_FFFFFFF_H__FE7E79C5_960B_4BB1_A91F_94ECC0E7F249__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFffffffApp:
// See fffffff.cpp for the implementation of this class
//

class CFffffffApp : public CWinApp
{
public:
	CFffffffApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFffffffApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFffffffApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFFFFFF_H__FE7E79C5_960B_4BB1_A91F_94ECC0E7F249__INCLUDED_)
