/********************************************************************
  Purpose:	Utilities for invoking functions,that might throw exceptions, on a remote server through DCOM.
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#pragma once

#include "JException.h"

/*
 * Converts the given hr to a descriptive string.
 *
 * Parameter: HRESULT hr - status, to be examined, that was returned by some DCOM function
 * Returns  : string describing the error
 */
EXCEPTION_LIB_EXT_API string TranslateCOMException(HRESULT hr);

/* 
 * A macro for invoking DCOM functions on the client side.
 * The key benefit of it is conversion of JException that is thrown on the server side to
 * an appropriate one on the client side, which overcomes the lack of such mechanism in DCOM.
 * The rethrown exception contains the stack trace of both the server and the client.
 * For example:
 *
 * COM_ACTION(p_demoCOM->DoSomethingRemote());
 *
 * Parameter: _comFunction - an expression to execute
 */
#define COM_ACTION( _comFunction )														\
{																						\
    HRESULT hr;																			\
    if ( ( hr = _comFunction ) < 0 )													\
    {																					\
    USES_CONVERSION;																    \
    /* Smart pointer to release the IErrorInfo when done with it */					    \
    CComPtr<IErrorInfo> pError = NULL;												    \
    JException e;																	    \
    if ( GetErrorInfo(0, &pError) == S_OK && pError != NULL ) {						    \
        /* Smart pointer wrapper to release strError when done with it */			    \
        CComBSTR strError;															    \
        pError->GetDescription( &strError );										    \
        /* Parse the string to form a JException and throw the exception */			    \
        e = JException::FromXml( strError );										    \
    } else {																		    \
        /* Error info is missing, try to figure out what went wrong from the hr */	    \
        string cause = TranslateCOMException(hr);									    \
        e = JException(cause);														    \
    }																				    \
    throw e;																		    \
    }																					\
}
