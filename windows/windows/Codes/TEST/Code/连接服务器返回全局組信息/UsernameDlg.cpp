// UsernameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "net.h"
#include "UsernameDlg.h"
#include "netDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsernameDlg dialog


CUsernameDlg::CUsernameDlg(CString &csName, CWnd* pParent /*=NULL*/)
	: CDialog(CUsernameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUsernameDlg)
	m_username = _T("");
	//}}AFX_DATA_INIT
	m_serverName = csName;

}


void CUsernameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsernameDlg)
	DDX_Control(pDX, IDC_LIST1, m_listuserinfo);
	DDX_Text(pDX, IDC_EDIT2, m_username);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsernameDlg, CDialog)
	//{{AFX_MSG_MAP(CUsernameDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CUsernameDlg::OnButton1() 
{
	   m_listuserinfo.DeleteAllItems();
 	   DWORD i;
 	   DWORD dwResumeHandle=0;
 	   DWORD dwTotalCount=0;
 	   
 	   CString csFmtname;
 	   CString csFmtgrui0_name;
 	   CString serverna;
 	   
 	   
///////////////////////////////////////////////////
	   PGROUP_INFO_2 pBuf = NULL;
	   PGROUP_INFO_2 pTmpBuf = NULL;
	   DWORD dwLevel = 2;
	   DWORD dwPrefMaxLen = -1;
	   DWORD dwEntriesRead = 0;
	   DWORD dwTotalEntries = 0;
	   NET_API_STATUS nStatus;
 	   UpdateData();
  	   WCHAR pszServerName[MAX_PATH] = {0};   
       WCHAR pszgroupname[MAX_PATH]={0};

 	   char servername[MAX_PATH];
	   char groupname[MAX_PATH];
	   CString m_groupname("Domain Controllers");
 	   strcpy(servername, m_serverName.GetBuffer(0));
	   strcpy(groupname, m_groupname.GetBuffer(0));
//	   strcpy(username,m_username.GetBuffer(0));

 	   DWORD rc = MultiByteToWideChar(CP_ACP, 
 		                              0, 
 		                              servername,
 		                              -1,	
 		                              pszServerName,
 		                              sizeof(pszServerName));
	   DWORD Fc = MultiByteToWideChar(CP_ACP, 
		                                0, 
		                                groupname,
										-1,	
								    	pszgroupname,
										sizeof(pszgroupname));
	   

 	   if(rc == 0)
 	   {
 		   int ret = GetLastError();
 		   CString csError;
 		   csError.Format("MultiByteToWideChar error %d",ret);
 		   AfxMessageBox(csError);
 
 	   }
 	   do 
	   {

		   nStatus =NetGroupEnum(pszServerName,
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
 					   csFmtname.Format("%S", pTmpBuf->grpi2_name);

  					   m_listuserinfo.InsertItem(i,csFmtname);//插入项目到列表视图

 					   
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
  	   while (nStatus == ERROR_MORE_DATA); // end do
 	   
 	   if (pBuf != NULL)
 		   NetApiBufferFree(pBuf);
 	   
 	   fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);
	
}

BOOL CUsernameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	m_listuserinfo.InsertColumn(0,"用户名称",LVCFMT_LEFT,100);
//	m_listuserinfo.InsertColumn(1,"登录脚本",LVCFMT_LEFT,100);
    
	return TRUE;  
}

void CUsernameDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CStationscriptDlg dlgscrift(m_serverName);

	
	
    
	dlgscrift.DoModal();
}
