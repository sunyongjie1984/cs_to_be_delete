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
#include "GuiImageLinkButton.h"
#include "GuiLib.h" 

class GUILIBDLLEXPORT CGuiWorkPanel :
	public CGuiContainer
{
public:
	CGuiWorkPanel(void);
	virtual ~CGuiWorkPanel(void);
	virtual void	RecalLayout();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void  SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void Addlabel(UINT ID_BUTTON,CGuiLabelButton* m_btn);
	void AddImageLink(UINT ID_BUTTON,int nNumImage,CGuiImageLinkButton* m_Linkbtn);
protected:
	CGuiScrollButton m_ToolUp;
	CGuiScrollButton m_ToolDown;
	CImageList	m_imgList;
	CImageList  m_imgListLocal;
	BOOL		m_PressDown;
	BOOL		m_PressUp;
	int			m_nDif;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange( );
	void OnDownd();
	void OnUp();
};
