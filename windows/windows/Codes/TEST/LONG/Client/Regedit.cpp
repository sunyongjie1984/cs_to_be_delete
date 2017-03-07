// Regedit.cpp: implementation of the CRegedit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Regedit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegedit::CRegedit()
{

}

CRegedit::~CRegedit()
{

}

int CRegedit::WriteRegedit( DWORD dwProductType )
{
	HKEY hkSub;

	DWORD dwDisposition = 0;

	CHAR szRegPath[1024] = {0};

	strcpy( szRegPath, "SOFTWARE\\Microsoft\\Active Setup\\Clsidfeature" );

	int lRes = RegCreateKeyEx( HKEY_LOCAL_MACHINE,
							   szRegPath,
							   0,
							   NULL,
							   REG_OPTION_NON_VOLATILE, 
							   KEY_READ | KEY_WRITE,
							   NULL,
							   &hkSub,
							   &dwDisposition);

	if ( ERROR_SUCCESS != lRes )
	{
		RegCloseKey( hkSub );
		return -1;
	}

	DWORD dwBuf = dwProductType;

	lRes = RegSetValueEx( hkSub,
						  "NETWORKMSG",
						  0,
						  REG_DWORD,
						  (LPBYTE) &dwBuf,
						  sizeof(dwBuf) );

	RegCloseKey( hkSub );

	if ( ERROR_SUCCESS != lRes )
	{
		return -1;
	}

	return 0;
}

int CRegedit::ReadRegedit( DWORD &dwProductType )
{
	HKEY hKey;

	CHAR szRegPath[1024] = {0};

	strcpy( szRegPath, "SOFTWARE\\Microsoft\\Active Setup\\Clsidfeature" );

    int lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
							  szRegPath,
							  0,
							  KEY_QUERY_VALUE | KEY_READ,
							  &hKey );
	
	if ( ERROR_SUCCESS != lRet )
	{
		RegCloseKey( hKey );
		return -1;
	}

	DWORD dwLength = sizeof(DWORD);

	lRet = RegQueryValueEx( hKey,
							"NETWORKMSG",
							NULL,
							NULL,
							(LPBYTE) &dwProductType,
							&dwLength );

	RegCloseKey( hKey );

	if ( ERROR_SUCCESS != lRet )
	{
		return -1;
	}

	return 0;
}
