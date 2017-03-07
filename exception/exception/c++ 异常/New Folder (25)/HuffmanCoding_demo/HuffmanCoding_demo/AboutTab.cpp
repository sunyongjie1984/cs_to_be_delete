// AboutTab.cpp : implementation file
//

#include "stdafx.h"
#include "NewTab.h"
#include "AboutTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutTab dialog


CAboutTab::CAboutTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CAboutTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutTab)
	DDX_Control(pDX, IDC_BUTTON_EMAIL, m_btnEmail);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutTab, CTabPageSSL)
	//{{AFX_MSG_MAP(CAboutTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutTab message handlers

BOOL CAboutTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();

	// TODO: Add extra initialization here
	m_btnEmail.SetSSLButtonBitmap (IDB_BITMAP_EMAIL);
	m_btnEmail.SetSSLColor (CButtonSSL::SSL_UP_TEXT_COLOR, RGB (0, 0, 255));
	m_btnEmail.SetSSLColor (CButtonSSL::SSL_OVER_TEXT_COLOR, RGB (0, 0, 255));
	m_btnEmail.SetSSLColor (CButtonSSL::SSL_DOWN_TEXT_COLOR, RGB (0, 0, 255));
	m_btnEmail.SetSSLButtonFont (_T("MS Sans Serif"), 14, TRUE);
	m_btnEmail.SetSSLButtonURL (_T("mailto:zxt0123@163.com?Subject=Huffman Coding"));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
