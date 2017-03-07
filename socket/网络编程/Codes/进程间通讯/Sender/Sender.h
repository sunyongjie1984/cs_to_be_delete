// Sender.h : main header file for the SENDER application
//

#if !defined(AFX_SENDER_H__F7B3A83B_016A_49D1_9B54_328F9781E00C__INCLUDED_)
#define AFX_SENDER_H__F7B3A83B_016A_49D1_9B54_328F9781E00C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSenderApp:
// See Sender.cpp for the implementation of this class
//

class CSenderApp : public CWinApp
{
public:
	CSenderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSenderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSenderApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDER_H__F7B3A83B_016A_49D1_9B54_328F9781E00C__INCLUDED_)
