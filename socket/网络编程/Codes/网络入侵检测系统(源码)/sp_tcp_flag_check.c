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

/* $Id: sp_tcp_flag_check.c,v 1.6 2001/01/02 08:06:01 roesch Exp $ */
#include "sp_tcp_flag_check.h"

extern char *file_name;
extern int file_line;

void SetupTCPFlagCheck()
{
    RegisterPlugin("flags", TCPFlagCheckInit);

#ifdef DEBUG
    printf("Plugin: TCPFlagCheck Initialized!\n");
#endif
}



void TCPFlagCheckInit(char *data, OptTreeNode *otn, int protocol)
{
    if(protocol != IPPROTO_TCP)
    {
        FatalError("[!] ERROR Line %s (%d): TCP Options on non-TCP rule\n", file_name, file_line);
    }

    otn->ds_list[PLUGIN_TCP_FLAG_CHECK] = (TCPFlagCheckData *)calloc(sizeof(TCPFlagCheckData), sizeof(char));

    /* set up the pattern buffer */
    ParseTCPFlags(data, otn);

#ifdef DEBUG
    printf("Adding TCP flag check function (%p) to list\n", CheckTcpFlags);
#endif

    /* link the plugin function in to the current OTN */
    AddOptFuncToList(CheckTcpFlags, otn);

#ifdef DEBUG
    printf("OTN function CheckTcpFlags added to rule!\n");
#endif
}



/****************************************************************************
 *
 * Function: ParseTCPflags(char *)
 *
 * Purpose: Figure out which TCP flags the current rule is interested in
 *
 * Arguments: rule => the rule string 
 *
 * Returns: void function
 *
 ***************************************************************************/
void ParseTCPFlags(char *rule, OptTreeNode *otn)
{
    char *fptr;
    char *fend;
    TCPFlagCheckData *idx;

    idx = otn->ds_list[PLUGIN_TCP_FLAG_CHECK];

    fptr = rule;

    while(isspace((u_char) *fptr))
        fptr++;

    if(strlen(fptr) == 0)
    {
        FatalError("[!] ERROR Line %s (%d): Flags missing in TCP flag rule\n", file_name, file_line);
    }

    /* find the end of the alert string */
    fend = fptr + strlen(fptr); 

    idx->mode = M_NORMAL; /* this is the default, unless overridden */

    while(fptr < fend)
    {
        switch((*fptr&0xFF))
        {
            case 'f':
            case 'F':
                idx->tcp_flags |= R_FIN;
                break;

            case 's':
            case 'S':
                idx->tcp_flags |= R_SYN;
                break;

            case 'r':
            case 'R':
                idx->tcp_flags |= R_RST;
                break;

            case 'p':
            case 'P':
                idx->tcp_flags |= R_PSH;
                break;

            case 'a':
            case 'A':
                idx->tcp_flags |= R_ACK;
                break;

            case 'u':
            case 'U':
                idx->tcp_flags |= R_URG;
                break;

            case '0':
                idx->tcp_flags = 0;
                break;

            case '1': /* reserved bit flags */
                idx->tcp_flags |= R_RES1;
                break;

            case '2': /* reserved bit flags */
                idx->tcp_flags |= R_RES2;
                break;

            case '!': /* not, fire if all flags specified are not present,
                         other are don't care */
                idx->mode = M_NOT;
                break;
            case '*': /* star or any, fire if any flags specified are 
                         present, other are don't care */
                idx->mode = M_ANY;
                break;
            case '+': /* plus or all, fire if all flags specified are
                         present, other are don't care */
                idx->mode = M_ALL;
                break;
            default:
                ErrorMessage("[!] ERROR Line %s (%d): bad TCP flag = \"%c\"\n",
                             file_name, file_line, *fptr);
                FatalError("      Valid otions: UAPRSF12 or 0 for NO flags (e.g. NULL scan), and !, + or * for modifiers\n");
        }

        fptr++;
    }
}


int CheckTcpFlags(Packet *p, struct _OptTreeNode *otn_idx, OptFpList *fp_list)
{
    TCPFlagCheckData *flagptr;

    flagptr = otn_idx->ds_list[PLUGIN_TCP_FLAG_CHECK];



    if(!p->tcph)
        return 0; /* if error appeared when tcp header was processed,
               * test fails automagically */

#ifdef DEBUG
    printf("           <!!> CheckTcpFlags: ");
#endif

    switch((flagptr->mode))
    {
        case M_NORMAL:
            if(flagptr->tcp_flags == p->tcph->th_flags) /* only these set */
            {
#ifdef DEBUG
                printf("Got TCP [default] flag match!\n");
#endif
                return fp_list->next->OptTestFunc(p, otn_idx, fp_list->next);
            }
#ifdef DEBUG
            else
            {
                printf("No match\n");
            }
#endif
            break;

        case M_ALL:
            /* all set */
            if((flagptr->tcp_flags & p->tcph->th_flags) == flagptr->tcp_flags)
            {
#ifdef DEBUG
                printf("Got TCP [ALL] flag match!\n");
#endif
                return fp_list->next->OptTestFunc(p, otn_idx, fp_list->next);
            }
#ifdef DEBUG
            else
            {
                printf("No match\n");
            }
#endif
            break;

        case M_NOT:
            if((flagptr->tcp_flags & p->tcph->th_flags) == 0)  /* none set */
            {
#ifdef DEBUG
                printf("Got TCP [NOT] flag match!\n");
#endif
                return fp_list->next->OptTestFunc(p, otn_idx, fp_list->next);
            }
#ifdef DEBUG
            else
            {
                printf("No match\n");
            }
#endif
            break;

        case M_ANY:
            if((flagptr->tcp_flags & p->tcph->th_flags) != 0)  /* something set */
            {
#ifdef DEBUG
                printf("Got TCP [ANY] flag match!\n");
#endif
                return fp_list->next->OptTestFunc(p, otn_idx, fp_list->next);
            }
#ifdef DEBUG
            else
            {
                printf("No match\n");
            }
#endif
            break;

        default:  /* Should never see this */
#ifdef DEBUG
            printf("TCP flag check went to default case for some dumbshit reason\n");
#endif
            break;
    }

    return 0;
}

