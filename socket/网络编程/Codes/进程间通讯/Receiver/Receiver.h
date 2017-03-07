// Receiver.h : main header file for the RECEIVER application
//

#if !defined(AFX_RECEIVER_H__780E9E73_93EF_4C29_8E12_FEEFE8CD81AC__INCLUDED_)
#define AFX_RECEIVER_H__780E9E73_93EF_4C29_8E12_FEEFE8CD81AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CReceiverApp:
// See Receiver.cpp for the implementation of this class
//

class CReceiverApp : public CWinApp
{
public:
	CReceiverApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReceiverApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CReceiverApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVER_H__780E9E73_93EF_4C29_8E12_FEEFE8CD81AC__INCLUDED_)
