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

/* $Id: spo_log_tcpdump.h,v 1.3 2001/01/02 08:06:01 roesch Exp $ */

/* This file gets included in plugbase.h when it is integrated into the rest 
 * of the program.  Sometime in The Future, I'll whip up a bad ass Perl script
 * to handle automatically loading all the required info into the plugbase.*
 * files.
 */
#include "snort.h"

#ifndef __SPO_LOG_TCPDUMP_H__
#define __SPO_LOG_TCPDUMP_H__

typedef struct _LogTcpdumpData
{
    char *filename;
    int log_written;
    pcap_dumper_t *dumpd;

} LogTcpdumpData;

/* list of function prototypes for this preprocessor */
void SetupLogTcpdump();
void LogTcpdumpInit(u_char *);
LogTcpdumpData *ParseTcpdumpArgs(char *);
void LogTcpdump(Packet *, char *, void *);
void TcpdumpInitLogFile(LogTcpdumpData *);
void SpoLogTcpdumpCleanExitFunc(int, void *);
void SpoLogTcpdumpRestartFunc(int, void *);

#endif  /* __SPO_SYSLOG_H__ */
