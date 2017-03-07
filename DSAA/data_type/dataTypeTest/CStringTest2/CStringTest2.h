
// CStringTest2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCStringTest2App:
// See CStringTest2.cpp for the implementation of this class
//

class CCStringTest2App : public CWinAppEx
{
public:
	CCStringTest2App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCStringTest2App theApp;