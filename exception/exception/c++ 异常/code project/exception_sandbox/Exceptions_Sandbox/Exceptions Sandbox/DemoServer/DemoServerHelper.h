/********************************************************************
    Purpose:	Contains a single utility function to ease the creation of the 
                demo server's proxy on the client side.

    Created:	8 Aug, 2009
    Author:	    Yalon Lotan
*********************************************************************/
#pragma once

#include "DemoServer_i.h"
#include <string>
#include <sstream>
#include "errorHandling.h"
#include <atlconv.h>

/*
 * Initializes COM and instantiates a DemoServer on the given server, if it's not already running.
 *
 * Access   : public
 * Parameter: string serverName - name of the server on which to instantiate DemoServer. 
 *                                Use an empty string or "localhost" to run locally
 * Returns  : a pointer to an instance of a proxy to DemoServer
 */
IDemoDCOM* CreateDemoProxy(string serverName) {
    HRESULT hr;

    // Initialize COM library
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        throw JException("Failed to initialize the COM library due to: " + TranslateCOMException(hr));														
    }

    // Set a low level of security
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_NONE, 
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL, 
        EOAC_NONE, 
        NULL);
    if (FAILED(hr)) {
        throw JException("Failed to register and set security values due to: " + TranslateCOMException(hr));														
    }

	// Create the server info
    USES_CONVERSION; 
	COSERVERINFO serverInfo; 
	COSERVERINFO* pServerInfo;
	serverInfo.dwReserved1 = 0;
	serverInfo.dwReserved2 = 0;
    // Convert the server name from ANSI to LPWSTR
	serverInfo.pwszName = A2W(serverName.c_str());
	serverInfo.pAuthInfo = NULL;

	if (serverName.empty()) {
		pServerInfo = NULL;
		Trace("Attempt to create an instance of DemoServer on local host (server name not provided)\n");
	} else {
		pServerInfo = &serverInfo;
		Trace("Attempt to create an instance of DemoServer on host: %s\n", serverName.c_str());
	}

	MULTI_QI qi;
    qi.pIID = &IID_IDemoDCOM;
	qi.pItf = NULL;
	qi.hr = 0;

	hr = CoCreateInstanceEx(
        CLSID_DemoDCOM, 
        NULL,	
		CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER,
		pServerInfo, 
        1, 
        &qi);

	if (FAILED(hr)) {
		string cause = "Failed to create an instance of DemoServer due to: " + TranslateCOMException(hr);									
		throw JException(cause);														
	}

	if (FAILED(qi.hr)) {
		string cause = "IDemoDCOM interface is missing. Further info: " + TranslateCOMException(hr);									
		throw JException(cause);														
	}
    return (IDemoDCOM*)qi.pItf;
}
