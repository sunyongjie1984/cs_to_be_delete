// PublicNetSoft.h : main header file for the PUBLICNETSOFT application
//

#if !defined(AFX_PUBLICNETSOFT_H__743C2352_715E_4985_AC76_029AE4D2BDEE__INCLUDED_)
#define AFX_PUBLICNETSOFT_H__743C2352_715E_4985_AC76_029AE4D2BDEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPublicNetSoftApp:
// See PublicNetSoft.cpp for the implementation of this class
//

class CPublicNetSoftApp : public CWinApp
{
public:
	CPublicNetSoftApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPublicNetSoftApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPublicNetSoftApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUBLICNETSOFT_H__743C2352_715E_4985_AC76_029AE4D2BDEE__INCLUDED_)
