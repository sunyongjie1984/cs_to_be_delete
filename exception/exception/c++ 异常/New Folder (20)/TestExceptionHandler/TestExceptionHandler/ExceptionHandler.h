/* Copyright (c) Robert Walker, support@tunesmithy.co.uk
 * Free source. Do what you wish with it - treat it as you would
 * example code in a book on c programming.
 */ 

// Note that this is coded for builds with UNICODE undefined.

#ifndef INCLUDE_EXCEPTION_HANDLER_H
#define INCLUDE_EXCEPTION_HANDLER_H

// Set these appropriately for your app.
#define SZ_EMAIL "support@tunesmithy.co.uk"
#define SZ_NAME "Robert Walker"
// Set these in your WinMain
extern char szWorkingDirectory[MAX_PATH];
extern char szAppName[MAX_PATH];

// Set this to whichever window has the focus - so that the exception handler can use
// it as its parent window for the message boxes and e-mail dialog. If left at NULL then it just
// does them with NULL as parent.
extern HWND ghwndFocus;


#ifdef _DEBUG
 /* normally wouldn't have the exception handler in debug builds as it is better 
  * to break immediately at the exception - if one wants to continue one
  * can skip over the statement that causes the exception in the debugger
  * But here, wan't to demo it in debug mode too, so enable it.
  */
 #define cl_exception_handler
#else
 #define cl_exception_handler
#endif

/* Now you bracket any code that may have an exception with
 * DO_ENTER_TRY_BLOCK
 * DO_EXIT_TRY_BLOCK_DLGPROC(szName,message,wParam,lParam)
 *
 * or 
 * DO_ENTER_TRY_BLOCK
 * DO_EXIT_TRY_BLOCK_PROC(szName)
 */

#ifdef cl_exception_handler
#define DO_ENTER_TRY_BLOCK\
 __try\
 {

void ExceptionHandlerForDlgProc(char *sztype,UINT message,WPARAM wParam,LPARAM lParam);
void ExceptionHandler(char *sztype);
int Eval_Exception ( int n_except,LPEXCEPTION_POINTERS ExceptionInfo);

#define DO_EXIT_TRY_BLOCK_DLGPROC(szName,message,wParam,lParam)\
 }\
 __except(Eval_Exception(GetExceptionCode(),GetExceptionInformation()))\
 {\
  ExceptionHandlerForDlgProc(szName,message,wParam,lParam);\
 }

#define DO_EXIT_TRY_BLOCK_PROC(szName)\
 }\
 __except(Eval_Exception(GetExceptionCode( ),GetExceptionInformation()))\
 {\
  ExceptionHandler(szName);\
 }
#else
#define DO_ENTER_TRY_BLOCK
#define DO_EXIT_TRY_BLOCK_DLGPROC(szName,message,wParam,lParam)
#define DO_EXIT_TRY_BLOCK_PROC(szName)
#endif

// in ExceptionHandler.cpp
int Eval_Exception ( int n_except,LPEXCEPTION_POINTERS ExceptionInfo);
void ExceptionHandlerExtraParam(char is_dlg_proc,char *sztype,UINT message,WPARAM wParam,LPARAM lParam);
void ExceptionHandlerForDlgProc(char *sztype,UINT message,WPARAM wParam,LPARAM lParam);
void ExceptionHandler(char *sztype);


void ExceptionHandlerExtraParam(char is_dlg_proc,char *sztype,UINT message,WPARAM wParam,LPARAM lParam);

// in ExceptionHandlerUtils.cpp
char substrcmp(const char * pstr1,const char * pstrsubstr);
int find_char_from_end(char *sz,char c);
void MakePathFile(char *szPathFile,char *szPath,char *szFile);
char *szFindOS(void);

#include <mapi.h>

void DoMAPISendEmail(LHANDLE lhSession,         
  ULONG ulUIParam,           
  lpMapiMessage lpMessage,   
  FLAGS flFlags);          

void SendEmailMessage(char *szRecipientName,char *szRecipientEmailAddress
                     ,char *szSubject
                     ,char *szEMailMessageText
                     ,char *szPFileAttachment
                     );


#define FREE_IF_NON_ZERO(p) if(p) free(p)
#define ONE_K 1024

#endif// INCLUDE_EXCEPTION_HANDLER_H
