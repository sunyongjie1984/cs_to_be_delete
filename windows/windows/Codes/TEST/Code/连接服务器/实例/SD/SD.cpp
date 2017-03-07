

   // NOTE: This code must be linked with netapi32.lib
#include "stdafx.h"
   #include <windows.h>
   #include <tchar.h>
   #include <stdio.h>
   #include <lm.h>

   // Declarations based on USERENV.H for Windows 2000 Beta 2
   #define PI_NOUI         0x00000001   // Prevents displaying of messages
   #define PI_APPLYPOLICY  0x00000002   // Apply NT4 style policy

   typedef struct _PROFILEINFO {
      DWORD    dwSize;          // Must be set to sizeof(PROFILEINFO)
      DWORD    dwFlags;         // See flags above
      LPTSTR   lpUserName;      // User name (required)
      LPTSTR   lpProfilePath;   // Roaming profile path
      LPTSTR   lpDefaultPath;   // Default user profile path
      LPTSTR   lpServerName;    // Validating DC name in netbios format
      LPTSTR   lpPolicyPath;    // Path to the NT4 style policy file
      HANDLE   hProfile;        // Registry key handle - filled by function
   } PROFILEINFO, FAR * LPPROFILEINFO;

   // Typedefs for function pointers in USERENV.DLL
   typedef BOOL (STDMETHODCALLTYPE FAR * LPFNLOADUSERPROFILE) (
      HANDLE hToken,
      LPPROFILEINFO lpProfileInfo
   );

   typedef BOOL (STDMETHODCALLTYPE FAR * LPFNUNLOADUSERPROFILE) (
      HANDLE hToken,
      HANDLE hProfile
   );

   typedef BOOL (STDMETHODCALLTYPE FAR * LPFNGETUSERPROFILEDIR) (
      HANDLE hToken,
      LPTSTR lpProfileDir,
      LPDWORD lpcchSize
   );

   HMODULE                 g_hUserEnvLib           = NULL;
   LPFNLOADUSERPROFILE     LoadUserProfile         = NULL;
   LPFNUNLOADUSERPROFILE   UnloadUserProfile       = NULL;
   LPFNGETUSERPROFILEDIR   GetUserProfileDirectory = NULL;
   BOOL InitUserEnv( void ) {

      g_hUserEnvLib = LoadLibrary( _T("userenv.dll") );
      if ( !g_hUserEnvLib ) {
         _tprintf( _T("LoadLibrary(userenv.dll) failed.  Error %d\n"),
              GetLastError() );
         return FALSE;
      }

   #ifdef UNICODE
      LoadUserProfile =
            (LPFNLOADUSERPROFILE) GetProcAddress( g_hUserEnvLib,
            "LoadUserProfileW" );
   #else
      LoadUserProfile =
            (LPFNLOADUSERPROFILE) GetProcAddress( g_hUserEnvLib,
            "LoadUserProfileA" );
   #endif

      if (!LoadUserProfile) {
         _tprintf( _T("GetProcAddress(%s) failed.  Error %d\n"),
               "LoadUserProfile", GetLastError() );
         return FALSE;
      }

      UnloadUserProfile =
            (LPFNUNLOADUSERPROFILE) GetProcAddress( g_hUserEnvLib,
            "UnloadUserProfile" );

      if (!UnloadUserProfile) {
         _tprintf( _T("GetProcAddress(%s) failed.  Error %d\n"),
               "UnloadUserProfile", GetLastError() );
         return FALSE;
      }

   #ifdef UNICODE
      GetUserProfileDirectory =
            (LPFNGETUSERPROFILEDIR) GetProcAddress( g_hUserEnvLib,
            "GetUserProfileDirectoryW" );
   #else
      GetUserProfileDirectory =
            (LPFNGETUSERPROFILEDIR) GetProcAddress( g_hUserEnvLib,
            "GetUserProfileDirectoryA" );
   #endif

      if (!GetUserProfileDirectory) {
         _tprintf( _T("GetProcAddress(%s) failed.  Error %d\n"),
               "GetUserProfileDirectory", GetLastError() );
         return FALSE;
      }

      return TRUE;
   }


   #ifdef __cplusplus
      extern "C"
   #endif

   #ifdef UNICODE
      int _cdecl
   #else
      int
   #endif

   _tmain(int argc, _TCHAR **argv, _TCHAR **envp) {

      USER_INFO_1   ui1;
      DWORD         dwError;
      HANDLE        hToken;
      PROFILEINFO   pi;
      TCHAR         szProfilePath[1024];
      DWORD         cchPath = 1024;
      WCHAR         szUserName[20];
      WCHAR         szPassword[20];

      // Check for the required command-line arguments
      if (argc < 2) {
         _tprintf( _T("Usage: AddUser <user> [password]\n") );
         return -1;
      }

      // Set USERENV.DLL function pointers
      if ( !InitUserEnv() ) {
         _tprintf( _T("Failed to set USERENV.DLL function pointers.\n") );
         return -1;
      }

      // Create local copies of the user name and password
      #ifdef UNICODE

      _tcscpy( szUserName, argv[1] );
      if ( argc == 2 ) {
         _tcscpy( szPassword, szUserName );
      } else {
         _tcscpy( szPassword, argv[2] );
      }

      #else
      {
         int n;

         n = MultiByteToWideChar(0, 0, argv[1], -1, szUserName, 20);
         if (n == 0)
         {
            _tprintf( _T("Failed to convert username to unicode\n"));
            return -1;
         }

         if ( argc == 2 ) {
            n = MultiByteToWideChar(0, 0, argv[1], -1, szPassword, 20);
         } else {
            n = MultiByteToWideChar(0, 0, argv[2], -1, szPassword, 20);
         }
         if (n == 0)
         {
            _tprintf( _T("Failed to convert password to unicode\n"));
            return -1;
         }
      }
      #endif

      // Set up the USER_INFO_1 structure that will be used to create the
      // new user account
      ZeroMemory( &ui1, sizeof(ui1) );
      ui1.usri1_name = szUserName;
      ui1.usri1_password = szPassword;
      ui1.usri1_priv = USER_PRIV_USER;
      ui1.usri1_flags = UF_NORMAL_ACCOUNT | UF_SCRIPT;

      // Create the new user account
      dwError = NetUserAdd(
            NULL,            // target computer name
            1,               // info level
            (LPBYTE) &ui1,   // address of user info structure
            NULL );          // index to invalid parameter
      if ( dwError != NERR_Success ) {
         _tprintf( _T("NetUserAdd() failed.  Error %d\n"), dwError );
         dwError = ERROR_ACCESS_DENIED;
         return -1;
      }

      if ( !LogonUser(
            argv[1],                        // user name
            _T("."),                        // domain or server
            (argc == 2) ? argv[1]:argv[2],  // password
            LOGON32_LOGON_NETWORK,          // type of logon operation
            LOGON32_PROVIDER_DEFAULT,       // logon provider
            &hToken ) ) {                   // pointer to token handle
         _tprintf( _T("LogonUser() failed.  Error %d\n"), GetLastError() );
         return -1;
      }

      // Set up the PROFILEINFO structure that will be used to load the
      // new user's profile
      ZeroMemory( &pi, sizeof(pi) );
      pi.dwSize = sizeof(pi);

      #ifdef UNICODE
      pi.lpUserName = szUserName;
      #else
      pi.lpUserName = argv[1];
      #endif

      pi.dwFlags = PI_NOUI;

      // Load the profile. Since it doesn't exist, it will be created
      if ( !LoadUserProfile(
            hToken,        // token for the user
            &pi ) ) {      // pointer to PROFILEINFO structure
         _tprintf( _T("LoadUserProfile() failed.  Error %d\n"),
               GetLastError() );
         return -1;
      }

      // Unload the profile when it is no longer needed
      if ( !UnloadUserProfile(
            hToken,              // token for the user
            pi.hProfile ) ) {    // registry key handle
         _tprintf( _T("UnloadUserProfile() failed.  Error %d\n"),
               GetLastError() );
         return -1;
      }

      // Retrieve the new user's profile directory
      if ( !GetUserProfileDirectory( hToken, szProfilePath, &cchPath ) ) {
         _tprintf( _T("GetProfilePath() failed.  Error %d\n"),
               GetLastError() );
         return -1;
      }

      // Display the new user's profile directory
      _tprintf( _T("The new user's profile path is %s\n"), szProfilePath );

      // Release USERENV.DLL
      if ( g_hUserEnvLib ) {
         FreeLibrary( g_hUserEnvLib );
      }

      return 0;
   }
