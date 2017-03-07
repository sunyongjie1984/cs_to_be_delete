// GetDomainAccountsInfo1.cpp: implementation of the GetDomainAccountsInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GetDomainAccountsInfo1.h"
#include "resource.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GetDomainAccountsInfo::GetDomainAccountsInfo()
{

}

GetDomainAccountsInfo::~GetDomainAccountsInfo()
{

}
typedef NET_API_STATUS (__stdcall *P_WNetAddConnection2)(LPNETRESOURCE lpNetResource, LPCTSTR lpPassword, LPCTSTR lpUsername, DWORD dwFlags);

BOOL GetDomainAccountsInfo::ConnectNetword(CStdString m_serverName/*,CStdString lpPassword,CStdString lpUsername*/)
{   
    HMODULE hLoad = ::LoadLibrary("Mpr.dll");
	if(!hLoad)
	{
		int iErrorCode = ::GetLastError();
//		LogError(0x19780827, "CIsClientEnterDomain::GetGroupInfo LoadLibrary Error is: %d", iErrorCode);
		return -1;
	}
	P_WNetAddConnection2 pWNetAddConnection2 = (P_WNetAddConnection2)::GetProcAddress(hLoad, "WNetAddConnection2A");
	if(!pWNetAddConnection2)
	{
		return -1;
	}

	NETRESOURCE lpNetResource;
	DWORD dwFlags1 = CONNECT_INTERACTIVE;
	DWORD hr;
	
	
	lpNetResource.dwType =	RESOURCETYPE_ANY;
	lpNetResource.dwDisplayType = RESOURCETYPE_ANY;
	lpNetResource.dwScope = RESOURCE_GLOBALNET;
	lpNetResource.dwUsage = RESOURCEUSAGE_CONTAINER;
	lpNetResource.lpComment = NULL;
	lpNetResource.lpLocalName = NULL;
	lpNetResource.lpProvider = NULL;
	lpNetResource.lpRemoteName =m_serverName.GetBuffer(0);
	hr=pWNetAddConnection2(&lpNetResource, NULL, NULL, dwFlags1);
	
	if( NO_ERROR == hr )
	{
        GetAccountsinfo(m_serverName,_T("Domain Users"));
		GetGroupaccountsInfo(m_serverName);
		return	TRUE;
	}
	CtdString csTemp;
	csTemp.LoadString(IDS_CONNECTION_FAIL);
	AfxMessageBox( csTemp );
    return FALSE;
}

typedef NET_API_STATUS (__stdcall *P_NetGroupGetUsers)(LPCWSTR servername,LPCWSTR groupname,DWORD level,LPBYTE* bufptr, DWORD prefmaxlen, LPDWORD entriesread, LPDWORD totalentries, PDWORD_PTR ResumeHandle);
typedef NET_API_STATUS (__stdcall *P_NetApiBufferFree)(LPVOID Buffer);

int GetDomainAccountsInfo::GetAccountsinfo(CStdString m_serverName,CStdString m_groupname)
{   
	HMODULE hLoad = ::LoadLibrary("Netapi32.dll");
	if(!hLoad)
	{
		int iErrorCode = ::GetLastError();
		return -1;
	}
	P_NetGroupGetUsers pNetGroupGetUsers = (P_NetGroupGetUsers)::GetProcAddress(hLoad, "NetGroupGetUsers");
	P_NetApiBufferFree pNetApiBufferFree = (P_NetApiBufferFree)::GetProcAddress(hLoad, "NetApiBufferFree");
    if(!pNetGroupGetUsers)
	{
		return -1;
	}
    if(!pNetApiBufferFree)
	{
		return -1;
	}
	
	CStdString csFmtname;
	NET_API_STATUS nStatus;
	PGROUP_USERS_INFO_0 pBuf = NULL;
	PGROUP_USERS_INFO_0 pTmpBuf = NULL;
	DWORD i = 0;
	DWORD dwResumeHandle=0;
	DWORD dwTotalCount=0;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = -1;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	WCHAR pszServerName[MAX_PATH] = {0};   
    WCHAR pszgroupname[MAX_PATH] = {0};	   
	char servername[MAX_PATH] = {0};	   
	char groupname[MAX_PATH] = {0};

	strcpy(servername, m_serverName.GetBuffer(0));
	strcpy(groupname, m_groupname.GetBuffer(0));

	DWORD rc = MultiByteToWideChar(CP_ACP, 0, servername,-1, pszServerName,sizeof(pszServerName));
	DWORD fc = MultiByteToWideChar(CP_ACP, 0, groupname,-1,	pszgroupname,sizeof(pszgroupname));	 
	
	do
	{		
	    nStatus =pNetGroupGetUsers(pszServerName, pszgroupname, dwLevel, (LPBYTE *)&pBuf, dwPrefMaxLen, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);	   
	    if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
		    if ((pTmpBuf = pBuf) != NULL)
			{			
			    for (i = 0; (i < dwEntriesRead); i++)
				{
				    assert(pTmpBuf != NULL);
				    if (pTmpBuf == NULL)
					{				  
				        AfxMessageBox("An access violation has occurred" );
					    break;
					} 
				    csFmtname.Format("%S",pTmpBuf->grui0_name);
					m_strVector.push_back(csFmtname);
				    pTmpBuf++;
				    dwTotalCount++;
					}
				}
		   }	
           else
		   {
  			   if (pBuf != NULL)
			   {
				   pNetApiBufferFree(pBuf);
				   pBuf = NULL;
			   }
		   }
	   }
       while (nStatus == ERROR_MORE_DATA); 

	   if (pBuf != NULL)
	   {
		    pNetApiBufferFree(pBuf);
	   }		  
	   return 1;
}

typedef NET_API_STATUS (__stdcall *P_NetGroupEnum)(LPCWSTR servername, DWORD level, LPBYTE* bufptr, DWORD prefmaxlen, LPDWORD entriesread, LPDWORD totalentries, PDWORD_PTR resume_handle);

int GetDomainAccountsInfo::GetGroupaccountsInfo(CStdString serverName)
{
 	HMODULE hLoad = ::LoadLibrary("Netapi32.dll");

	if(!hLoad)
	{
		int iErrorCode = ::GetLastError();
		//LogError(0x19780827, "CIsClientEnterDomain::GetGroupInfo LoadLibrary Error is: %d", iErrorCode);
		return -1;
	}

	P_NetGroupEnum pNetGroupEnum = (P_NetGroupEnum)::GetProcAddress(hLoad, "NetGroupEnum");

	CStdString csFmtname;
    NET_API_STATUS nStatus;
	PGROUP_INFO_2 pBuf = NULL;
    PGROUP_INFO_2 pTmpBuf = NULL;
	DWORD i = 0;
	DWORD dwResumeHandle=0;
	DWORD dwTotalCount=0;	
    DWORD dwLevel = 2;
    DWORD dwPrefMaxLen = -1;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;    
    WCHAR pszServerName[MAX_PATH] = {0};   
    char servername[MAX_PATH];
	   
    strcpy(servername, serverName.GetBuffer(0));

    DWORD rc = MultiByteToWideChar(CP_ACP, 0, servername,-1,	pszServerName,sizeof(pszServerName));   
	do
	{
		
		nStatus =pNetGroupEnum(pszServerName, dwLevel, (LPBYTE *)&pBuf, dwPrefMaxLen, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);
		   
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				
			    for (i = 0; (i < dwEntriesRead); i++)
				{
					assert(pTmpBuf != NULL);
					if (pTmpBuf == NULL)
					{						
						AfxMessageBox("An access violation has occurred" );
						break;
					} 
					csFmtname.Format("%S",pTmpBuf->grpi2_name);
					m_strVectorgroup.push_back(csFmtname);
					pTmpBuf++;
					dwTotalCount++;
				   }
			   }
		   }	
           else
		   {
			   if (pBuf != NULL)
			   {
				   NetApiBufferFree(pBuf);
				   pBuf = NULL;
			   }
		   }
	   }
       while (nStatus == ERROR_MORE_DATA); 
	   if (pBuf != NULL)
	   {
		   NetApiBufferFree(pBuf);
	   }		  
	   return 1;
}

typedef NET_API_STATUS (__stdcall *P_NetGroupDel)(LPCWSTR servername, LPCWSTR groupname);

int GetDomainAccountsInfo::DelGroupaccount(CStdString servernamein,CStdString groupnamein)
{
	HMODULE hLoad = ::LoadLibrary("Netapi32.dll");
	
	if(!hLoad)
	{
		int iErrorCode = ::GetLastError();
		//LogError(0x19780827, "CIsClientEnterDomain::GetGroupInfo LoadLibrary Error is: %d", iErrorCode);
		return -1;
	}	
	P_NetGroupDel pNetGroupDel = (P_NetGroupDel)::GetProcAddress(hLoad, "NetGroupDel");

	TCHAR servername[100] = {0};	
	TCHAR groupname[100] = {0}; 
	WCHAR wservername[100] = {0};
	WCHAR wgroupname[100] = {0};
	
	strcpy(servername, servernamein.GetBuffer(0));	
	strcpy(groupname, groupnamein.GetBuffer(0));
	
	DWORD rc = MultiByteToWideChar(CP_ACP, 0, servername,-1, wservername, sizeof(wservername));		
	DWORD hc = MultiByteToWideChar(CP_ACP, 0, groupname,-1, wgroupname, sizeof(wgroupname));	
	
	NET_API_STATUS nStatus=pNetGroupDel(wservername,wgroupname);
	if (nStatus)
	{
		return 0;
	}

	return 1;
}

typedef NET_API_STATUS (__stdcall *P_NetUserDel)(LPCWSTR servername, LPCWSTR groupname);

int GetDomainAccountsInfo::DelUseraccount(CStdString servernamein,CStdString usernamein)
{
	HMODULE hLoad = ::LoadLibrary("Netapi32.dll");
	
	if(!hLoad)
	{
		int iErrorCode = ::GetLastError();
		//LogError(0x19780827, "CIsClientEnterDomain::GetGroupInfo LoadLibrary Error is: %d", iErrorCode);
		return -1;
	}	
	P_NetUserDel pNetUserDel = (P_NetUserDel)::GetProcAddress(hLoad, "NetUserDel");
	TCHAR servername[100] = {0};	
	TCHAR username[100] = {0}; 
	WCHAR wservername[100] = {0};
	WCHAR wusername[100] = {0};
	
	strcpy(servername, servernamein.GetBuffer(0));	
	strcpy(username, usernamein.GetBuffer(0));
	
	DWORD rc = MultiByteToWideChar(CP_ACP, 0, servername,-1, wservername, sizeof(wservername));		
	DWORD hc = MultiByteToWideChar(CP_ACP, 0, username,-1, wusername, sizeof(wusername));	
	
	NET_API_STATUS nStatus=pNetUserDel(wservername,wusername);
	if (nStatus)
	{
        return 0;
	}
	
	return 1;
}


int GetDomainAccountsInfo::EstablishNewGroup(CStdString servernamein,CStdString newgroupnamein)
{
	NET_API_STATUS nStatus;	
	GROUP_INFO_2 ui;
	DWORD dwLevel = 2;
	DWORD dwError = 0;
	WCHAR wnewservername[100] = {0};
	WCHAR wnewgroupname[100] = {0};
	TCHAR newservername[100] = {0};
	TCHAR newgroupname[100] = {0};
	strcpy(newservername,servernamein.GetBuffer(0));
	strcpy(newgroupname,newgroupnamein.GetBuffer(0));
	   
	DWORD rc = MultiByteToWideChar(CP_ACP, 0, newgroupname, -1, wnewgroupname, sizeof(newgroupnamein));	
	
	ui.grpi2_name=wnewgroupname;
	ui.grpi2_group_id=599;
	ui.grpi2_comment=NULL;
	ui.grpi2_attributes=SE_GROUP_ENABLED;

	nStatus = NetGroupAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);
	if (nStatus)
	{
		return 0;
	}
	return 1;
}

