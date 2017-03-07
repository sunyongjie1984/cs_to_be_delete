/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 2000,2001 Andrew R. Baker <andrewb@uab.edu>
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

/* spo_alert_smb
 * 
 * Purpose:  output plugin for smb alerting
 *
 * Arguments:  workstations file
 *   
 * Effect:
 *
 * Alerts are sent to each workstation in the workstations file via WinPopup
 *
 * Comments:  Requires smbclient to be in PATH
 *
 */

/* output plugin header file */
#include "spo_alert_smb.h"
#ifdef ENABLE_SMB_ALERTS
/* external globals from rules.c */
extern char *file_name;
extern int file_line;

/*
 * Function: SetupAlertSmb()
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
void SetupAlertSmb()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("alert_smb", NT_OUTPUT_ALERT, AlertSmbInit);

#ifdef DEBUG
    printf("Output plugin: AlertSmb is setup...\n");
#endif
}


/*
 * Function: AlertSmbInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void AlertSmbInit(u_char *args)
{
    SpoAlertSmbData *data;
#ifdef DEBUG
    printf("Output: AlertSmb Initialized\n");
#endif

    pv.alert_plugin_active = 1;

    /* parse the argument list from the rules file */
    data = ParseAlertSmbArgs(args);


#ifdef DEBUG
    printf("Linking SmbAlert functions to call lists...\n");
#endif

    /* Set the preprocessor function into the function list */
    AddFuncToOutputList(SpoAlertSmb, NT_OUTPUT_ALERT, data);
    AddFuncToCleanExitList(SpoAlertSmbCleanExitFunc, data);
    AddFuncToRestartList(SpoAlertSmbRestartFunc, data);
}


/*
 * Function: ParseAlertSmbArgs(char *)
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
 * Notes:	code adapted from ParseTcpdumpArgs in spo_log_tcpdump.c
 */
SpoAlertSmbData *ParseAlertSmbArgs(char *args)
{
    SpoAlertSmbData *data;

#ifdef DEBUG
    printf("ParseAlertSmbArgs: %s\n", args);
#endif

    data = (SpoAlertSmbData *) malloc(sizeof(SpoAlertSmbData));

    if(args != NULL)
    {
        while(isspace((int)*args)) args++;
        data->filename = (char *) calloc(strlen(args) + 1, sizeof(char));
        if(data->filename == NULL)
        {
            FatalError("ParseAlertSmbArgs() filename calloc failed: %s\n",
                       strerror(errno));
        }

        strncpy(data->filename, args, strlen(args)+1);
    }
    else
    {
        FatalError("Error line %s (%d): No filename for AlertSmb\n",
                   file_name, file_line);
    }

    return data;
}

/****************************************************************************
 *
 * Function: SmbAlert(Packet *, char *)
 *
 * Purpose: Send the current alert to a waiting WinPopup client
 *
 * Arguments: p => pointer to the packet data struct
 *            msg => the message to print in the alert
 *
 * Returns: void function
 *
 ***************************************************************************/
void SpoAlertSmb(Packet *p, char *msg, void *arg)
{
    char command_line[2048];
    FILE *output;
    FILE *workstations;
    char *tempmsg;
    char tempwork[STD_BUF];
    char timestamp[23];
    char sip[16];
    char dip[16];
    int msg_str_size;
    SpoAlertSmbData *data = (SpoAlertSmbData *)arg;

    bzero((char *)timestamp, 23);

    ts_print(p==NULL?NULL:(struct timeval *)&p->pkth->ts, timestamp);


#ifdef DEBUG
    printf("Generating SMB alert!\n");
#endif

    /* message size + IP addrs + ports + pad space */  
    msg_str_size = strlen(msg) + 32 + 10 + 150;

    if((tempmsg = (char *) calloc(msg_str_size, sizeof(char))) == NULL)
    {
        FatalError("[!] ERROR: SmbAlert() unable to allocate space for tempmsg: %s\n", strerror(errno));
    }

    /* open the message file and the workstation names file */
    if((workstations = fopen(data->filename,"r")) != NULL)
    {
        if(p != NULL)
        {
            strncpy(sip, inet_ntoa(p->iph->ip_src), 16);
            strncpy(dip, inet_ntoa(p->iph->ip_dst), 16);
            if(p->frag_flag || p->iph->ip_proto)
            {
                /* write the alert message into the buffer */
                sprintf(tempmsg, "SNORT ALERT - Possible Network Attack or Probe:\n [**] %s [**]\n%s %s->%s", msg, timestamp, sip, dip);
            }
            else
            {
                /* write the alert message into the buffer */
                sprintf(tempmsg, "SNORT ALERT - Possible Network Attack or Probe:\n [**] %s [**]\n%s %s:%d->%s:%d", msg, timestamp, sip, p->sp, dip, p->dp);
            }
        }
        else
        {
            /* write the alert message into the buffer - this part is for alerts with NULL packets (like portscans)*/
            sprintf(tempmsg, "SNORT ALERT - Possible Network Attack or Probe:\n [**] %s [**]\n", msg);
        }

        bzero((char *)tempwork, STD_BUF);
        bzero((char *)command_line, 2048);

        /* read in the name of each workstation to send the message to */
        while((fgets(tempwork, STD_BUF-1, workstations)) != NULL)
        {
            /* if the line isn't blank */
            if(tempwork[0] != 0x0A)
            {
                /* chop the <CR> */
                strip(tempwork);

                if(strlen(tempmsg) + strlen(tempwork) + 50 < 2048)
                {
                    /* build the command line */
                    sprintf(command_line, "echo \"%s\" | smbclient -U Snort -M %s", tempmsg, tempwork);

                    /* run the command */
                    output = popen(command_line,"r");

                    pclose(output);
                }
                else
                {
                    ErrorMessage("[!] WARNING: Unable to send alert to %s, command buffer size exceeded!\n", tempwork);
                }

#ifdef DEBUG
                printf("Sending WinPopup alert to: %s\n", tempwork);
                printf("Command Line: %s\n", command_line);
#endif
                bzero((char *)tempwork, STD_BUF);
                bzero((char *)command_line, 2048);
            }
        }

        fclose(workstations);
    }

    free(tempmsg);
}

void SpoAlertSmbCleanExitFunc(int signal, void *arg)
{
    SpoAlertSmbData *data = (SpoAlertSmbData *)arg;
#ifdef DEBUG
    printf("SpoAlertSmbCleanExitFunc\n");
#endif
    /* free memory from SpoAlertSmbData */
    free(data->filename);
    free(data);
}

void SpoAlertSmbRestartFunc(int signal, void *arg)
{
    SpoAlertSmbData *data = (SpoAlertSmbData *)arg;
#ifdef DEBUG
    printf("SpoAlertSmbRestartFunc\n");
#endif
    /* free memory from SpoAlertSmbData */
    free(data->filename);
    free(data);
}
#endif