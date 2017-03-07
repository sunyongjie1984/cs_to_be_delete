//Download by http://www.NewXing.com
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: ThreadPool.cpp $
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
// $Log: /Web Articles/SocketServers/ThreadPoolLargePacketEchoServer/ThreadPoolLargePacketEchoServer/ThreadPool.cpp $
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

#include "ThreadPool.h"
#include "ThreadPoolWorkerThread.h"

#include "JetByteTools\Win32Tools\Utils.h"
#include "JetByteTools\Win32Tools\Exception.h"

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//
// Member not defined
//lint -esym(1526, CThreadPool::CThreadPool)
//lint -esym(1526, CThreadPool::operator=)
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Using directives
///////////////////////////////////////////////////////////////////////////////

using JetByteTools::Win32::CIOCompletionPort;
using JetByteTools::Win32::CEvent;
using JetByteTools::Win32::Output;
using JetByteTools::Win32::CSocketServer;
using JetByteTools::Win32::CIOBuffer;
using JetByteTools::Win32::CException;

///////////////////////////////////////////////////////////////////////////////
// CThreadPool
///////////////////////////////////////////////////////////////////////////////

CThreadPool::CThreadPool(
   size_t initialThreads,
   size_t minThreads,
   size_t maxThreads,
   size_t maxDormantThreads,
   size_t poolMaintPeriod,
   size_t dispatchTimeout,
   size_t maxThreadsDispatchTimeout,
   size_t numReads,
   bool usingSequenceNumbers,
   bool useMultipleWrites)
   :  JetByteTools::Win32::CThreadPool(
         initialThreads, 
         minThreads, 
         maxThreads, 
         maxDormantThreads, 
         poolMaintPeriod, 
         dispatchTimeout,
         maxThreadsDispatchTimeout),
      m_numReads(numReads),
      m_usingSequenceNumbers(usingSequenceNumbers),
      m_useMultipleWrites(useMultipleWrites)
{
}

JetByteTools::Win32::CThreadPool::WorkerThread *CThreadPool::CreateWorkerThread(
   CIOCompletionPort &iocp,
   CEvent &messageReceivedEvent,
   JetByteTools::Win32::CThreadPool &pool)
{
   return new CThreadPoolWorkerThread(
      iocp, 
      messageReceivedEvent, 
      pool,
      m_numReads,
      m_usingSequenceNumbers,
      m_useMultipleWrites);
}

void CThreadPool::OnThreadStarted()
{
   Output(_T("OnThreadStarted"));
}

void CThreadPool::OnThreadInitialised()
{
   Output(_T("OnThreadInitialised"));
}

void CThreadPool::OnProcessingStarted()
{
   Output(_T("OnProcessingStarted"));
}

void CThreadPool::OnReceivedMessage()
{
   Output(_T("OnReceivedMessage"));
}

void CThreadPool::OnProcessingStopped()
{
  Output(_T("OnProcessingStopped"));
}

void CThreadPool::OnThreadStopped()
{
   Output(_T("OnThreadStopped"));
}

void CThreadPool::DispatchConnectionEstablished(
   JetByteTools::Win32::CSocketServer::Socket *pSocket,
   JetByteTools::Win32::CIOBuffer *pAddress)
{
   DoDispatch(pSocket, pAddress, ConnectionEstablished);
}

void CThreadPool::DispatchConnectionClosing(
   JetByteTools::Win32::CSocketServer::Socket *pSocket)
{
   DoDispatch(pSocket, 0, ConnectionClosing);
}

void CThreadPool::DispatchConnectionClosed(
   JetByteTools::Win32::CSocketServer::Socket *pSocket)
{
   DoDispatch(pSocket, 0, ConnectionClosed);
}

void CThreadPool::DispatchReadCompleted(
   JetByteTools::Win32::CSocketServer::Socket *pSocket,
   JetByteTools::Win32::CIOBuffer *pBuffer)
{
   DoDispatch(pSocket, pBuffer, ReadCompleted);
}

void CThreadPool::DoDispatch(
   CSocketServer::Socket *pSocket,
   CIOBuffer *pBuffer,
   DispatchEvents event)
{
   pSocket->AddRef();
   
   if (pBuffer)
   {
      pBuffer->AddRef();
   }
   else if (event != ConnectionClosed && event != ConnectionClosing)
   {
      throw CException(_T("CThreadPool::DoDispatch()"), _T("Unexpected: Only the ConnectionClosed and ConnectionClosing events can have a null pBuffer"));
   }

   Dispatch(
      reinterpret_cast<ULONG_PTR>(pSocket), 
      event,
      pBuffer);
}

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -restore
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
