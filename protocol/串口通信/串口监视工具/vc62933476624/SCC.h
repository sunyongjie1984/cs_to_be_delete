// SCC.h : main header file for the SCC application
//

#if !defined(AFX_SCC_H__5D774E98_6E08_464D_849F_5C6A3EC688A9__INCLUDED_)
#define AFX_SCC_H__5D774E98_6E08_464D_849F_5C6A3EC688A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#pragma warning(disable:4146)
#include "GLOBAL.H"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CSCCApp:
// See SCC.cpp for the implementation of this class
//

class CSCCApp : public CWinApp
{
public:
	CSCCApp();
	CRecentFileList* GetFileList(){return m_pRecentFileList;};
	void	RemoveFile(int nIndex){m_pRecentFileList->Remove(nIndex);};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCCApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSCCApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
};

extern CSCCApp theApp;
extern CMainFrame *g_mw;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCC_H__5D774E98_6E08_464D_849F_5C6A3EC688A9__INCLUDED_)
