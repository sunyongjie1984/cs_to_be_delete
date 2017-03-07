//Download by http://www.NewXing.com
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: SocketAddress.cpp $
// Version        : $Revision: 2 $
// Function       :
//
// Author         : $Author: Len $
// Date           : $Date: 29/05/02 13:46 $
//
// Notes          : 
//
// Modifications  :
//
// $Log: /Web Articles/SocketServers/SimpleProtocolServer2/JetByteTools/Win32Tools/SocketAddress.cpp $
// 
// 2     29/05/02 13:46 Len
// Lint issues.
// 
// 1     21/05/02 11:35 Len
// 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2002 JetByte Limited.
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

#include "SocketAddress.h"
#include "Utils.h"

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//
// Member not defined
//lint -esym(1526, CSocketAddress::CSocketAddress)
//lint -esym(1526, CSocketAddress::operator=)
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static _tstring DeblockSockAddr(
   const sockaddr *pSockAddr);

///////////////////////////////////////////////////////////////////////////////
// CSocketAddress
///////////////////////////////////////////////////////////////////////////////

CSocketAddress::CSocketAddress(
   const sockaddr *pSockAddr)
   : m_address(DeblockSockAddr(pSockAddr))
{
   
}

_tstring CSocketAddress::GetAsString() const
{
   return m_address;
}
  
///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static _tstring DeblockSockAddr(
   const sockaddr *pSockAddr)
{
   USES_CONVERSION;

   if (pSockAddr->sa_family != AF_INET)
   {
      return _T("CSocketAddress() - TODO - we only handle AF_INET address at present");
   }

   const sockaddr_in *pSockAddrIn = reinterpret_cast<const sockaddr_in *>(pSockAddr);

   //lint -e40 Undeclared identifier inet_ntoa (wierd! it's in winsock2.h)
   //lint -e64 Type mismatch, just due to the above problem
   _tstring address(A2T(::inet_ntoa(pSockAddrIn->sin_addr)));
   
   return address + _T(":") + ToString(pSockAddrIn->sin_port);
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
