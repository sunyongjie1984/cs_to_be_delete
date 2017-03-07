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

/* $Id: sp_ip_tos_check.h,v 1.3 2001/01/12 20:33:16 roesch Exp $ */
#ifndef __SP_IP_TOS_CHECK_H__
#define __SP_IP_TOS_CHECK_H__

#include "snort.h"

#define PLUGIN_IP_TOS_CHECK  17

typedef struct _IpTosData
{
    u_int8_t ip_tos;
    u_int8_t not_flag;

} IpTosData;

void IpTosCheckInit(char *, OptTreeNode *, int);
void SetupIpTosCheck();
void ParseIpTos(char *, OptTreeNode *);
int IpTosCheckEq(Packet *, struct _OptTreeNode *, OptFpList *);

#endif  /* __SP_IP_TOS_CHECK_H__ */
