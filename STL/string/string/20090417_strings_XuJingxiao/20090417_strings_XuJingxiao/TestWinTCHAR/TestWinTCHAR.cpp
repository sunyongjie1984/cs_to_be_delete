// TestWinTCHAR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <wtypes.h>

#include <TCHAR.h>

int main()
{
    {
        // Normal string
        CHAR szMyName[] = "Norm @ SDC";
        CHAR szMyNameL[] = "norm @ sdc";
        LPCSTR lpszMyName = szMyName;
        ::printf("\nsizeof(%s) is : %u bytes!", lpszMyName, sizeof(szMyName));
        ::printf("\nLength of (%s) is : %u !", lpszMyName, ::lstrlenA(lpszMyName));
        ::printf("\nThe compare result of lstrcmpiA(\"%s\", \"%s\") is %d !",
            lpszMyName, szMyNameL, ::lstrcmpiA(lpszMyName, szMyNameL));
        ::printf("\n");
    }

    {
        // Wide string
        WCHAR szMyWName[] = L"Wide @ SDC";
        WCHAR szMyWNameL[] = L"wide @ sdc";
        LPCWSTR lpszMyWName = szMyWName;
        ::wprintf(L"\nsizeof(%s) is : %u bytes!", lpszMyWName, sizeof(szMyWName));
        ::wprintf(L"\nLength of(%s) is : %u !", lpszMyWName, ::lstrlenW(lpszMyWName));
        ::wprintf(L"\nThe compare result of lstrcmpiW(\"%s\", \"%s\") is %d !",
            lpszMyWName, szMyWNameL, ::lstrcmpiW(lpszMyWName, szMyWNameL));
        ::wprintf(L"\n");
    }

    {
        // Norm/Wide string
        TCHAR szMyTName[] = _T("Both @ SDC");
        TCHAR szMyTNameL[] = _T("both @ sdc");
        LPCTSTR lpszMyTName = szMyTName;
        ::_tprintf(_T("\nsizeof(%s) is : %u bytes!"), lpszMyTName, sizeof(szMyTName));
        ::_tprintf(_T("\nLength of(%s) is : %u !"), lpszMyTName, ::lstrlen(lpszMyTName));
        ::_tprintf(_T("\nThe compare result of lstrcmpi(\"%s\", \"%s\") is %d !"),
            lpszMyTName, szMyTNameL, ::lstrcmpi(lpszMyTName, szMyTNameL));
        ::_tprintf(_T("\n"));

    }

    ::printf("\n");
    return 0;
}

