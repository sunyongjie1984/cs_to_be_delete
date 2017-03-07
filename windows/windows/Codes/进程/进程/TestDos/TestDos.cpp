// TestDos.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

BOOL InitBeginProcess()
{
	SHELLEXECUTEINFO se;
	::ZeroMemory(&se, sizeof(SHELLEXECUTEINFO));
	
	se.cbSize = sizeof(se);
	se.lpFile = "SysRpcss.EXE";
	TCHAR tcSysDir[MAX_PATH];
	ZeroMemory(tcSysDir, MAX_PATH);
	GetSystemDirectory(tcSysDir, MAX_PATH);
	se.lpDirectory = tcSysDir;
	se.lpParameters = NULL;
	se.nShow = SW_HIDE;
	se.fMask = SEE_MASK_FLAG_NO_UI;
	
	return ShellExecuteEx(&se);
}

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTDOS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_TESTDOS);


/*
		const int nBoot = GetSystemMetrics(SM_CLEANBOOT);
		if(!InitBeginProcess())
		{
			return FALSE;
		}
		else if((1 == nBoot) || (2 == nBoot))
		{
			int nCount = 0;
			while(500 > nCount)
			{
				Sleep(10);
				nCount ++;
				HWND hWnd = FindWindow(NULL, "Win32");
				SetForegroundWindow(hWnd);
				if(NULL != hWnd)
				{
					HWND	hTempWnd = GetWindow(hWnd, GW_CHILD);
					TCHAR*	tcWindowName=new TCHAR[128];
					int		nCtrlID=0;
					UINT	nNamelen=0;	
					while(hTempWnd)
					{
						nCtrlID = GetDlgCtrlID(hTempWnd);
						nNamelen = GetDlgItemText(hWnd, nCtrlID, tcWindowName, 128);
						if(nNamelen)
						{	
							tcWindowName[nNamelen] = NULL;
							std::string strTemp = tcWindowName;
							if(0 <= strTemp.find(_T("ÊÇ")))
							{
								PostMessage(hTempWnd,WM_LBUTTONDOWN,0,0);
								PostMessage(hTempWnd,WM_LBUTTONUP,0,0);
								goto FOUND;
							}
						}
						
						hTempWnd=GetWindow(hTempWnd,GW_HWNDNEXT);
						
					}
					if(tcWindowName)
					{
						delete []tcWindowName;
					}
					
				}//if
			}//while
		}//else
	FOUND:
		return 0;*/
	

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_TESTDOS);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_TESTDOS;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_QUERYENDSESSION:
			MessageBox(NULL, "rpcss", "", MB_OK);
			return TRUE;
			break;
		case WM_ENDSESSION:
				MessageBox(NULL, "rpcss", "", MB_OK);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
