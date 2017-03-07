// ttrreer.h : main header file for the TTRREER application
//

#if !defined(AFX_TTRREER_H__EBE804A0_8D5F_4081_860D_C175DEB44FC1__INCLUDED_)
#define AFX_TTRREER_H__EBE804A0_8D5F_4081_860D_C175DEB44FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTtrreerApp:
// See ttrreer.cpp for the implementation of this class
//

class CTtrreerApp : public CWinApp
{
public:
	CTtrreerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTtrreerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTtrreerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTRREER_H__EBE804A0_8D5F_4081_860D_C175DEB44FC1__INCLUDED_)
