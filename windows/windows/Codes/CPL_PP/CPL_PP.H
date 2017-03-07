#ifndef __CPL_PP_H__
#define __CPL_PP_H__


#ifndef __AFXTEMPL_H__
#include <afxtempl.h> 
#pragma message("To avoid this message, please put afxtempl.h in your PCH")
#endif



//Class which encapsulates one control panel applet
class CControlPanelApplet : public CCmdTarget
{
public:
  CControlPanelApplet(UINT nResourceID, CRuntimeClass* pUIClass);
  CControlPanelApplet(UINT nResourceID, UINT nDescriptionID, CRuntimeClass* pUIClass);
  virtual ~CControlPanelApplet();

protected:
//Overridable Member Functions
  virtual LRESULT OnRun(CWnd* pParentWnd);
  virtual LRESULT OnStartParms(CWnd* pParentWnd, LPCTSTR lpszExtra);
  virtual LRESULT OnInquire(CPLINFO* pInfo);
  virtual LRESULT OnNewInquire(NEWCPLINFO* pInfo);
  virtual LRESULT OnSelect();
  virtual LRESULT OnStop();

//Data members
  CRuntimeClass* m_pUIClass;       //Pointer to property sheet or dialog to display
  BOOL           m_bDynamic;       //Show this class respond to OnNewInquire instead of OnInquire
  UINT           m_nResourceID;    //Resource ID of the string resource for this applet
  UINT           m_nDescriptionID; //Resource ID of the description to use (only used for CPL_INQUIRE)
  CString        m_sName;          //The name of the control panel applet
  int            m_nPageNumber;    //The initial page to display
  
  friend class CControlPanelApp;   //The app class is allowed to access our innards

  DECLARE_DYNAMIC(CControlPanelApplet);
};


//The main app class which contains all the applets in this dll
class CControlPanelApp : public CWinApp
{
public:
//Constructors / Destructors
  CControlPanelApp();
  virtual ~CControlPanelApp();

//Public Methods
  void AddApplet(CControlPanelApplet* pApplet);

protected:
  CList<CControlPanelApplet*, CControlPanelApplet*&> m_Applets; //The array of all the control panel applets

  friend LONG APIENTRY CPlApplet(HWND hWndCPl, UINT uMsg, LONG lParam1, LONG lParam2);
  virtual LRESULT OnCplMsg(HWND hWndCPl, UINT msg, LPARAM lp1, LPARAM lp2);
  virtual LRESULT OnInit();
  virtual LRESULT OnExit();

  DECLARE_DYNAMIC(CControlPanelApp);
};


//Global Functions
CControlPanelApp* GetControlPanelApp();


#endif //__CPL_PP_H__
