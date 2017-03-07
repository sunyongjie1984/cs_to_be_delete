/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 1999,2000,2001 Christopher E. Cramer <cec@ee.duke.edu>
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

/* Snort TCP Stream Reconstruction Plugin
   by Christopher E. Cramer <cec@ee.duke.edu>
*/

/* $Id: spp_tcp_stream.h,v 1.5 2001/01/02 08:06:01 roesch Exp $ */

#include "snort.h"

#ifndef __SPP_TCP_STREAM_H__
#define __SPP_TCP_STREAM_H__

#define CLOSED       0
#define LISTEN       1
#define SYN_RCVD     2
#define SYN_SENT     3
#define ESTABLISHED  4
#define CLOSE_WAIT   5
#define LAST_ACK     6
#define FIN_WAIT_1   7
#define CLOSING      8
#define FIN_WAIT_2   9
#define TIME_WAIT   10

typedef struct _TcpStreamSession
{
    u_long sip,cip;  /* can be found in p->iph->ip_src.s_addr */
    u_int16_t sp, cp;
    int client_status, server_status;
    u_long c_first_seq;
    u_long s_first_seq;
    u_long c_fin_seq;
    u_long s_fin_seq;
    u_long c_last_acked;
    u_long s_last_acked;
    u_long s_last_byte;
    u_long c_last_byte;
    u_long c_buf_start;
    u_long s_buf_start;
    u_char *c_buf; /* this needn't be larger than the TCP window size + maxbytes */
    u_char c_buf_allocd; /* flag indicating that the client buf has been setup */
    u_long c_buf_siz;
    int c_inbuf;
    u_char *s_buf; /* this needn't be larger than the TCP window size + maxbytes */
    u_char s_buf_allocd; /* flag to indicate server buf is alloc'd */
    u_long s_buf_siz;
    int s_inbuf;
    struct _TcpStreamSession *next;
    u_long timestamp;
} TcpStreamSession;

typedef struct _TcpStreamData
{
    int ports[32];   /* 32 is kind of arbitrary */
    int num_entries;
    TcpStreamSession * heads[256];
    u_long timestamp;
    u_long prunetime;
    u_long maxbytes;
} TcpStreamData;

/* list of function prototypes for this preprocessor */
void SetupTcpStream();
void TcpStreamInit(u_char *);
void ParseTcpStreamArgs(char *);
void TcpStreamPacket(Packet *);
u_long TcpStreamTime();
TcpStreamSession * TcpStreamCheckSession(Packet *, int, int * );
void TcpStreamPruneSessions();
void TcpStreamCommit(TcpStreamSession *, int );
void TcpStreamPacketize(Packet *, u_char *, u_long , int);
#endif  /* __SPP_TCP_STREAM_H__ */
