// IsClientEnterDomain1.cpp: implementation of the IsClientEnterDomain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IsClientEnterDomain.h"
#include "globalfunc.h"

#include "Lm.h"
#include "Lmjoin.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIsClientEnterDomain::CIsClientEnterDomain()
{

}

CIsClientEnterDomain::~CIsClientEnterDomain()
{

}

typedef NET_API_STATUS (__stdcall *P_NetApiBufferAllocate)(DWORD ByteCount, LPVOID *Buffer);
typedef NET_API_STATUS (__stdcall *P_NetGetJoinInformation)(LPCWSTR lpServer, LPWSTR *lpNameBuffer, PNETSETUP_JOIN_STATUS BufferType);
typedef NET_API_STATUS (__stdcall *P_NetApiBufferFree)(LPVOID Buffer);


int CIsClientEnterDomain::GetGroupInfo(LPSTR strServerName, UINT *uType)
{
	LPWSTR buffer = NULL;
	ZeroMemory(strServerName,_tcslen(strServerName));
	WCHAR pszServerName[MAX_PATH]={0};

	HMODULE hLoad = ::LoadLibrary("Netapi32.dll");
	if(!hLoad)
	{
		int iErrorCode = ::GetLastError();
		LogError(0x19780827, "CIsClientEnterDomain::GetGroupInfo LoadLibrary Error is: %d", iErrorCode);
		return -1;
	}

	P_NetApiBufferAllocate pNetApiBufferAllocate = (P_NetApiBufferAllocate)::GetProcAddress(hLoad, "NetApiBufferAllocate");
	P_NetGetJoinInformation pNetGetJoinInformation = (P_NetGetJoinInformation)::GetProcAddress(hLoad, "NetGetJoinInformation");
	P_NetApiBufferFree pNetApiBufferFree = (P_NetApiBufferFree)::GetProcAddress(hLoad, "NetApiBufferFree");
	if(!pNetApiBufferAllocate)
	{
		return -1;
	}
	if(!pNetGetJoinInformation)
	{
		return -1;
	}
	if(!pNetApiBufferFree)
	{
		return -1;
	}

	DWORD Kc = MultiByteToWideChar(CP_ACP, 0, strServerName, -1, pszServerName,	sizeof(pszServerName));
	NET_API_STATUS net = pNetApiBufferAllocate(1024,(LPVOID*)&buffer);	
	if(net != NERR_Success)		
	{		
		return net;		
	}	
	NETSETUP_JOIN_STATUS netStatus;	
	net = pNetGetJoinInformation(NULL,&buffer,&netStatus);	
	if(net != NERR_Success)		
	{		
		net = pNetApiBufferFree((LPVOID*)buffer);		
		if(net != NERR_Success)			
		{			
			return net;			
		}		
		return net;		
	}	
	DWORD rc = WideCharToMultiByte(CP_ACP,0,buffer,-1,strServerName,256,NULL,NULL);	
	if(rc==0)		
	{		
		int error = GetLastError();		
		net = pNetApiBufferFree((LPVOID*)buffer);		
		if(net != NERR_Success)			
		{
			return net;
		}
		return error;		
	}	
	if(netStatus == NetSetupWorkgroupName)	
	{
		*uType = JOIN_GROUP;//The computer is joined to a workgroup
        return JOIN_GROUP;
	}	
	else if(netStatus == NetSetupDomainName)		
	{	
		*uType = JOIN_DOMAIN;//The computer is joined to a domain
         return JOIN_DOMAIN;
	}
	else		
	{
		*uType = NOT_JOIN;
		return NOT_JOIN;
	}
	net = pNetApiBufferFree((LPVOID*)buffer);	
	if(net != NERR_Success)		
	{		
		return net;		
	}	
	return 0;
}

typedef BOOL (__stdcall *P_VerifyVersionInfo)(
					   LPOSVERSIONINFOEX lpVersionInfo,  // version info 
					   DWORD dwTypeMask,                 // attributes
					   DWORDLONG dwlConditionMask        // comparison type
					   );

typedef ULONGLONG (__stdcall *P_VER_SET_CONDITION)(
									ULONGLONG dwlConditionMask,  // mask whose bits are set
									DWORD dwTypeBitMask,         // type of attribute
									BYTE dwConditionMask         // type of comparison
									);

int CIsClientEnterDomain::Is_Win2000_DomainController()
{
	OSVERSIONINFOEX osvi;
	ULONGLONG dwlConditionMask = 0;
	// Initialize the OSVERSIONINFOEX structure.
	//向一个内存块中填充0
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.dwMajorVersion = 5;
	osvi.wProductType = VER_NT_DOMAIN_CONTROLLER;

	HMODULE	hLoad = ::LoadLibrary("Kernel32.dll");
	if(!hLoad)
	{
		int iErrorCode = ::GetLastError();
		LogError(0x19780827, "CIsClientEnterDomain::Is_Win2000_DomainController() LoadLibrary() Error is: %d", iErrorCode);
		return -1;
	}

	P_VER_SET_CONDITION	pVER_SET_CONDITION = (P_VER_SET_CONDITION)::GetProcAddress(hLoad, "VerSetConditionMask");
	if(!pVER_SET_CONDITION)
	{
		int iErrorCode = ::GetLastError();
		LogError(0x19780827, "CIsClientEnterDomain::Is_Win2000_DomainController() GetProcAddress() Error is: %d", iErrorCode);
		return -1;
	}

	// Initialize the condition mask.
	dwlConditionMask = pVER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL );
	dwlConditionMask = pVER_SET_CONDITION( dwlConditionMask, VER_PRODUCT_TYPE, VER_EQUAL );
	
	// Perform the test.
	//VerifyVersionInfo检查主版本号、次版本号以及服务包。

	P_VerifyVersionInfo pVerifyVersionInfo = (P_VerifyVersionInfo)::GetProcAddress(hLoad, "VerifyVersionInfoA");
	if(!pVerifyVersionInfo)
	{
		int iErrorCode = ::GetLastError();
		LogError(0x19780827, "CIsClientEnterDomain::Is_Win2000_DomainController() VerifyVersionInfo() Error is: %d", iErrorCode);
		return -1;
	}
	BOOL bRet = pVerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_PRODUCT_TYPE, dwlConditionMask);

	return bRet;
}

BOOL CIsClientEnterDomain::IsEnterDomain()
{
	
	HKEY hKey = HKEY_LOCAL_MACHINE;
	CStdString strSubKey = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\winlogon");
	HKEY hNewKey = 0;
	LONG lResult = ERROR_SUCCESS;
	lResult = ::RegOpenKeyEx(hKey, 
		strSubKey, 
		0,
		KEY_READ, 
		&hNewKey);
	if(ERROR_SUCCESS != lResult)
	{
		char ch[256] = {0};
		RegCloseKey(hKey);
		RegCloseKey(hNewKey);			
		return FALSE;
	}
	DWORD dwLp = 1000;
	DWORD dwRegType = REG_SZ;
	unsigned char bRtn[100] = {0};
	
	lResult = ::RegQueryValueEx(hNewKey, 
		"AltDefaultDomainName", 
		NULL, 
		&dwRegType, 
		bRtn, 
		&dwLp);
	
	if(ERROR_SUCCESS != lResult)
	{
		RegCloseKey(hKey);
		::MessageBox(NULL, "函数执行失败", NULL, NULL);
		return FALSE;
	}	
	RegCloseKey(hNewKey);
	RegCloseKey(hKey);	
	TCHAR lpBuffer[100];
	DWORD lpnSize=MAX_PATH;
	GetComputerName(lpBuffer, //  LPTSTR
		            &lpnSize  ); //LPDWORD
	CStdString str;
	str.Format("%s",lpBuffer);
	
	
	if (strcmp((char*)bRtn, str.c_str()) == 0) 
	{
		return FALSE;//enter oneself
	}
	else
	{
		return TRUE;//enter DNS server
	}
}

BOOL CIsClientEnterDomain::GetEnterType()//If the client enter DNS server ,The return values is TRUE . 
{
	BYTE btOsVersion = 0;
	GetOsVersion(btOsVersion);
	if(OS_WIN_98 == btOsVersion || OS_WIN_ME == btOsVersion)
	{
		LogError(0x19780827, "OS Version is: Windows 9x");
		return FALSE;
	}
	else if (1 == Is_Win2000_DomainController()) 
	{   		  
		return FALSE;	// Domain Server
	}
	UINT uType = 0;
	char Servernameinfo[100] = {0};
	if(JOIN_DOMAIN != GetGroupInfo(Servernameinfo, &uType)) 
	{ 
		return FALSE;//The currently computer do not join DNS server
	}
	if(!IsEnterDomain())
	{
		return FALSE;//登录本地
	}
	return TRUE;
}