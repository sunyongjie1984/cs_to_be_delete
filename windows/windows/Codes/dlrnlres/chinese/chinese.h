// chinese.h : main header file for the CHINESE DLL
//

#if !defined(AFX_CHINESE_H__6A15D4D0_FB94_4809_87EC_8FDFB7549477__INCLUDED_)
#define AFX_CHINESE_H__6A15D4D0_FB94_4809_87EC_8FDFB7549477__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChineseApp
// See chinese.cpp for the implementation of this class
//

class CChineseApp : public CWinApp
{
public:
	CChineseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChineseApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CChineseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHINESE_H__6A15D4D0_FB94_4809_87EC_8FDFB7549477__INCLUDED_)
