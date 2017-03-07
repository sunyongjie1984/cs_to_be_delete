// MyQQServer.h : main header file for the 20043155MYQQSERVER05 application
//

#if !defined(AFX_20043155MYQQSERVER05_H__704343F8_43B9_4149_A55D_CF2A8352A42B__INCLUDED_)
#define AFX_20043155MYQQSERVER05_H__704343F8_43B9_4149_A55D_CF2A8352A42B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyMyQQServerApp:
// See MyQQServer.cpp for the implementation of this class
//

class CMyMyQQServerApp : public CWinApp
{
public:
	CPtrList * m_pClientSocketList;//socket¡¥±Ì
	CMyMyQQServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMyQQServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyMyQQServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_20043155MYQQSERVER05_H__704343F8_43B9_4149_A55D_CF2A8352A42B__INCLUDED_)
