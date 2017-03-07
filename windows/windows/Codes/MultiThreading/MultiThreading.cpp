// MultiThreading.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <windows.h>

int g_i = 10;  //一个全局变量

CRITICAL_SECTION cs;  //一个临界区变量

DWORD WINAPI ThreadProc(LPVOID lpv)
{
//	EnterCriticalSection(&cs);  //进入临界区

	g_i += 10;
	std::cout <<"In the Thread " << ::GetCurrentThreadId() << ",the first g_i is "  << g_i << "!" <<std::endl;

//	::LeaveCriticalSection(&cs);

	Sleep(5000); //睡眠

//	EnterCriticalSection(&cs);
	g_i += 10;

	std::cout <<"In the Thread " << ::GetCurrentThreadId() << ",the secend g_i is "  << g_i << "!" <<std::endl;

//	::LeaveCriticalSection(&cs);

	return 0;

}

int main(int argc, char* argv[])
{
	
	DWORD threadID[2];
	HANDLE hThreads[2];

	InitializeCriticalSection(&cs);

	for(int i = 0; i <= 1; i++ )			//创建两个线程
		hThreads[i] = ::CreateThread(NULL,
									0,
									ThreadProc,
									NULL,
									0,
									&threadID[i]);


	WaitForMultipleObjects(2,hThreads,TRUE,INFINITE);   //等待线程结束

	for(i = 0; i <= 1; i++ )
		::CloseHandle(hThreads[i]);				//关闭线程句柄



	system("pause");

	return 0;
}