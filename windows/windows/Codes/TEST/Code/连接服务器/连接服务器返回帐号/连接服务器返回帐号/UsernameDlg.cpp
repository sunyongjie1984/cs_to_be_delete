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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_serverName = csName;
}


void CUsernameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsernameDlg)
	DDX_Control(pDX, IDC_LIST1, m_listuserinfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsernameDlg, CDialog)
	//{{AFX_MSG_MAP(CUsernameDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsernameDlg message handlers

//DEL BOOL CUsernameDlg::OnInitDialog() 
//DEL {
//DEL 	CDialog::OnInitDialog();
//DEL 	
//DEL 	// TODO: Add extra initialization here
//DEL 
//DEL 	   DWORD i;
//DEL 	   LPUSER_INFO_2 pBuf= NULL;
//DEL 	   LPUSER_INFO_2 pTmpBuf = NULL;
//DEL 	   DWORD dwLevel=0;
//DEL 	   DWORD dwPrefMaxLen= MAX_PREFERRED_LENGTH;
//DEL 	   DWORD dwEntriesRead=0;
//DEL 	   DWORD dwTotalEntries=0;
//DEL 	   DWORD dwResumeHandle=0;
//DEL 	   DWORD dwTotalCount=0;
//DEL 	   
//DEL 	   CString csFmtname;
//DEL 	   CString csFmtscript_path;
//DEL 	   CString serverna;
//DEL 	   
//DEL 	   NET_API_STATUS nStatus;
//DEL 	   // LPTSTR pszServerName=NULL;
//DEL 	   
//DEL 	   UpdateData();
//DEL 	   
//DEL 	   
//DEL 	   //   WCHAR wServerName[MAX_PATH] ={0}/*L"\\\\192.168.0.206"*/;
//DEL 	   
//DEL 	   WCHAR pszServerName[MAX_PATH] = {0};   
//DEL 	   CNetDlg dlg;
//DEL        serverna= "\\\\" + dlg.m_servernamemsg;
//DEL 	   char servername[MAX_PATH];
//DEL 	   strcpy(servername, serverna.GetBuffer(0));
//DEL 	   DWORD rc = MultiByteToWideChar(CP_ACP, 
//DEL 		   0, 
//DEL 		   serverna,
//DEL 		   -1,	
//DEL 		   pszServerName,
//DEL 		   sizeof(pszServerName));
//DEL 	   if(rc == 0)
//DEL 	   {
//DEL 		   int ret = GetLastError();
//DEL 		   CString csError;
//DEL 		   csError.Format("MultiByteToWideChar error %d",ret);
//DEL 		   AfxMessageBox(csError);
//DEL 
//DEL 	   }
//DEL 	   do 
//DEL 	   {
//DEL 		   nStatus = NetUserEnum(/*(const unsigned short *)*/pszServerName,
//DEL 			   2,
//DEL 			   //FILTER_SERVER_TRUST_ACCOUNT, // global users
//DEL 			   FILTER_NORMAL_ACCOUNT,
//DEL 			   //FILTER_TEMP_DUPLICATE_ACCOUNT,
//DEL 			   //FILTER_WORKSTATION_TRUST_ACCOUNT,
//DEL 			   (LPBYTE*)&pBuf,
//DEL 			   dwPrefMaxLen,
//DEL 			   &dwEntriesRead,
//DEL 			   &dwTotalEntries,                            
//DEL 			   &dwResumeHandle);
//DEL 		   if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
//DEL 		   {
//DEL 			   if ((pTmpBuf = pBuf) != NULL)
//DEL 			   {
//DEL 				   
//DEL 				   for (i = 0; (i < dwEntriesRead); i++)
//DEL 				   {
//DEL 					   assert(pTmpBuf != NULL);
//DEL 					   if (pTmpBuf == NULL)
//DEL 					   {				  
//DEL 						   AfxMessageBox("An access violation has occurred" );
//DEL 						   break;
//DEL 					   } 
//DEL 					   csFmtname = pTmpBuf->usri2_name;
//DEL 					   csFmtscript_path.Format("%S",pTmpBuf->usri2_script_path);
//DEL 					   
//DEL 					   m_listuserinfo.InsertItem(i,csFmtname);//插入项目到列表视图
//DEL 					   m_listuserinfo.SetItemText(i,1,csFmtscript_path);
//DEL 					   
//DEL 					   pTmpBuf++;
//DEL 					   dwTotalCount++;
//DEL 				   }
//DEL 			   }
//DEL 		   }
//DEL 		   
//DEL 		   else
//DEL 			   //	     m_value1=nStatus;
//DEL 			   
//DEL 			   if (pBuf != NULL)
//DEL 			   {
//DEL 				   NetApiBufferFree(pBuf);
//DEL 				   pBuf = NULL;
//DEL 			   }
//DEL 	   }
//DEL 	   
//DEL 	   while (nStatus == ERROR_MORE_DATA); // end do
//DEL 	   
//DEL 	   if (pBuf != NULL)
//DEL 		   NetApiBufferFree(pBuf);
//DEL 	   
//DEL 	   fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);
//DEL 	
//DEL 	return TRUE;  // return TRUE unless you set the focus to a control
//DEL 	              // EXCEPTION: OCX Property Pages should return FALSE
//DEL }

void CUsernameDlg::OnButton1() 
{
	m_listuserinfo.DeleteAllItems();
 	   DWORD i;
 	   LPUSER_INFO_2 pBuf= NULL;
 	   LPUSER_INFO_2 pTmpBuf = NULL;
 	   DWORD dwLevel=0;
 	   DWORD dwPrefMaxLen= MAX_PREFERRED_LENGTH;
 	   DWORD dwEntriesRead=0;
 	   DWORD dwTotalEntries=0;
 	   DWORD dwResumeHandle=0;
 	   DWORD dwTotalCount=0;
 	   
 	   CString csFmtname;
 	   CString csFmtscript_path;
	   CString csFmt_password;
 	   CString serverna;
 	   
 	   NET_API_STATUS nStatus;
	   // LPTSTR pszServerName=NULL;
 	   
 	   UpdateData();
 	   
 	   
 	   //   WCHAR wServerName[MAX_PATH] ={0}/*L"\\\\192.168.0.206"*/;
 	   
 	   WCHAR pszServerName[MAX_PATH] = {0};   
 	   
//	MessageBox(serverna);
 	   char servername[MAX_PATH];
 	   strcpy(servername, m_serverName.GetBuffer(0));
	   MessageBox(servername);
 	   DWORD rc = MultiByteToWideChar(CP_ACP, 
 		                              0, 
 		                              servername,
 		                              -1,	
 		                              pszServerName,
 		                              sizeof(pszServerName));

 	   if(rc == 0)
 	   {
 		   int ret = GetLastError();
 		   CString csError;
 		   csError.Format("MultiByteToWideChar error %d",ret);
 		   AfxMessageBox(csError);
 
 	   }
 	   do 
 	   {
 		   nStatus = NetUserEnum(/*(const unsigned short *)*/pszServerName,
 			   2,
 			   //FILTER_SERVER_TRUST_ACCOUNT, // global users
 			   FILTER_NORMAL_ACCOUNT,
 			   //FILTER_TEMP_DUPLICATE_ACCOUNT,
 			   //FILTER_WORKSTATION_TRUST_ACCOUNT,
 			   (LPBYTE*)&pBuf,
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
 					   csFmtname = pTmpBuf->usri2_name;
					   csFmtscript_path.Format("%S",pTmpBuf->usri2_script_path);
					   csFmt_password.Format("%S",pTmpBuf->usri2_password);
 					   
 					   m_listuserinfo.InsertItem(i,csFmtname);//插入项目到列表视图
 					   m_listuserinfo.SetItemText(i,1,csFmtscript_path);
					   m_listuserinfo.SetItemText(i,2,csFmt_password);
 					   
 					   pTmpBuf++;
 					   dwTotalCount++;
 				   }
 			   }
 		   }
 		   
 		   else
 			   //	     m_value1=nStatus;
 			   
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
	
	// TODO: Add extra initialization here
	m_listuserinfo.InsertColumn(0,"用户名称",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(1,"登录脚本",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(2,"用户密码",LVCFMT_LEFT,100);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
