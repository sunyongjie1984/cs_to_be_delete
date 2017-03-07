// ReadSector.h : main header file for the READSECTOR application
//

#if !defined(AFX_READSECTOR_H__78EC8972_9208_4166_82E8_70C62234A651__INCLUDED_)
#define AFX_READSECTOR_H__78EC8972_9208_4166_82E8_70C62234A651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReadSectorApp:
// See ReadSector.cpp for the implementation of this class
//

class CReadSectorApp : public CWinApp
{
public:
	CReadSectorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadSectorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReadSectorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READSECTOR_H__78EC8972_9208_4166_82E8_70C62234A651__INCLUDED_)
