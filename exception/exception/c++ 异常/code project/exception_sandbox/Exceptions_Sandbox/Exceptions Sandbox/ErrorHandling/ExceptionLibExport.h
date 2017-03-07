#pragma once

#ifdef __EXCEPTION_LIB_DLL_IMPL__

    #define EXCEPTION_LIB_EXT_CLASS  __declspec(dllexport)
    #define EXCEPTION_LIB_EXT_API    __declspec(dllexport)

#elif defined __USE_EXCEPTION_LIB_DLL__  

    #define EXCEPTION_LIB_EXT_CLASS  __declspec(dllimport)
    #define EXCEPTION_LIB_EXT_API    __declspec(dllimport)

#else

    #define EXCEPTION_LIB_EXT_CLASS  
    #define EXCEPTION_LIB_EXT_API    

#endif
