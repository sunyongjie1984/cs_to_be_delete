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

/* $Id: spp_minfrag.c,v 1.5 2001/01/25 19:16:16 fygrave Exp $ */
#include "spp_minfrag.h"

extern char *file_name;
extern int file_line;
extern int do_detect;

MinfragData FragData;

void SetupMinfrag()
{
    RegisterPreprocessor("minfrag", MinfragInit);

#ifdef DEBUG
    printf("Preprocessor: Minfrag Initialized\n");
#endif
}


void MinfragInit(u_char *args)
{
#ifdef DEBUG
    printf("Preprocessor: Minfrag initializing\n");
#endif

    ProcessMinfragArgs(args);

#ifdef DEBUG
    printf("Setting Minimum Fragment Size: %d bytes\n", FragData.minfrag);
#endif

    AddFuncToPreprocList(CheckMinfrag);
}



void ProcessMinfragArgs(u_char *args)
{
    char **toks;
    int num_toks;
    int i;

    if(args == NULL)
    {
        FatalError("ERROR %s (%d)=> No arguments to minfrag preprocessor!\n", file_name, file_line);
    }

    /* tokenize the argument list */
    toks = mSplit(args, " ", 3, &num_toks, '\\');

    /* loop through each token */
    for(i = 0; i < num_toks; i++)
    {
        /* we'll assume any token that starts with a digit is the threshold value, 
           and non-digit tokens are the home/any detection modifiers */
        switch(isdigit((int)toks[i][0]))
        {
            
            case 0: 
                if(!strncasecmp(toks[i], "home", 4))
                {
#ifdef DEBUG
                    printf("Setting home_net_only active for minfrag\n");
#endif
                    FragData.home_net_only = 1;
                }
                else if(!strncasecmp(toks[i], "any", 3))
                {
                    FragData.home_net_only = 0;
                }
                else
                {
                    FatalError("ERROR %s (%d)=> Unknown minfrag argument: %s\n", file_name, file_line, toks[i]);
                }

                break;

            default:
                FragData.minfrag = atoi(toks[i]);
                break;

        } 
    }
}



void CheckMinfrag(Packet *p)
{
    if(!p->frag_flag)
    {
#ifdef DEBUG
        printf("p->frag_flag = %d\n", p->frag_flag);
#endif
        return;
    }

#ifdef DEBUG
    printf("p->frag_offset = 0x%04X\n", p->frag_offset);
#endif

    do_detect = 0;

    if(FragData.home_net_only)
    {
        if(!DestinationIpIsHomenet(p))
        {
            return;
        }
    }

    if(p->frag_offset == 0)
    {
        if(p->dsize <= FragData.minfrag)
        {
#ifdef DEBUG
            printf("datasize = %d   minfrag = %d  \n", p->dsize, FragData.minfrag);
            printf("Calling AlertFunc & LogFunc!\n");
#endif
            /*(*AlertFunc)(p, MINFRAG_ALERT_MESSAGE);*/
            CallAlertFuncs(p, MINFRAG_ALERT_MESSAGE, NULL);
            /*(*LogFunc)(p, MINFRAG_ALERT_MESSAGE);*/
            CallLogFuncs(p, MINFRAG_ALERT_MESSAGE, NULL);
        }
    }
}


