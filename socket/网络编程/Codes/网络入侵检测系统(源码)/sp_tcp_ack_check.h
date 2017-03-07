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

/* $Id: sp_tcp_ack_check.h,v 1.2 2001/01/02 08:06:01 roesch Exp $ */
#ifndef __SP_TCP_ACK_CHECK_H__
#define __SP_TCP_ACK_CHECK_H__

#include "snort.h"

#define PLUGIN_TCP_ACK_CHECK  9

typedef struct _TcpAckCheckData
{
    u_long tcp_ack;

} TcpAckCheckData;

void TcpAckCheckInit(char *, OptTreeNode *, int);
void SetupTcpAckCheck();
void ParseTcpAck(char *, OptTreeNode *);
int CheckTcpAckEq(Packet *, struct _OptTreeNode *, OptFpList *);

#endif  /* __SP_TCP_ACK_CHECK_H__ */
