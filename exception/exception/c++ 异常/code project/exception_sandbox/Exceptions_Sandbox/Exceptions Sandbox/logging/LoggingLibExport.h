#pragma once

#ifdef __LOGGING_LIB_DLL_IMPL__

    #define LOGGING_LIB_EXT_CLASS  __declspec(dllexport)
    #define LOGGING_LIB_EXT_API    __declspec(dllexport)

#elif defined __USE_LOGGING_LIB_DLL__  

    #define LOGGING_LIB_EXT_CLASS  __declspec(dllimport)
    #define LOGGING_LIB_EXT_API    __declspec(dllimport)

#else

    #define LOGGING_LIB_EXT_CLASS  
    #define LOGGING_LIB_EXT_API    

#endif
