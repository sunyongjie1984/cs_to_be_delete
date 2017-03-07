#include "stdafx.h"
#include <objbase.h>
#include <tlhelp32.h>
#include <TCHAR.h>
//#include <string>
#include <psapi.h>
#include <DBT.h>

HDEVNOTIFY g_NotificationHandle = NULL;

HWND InitMsgDialog(HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow("RpcssWin32", 
								"RpcssWin32",
								WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,
								0,
								CW_USEDEFAULT, 
								0, 
								NULL, 
								NULL, 
								hInstance, 
								NULL);
	
	if (!hWnd)
	{
		return NULL;
	}
	
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);
	
	DEV_BROADCAST_DEVICEINTERFACE dbch;
	GUID guid;
	CoCreateGuid(&guid);
	dbch.dbcc_size = sizeof(dbch);
	dbch.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	dbch.dbcc_classguid = guid;
	dbch.dbcc_name[0] = '\0';
	
	g_NotificationHandle = RegisterDeviceNotification(hWnd,
													&dbch, 
													DEVICE_NOTIFY_WINDOW_HANDLE);	
	return hWnd;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	HWND hWnd = InitMsgDialog(hInstance);
	if(!hWnd)
	{
		MessageBox(hWnd, "Can't InitMsgDialog", "Warning", MB_OK);
		return -1;
	}

	return 0;
}



