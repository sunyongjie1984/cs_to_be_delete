// LoginLoad.cpp : implementation file
//

#include "stdafx.h"
#include "MyQQClient.h"
#include "LoginLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginLoad dialog


CLoginLoad::CLoginLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginLoad)
	m_name = _T("");
	m_Server = _T("");
	m_Port = 0;
	//}}AFX_DATA_INIT
}


void CLoginLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginLoad)
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_SEVER, m_Server);
	DDX_Text(pDX, IDC_IP, m_Port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginLoad, CDialog)
	//{{AFX_MSG_MAP(CLoginLoad)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginLoad message handlers
