#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <mapi.h>
#include "ExceptionHandler.h"
#ifdef _DEBUG
char *szVersionDate="<Date gets shown here in release builds>";
#else
#include "VersionDate.h" // gets saved every time we run the debug build.
#endif
#define FREE_IF_NON_ZERO(p) if(p) free(p)

extern char szWorkingDirectory[MAX_PATH];
extern char szAppName[MAX_PATH];
#define ONE_K 1024
static int g_n_except;
extern HWND ghwndFocus;// Calling app can set this global to whichever window has the focus
// http://www.codeproject.com/debug/mapfile.asp

/*
 * Note. Coded for UNICODE undefined only. 
 */

static EXCEPTION_RECORD ExceptionRecord;
static char skip_exception_msg=0;

int Eval_Exception ( int n_except,LPEXCEPTION_POINTERS ExceptionInfo)
{
 g_n_except=n_except;
 if(ExceptionInfo)
  ExceptionRecord=*(ExceptionInfo->ExceptionRecord);
 return TRUE;
}

char substrcmp(const char * pstr1,const char * pstrsubstr)
//returns 0 if the same, or lpstrsubstr a sub string of lpstr1
{
long i;
TCHAR c1[2],c2[2];
char return_value=0;
c1[1]=c2[1]='\0';
if(pstr1==NULL||pstrsubstr==NULL)                          
{return_value=1;goto to_return;}
for(i=0;;i++)
 {
 c1[0]=pstr1[i];
 c2[0]=pstrsubstr[i];
 if(c2[0]=='\0')
{return_value=0;goto to_return;}
 if(c1[0]!=c2[0])
{return_value=1;goto to_return;}
 }
 to_return:
 return return_value;
}

int find_char_from_end(char *sz,char c)
{
	int iext_pos;
	for(iext_pos=strlen(sz);iext_pos>0;iext_pos--)
		if(sz[iext_pos]==c)
			return iext_pos;
	return 0;
}

void MakePathFile(char *szPathFile,char *szPath,char *szFile)
{
 if(!szPath||!szFile)
  return;
 if(szFile[0]=='\0')
 {
  strcpy(szPathFile,szPath);
  if(strlen(szPathFile)>1&&strlen(szPathFile)<MAX_PATH-1)
  if(szPathFile[strlen(szPath)-1]!='\\')
   strcat(szPathFile,"\\");
  return;
 }
 if(szFile[1]==':'||(szFile[0]=='\\'||szFile[1]=='\\'))
 {// to deal with use of "\\machine\path\file" for networks.
  strcpy(szPathFile,szFile);return;
 }
 else
 {
  int ifile=0;
  int istrlen=0;
  int ipos=0,nfolders_retrace=0;
  char szTPath[MAX_PATH],szTFile[MAX_PATH];
  char szTPathFile[2*MAX_PATH];
  strcpy(szTPath,szPath);
  strcpy(szTFile,szFile);
  if(szFile[0]=='\\')
   strcpy(szTFile,&szFile[1]);
  strcpy(szTPathFile,szTPath);
	 istrlen=strlen(szTPathFile);
  if(istrlen>0&&szTPathFile[istrlen-1]!='\\')
  {
		 szTPathFile[istrlen]='\\';
		 szTPathFile[istrlen+1]='\0';
  }
  ifile=0;
  // look for .\ and ..\ in the path
  for(;;)
  {
   char c=szTFile[ifile];
   if(c=='.')
   {
    if(substrcmp(&szTFile[ifile],".\\")==0)
    {ipos+=2;continue;}
    if(substrcmp(&szTFile[ifile],"..\\")==0)
    {nfolders_retrace++;ifile+=3;continue;}
    break;
   }
   else
    break;
  }
  if(nfolders_retrace>0)
  {
   szTPathFile[max(0,istrlen-1)]='\0';//remove the '\\' at the end
   for(;nfolders_retrace>0;nfolders_retrace--)
   {
    int ifolder=find_char_from_end(szPathFile,'\\');
    if(ifolder>0)
     szTPathFile[ifolder]='\0';
    else
     break;
   }
		 strcat(szTPathFile,"\\");
  }
	 strcat(szTPathFile,&szTFile[ifile]);
	 szTPathFile[MAX_PATH-1]='\0';
  strcpy(szPathFile,szTPathFile);
 }
}

char *szFindOS(void)
{
 OSVERSIONINFO OSversion;
 static char szVersion[ONE_K];
 OSversion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
 GetVersionEx(&OSversion);
 szVersion[0]='\0';
 switch(OSversion.dwPlatformId)
 {
  case VER_PLATFORM_WIN32s: 
         sprintf(szVersion,"Windows %d.%d",OSversion.dwMajorVersion,OSversion.dwMinorVersion);
	  break;
  case VER_PLATFORM_WIN32_WINDOWS:
  	if(OSversion.dwMinorVersion==0)
	    strcpy(szVersion,"Windows 95");  
	  else
         if(OSversion.dwMinorVersion==10)  
	    strcpy(szVersion,"Windows 98");
       	 else
         if(OSversion.dwMinorVersion==90)  
	     strcpy(szVersion,"Windows Me");

         break;
  case VER_PLATFORM_WIN32_NT:
  	if(OSversion.dwMajorVersion==5 && OSversion.dwMinorVersion==0)
        sprintf(szVersion,"Windows 2000 With %s", OSversion.szCSDVersion);
        else	
        if(OSversion.dwMajorVersion==5 &&   OSversion.dwMinorVersion==1)
            sprintf(szVersion,"Windows XP %s",OSversion.szCSDVersion);
        else	
	if(OSversion.dwMajorVersion<=4)
	   sprintf(szVersion,"Windows NT %d.%d with %s",OSversion.dwMajorVersion,OSversion.dwMinorVersion,OSversion.szCSDVersion);			
        else	
            //for unknown windows/newest windows version
	   sprintf(szVersion,"Windows %d.%d ",OSversion.dwMajorVersion,OSversion.dwMinorVersion);			
   
 }
 return szVersion;
}

#define MAX_EMAIL_FILES 1
MapiMessage EMailMessage;
char do_ok_email_msg;
MapiRecipDesc recip,originator;
MapiFileDesc lpEmailFiles[MAX_EMAIL_FILES];
void DoSendEmail(VOID *pvoid);

void SendEmailMessage(char *szRecipientName,char *szRecipientEmailAddress
                     ,char *szSubject
                     ,char *szEMailMessageText
                     ,char *szPFileAttachment
                     )
{
 // adapted from c++ code at http://mlarchive.ima.com/mapi-l/1999/0603.html
 memset(&recip, 0, sizeof(recip));
 recip.ulRecipClass = MAPI_TO;
 memset(&originator, 0, sizeof(originator));
 originator.ulRecipClass = MAPI_ORIG;
 recip.lpszName=strdup(szRecipientName);              
 recip.lpszAddress=strdup(szRecipientEmailAddress);
 // prepare the message -----------------------------------------------------
 memset(&EMailMessage, 0, sizeof(EMailMessage));
 EMailMessage.nRecipCount,szRecipientEmailAddress[0]=='\0'?0:1;
 EMailMessage.lpRecips = &recip;
 EMailMessage.lpOriginator=&originator;
 EMailMessage.lpszSubject=strdup(szSubject);
 EMailMessage.lpszNoteText=strdup(szEMailMessageText);
 EMailMessage.nFileCount=1;
 EMailMessage.lpFiles=lpEmailFiles;
 memset(&lpEmailFiles, 0, MAX_EMAIL_FILES*sizeof(MapiFileDesc));
 if(szPFileAttachment&&szPFileAttachment[0]!='\0')
 {
  lpEmailFiles[0].nPosition=-1;
  lpEmailFiles[0].lpszPathName=strdup(szPFileAttachment);
 }
 DoSendEmail(NULL);
}

extern HINSTANCE MapiLib;

void DoSendEmail(VOID *pvoid)
{
 ULONG uret=0;
 DO_ENTER_TRY_BLOCK
 MapiLib=LoadLibrary(TEXT("MAPI32.DLL")); //Manual access only since no .lib file
 if (NULL == MapiLib)
 {
  MessageBox(ghwndFocus,"The MAPI library MAPI32.DLL couldn't be loaded to send the e-mail","Send e-mail",MB_ICONEXCLAMATION);
  return;
 }
 { 
  // typedef int  (*MapiMessageProc)(LHANDLE,ULONG,lpMapiMessage,FLAGS,ULONG);
  PROC lpfnSendMail = (MapiMessageProc)GetProcAddress(MapiLib, "MAPISendMail");
  if(NULL == lpfnSendMail)
   MessageBox(ghwndFocus,"The MAPI library MAPI32.DLL loaded but seems to be corrupt? Couldn't find MAPISendMail function in it","Send e-mail",MB_ICONEXCLAMATION);
  else
  {
   char *szmsg="An unspecified error occurred";
   // uret=lpfnSendDocuments(0,";","L:\\e-cards\\blue_flower.jpg;L:\\e-cards\\r_familiar_territory.mid",NULL,NULL);
  	DO_ENTER_TRY_BLOCK
   uret=lpfnSendMail(0, ghwndFocus, &EMailMessage, MAPI_LOGON_UI|MAPI_DIALOG, 0 );//|MAPI_DIALOG
   DO_EXIT_TRY_BLOCK_PROC("lpfnSendMail")
   switch(uret)
   {
   case MAPI_E_AMBIGUOUS_RECIPIENT:szmsg="Multiple identical recipients";break;
   case MAPI_E_ATTACHMENT_NOT_FOUND:szmsg="A file attachment couldn't be found";break;
   case MAPI_E_ATTACHMENT_OPEN_FAILURE :szmsg="A file attachment couldn't be opened";break;
   case MAPI_E_BAD_RECIPTYPE :szmsg="Coding error - recipient is not specified correctly";break; 
   case MAPI_E_INSUFFICIENT_MEMORY :szmsg="Out of memory";break; 
   case MAPI_E_INVALID_RECIPS :szmsg="One or more recipient addresses invalid or not resolved ";break; 
   case MAPI_E_LOGIN_FAILURE :szmsg="Not logged on ";break; 
   case MAPI_E_TEXT_TOO_LARGE :szmsg="E-mail text is too large to send";break; 
   case MAPI_E_TOO_MANY_FILES :szmsg="E-mail text has too many file attachments";break; 
   case MAPI_E_UNKNOWN_RECIPIENT :szmsg="Recipient didn't appear in the address list ";break; 
   case MAPI_E_USER_ABORT :szmsg="Cancelled by user ";break; 
   default:
   case MAPI_E_FAILURE :szmsg="An unspecified error occurred ";break; 
   case SUCCESS_SUCCESS :szmsg="EMailMessage prepared for posting successfully - check your e-mail client to see if it has been sent";break; 
   }
   if(uret!=SUCCESS_SUCCESS)
   {
    char szCaption[ONE_K];
    char *szMsg=(char *)malloc(ONE_K+strlen(EMailMessage.lpszSubject)+strlen(recip.lpszName)+strlen(recip.lpszAddress));
    sprintf(szCaption,"Send E-mail (%s)",szAppName);
    if(szMsg)
    {
     sprintf(szMsg,"Message with subject \"%s\"\r\n\r\n"
                     "Addressed to: %s - \"%s\"\r\n\r\n"
                     "%s"
                     ,EMailMessage.lpszSubject
                     ,recip.lpszName
                     ,recip.lpszAddress
                     ,szmsg
                     );
     MessageBox(ghwndFocus,szMsg,szCaption
                   ,uret==SUCCESS_SUCCESS?MB_OK:MB_ICONEXCLAMATION
                   );
     free(szMsg);
    }
   }
  }
  FreeLibrary(MapiLib); //decrement reference count
  FREE_IF_NON_ZERO(EMailMessage.lpszSubject);
  FREE_IF_NON_ZERO(EMailMessage.lpszNoteText);
  FREE_IF_NON_ZERO(EMailMessage.lpszDateReceived);
  FREE_IF_NON_ZERO(recip.lpszName);            
  FREE_IF_NON_ZERO(recip.lpszAddress);;
  FREE_IF_NON_ZERO(originator.lpszName);;              
  FREE_IF_NON_ZERO(lpEmailFiles[0].lpszPathName);
  FREE_IF_NON_ZERO(lpEmailFiles[1].lpszPathName);
  FREE_IF_NON_ZERO(lpEmailFiles[2].lpszPathName);
 }
 DO_EXIT_TRY_BLOCK_PROC("DoSendEmail")
 return;
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
 char szPFile[MAX_PATH];
#ifdef UNICODE
 GetShortPathName(szWorkingDirectory,szShortWD,MAX_PATH);
#else
 strcpy(szShortWD,szWorkingDirectory);
#endif
 MakePathFile(szPFile,szShortWD,"BugReport.txt");
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
  FILE *fp=fopen(szPFile,"w");
  if(fp)
  {
   if(is_dlg_proc)
   fprintf(fp,"Work log version uploaded %s\n"
       "Operating System %s\n\n"
       "Exception occurred at %x:\n\n%s (in %s)\n\n"
							"message %d, wParam lw %d hw %d, lParam lw %d, hw %d\n\n"
       ,szVersionDate,szFindOS()
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
    SendEmailMessage(szSupport,"support@your_company_address.com","Bug Report"
							,"Please send this message now, after adding any extra details, or save it - if you close this message without saving it, then it usually gets discarded.\n\n"
				   "Please add any observations that may help to locate the bug,\r\n\r\n"
					  "Examples of the sort of thing that is useful to know are: that it happened when you pressed "
							"a particular button, opened a particular file (attach any relevant file to this e-mail), etc. All this makes it easier to locate it.\n\n"
       "Expect to hear from me soon. Most bugs get fixed within a day or two.\n\n"
       "Thanks!\n\n"
       ,szPFile
							);
   }
   t_exception_msg=clock();
  }
 }
 in_this=0;
}
