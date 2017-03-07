#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>

#include "..\TestComObject1\TestComObject1_i.c"
#include "..\TestComObject1\TestComObject1.h"

DWORD WINAPI ThreadProc(LPVOID lpv)
{

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	if ( FAILED(hr) )
	{
		std::cout << "CoinitializeEx failed!" << std::endl;
		return 0;
	}

	ITestInterface1 *pTest = NULL;

	hr = ::CoCreateInstance(CLSID_TestInterface1,
							0,
							CLSCTX_INPROC,
							IID_ITestInterface1,
							(void**)&pTest);

	if ( FAILED(hr) )
	{
		std::cout << "CoCreateInstance failed!" << std::endl;
		return 0;
	}

	hr = pTest->TestFunc1();

	if ( FAILED(hr) )
	{
		std::cout << "TestFunc1 failed!" << std::endl;
		return 0;
	}
	

	pTest->Release();

	::CoUninitialize();

	return 0;
}


int main(int argc, char* argv[])
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	if ( FAILED(hr) )
	{
		std::cout << "CoinitializeEx failed!" << std::endl;
		return 0;
	}

	ITestInterface1 *pTest = NULL;

	hr = ::CoCreateInstance(CLSID_TestInterface1,
							0,
							CLSCTX_INPROC,
							IID_ITestInterface1,
							(void**)&pTest);

	if ( FAILED(hr) )
	{
		std::cout << "CoCreateInstance failed!" << std::endl;
		return 0;
	}





	DWORD threadID;
	HANDLE hThreads  =   ::CreateThread(NULL,			//创建一个进程
										0,
										ThreadProc,
										NULL,  //将pTest作为一个参数传入新线程
										0,
										&threadID);
	hr = pTest->TestFunc1();
	
	if ( FAILED(hr) )
	{
		std::cout << "TestFunc1 failed!" << std::endl;
		return 0;
	}




	::WaitForSingleObject(hThreads,INFINITE);	//等待线程结束



	::CloseHandle(hThreads);				//关闭线程句柄

	pTest->Release();

	::CoUninitialize();

	system("pause");

	
	return 0;
}
