//Download by http://www.NewXing.com
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: SocketServer.cpp $
// Version        : $Revision: 7 $
// Function       : 
//
// Author         : $Author: Len $
// Date           : $Date: 12/08/02 11:41 $
//
// Notes          : 
//
// Modifications  :
//
// $Log: /Web Articles/SocketServers/ThreadPoolLargePacketEchoServer/ThreadPoolLargePacketEchoServer/SocketServer.cpp $
// 
// 7     12/08/02 11:41 Len
// Handle new connection reset and connection error events.
// 
// 6     9/08/02 18:22 Len
// Code cleaning. Lint issues and a more structured method of work item
// dispatch.
// 
// 5     9/08/02 16:25 Len
// Check for invalid packet size.
// 
// 4     15/07/02 9:54 Len
// Demonstrate the need for read and write sequencing at various levels.
// 
// 3     29/06/02 18:26 Len
// Changes due to the thread event changes and default worker thread
// implementation.  We now only have to derive from the socket server,
// rather than from socket server and worker thread and all notifications
// come via the socket server base class.
// 
// 2     28/06/02 16:37 Len
// Handle connection closing notifications.
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

#include "SocketServer.h"
#include "ThreadPool.h"

#include "JetByteTools\Win32Tools\Exception.h"
#include "JetByteTools\Win32Tools\Utils.h"

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//
// Member not defined
//lint -esym(1526, CSocketServer::CSocketServer)
//lint -esym(1526, CSocketServer::operator=)
//
// Default constructor implicitly called
//lint -esym(1926, CSocketServer::m_criticalSection)
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Using directives
///////////////////////////////////////////////////////////////////////////////

using JetByteTools::Win32::CIOCompletionPort;
using JetByteTools::Win32::CIOBuffer;
using JetByteTools::Win32::Output;
using JetByteTools::Win32::ToString;
using JetByteTools::Win32::_tstring;
using JetByteTools::Win32::CException;
using JetByteTools::Win32::CCriticalSection;
using JetByteTools::Win32::GetLastErrorMessage;

///////////////////////////////////////////////////////////////////////////////
// CSocketServer
///////////////////////////////////////////////////////////////////////////////

CSocketServer::CSocketServer(
   unsigned long addressToListenOn,
   unsigned short portToListenOn,
   size_t maxFreeSockets,
   size_t maxFreeBuffers,
   size_t bufferSize,
   CThreadPool &pool,
   size_t maxMessageSize,
   bool usingReadSequenceNumbers,
   bool usingSequenceNumbers,
   bool issueEarlyRead,
   size_t numThreads /* = 0 */)
   :  JetByteTools::Win32::CSocketServer(addressToListenOn, portToListenOn, maxFreeSockets, maxFreeBuffers, bufferSize, numThreads, usingSequenceNumbers, false),
      m_pool(pool),
      m_allocator(maxMessageSize, 10),
      m_maxMessageSize(maxMessageSize),
      m_usingSequenceNumbers(usingReadSequenceNumbers),
      m_issueEarlyRead(issueEarlyRead)
{

}

void CSocketServer::OnStartAcceptingConnections()
{
   Output(_T("OnStartAcceptingConnections"));
}

void CSocketServer::OnStopAcceptingConnections()
{
   Output(_T("OnStopAcceptingConnections"));
}
      
void CSocketServer::OnShutdownInitiated()
{
   Output(_T("OnShutdownInitiated"));
}
      
void CSocketServer::OnShutdownComplete()
{
   Output(_T("OnShutdownComplete"));
}

void CSocketServer::OnConnectionEstablished(
   Socket *pSocket,
   CIOBuffer *pAddress)
{
   Output(_T("OnConnectionEstablished"));

   if (0 != GetPerConnectionData(pSocket))
   {
      throw CException(_T("CSocketServer::OnConnectionEstablished()"), _T("Programming error - Socket's server data already contains data"));
   }

   CPerConnectionData *pPerConnectionData = new CPerConnectionData(m_criticalSection, m_allocator);

   SetPerConnectionData(pSocket, pPerConnectionData);

   m_pool.DispatchConnectionEstablished(pSocket, pAddress);
}

void CSocketServer::OnConnectionClientClose(
   Socket * /*pSocket*/)
{
   Output(_T("OnConnectionClientClose"));
}

void CSocketServer::OnConnectionReset(
   Socket * /*pSocket*/)
{
   Output(_T("OnConnectionReset"));
}

bool CSocketServer::OnConnectionClosing(
   Socket *pSocket)
{
   Output(_T("OnConnectionClosing"));

   m_pool.DispatchConnectionClosing(pSocket);

   return true;      // We'll handle the close on a worker thread 
}

void CSocketServer::OnConnectionClosed(
   Socket *pSocket)
{
   Output(_T("OnConnectionClosed"));

   CPerConnectionData *pPerConnectionData = GetPerConnectionData(pSocket);

   delete pPerConnectionData;

   SetServerDataPtr(pSocket, 0);

   m_pool.DispatchConnectionClosed(pSocket);
}

void CSocketServer::OnConnectionCreated()
{
   Output(_T("OnConnectionCreated"));
}

void CSocketServer::OnConnectionDestroyed()
{
   Output(_T("OnConnectionDestroyed"));
}

void CSocketServer::OnConnectionError(
   ConnectionErrorSource source,
   Socket *pSocket,
   CIOBuffer *pBuffer,
   DWORD lastError)
{
   const LPCTSTR errorSource = (source == ZeroByteReadError ? _T(" Zero Byte Read Error:") : (source == ReadError ? _T(" Read Error:") : _T(" Write Error:")));

   Output(_T("OnConnectionError - Socket = ") + ToString(pSocket) + _T(" Buffer = ") + ToString(pBuffer) + errorSource + GetLastErrorMessage(lastError));
}

void CSocketServer::OnError(
   const JetByteTools::Win32::_tstring &message)
{
   Output(_T("OnError - ") + message);
}

void CSocketServer::OnBufferCreated()
{
   Output(_T("OnBufferCreated"));
}

void CSocketServer::OnBufferAllocated()
{
   Output(_T("OnBufferAllocated"));
}

void CSocketServer::OnBufferReleased()
{
   Output(_T("OnBufferReleased"));
}

void CSocketServer::OnBufferDestroyed()
{
   Output(_T("OnBufferDestroyed"));
}

void CSocketServer::OnThreadCreated()
{
   Output(_T("OnThreadCreated"));
}

void CSocketServer::OnThreadBeginProcessing()
{
   Output(_T("OnThreadBeginProcessing"));
}

void CSocketServer::OnThreadEndProcessing()
{
   Output(_T("OnThreadEndProcessing"));
}

void CSocketServer::OnThreadDestroyed()
{
   Output(_T("OnThreadDestroyed"));
}

void CSocketServer::ReadCompleted(
   Socket *pSocket,
   CIOBuffer *pBuffer)
{
   try
   {
      if (m_issueEarlyRead)
      {
         pSocket->Read();
      }

      CPerConnectionData *pPerConnectionData = GetPerConnectionData(pSocket);

      pBuffer->AddRef();

      if (m_usingSequenceNumbers)
      {
         pBuffer = pPerConnectionData->m_outOfSequenceReads.GetNext(pBuffer);
      }

      while (pBuffer)
      {
         //Output(_T("Processing buffer: ") + ToString(pBuffer) + _T(": Seq:") + ToString(pBuffer->GetSequenceNumber()));

         if (!pPerConnectionData->Finished())
         {
            ProcessDataStream(pSocket, pBuffer);
         }

         pBuffer->Release();
   
         pBuffer = 0;

         if (m_usingSequenceNumbers)
         {
            pBuffer = pPerConnectionData->m_outOfSequenceReads.ProcessAndGetNext();
         }
      }

      if (!m_issueEarlyRead)
      {
         pSocket->Read();
      }
   }
   catch(const CException &e)
   {
      Output(_T("ReadCompleted - Exception - ") + e.GetWhere() + _T(" - ") + e.GetMessage());
      pSocket->Shutdown();
   }
   catch(...)
   {
      Output(_T("ReadCompleted - Unexpected exception"));
      pSocket->Shutdown();
   }
}

static size_t AddAtMost(
   CIOBuffer *pBufferOut,
   size_t atMost,
   const CIOBuffer *pBufferIn,
   size_t readOffset)
{
   const size_t available = pBufferIn->GetUsed() - readOffset;

   const size_t bytesToAdd = min(available, atMost);

   pBufferOut->AddData(pBufferIn->GetBuffer() + readOffset, bytesToAdd);

   return bytesToAdd;
}


void CSocketServer::ProcessDataStream(
   Socket *pSocket,
   const CIOBuffer *pBuffer)
{
   CPerConnectionData *pPerConnectionData = GetPerConnectionData(pSocket);
   
   size_t bufferReadOffset = 0;

   do
   {
      if (!pPerConnectionData->HasBuffer())
      {
         //Output(_T("New buffer"));
         
         pPerConnectionData->NewBuffer();
      
         // make sure that we store the message header, even if it's fragmented and we
         // cant actually process it all...

         size_t added = AddAtMost(
            pPerConnectionData->m_pTransferBuffer, 
            GetMinimumMessageSize(), 
            pBuffer, 
            bufferReadOffset);

         bufferReadOffset += added;
      }
      
      if (pPerConnectionData->m_messageSize == 0)
      {
         // Try and work out the message size.

         if (pPerConnectionData->m_pTransferBuffer->GetUsed() >= GetMinimumMessageSize())
         {
            const size_t messageSize = GetMessageSize(pPerConnectionData->m_pTransferBuffer);

			if (messageSize < GetMinimumMessageSize())
			{
				Output(_T("Invalid message size"));

				const std::string response("Invalid message size! Go away!\r\n");

				// Write this message and then shutdown the sending side of the socket.
            
				pSocket->Write(response.c_str(), response.length());
				pSocket->Shutdown();

				// We cant recover from this. We cant continue to process reads because we'd be out of sync.

				pPerConnectionData->Finished(true);

				break;
			}
			else if (messageSize <= m_maxMessageSize)
            {
               pPerConnectionData->m_messageSize = messageSize;

               Output(_T("Message size = ") + ToString(messageSize));
            }
            else
            {
               Output(_T("Too much data!"));

               const std::string response("Too much data! Go away!\r\n");

               // Write this message and then shutdown the sending side of the socket.
            
               pSocket->Write(response.c_str(), response.length());
               pSocket->Shutdown();

               // We cant recover from this. We cant continue to process reads because we'd be out of sync.

               pPerConnectionData->Finished(true);

               break;
            }
         }
         else
         {
            size_t added = AddAtMost(
               pPerConnectionData->m_pTransferBuffer, 
               GetMinimumMessageSize() - pPerConnectionData->m_pTransferBuffer->GetUsed(), 
               pBuffer, 
               bufferReadOffset);

            bufferReadOffset += added;
         }
      }

      if (pPerConnectionData->m_messageSize != 0)
      {
         // we have a transfer buffer
         // we know how big the message is
         // we know how much of it we already have

         const size_t bytesRequired = pPerConnectionData->m_messageSize - pPerConnectionData->m_pTransferBuffer->GetUsed();

         size_t added = AddAtMost(
            pPerConnectionData->m_pTransferBuffer, 
            bytesRequired,
            pBuffer, 
            bufferReadOffset);

         bufferReadOffset += added;
      }

      if (pPerConnectionData->m_messageSize != 0 && pPerConnectionData->m_messageSize == pPerConnectionData->m_pTransferBuffer->GetUsed())
      {
         // We have a complete message in our transfer buffer.

         //Output(_T("We have a complete message"));

         CIOBuffer *pTransferBuffer = pPerConnectionData->RemoveTransferBuffer();

         if (pTransferBuffer)
         {
            ProcessCommand(pSocket, pTransferBuffer);

            pTransferBuffer->Release();
         }
      }
   }
   while (bufferReadOffset < pBuffer->GetUsed());
}

size_t CSocketServer::GetMinimumMessageSize() const
{
   // The smallest possible packet is 2 bytes for the message length with a 0 length message.
   return 2;   
}

size_t CSocketServer::GetMessageSize(
   const CIOBuffer *pBuffer) const
{
   const BYTE *pData = pBuffer->GetBuffer();

   return *pData + (*(pData + 1) * 256);
}

void CSocketServer::ProcessCommand(
   Socket *pSocket,
   CIOBuffer *pBuffer)
{
   m_pool.DispatchReadCompleted(pSocket, pBuffer);
}

void CSocketServer::SetPerConnectionData(
   Socket *pSocket, 
   CPerConnectionData *pData)
{
   SetServerDataPtr(pSocket, pData);
}

CSocketServer::CPerConnectionData *CSocketServer::GetPerConnectionData(
   const Socket *pSocket)
{
   return (CPerConnectionData*)GetServerDataPtr(pSocket);
}

CSocketServer::CPerConnectionData::CPerConnectionData(
   CCriticalSection &criticalSection,
   CIOBuffer::Allocator &allocator)
   :  m_messageSize(0),
      m_pTransferBuffer(0),
      m_outOfSequenceReads(criticalSection),
      m_transferSequenceNumber(0),
      m_finished(0),
      m_allocator(allocator)
{
}

CSocketServer::CPerConnectionData::~CPerConnectionData()
{
   try
   {
      if (m_pTransferBuffer)
      {
         m_pTransferBuffer->Release();
         m_pTransferBuffer = 0;
      }
   }
   catch(...)
   {
   }
}

void CSocketServer::CPerConnectionData::NewBuffer()
{
   if (m_pTransferBuffer)
   {
      throw "TODO";
   }

   m_messageSize = 0;
   m_pTransferBuffer = m_allocator.Allocate();

   m_pTransferBuffer->SetSequenceNumber(::InterlockedExchangeAdd(&m_transferSequenceNumber, 1));
}

void CSocketServer::CPerConnectionData::AddData(
   const BYTE *pData,
   size_t dataLength)
{
   if (!m_pTransferBuffer)
   {
      throw "TODO";
   }

   m_pTransferBuffer->AddData(pData, dataLength);
}
/*
size_t CSocketServer::CPerConnectionData::GetMessageSize()
{
   if (m_messageSize == 0)
   {
      if (m_pTransferBuffer && m_pTransferBuffer->GetUsed() >= GetMinimumMessageSize())
      {
         m_messageSize = GetMessageSize(pPerConnectionData->pTransferBuffer);
      }
   }

   return m_messageSize;
}
*/

bool CSocketServer::CPerConnectionData::HasBuffer() const
{
   return (0 != m_pTransferBuffer);
}

CIOBuffer *CSocketServer::CPerConnectionData::RemoveTransferBuffer()
{
   CIOBuffer *pBuffer = m_pTransferBuffer;
   
   m_pTransferBuffer = 0;
   m_messageSize = 0;

   return pBuffer;
}


bool CSocketServer::CPerConnectionData::Finished()
{
   return (1 == ::InterlockedExchange(&m_finished, m_finished));
}

void CSocketServer::CPerConnectionData::Finished(bool finished)
{
   //lint -e{534} Ignoring return value of function 
   ::InterlockedExchange(&m_finished, finished ? 1 : 0);
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
