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

/* $Id: spp_http_decode.h,v 1.2 2001/01/02 08:06:01 roesch Exp $ */
#include "snort.h"

#ifndef __SPP_HTTP_DECODE_H__
#define __SPP_HTTP_DECODE_H__

/* this is where we keep the list of ports that this process is 
   going to be applied to */
typedef struct _PortList
{
    int ports[32];   /* 32 is kind of arbitrary */

    int num_entries;

} PortList;


void SetupHttpDecode();
void HttpDecodeInit(u_char *);
void SetPorts(char *);
void PreprocUrlDecode(Packet *);
int nibble(char);


#endif  /* __SPP_HTTP_DECODE_H__ */
