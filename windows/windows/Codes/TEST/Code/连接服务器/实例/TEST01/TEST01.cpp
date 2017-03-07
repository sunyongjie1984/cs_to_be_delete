#include "stdafx.h"
#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int wmain(int argc, wchar_t *argv[])
{
	DWORD dwLevel = 1008;
	USER_INFO_1008 ui;
	NET_API_STATUS nStatus;
	
	if (argc != 3)
	{
		fwprintf(stderr, L"Usage: %s \\\\ServerName UserName\n", argv[0]);
		exit(1);
	}
	// Fill in the USER_INFO_1008 structure member.
	// UF_SCRIPT: required for LAN Manager 2.0 and
	//  Windows NT and later.
	//
	ui.usri1008_flags = UF_SCRIPT | UF_ACCOUNTDISABLE;
	//
	// Call the NetUserSetInfo function 
	//  to disable the account, specifying level 1008.
	//
	nStatus = NetUserSetInfo(argv[1],
		argv[2],
		dwLevel,
		(LPBYTE)&ui,
		NULL);
	//
	// Display the result of the call.
	//
	if (nStatus == NERR_Success)
		fwprintf(stderr, L"User account %s has been disabled\n", argv[2]);
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
	
	return 0;
}
