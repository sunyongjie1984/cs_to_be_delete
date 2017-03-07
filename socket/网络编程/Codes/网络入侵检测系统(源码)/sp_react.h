/* $Id: sp_react.h,v 1.9 2001/01/02 08:06:01 roesch Exp $ */

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

#ifndef __SP_REACT_H__
#define __SP_REACT_H__

#include "snort.h"

#ifdef ENABLE_RESPONSE

    #define TCP_DATA_BUF	1024

    #define REACT_BLOCK	0x01
    #define REACT_WARN	0x02

typedef struct _ReactData
{
    int reaction_flag;  /* flexible reaction on alert */
    int proxy_port_nr;      /* proxy TCP port */
    u_int html_resp_size;       /* size of app html response */
    u_char *html_resp_buf;      /* html response to send */

} ReactData;

#endif /* ENABLE_RESPONSE */

void SetupReact();

#ifdef ENABLE_RESPONSE
void ReactInit(char *, OptTreeNode *, int);
void ParseReact(char *, OptTreeNode *, ReactData *);
int React(Packet *, RspFpList *);
int SendTCP(u_long, u_long, u_short, u_short, int, int, u_char, const u_char *,
            int);

#endif  /* ENABLE_RESPONSE */
#endif  /* __SP_REACT_H__ */


