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

/* $Id: sp_rpc_check.h,v 1.3 2001/01/02 10:40:57 fygrave Exp $ */
#ifndef __SP_RPC_CHECK_H__
#define __SP_RPC_CHECK_H__

#include "snort.h"

#define PLUGIN_RPC_CHECK  14

typedef struct _RpcCheckData
{
    u_long program; /* RPC program number */
    u_long vers; /* RPC program version */
    u_long proc; /* RPC procedure number */
    int flags; /* Which of the above fields have been specified */

} RpcCheckData;

#define RPC_CHECK_PROG 1
#define RPC_CHECK_VERS 2
#define RPC_CHECK_PROC 4

void RpcCheckInit(char *, OptTreeNode *, int);
void SetupRpcCheck();
void ParseRpc(char *, OptTreeNode *);
int CheckRpc(Packet *, struct _OptTreeNode *, OptFpList *);

#endif  /* __SP_RPC_CHECK_H__ */
