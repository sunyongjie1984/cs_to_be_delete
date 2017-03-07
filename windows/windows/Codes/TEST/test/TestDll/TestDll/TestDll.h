// TestDll.h : main header file for the TestDll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CTestDllApp
// See TestDll.cpp for the implementation of this class
//

class CTestDllApp : public CWinApp
{
public:
	CTestDllApp();

// Overrides
public:
	virtual BOOL InitInstance();

public:
	//Š÷Ší–¼
	char* GetHostName(void);
	//Œn??Œ^
	char* GetSystemType(void);
	//IP’nš¬
	void GetIPAddressList(char ** lpIPList, DWORD *lpNumber);

	DECLARE_MESSAGE_MAP()
};
