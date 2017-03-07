// FileOperate.h : main header file for the FILEOPERATE application
//

#if !defined(AFX_FILEOPERATE_H__3540DB72_D849_46AB_ABF0_AF0262BCC425__INCLUDED_)
#define AFX_FILEOPERATE_H__3540DB72_D849_46AB_ABF0_AF0262BCC425__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileOperateApp:
// See FileOperate.cpp for the implementation of this class
//

class CFileOperateApp : public CWinApp
{
public:
	CFileOperateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileOperateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileOperateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEOPERATE_H__3540DB72_D849_46AB_ABF0_AF0262BCC425__INCLUDED_)
