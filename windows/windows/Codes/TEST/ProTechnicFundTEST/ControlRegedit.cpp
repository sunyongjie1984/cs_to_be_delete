// ControlRegedit.cpp: implementation of the CControlRegedit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "ControlRegedit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define  BUFSIZE     1024
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CControlRegedit::CControlRegedit()
{

}

CControlRegedit::~CControlRegedit()
{

}

int CControlRegedit::CreateSpecifyRegeditKey(
									 IN		HKEY		hkRootName,
									 IN		LPTSTR		RegKeyPath,
									 IN		LPTSTR		lpSpecifyKeyName,
									 IN     DWORD		dwSpecifyData    )
{
	CHAR					lpSubKey[1024]		 = {0};
	DWORD					Reserved			 = 0;
	LPSTR					lpClass				 = NULL;
	DWORD					dwOptions			 = REG_OPTION_NON_VOLATILE;
	REGSAM					samDesired			 = KEY_WRITE;
	LPSECURITY_ATTRIBUTES	lpSecurityAttributes = NULL;
	HKEY					hkResult;
	LPDWORD					lpdwDisposition		 = 0;

	strcpy( lpSubKey, RegKeyPath );
	
	LONG lStatus = RegCreateKeyEx ( hkRootName,
									lpSubKey,
									Reserved,
									lpClass,
									dwOptions,
									samDesired,
									lpSecurityAttributes,
									&hkResult,
									lpdwDisposition );

	if ( ERROR_SUCCESS != lStatus )
	{
		return -1;
	}

	CHAR  lpValueName[1024] = {0};
	DWORD dwType			= REG_DWORD;
	DWORD dwData			= dwSpecifyData;
	DWORD cbData			= sizeof( DWORD );
	
	strcpy( lpValueName, lpSpecifyKeyName );

	lStatus = RegSetValueEx ( hkResult,
							  lpValueName,
							  Reserved,
							  dwType,
							  (LPBYTE)&dwData,
							  cbData );

	RegCloseKey( hkResult );

	if ( ERROR_SUCCESS != lStatus )
	{
		return -1;
	}

	return 0;
}

int CControlRegedit::ReadSpecifyRegeditKeyValue(
									IN		      HKEY     hkRootName,
									IN		      LPTSTR   lpRegKeyPath,
									IN		      LPTSTR   lpRegSpecifyKeyName,
									IN		OUT   DWORD	  &dwKeyValue )
{
	CHAR	lpSubKey[1024]  = {0};
	DWORD	ulOptions		= 0;
	REGSAM	samDesired      = KEY_READ | KEY_QUERY_VALUE;
	HKEY	hkResult;

	strcpy( lpSubKey, lpRegKeyPath );
	
	LONG lStatus = RegOpenKeyEx ( hkRootName,
								  lpSubKey,
								  ulOptions,
								  samDesired,
								  &hkResult );

	if ( ERROR_SUCCESS != lStatus )
	{
		return -1;
	}

	CHAR		lpValueName[1024] = {0};
	LPDWORD		lpReserved		  = NULL;
	LPDWORD		lpType            = NULL;
	DWORD 		dwData			  = 0;
	DWORD		dwDataLength      = BUFSIZE;
	
	strcpy( lpValueName, lpRegSpecifyKeyName );

	lStatus = RegQueryValueEx ( hkResult,
								lpValueName,
								lpReserved,
								lpType,
								(LPBYTE) &dwData,
								&dwDataLength );

	RegCloseKey( hkResult );

	dwKeyValue = ( DWORD )dwData;

	if ( (ERROR_SUCCESS != lStatus) || (dwData > BUFSIZE) )
	{
		return -1;
	}

	return 0;
}