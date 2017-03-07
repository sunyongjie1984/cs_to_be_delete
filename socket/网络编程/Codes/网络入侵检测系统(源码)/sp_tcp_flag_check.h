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

/* $Id: sp_tcp_flag_check.h,v 1.2 2001/01/02 08:06:01 roesch Exp $ */
#ifndef __SP_TCP_FLAG_CHECK_H__
#define __SP_TCP_FLAG_CHECK_H__

#include "snort.h"

#define PLUGIN_TCP_FLAG_CHECK   2
#define M_NORMAL  0
#define M_ALL     1
#define M_ANY     2
#define M_NOT     3

typedef struct _TCPFlagCheckData
{
    u_char mode;
    u_char tcp_flags; /* ptr to next match struct */

} TCPFlagCheckData;

void TCPFlagCheckInit(char *, OptTreeNode *, int);
void SetupTCPFlagCheck();
void ParseTCPFlags(char *, OptTreeNode *);
int CheckTcpFlags(Packet *, struct _OptTreeNode *, OptFpList *);


#endif
