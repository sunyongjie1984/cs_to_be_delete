// NL_Button_Test.cpp : implementation file
//

#include "stdafx.h"
#include "TestDrawItemFunction.h"
#include "NL_Button_Test.h"
#include "TestDrawItemFunctionDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
void Msg(char *szFormat, ...);
/////////////////////////////////////////////////////////////////////////////
// NL_Button_Test

NL_Button_Test::NL_Button_Test()
{
	m_bOver=false;
	m_bIsInBtn=false;
}

NL_Button_Test::~NL_Button_Test()
{
}


BEGIN_MESSAGE_MAP(NL_Button_Test, CButton)
	//{{AFX_MSG_MAP(NL_Button_Test)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NL_Button_Test message handlers
void NL_Button_Test::DrawItem( LPDRAWITEMSTRUCT lpDIS )
{
	/*
	typedef struct tagDRAWITEMSTRUCT {
    UINT   CtlType;
    UINT   CtlID;
    UINT   itemID;
    UINT   itemAction;
    UINT   itemState;
    HWND   hwndItem;
    HDC    hDC;
    RECT   rcItem;
    DWORD  itemData;
	} DRAWITEMSTRUCT;
	*/
	CTestDrawItemFunctionDlg* pDlg;
	CListBox *plb;
	pDlg=(CTestDrawItemFunctionDlg*)::AfxGetMainWnd();
	ASSERT(pDlg);
	plb=&(pDlg->m_ListBox);
	CRect rc,rcTemp;
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	rc=lpDIS->rcItem;
	pDC->FillRect(rc,&CBrush(GetSysColor(COLOR_BTNFACE)));

	CString s;
	s.Format("BT CtlType %04X "
			 "CtlID %04X "
			 "itemID %06X "
			 "itemAction %04X "
			 "itemState %08X "
			 "wnd %08X "
			 "dc %08X "
			 "rc (%03d %03d %03d %03d) "
			 "itemData %08X",
			 lpDIS->CtlType,
			 lpDIS->CtlID,
			 lpDIS->itemID,	
			 lpDIS->itemAction,
			 lpDIS->itemState,
			 lpDIS->hwndItem,
			 lpDIS->hDC,
			 rc.left,rc.top,rc.right,rc.bottom,
			 lpDIS->itemData);
	plb->InsertString(0,s);
	s.ReleaseBuffer();

	if(m_bOver) //in the button
	{
		DrawBorder(pDC,rc,2);
		pDC->DrawText("Over",&rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}
	else
	{
		//out the button
		DrawBorder(pDC,rc,0);
		pDC->DrawText("Button",&rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

	if(lpDIS->itemState & 	ODS_DISABLED)//disabled
	{
		DrawBorder(pDC,rc,0);
		pDC->DrawText("disabled",&rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

	if(lpDIS->itemState & ODS_FOCUS)//focus
	{
		DrawBorder(pDC,rc,0);
		rcTemp=rc;
		rcTemp.OffsetRect(0,3);
		pDC->DrawText("Focus",&rcTemp,DT_SINGLELINE|DT_TOP|DT_CENTER);
	}
	
	if(lpDIS->itemState & ODS_SELECTED && lpDIS->itemState & ODS_FOCUS)//click
	{
		DrawBorder(pDC,rc,1);
		pDC->DrawText("Click",&rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

}

void NL_Button_Test::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bOver=true;
	if(MK_LBUTTON&nFlags)return;   
	SetCapture();
	ClientToScreen(&point);
	static int i=0;
	if(WindowFromPoint(point)->m_hWnd!=this->m_hWnd)
	{
		i=0;
		m_bOver=false;
		ReleaseCapture();
		Invalidate(0);
	}
	if(m_bOver)
	{
		i++;
		if(i==1)
			Invalidate(0);
		i=1;
	}
	CButton::OnMouseMove(nFlags, point);
}

void Msg(char *szFormat, ...)
{
    TCHAR szBuffer[512];
    va_list pArgs;
    va_start(pArgs, szFormat);
    vsprintf(szBuffer, szFormat, pArgs);
    va_end(pArgs);
	::AfxGetMainWnd()->SetWindowText(szBuffer);
}
