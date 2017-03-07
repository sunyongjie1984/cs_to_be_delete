//-----------------------------------------------------------------------//
// This is a part of the GuiLib MFC Extention.							 //	
// Autor  :  Francisco Campos											 //
// (C) 2002 Francisco Campos <www.beyondata.com> All rights reserved     //
// This code is provided "as is", with absolutely no warranty expressed  //
// or implied. Any use is at your own risk.								 //		
// You must obtain the author's consent before you can include this code //
// in a software library.												 //
// If the source code in  this file is used in any application			 //
// then acknowledgement must be made to the author of this program		 //	
// fco_campos@tutopia.com													 //
//-----------------------------------------------------------------------//

#include "stdafx.h"
#include "..\header\GuiFDir.h"
#include <Dlgs.h>     
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFDir

#define ID_BUTTONOK  200
#define IDEDIT		 201

IMPLEMENT_DYNAMIC(CGuiFDir, CFileDialog)

CGuiFDir::CGuiFDir(CWnd* parent)
:CFileDialog(TRUE, NULL,"*..*", 
             OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
             NULL, parent)
{
    m_ofn.lpstrTitle = _T("Select Folder");
	m_ofn.lpstrFilter =_T("Directory");
	
	
}


BEGIN_MESSAGE_MAP(CFWnd, CWnd)
        //ON_BN_CLICKED(ID_BUTTONOK, OnOpen)
		ON_BN_CLICKED(IDOK, OnOpen)
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CGuiFDir,CFileDialog)
	//{{AFX_MSG_MAP(CFDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CFWnd::OnOpen()
{
	CString m_GetPath;
	GetDlgItem(IDEDIT)->GetWindowText(m_GetPath);
	DWORD attr = GetFileAttributes((LPCTSTR)m_GetPath);
    if (attr != 0xFFFFFFFF && (attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
     {
		::EndDialog(m_hWnd, IDOK);
     }
	 
}
void CGuiFDir::OnInitDone()
{
	CRect rc;
	CRect rcCancel;
	CRect rclst;
	CString m_Caption;
	VERIFY(cw=GetParent());
	VERIFY(cfwn.SubclassWindow(cw->m_hWnd));
	cw->GetDlgItem(stc3)->SetWindowText(_T("Folder:"));
	cw->GetDlgItem(stc2)->SetWindowText(_T("Selection type:"));
    cw->GetDlgItem(edt1)->GetWindowRect(rc);
	cw->ScreenToClient(rc);
	m_cedit.Create(WS_TABSTOP | WS_VISIBLE | WS_CHILD,rc,cw,IDEDIT);
	m_cedit.SetWindowPos(this,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
	m_cedit.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME);
	m_cedit.SetWindowText(m_ofn.lpstrInitialDir);
	m_cedit.SetFont(cw->GetDlgItem(edt1)->GetFont());
	HideControl(edt1);
	CFileDialog::OnInitDone();
	
}

void CGuiFDir::OnFolderChange()
{
	m_GetPath=GetFolderPath();
	m_cedit.SetWindowText(m_GetPath);
	CFileDialog::OnFolderChange();
}

