// GetIP.cpp : implementation file
//

#include "stdafx.h"
#include "ClientTest.h"
#include "GetIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetIP dialog


CGetIP::CGetIP(CWnd* pParent /*=NULL*/)
	: CDialog(CGetIP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetIP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ipstr = _T("");
}


void CGetIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetIP)
	DDX_Control(pDX, IDC_IPADDRESS, ip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetIP, CDialog)
	//{{AFX_MSG_MAP(CGetIP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetIP message handlers

void CGetIP::OnOK() 
{
	ip.GetWindowText(ipstr);
	CDialog::OnOK();
}

BOOL CGetIP::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ip.SetWindowText(ipstr);

	return TRUE;  // return TRUE unless you set the focus to a control
}
