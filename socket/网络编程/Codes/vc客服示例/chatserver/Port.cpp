// Port.cpp : implementation file
//

#include "stdafx.h"
#include "chatserver.h"
#include "Port.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPort dialog


CPort::CPort(CWnd* pParent /*=NULL*/)
	: CDialog(CPort::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPort)
	m_port = 8800;
	//}}AFX_DATA_INIT
}


void CPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPort)
	DDX_Text(pDX, IDC_EDIT1, m_port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPort, CDialog)
	//{{AFX_MSG_MAP(CPort)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPort message handlers
