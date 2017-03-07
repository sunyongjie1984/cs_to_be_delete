/* Copyright (c) Robert Walker, support@tunesmithy.co.uk
 * Free source. Do what you wish with it - treat it as you would
 * example code in a book on c programming.
 */ 

// Note that this is coded for builds with UNICODE undefined.

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include "ExceptionHandler.h"

#ifdef _DEBUG
char *szVersionDate="<Date gets shown here in release builds>";
#else
#include "VersionDate.h" // Save this every time we run the debug build.
 // so that the exception message can include the date of the release
 // which we can check to make sure we have the same version of the source as
 // the user. See the beginning of WinMain(...) for example to show how one can make it.
#endif


// http://www.codeproject.com/debug/mapfile.asp

/*
 * Note. Coded for UNICODE undefined only. 
 */

static int g_n_except;
static EXCEPTION_RECORD ExceptionRecord;
static char skip_exception_msg=0;

int Eval_Exception ( int n_except,LPEXCEPTION_POINTERS ExceptionInfo)
{
 g_n_except=n_except;
 if(ExceptionInfo)
  ExceptionRecord=*(ExceptionInfo->ExceptionRecord);
 return TRUE;
}

void ExceptionHandlerExtraParam(char is_dlg_proc,char *sztype,UINT message,WPARAM wParam,LPARAM lParam);

void ExceptionHandlerForDlgProc(char *sztype,UINT message,WPARAM wParam,LPARAM lParam)
{
 ExceptionHandlerExtraParam(1/*is_dlg_proc*/,sztype,message,wParam,lParam);
}

void ExceptionHandler(char *sztype)
{
 ExceptionHandlerExtraParam(0/*is_dlg_proc*/,sztype,0,0,0);
}


void ExceptionHandlerExtraParam(char is_dlg_proc,char *sztype,UINT message,WPARAM wParam,LPARAM lParam)
{
 char szPFileBugReport[MAX_PATH];
 char *szExceptionType="Floating point, or software exception";
 // char *szExceptionType="Exception";
 char szmsg[ONE_K];
 static time_t t_exception_msg;
	double diff=difftime(clock(),t_exception_msg)/(double)CLOCKS_PER_SEC;  
 static char skip_exception_msg;
 static char in_this;
 char szCaption[ONE_K];
 char szShortWD[MAX_PATH];
#ifdef UNICODE
 GetShortPathName(szWorkingDirectory,szShortWD,MAX_PATH);
#else
 strcpy(szShortWD,szWorkingDirectory);
#endif
 MakePathFile(szPFileBugReport,szShortWD,"BugReport.txt");
 // so we don't need to worry about unicode or MBCSTR when constructing the path
 if(in_this)
  return;
 if(skip_exception_msg)
  return;
 in_this=1;
 sprintf(szCaption,"%s Exception Handler",szAppName);
 switch(g_n_except)
 {
  case STATUS_ACCESS_VIOLATION: szExceptionType="Access violation";break;
  case STATUS_BREAKPOINT: szExceptionType="Breakpoint";break;
  case STATUS_DATATYPE_MISALIGNMENT: szExceptionType="Address misaligned";break;
#ifdef STATUS_FLOATING_DIVIDE_BY_ZERO
  case STATUS_FLOATING_DIVIDE_BY_ZERO: szExceptionType="Floating point divide by 0";break;
  case STATUS_FLOATING_OVERFLOW: szExceptionType="Floating point overflow";break;
  case STATUS_FLOATING_UNDERFLOW: szExceptionType="Floating point underflow";break;
  case STATUS_FLOATING_RESEVERED_OPERAND: szExceptionType="Reserved Floating point format";break;
#endif
  case STATUS_ILLEGAL_INSTRUCTION: szExceptionType="Illegal instruction";break;
  case STATUS_PRIVILEGED_INSTRUCTION: szExceptionType="Priviledged instruction";break;
  case STATUS_INTEGER_DIVIDE_BY_ZERO: szExceptionType="Integer divide by 0";break;
  case STATUS_INTEGER_OVERFLOW: szExceptionType="Integer overflow";break;
  case STATUS_SINGLE_STEP: szExceptionType="Single step";break;
 }
	sprintf(szmsg,
        "Exception occurred at %x:\n\n%s\n\n"
								"It may be possible to continue normally.\n\n"
		 					"Continue?.\n\n"
		 					"Ctrl + Yes to continue and skip this message for rest of session.\n\n"
        "Answer No to close program.\n\n"
        "Shift + Yes or No to send a bug report.\n\n"
        "If this message recurs please send a report. You will get a reply, and most bugs get fixed quickly :-)."
								,ExceptionRecord.ExceptionAddress,szExceptionType,sztype,LOWORD(wParam),HIWORD(wParam),LOWORD(lParam),HIWORD(lParam)
								);
 {
  FILE *fp=fopen(szPFileBugReport,"w");
  if(fp)
  {
   if(is_dlg_proc)
   fprintf(fp,"%s - build date %s\n"
       "Operating System %s\n\n"
       "Exception occurred at %x:\n\n%s (in %s)\n\n"
							"message %d, wParam lw %d hw %d, lParam lw %d, hw %d\n\n"
       ,szAppName,szVersionDate,szFindOS()
							,ExceptionRecord.ExceptionAddress,szExceptionType,sztype
       ,message,LOWORD(wParam),HIWORD(wParam),LOWORD(lParam),HIWORD(lParam)
      );
   fclose(fp);
  }
  // only show exception messages at most one every three seconds
  if(diff>3||t_exception_msg==0)
  {
   if(IDNO==MessageBox(ghwndFocus,szmsg,szCaption,MB_YESNO|MB_ICONEXCLAMATION))
				exit(0);
   if(GetKeyState(VK_CONTROL)<0)
    skip_exception_msg=1;
   if(GetKeyState(VK_SHIFT)<0)
   {
    char szSupport[MAX_PATH+50];
    sprintf(szSupport,"%s Support",szAppName);
    SendEmailMessage(szSupport,SZ_EMAIL,"Bug Report"
							,"Thanks for sending a bug report!\n\n"
				   "It will help if you add any observations that may help to locate the bug here,\r\n"
       "...................................\r\n"
       "\r\n\r\n"
       "...................................\r\n"
					  "Examples of the sort of thing that is useful to know are: that it happened when you pressed "
							"a particular button, opened a particular file (attach any relevant file to this e-mail), etc. All this makes it easier to locate it.\n\n"
       "Be sure to save this message or send it straight away - if you close this message without saving it, then it usually gets discarded by your e-mail program.\n\n"
       "Expect to hear from me soon. Most bugs get fixed within a day or two.\n\n"
       "Thanks!\n\n"
       SZ_NAME
       ,szPFileBugReport
							);
   }
   t_exception_msg=clock();
  }
 }
 in_this=0;
}
