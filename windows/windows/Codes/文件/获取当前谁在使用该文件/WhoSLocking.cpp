// WhoSLocking.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WhoSLocking.h"
#include "WhoSLockingDlg.h"
#include "WhoSLockingCommandLineInfo.h"
#include "WindowsRegistry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhoSLockingApp

BEGIN_MESSAGE_MAP(CWhoSLockingApp, CWinApp)
	//{{AFX_MSG_MAP(CWhoSLockingApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhoSLockingApp construction

CWhoSLockingApp::CWhoSLockingApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWhoSLockingApp object

CWhoSLockingApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWhoSLockingApp initialization

BOOL CWhoSLockingApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    // Register application for DLLs, Ocx, Exe files
    ShellRegister("Who's Locking?", "ocxfile", "ActiveX COMponent", ".OCX", "application/ocx", "%SystemRoot%\\system32\\SHELL32.dll,21");
    ShellRegister("Who's Locking?", "dllfile");
    ShellRegister("Who's Locking?", "exefile");

    CWhoSLockingCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);
/*
    if (!ProcessShellCommand) {
        return FALSE;
    }
*/

	CWhoSLockingDlg dlg(NULL, cmdInfo.m_szDefaultFilePath);
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CWhoSLockingApp::ShellRegister(LPCTSTR lpszApplicationName, LPCTSTR lpszRegistryClass, LPCTSTR lpszFileDescription, LPCTSTR lpszFileExtension, LPCTSTR lpszMimeType, LPCTSTR lpszDefaultIcon)
{
    BOOL bReturnCode = FALSE;
    CWindowsRegistry MyRegistry;
    CString szShellCommand;
    CString szKeyName;

    // Build shell command
    TCHAR lpszExecutablePath[_MAX_PATH];
    if (GetModuleFileName(m_hInstance,    // handle to module to find filename for
                          lpszExecutablePath,  // pointer to buffer to receive module path
                          sizeof(lpszExecutablePath)         // size of buffer, in characters
                          )) {
        szShellCommand = lpszExecutablePath;
    } else {
        szShellCommand = "WhoSLocking.exe";
    }
    // Add the parameter
    szShellCommand+=" \"%1\"";

    // (1) shell type & command
    if (lpszRegistryClass) {
        szKeyName = "\\HKEY_CLASSES_ROOT\\";
        szKeyName += lpszRegistryClass;
        if (MyRegistry.OpenKey(szKeyName, NULL, KEY_ALL_ACCESS) != ERROR_SUCCESS) {
            MyRegistry.CreateKey(szKeyName);
        }

        if (MyRegistry.OpenKey(szKeyName, NULL, KEY_ALL_ACCESS) == ERROR_SUCCESS) {
            if (lpszFileDescription != NULL) {
                MyRegistry.WriteValue("", lpszFileDescription);
            }
            CString szShellKey = szKeyName;
            szShellKey+="\\shell";
            MyRegistry.CreateKey(szShellKey);
            szShellKey+="\\";
            szShellKey+=lpszApplicationName;
            MyRegistry.CreateKey(szShellKey);
            szShellKey+="\\command";
            MyRegistry.CreateKey(szShellKey);
            if (MyRegistry.OpenKey(szShellKey, NULL, KEY_ALL_ACCESS) == ERROR_SUCCESS) {
                MyRegistry.WriteValue("", szShellCommand);
            }
        }
    }

    // (2) mapping shell type <-> file extension
    if (lpszFileExtension && lpszRegistryClass) {
        szKeyName = "\\HKEY_CLASSES_ROOT\\";
        szKeyName += lpszFileExtension;
        if (MyRegistry.OpenKey(szKeyName, NULL, KEY_ALL_ACCESS) != ERROR_SUCCESS) {
                MyRegistry.CreateKey(szKeyName);
        }

        if (MyRegistry.OpenKey(szKeyName, NULL, KEY_ALL_ACCESS) == ERROR_SUCCESS) {
            MyRegistry.WriteValue("", lpszRegistryClass);
            if (lpszMimeType) {
                MyRegistry.WriteValue("Content Type", lpszMimeType);
            }
        }
    }

    // (3) MIME Type
    if (lpszMimeType) {
        szKeyName = "\\HKEY_CLASSES_ROOT\\MIME\\Database\\Content Type\\";
        szKeyName += lpszMimeType;
        if (MyRegistry.OpenKey(szKeyName, NULL, KEY_ALL_ACCESS) != ERROR_SUCCESS) {
            if (lpszFileDescription != NULL && lpszMimeType != NULL) {
                MyRegistry.CreateKey(szKeyName);
            }
        }

        if (MyRegistry.OpenKey(szKeyName, NULL, KEY_ALL_ACCESS) == ERROR_SUCCESS) {
            MyRegistry.WriteValue("Extension", lpszFileExtension);
        }
    }

    return(bReturnCode);
}
