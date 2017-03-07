// CockFight.h : main header file for the COCKFIGHT application
//

#if !defined(AFX_COCKFIGHT_H__4AA485EB_9899_41E7_91A0_B76B796AAFBA__INCLUDED_)
#define AFX_COCKFIGHT_H__4AA485EB_9899_41E7_91A0_B76B796AAFBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCockFightApp:
// See CockFight.cpp for the implementation of this class
//

class CCockFightApp : public CWinApp
{
public:
	CCockFightApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCockFightApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCockFightApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COCKFIGHT_H__4AA485EB_9899_41E7_91A0_B76B796AAFBA__INCLUDED_)
