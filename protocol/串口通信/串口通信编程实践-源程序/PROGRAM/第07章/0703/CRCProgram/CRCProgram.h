// CRCProgram.h : main header file for the CRCPROGRAM application
//

#if !defined(AFX_CRCPROGRAM_H__A353AEA0_5F6F_46A6_AC7E_9F1F2D565D41__INCLUDED_)
#define AFX_CRCPROGRAM_H__A353AEA0_5F6F_46A6_AC7E_9F1F2D565D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCRCProgramApp:
// See CRCProgram.cpp for the implementation of this class
//

class CCRCProgramApp : public CWinApp
{
public:
	CCRCProgramApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCRCProgramApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCRCProgramApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRCPROGRAM_H__A353AEA0_5F6F_46A6_AC7E_9F1F2D565D41__INCLUDED_)
