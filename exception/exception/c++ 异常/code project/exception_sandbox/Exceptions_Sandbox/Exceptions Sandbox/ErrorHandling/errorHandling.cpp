/********************************************************************
  Purpose:	Implementation of errorHandling.h
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#include "errorHandling.h"

string TranslateCOMException(HRESULT hr)
{
    LPVOID lpMsgBuf = 0;
    ::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL 
        );
    string result;
    if (lpMsgBuf)
    {
        result =(LPCTSTR)lpMsgBuf;
        LocalFree(lpMsgBuf);
    }

    return result;
}