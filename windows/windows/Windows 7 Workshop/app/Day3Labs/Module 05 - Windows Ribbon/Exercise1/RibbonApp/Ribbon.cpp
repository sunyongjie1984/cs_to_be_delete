// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#include "stdafx.h"

#include <atlbase.h>
#include <atlcom.h>
#include <initguid.h>

#include <scenicintent.h>

IUIFramework* g_pFramework = NULL;

class CApplication
	: public CComObjectRootEx<CComMultiThreadModel>
	, public IUIApplication
{
public:
	BEGIN_COM_MAP(CApplication)
		COM_INTERFACE_ENTRY(IUIApplication)
	END_COM_MAP()


	STDMETHOD(OnViewChanged)(UINT32 nViewID, __in UI_VIEWTYPE typeID, __in IUnknown* pView, UI_VIEWVERB verb, INT32 uReasonCode)  
	{ 
		return E_NOTIMPL; 
	}

	STDMETHOD(OnCreateUICommand)(UINT32 nCmdID, __in UI_COMMANDTYPE typeID, __deref_out IUICommandHandler** ppCommandHandler) 
	{ 
		return E_NOTIMPL; 
	}

	STDMETHOD(OnDestroyUICommand)(UINT32 commandId, __in UI_COMMANDTYPE typeID, __in_opt IUICommandHandler* pCommandHandler) 
	{ 
		return E_NOTIMPL; 
	}
};

HRESULT InitRibbon(HWND hWindowFrame)
{
	::CoCreateInstance(CLSID_ScenicIntentUIFramework, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pFramework));

	CComObject<CApplication> *pApplication = NULL;
	CComObject<CApplication>::CreateInstance(&pApplication);

	g_pFramework->Initialize(hWindowFrame, pApplication);

	g_pFramework->LoadUI(GetModuleHandle(NULL), L"APPLICATION_RIBBON");

	return 0;
}

void DestroyRibbon()
{
	if (g_pFramework)
	{
		g_pFramework->Destroy();
		g_pFramework->Release();
		g_pFramework = NULL;
	}
}
