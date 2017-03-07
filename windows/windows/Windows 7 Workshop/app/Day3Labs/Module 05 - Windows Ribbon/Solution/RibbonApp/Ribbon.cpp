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

	CApplication() : _fEnabled(TRUE) {}

    STDMETHOD(OnViewChanged)(UINT32 nViewID, __in UI_VIEWTYPE typeID, __in IUnknown* pView, UI_VIEWVERB verb, INT32 uReasonCode)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(OnCreateUICommand)(UINT32 nCmdID, 
                               __in UI_COMMANDTYPE typeID,
                               __deref_out IUICommandHandler** ppCommandHandler)
    {
		if (nCmdID == cmdMyButton ||
            nCmdID == cmdMyChoice )
		{
			return QueryInterface(IID_PPV_ARGS(ppCommandHandler));;
		}

        return E_NOTIMPL;
    }

    STDMETHOD(OnDestroyUICommand)(UINT32 commandId, __in UI_COMMANDTYPE typeID, __in_opt IUICommandHandler* pCommandHandler)
    {
        return E_NOTIMPL;
    }

    // User action callback, with transient execution parameters
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

    STDMETHODIMP UpdateProperty(UINT32 commandId, REFPROPERTYKEY key, __in_opt  const PROPVARIANT *currentValue, PROPVARIANT *newValue)
    {
        UNREFERENCED_PARAMETER(currentValue);

        HRESULT hr = E_FAIL;
        
        if (key == UI_PKEY_Label)
        {
            // Update the Label of ToggleButton control
            if (commandId == cmdMyChoice)
            {
		        if (_fEnabled)
		        {
			        hr = UIInitPropertyFromString(UI_PKEY_Label, L"Disable Button", newValue);
		        }
		        else
		        {
			        hr = UIInitPropertyFromString(UI_PKEY_Label, L"Enable Button", newValue);
		        }
            }
        }

        return hr;
    }

private:
    BOOL _fEnabled;
};

HRESULT InitRibbon(HWND host)
{
    HRESULT hr = ::CoCreateInstance(CLSID_ScenicIntentUIFramework, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pFramework));
    if (FAILED(hr))
    {
        return hr;
    }

    CComObject<CApplication> *pApplication = NULL;
    hr = CComObject<CApplication>::CreateInstance(&pApplication);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = g_pFramework->Initialize(host, pApplication);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = g_pFramework->LoadUI(GetModuleHandle(NULL), L"APPLICATION_RIBBON");
    if (FAILED(hr))
    {
        return hr;
    }
    
    return hr;
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
