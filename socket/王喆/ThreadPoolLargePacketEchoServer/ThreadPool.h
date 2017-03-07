//Download by http://www.NewXing.com
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef THREAD_POOL_LARGE_PACKET_ECHO_SERVER_THREAD_POOL_INCLUDED__
#define THREAD_POOL_LARGE_PACKET_ECHO_SERVER_THREAD_POOL_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: ThreadPool.h $
// Version        : $Revision: 4 $
// Function       : 
//
// Author         : $Author: Len $
// Date           : $Date: 10/08/02 13:55 $
//
// Notes          : 
//
// Modifications  :
//
// $Log: /Web Articles/SocketServers/ThreadPoolLargePacketEchoServer/ThreadPoolLargePacketEchoServer/ThreadPool.h $
// 
// 4     10/08/02 13:55 Len
// Typo.
// 
// 3     9/08/02 18:22 Len
// Code cleaning and use of enums for dispatch.
// 
// 2     15/07/02 9:54 Len
// Demonstrate the need for read and write sequencing at various levels.
// 
// 1     27/06/02 17:13 Len
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
// Private copy constructor
//lint -esym(1704, CThreadPool::CThreadPool) 
//
///////////////////////////////////////////////////////////////////////////////

#include "JetByteTools\Win32Tools\SocketServer.h"
#include "JetByteTools\Win32Tools\ThreadPool.h"

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools
{
   namespace Win32
   {
      class CEvent;
   }
}

///////////////////////////////////////////////////////////////////////////////
// CThreadPool
///////////////////////////////////////////////////////////////////////////////

class CThreadPool : public JetByteTools::Win32::CThreadPool
{
   public:

      CThreadPool(
         size_t initialThreads,
         size_t minThreads,
         size_t maxThreads,
         size_t maxDormantThreads,
         size_t poolMaintPeriod,
         size_t dispatchTimeout,
         size_t maxThreadsDispatchTimeout,
         size_t m_numReads,
         bool usingSequenceNumbers,
         bool useMultipleWrites);

      void DispatchConnectionEstablished(
         JetByteTools::Win32::CSocketServer::Socket *pSocket,
         JetByteTools::Win32::CIOBuffer *pAddress);

      void DispatchConnectionClosing(
         JetByteTools::Win32::CSocketServer::Socket *pSocket);

      void DispatchConnectionClosed(
         JetByteTools::Win32::CSocketServer::Socket *pSocket);

      void DispatchReadCompleted(
         JetByteTools::Win32::CSocketServer::Socket *pSocket,
         JetByteTools::Win32::CIOBuffer *pBuffer);

      enum DispatchEvents
      {
         ConnectionEstablished,
         ConnectionClosing,
         ConnectionClosed,
         ReadCompleted
      };

   private :

      void DoDispatch(
         JetByteTools::Win32::CSocketServer::Socket *pSocket,
         JetByteTools::Win32::CIOBuffer *pBuffer,
         DispatchEvents event);

      virtual void OnThreadStarted();
      virtual void OnThreadInitialised();
      virtual void OnProcessingStarted();
      virtual void OnReceivedMessage();
      virtual void OnProcessingStopped();
      virtual void OnThreadStopped();

      virtual JetByteTools::Win32::CThreadPool::WorkerThread *CreateWorkerThread(
         JetByteTools::Win32::CIOCompletionPort &iocp,
         JetByteTools::Win32::CEvent &messageReceivedEvent,
         JetByteTools::Win32::CThreadPool &pool);

      const size_t m_numReads;

      const bool m_usingSequenceNumbers;

      const bool m_useMultipleWrites;
   
      // No copies do not implement
      CThreadPool(const CThreadPool &rhs);
      CThreadPool &operator=(const CThreadPool &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -restore
//
///////////////////////////////////////////////////////////////////////////////

#endif // THREAD_POOL_LARGE_PACKET_ECHO_SERVER_THREAD_POOL_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
