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

#pragma once
#include "guicontainer.h"
#include "guiToolButton.h"
#include "GuiButton.h" 
#include "GuiLib.h" 
#include "GuiButtonTimer.h"

class GUILIBDLLEXPORT CGuiPanelAccess :
	public CGuiContainer
{
public:
	CGuiPanelAccess(void);
	virtual ~CGuiPanelAccess(void);
	virtual void	RecalLayout();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void  SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void AddButton(UINT ID_BUTTON,int nNumImage,CGuiToolButton* m_pBtn,CString m_sztext);
protected:
	CGuiButtonTimer m_ToolUp;
	CGuiButtonTimer m_ToolDown;
	CImageList	m_imgList;
	CImageList  m_imgListLocal;
	BOOL		m_PressDown;
	BOOL		m_PressUp;
	int			m_nDif;
	CFont		m_cfont;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	void OnDownd();
	void OnUp();
};
