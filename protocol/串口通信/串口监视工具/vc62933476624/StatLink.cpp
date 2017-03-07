#include "StdAfx.h"
#include "StatLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF CStaticLink::g_colorUnvisited = RGB(0,0,255);
COLORREF CStaticLink::g_colorVisited   = RGB(128,0,128);

HCURSOR	CStaticLink::g_hCursorLink = NULL;

IMPLEMENT_DYNAMIC(CStaticLink, CStatic)

BEGIN_MESSAGE_MAP(CStaticLink, CStatic)
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

CStaticLink::CStaticLink(LPCTSTR lpText, BOOL bDeleteOnDestroy)
{
	m_link = lpText;
	m_color = g_colorUnvisited;
	m_bDeleteOnDestroy = bDeleteOnDestroy;
}

UINT CStaticLink::OnNcHitTest(CPoint point)
{
	return HTCLIENT;
}

HBRUSH CStaticLink::CtlColor(CDC* pDC, UINT nCtlColor)
{
	ASSERT(nCtlColor == CTLCOLOR_STATIC);
	DWORD dwStyle = GetStyle();
	
	HBRUSH hbr = NULL;
	if ((dwStyle & 0xFF) <= SS_RIGHT) {

		if (!(HFONT)m_font) {
			LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfUnderline = TRUE;
			m_font.CreateFontIndirect(&lf);
		}

		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_color);
		pDC->SetBkMode(TRANSPARENT);

		hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	}
	return hbr;
}

void CStaticLink::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_link.IsEmpty()) {
		GetWindowText(m_link);
		if (m_link.IsEmpty())
			return;
	}

	HINSTANCE h = m_link.Navigate();
	if ((UINT)h > 32) {
		m_color = g_colorVisited;
		Invalidate();
	} else {
		MessageBeep(0);
		TRACE(_T("*** WARNING: CStaticLink: unable to navigate link %s\n"),
			(LPCTSTR)m_link);
	}
}


BOOL CStaticLink::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (g_hCursorLink == NULL) {
		static bTriedOnce = FALSE;
		if (!bTriedOnce) {
         CString windir;
         GetWindowsDirectory(windir.GetBuffer(MAX_PATH), MAX_PATH);
         windir.ReleaseBuffer();
         windir += _T("\\winhlp32.exe");
         HMODULE hModule = LoadLibrary(windir);
			if (hModule) {
				g_hCursorLink =
					CopyCursor(::LoadCursor(hModule, MAKEINTRESOURCE(106)));
			}
			FreeLibrary(hModule);
			bTriedOnce = TRUE;
		}
	}
	if (g_hCursorLink) {
		::SetCursor(g_hCursorLink);
		return TRUE;
	}
	return FALSE;
}

void CStaticLink::PostNcDestroy()
{
	if (m_bDeleteOnDestroy)
		delete this;
}
