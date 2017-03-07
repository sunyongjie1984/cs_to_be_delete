// StationscriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "net.h"
#include "StationscriptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationscriptDlg dialog

CStationscriptDlg::CStationscriptDlg(CString &csName2,CWnd* pParent /*=NULL*/)
: CDialog(CStationscriptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStationscriptDlg)
	m_userName = _T("");
	m_scriptpath = _T("");
	//}}AFX_DATA_INIT
	m_serverName = csName2;
}


void CStationscriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStationscriptDlg)
	DDX_Text(pDX, IDC_EDIT1, m_userName);
	DDX_Text(pDX, IDC_EDIT2, m_scriptpath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStationscriptDlg, CDialog)
	//{{AFX_MSG_MAP(CStationscriptDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStationscriptDlg message handlers

void CStationscriptDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	DWORD dwLevel = 1009;///////////////////////////
	USER_INFO_1009 dbuf;////////////////////////////
	NET_API_STATUS nStatus;
	
	CString errormsg02;
	
	WCHAR dservername[MAX_PATH] = {0}; 
	WCHAR dusername[MAX_PATH] = {0};
	WCHAR dusri1009_script_path[MAX_PATH]={0};
	
	char servername[MAX_PATH];
	char username[MAX_PATH];
	char scriptpath[MAX_PATH];
	
	strcpy(servername, m_serverName.GetBuffer(0));
	strcpy(username, m_userName.GetBuffer(0));
	strcpy(scriptpath,m_scriptpath.GetBuffer(0));
	 	   MessageBox(servername);
	   DWORD rc = MultiByteToWideChar(CP_ACP, 
		   0, 
		   servername,
		   -1,	
		   dservername,
		   sizeof(dservername));
	   DWORD hc = MultiByteToWideChar(CP_ACP, 
		   0, 
		   username,
		   -1,	
		   dusername,
		   sizeof(dusername));
	   DWORD kc = MultiByteToWideChar(CP_ACP, //////////////////////
		   0, /////////////////////////////////
		   scriptpath,///////////////
		   -1,	////////////////////////
		   dusri1009_script_path,///////////////
		   sizeof(dusri1009_script_path));//////////
	   
	   dbuf.usri1009_script_path=dusri1009_script_path;
	   
	   
	   nStatus = NetUserSetInfo(/*NULL,//*/dservername,
		   /*L"administrator"*/dusername,
		   dwLevel,
		   (LPBYTE)&dbuf,
		   NULL);
	   if (nStatus == NERR_Success)
		   AfxMessageBox("file amend ok");
	   else
	   {	
		   errormsg02.Format("%d",nStatus);
		   CString errormsg="A system error has occurred:  "+errormsg02;
		   AfxMessageBox(errormsg);
	   }
	
	CDialog::OnOK();
}
