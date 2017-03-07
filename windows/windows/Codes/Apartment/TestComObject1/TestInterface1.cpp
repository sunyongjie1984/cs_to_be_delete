// TestInterface1.cpp : Implementation of CTestInterface1
#include "stdafx.h"
#include "TestComObject1.h"
#include "TestInterface1.h"

#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// CTestInterface1


STDMETHODIMP CTestInterface1::TestFunc1()
{
	// TODO: Add your implementation code here
	
/*	LPVOID lpvData = TlsGetValue(dwTlsIndex);

	if ( lpvData == NULL )
		return RPC_E_WRONG_THREAD;
*/
	std::cout << "In the itestinferface1's object, the thread's id is " << ::GetCurrentThreadId() << std::endl;

	return S_OK;
}
