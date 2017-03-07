// PrinterSelect.h : main header file for the PRINTERSELECT application
//

#if !defined(AFX_PRINTERSELECT_H__25391385_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_)
#define AFX_PRINTERSELECT_H__25391385_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "EnumPrinters.h"

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectApp:
// See PrinterSelect.cpp for the implementation of this class
//

class CPrinterSelectApp : public CWinApp
{
public:
	CPrinterSelectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterSelectApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	CEnumPrinters	m_PrinterControl ;
	void			SetPrintOrientation(int mode) ;
	CString			GetDefaultPrinter() ;
	bool			SetNewPrinter(int index) ;

// Implementation
	//{{AFX_MSG(CPrinterSelectApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERSELECT_H__25391385_5DD8_11D6_AD8E_00B0D0652E95__INCLUDED_)
