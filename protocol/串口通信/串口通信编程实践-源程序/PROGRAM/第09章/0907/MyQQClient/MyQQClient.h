// MyQQClient.h : main header file for the 20043155MYQQCLIENT05 application
//

#if !defined(AFX_20043155MYQQCLIENT05_H__0EA4349B_8B05_4401_968C_6765FB186A8B__INCLUDED_)
#define AFX_20043155MYQQCLIENT05_H__0EA4349B_8B05_4401_968C_6765FB186A8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyMyQQClientApp:
// See MyQQClient.cpp for the implementation of this class
//

class CMyMyQQClientApp : public CWinApp
{
public:
	CMyMyQQClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMyQQClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyMyQQClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_20043155MYQQCLIENT05_H__0EA4349B_8B05_4401_968C_6765FB186A8B__INCLUDED_)
