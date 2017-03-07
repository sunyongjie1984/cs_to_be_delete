// printer.h : main header file for the PRINTER application
//

#if !defined(AFX_PRINTER_H__B2586692_879B_4CF7_B936_57FC1A395CAA__INCLUDED_)
#define AFX_PRINTER_H__B2586692_879B_4CF7_B936_57FC1A395CAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrinterApp:
// See printer.cpp for the implementation of this class
//

class CPrinterApp : public CWinApp
{
public:
	CPrinterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPrinterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTER_H__B2586692_879B_4CF7_B936_57FC1A395CAA__INCLUDED_)
