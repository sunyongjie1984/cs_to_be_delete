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
#include "guifolder.h"

#include "GuiLib.h"



//*****************************************************************

class GUILIBDLLEXPORT   CGuiFolderFlat :
	public CGuiFolder
{
public:
	CGuiFolderFlat(void);
	virtual ~CGuiFolderFlat(void);
public:
	virtual void DrawFolder(CFolderBar* cfb,Style m_Style);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
};
