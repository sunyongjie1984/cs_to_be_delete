#include "stdafx.h"
#include "cpl_pp.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////// Implementation ///////////////////////////////////////////////

CControlPanelApp* GetControlPanelApp()
{
  CControlPanelApp* pApp = (CControlPanelApp*) AfxGetApp();
  ASSERT(pApp);
  ASSERT(pApp->IsKindOf(RUNTIME_CLASS(CControlPanelApp)));
  return pApp;
}

LONG APIENTRY CPlApplet(HWND hWndCPl, UINT uMsg, LONG lParam1, LONG lParam2)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

  //Convert from the SDK world to the C++ world by calling the 
  //App's OnCplMsg method
  CControlPanelApp* pApp = GetControlPanelApp();
  return pApp->OnCplMsg(hWndCPl, uMsg, lParam1, lParam2);
} 



IMPLEMENT_DYNAMIC(CControlPanelApplet, CCmdTarget);

CControlPanelApplet::CControlPanelApplet(UINT nResourceID, CRuntimeClass* pUIClass)
{
  //Validate our parameters
  ASSERT(pUIClass);
  ASSERT(pUIClass->IsDerivedFrom(RUNTIME_CLASS(CDialog)) || 
         pUIClass->IsDerivedFrom(RUNTIME_CLASS(CPropertySheet)) ); //The runtime class must be derived from one of these classes

  //Store the parameters away in member variables
  m_nResourceID = nResourceID;
  m_pUIClass = pUIClass;
  m_bDynamic = TRUE;
  m_nDescriptionID = 0;
  m_nPageNumber = 0;

  //Store away the name of the applet for later use
  CString sResource;
  VERIFY(sResource.LoadString(m_nResourceID)); //Did you forget to specify a string resource for the applet?
  AfxExtractSubString(m_sName, sResource, 0);
}

CControlPanelApplet::CControlPanelApplet(UINT nResourceID, UINT nDescriptionID, CRuntimeClass* pUIClass)
{
  //Validate our parameters
  ASSERT(pUIClass);
  ASSERT(pUIClass->IsDerivedFrom(RUNTIME_CLASS(CDialog)) || 
         pUIClass->IsDerivedFrom(RUNTIME_CLASS(CPropertySheet)) ); //The runtime class must be derived from one of these classes

  //Store the parameters away in member variables
  m_nResourceID = nResourceID;
  m_nDescriptionID = nDescriptionID;
  m_pUIClass = pUIClass;
  m_bDynamic = FALSE;
  m_nPageNumber = 0;

  //Store away the name of the applet for later use
  m_sName.LoadString(nResourceID);
}

CControlPanelApplet::~CControlPanelApplet()
{
  //Doesn't need to do anything  
}

LRESULT CControlPanelApplet::OnStartParms(CWnd* /*pParentWnd*/, LPCTSTR lpszExtra)
{
  if (lpszExtra)
    m_nPageNumber = ::_ttoi(lpszExtra) - 1; //We're 0 based

  return 0; //Message was handled
}

LRESULT CControlPanelApplet::OnRun(CWnd* pParentWnd)
{
  CWnd* pWnd = (CWnd*) m_pUIClass->CreateObject(); 
  LRESULT lResult = 1; //Assume failure
  if (pWnd)
  {
    lResult = 0; //Success;
    if (pWnd->IsKindOf(RUNTIME_CLASS(CPropertySheet)))
    {
      CPropertySheet* pSheet = (CPropertySheet*) pWnd;
      pSheet->Construct(m_sName, pParentWnd, m_nPageNumber);
      pSheet->DoModal();
    }
    else
    {
      ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CDialog)));
      CDialog* pDialog = (CDialog*) pWnd;

      //Currently do now observe the pParentWnd for dialog based applets.
      //The reason is that we need to be able to set CDialog::m_pParentWnd 
      //but we cannot do it from here since it is a protected member variable.

      pDialog->DoModal();
    }

    //Don't forget to tidy up the memory used
    delete pWnd;
  }

  return lResult;
}

LRESULT CControlPanelApplet::OnInquire(CPLINFO* pInfo)
{
  if (m_bDynamic)
    return  1; //Fail it, we want OnInquire instead

  pInfo->idIcon = m_nResourceID;    //The resource id of the icon to use
  pInfo->idName = m_nResourceID;    //The resource id of the name
  pInfo->idInfo = m_nDescriptionID; //The resource id of the description
  pInfo->lData  = (LONG) this;

  return 0; //Message was handled
}

LRESULT CControlPanelApplet::OnNewInquire(NEWCPLINFO* pInfo)
{
  if (!m_bDynamic)
    return 1; //Fail it, we want OnInquire instead

  pInfo->dwSize = sizeof(NEWCPLINFO);
  pInfo->dwFlags = 0;
  pInfo->dwHelpContext = 0;
  pInfo->lData = (LONG) this;  

  //Load the icon from the icon resource with the same ID as the string
  //resource "m_nResourceID". This is similar to the way MFC implements doc templates
  //work
  pInfo->hIcon = GetControlPanelApp()->LoadIcon(m_nResourceID);
  ASSERT(pInfo->hIcon != NULL);  //Did you forget to specify an icon for this applet

  //Load the resource string. The format is "Name\nDescription\nHELPFILE.HLP"
  CString sResource;
  VERIFY(sResource.LoadString(m_nResourceID)); //Did you forget to specify a string resource for the applet?

  //Split the string into the 3 parts
  ASSERT(m_sName.GetLength());      //Name should have been loaded
  ASSERT(m_sName.GetLength() < 32); //Structure only allows names of length 31 or less
  _tcscpy(pInfo->szName, m_sName);

  CString sDescription;
  AfxExtractSubString(sDescription, sResource, 1);
  ASSERT(sDescription.GetLength()); //Description should have been loaded
  ASSERT(sDescription.GetLength() < 64); //structure only allows descriptions of length 63 or less
  _tcscpy(pInfo->szInfo, sDescription);

  CString sHelpFile;
  AfxExtractSubString(sHelpFile, sResource, 2);
  if (sHelpFile.GetLength())
  {
    ASSERT(sHelpFile.GetLength() < 128); //structure only allows help file size of length 128 or less
    _tcscpy(pInfo->szHelpFile, sHelpFile);
  }
  else
    _tcscpy(pInfo->szHelpFile, _T(""));

  return 0; //message was handled
}

LRESULT CControlPanelApplet::OnSelect()
{
  return 0; //Default is do nothing for CPL_SELECT
}

LRESULT CControlPanelApplet::OnStop()
{
  return 0; //Default is do nothing. You could if you want
            //post a WM_CLOSE to yourself or do a EndDialog
            //if you wanted to close your applet when the 
            //control panel exits.
}



IMPLEMENT_DYNAMIC(CControlPanelApp, CControlPanelApp);

CControlPanelApp::CControlPanelApp()
{
  //Doesn't need to do anything
}

CControlPanelApp::~CControlPanelApp()
{
  //Free up the memory for all the applets
  while (!m_Applets.IsEmpty())
    delete m_Applets.RemoveHead();
}

void CControlPanelApp::AddApplet(CControlPanelApplet* pApplet)
{
  ASSERT(pApplet);
  m_Applets.AddTail(pApplet);
}

LRESULT CControlPanelApp::OnInit()
{
  //This is the function you should call AddApplet 
  //in, in your derived class
  int nApplets = m_Applets.GetCount();
  if (nApplets == 0)
  {
    ASSERT(FALSE); //You've forget to call AddApplet in your version of OnInit
                   //before calling this versions
  }

  return nApplets;
}

LRESULT CControlPanelApp::OnExit()
{
  //Default is do nothing for CPL_EXIT
  return 1; //Success
}

LRESULT CControlPanelApp::OnCplMsg(HWND hWndCPl, UINT uMsg, LONG lParam1, LONG lParam2)
{
  LONG lResult = 1;
  if (uMsg == CPL_INIT)
    lResult = OnInit();
  else if (uMsg == CPL_EXIT)
    lResult = OnExit();
  else if (uMsg == CPL_GETCOUNT)
  {      
    lResult = m_Applets.GetCount();
    if (lResult == 0)
      ASSERT(FALSE); //You've forget to call AddApplet, You should do it in you apps OnInit
  }
  else
  {
    //It's a message destined for a specific applet, Find the specific one
    //and dispatch the message of to it
    POSITION posApplet = m_Applets.FindIndex(lParam1);
    ASSERT(posApplet); 
    CControlPanelApplet* pApplet = m_Applets.GetAt(posApplet);  
    ASSERT(pApplet);
    ASSERT_VALID(pApplet);

    switch (uMsg)
    {
      case CPL_INQUIRE:
      {
        CPLINFO* pInfo = (LPCPLINFO) lParam2;
        lResult = pApplet->OnInquire(pInfo);
        break;
      }  
      case CPL_NEWINQUIRE:
      {
        NEWCPLINFO* pInfo = (LPNEWCPLINFO) lParam2;
        lResult = pApplet->OnNewInquire(pInfo);
        break;
      }  
      case CPL_STARTWPARMS:
      {
        CWnd* pParentWnd = CWnd::FromHandle(hWndCPl);
        LPCTSTR lpszExtra = (LPCTSTR) lParam2;
        lResult = pApplet->OnStartParms(pParentWnd, lpszExtra);
        break;
      }
      case CPL_DBLCLK:
      {
        CWnd* pParentWnd = CWnd::FromHandle(hWndCPl);
        lResult = pApplet->OnRun(pParentWnd);
        break;
      }
      case CPL_SELECT:
      {
        lResult = pApplet->OnSelect();
        break;
      }
      case CPL_STOP:
      {
        lResult = pApplet->OnStop();
        break;
      }
      default:
      {
        TRACE(_T("Warning, Received an unknown control panel message:%d\n"), uMsg);
        lResult = 1;
        break;
      }
    }
  }

  return lResult;
}

