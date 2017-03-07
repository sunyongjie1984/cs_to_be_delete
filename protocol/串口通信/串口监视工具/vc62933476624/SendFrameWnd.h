#if !defined(AFX_SENDFRAMEWND_H__4CED9533_A41F_4B75_8F07_EAAF2BDD1271__INCLUDED_)
#define AFX_SENDFRAMEWND_H__4CED9533_A41F_4B75_8F07_EAAF2BDD1271__INCLUDED_

#include "GUILIB\HEADER\GuiContainer.h"	// Added by ClassView
#include "SCCSendEdit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFrameWnd.h : header file
//
#include "GUILIB\HEADER\guicontrolbar.h"
#include "GUILIB\HEADER\GuiMiniTool.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CSendFrameWnd window

class CSendFrameWnd : public CGuiControlBar
{
// Construction
public:
	CSendFrameWnd();

// Attributes
public:

// Operations
public:
	CSCCSendEdit m_xrec;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFrameWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveConfig();
	void DrawLnCol(int nLine,int nCol);
	BOOL CreateX(LPCTSTR str,CWnd* pf,UINT unID,DWORD dwstyle=WS_CHILD|WS_VISIBLE);
	virtual ~CSendFrameWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSendFrameWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_XRICHEDIT_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGuiContainer m_cntr;
	
	CGuiMiniTool m_mini;
	void RecvSendWnd(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFRAMEWND_H__4CED9533_A41F_4B75_8F07_EAAF2BDD1271__INCLUDED_)
