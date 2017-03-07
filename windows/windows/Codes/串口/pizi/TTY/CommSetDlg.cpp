// CommSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TTY.h"
#include "CommSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommSetDlg dialog


CCommSetDlg::CCommSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommSetDlg::IDD, pParent)
{
	m_nParity = 0;
	m_nStopBits = 0;
	//{{AFX_DATA_INIT(CCommSetDlg)
	m_sBaud = _T("");
	m_sDataBits = _T("");
	m_bEcho = FALSE;
	m_bNewLine = FALSE;
	m_sPort = _T("");
	//}}AFX_DATA_INIT
}

void CCommSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommSetDlg)
	DDX_Control(pDX, IDC_STOPBITS, m_ctrlStopBits);
	DDX_Control(pDX, IDC_PARITY, m_ctrlParity);
	DDX_Control(pDX, IDC_PORT, m_ctrlPort);
	DDX_Control(pDX, IDC_DATABITS, m_ctrlDataBits);
	DDX_Control(pDX, IDC_BAUD, m_ctrlBaud);
	DDX_CBString(pDX, IDC_BAUD, m_sBaud);
	DDX_CBString(pDX, IDC_DATABITS, m_sDataBits);
	DDX_Check(pDX, IDC_ECHO, m_bEcho);
	DDX_Check(pDX, IDC_NEWLINE, m_bNewLine);
	DDX_CBString(pDX, IDC_PORT, m_sPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCommSetDlg, CDialog)
	//{{AFX_MSG_MAP(CCommSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommSetDlg message handlers

BOOL CCommSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//对对话框的显示情况进行初始化
	m_ctrlPort.AddString(_T("COM1"));
	m_ctrlPort.AddString(_T("COM2"));

	m_ctrlParity.AddString(_T("NONE"));
	m_ctrlParity.AddString(_T("EVEN"));
	m_ctrlParity.AddString(_T("ODD"));
	m_ctrlParity.SetCurSel(m_nParity);

	m_ctrlDataBits.AddString(_T("5"));
	m_ctrlDataBits.AddString(_T("6"));
	m_ctrlDataBits.AddString(_T("7"));
	m_ctrlDataBits.AddString(_T("8"));
	

	m_ctrlBaud.AddString(_T("300"));
	m_ctrlBaud.AddString(_T("600"));
	m_ctrlBaud.AddString(_T("1200"));
	m_ctrlBaud.AddString(_T("2400"));
	m_ctrlBaud.AddString(_T("9600"));
	m_ctrlBaud.AddString(_T("14400"));
	m_ctrlBaud.AddString(_T("19200"));
	m_ctrlBaud.AddString(_T("38400"));
	m_ctrlBaud.AddString(_T("57600"));

	m_ctrlStopBits.AddString(_T("1"));
	m_ctrlStopBits.AddString(_T("1.5"));
	m_ctrlStopBits.AddString(_T("2"));
	m_ctrlStopBits.SetCurSel(m_nStopBits);

	GetDlgItem(IDC_PORT)->EnableWindow(!m_bConnected);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//"确定"按钮的响应函数
void CCommSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	UpdateData(FALSE);

	m_nParity = m_ctrlParity.GetCurSel();
	m_nStopBits = m_ctrlStopBits.GetCurSel();
	
	CDialog::OnOK();
}
