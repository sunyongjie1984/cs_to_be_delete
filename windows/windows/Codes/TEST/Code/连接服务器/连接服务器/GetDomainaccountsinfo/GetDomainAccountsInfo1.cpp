// GetDomainAccountsInfo1.cpp: implementation of the GetDomainAccountsInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GetDomainAccountsInfo1.h"


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

BOOL GetDomainAccountsInfo::ConnectNetword(CStdString serverName,CStdString lpPassword,CStdString lpUsername)
{
	NETRESOURCE lpNetResource1;
	DWORD dwFlags1 = CONNECT_INTERACTIVE;
	DWORD hr;
	
	
	lpNetResource1.dwType =	RESOURCETYPE_ANY;
	lpNetResource1.dwDisplayType = RESOURCETYPE_ANY;
	lpNetResource1.dwScope = RESOURCE_GLOBALNET;
	lpNetResource1.dwUsage = RESOURCEUSAGE_CONTAINER;
	lpNetResource1.lpComment = NULL;
	lpNetResource1.lpLocalName = NULL;
	lpNetResource1.lpProvider = NULL;
	lpNetResource1.lpRemoteName =serverName.GetBuffer(0);
	hr=WNetAddConnection2(&lpNetResource1,  
		                   lpPassword,           
		                   lpUsername,           
		                  dwFlags1);	
	if( NO_ERROR == hr )
	{
        GetAccountsinfo(serverName,_T("Domain Users"));
		return	TRUE;
	}
	AfxMessageBox( "连接失败！" );
    return FALSE;
}

void GetDomainAccountsInfo::GetAccountsinfo(CStdString serverName,CStdString groupname)
{
	DWORD i;
	DWORD dwResumeHandle=0;
	DWORD dwTotalCount=0;
	
	CStdString csFmtname;
	///////////////////////////////////////////////////
	   PGROUP_USERS_INFO_0 pBuf = NULL;
	   PGROUP_USERS_INFO_0 pTmpBuf = NULL;
	   DWORD dwLevel = 0;
	   DWORD dwPrefMaxLen = -1;
	   DWORD dwEntriesRead = 0;
	   DWORD dwTotalEntries = 0;
	   NET_API_STATUS nStatus;

	   WCHAR pszServerName[MAX_PATH] = {0};   
       WCHAR pszgroupname[MAX_PATH]={0};	   
	   char cservername[MAX_PATH];	   
	   char cgroupname[MAX_PATH];
	   strcpy(cservername, serverName.GetBuffer(0));
	   strcpy(cgroupname, groupname.GetBuffer(0));

	   DWORD rc = MultiByteToWideChar(CP_ACP, 
		   0, 
		   cservername,
		   -1,	
		   pszServerName,
		   sizeof(pszServerName));
	   DWORD Fc = MultiByteToWideChar(CP_ACP, 
		   0, 
		   cgroupname,
		   -1,	
		   pszgroupname,
		   sizeof(pszgroupname));	   
//	   if(rc == 0)
//	   {
//		   int ret = GetLastError();
//		   CStdString csError;
//		   csError.Format("MultiByteToWideChar error %d",ret);
//		   AfxMessageBox(csError);
//		   
//	   }
	   do
	   {  
	      nStatus =NetGroupGetUsers(pszServerName,//指定远程服务的域服务器或网络输入输出系统名
		                            pszgroupname,//列出指定全局组名列表
		                            dwLevel,              
		                            (LPBYTE *)&pBuf,           
		                            dwPrefMaxLen,         
		                            &dwEntriesRead,      
		                            &dwTotalEntries,     
		                            &dwResumeHandle);
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
						   //加数组
						   csFmtname.Format("%S",pTmpBuf->grui0_name);
						   m_strVector.push_back(csFmtname);//
				           pTmpBuf++;
				           dwTotalCount++;
					 }
				}
		   }	
           else
  			   if (pBuf != NULL)
			   {
				   NetApiBufferFree(pBuf);
				   pBuf = NULL;
			   }
	   }
       while (nStatus == ERROR_MORE_DATA); 
	   if (pBuf != NULL)
		   NetApiBufferFree(pBuf);
}
