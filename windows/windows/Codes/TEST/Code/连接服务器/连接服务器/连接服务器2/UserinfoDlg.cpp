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
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
