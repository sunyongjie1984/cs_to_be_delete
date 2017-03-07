// This is the main DLL file.

#include "stdafx.h"

#include "ServiceControlInterop.h"
#include <windows.h>
#include <msclr\marshal.h>
#include <msclr\marshal_windows.h>
#include <vcclr.h>

using namespace msclr::interop;

#pragma comment (lib, "advapi32.lib")

using namespace System::Runtime::InteropServices;

namespace ServiceControlInterop {

void ServiceControl::AddService(System::String^ serviceName, System::String^ displayName, System::String^ path)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = CreateService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName),
		context.marshal_as<LPCWSTR>(displayName),
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL, context.marshal_as<LPCWSTR>(path),
		NULL, NULL, NULL, NULL, /*L"NT AUTHORITY\\LOCALSERVICE",*/ NULL);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);

}

void ServiceControl::RemoveService(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	if (DeleteService(hService) == FALSE)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
}

void ServiceControl::ActivateService(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	if (StartService(hService, 0, NULL) == FALSE)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
}

void ServiceControl::DeactivateService(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	SERVICE_STATUS serviceStatus = {0};
	if (ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus) == FALSE)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
}

void ServiceControl::RemoveAllPrivilegesFromService(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	//

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
}

bool ServiceControl::IsServiceTriggerStart(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	DWORD cbBytesNeeded = (DWORD)-1;
	QueryServiceConfig2(hService, SERVICE_CONFIG_TRIGGER_INFO, NULL, 0, &cbBytesNeeded);
	if (cbBytesNeeded == (DWORD)-1)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}
	PBYTE lpBuffer = (PBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbBytesNeeded);

	if (QueryServiceConfig2(hService, SERVICE_CONFIG_TRIGGER_INFO, lpBuffer, cbBytesNeeded, &cbBytesNeeded) == FALSE)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCManager);
		HeapFree(GetProcessHeap(), 0, lpBuffer);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	PSERVICE_TRIGGER_INFO pTriggerInfo = (PSERVICE_TRIGGER_INFO)lpBuffer;
	BOOL bTriggerStart = pTriggerInfo->cTriggers > 0;

	HeapFree(GetProcessHeap(), 0, lpBuffer);

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);

	return bTriggerStart;
}

static const GUID GUID_USBDevice = {
	0x53f56307, 0xb6bf, 0x11d0, {0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b }};

void ServiceControl::SetServiceTriggerStartOnUSBArrival(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	//

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
}

void ServiceControl::SetServiceTriggerStartOnIPAddressArrival(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	SERVICE_TRIGGER serviceTrigger = {0};
	serviceTrigger.dwTriggerType = SERVICE_TRIGGER_TYPE_IP_ADDRESS_AVAILABILITY;
	serviceTrigger.dwAction = SERVICE_TRIGGER_ACTION_SERVICE_START;
	serviceTrigger.pTriggerSubtype = (GUID*)&NETWORK_MANAGER_FIRST_IP_ADDRESS_ARRIVAL_GUID;

	SERVICE_TRIGGER_INFO serviceTriggerInfo = {0};
	serviceTriggerInfo.cTriggers = 1;
	serviceTriggerInfo.pTriggers = &serviceTrigger;

	if (ChangeServiceConfig2(hService, SERVICE_CONFIG_TRIGGER_INFO, &serviceTriggerInfo) == FALSE)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
}

void ServiceControl::SetServiceDelayedAutoStart(System::String^ serviceName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCManager == NULL)
	{
		throw Marshal::GetExceptionForHR(GetLastError());
	}

	marshal_context context;

	SC_HANDLE hService = OpenService(hSCManager,
		context.marshal_as<LPCWSTR>(serviceName), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	SERVICE_DELAYED_AUTO_START_INFO delayedAutoStartInfo = {0};
	delayedAutoStartInfo.fDelayedAutostart = TRUE;

	if (ChangeServiceConfig2(hService, SERVICE_CONFIG_DELAYED_AUTO_START_INFO, &delayedAutoStartInfo) == FALSE)
	{
		DWORD dwLastError = GetLastError();
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCManager);
		throw Marshal::GetExceptionForHR(dwLastError);
	}

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
}

}//end namespace ServiceControlInterop