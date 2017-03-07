/* $Id: sp_session.c,v 1.9 2001/01/18 06:40:50 roesch Exp $ */

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

/* Snort Session Logging Plugin */

/* sp_session 
 * 
 * Purpose:
 *
 * Drops data (printable or otherwise) into a SESSION file.  Useful for 
 * logging user sessions (telnet, http, ftp, etc).
 *
 * Arguments:
 *   
 * This plugin can take two arguments:
 *    printable => only log the "printable" ASCII characters.
 *    all       => log all traffic in the session, logging non-printable
 *                 chars in "\xNN" hexidecimal format
 *
 * Effect:
 *
 * Warning, this plugin may slow Snort *way* down!
 *
 */

/* put the name of your pluging header file here */
#include "sp_session.h"

extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */


/****************************************************************************
 * 
 * Function: SetupSession()
 *
 * Purpose: Init the session plugin module.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetupSession()
{
    /* map the keyword to an initialization/processing function */
    RegisterPlugin("session", SessionInit);

#ifdef DEBUG
    printf("Plugin: Session Setup\n");
#endif
}


/**************************************************************************
 * 
 * Function: SessionInit(char *, OptTreeNode *)
 *
 * Purpose: Initialize the sesion plugin, parsing the rule parameters and
 *          setting up any necessary data structures.
 *
 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *
 * Returns: void function
 *
 *************************************************************************/
void SessionInit(char *data, OptTreeNode *otn, int protocol)
{

    /*
     * Theoretically we should only all this plugin to be used when there's a 
     * possibility of a session happening (i.e. TCP), but I get enough 
     * requests that I'm going to pull the verifier so that things should work
     * for everyone
     */
/*    if(protocol != IPPROTO_TCP)
    {
        FatalError("ERROR line %s (%d): Session keyword can not be used in non-TCP rule\n",
                file_name, file_line);
    }*/

    /* allocate the data structure and attach it to the
       rule's data struct list */
    otn->ds_list[PLUGIN_SESSION] = (SessionData *) calloc(sizeof(SessionData), sizeof(char));

    /* be sure to check that the protocol that is passed in matches the
       transport layer protocol that you're using for this rule! */

    /* this is where the keyword arguments are processed and placed into 
       the rule option's data structure */
    ParseSession(data, otn);

    /* finally, attach the option's detection function to the rule's 
       detect function pointer list */
    AddOptFuncToList(LogSessionData, otn);
}



/****************************************************************************
 * 
 * Function: ParseSession(char *, OptTreeNode *)
 *
 * Purpose: Figure out how much of the session data we're collecting
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseSession(char *data, OptTreeNode *otn)
{
    SessionData *ds_ptr;  /* data struct pointer */

    /* set the ds pointer to make it easier to reference the option's
       particular data struct */
    ds_ptr = otn->ds_list[PLUGIN_SESSION];

    /* manipulate the option arguments here */
    while(isspace((int)*data))
        data++;

    if(!strncasecmp(data, "printable", 9))
    {
        ds_ptr->session_flag = SESSION_PRINTABLE;
        return;
    }

    if(!strncasecmp(data, "all", 3))
    {
        ds_ptr->session_flag = SESSION_ALL;
        return;
    }

    FatalError( "ERROR %s (%d): invalid session modifier: %s\n", file_name, file_line, data);

}



/****************************************************************************
 * 
 * Function: LogSessionData(char *, OptTreeNode *)
 *
 * Purpose: Dumps the session data to the log file.
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: Always calls the next function (this one doesn't test the data,
 *          it just logs it....)
 *
 ****************************************************************************/
int LogSessionData(Packet *p, struct _OptTreeNode *otn, OptFpList *fp_list)
{
    FILE *session;         /* session file ptr */
    char *filename = NULL;

    /* if there's data in this packet */
    if(p != NULL && p->dsize != 0 && p->data != NULL)
    {
        session = OpenSessionFile(p, filename);

        if(session == NULL)
        {
            FatalError("ERROR: OpenSessionFile() => fopen(%s) session file: %s\n", filename, strerror(errno));
        }

        DumpSessionData(session, p, otn);

        free(filename);

        fclose(session);
    }

    return fp_list->next->OptTestFunc(p, otn, fp_list->next);
}



void DumpSessionData(FILE *fp, Packet *p, struct _OptTreeNode *otn)
{
    u_char *idx;
    u_char *end;
    char conv[] = "0123456789ABCDEF"; /* xlation lookup table */

    if(p->dsize == 0 || p->data == NULL)
        return;

    idx = p->data;
    end = idx + p->dsize;

    if(((SessionData *) otn->ds_list[PLUGIN_SESSION])->session_flag == SESSION_PRINTABLE)
    {
        while(idx != end)
        {
            if((*idx > 0x1f && *idx < 0x7f) || *idx == 0x0a || *idx == 0x0d)
            {
                fputc(*idx, fp);
            }
            idx++;
        }
    }
    else
    {
        while(idx != end)
        {
            if((*idx > 0x1f && *idx < 0x7f) || *idx == 0x0a || *idx == 0x0d)
            {
                fputc(*idx, fp);
            }
            else
            {
                fputc('\\', fp);
                fputc(conv[((*idx&0xFF) >> 4)], fp);
                fputc(conv[((*idx&0xFF)&0x0F)], fp);
            }

            idx++;
        }
    }
}



FILE *OpenSessionFile(Packet *p, char *filename)
{
    char log_path[STD_BUF];
    char session_file[STD_BUF]; /* name of session file */

    if(p->frag_flag)  
    {
        return NULL;
    }

    bzero((char *)session_file, STD_BUF);
    bzero((char *)log_path, STD_BUF);

    /* figure out which way this packet is headed in relation to the homenet */
    if((p->iph->ip_dst.s_addr & pv.netmask) == pv.homenet)
    {
        if((p->iph->ip_src.s_addr & pv.netmask) != pv.homenet)
        {
            sprintf(log_path, "%s/%s", pv.log_dir, inet_ntoa(p->iph->ip_src));
        }
        else
        {
            if(p->sp >= p->dp)
            {
                sprintf(log_path, "%s/%s", pv.log_dir, inet_ntoa(p->iph->ip_src));
            }
            else
            {
                sprintf(log_path, "%s/%s", pv.log_dir, inet_ntoa(p->iph->ip_dst));
            }
        }
    }
    else
    {
        if((p->iph->ip_src.s_addr & pv.netmask) == pv.homenet)
        {
            sprintf(log_path, "%s/%s", pv.log_dir, inet_ntoa(p->iph->ip_dst));
        }
        else
        {
            if(p->sp >= p->dp)
            {
                sprintf(log_path, "%s/%s", pv.log_dir, inet_ntoa(p->iph->ip_src));
            }
            else
            {
                sprintf(log_path, "%s/%s", pv.log_dir, inet_ntoa(p->iph->ip_dst));
            }
        }
    }

    /* build the log directory */
    if(mkdir(log_path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
    {
#ifdef DEBUG
        if(errno != EEXIST)
        {
            FatalError("Problem creating directory %s\n",log_path);
        }
#endif
    }

    if(p->sp >= p->dp)
    {
        sprintf(session_file, "%s/SESSION:%d-%d", log_path, p->sp, p->dp);
    }
    else
    {
        sprintf(session_file, "%s/SESSION:%d-%d", log_path, p->dp, p->sp);
    }

    filename = (char *) calloc(strlen(session_file)+1,sizeof(char));
    strncpy(filename, session_file, strlen(session_file)+1);
    return fopen(session_file, "a");
}




