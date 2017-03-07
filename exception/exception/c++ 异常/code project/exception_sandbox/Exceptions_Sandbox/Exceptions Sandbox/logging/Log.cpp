/********************************************************************
  Purpose:	Implementation of Log.h	that uses the Windows function for sending messages to the debugger.
            Output can be viewed with DebugView (http://technet.microsoft.com/en-us/sysinternals/bb896647.aspx)
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#include "Log.h"

#include <wtypes.h>
#include <winbase.h>
#include <Strsafe.h>
#include <stdarg.h>
#include <iostream>

void Trace(const string messageFormat, ...)
{
    char tempBuffer[6144];
    va_list args;
    va_start(args, messageFormat);
    vsnprintf_s(tempBuffer, 6144, _TRUNCATE, messageFormat.c_str(), args);
    va_end(args);

    OutputDebugString(tempBuffer);
    std::cout << tempBuffer;

}
