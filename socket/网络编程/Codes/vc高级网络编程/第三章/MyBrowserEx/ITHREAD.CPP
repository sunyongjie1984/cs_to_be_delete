#include "stdafx.h"
#include "IThread.h"


BOOL Succeeded(HANDLE h, LPCTSTR strFunctionName) ;

CInternetThread::CInternetThread()
   : m_hPostMsgWnd(NULL), 
      m_hSession(NULL), 
      m_buffer(NULL),
      m_dwAccessType(PRE_CONFIG_INTERNET_ACCESS)
{
}

void CInternetThread::ResetSession()
{
   TRACE0("重置会话\r\n") ;
   if (m_hSession != NULL)
   {
      VERIFY(::InternetCloseHandle(m_hSession)) ;
      m_hSession = NULL ;
   }   
}

CInternetThread::~CInternetThread()
{
   if (m_buffer) delete m_buffer ;
   ResetSession(); 
}

BOOL CInternetThread::Init(HWND hPostMsgWnd)
{
   ASSERT(hPostMsgWnd) ;
   m_hPostMsgWnd = hPostMsgWnd ;

   return TRUE ;
}

int CInternetThread::GetAccessTypeIndex() 
{
   int index = 0 ;
   switch (m_dwAccessType)
   {
   case PRE_CONFIG_INTERNET_ACCESS:
      index = 0 ;
      break ;
   case CERN_PROXY_INTERNET_ACCESS:
      index = 2 ;
      break ;
   case LOCAL_INTERNET_ACCESS:
      index = 3 ;
      break ;
   default:
      ASSERT(0) ;
   }
   return index ;
}

void CInternetThread::SetAccessTypeIndex(int index) 
{
   switch(index)
   {
   case 0:
      m_dwAccessType = PRE_CONFIG_INTERNET_ACCESS ;
      break;
   case 1:
      break;
   case 2:
      m_dwAccessType = CERN_PROXY_INTERNET_ACCESS ;
      break;
   case 3:
      m_dwAccessType = LOCAL_INTERNET_ACCESS ;
      break;
   default:
      ASSERT(0) ;
   }
   ResetSession() ;
}

void CInternetThread::GetPage(CString& rAddress)
{
   ASSERT(!rAddress.IsEmpty()) ;
   CString strTemp = rAddress.Mid(7) ;
   int i = strTemp.Find("/"); 
   if (i != -1)
   {
      m_strServer = strTemp.Left(i) ;
      m_strPath = strTemp.Mid(i) ;
      TRACE("Path = [%s]", (LPCTSTR)m_strPath) ; 
  }
   else
      m_strServer = strTemp ;

   TRACE("\t Server = [%s] \r\n", (LPCTSTR)m_strServer) ;   

   ASSERT(IsBufferEmpty()) ;
   AfxBeginThread(GetWebPageWorkerThread, this) ;
}

UINT CInternetThread::GetWebPageWorkerThread(LPVOID pvThread)
{
   TRACE0("GetWebPageWorkerThread\r\n") ;

   CInternetThread* pInternetThread = (CInternetThread*) pvThread ;
   if (pInternetThread == NULL 
       || pInternetThread->m_strServer.IsEmpty()
         || pInternetThread->m_hPostMsgWnd == NULL)
   {
      TRACE0("Internet相称不合法\r\n") ;
      return THREAD_BAD ;
   }

   return pInternetThread->_GetPageWorker() ;
}

UINT CInternetThread::_GetPageWorker()
{
    UINT uiResult = THREAD_BAD;

    if (m_hSession == NULL)
   {
      TRACE("Starting Session (Access = %i) (Proxy = %s)\r\n",
            GetAccessTypeIndex(),
            (LPCTSTR)m_strProxyServer) ;
      m_hSession = ::InternetOpen("MyBorwserEx",
                                  m_dwAccessType,
                                  m_strProxyServer,
                                  INTERNET_INVALID_PORT_NUMBER,
                                  0 ) ;

      if (!Succeeded(m_hSession, "InternetOpen"))
      {
         ::PostMessage(m_hPostMsgWnd,WM_READFILECOMPLETED, NULL, (LPARAM)THREAD_BAD) ;

         return THREAD_BAD;
      }
   }

   HINTERNET hConnect = ::InternetConnect(m_hSession,
                                          m_strServer,
                                          INTERNET_INVALID_PORT_NUMBER,
                                          "",
                                          "",
                                          INTERNET_SERVICE_HTTP,
                                          0,
                                          0) ;

                                          
   if (Succeeded(hConnect, "InternetConnect"))
   {

      HINTERNET hHttpFile = ::HttpOpenRequest(hConnect,
                                              "GET",
                                              m_strPath,
                                              HTTP_VERSION,
                                              NULL,
                                              0,
                                              INTERNET_FLAG_DONT_CACHE,
                                              0) ;

      if (Succeeded(hHttpFile, "HttpOpenRequest"))
      {
         
         BOOL bSendRequest = ::HttpSendRequest(hHttpFile, NULL, 0, 0, 0);
         
         if (Succeeded((HINTERNET)bSendRequest, "HttpSendRequest"))
         {
            char bufQuery[32] ;
            DWORD dwFileSize ;
            DWORD dwLengthBufQuery = sizeof (bufQuery);
            BOOL bQuery = ::HttpQueryInfo(hHttpFile,
                           HTTP_QUERY_CONTENT_LENGTH, 
                           bufQuery, 
                           &dwLengthBufQuery,
                           NULL) ;
            if (Succeeded((HINTERNET)bQuery, "HttpQueryInfo"))
            {
               TRACE("HttpQueryInfo文件尺寸为 %s.\r\n", bufQuery) ;
               dwFileSize = (DWORD)atol(bufQuery) ;
            }
            else
            {
               TRACE("\tQueryInfo执行失败,只得到5k.\r\n") ;
               dwFileSize = 5*1024 ;
            }

            ASSERT(m_buffer == NULL); 
            m_buffer = new char[dwFileSize+1] ;
            DWORD dwBytesRead ;
            BOOL bRead = ::InternetReadFile(hHttpFile,	
                                            m_buffer,	
                                            dwFileSize+1, 	
                                            &dwBytesRead);	
            if (Succeeded((HINTERNET)bRead, "InternetReadFile"))
            {
               TRACE("\t读入字节数为 %d\r\n", dwBytesRead) ;
               m_buffer[dwBytesRead] = 0 ;
               uiResult = THREAD_GOOD;
            } // InternetReadFile
         } // HttpSendRequest

         VERIFY(::InternetCloseHandle(hHttpFile)); 
      } // HttpOpenRequest

      VERIFY(::InternetCloseHandle(hConnect)) ;
   } // InternetConnect 

   ::PostMessage(m_hPostMsgWnd,WM_READFILECOMPLETED, NULL, (LPARAM)uiResult) ;

   return uiResult ;
}

BOOL Succeeded(HANDLE h, LPCTSTR strFunctionName)
{
   if (h == NULL)
   {
      DWORD dwError = GetLastError() ;
      TRACE("%s *** Error = %u***\r\n",strFunctionName, dwError) ;

      CString errString ;
      errString.Format("%s 返回错误 %u", strFunctionName, dwError) ;
      AfxMessageBox(errString, MB_ICONEXCLAMATION | MB_OK) ;
      return FALSE;
   }
   else
   {
      TRACE("%s\r\n", strFunctionName) ;
      return TRUE ;
   }

}
