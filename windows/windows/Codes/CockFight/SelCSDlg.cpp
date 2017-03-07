// SelCSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CockFight.h"
#include "SelCSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelCSDlg dialog


CSelCSDlg::CSelCSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelCSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelCSDlg)
	m_nPort = 8000;
	m_strSvrName = _T("yanky");
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CSelCSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelCSDlg)
	DDX_Control(pDX, IDC_CMB_PIC, m_cmbPic);
	DDX_Control(pDX, IDC_CMB_CS, m_cmbSelCS);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_SEVERNAME, m_strSvrName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelCSDlg, CDialog)
	//{{AFX_MSG_MAP(CSelCSDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelCSDlg message handlers

void CSelCSDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	m_cmbSelCS.SetCurSel(1);
	COLORREF clrRef = SetBkColor(GetDC()->m_hDC,RGB(1,1,1));
	SetBkColor(GetDC()->m_hDC,clrRef);
	m_cmbPic.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),FALSE);

}

void CSelCSDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_nIndex = m_cmbSelCS.GetCurSel();
	CDialog::OnOK();
}
