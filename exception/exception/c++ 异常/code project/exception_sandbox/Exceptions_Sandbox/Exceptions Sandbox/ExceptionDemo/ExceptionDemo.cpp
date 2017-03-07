/********************************************************************
  Purpose:	Demonstrates two cases of handling exceptions. One that is thrown locally
            and one from a remote server.
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#include "stdafx.h"
#include "JException.h"
#include "Log.h"
#include "DemoServerHelper.h"
#include "DemoServer_i.c"
#include <atlcomcli.h>
#include <oaidl.h>

void Func3() 
{ 
    throw JException("Demo of a failure. Error %d", 67);  
}

void Func2() 
{ 
    Func3(); 
}

void DoSomething() 
{ 
    Func2(); 
}

void ActOnTheServer(IDemoDCOM* p_demoCOM)
{
    // Use COM_ACTION macro to handle exceptions thrown by the server and DCOM errors
    COM_ACTION(p_demoCOM->DoSomethingRemote());
}

int _tmain(int argc, _TCHAR* argv[]) 
{
    try 
    {
        Trace("[Info] An example of throwing an exception within the same process and thread\n");
    	DoSomething();
    }
    catch (JException& e) 
    {        
        e.PrependToCause("Failed to Do Something due to: ");
    	Trace("[Error] %s", e.GetCause().c_str());
        Trace("[Error] Exception stack trace: \n%s\n", e.GetStackTrace().c_str());
    } 

    try 
    {
        Trace("[Info] An example of handling an exception that is thrown by a remote server\n");
        // Create the server locally
        IDemoDCOM* p_demoCOM = CreateDemoProxy("localhost"); 
        
        ActOnTheServer(p_demoCOM);

        p_demoCOM->Release();

        CoUninitialize();
    }
    catch (const JException& e) 
    {
        Trace("[Error] %s", e.AsString().c_str());
    }

	return 0;
}

