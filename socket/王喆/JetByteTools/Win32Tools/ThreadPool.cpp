//Download by http://www.NewXing.com
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: ThreadPool.cpp $
// Version        : $Revision: 7 $
// Function       : 
//
// Author         : $Author: Len $
// Date           : $Date: 10/08/02 13:57 $
//
// Notes          : 
//
// Modifications  :
//
// $Log: /Web Articles/SocketServers/FilteringThreadPoolPacketEchoServer/JetByteTools/Win32Tools/ThreadPool.cpp $
// 
// 7     10/08/02 13:57 Len
// Typo.
// 
// 6     6/08/02 11:50 Len
// All calls to Output() are now wrapped in a DEBUG_ONLY() macro so they
// vanish completely from release builds.
// 
// 5     20/05/02 23:17 Len
// Updated copyright and disclaimers.
// 
// 4     14/05/02 14:38 Len
// Expose CThread::Start() using a using declaration rather than a
// forwarding function.
// 
// 3     14/05/02 13:51 Len
// We now explicitly start the thread pool rather than allowing it to
// start itself in the constructor. There was a race condition over the
// completion of construction of derived classes and the first access to
// the pure virtual functions.
// 
// 2     10/05/02 19:25 Len
// Lint options and code cleaning.
// 
// 1     9/05/02 18:47 Len
// 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 1997 - 2002 JetByte Limited.
//
// JetByte Limited grants you ("Licensee") a non-exclusive, royalty free, 
// licence to use, modify and redistribute this software in source and binary 
// code form, provided that i) this copyright notice and licence appear on all 
// copies of the software; and ii) Licensee does not utilize the software in a 
// manner which is disparaging to JetByte Limited.
//
// This software is provided "as is" without a warranty of any kind. All 
// express or implied conditions, representations and warranties, including
// any implied warranty of merchantability, fitness for a particular purpose
// or non-infringement, are hereby excluded. JetByte Limited and its licensors 
// shall not be liable for any damages suffered by licensee as a result of 
// using, modifying or distributing the software or its derivatives. In no
// event will JetByte Limited be liable for any lost revenue, profit or data,
// or for direct, indirect, special, consequential, incidental or punitive
// damages, however caused and regardless of the theory of liability, arising 
// out of the use of or inability to use software, even if JetByte Limited 
// has been advised of the possibility of such damages.
//
// This software is not designed or intended for use in on-line control of 
// aircraft, air traffic, aircraft navigation or aircraft communications; or in 
// the design, construction, operation or maintenance of any nuclear 
// facility. Licensee represents and warrants that it will not use or 
// redistribute the Software for such purposes. 
//
///////////////////////////////////////////////////////////////////////////////

#include "ThreadPool.h"
#include "Exception.h"
#include "Win32Exception.h"
#include "Utils.h"

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//
// Symbol did not appear in the constructor initialiser list 
//lint -esym(1928, CThread)
//lint -esym(1928, CUsesWinsock)
//
// Symbol's default constructor implicitly called
//lint -esym(1926, CThreadPool::m_shutdownEvent)
//lint -esym(1926, CThreadPool::m_poolEmptyEvent)
//lint -esym(1926, CThreadPool::m_criticalSection)
//lint -esym(1926, CThreadPool::m_dispatchCompleteEvent)
//
// Ignoring return value
//lint -esym(534, InterlockedIncrement)
//lint -esym(534, InterlockedDecrement)
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// CThreadPool
//////////////////////////////////////////////////////////////////////////////

CThreadPool::CThreadPool(
   size_t initialThreads,
   size_t minThreads,
   size_t maxThreads,
   size_t maxDormantThreads,
   size_t poolMaintPeriod,
   size_t dispatchTimeout,
   size_t maxThreadsDispatchTimeout)
   :  m_workPort(0),
      m_dispatchPort(0),
      m_activeThreads(0),
      m_initialisedThreads(0),
      m_processingThreads(0),
      m_initialThreads(initialThreads),
      m_minThreads(minThreads),
      m_maxThreads(maxThreads),
      m_maxDormantThreads(maxDormantThreads),
      m_pHead(0),
      m_poolMaintPeriod(poolMaintPeriod),
      m_dispatchTimeout(dispatchTimeout),
      m_maxThreadsDispatchTimeout(maxThreadsDispatchTimeout)
{
   m_poolEmptyEvent.Set();
}

CThreadPool::~CThreadPool()
{
   try
   {
      if (m_pHead)
      {
         DEBUG_ONLY(Output(_T("~CThreadPool() - Shutting down worker threads")));

         WaitForShutdownToComplete();
      }

      if (m_pHead)
      {
         DEBUG_ONLY(Output(_T("~CThreadPool() - Unexpected - thread pool still contains threads")));
      }

      m_pHead = 0;
   }
   catch(...)
   {
   }
}

void CThreadPool::Dispatch(
   ULONG_PTR completionKey, 
   DWORD dwNumBytes /*= 0*/, 
   OVERLAPPED *pOverlapped /*= 0*/) 
{
   if (completionKey == 0)
   {
      throw CException(_T("CThreadPool::Dispatch()"), _T("0 is an invalid value for completionKey"));
   }

   m_dispatchPort.PostStatus(completionKey, dwNumBytes, pOverlapped); 
}

void CThreadPool::InitiateShutdown()
{
   m_shutdownEvent.Set();
}

void CThreadPool::WaitForShutdownToComplete(
   size_t timeout /* = INFINITE */,
   bool forceTermination /* = false */)
{
   InitiateShutdown();

   if (!Wait(timeout) && forceTermination)
   {
      DEBUG_ONLY(Output(_T("Terminating worker threads")));

      TerminateWorkerThreads();
   }

   Wait();
}

int CThreadPool::Run()
{
   try
   {
      for (size_t i = 0; i < m_initialThreads; ++i)
      {
         StartWorkerThread();
      }

      DWORD lastMaintainance = GetTickCount();

      //lint -e{716} while(1)
      while (true)
      {
         if (m_shutdownEvent.Wait(0))
         {
            // time to shutdown...
            break;
         }

         ULONG_PTR completionKey;
         DWORD dwNumBytes;
         OVERLAPPED *pOverlapped;

         bool ok = m_dispatchPort.GetStatus(
            &completionKey, 
            &dwNumBytes, 
            &pOverlapped, 
            m_poolMaintPeriod);

         if (m_shutdownEvent.Wait(0))
         {
            // time to shutdown...
            break;
         }

         if (ok)
         {
            HandleDispatch(completionKey, dwNumBytes, pOverlapped);

            if (GetTickCount() - lastMaintainance >= m_poolMaintPeriod)
            {
               HandleDormantThreads();

               lastMaintainance = GetTickCount();
            }
         }
         else
         {
            DWORD lastError = ::GetLastError();

            if (lastError == WAIT_TIMEOUT)
            {
               HandleDormantThreads();
            }
            else
            {
               DEBUG_ONLY(Output(_T("Unexpected - ") + GetLastErrorMessage(lastError)));
            }
         }
      }

      StopWorkerThreads(m_activeThreads);

      m_poolEmptyEvent.Wait();
   }
   catch(const CException &e)
   {
      DEBUG_ONLY(Output(_T("CThreadPool::Run() - Exception: ") + e.GetWhere() + _T(" - ") + e.GetMessage()));
   }
   catch(...)
   {
      DEBUG_ONLY(Output(_T("CThreadPool::Run() - Unexpected exception")));
   }

   return 0;
}

void CThreadPool::HandleDispatch(
   ULONG_PTR completionKey, 
   DWORD dwNumBytes, 
   OVERLAPPED *pOverlapped) 
{
   HANDLE handlesToWaitFor[2];

   handlesToWaitFor[0] = m_dispatchCompleteEvent.GetEvent();
   handlesToWaitFor[1] = m_shutdownEvent.GetEvent();

   m_dispatchCompleteEvent.Reset();

   bool processed = false;
   
   m_workPort.PostStatus(completionKey, dwNumBytes, pOverlapped); 

   // wait for someone to toggle the 'got message' event?

   DWORD timeoutMillis = m_dispatchTimeout + (((size_t)m_processingThreads == m_maxThreads) ? m_maxThreadsDispatchTimeout : 0);

   bool threadStarted = false;

   while (!processed)
   {
      DWORD result = ::WaitForMultipleObjects(2, handlesToWaitFor, false, timeoutMillis);

      if (result == WAIT_OBJECT_0)
      {
         processed = true;
      }
      else if (result == WAIT_OBJECT_0 + 1)
      {
         // Shutdown request...
         break;
      }
      else if (result == WAIT_TIMEOUT)
      {
         if (!threadStarted && m_processingThreads == m_activeThreads && (size_t)m_activeThreads < m_maxThreads)
         {            
            StartWorkerThread();

            threadStarted = true;
         }
      }
      else
      {
         throw CWin32Exception(_T("CThreadPool::Dispatch() - WaitForMultipleObjects"), GetLastError());
      }
   }
}

void CThreadPool::HandleDormantThreads()
{
   if ((size_t)m_activeThreads > m_minThreads)
   {
      const size_t dormantThreads = m_activeThreads - m_processingThreads;

      if (dormantThreads > m_maxDormantThreads)
      {
         const size_t threadsToShutdown = (dormantThreads - m_maxDormantThreads) / 2 + 1;

         StopWorkerThreads(threadsToShutdown);
      }
   }
}

void CThreadPool::StopWorkerThreads(size_t numThreads)
{
   for (size_t i = 0; i < numThreads; ++i)
   {
      m_workPort.PostStatus(0);
   }
}

void CThreadPool::TerminateWorkerThreads()
{
   CCriticalSection::Owner lock(m_criticalSection);

   while (m_pHead)
   {
      DEBUG_ONLY(Output(_T("Terminating thread")));

      m_pHead->Terminate(0);

      ThreadStopped(m_pHead);       
      
      // The call above will remove the thread from the active list, so next time
      // around we'll have a different thread as m_pHead... 
   }
}

void CThreadPool::StartWorkerThread()
{
   //lint -e{1933} call to unqualified virtual function
   WorkerThread *pThread = CreateWorkerThread(
      m_workPort, 
      m_dispatchCompleteEvent, 
      *this);

   AddThreadToList(pThread);

   pThread->Start();
}

void CThreadPool::ThreadStarted()
{
   ::InterlockedIncrement(&m_activeThreads);

   //lint -e{1933} call to unqualified virtual function
   OnThreadStarted();
}

void CThreadPool::ThreadInitialised()
{
   ::InterlockedIncrement(&m_initialisedThreads);

   //lint -e{1933} call to unqualified virtual function
   OnThreadInitialised();
}

void CThreadPool::ProcessingStarted()
{
   ::InterlockedIncrement(&m_processingThreads);

   //lint -e{1933} call to unqualified virtual function
   OnProcessingStarted();
}

void CThreadPool::ReceivedMessage()
{
   //lint -e{1933} call to unqualified virtual function
   OnReceivedMessage();
}

void CThreadPool::ProcessingStopped()
{
   ::InterlockedDecrement(&m_processingThreads);

   //lint -e{1933} call to unqualified virtual function
   OnProcessingStopped();
}

void CThreadPool::ThreadStopped(WorkerThread *pThread)
{
   ::InterlockedDecrement(&m_activeThreads);
   ::InterlockedDecrement(&m_initialisedThreads);

   RemoveThreadFromList(pThread);

   //lint -e{1933} call to unqualified virtual function
   OnThreadStopped();
}

void CThreadPool::AddThreadToList(
   WorkerThread *pThread)
{
   CCriticalSection::Owner lock(m_criticalSection);

   if (!m_pHead)
   {
      m_pHead = pThread;

      m_poolEmptyEvent.Reset();
   }
   else
   {
      pThread->m_pNext = m_pHead;
      m_pHead->m_pPrev = pThread;
      
      m_pHead = pThread;
   }
}

void CThreadPool::RemoveThreadFromList(
   WorkerThread *pThread)
{
   if (!pThread)
   {
      // TODO: should never happen...

      return;
   }

   CCriticalSection::Owner lock(m_criticalSection);

   if (m_pHead == pThread)
   {
      m_pHead = pThread->m_pNext;
      
      if (pThread->m_pNext)
      {
         pThread->m_pNext->m_pPrev = 0;
      }
   }
   else
   {
      pThread->m_pPrev->m_pNext = pThread->m_pNext;

      if (pThread->m_pNext)
      {
         pThread->m_pNext->m_pPrev = pThread->m_pPrev;
      }
   }

   delete pThread;         // a slim chance we could delete a thread
                           // twice in thread termination situations...
                           // we could walk the list first to make sure it's
                           // actually present...
   if (!m_pHead)
   {
      m_poolEmptyEvent.Set();
   }
}

///////////////////////////////////////////////////////////////////////////////
// CThreadPool::WorkerThread
///////////////////////////////////////////////////////////////////////////////

CThreadPool::WorkerThread::WorkerThread(
   CIOCompletionPort &iocp,
   CEvent &messageReceivedEvent,
   CThreadPool &pool)
   :  m_messageReceivedEvent(messageReceivedEvent),
      m_iocp(iocp),
      m_pool(pool),
      m_pNext(0),
      m_pPrev(0)
{
}
      
CThreadPool::WorkerThread::~WorkerThread()
{
   m_pNext = 0;
   m_pPrev = 0;
}

bool CThreadPool::WorkerThread::Initialise()
{
   return true;
}

void CThreadPool::WorkerThread::Shutdown()
{
}
 
int CThreadPool::WorkerThread::Run()
{
   m_pool.ThreadStarted();

   try
   {
      //lint -e{1933} call to unqualified virtual function
      if (Initialise())
      {
         m_pool.ThreadInitialised();
      
         //lint -e{716} while(1)
         while (true)
         {
            ULONG_PTR completionKey;
            DWORD dwNumBytes;
            OVERLAPPED *pOverlapped;
      
            m_iocp.GetStatus(&completionKey, &dwNumBytes, &pOverlapped);

            m_messageReceivedEvent.Set();

            if (completionKey == 0)
            {
               break; // request to shutdown
            }
            else
            {
               try
               {
                  m_pool.ReceivedMessage();
                  m_pool.ProcessingStarted();
               
                  //lint -e{1933} call to unqualified virtual function
                  Process(completionKey, dwNumBytes, pOverlapped);
                  
                  m_pool.ProcessingStopped();
               }
               catch(const CException &e)
               {
                  DEBUG_ONLY(Output(_T("CThreadPool::WorkerThread::Run() - Exception: ") + e.GetWhere() + _T(" - ") + e.GetMessage()));
               }
               catch(...)
               {
                  DEBUG_ONLY(Output(_T("CThreadPool::WorkerThread::Run() - Unexpected exception")));
               }
            }
         }
         //lint -e{1933} call to unqualified virtual function
         Shutdown();
      }
   }
   catch(const CException &e)
   {
      DEBUG_ONLY(Output(_T("CThreadPool::WorkerThread::Run() - Exception: ") + e.GetWhere() + _T(" - ") + e.GetMessage()));
   }
   catch(...)
   {
      DEBUG_ONLY(Output(_T("CThreadPool::WorkerThread::Run() - Unexpected exception")));
   }

   m_pool.ThreadStopped(this);

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -restore
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// End of file...
///////////////////////////////////////////////////////////////////////////////
