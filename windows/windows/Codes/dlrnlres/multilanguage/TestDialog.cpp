// TestDialog.cpp : implementation file
//

#include "stdafx.h"
#include "multilanguage.h"
#include "TestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog


CTestDialog::CTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDialog)
	m_sEdit = _T("");
	//}}AFX_DATA_INIT
}


void CTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDialog)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_Grid);
	DDX_Text(pDX, IDC_EDIT1, m_sEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDialog, CDialog)
	//{{AFX_MSG_MAP(CTestDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDialog message handlers

BEGIN_EVENTSINK_MAP(CTestDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(CTestDialog)
	ON_EVENT(CTestDialog, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTestDialog::OnClickMsflexgrid1() 
{
	m_Grid.SetRows(2);
	m_Grid.SetCols(2);
		m_Grid.SetTextMatrix(0,0,"sfsdf");
}
