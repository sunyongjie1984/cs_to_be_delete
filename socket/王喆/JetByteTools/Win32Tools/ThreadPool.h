//Download by http://www.NewXing.com
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef JETBYTE_TOOLS_WIN32_THREAD_POOL_INCLUDED__
#define JETBYTE_TOOLS_WIN32_THREAD_POOL_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: ThreadPool.h $
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
// $Log: /Web Articles/SocketServers/FilteringThreadPoolPacketEchoServer/JetByteTools/Win32Tools/ThreadPool.h $
// 
// 7     10/08/02 13:57 Len
// Typo.
// 
// 6     6/08/02 12:55 Len
// Dispatch is now protected.
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

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//
// No default constructor
//lint -esym(1712, CThreadPool)
//lint -esym(1712, WorkerThread)
//
// Member is a reference
//lint -esym(1725, WorkerThread::m_messageReceivedEvent)
//lint -esym(1725, WorkerThread::m_iocp)
//lint -esym(1725, WorkerThread::m_pool)
//
///////////////////////////////////////////////////////////////////////////////

#include "IOCompletionPort.h"
#include "Thread.h"
#include "ManualResetEvent.h"
#include "AutoResetEvent.h"
#include "CriticalSection.h"

#include <deque>

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// CThreadPool
///////////////////////////////////////////////////////////////////////////////

class CThreadPool : private CThread
{
   public :

      class WorkerThread;

      friend class WorkerThread;

      CThreadPool(
         size_t initialThreads,
         size_t minThreads,
         size_t maxThreads,
         size_t maxDormantThreads,
         size_t poolMaintPeriod,
         size_t dispatchTimeout,
         size_t maxThreadsDispatchTimeout);

      virtual ~CThreadPool();

      using CThread::Start;

      void InitiateShutdown();

      void WaitForShutdownToComplete(
         size_t timeout = INFINITE,
         bool forceTermination = false);

   protected :

      void Dispatch(
         ULONG_PTR completionKey, 
         DWORD dwNumBytes = 0, 
         OVERLAPPED *pOverlapped = 0);

   private :

      void ThreadStarted();

      virtual void OnThreadStarted() {};

      void ThreadInitialised();

      virtual void OnThreadInitialised() {};
      
      void ProcessingStarted();
      
      virtual void OnProcessingStarted() {};

      void ReceivedMessage();

      virtual void OnReceivedMessage() {};
      
      void ProcessingStopped();
     
      virtual void OnProcessingStopped() {};
      
      void ThreadStopped(
         WorkerThread *pThread);
      
      virtual void OnThreadStopped() {};

      int Run();

      void StartWorkerThread();

      virtual WorkerThread *CreateWorkerThread(
         CIOCompletionPort &iocp,
         CEvent &messageReceivedEvent,
         CThreadPool &pool) = 0;

      void HandleDormantThreads();
      
      void StopWorkerThreads(
         size_t numThreads);

      void TerminateWorkerThreads();

      void AddThreadToList(
         WorkerThread *pThread);
      
      void RemoveThreadFromList(
         WorkerThread *pThread);
   
      void HandleDispatch(
         ULONG_PTR completionKey, 
         DWORD dwNumBytes, 
         OVERLAPPED *pOverlapped);

      CManualResetEvent m_shutdownEvent;
      CManualResetEvent m_dispatchCompleteEvent;
      CManualResetEvent m_poolEmptyEvent;

      CCriticalSection m_criticalSection;

      CIOCompletionPort m_workPort;
      CIOCompletionPort m_dispatchPort;

      long m_activeThreads;
      long m_initialisedThreads;
      long m_processingThreads;

      const size_t m_initialThreads;
      const size_t m_minThreads;
      const size_t m_maxThreads;
      const size_t m_maxDormantThreads;

      WorkerThread *m_pHead;

      const size_t m_poolMaintPeriod;
      const size_t m_dispatchTimeout;
      const size_t m_maxThreadsDispatchTimeout;
};

///////////////////////////////////////////////////////////////////////////////
// CThreadPool::WorkerThread
///////////////////////////////////////////////////////////////////////////////

class CThreadPool::WorkerThread : public CThread
{
   friend class CThreadPool;

   protected :
   
      WorkerThread(
         CIOCompletionPort &iocp,
         CEvent &messageReceivedEvent,
         CThreadPool &pool);
      
      virtual ~WorkerThread();

   private :

      virtual bool Initialise();

      virtual void Process(
         ULONG_PTR completionKey,
         DWORD dwNumBytes,
         OVERLAPPED *pOverlapped) = 0;

      virtual void Shutdown();

      virtual int Run();

      CEvent &m_messageReceivedEvent;

      CIOCompletionPort &m_iocp;

      CThreadPool &m_pool;

      WorkerThread *m_pNext;
      WorkerThread *m_pPrev;
};

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

#endif // JETBYTE_TOOLS_WIN32_THREAD_POOL_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
