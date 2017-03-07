//*******************************************************************
//              
//  FILE:       Service.cpp
//              
//  AUTHOR:     sam sha
//              
//  PROJECT:    mproxysvr3
//              
//  COMPONENT:  CService
//              
//  DATE:       23.06.2003
//              
//  COMMENTS:   - 服务程序模型来源于codeproject上的一个wizard模型，稍有扩充
//              　　
//              
//*******************************************************************





// Includes
// Service.cpp: implementation of the CService class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include "Service.h"
#include "mproxy3.h"

CService _Module;

//两个二级代理的服务端口
CMProxy3 _ProxyHttp(18800,"10.20.188.16",80);
CMProxy3 _ProxySocket(18801,"10.20.188.16",1080);
//本软件仅支持直接的http代理
//CMProxy3 _ProxyHttpDirect(801);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CService::CService()
{
	int nErr;
	WSADATA WsaData;
	nErr = WSAStartup (0x0202, &WsaData);
	if (nErr == SOCKET_ERROR)
	{
		//printf( "WSAStartup Failed\n");
		return;
	}
	

}

CService::~CService()
{
	WSACleanup();
}

void CService::Init(LPCTSTR pServiceName,LPCTSTR pServiceDisplayedName)
{
    lstrcpy(m_szServiceName,pServiceName);
    lstrcpy(m_szServiceDisplayedName,pServiceDisplayedName);

    // set up the initial service status 
    m_hServiceStatus = NULL;
    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_status.dwCurrentState = SERVICE_STOPPED;
    m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP/* | SERVICE_ACCEPT_PAUSE_CONTINUE*/;
    m_status.dwWin32ExitCode = 0;
    m_status.dwServiceSpecificExitCode = 0;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
}

void CService::Start()
{
    SERVICE_TABLE_ENTRY st[] =
    {
		{ m_szServiceName, _ServiceMain },
        { NULL, NULL }
    };
    if (!::StartServiceCtrlDispatcher(st) && m_bService)
	{
		DWORD dw = GetLastError();
		LogEvent("StartServiceCtrlDispatcher Error=%d",dw);
		m_bService = FALSE;
	}

    if (m_bService == FALSE)
        Run();
}

void CService::ServiceMain()
{
    // Register the control request handler
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, _Handler);
    if (m_hServiceStatus == NULL)
    {
        LogEvent("Handler not installed");
        return;
    }
    SetServiceStatus(SERVICE_START_PENDING);

    m_status.dwWin32ExitCode = S_OK;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;

    // When the Run function returns, the service has stopped.
    Run();

    SetServiceStatus(SERVICE_STOPPED);
    LogEvent("Service stopped");
}

inline void CService::Handler(DWORD dwOpcode)
{
    switch (dwOpcode)
    {
    case SERVICE_CONTROL_STOP:
		LogEvent("Request to stop...");
		SetServiceStatus(SERVICE_STOP_PENDING);
	    //PostThreadMessage(m_dwThreadID, WM_QUIT, 0, 0);
        break;
    case SERVICE_CONTROL_PAUSE:
	//	LogEvent("Request to pause...");
	//	SetServiceStatus(SERVICE_PAUSE_PENDING);
        break;
    case SERVICE_CONTROL_CONTINUE:
	//	LogEvent("Request to continue...");
	//	SetServiceStatus(SERVICE_CONTINUE_PENDING);
       break;
    case SERVICE_CONTROL_INTERROGATE:
        break;
    case SERVICE_CONTROL_SHUTDOWN:
        break;
    default:
        LogEvent("Bad service request");
		break;
    }
}

void WINAPI CService::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    _Module.ServiceMain();
}
void WINAPI CService::_Handler(DWORD dwOpcode)
{
    _Module.Handler(dwOpcode); 
}

void CService::SetServiceStatus(DWORD dwState)
{
    m_status.dwCurrentState = dwState;
    ::SetServiceStatus(m_hServiceStatus, &m_status);
}

DWORD CService::GetServiceStatus()
{
	return m_status.dwCurrentState;
}
//*******************************************************************
//              
//  FUNCTION:   -　Run()
//              
//  RETURNS:    -
//              
//  PARAMETERS: -
//              
//  COMMENTS:   -　当服务启动后，调用Run(),Run()结束后服务停止
//              
//              
//*******************************************************************

void CService::Run()
{
    LogEvent("Service started");
	m_dwThreadID = GetCurrentThreadId();

    if (m_bService)
        SetServiceStatus(SERVICE_RUNNING);

	//启动服务
	_ProxyHttp.Start();
	//_ProxyFtp.Start();
	_ProxySocket.Start();


	//判断服务停止
	while (m_status.dwCurrentState == SERVICE_RUNNING )
	{
		Sleep(3000);
		if ( m_status.dwCurrentState == SERVICE_STOP_PENDING )
			break;
	}
	//停止服务
	_ProxyHttp.Stop();
	//_ProxyFtp.Stop();
	_ProxySocket.Stop();



}

BOOL CService::Install()
{
    if (IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        MessageBox(NULL, "Couldn't open service manager", m_szServiceName, MB_OK);
        return FALSE;
    }

    // Get the executable file path
    TCHAR szFilePath[_MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

    SC_HANDLE hService = ::CreateService(
        hSCM, m_szServiceName, m_szServiceDisplayedName,
        SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
        SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
        szFilePath, NULL, NULL, NULL, NULL, NULL);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, "Couldn't create service", m_szServiceName, MB_OK);
        return FALSE;
    }

    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
    return TRUE;
}

BOOL CService::Uninstall()
{
    if (!IsInstalled())
        return TRUE;

	

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM == NULL)
    {
        MessageBox(NULL, "Couldn't open service manager", m_szServiceName, MB_OK);
        return FALSE;
    }

    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, "Couldn't open service", m_szServiceName, MB_OK);
        return FALSE;
    }
    SERVICE_STATUS status;
    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);

    BOOL bDelete = ::DeleteService(hService);
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    if (bDelete)
        return TRUE;

    MessageBox(NULL, "Service could not be deleted", m_szServiceName, MB_OK);
    return FALSE;
}

BOOL CService::IsInstalled()
{
    BOOL bResult = FALSE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM != NULL)
    {
        SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
        {
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bResult;
}

///////////////////////////////////////////////////////////////////////////////////////
// Logging functions
void CService::LogEvent(LPCSTR pFormat, ...)
{
    TCHAR    chMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1];
    va_list pArg;

    va_start(pArg, pFormat);
    vsprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;

    if (m_bService)
    {
        /* Get a handle to use with ReportEvent(). */
        hEventSource = RegisterEventSource(NULL, m_szServiceName);
        if (hEventSource != NULL)
        {
            /* Write to event log. */
            ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
            DeregisterEventSource(hEventSource);
        }
    }
    else
    {
        // As we are not running as a service, just write the error to the console.
        printf(chMsg);
    }
}
