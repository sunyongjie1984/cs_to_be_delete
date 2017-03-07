// IsClientEnterDomain1.cpp: implementation of the IsClientEnterDomain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IsClientEnterDomain.h"

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

IsClientEnterDomain::IsClientEnterDomain()
{

}

IsClientEnterDomain::~IsClientEnterDomain()
{

}
int IsClientEnterDomain::GetGroupInfo(LPSTR strServerName, UINT *uType)
{
	LPWSTR buffer;
	 ZeroMemory(strServerName,_tcslen(strServerName));
	WCHAR pszServerName[MAX_PATH]={0};
	DWORD Kc = MultiByteToWideChar(CP_ACP, 
		0, 
		strServerName,
		-1,	
		pszServerName,
		sizeof(pszServerName));
	NET_API_STATUS net = NetApiBufferAllocate(1024,(LPVOID*)&buffer);	
	if(net != NERR_Success)		
	{		
		return net;		
	}	
	NETSETUP_JOIN_STATUS netStatus;	
	net = NetGetJoinInformation(NULL,&buffer,&netStatus);	
	if(net != NERR_Success)		
	{		
		net = NetApiBufferFree((LPVOID*)buffer);		
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
		net = NetApiBufferFree((LPVOID*)buffer);		
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
	net = NetApiBufferFree((LPVOID*)buffer);	
	if(net != NERR_Success)		
	{		
		return net;		
	}	
	return 0;
}

BOOL IsClientEnterDomain::Is_Win2000_DomainController()
{
	OSVERSIONINFOEX osvi;
	DWORDLONG dwlConditionMask = 0;
	
	// Initialize the OSVERSIONINFOEX structure.
	//向一个内存块中填充0
	ZeroMemory(&osvi,//指向需填充内存块的起置指针
		sizeof(OSVERSIONINFOEX));//内存块大小
	
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.dwMajorVersion = 5;
	osvi.wProductType = VER_NT_DOMAIN_CONTROLLER;
	
	// Initialize the condition mask.
	VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, 
		VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_PRODUCT_TYPE, 
		VER_EQUAL );
	
	// Perform the test.
	//VerifyVersionInfo检查主版本号、次版本号以及服务包。
	return VerifyVersionInfo(&osvi, 
		VER_MAJORVERSION | VER_PRODUCT_TYPE,
		dwlConditionMask);
	
}

BOOL IsClientEnterDomain::IsEnterDomain()
{
	
	HKEY hKey = HKEY_LOCAL_MACHINE;
	CString strSubKey = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\winlogon");
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
		AfxMessageBox("函数执行失败");
		return FALSE;
	}	
	RegCloseKey(hNewKey);
	RegCloseKey(hKey);	
	TCHAR lpBuffer[100];
	DWORD lpnSize=MAX_PATH;
	GetComputerName(lpBuffer, //  LPTSTR
		            &lpnSize  ); //LPDWORD
	CString str;
	str.Format("%s",lpBuffer);
	
	
	if (CString(bRtn)==str) 
	{
		return FALSE;//登录本地
	}
	else
	{
		return TRUE;//enter DNS server
	}
}

BOOL IsClientEnterDomain::GetEnterType()//If the client enter DNS server ,The return values is TRUE . 
{
      if (TRUE==Is_Win2000_DomainController()) 
	  {    //AfxMessageBox("当前计算机是域服务器");
		  return FALSE;//It is DNS server
      }
	  UINT uType;
	  char Servernameinfo[100];
	  if (JOIN_DOMAIN!=GetGroupInfo(Servernameinfo, &uType)) 
	  { //AfxMessageBox("当前计算机没有加入了域");
		  return FALSE;//The currently computer do not join DNS server
	  }
	  if (!IsEnterDomain())
	  	  return FALSE;//登录本地
	  return TRUE;
}