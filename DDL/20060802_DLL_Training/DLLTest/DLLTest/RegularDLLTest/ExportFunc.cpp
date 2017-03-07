// ExportFunc.cpp
//
#include "stdafx.h"
#include "ExportFunc.h"
#include "ChildDialog.h"

int _stdcall ShowMessage( HWND hWnd, LPCTSTR lpszMsg )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	
	return ::MessageBox( hWnd, lpszMsg, _T( "RegularDLL" ), MB_YESNO );
}

//int CreateChildDlg( CWnd *pWnd, RECT *pRt, CWnd *&pWndChild )
//{
//	AFX_MANAGE_STATE( AfxGetStaticModuleState());
//
//	CChildDialog *pDlg = new CChildDialog;
//	pDlg->Create( CChildDialog::IDD, pWnd );
//	pDlg->MoveWindow( pRt );
//	pDlg->ShowWindow( SW_SHOW );
//	pWndChild = pDlg;
//
//	return 1;
//}

int CreateChildDlg( HWND hWndParent, RECT *pRt, HWND &hWndChild )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	
	CChildDialog *pDlg = new CChildDialog;

	pDlg->Create( CChildDialog::IDD
		, CWnd::FromHandle( hWndParent ));

	pDlg->MoveWindow( pRt );
	pDlg->ShowWindow( SW_SHOW );
	hWndChild = pDlg->GetSafeHwnd();
	
	return 1;
}
