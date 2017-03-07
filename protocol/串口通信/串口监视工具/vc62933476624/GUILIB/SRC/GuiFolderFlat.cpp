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
#include "..\header\guifolderflat.h"
#include "..\header\GuiDrawLayer.h"
#include "..\header\guifolderflat.h"
CGuiFolderFlat::CGuiFolderFlat(void)
{
}

CGuiFolderFlat::~CGuiFolderFlat(void)
{
}


void CGuiFolderFlat::DrawFolder(CFolderBar* cfb,Style m_Style)
{
	CRect rc=cfb->m_rect;
	CBrush cb;
	CClientDC pDC(this);
	cb.CreateSysColorBrush(COLOR_BTNFACE);
	rc.top+=1;
	//rc.right-=1;
	rc.right+=1;
	pDC.FillRect(&rc,&cb);

	pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorShadow());
	
	int OldMode=pDC.SetBkMode(TRANSPARENT);
	cfont = pDC.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CString m_cadBreak=cfb->m_lpMsg;
	int cont=m_cadBreak.GetLength();
	CSize coor=pDC.GetTextExtent(m_cadBreak,m_cadBreak.GetLength());
	if ( coor.cx > rc.Width())
	{
		rc.left+=1;
		while(cont > 1 )
		{
			CString m_scadtemp=m_cadBreak+"...";
			CSize coor=pDC.GetTextExtent(m_scadtemp,m_scadtemp.GetLength());
			if(coor.cx > rc.Width())
				m_cadBreak=m_cadBreak.Left(m_cadBreak.GetLength()-1);
			else
				break;
			cont--;
		}
		m_cadBreak+=_T("...");
		rc.right+=3;
		
			pDC.DrawText(m_cadBreak,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	}
	else
	{
	  if (m_typel!=mOutlook)
			pDC.DrawText(cfb->m_lpMsg,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	  else	
			pDC.DrawText(cfb->m_lpMsg,rc,DT_WORDBREAK|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}

   	pDC.SetBkColor(OldMode);


}
BEGIN_MESSAGE_MAP(CGuiFolderFlat, CGuiFolder)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CGuiFolderFlat::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(::LoadCursor(NULL,IDC_SIZEALL));
	CGuiFolder::OnLButtonDown(nFlags, point);
}
