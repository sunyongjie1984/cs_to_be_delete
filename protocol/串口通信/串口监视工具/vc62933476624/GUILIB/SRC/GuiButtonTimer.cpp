//-----------------------------------------------------------------------//
// This is a part of the GuiLib MFC Extention.							 //	
// Modified by  :  Francisco Campos										 //
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
#include "..\header\GuiButtonTimer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CGuiButtonTimer, CGuiToolButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()


CGuiButtonTimer::CGuiButtonTimer()
{
	bPress=FALSE;
	m_nInterval=50;
}

CGuiButtonTimer::~CGuiButtonTimer()
{

}

void CGuiButtonTimer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!bPress) return;
	bPress=FALSE;
	KillTimer(1);
	//CGuiNormalButton::OnLButtonUp(nFlags, point);
}
void CGuiButtonTimer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bPress) return;
	bPress=TRUE;
	SetTimer(1,m_nInterval,NULL);
	//CGuiNormalButton::OnLButtonDown(nFlags, point);
}

void CGuiButtonTimer::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (bPress == FALSE) return;
	CRect rc;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(rc);
	if (rc.PtInRect(pt))
	{
		CWnd* pParent=GetParent();
		if (IsWindowEnabled())
			pParent->SendMessage(WM_COMMAND,GetDlgCtrlID());
		//bPress=FALSE;
		//KillTimer(1);
	}
	else
	{
		bPress=FALSE;
		KillTimer(1);
		//CGuiNormalButton::OnTimer(nIDEvent);
	}
	
}
