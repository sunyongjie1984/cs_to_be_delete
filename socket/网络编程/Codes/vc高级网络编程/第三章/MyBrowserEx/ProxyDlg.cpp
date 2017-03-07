// ProxyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyBrowserEx.h"
#include "ProxyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProxyDlg dialog


CProxyDlg::CProxyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProxyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProxyDlg)
	m_strProxy = _T("");
	//}}AFX_DATA_INIT
}


void CProxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProxyDlg)
	DDX_Text(pDX, IDC_PROXYNAME, m_strProxy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProxyDlg, CDialog)
	//{{AFX_MSG_MAP(CProxyDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProxyDlg message handlers
