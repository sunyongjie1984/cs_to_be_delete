#ifndef _STATLINK_H
#define _STATLINK_H

class CHyperlink : public CString 
{
public:
	CHyperlink(LPCTSTR lpLink = NULL) : CString(lpLink) { }
	~CHyperlink() { }
	const CHyperlink& operator=(LPCTSTR lpsz) {
		CString::operator=(lpsz);
		return *this;
	}
	operator LPCTSTR() {return CString::operator LPCTSTR();	}
	HINSTANCE Navigate() { CWaitCursor wait;
		return  IsEmpty() ? NULL :
			ShellExecute(0, _T("open"), *this, 0, 0, SW_SHOWNORMAL);
	}
};

class CStaticLink : public CStatic 
{
public:
	DECLARE_DYNAMIC(CStaticLink)
	CStaticLink(LPCTSTR lpText = NULL, BOOL bDeleteOnDestroy=FALSE);
	~CStaticLink() { }

	BOOL SubclassDlgItem(UINT nID, CWnd* pParent, LPCTSTR lpszLink=NULL) {
		if (lpszLink)		m_link = lpszLink;
		return CStatic::SubclassDlgItem(nID, pParent);
	}

	CHyperlink	m_link;
	COLORREF		m_color;

	static COLORREF g_colorUnvisited;
	static COLORREF g_colorVisited;

	static HCURSOR	 g_hCursorLink;

protected:
	CFont			m_font;
	BOOL			m_bDeleteOnDestroy;

	virtual void PostNcDestroy();

	DECLARE_MESSAGE_MAP()
	afx_msg UINT	OnNcHitTest(CPoint point);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL	OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#endif _STATLINK_H
