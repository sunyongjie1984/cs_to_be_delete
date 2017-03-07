// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDll.h"
#include "TestDlg.h"


// CTestDlg dialog

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)
CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
END_MESSAGE_MAP()


// CTestDlg message handlers
