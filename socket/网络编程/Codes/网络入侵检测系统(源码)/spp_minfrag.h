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

/* $Id: spp_minfrag.h,v 1.2 2001/01/02 08:06:01 roesch Exp $ */
#ifndef __SPP_MINFRAG_H__
#define __SPP_MINFRAG_H__

#include "snort.h"

#define MINFRAG_ALERT_MESSAGE "Tiny Fragments - Possible Hostile Activity"

typedef struct _MinfragData
{
    int minfrag;   /* fragmentation size alert threshold */
    int home_net_only;  /* flag, only get tiny frags on the home network */
} MinfragData;

void SetupMinfrag();
void MinfragInit(u_char *);
void ProcessMinfragArgs(u_char *);
void CheckMinfrag(Packet *);


#endif  /* __SPP_MINFRAG_H__ */
