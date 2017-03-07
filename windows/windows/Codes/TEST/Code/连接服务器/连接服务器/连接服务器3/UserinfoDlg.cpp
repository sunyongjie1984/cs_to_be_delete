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
    while(i<20)
	{
	     Item.iItem=i;
	     Item.pszText=msg.GetBuffer(0);
	     m_listuserinfo.InsertItem(&Item);//插入项目到列表视图

	     m_listuserinfo.SetItemText(i,1,"SSDFLSKLKF01");
	     m_listuserinfo.SetItemText(i,2,"SSDFLSKLKF02");
	     i++;

	}	
	
//	Item.iItem=i;
//	Item.iSubItem=0;
//	Item.pszText=msg.GetBuffer(0);
//	m_listuserinfo.InsertItem(&Item);
//	m_list.SetItemText(1,1,"SSDFLSKLKF01");
//	m_list.SetItemText(1,2,"SSDFLSKLKF02");
	

    UpdateData();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
