#include "stdafx.h"
#include "myapplet.h"
#include "DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDemoDlg, CDialog)

CDemoDlg::CDemoDlg()
	: CDialog(CDemoDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	//}}AFX_DATA_INIT
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



IMPLEMENT_DYNCREATE(CDemoPage1, CPropertyPage)

CDemoPage1::CDemoPage1() : CPropertyPage(CDemoPage1::IDD)
{
	//{{AFX_DATA_INIT(CDemoPage1)
	//}}AFX_DATA_INIT
}

CDemoPage1::~CDemoPage1()
{
}

void CDemoPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoPage1)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CDemoPage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



IMPLEMENT_DYNCREATE(CDemoPage2, CPropertyPage)

CDemoPage2::CDemoPage2() : CPropertyPage(CDemoPage2::IDD)
{
	//{{AFX_DATA_INIT(CDemoPage2)
	//}}AFX_DATA_INIT
}

CDemoPage2::~CDemoPage2()
{
}

void CDemoPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoPage2)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CDemoPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



IMPLEMENT_DYNCREATE(CDemoPropertySheet, CPropertySheet)

CDemoPropertySheet::CDemoPropertySheet()
	:CPropertySheet()
{
  AddPage(&m_Page1);
  AddPage(&m_Page2);
}

CDemoPropertySheet::~CDemoPropertySheet()
{
}

BEGIN_MESSAGE_MAP(CDemoPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDemoPropertySheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

