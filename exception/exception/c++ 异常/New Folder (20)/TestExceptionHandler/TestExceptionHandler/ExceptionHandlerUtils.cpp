/* Copyright (c) Robert Walker, support@tunesmithy.co.uk
 * Free source. Do what you wish with it - treat it as you would
 * example code in a book on c programming.
 */ 

// Note that this is coded for builds with UNICODE undefined.

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <mapi.h>
#include "exceptionhandler.h"
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
HINSTANCE MapiLib;
MapiMessage EMailMessage;
char do_ok_email_msg;
MapiRecipDesc recip,originator;
MapiFileDesc lpEmailFiles[MAX_EMAIL_FILES];

void DoMAPISendEmail(LHANDLE lhSession,         
  ULONG ulUIParam,           
  lpMapiMessage lpMessage,   
  FLAGS flFlags)           
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
  LPMAPISENDMAIL pMAPISendMail = (LPMAPISENDMAIL)GetProcAddress(MapiLib, "MAPISendMail");
  if(NULL == pMAPISendMail)
   MessageBox(ghwndFocus,"The MAPI library MAPI32.DLL loaded but seems to be corrupt? Couldn't find MAPISendMail function in it","Send e-mail",MB_ICONEXCLAMATION);
  else
  {
   char *szmsg="An unspecified error occurred";
   // uret=lpfnSendDocuments(0,";","L:\\e-cards\\blue_flower.jpg;L:\\e-cards\\r_familiar_territory.mid",NULL,NULL);
  	DO_ENTER_TRY_BLOCK
   uret=pMAPISendMail(lhSession, ulUIParam, lpMessage,flFlags , 0 );//|MAPI_DIALOG
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
 }
 DO_EXIT_TRY_BLOCK_PROC("DoMapiSendEmail")
 return;
}

void SendEmailMessage(char *szRecipientName,char *szRecipientEmailAddress
                     ,char *szSubject
                     ,char *szEMailMessageText
                     ,char *szPFileAttachment
                     )
{
 MapiMessage EMailMessage;
 MapiRecipDesc recip;
 MapiFileDesc lpEmailFiles[MAX_EMAIL_FILES];
 // adapted from c++ code at http://mlarchive.ima.com/mapi-l/1999/0603.html
 memset(&recip, 0, sizeof(recip));
 recip.ulRecipClass = MAPI_TO;
 recip.lpszName=szRecipientName;              
 recip.lpszAddress=szRecipientEmailAddress;
 // prepare the message -----------------------------------------------------
 memset(&EMailMessage, 0, sizeof(EMailMessage));
 EMailMessage.nRecipCount=szRecipientEmailAddress[0]=='\0'?0:1;
 EMailMessage.lpRecips = &recip;
 EMailMessage.lpszSubject=szSubject;
 EMailMessage.lpszNoteText=szEMailMessageText;
 EMailMessage.nFileCount=1;
 EMailMessage.lpFiles=lpEmailFiles;
 memset(&lpEmailFiles, 0, MAX_EMAIL_FILES*sizeof(MapiFileDesc));
 if(szPFileAttachment&&szPFileAttachment[0]!='\0')
 {
  lpEmailFiles[0].nPosition=(ULONG)-1;
  lpEmailFiles[0].lpszPathName=szPFileAttachment;
 }
 DoMAPISendEmail (0, (ULONG) ghwndFocus, &EMailMessage, MAPI_LOGON_UI|MAPI_DIALOG);//|MAPI_DIALOG
}