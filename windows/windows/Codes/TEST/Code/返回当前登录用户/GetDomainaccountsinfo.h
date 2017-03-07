// GetDomainaccountsinfo.h : main header file for the GETDOMAINACCOUNTSINFO application
//

#if !defined(AFX_GETDOMAINACCOUNTSINFO_H__9E3CC7CA_880B_4875_B580_E144262EDD6C__INCLUDED_)
#define AFX_GETDOMAINACCOUNTSINFO_H__9E3CC7CA_880B_4875_B580_E144262EDD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetDomainaccountsinfoApp:
// See GetDomainaccountsinfo.cpp for the implementation of this class
//

class CGetDomainaccountsinfoApp : public CWinApp
{
public:
	CGetDomainaccountsinfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetDomainaccountsinfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetDomainaccountsinfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETDOMAINACCOUNTSINFO_H__9E3CC7CA_880B_4875_B580_E144262EDD6C__INCLUDED_)
