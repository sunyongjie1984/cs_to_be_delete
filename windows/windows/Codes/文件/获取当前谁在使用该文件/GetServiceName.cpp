/*=========================================================================== 
    (c) Copyright 1999, Emmanuel KARTMANN, all rights reserved                 
  =========================================================================== 
    File           : GetServiceName.cpp
    $Header: $
    Author         : Emmanuel KARTMANN
    Creation       : Friday 9/24/99 4:52:56 PM
    Remake         : 
  ------------------------------- Description ------------------------------- 

           Implementation of the GetServiceName function

  ------------------------------ Modifications ------------------------------ 
    $Log: $  
  =========================================================================== 
*/

#include <stdlib.h>
#include "stdafx.h"
#include "GetServiceName.h"
#include "WindowsRegistry.h"

// Uses Registry
CString GetServiceName(LPCTSTR lpszExecutablePath)
{
    CString szServiceName;
    CWindowsRegistry MyRegistry;
    CString szKeyName = "\\HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services";
    TCHAR lpszExecutableShortPath[_MAX_PATH+1];

    if (!GetShortPathName(lpszExecutablePath, lpszExecutableShortPath, sizeof(lpszExecutableShortPath))) {
        strcpy(lpszExecutableShortPath, lpszExecutablePath);
    }

    // Open Registry (note: the base key "LOCAL_MACHINE" is part of the KeyName)
    LONG nResult=MyRegistry.OpenKey(szKeyName, NULL, KEY_READ);
    if (nResult == ERROR_SUCCESS) {
        // Loop on all subkeys
        TCHAR lpszSubKey[FWR_MAXIMUM_KEY_SIZE];
        TCHAR lpszImagePathSubKey[FWR_MAXIMUM_KEY_SIZE];
        TCHAR lpszServicePath[_MAX_PATH+1];
        TCHAR lpszServiceShortPath[_MAX_PATH+1];
        BOOL bFound = FALSE;
        for (int i=0; MyRegistry.EnumerateSubKeys(i, lpszSubKey)==TRUE && !bFound; i++) {
            char *lpszImagePath;
            strcpy(lpszImagePathSubKey, lpszSubKey);
            strcat(lpszImagePathSubKey, "\\ImagePath");
            if (MyRegistry.QueryValue(lpszImagePathSubKey,&lpszImagePath) == ERROR_SUCCESS) {

                // (1) Expand environment variable in path
                if (ExpandEnvironmentStrings(lpszImagePath, lpszServicePath, sizeof(lpszServicePath))==0) {
                    strcpy(lpszServicePath, lpszImagePath);
                }

                // (2) Convert to short path
                if (!GetShortPathName(lpszServicePath, lpszServiceShortPath, sizeof(lpszServiceShortPath))) {
                    strcpy(lpszServiceShortPath, lpszServicePath);
                }

                // (3) Compare to executable short path
                if (!stricmp(lpszExecutableShortPath, lpszServiceShortPath)) {

                    // The registry key is the service name (internal name)
                    szServiceName=lpszSubKey; 

                    // Stop the loop
                    bFound = TRUE;
                }

                // For a string value, the pointer has been allocated: do not forget to free it
                if (lpszImagePath) {
                    // <FONT COLOR=red><U>CAUTION:</U></FONT> use <B>delete []</B>, not free or LocalFree
                    delete [] lpszImagePath;
                }
            }
       }
    }

    return(szServiceName);
}

