/* $Id: checksum.h,v 1.3 2001/01/02 08:06:00 roesch Exp $ */
/*
** Copyright (C) 2000,2001 Christopher Cramer <cec@ee.duke.edu>
** Snort is Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
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

#ifndef __CHECKSUM_H__
#define __CHECKSUM_H__

#include "snort.h"

/* define checksum error flags */
#define CSE_IP    0x01
#define CSE_TCP   0x02
#define CSE_UDP   0x04
#define CSE_ICMP  0x08
#define CSE_IGMP  0x10

u_int16_t checksum(u_int16_t *, u_int32_t, u_int16_t *, u_int32_t );

#endif /* __CHECKSUM_H__ */
