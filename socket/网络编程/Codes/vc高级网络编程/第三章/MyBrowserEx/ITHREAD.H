#ifndef __InternetThread_h__
#define __InternetThread_h__
#include <wininet.h>

// GetWebPageWorkerThreadde的返回值
const UINT THREAD_GOOD = 0 ;
const UINT THREAD_BAD = 1 ;

// 当线程结束时发送的消息
#define WM_READFILECOMPLETED (WM_USER + 100)


// 管理从Internet中读出数据的工作线程
class CInternetThread
{
public:
   // Construction
   CInternetThread() ;
   ~CInternetThread() ;

   // 初始化函数
   BOOL Init(HWND hPostMsgWnd) ;

   // 在改变访问类型后，重新初始化Internet函数
   void ResetSession() ;

   // 管理容纳HTML数据的缓冲区
   void EmptyBuffer()
      { delete m_buffer ; m_buffer = NULL ; }
   BOOL IsBufferEmpty() 
      { return m_buffer == NULL;}
   char* GetBuffer()
      { return m_buffer ;}

   // 得到访问类型
   int GetAccessTypeIndex() ;
   void SetAccessTypeIndex(int index) ;

   // 得到代理服务器名
   CString& GetProxyServer() 
      {return m_strProxyServer; }
   void SetProxyServer(CString& strProxyServer) 
      { m_strProxyServer = strProxyServer; ResetSession() ;}

   // 得到请求的网页
   void GetPage(CString& rAddress) ;

private:
   // 得到工作线程
   static UINT GetWebPageWorkerThread(LPVOID pvThread) ;

   UINT _GetPageWorker() ;

   CString m_strServer ;
   CString m_strPath ;   
   DWORD m_dwAccessType ;
   char* m_buffer ;
   HINTERNET m_hSession ;
   HWND m_hPostMsgWnd ;
public:
	CString m_strProxyServer ;
};

UINT GetWebPageWorkerThread(LPVOID pvThreadData);

#endif 
