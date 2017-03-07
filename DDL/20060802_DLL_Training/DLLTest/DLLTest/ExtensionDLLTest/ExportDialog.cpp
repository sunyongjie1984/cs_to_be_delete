// ExportDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExportDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CExportDialog, CDialog,1)

// CExportDialog dialog
//
CExportDialog::CExportDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CExportDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExportDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExportDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExportDialog, CDialog)
	//{{AFX_MSG_MAP(CExportDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//
// CExportDialog message handlers

void CExportDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	BITMAP bmpInfo = { 0 };
	m_bmp.GetBitmap( &bmpInfo );
	
	CDC dcMemory;
	dcMemory.CreateCompatibleDC( &dc );
	CBitmap* pOldBitmap = dcMemory.SelectObject( &m_bmp );
	
	dc.BitBlt( 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 
		0, 0, SRCCOPY );
	
	dcMemory.SelectObject( pOldBitmap );
}

BOOL CExportDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_bmp.LoadBitmap( IDB_WATERLINES );
	
	return TRUE;  // return TRUE unless you set the focus to a control
}
