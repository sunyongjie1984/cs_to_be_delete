#ifndef __MYAPPLET_H__
#define __MYAPPLET_H__

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "cpl_pp.h"


class CApp : public CControlPanelApp
{
protected:
  virtual LRESULT OnInit();

  DECLARE_DYNAMIC(CApp);
};

#endif //__MYAPPPLET_H__
