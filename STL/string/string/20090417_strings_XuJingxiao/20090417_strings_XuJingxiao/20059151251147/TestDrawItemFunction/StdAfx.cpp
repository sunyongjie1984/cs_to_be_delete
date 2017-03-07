// stdafx.cpp : source file that includes just the standard includes
//	TestDrawItemFunction.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void DrawBorder(CDC *pDC, CRect rc,int iMode/* 0 out 1 in 2 flat 3 no*/)
{
	CPen penHighLight(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
	CPen penShadow(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
	CPen *oldPen;
	if(iMode==0)	
		oldPen=(CPen*)pDC->SelectObject(&penHighLight);
	if(iMode==1)	
		oldPen=(CPen*)pDC->SelectObject(&penShadow);
	if(iMode==2)
		oldPen=(CPen*)pDC->SelectObject(&penShadow);
	if(iMode<3)
	{
		pDC->MoveTo(rc.left,rc.bottom);
		pDC->LineTo(rc.left,rc.top);
		pDC->LineTo(rc.right-1,rc.top);
	}
	if(iMode==0)
		pDC->SelectObject(&penShadow);
	if(iMode==1)
		pDC->SelectObject(&penHighLight);
	if(iMode<3)
	{
		pDC->LineTo(rc.right-1,rc.bottom-1);
		pDC->LineTo(rc.left,rc.bottom-1);
		pDC->SelectObject(oldPen);
	}
}
