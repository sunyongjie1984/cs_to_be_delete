// mydll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "mydll.h"

#ifdef UNICODE
                     
	#define aMsgBox aMsgBoxW

#else

	#define aMsgBox aMsgBoxA

#endif

EXPORT BOOL CALLBACK aMsgBoxA(HWND, LPCSTR, LPCSTR);
EXPORT BOOL CALLBACK aMsgBoxW(HWND, LPCWSTR, LPCWSTR);

/////	每一个DLL必须有一个入口点，DllMain是一个缺省的入口函数。DllMain负责初始化(Initialization)
   //	和结束(Termination)工作，每当一个新的进程或者该进程的新的线程访问DLL时，或者访问DLL的每一
   //	个进程或者线程不再使用DLL或者结束时，都会调用DllMain。
   //	但是，使用TerminateProcess或TerminateThread结束进程或者线程，不会调用DllMain。

BOOL APIENTRY DllMain( HANDLE hModule,				///// 是动态库被调用时所传递来的一个指向自己的句柄(实际上，它是指向_DGROUP段的一个选择符)；
                       DWORD  ul_reason_for_call,	///// 是一个说明动态库被调原因的标志。当进程或线程装入或卸载动态连接库的时候，操作系统调用
													   // 入口函数，并说明动态连接库被调用的原因。
													   // 所有的可能值为：
															// DLL_PROCESS_ATTACH: 进程被调用；
															// DLL_THREAD_ATTACH: 线程被调用；
															// DLL_PROCESS_DETACH: 进程被停止；
															// DLL_THREAD_DETACH: 线程被停止；
				   
                       LPVOID lpReserved )			///// 是一个被系统所保留的参数。
{
    return TRUE;
}

EXPORT BOOL CALLBACK MyMsgBox()
{
	return MessageBox(NULL, TEXT("MessageBox in DLL"), TEXT("USE DLL"), MB_ICONERROR);
}

//使用ASCII字符集
EXPORT BOOL CALLBACK aMsgBoxA(HWND hwnd, LPCSTR lpText, LPCSTR lpCaption)
{
	return MessageBoxA(hwnd, lpText, lpCaption, NULL);
}

//使用UNICODE字符集
EXPORT BOOL CALLBACK aMsgBoxW(HWND hwnd, LPCWSTR lpText, LPCWSTR lpCaption)
{
	return MessageBoxW(hwnd, lpText, lpCaption, NULL);
}