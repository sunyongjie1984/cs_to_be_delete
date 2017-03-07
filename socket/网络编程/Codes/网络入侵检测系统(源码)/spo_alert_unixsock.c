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

/* spo_alert_unixsock
 * 
 * Purpose:  output plugin for Unix Socket alerting
 *
 * Arguments:  none (yet)
 *   
 * Effect:	???
 *
 */

/* output plugin header file */
#include "spo_alert_unixsock.h"

/* external globals from rules.c */
extern char *file_name;
extern int file_line;

/*
 * Function: SetupAlertUnixSock()
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
void SetupAlertUnixSock()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("alert_unixsock", NT_OUTPUT_ALERT, AlertUnixSockInit);

#ifdef DEBUG
    printf("Output plugin: AlertUnixSock is setup...\n");
#endif
}


/*
 * Function: AlertUnixSockInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void AlertUnixSockInit(u_char *args)
{
#ifdef DEBUG
    printf("Output: AlertUnixSock Initialized\n");
#endif

    pv.alert_plugin_active = 1;

    /* parse the argument list from the rules file */
    ParseAlertUnixSockArgs(args);


#ifdef DEBUG
    printf("Linking UnixSockAlert functions to call lists...\n");
#endif

    /* Set the preprocessor function into the function list */
    AddFuncToOutputList(SpoAlertUnixSock, NT_OUTPUT_ALERT, NULL);
}


/*
 * Function: ParseAlertUnixSockArgs(char *)
 *
 * Purpose: Process the preprocessor arguements from the rules file and 
 *          initialize the preprocessor's data struct.  This function doesn't
 *          have to exist if it makes sense to parse the args in the init 
 *          function.
 *
 * Arguments: args => argument list
 *
 * Returns: void function
 */
void ParseAlertUnixSockArgs(char *args)
{
#ifdef DEBUG
    printf("ParseAlertUnixSockArgs: %s\n", args);
#endif
    /* eventually we may support more than one socket */
    OpenAlertSock();
}

/****************************************************************************
 *
 * Function: SpoUnixSockAlert(Packet *, char *)
 *
 * Arguments: p => pointer to the packet data struct
 *            msg => the message to print in the alert
 *
 * Returns: void function
 *
 ***************************************************************************/
void SpoAlertUnixSock(Packet *p, char *msg, void *arg)
{
    static Alertpkt alertpkt;

#ifdef DEBUG
    printf("Logging Alert data!\n");
#endif

    bzero((char *)&alertpkt,sizeof(alertpkt));
    if(p)
    {
        bcopy((const void *)p->pkth,(void *)&alertpkt.pkth,sizeof(struct pcap_pkthdr));
        bcopy((const void *)p->pkt,alertpkt.pkt,
              alertpkt.pkth.caplen > SNAPLEN? SNAPLEN : alertpkt.pkth.caplen);
    }
    else
        alertpkt.val|=NOPACKET_STRUCT;

    bcopy((const void *)msg,(void *)alertpkt.alertmsg,strlen(msg) > 255 ? 256: strlen(msg)+1);

    /* some data which will help monitoring utility to dissect packet */
    if(!(alertpkt.val & NOPACKET_STRUCT))
    {
        alertpkt.dlthdr=(char *)p->eh-(char *)p->pkt;

        /* we don't log any headers besides eth yet */
        alertpkt.nethdr=(char *)p->iph-(char *)p->pkt;

        switch(p->iph->ip_proto)
        {
            case IPPROTO_TCP:
                alertpkt.transhdr=(char *)p->tcph-(char *)p->pkt;
                break;

            case IPPROTO_UDP:
                alertpkt.transhdr=(char *)p->udph-(char *)p->pkt;
                break;

            case IPPROTO_ICMP:
                alertpkt.transhdr=(char *)p->icmph-(char *)p->pkt;
                break;

            default:
                /* alertpkt.transhdr is null due to initial bzero */
                alertpkt.val|=NO_TRANSHDR;
        }
        alertpkt.data=p->data - p->pkt;
    }


    if(sendto(alertsd,(const void *)&alertpkt,sizeof(Alertpkt),
              0,(struct sockaddr *)&alertaddr,sizeof(alertaddr))==-1)
    {
        /* whatever we do to sign that some alerts could be missed */
    }


}

