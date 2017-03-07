#include "excptstorage.h"
#include <windows.h>

namespace
{
    DWORD dwstorage;
}

namespace my_handler
{
    __declspec(dllexport) exception_storage* get_exception_storage() throw()
    {
        void *p = TlsGetValue(dwstorage);
        return reinterpret_cast<exception_storage*>(p);
    }
}


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    using my_handler::exception_storage;
    exception_storage *p;
    switch(ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        //For the first main thread, this case also contains implicit 
        //DLL_THREAD_ATTACH, hence there is no DLL_THREAD_ATTACH for 
        //the first main thread.
        dwstorage = TlsAlloc();
        if(-1 == dwstorage)
            return FALSE;
        p = new exception_storage();
        TlsSetValue(dwstorage, p);
        break;
    case DLL_THREAD_ATTACH:
        p = new exception_storage();
        TlsSetValue(dwstorage, p);
        break;
    case DLL_THREAD_DETACH:
        p = my_handler::get_exception_storage();
        delete p;
        break;
    case DLL_PROCESS_DETACH:
        p = my_handler::get_exception_storage();
        delete p;
        break;
    }
    return TRUE;
}
