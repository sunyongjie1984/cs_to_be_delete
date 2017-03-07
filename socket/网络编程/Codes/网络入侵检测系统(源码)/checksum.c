/* $Id: checksum.c,v 1.2 2001/01/02 08:06:00 roesch Exp $ */
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

#include "checksum.h"

/*
 * Function: checksum(u_int16_t *, u_int32_t, u_int16_t *, u_int32_t)
 *
 * Purpose: Huh huh, math....
 *
 * Arguments: b1   => pointer to data set one
 *            len1 => length of data set one
 *            b2   => pointer to data set two
 *            len2 => length of data set two
 *
 * Returns: csum => the calculated checksum for the given data
 */
u_int16_t checksum(u_int16_t *b1, u_int32_t len1, u_int16_t *b2, u_int32_t len2)
{
    u_int32_t sum = 0;

    if(b1 != (u_int16_t *)NULL) 
    {
        while(len1 > 1) 
        {
            sum += *((u_int16_t *)b1 ++);

            if(sum & 0x80000000)
            {
                sum = (sum & 0xffff) + (sum >> 16);
            }

            len1 -= 2;
        }
    
        /* we'll have problems if b2 exists and len1 is odd */
        if(len1)
        {
           sum += (u_int16_t) * (u_int8_t*) b1;
        }
    }

    if(b2 != (u_int16_t*)NULL) 
    {
        while(len2 > 1) 
        {
            sum += *((u_int16_t*)b2 ++);

            if(sum & 0x80000000)
            {
                sum = (sum & 0xffff) + (sum >> 16);
            }

            len2 -= 2;
        }

        if(len2)
        {
            sum += (u_int16_t) * (u_int8_t*) b2;
        }
    }

    while(sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}
