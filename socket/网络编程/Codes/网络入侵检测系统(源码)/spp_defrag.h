/* Snort Preprocessor Plugin Header File Defrag */
/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 2000,2001 Dragos Ruiu <dr@dursec.com>
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

#include "snort.h"

#ifndef __SPP_DEFRAG_H__
#define __SPP_DEFRAG_H__

#define IP_OFFMASK 0x1fff
#define IP_MF 0x2000
#define IP_DF 0x4000
#define IP_RF 0x8000

/* Data structures for fragments hash.  A Fragment is allocated for each
 * ip fragment received.  FragQ is the hashtable...  Each element points
 * to a linked-list of FragQs, each of which has a linked-list of
 * Fragments attached. the Fragments lists are circular.
 */
typedef struct _Fragment
{
    struct _Fragment *prev;
    struct _Fragment *next;
    u_char *frag;
    u_int offset;
    u_int len;
    u_int mf;
} Fragment;

typedef struct _FragQ
{
    Fragment *prev, *next;
    u_short id;
    u_char proto;
    u_int ttl;
    u_char *hdr;
    u_int hlen;
    struct in_addr ip_src;
    struct in_addr ip_dst;
    struct _FragQ *nq, *pq;
} FragQ;

/* Packet reassembly stuff - stolen from ip_input.c/FreeBSD */
#define IPREASS_NHASH_LOG2      6
#define IPREASS_NHASH           (1 << IPREASS_NHASH_LOG2)
#define IPREASS_HMASK           (IPREASS_NHASH - 1)
#define IPREASS_HASH(x,y) \
	(((((x) & 0xF) | ((((x) >> 8) & 0xF) << 4)) ^ (y)) & IPREASS_HMASK)

/* list of function prototypes for this preprocessor */
void SetupDefrag();
void DefragInit(u_char *);
void PreprocDefrag(Packet *);
void AddFrag(Packet *, FragQ *);
void AddNewQ(Packet *, int);
void TrimFrag(Fragment *, int);
void DeleteFrag(Fragment *);
void DeleteFragQ(FragQ *);
void CheckReassembled(FragQ *);
Packet *GeneratePacket(FragQ *);

#endif							/* __SPP_DEFRAG_H__ */
