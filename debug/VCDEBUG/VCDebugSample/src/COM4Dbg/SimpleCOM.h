// SimpleCOM.h : Declaration of the CSimpleCOM

#ifndef __SIMPLECOM_H_
#define __SIMPLECOM_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleCOM
class ATL_NO_VTABLE CSimpleCOM : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleCOM, &CLSID_SimpleCOM>,
	public IDispatchImpl<ISimpleCOM, &IID_ISimpleCOM, &LIBID_COM4DBGLib>
{
public:
	CSimpleCOM()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLECOM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSimpleCOM)
	COM_INTERFACE_ENTRY(ISimpleCOM)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISimpleCOM
public:
	STDMETHOD(StrComp)(/*[in]*/BSTR bstr);
	STDMETHOD(Plus)(/*[in]*/ double dX, /*[in]*/ double dY, /*[out]*/ double* dRet);
};

#endif //__SIMPLECOM_H_
