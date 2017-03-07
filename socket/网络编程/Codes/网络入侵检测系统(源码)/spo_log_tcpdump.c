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

/* $Id: spo_log_tcpdump.c,v 1.11 2001/01/17 03:19:01 roesch Exp $ */

/* spo_log_tcpdump 
 * 
 * Purpose:
 *
 * This plugin generates tcpdump formatted binary log files
 *
 * Arguments:
 *   
 * filename of the output log (default: snort.log)
 *
 * Effect:
 *
 * Packet logs are written (quickly) to a tcpdump formatted output
 * file
 *
 * Comments:
 *
 * First logger...
 *
 */

/* your output plugin header file goes here */
#include "spo_log_tcpdump.h"

/* external globals from rules.c */
extern char *file_name;    /* current rules file filename */
extern int file_line;      /* current line being processed in rules file */
extern pcap_dumper_t *dumpd;  /* ptr to pcap packet dump facility */
extern PV pv;              /* program variables struct */

/* If you need to instantiate the plugin's data structure, do it here */
LogTcpdumpData TcpdumpLogInfo;

/*
 * Function: SetupLogTcpdump()
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
void SetupLogTcpdump()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("log_tcpdump", NT_OUTPUT_LOG, LogTcpdumpInit);

#ifdef DEBUG
    printf("Output plugin: Log-Tcpdump is setup...\n");
#endif
}


/*
 * Function: LogTcpdumpInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void LogTcpdumpInit(u_char *args)
{
    LogTcpdumpData *data;
#ifdef DEBUG
    printf("Output: Log-Tcpdump Initialized\n");
#endif

    /* tell command line loggers to go away */
    pv.log_plugin_active = 1;

    /* parse the argument list from the rules file */
    data = ParseTcpdumpArgs(args);

    TcpdumpInitLogFile(data);

    /* Set the preprocessor function into the function list */
    AddFuncToOutputList(LogTcpdump, NT_OUTPUT_LOG, data);
    AddFuncToCleanExitList(SpoLogTcpdumpCleanExitFunc, data);
    AddFuncToRestartList(SpoLogTcpdumpRestartFunc, data);
}



/*
 * Function: ParseTcpdumpArgs(char *)
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
LogTcpdumpData *ParseTcpdumpArgs(char *args)
{
    LogTcpdumpData *data;

    data = (LogTcpdumpData *)malloc(sizeof(LogTcpdumpData));

#ifdef DEBUG
    printf("Args: %s<>\n", args);
#endif

    if(args != NULL)
    {
        while(isspace((int)*args)) args++;
        if(strcmp(args, "") != 0)
            data->filename = strdup(args);
        else
            data->filename = strdup("snort.log");
    }
    else
    {
        data->filename = strdup("snort.log");
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
 */
void LogTcpdump(Packet *p, char *msg, void *arg)
{
    LogTcpdumpData *data = (LogTcpdumpData *)arg;

    if(p)
    {
        data->log_written = 1;
        /* sizeof(struct pcap_pkthdr) = 16 bytes */
        pcap_dump((u_char *)data->dumpd,p->pkth,p->pkt);
        fflush((FILE *)data->dumpd);
    }
    else
    {
        /* we don't want to miss log message from portscan and other modules which don't
       log packet data. */
        ErrorMessage("LOG: %s\n", msg);
    }
}


/*
 * Function: TcpdumpInitLogFile()
 *
 * Purpose: Initialize the tcpdump log file header
 *
 * Arguments: data => pointer to the plugin's reference data struct 
 *
 * Returns: void function
 */
void TcpdumpInitLogFile(LogTcpdumpData *data)
{
    time_t curr_time;      /* place to stick the clock data */
    struct tm *loc_time;   /* place to stick the adjusted clock data */
    char timebuf[10];
    char logdir[STD_BUF];
    int value;

    bzero(logdir, STD_BUF);
    bzero(timebuf, 10);
    curr_time = time(NULL);
    loc_time = localtime(&curr_time);
    strftime(timebuf,91,"%m%d@%H%M",loc_time);

    if(data->filename[0] == '/')
        value = snprintf(logdir, STD_BUF, "%s%s", 
                chrootdir == NULL ? "" : chrootdir, data->filename);
    else
        value = snprintf(logdir, STD_BUF, "%s%s/%s-%s",
               chrootdir == NULL ? "" : chrootdir, pv.log_dir, timebuf, 
               data->filename);

       if(value == -1)
        FatalError("ERROR: log file logging path and file name are too long, aborting!\n");

#ifdef DEBUG
    printf("Opening %s\n", logdir);
#endif

    if((data->dumpd=pcap_dump_open(pd,logdir)) == NULL)
    {
        FatalError("log_tcpdump TcpdumpInitLogFile(): %s\n", strerror(errno));
    }

    /* keep a copy of the filename for later reference */
    if(data->filename != NULL)
    {
        free(data->filename);

        data->filename = strdup(logdir);
    }

    return;
}



/*
 * Function: SpoLogTcpdumpCleanExitFunc()
 *
 * Purpose: Cleanup at exit time
 *
 * Arguments: signal => signal that caused this event
 *            arg => data ptr to reference this plugin's data
 *
 * Returns: void function
 */
void SpoLogTcpdumpCleanExitFunc(int signal, void *arg)
{
    /* cast the arg pointer to the proper type */
    LogTcpdumpData *data = (LogTcpdumpData *)arg;

#ifdef DEBUG
    printf("SpoLogTcpdumpCleanExitFunc\n");
#endif

    /* close the output file */
    pcap_dump_close(data->dumpd);   

    /* 
     * if we haven't written any data, dump the output file so there aren't
     * fragments all over the disk 
     */
    if(pc.alert_pkts==0 && pc.log_pkts==0)
    {
        unlink(data->filename);
    }

    /* free up initialized memory */
    free(data->filename);
    free(data);
}



/*
 * Function: SpoLogTcpdumpRestartFunc()
 *
 * Purpose: For restarts (SIGHUP usually) clean up structs that need it
 *
 * Arguments: signal => signal that caused this event
 *            arg => data ptr to reference this plugin's data
 *
 * Returns: void function
 */
void SpoLogTcpdumpRestartFunc(int signal, void *arg)
{
    LogTcpdumpData *data = (LogTcpdumpData *)arg;

#ifdef DEBUG
    printf("SpoLogTcpdumpRestartFunc\n");
#endif

    pcap_dump_close(data->dumpd);   

    /* 
     * if we haven't written any data, dump the output file so there aren't
     * fragments all over the disk 
     */
    if(pc.alert_pkts==0 && pc.log_pkts==0)
    {
        unlink(data->filename);
    }

    free(data->filename);
    free(data->dumpd);
    free(data);
}

