/*
* Copyright (c) 2004,NLSoft 
* Http://newnan.8u8.com
* All rights reserved. At 延吉
* 
* 文件名称：NL_Button_Test.h
* 文件标识：NL_Button_Test Class
* 摘    要：主要DrawItem函数
* 
* 当前版本：1.0
* 作    者：南龙
* 完成日期：2002年8月3日
*
* 原作者  ：
* 摘    要：继承CButton
* 提    示：判断覆盖时还有点.....
*/

#if !defined(AFX_NL_BUTTON_H__FD3637C3_19C6_4BF3_A8B4_6BEF2258DCD2__INCLUDED_)
#define AFX_NL_BUTTON_H__FD3637C3_19C6_4BF3_A8B4_6BEF2258DCD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NL_Button_Test.h : header file
//

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// NL_Button_Test window

class NL_Button_Test : public CButton
{
// Construction
public:
	NL_Button_Test();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NL_Button_Test)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~NL_Button_Test();
	// Generated message map functions
protected:
	//{{AFX_MSG(NL_Button_Test)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	void DrawItem( LPDRAWITEMSTRUCT lpDIS);
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bIsInBtn;
	BOOL m_bOver;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NL_BUTTON_H__FD3637C3_19C6_4BF3_A8B4_6BEF2258DCD2__INCLUDED_)
