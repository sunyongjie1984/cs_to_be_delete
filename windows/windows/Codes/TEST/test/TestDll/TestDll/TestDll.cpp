// TestDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "TestDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CTestDllApp

BEGIN_MESSAGE_MAP(CTestDllApp, CWinApp)
END_MESSAGE_MAP()


// CTestDllApp construction

CTestDllApp::CTestDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTestDllApp object

CTestDllApp theApp;


// CTestDllApp initialization

/********************************************
函数名称:GetHostName
功能：?取本机的机器名称
返回:strHostName-本机机器名称
*********************************************/
extern "C" _declspec(dllexport) void GetHostName(LPTSTR strHostName )
{
	//如果是??字符串需要使用strcpy拷?字符串的地址，而不能直接等于。
	strcpy(strHostName, theApp.GetHostName());
}
/********************************************
函数名称:GetSystemType
功能：?取本机操作系?版本
返回:strSystemType-本机操作系?版本
*********************************************/
extern "C" _declspec(dllexport) void GetSystemType(char * strSystemType)
{
	strcpy(strSystemType, theApp.GetSystemType());
}
/********************************************
函数名称:GetIPAddressList
功能：?取本机的IP地址
返回:lpIPList-本机的IP地址数?，lpNumber IP地址个数
*********************************************/
extern "C" _declspec(dllexport) void GetIPAddressList(char ** lpIPList,DWORD *lpNumber)
{
	theApp.GetIPAddressList(lpIPList,lpNumber);
}

#include "TestDlg.h"

BOOL CTestDllApp::InitInstance()
{
	CWinApp::InitInstance();

	CTestDlg dlg;
	dlg.DoModal();

	::MessageBox(NULL, "CTestDllApp::InitInstance", "Title", NULL);

	return TRUE;
}

char* CTestDllApp::GetHostName(void)
{
	char* lpsz = new char[1024];
//	m_SystemInfo.GetHostName(lpsz);
	::MessageBox(NULL, "CTestDllApp::GetHostName", "Title", NULL);

	return lpsz;
}
//系??型
char* CTestDllApp::GetSystemType(void)
{
	char* lpsz = new char[1024];
//	m_SystemInfo.GetlSystemType(lpsz);
	::MessageBox(NULL, "CTestDllApp::GetSystemType", "Title", NULL);

	return lpsz;
}
//IP地址
void CTestDllApp::GetIPAddressList(char ** lpIPList,DWORD *lpNumber)
{
//	m_SystemInfo.GetIPAddressList(lpIPList,lpNumber);
	::MessageBox(NULL, "CTestDllApp::GetIPAddressList", "Title", NULL);
}
