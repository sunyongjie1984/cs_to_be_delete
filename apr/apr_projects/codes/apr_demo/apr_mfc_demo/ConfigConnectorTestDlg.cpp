// ConfigConnectorTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "apr_mfc_demo.h"
#include "ConfigConnectorTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigConnectorTestDlg dialog



CConfigConnectorTestDlg::CConfigConnectorTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigConnectorTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigConnectorTestDlg)
	m_ipAddr = _T("172.16.16.123");
	//}}AFX_DATA_INIT
}


void CConfigConnectorTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigConnectorTestDlg)
	DDX_Text(pDX, IDC_IP_ADDR, m_ipAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigConnectorTestDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigConnectorTestDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigConnectorTestDlg message handlers

void CConfigConnectorTestDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
