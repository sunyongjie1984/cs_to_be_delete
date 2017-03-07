// ExportFunc.h
// 

#pragma once

extern "C" 
int __declspec(dllexport) _stdcall ShowMessage( HWND hWnd, LPCTSTR lpszMsg );

//extern "C" 
//int __declspec(dllexport) CreateChildDlg( CWnd *pWnd, RECT *pRt, CWnd *&pWndChild );

extern "C" 
int __declspec(dllexport) CreateChildDlg( HWND hWndParent, RECT *pRt, HWND &hWndChild );
