// Crude Debugger.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCrudeDebuggerApp:
// See Crude Debugger.cpp for the implementation of this class
//

class CCrudeDebuggerApp : public CWinApp
{
public:
	CCrudeDebuggerApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCrudeDebuggerApp theApp;