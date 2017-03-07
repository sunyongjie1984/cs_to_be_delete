/********************************************************************
  Purpose:	Implementation of CDemoDCOM. 

  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/

#include "stdafx.h"
#include "DemoDCOM.h"
#include "JException.h"

void ServerFunc3() { throw JException("Demo of a failure on the server side");  }

void ServerFunc2() { ServerFunc3(); }

void SomeApplicationLogic() { ServerFunc2(); }

STDMETHODIMP CDemoDCOM::DoSomethingRemote()
{
    // This is the standard way to handle server requests. Wrap the application logic with a try catch
    // clause and on the catch handler serialize the exception as ErrorInfo.
    // There's no need to have catch handlers for exceptions that inherit from JException.
    // The exception's type is encoded in the XML string and will be recreated correctly on the client side.
    try {
        SomeApplicationLogic();
    }
    catch (const JException& e) {
    	return CComCoClass::Error(e.ToXml().c_str());	
    }    
    return S_OK;
}

STDMETHODIMP CDemoDCOM::InterfaceSupportsErrorInfo(REFIID riid)
{
    if (InlineIsEqualGUID(IID_IDemoDCOM, riid)) {
        return S_OK;
    }
    return S_FALSE;
}

