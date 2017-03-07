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

/* $Id: sp_pattern_match.h,v 1.6 2001/01/02 08:06:01 roesch Exp $ */
#ifndef __SP_PATTERN_MATCH_H__
#define __SP_PATTERN_MATCH_H__


#include "snort.h"
#include <ctype.h>

#define PLUGIN_PATTERN_MATCH   1

typedef struct _PatternMatchData
{
    int offset;             /* pattern search start offset */
    int depth;              /* pattern search depth */
    u_int pattern_size;     /* size of app layer pattern */
    char *pattern_buf;      /* app layer pattern to match on */
    int (*search)(char *, int, char *, int, int *, int *);  /* search function */
    int *skip_stride; /* B-M skip array */
    int *shift_stride; /* B-M shift array */
    struct _PatternMatchData *next; /* ptr to next match struct */

} PatternMatchData;

void PayloadSearchInit(char *, OptTreeNode *, int);
void PayloadSearchListInit(char *, OptTreeNode *, int);
void ParseContentListFile(char *, OptTreeNode *, int);
void SetupPatternMatch();
void ParsePattern(char *, OptTreeNode *);
int CheckANDPatternMatch(Packet *, struct _OptTreeNode *, OptFpList *);
int CheckORPatternMatch(Packet *, struct _OptTreeNode *, OptFpList *);
void PayloadSearchOffset(char *, OptTreeNode *, int);
void PayloadSearchDepth(char *, OptTreeNode *, int);
void PayloadSearchNocase(char *, OptTreeNode *, int);
void PayloadSearchRegex(char *, OptTreeNode *, int);
void NewNode(OptTreeNode *);


#endif
