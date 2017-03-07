#include "stdafx.h"
#include "myapplet.h"
#include "demodlg.h"


//////////////// Locals / Defines  ////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The one and only app
CApp theApp;




//////////////// Implementation ///////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CApp, CControlPanelApp);

LRESULT CApp::OnInit()
{
  //Add the control panel applets to the control panel
  AddApplet(new CControlPanelApplet(IDR_APPLET1, RUNTIME_CLASS(CDemoDlg))); //Example of a dynamic control panel applet
  AddApplet(new CControlPanelApplet(IDR_APPLET2, IDS_APPLET2_DESCRIPTION, RUNTIME_CLASS(CDemoPropertySheet))); //Example of a static control panel applet

  return CControlPanelApp::OnInit(); 
}
