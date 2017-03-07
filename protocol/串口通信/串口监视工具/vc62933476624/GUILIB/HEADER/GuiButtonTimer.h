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
// version : 1.0														 //
//-----------------------------------------------------------------------//

#if !defined(AFX_GUIBUTTONTIMER_H__2F022AE8_E4A9_444C_8827_AA1D82AC5BE0__INCLUDED_)
#define AFX_GUIBUTTONTIMER_H__2F022AE8_E4A9_444C_8827_AA1D82AC5BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiLib.h" 
#include "GuiToolButton.h" 

class GUILIBDLLEXPORT CGuiButtonTimer : public CGuiToolButton  
{
public:
	CGuiButtonTimer();
	virtual ~CGuiButtonTimer();
	void SetWaitClick(int nInterval=50){m_nInterval=nInterval;}
protected:
	BOOL	bPress;
	int		m_nInterval;
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_GUIBUTTONTIMER_H__2F022AE8_E4A9_444C_8827_AA1D82AC5BE0__INCLUDED_)
