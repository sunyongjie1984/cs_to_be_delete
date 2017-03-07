/* $Id: plugbase.c,v 1.18 2001/01/17 03:19:01 roesch Exp $ */
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

#include "plugbase.h"

KeywordXlateList *KeywordList;
PreprocessKeywordList *PreprocessKeywords;
PreprocessFuncNode *PreprocessList;
OutputKeywordList *OutputKeywords;
OutputFuncNode *AlertList;
OutputFuncNode *LogList;
PluginSignalFuncNode *PluginCleanExitList;
PluginSignalFuncNode *PluginRestartList;

extern int file_line;
extern char *file_name;

void InitPlugIns()
{
    if(!pv.quiet_flag)
    {
        printf("Initializing Plug-ins!\n");
    }
    SetupPatternMatch();
    SetupTCPFlagCheck();
    SetupIcmpTypeCheck();
    SetupIcmpCodeCheck();
    SetupTtlCheck();
    SetupIpIdCheck();
    SetupTcpAckCheck();
    SetupTcpSeqCheck();
    SetupDsizeCheck();
    SetupIpOptionCheck();
    SetupRpcCheck();
    SetupIcmpIdCheck();
    SetupIcmpSeqCheck();
    SetupSession();
    SetupReact();
    SetupIpTosCheck();
    SetupReference();
    SetupFragBits();
#ifdef ENABLE_RESPONSE
    SetupRespond();
#endif

}


void InitPreprocessors()
{
    if(!pv.quiet_flag)
    {
        printf("Initializing Preprocessors!\n");
    }
    SetupHttpDecode();
    SetupMinfrag();
    SetupPortscan();
    SetupPortscanIgnoreHosts();
    SetupDefrag();
    SetupTcpStream();
    SetupSpade();
}



void InitOutputPlugins()
{
    if(!pv.quiet_flag)
    {
        printf("Initializating Output Plugins!\n");
    }
    SetupAlertSyslog();
    SetupLogTcpdump();
    SetupDatabase();
    SetupFastAlert();
    SetupFullAlert();
#ifdef ENABLE_SMB_ALERTS
    SetupAlertSmb();
#endif
    SetupAlertUnixSock();
    SetupXml();
}


/****************************************************************************
 *
 * Function: RegisterPlugin(char *, void (*func)())
 *
 * Purpose:  Associates a rule option keyword with an option setup/linking
 *           function.
 *
 * Arguments: keyword => The option keyword to associate with the option
 *                       handler
 *            *func => function pointer to the handler
 *
 * Returns: void function
 *
 ***************************************************************************/
void RegisterPlugin(char *keyword, void (*func) (char *, OptTreeNode *, int))
{
    KeywordXlateList *idx;

#ifdef DEBUG
    printf("Registering keyword:func => %s:%p\n", keyword, func);
#endif

    idx = KeywordList;

    if(idx == NULL)
    {
        KeywordList = (KeywordXlateList *) calloc(sizeof(KeywordXlateList), sizeof(char));

        KeywordList->entry.keyword = (char *) calloc(strlen(keyword) + 1, sizeof(char));
        strncpy(KeywordList->entry.keyword, keyword, strlen(keyword)+1);
        KeywordList->entry.func = func;
    }
    else
    {
        /* go to the end of the list */
        while(idx->next != NULL)
        {
            if(!strncasecmp(idx->entry.keyword, keyword, strlen(keyword)))
            {
                FatalError("ERROR %s (%d) => Duplicate detection plugin keyword!\n", file_name, file_line);
            }
            idx = idx->next;
        }

        idx->next = (KeywordXlateList *) calloc(sizeof(KeywordXlateList), sizeof(char));

        idx = idx->next;

        idx->entry.keyword = (char *) calloc(strlen(keyword) + 1, sizeof(char));
        strncpy(idx->entry.keyword, keyword, strlen(keyword)+1);
        idx->entry.func = func;
    }
}




/****************************************************************************
 *
 * Function: DumpPlugIns()
 *
 * Purpose:  Prints the keyword->function list
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ***************************************************************************/
void DumpPlugIns()
{
    KeywordXlateList *idx;

    if(pv.quiet_flag)
        return;

    idx = KeywordList;

    printf("-------------------------------------------------\n");
    printf(" Keyword     |      Plugin Registered @\n");
    printf("-------------------------------------------------\n");
    while(idx != NULL)
    {
        printf("%-13s:      %p\n", idx->entry.keyword, idx->entry.func);
        idx = idx->next;
    }
    printf("-------------------------------------------------\n\n");
}



/****************************************************************************
 *
 * Function: RegisterPreprocessor(char *, void (*func)(u_char *))
 *
 * Purpose:  Associates a preprocessor statement with its function.
 *
 * Arguments: keyword => The option keyword to associate with the
 *                       preprocessor
 *            *func => function pointer to the handler
 *
 * Returns: void function
 *
 ***************************************************************************/
void RegisterPreprocessor(char *keyword, void (*func) (u_char *))
{
    PreprocessKeywordList *idx;

#ifdef DEBUG
    printf("Registering keyword:preproc => %s:%p\n", keyword, func);
#endif

    idx = PreprocessKeywords;

    if(idx == NULL)
    {
        /* alloc the node */
        PreprocessKeywords = (PreprocessKeywordList *) calloc(sizeof(PreprocessKeywordList), sizeof(char));

        /* alloc space for the keyword */
        PreprocessKeywords->entry.keyword = (char *) calloc(strlen(keyword) + 1, sizeof(char));

        /* copy the keyword into the struct */
        strncpy(PreprocessKeywords->entry.keyword, keyword, strlen(keyword)+1);

        /* set the function pointer to the keyword handler function */
        PreprocessKeywords->entry.func = (void *) func;
    }
    else
    {
        /* loop to the end of the list */
        while(idx->next != NULL)
        {
            if(!strncasecmp(idx->entry.keyword, keyword, strlen(keyword)))
            {
                FatalError("ERROR %s (%d) => Duplicate preprocessor keyword!\n", file_name, file_line);
            }
            idx = idx->next;
        }

        idx->next = (PreprocessKeywordList *) calloc(sizeof(PreprocessKeywordList), sizeof(char));

        idx = idx->next;

        /* alloc space for the keyword */
        idx->entry.keyword = (char *) calloc(strlen(keyword) + 1, sizeof(char));

        /* copy the keyword into the struct */
        strncpy(idx->entry.keyword, keyword, strlen(keyword)+1);

        /* set the function pointer to the keyword handler function */
        idx->entry.func = (void *) func;
    }
}




/****************************************************************************
 *
 * Function: DumpPreprocessors()
 *
 * Purpose:  Prints the keyword->preprocess list
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ***************************************************************************/
void DumpPreprocessors()
{
    PreprocessKeywordList *idx;

    if(pv.quiet_flag)
        return;
    idx = PreprocessKeywords;

    printf("-------------------------------------------------\n");
    printf(" Keyword     |       Preprocessor @ \n");
    printf("-------------------------------------------------\n");
    while(idx != NULL)
    {
        printf("%-13s:       %p\n", idx->entry.keyword, idx->entry.func);
        idx = idx->next;
    }
    printf("-------------------------------------------------\n\n");
}



/****************************************************************************
 *
 * Function: RegisterOutputPlugin(char *, void (*func)(Packet *, u_char *))
 *
 * Purpose:  Associates an output statement with its function.
 *
 * Arguments: keyword => The output keyword to associate with the
 *                       output processor
 *            type => alert or log types
 *            *func => function pointer to the handler
 *
 * Returns: void function
 *
 ***************************************************************************/
void RegisterOutputPlugin(char *keyword, int type, void (*func) (u_char *))
{
    OutputKeywordList *idx;

#ifdef DEBUG
    printf("Registering keyword:output => %s:%p\n", keyword, func);
#endif

    idx = OutputKeywords;

    if(idx == NULL)
    {
        /* alloc the node */
        OutputKeywords = (OutputKeywordList *) calloc(sizeof(OutputKeywordList), sizeof(char));

        idx = OutputKeywords;
    }
    else
    {
        /* loop to the end of the list */
        while(idx->next != NULL)
        {
            if(!strncasecmp(idx->entry.keyword, keyword, strlen(keyword)))
            {
                FatalError("ERROR %s (%d) => Duplicate output keyword!\n", file_name, file_line);
            }
            idx = idx->next;
        }

        idx->next = (OutputKeywordList *) calloc(sizeof(OutputKeywordList), sizeof(char));

        idx = idx->next;
    }

    /* alloc space for the keyword */
    idx->entry.keyword = (char *) calloc(strlen(keyword) + 1, sizeof(char));

    /* copy the keyword into the struct */
    strncpy(idx->entry.keyword, keyword, strlen(keyword)+1);

    /*
     * set the plugin type, needed to determine whether an overriding command
     * line arg has been specified
     */
    idx->entry.node_type = type;

    /* set the function pointer to the keyword handler function */
    idx->entry.func = (void *) func;
}




/****************************************************************************
 *
 * Function: DumpOutputPlugins()
 *
 * Purpose:  Prints the keyword->preprocess list
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ***************************************************************************/
void DumpOutputPlugins()
{
    OutputKeywordList *idx;

    if(pv.quiet_flag)
        return;

    idx = OutputKeywords;

    printf("-------------------------------------------------\n");
    printf(" Keyword     |          Output @ \n");
    printf("-------------------------------------------------\n");
    while(idx != NULL)
    {
        printf("%-13s:       %p\n", idx->entry.keyword, idx->entry.func);
        idx = idx->next;
    }
    printf("-------------------------------------------------\n\n");
}


int PacketIsIP(Packet * p)
{
    if(p->iph != NULL)
        return 1;

    return 0;
}



int PacketIsTCP(Packet * p)
{
    if(p->iph != NULL && p->tcph != NULL)
        return 1;

    return 0;
}



int PacketIsUDP(Packet * p)
{
    if(p->iph != NULL && p->udph != NULL)
        return 1;

    return 0;
}



int PacketIsICMP(Packet * p)
{
    if(p->iph != NULL && p->icmph != NULL)
        return 1;

    return 0;
}



int DestinationIpIsHomenet(Packet * p)
{
    if((p->iph->ip_dst.s_addr & pv.netmask) == pv.homenet)
    {
        return 1;
    }
    return 0;
}



int SourceIpIsHomenet(Packet * p)
{
    if((p->iph->ip_src.s_addr & pv.netmask) == pv.homenet)
    {
        return 1;
    }
    return 0;
}


int IsTcpSessionTraffic(Packet * p)
{
    if(p->tcph == NULL)
        return 0;

    if(p->tcph->th_flags != (TH_PUSH | TH_ACK))
    {
        return 0;
    }
    return 1;
}


int CheckNet(struct in_addr * compare, struct in_addr * compare2)
{
    if(compare->s_addr == compare2->s_addr)
    {
        return 1;
    }
    return 0;
}

/* functions to aid in cleaning up aftre plugins */
void AddFuncToRestartList(void (*func) (int, void *), void *arg)
{
    PluginRestartList = AddFuncToSignalList(func, arg, PluginRestartList);
}

void AddFuncToCleanExitList(void (*func) (int, void *), void *arg)
{
    PluginCleanExitList = AddFuncToSignalList(func, arg, PluginCleanExitList);
}

PluginSignalFuncNode *AddFuncToSignalList(void (*func) (int, void *), void *arg,
                                          PluginSignalFuncNode * list)
{
    PluginSignalFuncNode *idx;

    idx = list;

    if(idx == NULL)
    {
        idx = (PluginSignalFuncNode *) calloc(sizeof(PluginSignalFuncNode), sizeof(char));

        idx->func = func;
        idx->arg = arg;
        list = idx;
    }
    else
    {
        while(idx->next != NULL)
            idx = idx->next;

        idx->next = (PluginSignalFuncNode *) calloc(sizeof(PluginSignalFuncNode), sizeof(char));

        idx = idx->next;
        idx->func = func;
        idx->arg = arg;
    }
    idx->next = NULL;

    return list;
}


/****************************************************************************
 *
 * Function: GetUniqueName(char * iface)
 *
 * Purpose: To return a string that has a high probability of being unique
 *          for a given sensor.
 *
 * Arguments: char * iface - The network interface you are sniffing
 *
 * Returns: A char * -- its a static char * so you should not free it
 *
 ***************************************************************************/
char *GetUniqueName(char * iface)
{
	char * rptr;
#ifdef WIN32
		rptr = GetHostname(); 
#else
    rptr = GetIP(iface); 
    if(rptr == NULL)
    {
        rptr = GetHostname(); 
    }
#endif
    return rptr;
}    

/****************************************************************************
 *
 * Function: GetIP(char * iface)
 *
 * Purpose: To return a string representing the IP address for an interface
 *
 * Arguments: char * iface - The network interface you want to find an IP
 *            address for.
 *
 * Returns: A char * -- make sure you call free on this when you are done
 *          with it.
 *
 ***************************************************************************/
char *GetIP(char * iface)
{
    struct ifreq ifr;
    struct sockaddr_in *addr;
    int s;

    if(iface)
    {
        /* Set up a dummy socket just so we can use ioctl to find the
           ip address of the interface */
        s = socket(PF_INET, SOCK_DGRAM, 0);
        if(s == -1)
        {
            FatalError("Problem establishing socket to find IP address for interface: %s\n", iface);
        }

        strncpy(ifr.ifr_name, iface, strlen(iface) + 1);
#ifndef WIN32
        if(ioctl(s, SIOCGIFADDR, &ifr) < 0) return NULL;
        else
#endif
        {
            addr = (struct sockaddr_in *) &ifr.ifr_broadaddr;
        }
        close(s);

        return str2s(inet_ntoa(addr->sin_addr));
    }
    else
    {
        return "unknown";
    }
}

/****************************************************************************
 *
 * Function: GetHostname()
 *
 * Purpose: To return a string representing the hostname
 *
 * Arguments: None
 *
 * Returns: A static char * representing the hostname. 
 *
 ***************************************************************************/
char *GetHostname()
{
	char *error = "unknown";
#ifdef WIN32
	int buff = 256;

  GetComputerName(error, &buff);
  return error;
#else
    if(getenv("HOSTNAME")) return getenv("HOSTNAME");
    else if(getenv("HOST")) return getenv("HOST");
    else return error;
#endif
}

/****************************************************************************
 *
 * Function: TCPOptionValue(Options *o)
 *
 * Purpose: To return a string representing the code of an TCP option
 *
 * Arguments: An Options struct.
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *TCPOptionCode(Options *o)
{
    char *rval;

    rval = (char *)malloc(SMALLBUFFER);

    switch(o->code)
    {
        case TCPOPT_MAXSEG:
            strncpy(rval, "MSS", SMALLBUFFER);
            break;

        case TCPOPT_EOL:
            strncpy(rval, "EOL", SMALLBUFFER);
            break;

        case TCPOPT_NOP:
            strncpy(rval, "NOP", SMALLBUFFER);
            break;

        case TCPOPT_WSCALE:
            strncpy(rval, "WS", SMALLBUFFER);
            break;

        case TCPOPT_SACK:
            strncpy(rval, "Sack", SMALLBUFFER);
            break;

        case TCPOPT_SACKOK:
            strncpy(rval, "SackOK", SMALLBUFFER);
            break;

        case TCPOPT_ECHO:
            strncpy(rval, "Echo", SMALLBUFFER);
            break;

        case TCPOPT_ECHOREPLY:
            strncpy(rval, "Echo Rep", SMALLBUFFER);
            break;

        case TCPOPT_TIMESTAMP:
            strncpy(rval, "TS", SMALLBUFFER);
            break;

        case TCPOPT_CC:
            strncpy(rval, "CC", SMALLBUFFER);
            break;

        case TCPOPT_CCNEW:
            strncpy(rval, "CCNEW", SMALLBUFFER);
            break;

        case TCPOPT_CCECHO:
            strncpy(rval, "CCECHO", SMALLBUFFER);
            break;

        default:
            snprintf(rval, SMALLBUFFER, "Opt %d", o->code);
            break;
    }

    return rval;
}

/****************************************************************************
 *
 * Function: TCPOptionValue(Options *o)
 *
 * Purpose: To return a string representing the value of an TCP option
 *
 * Arguments: An Options struct.
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *TCPOptionValue(Options *o)
{
    char * rval;
    char * rvalptr;
    u_char tmp[5];
    int x;

    rval = (char *)malloc(SMALLBUFFER);
    rvalptr = rval;

    switch(o->code)
    {
        case TCPOPT_MAXSEG:
            bzero((char *)tmp, 5);
            strncpy(tmp, o->data, 2); 
            snprintf(rval, SMALLBUFFER, "%u", EXTRACT_16BITS(tmp));
            break;

        case TCPOPT_EOL:
            rval[0] = '\0';
            break;

        case TCPOPT_NOP:
            rval[0] = '\0';
            break;

        case TCPOPT_WSCALE:
            snprintf(rval, SMALLBUFFER, "%u", o->data[0]);
            break;

        case TCPOPT_SACK:
            bzero((char *)tmp, 5);
            memcpy(tmp, o->data, 2);
            snprintf(rval, SMALLBUFFER, "%u@", EXTRACT_16BITS(tmp));
            x = strlen(rval);
            rvalptr += x;
            bzero((char *)tmp, 5);
            memcpy(tmp, (o->data)+2, 2);
            snprintf(rvalptr, SMALLBUFFER - x, "%u", EXTRACT_16BITS(tmp));
            break;

        case TCPOPT_SACKOK:
            rval[0] = '\0';
            break;

        case TCPOPT_ECHO:
            bzero((char *)tmp, 5);
            memcpy(tmp, o->data, 4);
            snprintf(rval, SMALLBUFFER, "%u", EXTRACT_32BITS(tmp));
            break;

        case TCPOPT_ECHOREPLY:
            bzero((char *)tmp, 5);
            memcpy(tmp, o->data, 4);
            snprintf(rval, SMALLBUFFER, "%u", EXTRACT_32BITS(tmp));
            break;

        case TCPOPT_TIMESTAMP:
            bzero((char *)tmp, 5);
            memcpy(tmp, o->data, 4);
            snprintf(rval, SMALLBUFFER, "%u ", EXTRACT_32BITS(tmp));
            rvalptr += strlen(rval);
            bzero((char *)tmp, 5);
            memcpy(tmp, (o->data)+4, 4);
            snprintf(rvalptr, SMALLBUFFER, "%u", EXTRACT_32BITS(tmp));
            break;

        case TCPOPT_CC:
            bzero((char *)tmp, 5);
            memcpy(tmp, o->data, 4);
            snprintf(rval, SMALLBUFFER, "%u", EXTRACT_32BITS(tmp));
            break;

        case TCPOPT_CCNEW:
            bzero((char *)tmp, 5);
            memcpy(tmp, o->data, 4);
            snprintf(rval, SMALLBUFFER, "%u", EXTRACT_32BITS(tmp));
            break;

        case TCPOPT_CCECHO:
            bzero((char *)tmp, 5);
            memcpy(tmp, o->data, 4);
            snprintf(rval, SMALLBUFFER, "%u", EXTRACT_32BITS(tmp));
            break;

        default:
            rval[0] = '\0';
            if(o->len > 2)
            {
                for(x = 0; x < (int)(o->len-2); x+=2)
                {
                    snprintf(tmp, 5, "%02X%02X ", o->data[x], o->data[x+1]);
                    if(strlen(rval) < SMALLBUFFER - 5);
                    strncat(rval, tmp, SMALLBUFFER - strlen(rval));
                }
            }
            break;
    }
    return rval;
}

/****************************************************************************
 *
 * Function: IPOptionValue(Options *o)
 *
 * Purpose: To return a string representing the code of an IP option
 *
 * Arguments: An Options struct.
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *IPOptionCode(Options * o)
{
    char *rval;

    rval = (char *)malloc(SMALLBUFFER);

    switch(o->code)
    {
        case IPOPT_RR:
            strncpy(rval, "RR", SMALLBUFFER);
            break;

        case IPOPT_EOL:
            strncpy(rval, "EOL", SMALLBUFFER);
            break;

        case IPOPT_NOP:
            strncpy(rval, "NOP", SMALLBUFFER);
            break;

        case IPOPT_TS:
            strncpy(rval, "TS", SMALLBUFFER);
            break;

        case IPOPT_SECURITY:
            strncpy(rval, "SEC", SMALLBUFFER);
            break;

        case IPOPT_LSRR:
        case IPOPT_LSRR_E:
            strncpy(rval, "LSRR", SMALLBUFFER);
            break;

        case IPOPT_SATID:
            strncpy(rval, "SID", SMALLBUFFER);
            break;

        case IPOPT_SSRR:
            strncpy(rval, "SSRR", SMALLBUFFER);
            break;

        default:
            snprintf(rval, SMALLBUFFER, "Opt %d", o->code);
    } 
    return rval;
}

/****************************************************************************
 *
 * Function: IPOptionValue(Options *o)
 *
 * Purpose: To return a string representing the value of an IP option
 *
 * Arguments: An Options struct.
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *IPOptionValue(Options * o)
{
    int j;
    char *rval;
    char tmp[6];

    rval = (char *)malloc(SMALLBUFFER);
    rval[0] = '\0';

    if(o->len)
    {
        for(j = 0; j < (int)(o->len-2); j+=2)
        {
            rval = (char *)realloc(rval, strlen(rval) + 5);
            snprintf(tmp, 5, "%02X%02X ", o->data[j], o->data[j+1]);
            strncat(rval, tmp, 6);
        }
    }

    return rval;
}

/****************************************************************************
 *
 * Function: GetTimestamp(time_t * tv_sec, int tz)
 *
 * Purpose: Get an ISO-8601 formatted timestamp for tv_sec within the tz
 *          timezone. 
 *
 * Arguments: tv_sec is a time_t pointer. tz is a timezone. 
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *GetTimestamp(time_t * tv_sec, int tz)
{
    struct tm *time;
    char * buf;

    buf = (char *)malloc(SMALLBUFFER);

    if(pv.use_utc == 1)
        time = gmtime(tv_sec);
    else
        time = localtime(tv_sec);

    if(tz < 0)
        snprintf(buf, SMALLBUFFER, "%04i-%02i-%02i %02i:%02i:%02i%03i", 1900 + time->tm_year, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec, tz);
    else
        snprintf(buf, SMALLBUFFER, "%04i-%02i-%02i %02i:%02i:%02i+%02i", 1900 + time->tm_year, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec, tz);

    return buf;
}

/****************************************************************************
 *
 * Function: GetLocalTimezone()
 *
 * Purpose: Find the offset from GMT for current host
 *
 * Arguments: none 
 *
 * Returns: int representing the offset from GMT
 *
 ***************************************************************************/
int GetLocalTimezone()
{
    struct timezone tz;
    struct timeval tv;

    gettimeofday(&tv,&tz);

    if(tz.tz_minuteswest > 720) return(24 - tz.tz_minuteswest/60);
    else          return(0 - tz.tz_minuteswest/60);
}

/****************************************************************************
 *
 * Function: GetCurrentTimestamp()
 *
 * Purpose: Generate an ISO-8601 formatted timestamp for the current time.
 *
 * Arguments: none 
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *GetCurrentTimestamp()
{
    struct tm *lt;
    struct timezone tz;
    struct timeval tv;
    struct timeval *tvp;
    char * buf;
    int tzone;

    buf = (char *)malloc(SMALLBUFFER);

    bzero((char *)&tz,sizeof(tz));
    gettimeofday(&tv,&tz);
    tvp = &tv;

    if(pv.use_utc == 1)
    {
        lt = gmtime((time_t *)&tvp->tv_sec);
        snprintf(buf, SMALLBUFFER, "%04i-%02i-%02i %02i:%02i:%02i", 
                1900 + lt->tm_year, lt->tm_mon + 1, lt->tm_mday, 
                lt->tm_hour, lt->tm_min, lt->tm_sec);
    }
    else
    {
        lt = localtime((time_t *)&tvp->tv_sec);

    	tzone = GetLocalTimezone();

        if(tzone < 0)
            snprintf(buf, SMALLBUFFER, 
                    "%04i-%02i-%02i %02i:%02i:%02i%03i", 
                    1900 + lt->tm_year, lt->tm_mon + 1, lt->tm_mday, 
                    lt->tm_hour, lt->tm_min, lt->tm_sec, tzone);
        else
            snprintf(buf, SMALLBUFFER, 
                    "%04i-%02i-%02i %02i:%02i:%02i+%02i", 
                    1900 + lt->tm_year, lt->tm_mon + 1, lt->tm_mday, 
                    lt->tm_hour, lt->tm_min, lt->tm_sec, tzone);
    }

    return buf;
}

/*
 * Function: base64(char * xdata, int length)
 *
 * Purpose: Insert data into the database
 *
 * Arguments: xdata  => pointer to data to base64 encode
 *            length => how much data to encode 
 *
 * Make sure you allocate memory for the output before you pass
 * the output pointer into this function. You should allocate 
 * (1.5 * length) bytes to be safe.
 *
 * Returns: data base64 encoded as a char *
 *
 */
char * base64(u_char * xdata, int length)
{
    int count, cols, bits, c, char_count;
    unsigned char alpha[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char * payloadptr;
    char * output;
    char_count = 0;
    bits = 0;
    cols = 0;

    output = (char *)malloc((unsigned int)(length * 1.5 + 4));

    payloadptr = output;

    for(count = 0; count < length; count++)
    {
        c = xdata[count];

        if(c > 255)
        {
            ErrorMessage("plugbase.c->base64(): encountered char > 255 (decimal %d)\n If you see this error message a char is more than one byte on your machine\n This means your base64 results can not be trusted", c);
        }

        bits += c;
        char_count++;

        if(char_count == 3)
        {
            *output = alpha[bits >> 18]; output++;
            *output = alpha[(bits >> 12) & 0x3f]; output++;
            *output = alpha[(bits >> 6) & 0x3f]; output++;
            *output = alpha[bits & 0x3f]; output++; 
            cols += 4;
            if(cols == 72)
            {
                *output = '\n'; output++;
                cols = 0;
            }
            bits = 0;
            char_count = 0;
        }
        else
        {
            bits <<= 8;
        }
    }

    if(char_count != 0)
    {
        bits <<= 16 - (8 * char_count);
        *output = alpha[bits >> 18]; output++;
        *output = alpha[(bits >> 12) & 0x3f]; output++;
        if(char_count == 1)
        {
            *output = '='; output++;
            *output = '='; output++;
        }
        else
        {
            *output = alpha[(bits >> 6) & 0x3f]; 
            output++; *output = '='; 
            output++;
        }
    }
    *output = '\0';
    return payloadptr;
} 

/****************************************************************************
 *
 * Function: ascii(u_char *xdata, int length)
 *
 * Purpose: This function takes takes a buffer "xdata" and its length then
 *          returns a string of only the printible ASCII characters.
 *
 * Arguments: xdata is the buffer, length is the length of the buffer in
 *            bytes
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *ascii(u_char *xdata, int length)
{
    int x;
    int y;
    char *ret;
    char *buf;

    buf = (char *)malloc((unsigned int)(length * 1.1 + 2));

    ret = buf;

    y = 0;

    for(x = 0; ((x < length) && (x + y + 4 < length * 1.1)); x++)
    {
        if((xdata[x] > 0x1F) && (xdata[x] < 0x7F))
        {
            if(xdata[x] == '<')
            {
                *buf = '&'; buf++; y++;
                *buf = 'l'; buf++; y++;
                *buf = 't'; buf++; y++;
                *buf = ';';
            }
            else if(xdata[x] == '&')
            {
                *buf = '&'; buf++; y++;
                *buf = 'a'; buf++; y++;
                *buf = 'm'; buf++; y++;
                *buf = 'p'; buf++; y++;
                *buf = ';'; 
            }
            else if(xdata[x] == '>')
            {
                *buf = '&'; buf++; y++;
                *buf = 'g'; buf++; y++;
                *buf = 't'; buf++; y++;
                *buf = ';';
            }
            else if(xdata[x] == '\'')
            {
                *buf = '\\'; buf++; y++;
                *buf = '\'';
            }
            else
            {
                *buf = xdata[x];
            }
            buf++;
        }
        else
        {
            *buf = '.'; buf++;
        }
    }

    *buf = '\0';
    return ret;
}

/****************************************************************************
 *
 * Function: hex(u_char *xdata, int length)
 *
 * Purpose: This function takes takes a buffer "xdata" and its length then
 *          returns a string of hex with no spaces
 *
 * Arguments: xdata is the buffer, length is the length of the buffer in
 *            bytes
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *hex(u_char *xdata, int length)
{
    int x;
    char *rval;
    char *buf;

    buf = (char *)malloc(length * 2 + 1);
    rval = buf;

    for(x=0; x < length; x++)
    {
        snprintf(buf, 3, "%02X", xdata[x]);
        buf += 2;
    } 

    rval[length * 2] = '\0';

    return rval;
}


/****************************************************************************
 *
 * Function: int2s(int val)
 *
 * Purpose:  int2s creates a string representing the integer supplied as
 *           the first argument. It returns a char * that needs to be freed
 *           after it is used. 
 *
 * Arguments: val is the integer you want to convert to a string
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *int2s(int val)
{
    char * ptr;

    ptr = (char *)malloc(SMALLBUFFER);

    if(val)
    {
        snprintf(ptr, SMALLBUFFER, "%u", val);
    }
    else
    {
        ptr[0] = '\0';
    }
    return ptr;
}


/****************************************************************************
 *
 * Function: str2s(char * val)
 *
 * Purpose: str2s returns a string that is an exact replica of the char 
 *          supplied as the first argument. The purpose of this
 *          function is to create a dynamically allocated copy of a
 *          string. It is used when populating data structures that
 *          have char * elements that are freed. The point is that
 *          this is a short way to avoid calling free() on a buffer
 *          that is not dynamically allocated by this process. 
 *
 * Arguments: val is the string you want to copy 
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *str2s(char * val)
{
    char * ptr;

    if(val)
    {
        ptr = (char *)malloc(strlen(val) + 1);
        strncpy(ptr, val, strlen(val) + 1);
        return ptr;
    }
    else
    {
        return val;
    }
}

/****************************************************************************
 *
 * Function: hex2s(int val)
 *
 * Purpose:  hex2s creates a string representing the hexidecimal conversion
 *           of an integer. It returns a char * that needs to be freed after
 *           it is used. 
 *
 * Arguments: val is the integer you want to convert to a string
 *
 * Returns: char * -- You must free this char * when you are done with it.
 *
 ***************************************************************************/
char *hex2s(int val)
{
    char * ptr;

    ptr = (char *)malloc(SMALLBUFFER);

    if(val)
    {
        snprintf(ptr, SMALLBUFFER, "0x%x", val);
    }
    else
    {
        ptr[0] = '\0';
    }
    return ptr;
}
