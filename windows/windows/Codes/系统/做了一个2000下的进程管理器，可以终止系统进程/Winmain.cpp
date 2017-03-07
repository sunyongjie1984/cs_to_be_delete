#include <windows.h>
#include <Psapi.h>
#include <commctrl.h>
#include "resource.h"

HWND g_hDlg;
HWND g_hSplit;
HINSTANCE g_hInstance;
BOOL g_bSplit;
RECT g_SplitRect = { 268, 70 , 0, 0 };

INT_PTR CALLBACK DialogProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
void SetProcessPrivilege( LPCTSTR szPrivilegeName, BOOL bOpen );
void OnKill();
DWORD BreakProcess( LPSTR szProcName );
void ListProcesses();
void InitDialog();
void OnProcessItemChanged( LPNMLISTVIEW pi );
void ListModules( HANDLE hProc );
void OnResize( POINT *pWndSize );

// Winmain
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	g_hInstance = hInstance;
	InitCommonControls();
	DialogBox( hInstance, MAKEINTRESOURCE( IDD_MAINDIALOG ), NULL, DialogProc );
	return 0;
}

INT_PTR CALLBACK SplitBarProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static POINT LastCoor;
	switch ( uMsg )
	{
	case WM_LBUTTONDOWN:
		{
			POINT MouseCoor;
			GetCursorPos( &MouseCoor );
			RECT SplitRect;
			GetWindowRect( g_hSplit, &SplitRect );
			LastCoor.x = MouseCoor.x;
			LastCoor.y = MouseCoor.y;
			if ( !SetCapture( hwndDlg ) )
			break;
		}
	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			OnResize(NULL);
			InvalidateRect( g_hDlg, NULL, TRUE );
			break;
		}
	case WM_MOUSEMOVE:
		if ( wParam & MK_LBUTTON )
		{
			POINT MouseCoor;
			GetCursorPos( &MouseCoor );
			g_SplitRect.left += ( MouseCoor.x - LastCoor.x );
			g_SplitRect.right = g_SplitRect.left + 7;
			LastCoor.x = MouseCoor.x;
			LastCoor.y = MouseCoor.y;
			break;
		}
	case WM_PAINT:
		{
/*			HDC dc = GetWindowDC( hwndDlg );
			HBRUSH hb = GetSysColorBrush(COLOR_ACTIVECAPTION);
			HGDIOBJ hOld = SelectObject( dc, hb );
			RECT WndRect;
			GetWindowRect( hwndDlg, &WndRect );
			Rectangle( dc, 0, 0, WndRect.right - WndRect.left, WndRect.bottom - WndRect.top );
			ReleaseDC( hwndDlg, dc );*/
			break;
		}
	case WM_SETCURSOR:
		{
			HCURSOR hCur = LoadCursor( NULL, IDC_SIZEWE );
			DWORD e = GetLastError( );
			hCur = SetCursor( hCur );
			int a = 0;
			break;
		}
	default:
		break;
	}
	return FALSE;
}

// dialog message process function
INT_PTR CALLBACK DialogProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_INITDIALOG:
		g_hDlg = hwndDlg;
		InitDialog();
		return TRUE;
	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDOK:
			OnKill();
			return TRUE;
		case IDCLOSE:
			EndDialog( hwndDlg, IDOK );
			return TRUE;
		case IDC_BTNREFRESH:
			ListProcesses();
			return TRUE;
		}
		return FALSE;
	case WM_NOTIFY:
		switch ( (int) wParam )
		{
		case IDC_LISTPROCESSES:
			switch ( ((LPNMHDR)lParam)->code )
			{
			case LVN_ITEMCHANGED:
				OnProcessItemChanged( (LPNMLISTVIEW)lParam );
				break;
			}
		}
		return FALSE;
	case WM_SIZE:
		{
			POINT size;
			size.x = LOWORD( lParam );
			size.y = HIWORD( lParam );
			OnResize( &size );
			return TRUE;
		}
	case WM_CLOSE:
		SetProcessPrivilege( SE_DEBUG_NAME, FALSE );
		EndDialog( hwndDlg, IDOK );
		return TRUE;
	case WM_LBUTTONDOWN:
		SetCapture( hwndDlg );
		return TRUE;
	case WM_LBUTTONUP:
		ReleaseCapture();
		return TRUE;
	default:
		return FALSE;
	}
}

// Set privilege of this process
void SetProcessPrivilege( LPCTSTR szPrivilegeName, BOOL bOpen )
{
	BOOL bResult;
	DWORD dwCurProcId = GetCurrentProcessId();
	HANDLE hCurProc;
	hCurProc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwCurProcId );
	DWORD e = GetLastError();
	HANDLE hToken;
	bResult = OpenProcessToken( hCurProc, TOKEN_ADJUST_PRIVILEGES, &hToken );
	bResult = CloseHandle(hCurProc);

	LUID luid;
	bResult = LookupPrivilegeValue( NULL, szPrivilegeName, &luid );

	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	memcpy( &tp.Privileges[0].Luid, &luid, sizeof(LUID) );
	tp.Privileges[0].Attributes = bOpen ? SE_PRIVILEGE_ENABLED : 0;
	bResult = AdjustTokenPrivileges( hToken, FALSE, &tp, 0, NULL, NULL );
	CloseHandle( hToken );
}

// Kill process witch user spicificed in process list
void OnKill()
{
	HWND hList = GetDlgItem( g_hDlg, IDC_LISTPROCESSES );
	int nItemCount = ListView_GetItemCount( hList );
	for ( int i = 0; i < nItemCount; i++ )
	{
		UINT uState = ListView_GetItemState( hList, i, LVIS_SELECTED );
		if ( LVIS_SELECTED == uState )
		{
			char szId[256];
			ListView_GetItemText( hList, i, 1, szId, sizeof(szId) );

			int pid = atoi( szId );
			HANDLE hProc = OpenProcess( PROCESS_TERMINATE, FALSE, pid );
			BOOL br = TerminateProcess( hProc, 0 );
			CloseHandle( hProc );

			if ( br )
				MessageBox( g_hDlg, "Terminate successed!", "Information", MB_ICONINFORMATION );
			else
				MessageBox( g_hDlg, "Terminate failed!", "Error", MB_ICONHAND );
			ListProcesses();
			return;
		}
	}
}

DWORD BreakProcess( LPSTR szProcName )
{
	DWORD dwTerminated = 0;
	DWORD dwProcessId[500];
	DWORD ProcessCount;
	EnumProcesses( dwProcessId, 500, &ProcessCount );
	for ( DWORD i = 0; i < ProcessCount; i++ )
	{
		HANDLE hProc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwProcessId[i] );
		if ( !hProc )
			continue;
		HMODULE hMod[500];
		DWORD dwModCount;
		BOOL bResult = EnumProcessModules( hProc, hMod, sizeof(hMod), &dwModCount);
		if ( !bResult )
			continue;
		for ( DWORD j = 0; j < dwModCount; j++ )
		{
			char szTemp[256];
			ZeroMemory( szTemp, sizeof(szTemp) );
			GetModuleBaseName( hProc, hMod[j], szTemp, sizeof(szTemp) );
			if ( !strcmp( szTemp, szProcName ) )
			{
				if ( TerminateProcess( hProc, 0 ) )
					dwTerminated++;
				break;
			}
		}
		CloseHandle( hProc );
	}
	return dwTerminated;
}

// List all process to specific list view
void ListProcesses()
{
	HWND hList = GetDlgItem( g_hDlg, IDC_LISTPROCESSES );
	ListView_DeleteAllItems( hList );

	DWORD dwTerminated = 0;
	DWORD dwProcessId[500];
	DWORD ProcessCount;
	EnumProcesses( dwProcessId, 500, &ProcessCount );
	DWORD iIndex = 0;
	for ( DWORD i = 0; i < ProcessCount; i++ )
	{
		HANDLE hProc = OpenProcess( PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, dwProcessId[i] );
		if ( !hProc )
			continue;

		char szTemp[256];
		ZeroMemory( szTemp, sizeof(szTemp) );
		if ( !GetModuleBaseName( hProc, NULL, szTemp, sizeof(szTemp) ) )
			continue;

		LVITEM Item;
		ZeroMemory( &Item, sizeof(Item) );

		// 加入进程名
		Item.iItem = iIndex;
		Item.iSubItem = 0;
		Item.mask = LVIF_TEXT;
		Item.pszText = szTemp;
		Item.cchTextMax = (int)strlen( szTemp ) + 1;
		ListView_InsertItem( hList, &Item );

		// 加入进程ID
		Item.iSubItem = 1;
		_itoa( dwProcessId[i], szTemp, 10 );
		Item.pszText = szTemp;
		Item.cchTextMax = (int)strlen( szTemp ) + 1;
		ListView_SetItem( hList, &Item );

		// 加入进程文件名
		ZeroMemory( szTemp, sizeof(szTemp) );
		if ( !GetModuleFileNameEx( hProc, NULL, szTemp, sizeof(szTemp) ) )
			continue;
		Item.iSubItem = 2;
		Item.pszText = szTemp;
		Item.cchTextMax = (int)strlen( szTemp ) + 1;
		ListView_SetItem( hList, &Item );

		PROCESS_MEMORY_COUNTERS pmc;
		if ( GetProcessMemoryInfo( hProc, &pmc, sizeof(PROCESS_MEMORY_COUNTERS) ) )
		{
			Item.iSubItem = 3;
			_itoa( (int)pmc.WorkingSetSize, szTemp, 10 );
			strcat( szTemp, " Byte" );
			Item.pszText = szTemp;
			Item.cchTextMax = (int)strlen( szTemp ) + 1;
			ListView_SetItem( hList, &Item );
		}

		CloseHandle( hProc );
		iIndex++;
	}
}

void ListModules( HANDLE hProc )
{
	HWND hList = GetDlgItem( g_hDlg, IDC_LISTMODULES );
	ListView_DeleteAllItems( hList );

	if ( !hProc )
		return;
	HMODULE hMod[500];
	DWORD dwModCount;
	BOOL bResult = EnumProcessModules( hProc, hMod, sizeof(hMod), &dwModCount);
	if ( !bResult )
		return;
	for ( DWORD i = 0; i < dwModCount; i++ )
	{
		char szTemp[256];
		ZeroMemory( szTemp, sizeof(szTemp) );
		if ( !GetModuleBaseName( hProc, hMod[i], szTemp, sizeof(szTemp) ) )
			continue;

		LVITEM Item;
		ZeroMemory( &Item, sizeof(Item) );

		Item.iItem = i;
		Item.iSubItem = 0;
		Item.mask = LVIF_TEXT;
		Item.pszText = szTemp;
		Item.cchTextMax = sizeof(szTemp);
		ListView_InsertItem( hList, &Item );

		ZeroMemory( szTemp, sizeof(szTemp) );
		if ( !GetModuleFileNameEx( hProc, hMod[i], szTemp, sizeof(szTemp) ) )
			continue;
		Item.iSubItem = 1;
		Item.pszText = szTemp;
		Item.cchTextMax = sizeof(szTemp);
		ListView_SetItem( hList, &Item );
	}
}

//Initialize dialog and list all process
void InitDialog()
{
	SetProcessPrivilege( SE_DEBUG_NAME, TRUE );

	// Set modules list view
	HWND hList = GetDlgItem( g_hDlg, IDC_LISTMODULES );
	ListView_SetExtendedListViewStyleEx( hList, NULL, LVS_EX_FULLROWSELECT );
	LVCOLUMN Column;
	ZeroMemory( &Column, sizeof(LVCOLUMN) );
	Column.mask = LVCF_TEXT | LVCF_WIDTH;
	Column.pszText = "Module Name";
	Column.cchTextMax = 5;
	Column.cx = 120;
	ListView_InsertColumn( hList, 0, &Column );

	Column.pszText = "Module File Name";
	Column.cchTextMax = 6;
	Column.cx = 200;
	Column.iSubItem = 1;
	ListView_InsertColumn( hList, 1, &Column );

	// Set process list view
	hList = GetDlgItem( g_hDlg, IDC_LISTPROCESSES );
	ListView_SetExtendedListViewStyleEx( hList, NULL, LVS_EX_FULLROWSELECT );

	ZeroMemory( &Column, sizeof(LVCOLUMN) );
	Column.mask = LVCF_TEXT | LVCF_WIDTH;
	Column.pszText = "Process Image Name";
	Column.cchTextMax = (int)strlen(Column.pszText) + 1;
	Column.cx = 120;
	ListView_InsertColumn( hList, 0, &Column );

	Column.pszText = "Process ID";
	Column.cchTextMax = (int)strlen(Column.pszText) + 1;
	Column.cx = 70;
	Column.iSubItem = 1;
	ListView_InsertColumn( hList, 1, &Column );

	Column.pszText = "Process File Name";
	Column.cchTextMax = (int)strlen(Column.pszText) + 1;
	Column.cx = 200;
	Column.iSubItem = 2;
	ListView_InsertColumn( hList, 2, &Column );

	Column.pszText = "Memory Used";
	Column.cchTextMax = (int)strlen(Column.pszText) + 1;
	Column.cx = 150;
	Column.iSubItem = 3;
	ListView_InsertColumn( hList, 3, &Column );

	ListProcesses( );

	g_hSplit = CreateDialog( g_hInstance, MAKEINTRESOURCE(IDD_SPLITBAR), g_hDlg, SplitBarProc );
	ShowWindow( g_hSplit, SW_NORMAL );

	OnResize( NULL );
}

//On user selected a process item, list all module associator with the process
void OnProcessItemChanged( LPNMLISTVIEW pi )
{
	if ( ( LVIS_FOCUSED | LVIS_SELECTED ) != pi->uNewState )
		return;
	HWND hList = GetDlgItem( g_hDlg, IDC_LISTPROCESSES );
	char szId[256];
	ListView_GetItemText( hList, pi->iItem, 1, szId, sizeof(szId) );
	int pid = atoi( szId );
	HANDLE hProc = OpenProcess( PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid );
	hList = GetDlgItem( g_hDlg, IDC_LISTMODULES );
	ListModules( hProc );
	CloseHandle( hProc );
}

void OnResize( POINT *pWndSize )
{
	HWND hProcList = GetDlgItem( g_hDlg, IDC_LISTPROCESSES );
	HWND hModList = GetDlgItem( g_hDlg, IDC_LISTMODULES );

	RECT MainWndRect, ProcWndRect, ModWndRect, SplitRect;
	GetWindowRect( g_hDlg, &MainWndRect );
	GetWindowRect( hProcList, &ProcWndRect );
	GetWindowRect( hModList, &ModWndRect );

	SetWindowPos(
		g_hSplit,
		HWND_TOP,
		g_SplitRect.left,
		g_SplitRect.top,
		7,
		MainWndRect.bottom - MainWndRect.top - 140,
		SWP_DRAWFRAME
		);
	GetWindowRect( g_hSplit, &SplitRect );

	SetWindowPos(
		hProcList,
		NULL,
		0,
		0,
		SplitRect.left - MainWndRect.left - 15,
		MainWndRect.bottom - MainWndRect.top - 140,
		SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME
		);

	SetWindowPos(
		hModList,
		NULL,
		SplitRect.right - MainWndRect.left - 3,
		MainWndRect.top - MainWndRect.top + 70,
		MainWndRect.right - SplitRect.right - 15,
		MainWndRect.bottom - MainWndRect.top - 140,
		SWP_NOZORDER | SWP_DRAWFRAME
		);

	HWND hButton = GetDlgItem( g_hDlg, IDCLOSE );
	SetWindowPos(
		hButton,
		NULL,
		MainWndRect.right - MainWndRect.left - 95,
		MainWndRect.bottom - MainWndRect.top - 60,
		0,
		0,
		SWP_NOSIZE | SWP_NOCOPYBITS
		);

	hButton = GetDlgItem( g_hDlg, IDOK );
	SetWindowPos(
		hButton,
		NULL,
		MainWndRect.right - MainWndRect.left - 195,
		MainWndRect.bottom - MainWndRect.top - 60,
		0,
		0,
		SWP_NOSIZE | SWP_NOCOPYBITS
		);

	hButton = GetDlgItem( g_hDlg, IDC_BTNREFRESH );
	SetWindowPos(
		hButton,
		NULL,
		MainWndRect.right - MainWndRect.left - 275,
		MainWndRect.bottom - MainWndRect.top - 60,
		0,
		0,
		SWP_NOSIZE | SWP_NOCOPYBITS
		);
}
