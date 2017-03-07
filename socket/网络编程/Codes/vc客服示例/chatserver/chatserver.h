// chatserver.h : main header file for the CHATSERVER application
//

#if !defined(AFX_CHATSERVER_H__36649B73_396E_44AD_B7B6_7D860AABCBC8__INCLUDED_)
#define AFX_CHATSERVER_H__36649B73_396E_44AD_B7B6_7D860AABCBC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatserverApp:
// See chatserver.cpp for the implementation of this class
//

class CChatserverApp : public CWinApp
{
public:
	CChatserverApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatserverApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CChatserverApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSERVER_H__36649B73_396E_44AD_B7B6_7D860AABCBC8__INCLUDED_)
