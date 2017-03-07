// SFTPDoc.cpp : implementation of the CSFTPDoc class
//

#include "stdafx.h"
#include "SFTP.h"

#include "SFTPDoc.h"
#include "setupdlg.h"
#include "sftpview.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSFTPDoc

IMPLEMENT_DYNCREATE(CSFTPDoc, CDocument)

BEGIN_MESSAGE_MAP(CSFTPDoc, CDocument)
	//{{AFX_MSG_MAP(CSFTPDoc)
	ON_COMMAND(IDC_FILE_CONNECT, OnFileConnect)
	ON_COMMAND(IDC_FILE_DISCONNECT, OnFileDisconnect)
	ON_COMMAND(IDC_LOGIN, OnLogin)
	ON_UPDATE_COMMAND_UI(IDC_LOGIN, OnUpdateLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFTPDoc construction/destruction

CSFTPDoc::CSFTPDoc()
{
	ftp = new CFTPClient(this);
}

CSFTPDoc::~CSFTPDoc()
{
	delete ftp;
}

BOOL CSFTPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSFTPDoc serialization

void CSFTPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSFTPDoc diagnostics

#ifdef _DEBUG
void CSFTPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSFTPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSFTPDoc commands

void CSFTPDoc::Receive()
{
	ftp->Receive();
}

void CSFTPDoc::OnFileConnect() 
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSFTPView* pWnd = (CSFTPView*)pFrame->GetActiveView();
	pWnd->RemoveAll();

	CSetupDlg dlg;
	if(dlg.DoModal() == IDOK){
		ftp->Logon(dlg.m_strServer , dlg.m_uPort, dlg.m_strUser,
			dlg.m_strPass, "", dlg.m_strProxy, dlg.m_strProxyUser,
			dlg.m_strProxyPass, dlg.m_uProxPort, 
			dlg.m_uType);
		ftp->List();
		pWnd->Sort();
	}
}

void CSFTPDoc::RemoveAll()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSFTPView* pWnd = (CSFTPView*)pFrame->GetActiveView();
	pWnd->RemoveAll();

	CListItem* pItem = new CListItem;
	pItem->m_strName = "..";
	pItem->m_bDirectory = TRUE;
	pWnd->AddItem(pItem);
}

void CSFTPDoc::AddLine(CString strLine)
{
	CListItem* pItem = new CListItem();
	if(!pItem->ParseLine(strLine)){
		delete pItem;
		return;
	}
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSFTPView* pWnd = (CSFTPView*)pFrame->GetActiveView();
	pWnd->AddItem(pItem);
}

void CSFTPDoc::RetreiveFile(CString filename)
{
	CFileDialog dlg(FALSE, NULL, "test", OFN_EXTENSIONDIFFERENT | 
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					"All Files(*.*)|*.*||");

	if(dlg.DoModal() == IDOK){
		CString strFileName = dlg.m_ofn.lpstrFile;
		ftp->MoveFile(filename, strFileName, TRUE);
	}
}

void CSFTPDoc::CD(CString dir)
{
	dir.TrimLeft();
	dir.TrimRight();
	CString cmd = "CWD " + dir;// + "\r\n";

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSFTPView* pWnd = (CSFTPView*)pFrame->GetActiveView();
	pWnd->RemoveAll();

	ftp->FTPcommand(cmd);
	ftp->FTPcommand("PWD");
	ftp->List();
	pWnd->Sort();
}

void CSFTPDoc::Back()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSFTPView* pWnd = (CSFTPView*)pFrame->GetActiveView();

	ftp->FTPcommand("CDUP");
	ftp->List();
	pWnd->Sort();
}

void CSFTPDoc::OnFileDisconnect() 
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CSFTPView* pWnd = (CSFTPView*)pFrame->GetActiveView();
	pWnd->RemoveAll();

	ftp->Disconnect();	
}

void CSFTPDoc::OnLogin() 
{
	if(ftp->m_dlgMsg.m_hWnd == NULL)
		return;
	ftp->m_dlgMsg.ShowWindow(!ftp->m_dlgMsg.IsWindowVisible());	
}

void CSFTPDoc::OnUpdateLogin(CCmdUI* pCmdUI) 
{
	if(ftp->m_dlgMsg.m_hWnd == NULL)
		return;

	pCmdUI->SetCheck(ftp->m_dlgMsg.IsWindowVisible());	
}
