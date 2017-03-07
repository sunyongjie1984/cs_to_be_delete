#include "windows.h"
//----------------------start  ------------

HANDLE g_thread_handle =NULL; // 该DLL内部线程的句柄
DWORD  g_thread_id =0;        // 该DLL内部线程的ID
HANDLE g_hEvent=NULL;         // 应答事件的句柄

DWORD WINAPI InSideDll_ThreadProc( LPVOID p )
{     
	/* 表示一些操作。
	如果“---- operations.----”被打印到Output窗口中了，
	说明本线程函数在被执行了。 */ 
	OutputDebugString("---- operations.---- \n"); 
	/*  InSideDll_ThreadProc的操作完成后，
	通知在g_hEvent处等待的线程,可以继续运行了。*/ 
	SetEvent(g_hEvent);
	return  1;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)   
	{
	case DLL_PROCESS_ATTACH:
		//DLL正在映射到进程地址空间中
		{     
			// 禁止线程库调用，
			DisableThreadLibraryCalls((HINSTANCE)hModule);
			// 创建DLL内线程使用的事件对象
			g_hEvent = ::CreateEvent( NULL, FALSE, FALSE, "hello11");
			//创建DLL内线程对象
			g_thread_handle = ::CreateThread(NULL,0,  
				InSideDll_ThreadProc,(LPVOID)0,0,   &( g_thread_id) ) ;
			// 等待刚创建的线程完成相关操作
			::WaitForSingleObject( g_hEvent, INFINITE );    
			// 清除资源
			::CloseHandle(g_thread_handle);
			g_thread_id = 0 ;
			g_thread_handle = NULL ;                  
			::CloseHandle(g_hEvent);
			g_hEvent=NULL;

		}
		break;
	case DLL_PROCESS_DETACH:
		// DLL正在从进程地址空间中卸载
		break;
	}
	return TRUE;
}

//----------------------end  ------------

int main()
{
	return 0;
}
