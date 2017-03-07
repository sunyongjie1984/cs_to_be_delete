/* $Id: sp_respond.h,v 1.5 2001/01/02 08:06:01 roesch Exp $ */
/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 1999,2000,2001 Christian Lademann <cal@zls.de>
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

/*  I N C L U D E S
**********************************************************/
#include "snort.h"

/*  D E F I N E S
************************************************************/
#ifndef __RESPOND_H__
#define __RESPOND_H__


/*  D A T A  S T R U C T U R E S
*********************************************/


/*  P R O T O T Y P E S
******************************************************/
#ifdef ENABLE_RESPONSE

    #define PLUGIN_RESPOND 18

typedef struct _RespondData
{
    u_int response_flag;
} RespondData;

void SetupRespond(void);
void RespondInit(char *, OptTreeNode *, int ); 
int ParseResponse(char *);
int SendICMP_UNREACH(int, u_long, u_long, Packet *);
int SendTCPRST(u_long, u_long, u_short, u_short, u_long, u_long);
int Respond(Packet *, RspFpList *);
#endif

#endif /* __RESPOND_H__ */

