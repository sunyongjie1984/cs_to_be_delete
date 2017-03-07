// SimpleCOM.cpp : Implementation of CSimpleCOM
#include "stdafx.h"
#include <COM4Dbg/COM4Dbg.h>
#include "SimpleCOM.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleCOM


STDMETHODIMP CSimpleCOM::Plus(double dX, double dY, double *dRet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*dRet = dX + dY;
	
	return S_OK;
}

STDMETHODIMP CSimpleCOM::StrComp(BSTR bstr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (wcscmp(bstr,L"") == 0)
	{
		return E_FAIL;
	}
	return S_OK;
}
