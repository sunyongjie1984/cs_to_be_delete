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
/* $Id: spo_alert_syslog.c,v 1.6 2001/01/02 08:06:01 roesch Exp $ */

/* spo_alert_syslog 
 * 
 * Purpose:
 *
 * This module sends alerts to the syslog service.
 *
 * Arguments:
 *   
 * Logging mechanism?
 *
 * Effect:
 *
 * Alerts are written to the syslog service with in the facility indicated by
 * the module arguments.
 *
 * Comments:
 *
 * First try
 *
 */

/* your preprocessor header file goes here */
#include "spo_alert_syslog.h"

/* external globals from rules.c */
extern char *file_name;
extern int file_line;

/*
 * Function: SetupSyslog()
 *
 * Purpose: Registers the output plugin keyword and initialization 
 *          function into the output plugin list.  This is the function that
 *          gets called from InitOutputPlugins() in plugbase.c.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 */
void SetupAlertSyslog()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("alert_syslog", NT_OUTPUT_ALERT, AlertSyslogInit);

#ifdef DEBUG
    printf("Output plugin: Alert-Syslog is setup...\n");
#endif
}


/*
 * Function: AlertSyslogInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void AlertSyslogInit(u_char *args)
{
    SyslogData *data;
#ifdef DEBUG
    printf("Output: Alert-Syslog Initialized\n");
#endif

    pv.alert_plugin_active = 1;

    /* parse the argument list from the rules file */
    data = ParseSyslogArgs(args);

    openlog("snort", data->options, data->facility);

#ifdef DEBUG
    printf("Linking syslog alert function to call list...\n");
#endif

    /* Set the preprocessor function into the function list */
    AddFuncToOutputList(AlertSyslog, NT_OUTPUT_ALERT, data);
    AddFuncToCleanExitList(AlertSyslogCleanExitFunc, data);
    AddFuncToRestartList(AlertSyslogRestartFunc, data);
}



/*
 * Function: ParseSyslogArgs(char *)
 *
 * Purpose: Process the preprocessor arguements from the rules file and 
 *          initialize the preprocessor's data struct.  This function doesn't
 *          have to exist if it makes sense to parse the args in the init 
 *          function.
 *
 * Arguments: args => argument list
 *
 * Returns: void function
 *
 */
SyslogData *ParseSyslogArgs(char *args)
{
    char **toks;
    int num_toks;
    int i = 0;
    SyslogData *data;

    data = (SyslogData *)malloc(sizeof(SyslogData));

    /* default values for AlertInfo components */
    data->options = 0;
    data->facility = LOG_AUTH;
    data->priority = LOG_INFO;

    if(args == NULL)
    {
        fprintf(stderr, "ERROR %s (%d)=> No arguments to alert_syslog preprocessor!\n", file_name, file_line);
        exit(1);
    }

    /* tokenize the argument list */
    toks = mSplit(args, " |", 31, &num_toks, '\\');

    for(i = 0; i < num_toks; i++)
    {
        /* possible openlog options */

#ifdef LOG_CONS 
        if(!strncasecmp("LOG_CONS", toks[i], 8))
        {
            data->options |= LOG_CONS;
        }
#endif
#ifdef LOG_NDELAY 
        else if(!strncasecmp("LOG_NDELAY", toks[i], 10))
        {
            data->options |= LOG_NDELAY;
        }
#endif
#ifdef LOG_PERROR 
        else if(!strncasecmp("LOG_PERROR", toks[i], 10))
        {
            data->options |= LOG_PERROR;
        }
#endif
#ifdef LOG_PID 
        else if(!strncasecmp("LOG_PID", toks[i], 7))
        {
            data->options |= LOG_PID;
        }
#endif

        /* possible openlog facilities */

#ifdef LOG_AUTHPRIV 
        else if(!strncasecmp("LOG_AUTHPRIV", toks[i], 12))
        {
            data->facility = LOG_AUTHPRIV;
        }
#endif
#ifdef LOG_AUTH 
        else if(!strncasecmp("LOG_AUTH", toks[i], 8))
        {
            data->facility = LOG_AUTH;
        }
#endif
#ifdef LOG_DAEMON 
        else if(!strncasecmp("LOG_DAEMON", toks[i], 10))
        {
            data->facility = LOG_DAEMON;
        }
#endif
#ifdef LOG_LOCAL0 
        else if(!strncasecmp("LOG_LOCAL0", toks[i], 10))
        {
            data->facility = LOG_LOCAL0;
        }
#endif
#ifdef LOG_LOCAL1 
        else if(!strncasecmp("LOG_LOCAL1", toks[i], 10))
        {
            data->facility = LOG_LOCAL1;
        }
#endif
#ifdef LOG_LOCAL2 
        else if(!strncasecmp("LOG_LOCAL2", toks[i], 10))
        {
            data->facility = LOG_LOCAL2;
        }
#endif
#ifdef LOG_LOCAL3 
        else if(!strncasecmp("LOG_LOCAL3", toks[i], 10))
        {
            data->facility = LOG_LOCAL3;
        }
#endif
#ifdef LOG_LOCAL4 
        else if(!strncasecmp("LOG_LOCAL4", toks[i], 10))
        {
            data->facility = LOG_LOCAL4;
        }
#endif
#ifdef LOG_LOCAL5 
        else if(!strncasecmp("LOG_LOCAL5", toks[i], 10))
        {
            data->facility = LOG_LOCAL5;
        }
#endif
#ifdef LOG_LOCAL6 
        else if(!strncasecmp("LOG_LOCAL6", toks[i], 10))
        {
            data->facility = LOG_LOCAL6;
        }
#endif
#ifdef LOG_LOCAL7 
        else if(!strncasecmp("LOG_LOCAL7", toks[i], 10))
        {
            data->facility = LOG_LOCAL7;
        }
#endif
#ifdef LOG_USER 
        else if(!strncasecmp("LOG_USER", toks[i], 8))
        {
            data->facility = LOG_USER;
        }
#endif

        /* possible syslog priorities */

#ifdef LOG_EMERG 
        else if(!strncasecmp("LOG_EMERG", toks[i], 9))
        {
            data->priority = LOG_EMERG;
        }
#endif
#ifdef LOG_ALERT 
        else if(!strncasecmp("LOG_ALERT", toks[i], 9))
        {
            data->priority = LOG_ALERT;
        }
#endif
#ifdef LOG_CRIT 
        else if(!strncasecmp("LOG_CRIT", toks[i], 8))
        {
            data->priority = LOG_CRIT;
        }
#endif
#ifdef LOG_ERR 
        else if(!strncasecmp("LOG_ERR", toks[i], 7))
        {
            data->priority = LOG_ERR;
        }
#endif
#ifdef LOG_WARNING 
        else if(!strncasecmp("LOG_WARNING", toks[i], 11))
        {
            data->priority = LOG_WARNING;
        }
#endif
#ifdef LOG_NOTICE 
        else if(!strncasecmp("LOG_NOTICE", toks[i], 10))
        {
            data->priority = LOG_NOTICE;
        }
#endif
#ifdef LOG_INFO 
        else if(!strncasecmp("LOG_INFO", toks[i], 8))
        {
            data->priority = LOG_INFO;
        }
#endif
#ifdef LOG_DEBUG 
        else if(!strncasecmp("LOG_DEBUG", toks[i], 9))
        {
            data->priority = LOG_DEBUG;
        }
#endif
        else
        {
            fprintf(stderr, "WARNING %s (%d) => Unrecognized syslog facility/priority: %s\n", file_name, file_line, toks[i]);
        }
    }
    return data;
}


/*
 * Function: PreprocFunction(Packet *)
 *
 * Purpose: Perform the preprocessor's intended function.  This can be
 *          simple (statistics collection) or complex (IP defragmentation)
 *          as you like.  Try not to destroy the performance of the whole
 *          system by trying to do too much....
 *
 * Arguments: p => pointer to the current packet data struct 
 *
 * Returns: void function
 *
 */
void AlertSyslog(Packet *p, char *msg, void *arg)
{
    char sip[16];
    char dip[16];
    SyslogData *data = (SyslogData *)arg;

    if(p == NULL)
    {
#ifdef DEBUG
        printf("NULL packet in syslog alert!\n");
#endif
        syslog(data->priority, "%s",msg==NULL?"ALERT!":msg);
        return;
    }

    /* have to do this since inet_ntoa is fucked up and writes to
       a static memory location */
    strncpy(sip, inet_ntoa(p->iph->ip_src), 16);
    strncpy(dip, inet_ntoa(p->iph->ip_dst), 16);

    if(p->iph->ip_proto == IPPROTO_ICMP || p->frag_flag)
    {
        if(msg != NULL)
        {
            if(pv.alert_interface_flag)
            {
                /* ICMP packets don't get port info... */
#ifdef WIN32
				syslog(data->priority, "<%s> %s: %s -> %s", print_interface(pv.interfaces[0]),
#else
                syslog(data->priority, "<%s> %s: %s -> %s", pv.interfaces[0],
#endif
                       msg, sip, dip);
            }
            else
            {
                /* ICMP packets don't get port info... */
                syslog(data->priority, "%s: %s -> %s", msg, sip, dip);
            }
        }
        else
        {
            /* ICMP packets don't get port info... */
            syslog(data->priority, "ALERT: %s -> %s", sip, dip);
        }
    }
    else
    {
        if(msg != NULL)
        {
            if(pv.alert_interface_flag)
            {
                syslog(data->priority, "<%s> %s: %s:%i -> %s:%i", 
#ifdef WIN32
					   print_interface(pv.interfaces[0]), msg, sip, p->sp, dip, p->dp);
#else
                       pv.interfaces[0], msg, sip, p->sp, dip, p->dp);
#endif
            }
            else
            {
                syslog(data->priority, "%s: %s:%i -> %s:%i", msg,
                       sip, p->sp, dip, p->dp);
            }
        }
        else
        {
            syslog(data->priority, "ALERT: %s:%i -> %s:%i",
                   sip, p->sp, dip, p->dp);
        }
    }

    return;
}


void AlertSyslogCleanExitFunc(int signal, void *arg)
{
    SyslogData *data = (SyslogData *)arg;
#ifdef DEBUG
    printf("AlertSyslogCleanExitFunc\n");
#endif
    /* free memory from SyslogData */
    free(data);
}

void AlertSyslogRestartFunc(int signal, void *arg)
{
    SyslogData *data = (SyslogData *)arg;
#ifdef DEBUG
    printf("AlertSyslogRestartFunc\n");
#endif
    /* free memory from SyslogData */
    free(data);
}
