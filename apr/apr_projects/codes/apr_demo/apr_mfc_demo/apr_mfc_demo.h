// apr_mfc_demo.h : main header file for the APR_MFC_DEMO application
//

#if !defined(AFX_APR_MFC_DEMO_H__7A56EB04_0436_4CC8_BBA1_7D0ED557DE7B__INCLUDED_)
#define AFX_APR_MFC_DEMO_H__7A56EB04_0436_4CC8_BBA1_7D0ED557DE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CApr_mfc_demoApp:
// See apr_mfc_demo.cpp for the implementation of this class
//

class CApr_mfc_demoApp : public CWinApp
{
public:
	CApr_mfc_demoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApr_mfc_demoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CApr_mfc_demoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APR_MFC_DEMO_H__7A56EB04_0436_4CC8_BBA1_7D0ED557DE7B__INCLUDED_)
