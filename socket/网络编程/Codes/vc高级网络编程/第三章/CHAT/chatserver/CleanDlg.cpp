// CleanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chatsrvr.h"
#include "CleanDlg.h"
#include "Mainfrm.h"
//#include "Srvrvw.h"
#include "Srvrdoc.h"
#include "Clntsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCleanDlg dialog


CCleanDlg::CCleanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCleanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCleanDlg)
	m_cleanname = _T("");
	//}}AFX_DATA_INIT
}


void CCleanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCleanDlg)
	DDX_Control(pDX, IDC_CLEANLIST, m_cleanlist);
	DDX_LBString(pDX, IDC_CLEANLIST, m_cleanname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCleanDlg, CDialog)
	//{{AFX_MSG_MAP(CCleanDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCleanDlg message handlers

BOOL CCleanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	   m_cleanname="";
		m_cleanlist.ResetContent();
		CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
         CServerDoc* doc=(CServerDoc* )(frame->GetActiveView()->GetDocument());
		   for(POSITION pos=doc->m_connectionList.GetHeadPosition();pos;)
				{
			   CClientSocket* sock=(CClientSocket*)(doc->m_connectionList.GetNext(pos));
			   m_cleanlist.AddString(sock->name);
				}  
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
