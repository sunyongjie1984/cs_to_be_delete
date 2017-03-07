#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <assert.h>
#include <windows.h>

#include <lm.h>
#pragma comment(lib,"Netapi32.lib")
int wmain(int argc, wchar_t *argv[])
{
   LPWKSTA_USER_INFO_0 pBuf = NULL;
   LPWKSTA_USER_INFO_0 pTmpBuf;
   DWORD dwLevel = 0;
   DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwResumeHandle = 0;
   DWORD i;
   DWORD dwTotalCount = 0;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   if (argc > 2)
   {
      fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
      exit(1);
   }

   if (argc == 2)
      pszServerName = argv[1];
   fwprintf(stderr, L"\nUsers currently logged on %s:\n", pszServerName);

   do // begin do
   {
      nStatus = NetWkstaUserEnum((char*)pszServerName,
                                 dwLevel,
                                 (LPBYTE*)&pBuf,
                                 dwPrefMaxLen,
                                 &dwEntriesRead,
                                 &dwTotalEntries,
                                 &dwResumeHandle);

      if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
      {
         if ((pTmpBuf = pBuf) != NULL)
         {
            for (i = 0; (i < dwEntriesRead); i++)
            {
               assert(pTmpBuf != NULL);

               if (pTmpBuf == NULL)
               {

                  fprintf(stderr, "An access violation has occurred\n");
                  break;
               }

               wprintf(L"\t-- %s\n", pTmpBuf->wkui0_username);

               pTmpBuf++;
               dwTotalCount++;
            }
         }
      }

      else
         fprintf(stderr, "A system error has occurred: %d\n", nStatus);

      if (pBuf != NULL)
      {
         NetApiBufferFree(pBuf);
         pBuf = NULL;
      }
   }

   while (nStatus == ERROR_MORE_DATA); // end do

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);

   return 0;
}
