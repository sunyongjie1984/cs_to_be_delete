// GraphicsProgrammeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProgrammeTechnicAccumulate.h"
#include "GraphicsProgrammeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsProgrammeDlg dialog


CGraphicsProgrammeDlg::CGraphicsProgrammeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphicsProgrammeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphicsProgrammeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pShowBmpFrm = NULL;
}


void CGraphicsProgrammeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphicsProgrammeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphicsProgrammeDlg, CDialog)
	//{{AFX_MSG_MAP(CGraphicsProgrammeDlg)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_BITMAP_FILE, OnButtonShowBitmapFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsProgrammeDlg message handlers

void CGraphicsProgrammeDlg::OnButtonShowBitmapFile() 
{
	if ( NULL == m_pShowBmpFrm )
	{
		m_pShowBmpFrm = new CShowBitmapChildWindowFrame;

		RECT rect;

		rect.bottom = 600;
		rect.left	= 0;
		rect.right	= 600;
		rect.top	= 0;

		const RECT &rectSpecify = rect;

		BOOL bStatus;

		bStatus = m_pShowBmpFrm->Create( NULL,
										"",
										WS_OVERLAPPEDWINDOW,
										rectSpecify,
										NULL );

		if ( NULL == bStatus )
		{
			//logerror
			return;
		}

		m_pShowBmpFrm->ShowWindow( SW_SHOW );
	}
	else
	{
		m_pShowBmpFrm->SetActiveWindow();
		
		m_pShowBmpFrm->ShowWindow( SW_SHOW );
	}
}

void CGraphicsProgrammeDlg::OnOK() 
{
	char szTest[] = "192.168.101.206";
	char szHint[100] = {0};
	sprintf( szHint, "%d", sizeof(szTest) );
	::MessageBox( NULL, szHint, "", MB_OK );	
	CDialog::OnOK();
}
