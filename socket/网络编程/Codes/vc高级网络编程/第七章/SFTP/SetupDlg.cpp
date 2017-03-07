// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SFTP.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	m_strPass = _T("ware@para.net");
	m_uPort = 21;
	m_strProxy = _T("");
	m_strServer = _T("10.12.11.74");
	m_strUser = _T("anonymous");
	m_strProxyPass = _T("");
	m_strProxyUser = _T("");
	m_uProxPort = 0;
	//}}AFX_DATA_INIT
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_PROXYTYPE, m_ctrlType);
	DDX_Text(pDX, IDC_PASS, m_strPass);
	DDX_Text(pDX, IDC_PORT, m_uPort);
	DDX_Text(pDX, IDC_PROXY, m_strProxy);
	DDX_Text(pDX, IDC_SVRADDRESS, m_strServer);
	DDX_Text(pDX, IDC_USER, m_strUser);
	DDX_Text(pDX, IDC_USERPASS, m_strProxyPass);
	DDX_Text(pDX, IDC_USERNAME, m_strProxyUser);
	DDX_Text(pDX, IDC_PROXYPORT, m_uProxPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_CBN_SELCHANGE(IDC_PROXYTYPE, OnSelchangeProxytype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnOK() 
{
	m_uType = m_ctrlType.GetCurSel();
	CDialog::OnOK();
}

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlType.SetCurSel(0);
	GetDlgItem(IDC_PROXY)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROXYPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_USERPASS)->EnableWindow(FALSE);
	GetDlgItem(IDC_USERNAME)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnSelchangeProxytype() 
{
	if(m_ctrlType.GetCurSel() == 0){
		GetDlgItem(IDC_PROXY)->EnableWindow(FALSE);
		GetDlgItem(IDC_PROXYPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_USERPASS)->EnableWindow(FALSE);
		GetDlgItem(IDC_USERNAME)->EnableWindow(FALSE);
	}
	else{
		GetDlgItem(IDC_PROXY)->EnableWindow(TRUE);
		GetDlgItem(IDC_PROXYPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_USERPASS)->EnableWindow(TRUE);
		GetDlgItem(IDC_USERNAME)->EnableWindow(TRUE);
	}
}
