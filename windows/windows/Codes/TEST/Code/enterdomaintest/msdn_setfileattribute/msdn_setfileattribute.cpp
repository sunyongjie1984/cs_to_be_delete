#include <windows.h>
#include <stdio.h>

void main()
{
   WIN32_FIND_DATA FileData; 
   HANDLE hSearch; 
   DWORD dwAttrs;   
   TCHAR szDirPath[] = TEXT("d:\\TextRO\\"); 
   TCHAR szNewPath[MAX_PATH];   
   
   BOOL fFinished = FALSE; 
   
   // Create a new directory. 
   
   if (!CreateDirectory(szDirPath, NULL)) 
   { 
	   printf("Could not create new directory.\n"); 
	   return;
   } 
   
   // Start searching for text files in the current directory. 
   
   hSearch = FindFirstFile(TEXT("*.txt"), &FileData); 
   if (hSearch == INVALID_HANDLE_VALUE) 
   { 
	   printf("No text files found.\n"); 
	   return;
   } 
   
   // Copy each .TXT file to the new directory 
   // and change it to read only, if not already. 
   
   while (!fFinished) 
   { 
	   lstrcpy(szNewPath, szDirPath); 
	   lstrcat(szNewPath, FileData.cFileName); 
	   if (CopyFile(FileData.cFileName, szNewPath, FALSE))
	   { 
		   dwAttrs = GetFileAttributes(FileData.cFileName); 
		   if( GetLastError() != 0 ) return;
		   
		   if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) 
		   { 
			   SetFileAttributes(szNewPath, 
				   dwAttrs | FILE_ATTRIBUTE_READONLY); 
		   } 
	   } 
	   else 
	   { 
		   printf("Could not copy file.\n"); 
		   return;
	   } 
	   
	   if (!FindNextFile(hSearch, &FileData)) 
	   {
		   if (GetLastError() == ERROR_NO_MORE_FILES) 
		   { 
			   printf("Copied all text files.\n"); 
			   fFinished = TRUE; 
		   } 
		   else 
		   { 
			   printf("Could not find next file.\n"); 
			   return;
		   } 
	   }
   } 
   
   // Close the search handle. 
   
   FindClose(hSearch);
}
