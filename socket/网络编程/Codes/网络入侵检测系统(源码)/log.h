/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/* $Id: log.h,v 1.7 2001/01/02 08:06:00 roesch Exp $ */

/*  I N C L U D E S  **********************************************************/
#include "snort.h"

/*  D E F I N E S  ************************************************************/
#ifndef __LOG_H__
#define __LOG_H__

#if defined (SUNOS) || defined (SOLARIS) || defined (HPUX) || defined (IRIX) \
|| defined (AIX) || defined (OSF1)
    #define LOG_AUTHPRIV LOG_AUTH
#endif

#ifndef LOG_AUTHPRIV
    #define LOG_AUTHPRIV LOG_AUTH
#endif

#define FRAME_SIZE        66
#define C_OFFSET          49

#define DUMP              1
#define BOGUS             2
#define NON_IP            3
#define ARP               4
#define GENERIC_LOG	  5

/*  D A T A  S T R U C T U R E S  *********************************************/

void (*LogFunc)(Packet *, char *);
void (*AlertFunc)(Packet *, char *);

/*  P R O T O T Y P E S  ******************************************************/
int OpenLogFile(int,Packet*);
FILE *OpenAlertFile(char *);
void OpenAlertSock();
void PrintIPPkt(FILE *, int,Packet*);
void PrintNetData(FILE *, u_char *, const int);
void ClearDumpBuf();
void Print2ndHeader(FILE *, Packet *);
void PrintTrHeader(FILE *, Packet *);
void PrintEthHeader(FILE *, Packet *);
void PrintArpHeader(FILE *, Packet *);
void PrintIPHeader(FILE *, Packet *);
void PrintTCPHeader(FILE *, Packet *);
void PrintTcpOptions(FILE *, Packet *);
void PrintIpOptions(FILE *, Packet *);
void PrintICMPHeader(FILE *, Packet *);
void PrintUDPHeader(FILE *, Packet *);
void CreateTCPFlagString(Packet *, char *);
void LogAlertData();
void AlertMsg(Packet *, char *);
char *IcmpFileName(Packet *);

void InitBinLogFile();
void LogBin(Packet *, char *, void *);
void LogPkt(Packet *, char *, void *);
void LogArpPkt(Packet *);
void NoLog(Packet *, char *, void *);

void AlertFast(Packet *, char *, FILE *);
void AlertFull(Packet *, char *, FILE *);

void FastAlert(Packet *, char *, void *);
void FullAlert(Packet *, char *, void *);
void NoAlert(Packet *, char *, void *);
void UnixSockAlert(Packet *, char *, void *);
void SyslogAlert(Packet *, char *, void *);
#ifdef ENABLE_SMB_ALERTS
void SmbAlert(Packet *, char *, void *);
#endif


#endif /* __LOG_H__ */
