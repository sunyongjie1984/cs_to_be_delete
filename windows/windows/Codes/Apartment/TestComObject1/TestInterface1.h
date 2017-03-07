// TestInterface1.h : Declaration of the CTestInterface1

#ifndef __TESTINTERFACE1_H_
#define __TESTINTERFACE1_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestInterface1
class ATL_NO_VTABLE CTestInterface1 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestInterface1, &CLSID_TestInterface1>,
	public IDispatchImpl<ITestInterface1, &IID_ITestInterface1, &LIBID_TESTCOMOBJECT1Lib>
{
private:
//	DWORD dwTlsIndex; 
public:
	CTestInterface1()
	{
/*		dwTlsIndex = TlsAlloc();
		HLOCAL l =  LocalAlloc(LMEM_FIXED, 1); 
		TlsSetValue(dwTlsIndex, l);       
*/
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTINTERFACE1)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestInterface1)
	COM_INTERFACE_ENTRY(ITestInterface1)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ITestInterface1
public:
	STDMETHOD(TestFunc1)();
};

#endif //__TESTINTERFACE1_H_
