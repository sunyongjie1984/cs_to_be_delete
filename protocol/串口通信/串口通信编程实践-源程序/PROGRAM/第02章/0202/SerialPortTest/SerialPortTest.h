// SerialPortTest.h : main header file for the SERIALPORTTEST application
//

#if !defined(AFX_SERIALPORTTEST_H__556B3D04_5375_11D8_870F_00E04C3F78CA__INCLUDED_)
#define AFX_SERIALPORTTEST_H__556B3D04_5375_11D8_870F_00E04C3F78CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSerialPortTestApp:
// See SerialPortTest.cpp for the implementation of this class
//

class CSerialPortTestApp : public CWinApp
{
public:
	CSerialPortTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialPortTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerialPortTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALPORTTEST_H__556B3D04_5375_11D8_870F_00E04C3F78CA__INCLUDED_)
