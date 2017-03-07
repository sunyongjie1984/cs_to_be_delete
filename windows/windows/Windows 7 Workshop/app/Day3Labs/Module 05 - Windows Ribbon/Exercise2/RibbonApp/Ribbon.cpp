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
#include <ScenicIntentPropertyHelpers.h>
#include "ribbonres.h"

IUIFramework* g_pFramework = NULL;

class CApplication
	: public CComObjectRootEx<CComMultiThreadModel>
	, public IUIApplication
	, public IUICommandHandler
{
public:
	BEGIN_COM_MAP(CApplication)
		COM_INTERFACE_ENTRY(IUIApplication)
		COM_INTERFACE_ENTRY(IUICommandHandler)
	END_COM_MAP()


	STDMETHOD(OnViewChanged)(UINT32 nViewID, __in UI_VIEWTYPE typeID, __in IUnknown* pView, UI_VIEWVERB verb, INT32 uReasonCode)  
	{ 
		return E_NOTIMPL; 
	}

	STDMETHOD(OnCreateUICommand)(UINT32 nCmdID, __in UI_COMMANDTYPE typeID, __deref_out IUICommandHandler** ppCommandHandler) 
	{ 
		if (nCmdID == cmdMyButton || nCmdID == cmdMyChoice)
		{
			return QueryInterface(IID_PPV_ARGS(ppCommandHandler));
		}
		return E_NOTIMPL;  
	}

	STDMETHOD(OnDestroyUICommand)(UINT32 commandId, __in UI_COMMANDTYPE typeID, __in_opt IUICommandHandler* pCommandHandler) 
	{ 
		return E_NOTIMPL; 
	}

	STDMETHODIMP Execute(UINT nCmdID,
		UI_EXECUTIONVERB verb, 
		__in_opt const PROPERTYKEY* key,
		__in_opt const PROPVARIANT* ppropvarValue,
		__in_opt IUISimplePropertySet* pCommandExecutionProperties)
	{
		HRESULT hr = S_OK;

		switch (verb)    
		{  
		case UI_EXECUTIONVERB_EXECUTE:
			if (nCmdID == cmdMyButton)
			{
				MessageBox(NULL, L"Clicked on My Button!", L"My Button Execute", MB_OK);		
			}	
			else if (nCmdID == cmdMyChoice)
			{
				PROPVARIANT var, varNew;

				hr = g_pFramework->GetUICommandProperty(cmdMyChoice, UI_PKEY_BooleanValue, &var);
				if (FAILED(hr))
				{
					return hr;
				}

				hr = PropVariantToBoolean(var, &_fEnabled);
				if (FAILED(hr))
				{
					return hr;
				}

				_fEnabled = !_fEnabled;
				hr = UIInitPropertyFromBoolean(UI_PKEY_Enabled, _fEnabled, &varNew);
				if (FAILED(hr))
				{
					return hr;
				}

				hr = g_pFramework->SetUICommandProperty(cmdMyButton, UI_PKEY_Enabled, varNew);
				if (FAILED(hr))
				{
					return hr;
				}

				hr = g_pFramework->InvalidateUICommand(cmdMyChoice, UI_INVALIDATIONS_PROPERTY, &UI_PKEY_Label);
				if (FAILED(hr))
				{
					return hr;
				}
			}
			break;	
		}	    
		return hr;
	}

	STDMETHODIMP UpdateProperty(UINT nCmdID,
		__in REFPROPERTYKEY key,
		__in_opt const PROPVARIANT* ppropvarCurrentValue,
		__out PROPVARIANT* ppropvarNewValue)
	{
		UNREFERENCED_PARAMETER(ppropvarCurrentValue);

		HRESULT hr = E_FAIL;

		if (key == UI_PKEY_Label)
		{
			// Update the Label of ToggleButton control
			if (nCmdID == cmdMyChoice)
			{
				if (_fEnabled)
				{
					hr = UIInitPropertyFromString(UI_PKEY_Label, 
						L"Disable Button", ppropvarNewValue);
				}
				else
				{
					hr = UIInitPropertyFromString(UI_PKEY_Label, 
						L"Enable Button", ppropvarNewValue);
				}
			}
		}

		return hr;
	}

private:
	BOOL _fEnabled;

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
