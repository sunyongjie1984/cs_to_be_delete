#include "stdafx.h"
#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int wmain(int argc, wchar_t *argv[])
{
	DWORD dwLevel = 10;
	LPUSER_INFO_10 pBuf = NULL;
	NET_API_STATUS nStatus;
	
	if (argc != 3)
	{
		fwprintf(stderr, L"Usage: %s \\\\ServerName UserName\n", argv[0]);
		exit(1);
	}
	//
	// Call the NetUserGetInfo function; specify level 10.
	//
	nStatus = NetUserGetInfo(argv[1],
		argv[2],
		dwLevel,
		(LPBYTE *)&pBuf);
	//
	// If the call succeeds, print the user information.
	//
	if (nStatus == NERR_Success)
	{
		if (pBuf != NULL)
		{
			wprintf(L"\n\tAccount:      %s\n", pBuf->usri10_name);
			wprintf(L"\tComment:      %s\n", pBuf->usri10_comment);
			wprintf(L"\tUser comment: %s\n", pBuf->usri10_usr_comment);
			wprintf(L"\tFull name:    %s\n", pBuf->usri10_full_name);
		}
	}
	// Otherwise, print the system error.
	//
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
	//
	// Free the allocated memory.
	//
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	
	return 0;
}
