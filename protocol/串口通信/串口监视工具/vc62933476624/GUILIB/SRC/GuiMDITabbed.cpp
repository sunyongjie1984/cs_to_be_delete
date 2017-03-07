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
// Modified by : Francisco Campos
// Version 1.0.1
//-----------------------------------------------------------------------//
#include "stdafx.h"
#include "afxpriv.h"
#include "..\header\guimditabbed.h"
#include "..\header\GuiMDIFrame.h"
#include "..\header\MenuBar.h"

BEGIN_MESSAGE_MAP(CGuiMDITabbed, CGuiTabbed)
	  ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
	  ON_WM_TIMER()
END_MESSAGE_MAP()


LRESULT CGuiMDITabbed::OnSizeParent(WPARAM, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS* pParams = (AFX_SIZEPARENTPARAMS*)lParam;
    CRect rc=pParams->rect;

	CFrameWnd* pParent = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());
	CGuiMDIFrame* p= (CGuiMDIFrame*)pParent;
	ASSERT_VALID(p);

	CMenuBar *m=p->GetMenuBar();
	if (rc.top ==0 ) 
	{
		SetTimer(1,100,NULL);
		
	}
	if (GetCount() > 0 && m->IsWindowVisible())
	{
		pParams->rect.top += 24;	
		pParams->rect.left+=2;
		pParams->rect.right-=1;	
		pParams->rect.bottom-=1;		
		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
   MoveWindow(rc.left, rc.top , rc.Width(), rc.Height(), true);
   CClientDC dc(this);
   GetClientRect(rc);
   dc.Draw3dRect(rc,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
   
   return 0;
}

void CGuiMDITabbed::OnTimer(UINT nIDEvent) 
{

	UpdateWindows();
	CFrameWnd* pParent = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());
	CGuiMDIFrame* p= (CGuiMDIFrame*)pParent;
	ASSERT_VALID(p);
	KillTimer(1);
	CMenuBar *m=p->GetMenuBar();
	if (!m->IsWindowVisible())
	{
		CRect rc;
		ShowWindow(SW_HIDE);
		p->RecalcLayout();
	}
	if(m->IsFloating())
			p->RecalcLayout();

	
}

CGuiMDITabbed::CGuiMDITabbed(void)
{
	pParentWindow = NULL;
}

CGuiMDITabbed::~CGuiMDITabbed(void)
{
}


void CGuiMDITabbed::OnScrollClose()
{
	CWnd* pWnd=GetNumWnd(GetCurtab());
	if (pWnd==NULL)
	{
		
		return;
	}
	::SendMessage(AfxGetMainWnd()->m_hWnd,WM_GUI_MESSAGE,
		MAKEWPARAM(WM_GUI_TAB_CLOSE,0),MAKELPARAM(GetCurtab(),GetCount()));	
	pWnd->SendMessage(WM_CLOSE);
	UpdateWindows();
	if (GetCurtab()== 0)
		GetParentFrame()->RecalcLayout();
}

void CGuiMDITabbed::UpdateWindows()
{
	
CFrameWnd* pParent = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());

	SetTimer(1,200,NULL);
	CWnd* pWnd=CWnd::FromHandle(::GetTopWindow(GetParentFrame()->GetSafeHwnd()));	
	char ClassName[32];
	
	while (pWnd != NULL)
	{
		::GetClassName(pWnd->GetSafeHwnd(),ClassName,32);
		CString szClassName=ClassName;
		if(szClassName=="MDIClient")
			break;
		pWnd=pWnd->GetNextWindow();
	}
	ASSERT(::IsWindow(pWnd->GetSafeHwnd()));
	//primero adicionar los nuevos
	
	
	
	CWnd* pChild= CWnd::FromHandle(::GetTopWindow(pWnd->GetSafeHwnd()));	
	while(pChild != NULL)
	{
		CString m_Caption;
		pChild->GetWindowText(m_Caption);
		if (!m_Caption.IsEmpty()) 
		{
			if (!FindItem(pChild->GetSafeHwnd()))
				Addtab(pChild,m_Caption,-1);
			else
				UpdateCaption(pChild,m_Caption);
		}
		
		pChild= CWnd::FromHandle(::GetNextWindow(pChild->GetSafeHwnd(), GW_HWNDNEXT));
		
	}
	
	
	//---eliminar las ventanas borradas
	int nNumtabs=GetCount();
	for (int i=0; i< nNumtabs; i++)
	{
			CWnd* pWnd=GetNumWnd(i);
			if (!::IsWindow(HWND(pWnd->GetSafeHwnd())))
			{
				DeleteTab(i);
				UpdateWindow();
				break;
			}
	}
	SetTimer(1,100,NULL);
	
}



