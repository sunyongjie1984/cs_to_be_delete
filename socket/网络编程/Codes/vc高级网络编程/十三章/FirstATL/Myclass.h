// Myclass.h : Declaration of the CMyclass

#ifndef __MYCLASS_H_
#define __MYCLASS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyclass
class ATL_NO_VTABLE CMyclass : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyclass, &CLSID_Myclass>,
	public IDispatchImpl<IMyclass, &IID_IMyclass, &LIBID_FIRSTATLLib>
{
public:
	CMyclass()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYCLASS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyclass)
	COM_INTERFACE_ENTRY(IMyclass)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMyclass
public:
	STDMETHOD(SayGoodbye)();
	STDMETHOD(SayHello)();
};

#endif //__MYCLASS_H_
