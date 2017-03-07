// SafetyCode.h : main header file for the SAFETYCODE application
//

#if !defined(AFX_SAFETYCODE_H__5F044CEF_2AC0_44FE_9506_6BA263F3E14E__INCLUDED_)
#define AFX_SAFETYCODE_H__5F044CEF_2AC0_44FE_9506_6BA263F3E14E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSafetyCodeApp:
// See SafetyCode.cpp for the implementation of this class
//


extern char g_szvariableaddress[MAX_PATH];

#define SHOW_TEST_INFO( szvariableplace , szvariablename , address , value )\
{																			\
	memset ( g_szvariableaddress , 0 , MAX_PATH );							\
																			\
	sprintf (	g_szvariableaddress ,										\
				"%s { %s address : %x |value = %p }\r\n" ,					\
				szvariableplace , szvariablename , address , value );		\
																			\
	::OutputDebugString ( g_szvariableaddress );							\
}


class CSafetyCodeApp : public CWinApp
{
public:
	CSafetyCodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSafetyCodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSafetyCodeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAFETYCODE_H__5F044CEF_2AC0_44FE_9506_6BA263F3E14E__INCLUDED_)
