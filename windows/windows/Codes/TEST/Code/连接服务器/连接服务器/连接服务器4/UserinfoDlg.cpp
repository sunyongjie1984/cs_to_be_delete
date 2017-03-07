// UserinfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "net.h"
#include "UserinfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserinfoDlg dialog


CUserinfoDlg::CUserinfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserinfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserinfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pBuf = NULL;
	
	dwLevel = 0;
	dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	dwEntriesRead = 0;
	dwTotalEntries = 0;
	dwResumeHandle = 0;
	
	dwTotalCount = 0;
}


void CUserinfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserinfoDlg)
	DDX_Control(pDX, IDC_LIST1, m_listuserinfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserinfoDlg, CDialog)
	//{{AFX_MSG_MAP(CUserinfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserinfoDlg message handlers

BOOL CUserinfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// TODO: Add extra initialization here
	m_listuserinfo.InsertColumn(0,"用户名称",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(1,"类型",LVCFMT_LEFT,100);
	m_listuserinfo.InsertColumn(2,"描述",LVCFMT_LEFT,100);

/////////////////////////////////////////////////////////////////
	CString msg("User_name Item");
	int i=0;
	//////////////////////////////////////////////////////////////
	LV_ITEM Item;
	Item.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_STATE;
	Item.state=0;
	Item.stateMask=0;
	Item.iImage=0;
	
	Item.iSubItem=0;
    /*
    while(i<20)
    	{
    	     Item.iItem=i;
    	     Item.pszText=msg.GetBuffer(0);
    	     m_listuserinfo.InsertItem(&Item);//插入项目到列表视图
    
    	     m_listuserinfo.SetItemText(i,1,"SSDFLSKLKF01");
    	     m_listuserinfo.SetItemText(i,2,"SSDFLSKLKF02");
    	     i++;
    
    	}	
    	*/
    
    UpdateData();
    {
   

	CString msgip("\\192.168.0.215");
    pszServerName = msgip.GetBuffer(0) ;


/*
	NET_API_STATUS NET_API_FUNCTION NetUserEnum ( IN LPCWSTR servername OPTIONAL, 
		IN DWORD level, 
		IN DWORD filter, 
		OUT LPBYTE *bufptr, 
		IN DWORD prefmaxlen, 
		OUT	LPDWORD entriesread,
		OUT LPDWORD totalentries, 
		IN OUT LPDWORD resume_handle OPTIONAL )
*/

    do // begin do  
    {
		WCHAR	wServerName[MAX_PATH] ={0};
		DWORD rc = MultiByteToWideChar(CP_ACP, 0, pszServerName,	-1,	wServerName, sizeof(wServerName));
		if(rc==0)
		{
			int ret = GetLastError();
			CString csError;
			csError.Format("MultiByteToWideChar error %d",ret);
			AfxMessageBox(csError);
			return FALSE;
		}
        nStatus = NetUserEnum(wServerName,
                              dwLevel,
                              //FILTER_SERVER_TRUST_ACCOUNT, // global users
                              FILTER_NORMAL_ACCOUNT,
                              //FILTER_TEMP_DUPLICATE_ACCOUNT,
							  //FILTER_WORKSTATION_TRUST_ACCOUNT,
                              (LPBYTE*) &pBuf,
                              dwPrefMaxLen,
                              &dwEntriesRead,//项目数
                              &dwTotalEntries,                            
							  &dwResumeHandle);
        if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
            if ((pTmpBuf = pBuf) != NULL)//
			{
                 for (i = 0; (i < (int) dwEntriesRead); i++)
				 {
                      assert(pTmpBuf != NULL);
                    if (pTmpBuf == NULL)
					{
                        AfxMessageBox("An access violation has occurred" );
                        break;
					}
			        CString csFmt;
			        
			        csFmt.Format("%S",pTmpBuf->usri0_name);
             // m_listbox.AddString((/*const unsigned short **/LPTSTR)pTmpBuf->usri0_name) ;
			        Item.iItem=i;
			        Item.pszText=csFmt.GetBuffer(0);
			        m_listuserinfo.InsertItem(&Item);//插入项目到列表视图
			        m_listuserinfo.SetItemText(i,1,"SSDFLSKLKF01");
			        m_listuserinfo.SetItemText(i,2,"SSDFLSKLKF02");
			        i++;
					///////////////////////////////////////////////////////////////
                    pTmpBuf++;
                    dwTotalCount++;
				 }
			}
		}
        else
////	         m_value1=nStatus;
        if (pBuf != NULL)
		{
              NetApiBufferFree(pBuf);
              pBuf = NULL;
		}
	}while (nStatus == ERROR_MORE_DATA); // end do

    if (pBuf != NULL)
      NetApiBufferFree(pBuf);
    fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





















