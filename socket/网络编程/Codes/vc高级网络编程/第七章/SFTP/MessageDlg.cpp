// MessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SFTP.h"
#include "MessageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog


CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CMessageDlg::CMessageDlg()
{
	m_hWnd = NULL;
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageDlg)
	DDX_Control(pDX, IDC_TEXTOUT, m_ctrlEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialog)
	//{{AFX_MSG_MAP(CMessageDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg message handlers

void CMessageDlg::TextOut(CString strOut)
{
	int len = m_ctrlEdit.GetWindowTextLength();
	m_ctrlEdit.SetSel(len,len);
	m_ctrlEdit.ReplaceSel(" \r\n", TRUE);

	m_ctrlEdit.SetSel(len + 1, len + 1);
	m_ctrlEdit.ReplaceSel(strOut, TRUE);
}


BOOL CMessageDlg::Create(CWnd* pParent) 
{
	return CDialog::Create(IDD, pParent);
}
