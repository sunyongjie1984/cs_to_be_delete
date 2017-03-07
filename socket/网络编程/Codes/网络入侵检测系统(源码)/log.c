/* $Id: log.c,v 1.31 2001/01/26 16:40:44 roesch Exp $ */
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

#include "log.h"

extern OptTreeNode *otn_tmp;    /* global ptr to current rule data */

char *data_dump_buffer;     /* printout buffer for PrintNetData */
int dump_ready;         /* flag to indicate status of printout buffer */
int dump_size;          /* size of printout buffer */

static unsigned char ezero[6];  /* crap for ARP */

/*
 * Function: OpenLogFile()
 *
 * Purpose: Create the log directory and file to put the packet log into.
 *          This function sucks, I've got to find a better way to do this
 *          this stuff.
 *
 * Arguments: None.
 *
 * Returns: 0 on success, exits on error
 */
int OpenLogFile(int mode, Packet * p)
{
    char log_path[STD_BUF+1]; /* path to log file */
    char log_file[STD_BUF+1]; /* name of log file */
    char proto[5];      /* logged packet protocol */

    /* zero out our buffers */
    bzero((char *) log_path, STD_BUF+1);
    bzero((char *) log_file, STD_BUF+1);
    bzero((char *) proto, 5);

    if(mode == GENERIC_LOG)
    {
        snprintf(log_file, STD_BUF, "%s%s/log",
                 chrootdir == NULL ? "" : chrootdir, pv.log_dir);

        if((log_ptr = fopen(log_file, "a")) == NULL)
        {
            FatalError("ERROR: OpenLogFile() => fopen(%s) log file: %s\n",
                       log_file, strerror(errno));
        }
        return 0;
    }
    if(mode == DUMP)
    {
        snprintf(log_file, STD_BUF, "%s%s/PACKET_FRAG",
                 chrootdir == NULL ? "" : chrootdir, pv.log_dir);

        if((log_ptr = fopen(log_file, "a")) == NULL)
        {
            FatalError("ERROR: OpenLogFile() => fopen(%s) log file: %s\n",
                       log_file, strerror(errno));
        }
        return 0;
    }
    if(mode == BOGUS)
    {
        snprintf(log_file, STD_BUF, "%s%s/PACKET_BOGUS",
                 chrootdir == NULL ? "" : chrootdir, pv.log_dir);

        if((log_ptr = fopen(log_file, "a")) == NULL)
        {
            FatalError("ERROR: OpenLogFile() => fopen(%s) log file: %s\n",
                       log_file, strerror(errno));
        }
        return 0;
    }
    if(mode == NON_IP)
    {
        snprintf(log_file, STD_BUF, "%s%s/PACKET_NONIP",
                 chrootdir == NULL ? "" : chrootdir, pv.log_dir);

        if((log_ptr = fopen(log_file, "a")) == NULL)
        {
            FatalError("ERROR: OpenLogFile() => fopen(%s) log file: %s\n",
                       log_file, strerror(errno));
        }
        return 0;
    }
    if(mode == ARP)
    {
        snprintf(log_file, STD_BUF, "%s%s/ARP",
                 chrootdir == NULL ? "" : chrootdir,  pv.log_dir);

        if((log_ptr = fopen(log_file, "a")) == NULL)
        {
            FatalError("ERROR: OpenLogFile() => fopen(%s) log file: %s\n",
                       log_file, strerror(errno));
        }
        return 0;
    }
    if(otn_tmp != NULL)
    {
        if(otn_tmp->logto != NULL)
        {
            snprintf(log_file, STD_BUF, "%s%s/%s",
                     chrootdir == NULL ? "" : chrootdir,  pv.log_dir, otn_tmp->logto);

            if((log_ptr = fopen(log_file, "a")) == NULL)
            {
                FatalError("ERROR: OpenLogFile() => fopen(%s) log file: %s\n", log_file, strerror(errno));
            }
            return 0;
        }
    }
    /* figure out which way this packet is headed in relation to the homenet */
    if((p->iph->ip_dst.s_addr & pv.netmask) == pv.homenet)
    {
        if((p->iph->ip_src.s_addr & pv.netmask) != pv.homenet)
        {
            snprintf(log_path, STD_BUF, "%s%s/%s",
                     chrootdir == NULL ? "" : chrootdir, pv.log_dir, inet_ntoa(p->iph->ip_src));
        }
        else
        {
            if(p->sp >= p->dp)
            {
                snprintf(log_path, STD_BUF, "%s%s/%s",
                         chrootdir == NULL ? "" : chrootdir,  pv.log_dir, inet_ntoa(p->iph->ip_src));
            }
            else
            {
                snprintf(log_path, STD_BUF, "%s%s/%s",
                         chrootdir == NULL ? "" : chrootdir, pv.log_dir, inet_ntoa(p->iph->ip_dst));
            }
        }
    }
    else
    {
        if((p->iph->ip_src.s_addr & pv.netmask) == pv.homenet)
        {
            snprintf(log_path, STD_BUF, "%s%s/%s",
                     chrootdir == NULL ? "" : chrootdir,  pv.log_dir, inet_ntoa(p->iph->ip_dst));
        }
        else
        {
            if(p->sp >= p->dp)
            {
                snprintf(log_path, STD_BUF, "%s%s/%s",
                         chrootdir == NULL ? "" : chrootdir, pv.log_dir, inet_ntoa(p->iph->ip_src));
            }
            else
            {
                snprintf(log_path, STD_BUF, "%s%s/%s",
                         chrootdir == NULL ? "" : chrootdir, pv.log_dir, inet_ntoa(p->iph->ip_dst));
            }
        }
    }

#ifdef DEBUG
    ErrorMessage("Creating directory: %s\n", log_path);
#endif

    /* build the log directory */
    if(mkdir(log_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
    {

        if(errno != EEXIST)
        {
            FatalError("ERROR: OpenLogFile() => mkdir(%s) log directory: %s\n", log_path, strerror(errno));
        }
    }
#ifdef DEBUG
    printf("Directory Created!\n");
#endif

    /* build the log filename */
    if(p->iph->ip_proto == IPPROTO_TCP ||
       p->iph->ip_proto == IPPROTO_UDP)
    {
        if(p->frag_flag)
        {
#ifdef WIN32
			snprintf(log_file, STD_BUF, "%s/IP_FRAG.ids", log_path);
#else
            snprintf(log_file, STD_BUF, "%s/IP_FRAG", log_path);
#endif
        }
        else
        {
            if(p->sp >= p->dp)
            {
#ifdef WIN32
				snprintf(log_file, STD_BUF, "%s/%s_%d-%d.ids", log_path,
#else
                snprintf(log_file, STD_BUF, "%s/%s:%d-%d", log_path,
#endif
                        protocol_names[p->iph->ip_proto], p->sp, p->dp);
            }
            else
            {
#ifdef WIN32
				snprintf(log_file, STD_BUF, "%s/%s_%d-%d.ids", log_path,
#else
                snprintf(log_file, STD_BUF, "%s/%s:%d-%d", log_path,
#endif
                        protocol_names[p->iph->ip_proto], p->dp, p->sp);

            }
        }
    }
    else
    {
        if(p->frag_flag)
        {
#ifdef WIN32
			snprintf(log_file, STD_BUF, "%s/IP_FRAG.ids", log_path);
#else
            snprintf(log_file, STD_BUF, "%s/IP_FRAG", log_path);
#endif
        }
        else
        {
            if(p->iph->ip_proto == IPPROTO_ICMP)
            {
#ifdef WIN32
				snprintf(log_file, STD_BUF, "%s/%s_%s.ids", log_path, "ICMP", IcmpFileName(p));
#else
                snprintf(log_file, STD_BUF, "%s/%s_%s", log_path, "ICMP", IcmpFileName(p));
#endif
            }
            else
            {
#ifdef WIN32
				snprintf(log_file, STD_BUF, "%s/PROTO%d.ids", log_path, p->iph->ip_proto);
#else
                snprintf(log_file, STD_BUF, "%s/PROTO%d", log_path, p->iph->ip_proto);
#endif
            }
        }
    }

#ifdef DEBUG
    printf("Opening file: %s\n", log_file);
#endif

    /* finally open the log file */
    if((log_ptr = fopen(log_file, "a")) == NULL)
    {
        FatalError("ERROR: OpenLogFile() => fopen(%s) log file: %s\n",
                   log_file, strerror(errno));
    }
#ifdef DEBUG
    printf("File opened...\n");
#endif

    return 0;
}


/*
 * Function: PrintNetData(FILE *, u_char *,int)
 *
 * Purpose: Do a side by side dump of a buffer, hex dump of buffer bytes on
 *          the left, decoded ASCII on the right.
 *
 * Arguments: fp => ptr to stream to print to
 *            start => pointer to buffer data
 *            len => length of data buffer
 *
 * Returns: void function
 */
void PrintNetData(FILE * fp, u_char * start, const int len)
{
    char *end;          /* ptr to buffer end */
    int i;          /* counter */
    int j;          /* counter */
    int dbuf_size;      /* data buffer size */
    int done;           /* flag */
    char *data;         /* index pointer */
    char *frame_ptr;        /* we use 66 byte frames for a printed line */
    char *d_ptr;        /* data pointer into the frame */
    char *c_ptr;        /* char pointer into the frame */
    char conv[] = "0123456789ABCDEF";   /* xlation lookup table */

    /* initialization */
    done = 0;

    if(start == NULL)
    {
        printf("Got NULL ptr in PrintNetData()\n");
        return;
    }
    /* zero, print a <CR> and get out */
    if(!len)
    {
        fputc('\n', fp);
        return;
    }
    /*
     * if we've already prepared this particular data buffer, just print it
     * out again to save time
     */
    if(dump_ready)
    {
        fwrite(data_dump_buffer, dump_size, 1, fp);
        fflush(fp);
        return;
    }
    end = start + (len - 1);    /* set the end of buffer ptr */

    if(len > pv.mtus[0])
    {
        if(pv.verbose_flag)
        {
            printf("Got bogus buffer length (%d) for PrintNetData, defaulting to 16 bytes!\n", len);
        }
        
        if(pv.verbose_bytedump_flag == 1)
        {
            dbuf_size = (FRAME_SIZE + 8) + (FRAME_SIZE + 8) + 1;
        }
        else
        {
            dbuf_size = FRAME_SIZE + FRAME_SIZE + 1;
        }

        /* dbuf_size = 66 + 67; */
        end = start + 15;
    }
    else
    {
        if(pv.verbose_bytedump_flag == 1)
        {
            /* figure out how big the printout data buffer has to be */
            dbuf_size = ((len / 16) * (FRAME_SIZE + 8)) + (FRAME_SIZE + 8) + 1;
        }
        else
        {
            /* figure out how big the printout data buffer has to be */
            dbuf_size = ((len / 16) * FRAME_SIZE) + FRAME_SIZE + 1;
        }

        /* dbuf_size = ((len / 16) * 66) + 67; */
    }

    /* generate the buffer */
    data_dump_buffer = (char *) malloc(dbuf_size);

    /* make sure it got allocated properly */
    if(data_dump_buffer == NULL)
    {
        ErrorMessage("Failed allocating %X bytes! (Length: %X)\n",
                dbuf_size, len);
        perror("PrintNetData()");
        CleanExit(SIGQUIT);
    }
    /* clean it out */
    memset(data_dump_buffer, 0x20, dbuf_size);


    /* set the byte buffer pointer to step thru the data buffer */
    data = start;

    /* set the frame pointer to the start of the printout buffer */
    frame_ptr = data_dump_buffer;

    /* initialize counters and frame index pointers */
    i = 0;
    j = 0;

    /* loop thru the whole buffer */
    while(!done)
    {
        if(pv.verbose_bytedump_flag == 1)
        {
            d_ptr = frame_ptr + 8;
            c_ptr = (frame_ptr + 8 + C_OFFSET);
            sprintf(frame_ptr, "0x%04X: ", j);
            j += 16;
        }
        else
        {
            d_ptr = frame_ptr;
            c_ptr = (frame_ptr + C_OFFSET);
        }

        /* process 16 bytes per frame */
        for(i = 0; i < 16; i++)
        {
            /*
             * look up the ASCII value of the first nybble of the current
             * data buffer
             */
            *d_ptr = conv[((*data & 0xFF) >> 4)];
            d_ptr++;

            /* look up the second nybble */
            *d_ptr = conv[((*data & 0xFF) & 0x0F)];
            d_ptr++;

            /* put a space in between */
            *d_ptr = 0x20;
            d_ptr++;

            /* print out the char equivalent */
            if(*data > 0x1F && *data < 0x7F)
                *c_ptr = (*data & 0xFF);
            else
                *c_ptr = 0x2E;

            c_ptr++;

            /* increment the pointer or finish up */
            if(data < end)
                data++;
            else
            {
                /* finish up the buffer printout and set the "ready" flags */
                done = 1;
                dump_ready = 1;

                *c_ptr = '\n';
                c_ptr++;
                *c_ptr = '\n';
                c_ptr++;
                *c_ptr = 0;

                dump_size = (int) (c_ptr - data_dump_buffer);
                fwrite(data_dump_buffer, dump_size, 1, fp);
                return;
            }
        }

        *c_ptr = '\n';
        if(pv.verbose_bytedump_flag == 1)
        {
            frame_ptr += (FRAME_SIZE + 8);
        }
        else
        {
            frame_ptr += FRAME_SIZE;
        }
    }
}



/*
 * Function: PrintCharData(FILE *, char *,int)
 *
 * Purpose: Dump the ASCII data from a packet
 *          the left, decoded ASCII on the right.
 *
 * Arguments: fp => ptr to stream to print to
 *            data => pointer to buffer data
 *            data_len => length of data buffer
 *
 * Returns: void function
 */
void PrintCharData(FILE * fp, char *data, int data_len)
{
    int bytes_processed;    /* count of bytes in the data buffer
                 * processed so far */
    int linecount = 0;      /* number of lines in this dump */
    char *index;        /* index pointer into the data buffer */
    char *ddb_ptr;      /* index pointer into the data_dump_buffer */

    /* if there's no data, return */
    if(data == NULL)
    {
        return;
    }
    /* if we've already setup the buffer, just reprint it */
    if(dump_ready)
    {
        fwrite(data_dump_buffer, dump_size, 1, fp);
        fflush(fp);
        return;
    }
    /* setup the pointers and counters */
    bytes_processed = data_len;
    index = data;

    /* allocate a buffer to print the data to */
    data_dump_buffer = (char *) calloc(data_len + (data_len >> 6) + 2, sizeof(char));
    ddb_ptr = data_dump_buffer;

    /* loop thru the bytes in the data buffer */
    while(bytes_processed)
    {
        if(*index > 0x1F && *index < 0x7F)
        {
            *ddb_ptr = *index;
        }
        else
        {
            *ddb_ptr = '.';
        }

        if(++linecount == 64)
        {
            ddb_ptr++;
            *ddb_ptr = '\n';
            linecount = 0;
        }
        ddb_ptr++;
        index++;
        bytes_processed--;
    }

    /* slam a \n on the back */
    ddb_ptr++;
    *ddb_ptr = '\n';
    ddb_ptr++;

    /* setup the globals */
    dump_ready = 1;
    dump_size = (int) (ddb_ptr - data_dump_buffer);
    fwrite(data_dump_buffer, dump_size, 1, fp);
}



/*
 * Function: PrintIPPkt(FILE *, int, Packet *)
 *
 * Purpose: Dump the packet to the stream pointer
 *
 * Arguments: fp => pointer to print data to
 *            type => packet protocol
 *            p => pointer to decoded packet struct
 *
 * Returns: void function
 */
void PrintIPPkt(FILE * fp, int type, Packet * p)
{
    char timestamp[23];

#ifdef DEBUG
    printf("PrintIPPkt type = %d\n", type);
#endif

    bzero((char *) timestamp, 23);
    ts_print((struct timeval *) & p->pkth->ts, timestamp);

    /* dump the timestamp */
    fwrite(timestamp, 22, 1, fp);

    /* dump the ethernet header if we're doing that sort of thing */
    if(pv.show2hdr_flag)
    {
        Print2ndHeader(fp, p);
    }
    /* etc */
    PrintIPHeader(fp, p);

    /* if this isn't a fragment, print the other header info */
    if(!p->frag_flag)
    {
        switch(p->iph->ip_proto)
        {
            case IPPROTO_TCP:
                if(p->tcph != NULL)
                {
                    PrintTCPHeader(fp, p);
                }
                else
                {
                    PrintNetData(fp, (char *) (p->iph + (p->iph->ip_hlen << 2)), (p->iph->ip_len - (p->iph->ip_hlen << 2)));
                }

                break;

            case IPPROTO_UDP:
                if(p->udph != NULL)
                {
                    PrintUDPHeader(fp, p);
                }
                else
                {
                    PrintNetData(fp, (char *) (p->iph + (p->iph->ip_hlen << 2)), (p->iph->ip_len - (p->iph->ip_hlen << 2)));
                }

                break;

            case IPPROTO_ICMP:
                if(p->icmph != NULL)
                {
                    PrintICMPHeader(fp, p);
                }
                else
                {
                    PrintNetData(fp, (char *) (p->iph + (p->iph->ip_hlen << 2)), (p->iph->ip_len - (p->iph->ip_hlen << 2)));
                }

                break;

            default:
                break;
        }
    }
    /* dump the application layer data */
    if(pv.data_flag && !pv.verbose_bytedump_flag)
    {
        if(pv.char_data_flag)
            PrintCharData(fp, p->data, p->dsize);
        else
            PrintNetData(fp, p->data, p->dsize);
    }
    else if(pv.verbose_bytedump_flag)
    {
        PrintNetData(fp, p->pkt, p->pkth->caplen);
    }
    fprintf(fp, "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n\n");
}




/*
 * Function: OpenAlertSock
 *
 * Purpose:  Connect to UNIX socket for alert logging..
 *
 * Arguments: none..
 *
 * Returns: void function
 */
void OpenAlertSock()
{
    char *srv = UNSOCK_FILE;

    if(access(srv, W_OK))
    {
        ErrorMessage("WARNING: %s file doesn't exist or isn't writable!\n", srv);
    }
    bzero((char *) &alertaddr, sizeof(alertaddr));
    bcopy((const void *) srv, (void *) alertaddr.sun_path, strlen(srv));    /* we trust what we
                                         * define */
    alertaddr.sun_family = AF_UNIX;

    if((alertsd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        FatalError("socket() call failed: %s", strerror(errno));
    }
}



/****************************************************************************
 *
 * Function: OpenAlertFile(char *)
 *
 * Purpose: Set up the file pointer/file for alerting
 *
 * Arguments: filearg => the filename to open
 *
 * Returns: file handle
 *
 ***************************************************************************/
FILE *OpenAlertFile(char *filearg)
{
    char filename[STD_BUF + 1];
    FILE *file;

    if(filearg == NULL)
    {
        if(!pv.daemon_flag)
#ifdef WIN32
			snprintf(filename, STD_BUF, "%s%s/alert.ids", chrootdir == NULL ?
#else
            snprintf(filename, STD_BUF, "%s%s/alert", chrootdir == NULL ?
#endif
                     "" : chrootdir, pv.log_dir);
        else
            snprintf(filename, STD_BUF, "%s%s/%s", chrootdir == NULL ?
                     "" : chrootdir, pv.log_dir, DEFAULT_DAEMON_ALERT_FILE);
    }
    else
    {
        snprintf(filename, STD_BUF, "%s%s", chrootdir == NULL ?
                 "" : chrootdir, filearg);
    }


#ifdef DEBUG
    printf("Opening alert file: %s\n", filename);
#endif

    if((file = fopen(filename, "a")) == NULL)
    {
        FatalError("ERROR in OpenAlertFile() => fopen() alert file %s: %s\n",
                   filename, strerror(errno));
    }
#ifdef WIN32
	/* Do not buffer in WIN32 */
	setvbuf(file, (char *) NULL, _IONBF, (size_t) 0);
#else
    setvbuf(file, (char *) NULL, _IOLBF, (size_t) 0);
#endif
    return file;
}



/*
 *
 * Function: ClearDumpBuf()
 *
 * Purpose: Clear out the buffer that PrintNetData() generates
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 */
void ClearDumpBuf()
{
    if(data_dump_buffer != NULL && dump_ready)
        free(data_dump_buffer);
    else
        return;

    data_dump_buffer = NULL;

    dump_ready = 0;
}


/*
 * Function: FullAlert(Packet *, char *, void *)
 *
 * Purpose: Stub function for compatability
 *
 * Arguments:   p => ptr to packet data
 *            msg => message to send to alert facility
 *            arg => arguments to the alert facility
 *
 * Returns: void function
 */
void FullAlert(Packet * p, char *msg, void *arg)
{
    AlertFull(p, msg, alert);

    return;
}



/*
 *
 * Function: AlertFull(char *)
 *
 * Purpose: Write a full and informative alert message
 *
 * Arguments: 	p   => packet. (could be NULL)
 * 	            msg => the message to send
 *             file => file pointer to print data to
 *
 * Returns: void function
 *
 */
void AlertFull(Packet * p, char *msg, FILE * file)
{
    char timestamp[23];

    if(msg != NULL)
    {
        if(pv.alert_interface_flag)
        {
            fwrite("[**] ", 5, 1, file);
#ifdef WIN32
			fprintf(file, " <%s> ", print_interface(pv.interfaces[0]));
#else
            fprintf(file, " <%s> ", pv.interfaces[0]);
#endif
            fwrite(msg, strlen(msg), 1, file);
            fwrite(" [**]\n", 6, 1, file);
        }
        else
        {
            fwrite("[**] ", 5, 1, file);
            fwrite(msg, strlen(msg), 1, file);
            fwrite(" [**]\n", 6, 1, file);
        }
    }
    else
    {
        fwrite("[**] Snort Alert! [**]\n", 22, 1, file);
    }

#ifdef DEBUG
    printf("Logging Alert data!\n");
#endif

    bzero((char *) timestamp, 23);
    ts_print(p == NULL ? NULL : (struct timeval *) & p->pkth->ts, timestamp);

    /* dump the timestamp */
    fwrite(timestamp, 22, 1, file);

    if(p)
    {
        /* print the packet header to the alert file */

        if(pv.show2hdr_flag)
        {
            Print2ndHeader(file, p);
        }
        PrintIPHeader(file, p);

        /* if this isn't a fragment, print the other header info */
        if(!p->frag_flag)
        {
            switch(p->iph->ip_proto)
            {
                case IPPROTO_TCP:
                    PrintTCPHeader(file, p);
                    break;

                case IPPROTO_UDP:
                    PrintUDPHeader(file, p);
                    break;

                case IPPROTO_ICMP:
                    PrintICMPHeader(file, p);
                    break;

                default:
                    break;
            }
        }
    }               /* End of if(p) */
    fputc('\n', file);

    return;
}


void FastAlert(Packet * p, char *msg, void *arg)
{
    AlertFast(p, msg, alert);
    return;
}

/****************************************************************************
 *
 * Function: FastAlert(Packet *, char *)
 *
 * Purpose: Write a minimal alert message to the alert file
 *
 * Arguments: p => pointer to the packet data struct (could be NULL)
 *            msg => the message to print in the alert
 *
 * Returns: void function
 *
 ***************************************************************************/
void AlertFast(Packet * p, char *msg, FILE * file)
{
    char timestamp[23];

    bzero((char *) timestamp, 23);
    ts_print(p == NULL ? NULL : (struct timeval *) & p->pkth->ts, timestamp);

    /* dump the timestamp */
    fwrite(timestamp, 22, 1, file);

    if(msg != NULL)
    {
        if(pv.alert_interface_flag)
        {
            fwrite(" [**] ", 6, 1, file);
#ifdef WIN32
			fprintf(file, " <%s> ", print_interface(pv.interfaces[0]));
#else
            fprintf(file, " <%s> ", pv.interfaces[0]);
#endif
            fwrite(msg, strlen(msg), 1, file);
            fwrite(" [**] ", 6, 1, file);
        }
        else
        {
            fwrite(" [**] ", 6, 1, file);
            fwrite(msg, strlen(msg), 1, file);
            fwrite(" [**] ", 6, 1, file);
        }
    }

    /* print the packet header to the alert file */
    if(p)
    {
        if(p->frag_flag)
        {
            /* just print the straight IP header */
            fputs(inet_ntoa(p->iph->ip_src), file);
            fwrite(" -> ", 4, 1, file);
            fputs(inet_ntoa(p->iph->ip_dst), file);
        }
        else
        {
            switch(p->iph->ip_proto)
            {
                case IPPROTO_UDP:
                case IPPROTO_TCP:
                    /* print the header complete with port information */
                    fputs(inet_ntoa(p->iph->ip_src), file);
                    fprintf(file, ":%d -> ", p->sp);
                    fputs(inet_ntoa(p->iph->ip_dst), file);
                    fprintf(file, ":%d", p->dp);
                    break;
                case IPPROTO_ICMP:
                default:
                    /* just print the straight IP header */
                    fputs(inet_ntoa(p->iph->ip_src), file);
                    fwrite(" -> ", 4, 1, file);
                    fputs(inet_ntoa(p->iph->ip_dst), file);
            }
        }
    }               /* end of if (p) */

    fputc('\n', file);

    return;
}




/****************************************************************************
 *
 * Function: SyslogAlert(Packet *, char *)
 *
 * Purpose: Send the current alert to syslog
 *
 * Arguments: p => pointer to the packet data struct
 *            msg => the message to print in the alert
 *
 * Returns: void function
 *
 ***************************************************************************/
void SyslogAlert(Packet * p, char *msg, void *arg)
{
    char sip[16];
    char dip[16];

    /*
     * have to do this since inet_ntoa is fucked up and writes to a static
     * memory location
     */
    if(p)
    {
        strncpy(sip, inet_ntoa(p->iph->ip_src), 16);
        strncpy(dip, inet_ntoa(p->iph->ip_dst), 16);

        if((p->iph->ip_proto != IPPROTO_TCP &&
            p->iph->ip_proto != IPPROTO_UDP) || p->frag_flag)
        {
            if(msg != NULL)
            {
                if(pv.alert_interface_flag)
                {
                    /* ICMP packets don't get port info... */
                    syslog(LOG_AUTHPRIV | LOG_ALERT, "<%s> %s: %s -> %s", 
#ifdef WIN32
						   print_interface(pv.interfaces[0]), msg, sip, dip);
#else
                           pv.interfaces[0], msg, sip, dip);
#endif
                }
                else
                {
                    /* ICMP packets don't get port info... */
                    syslog(LOG_AUTHPRIV | LOG_ALERT, "%s: %s -> %s", msg,
                           sip, dip);
                } 
            }
            else
            {
                /* ICMP packets don't get port info... */
                syslog(LOG_AUTHPRIV | LOG_ALERT, "ALERT: %s -> %s",
                       sip, dip);
            }
        }
        else
        {
            if(msg != NULL)
            {
                if(pv.alert_interface_flag)
                {
                    syslog(LOG_AUTHPRIV | LOG_ALERT, "<%s> %s: %s:%i -> %s:%i",
#ifdef WIN32
						   print_interface(pv.interfaces[0]), msg, sip, p->sp, dip, p->dp);
#else
                           pv.interfaces[0], msg, sip, p->sp, dip, p->dp);
#endif
                }
                else
                {
                    syslog(LOG_AUTHPRIV | LOG_ALERT, "%s: %s:%i -> %s:%i", 
                           msg, sip, p->sp, dip, p->dp);
                }
            }
            else
            {
                syslog(LOG_AUTHPRIV | LOG_ALERT, "ALERT: %s:%i -> %s:%i",
                       sip, p->sp, dip, p->dp);
            }
        }
    }
    else            /* p == NULL */
    {
        syslog(LOG_AUTHPRIV | LOG_ALERT, "%s", msg == NULL ? "ALERT!" : msg);
    }

    return;
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
#ifdef ENABLE_SMB_ALERTS
void SmbAlert(Packet * p, char *msg, void *arg)
{
    char command_line[2048];
    FILE *output;
    FILE *workstations;
    char *tempmsg;
    char workfile[STD_BUF];
    char tempwork[STD_BUF];
    char timestamp[23];
    int msg_str_size;

    bzero((char *) timestamp, 23);

    ts_print(p == NULL ? NULL : (struct timeval *) & p->pkth->ts, timestamp);

#ifdef DEBUG
    printf("Generating SMB alert!\n");
#endif

    /* set the workstation name filename */
    sprintf(workfile, "%s", pv.smbmsg_dir);

    /* message size + IP addrs + ports + pad space */
    msg_str_size = strlen(msg) + 32 + 10 + 150;

    if((tempmsg = (char *) calloc(msg_str_size, sizeof(char))) == NULL)
    {
        FatalError("[!] ERROR: SmbAlert() unable to allocate space for tempmsg: %s\n", strerror(errno));
    }
    /* open the message file and the workstation names file */
    if((workstations = fopen(workfile, "r")) != NULL)
    {
        /* clear the read buffers */
        bzero((char *) workfile, STD_BUF);

        if(p != NULL)
        {
            if(p->frag_flag || (p->iph->ip_proto != IPPROTO_TCP
                                && p->iph->ip_proto != IPPROTO_UDP))
            {
                /* write the alert message into the buffer */
                sprintf(tempmsg, "SNORT ALERT - Possible Network Attack or Probe:\n [**] %s [**]\n%s %s->%s", msg, timestamp, inet_ntoa(p->iph->ip_src), inet_ntoa(p->iph->ip_dst));
            }
            else
            {
                /* write the alert message into the buffer */
                sprintf(tempmsg, "SNORT ALERT - Possible Network Attack or Probe:\n [**] %s [**]\n%s %s:%d->%s:%d", msg, timestamp, inet_ntoa(p->iph->ip_src), p->sp, inet_ntoa(p->iph->ip_dst), p->dp);
            }
        }
        else
        {
            /*
             * write the alert message into the buffer - this part is for
             * alerts with NULL packets (like portscans)
             */
            sprintf(tempmsg, "SNORT ALERT - Possible Network Attack or Probe:\n [**] %s [**]\n", msg);
        }

        bzero((char *) tempwork, STD_BUF);
        bzero((char *) command_line, 2048);

        /* read in the name of each workstation to send the message to */
        while((fgets(tempwork, STD_BUF - 1, workstations)) != NULL)
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
                    output = popen(command_line, "r");

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

                bzero((char *) tempwork, STD_BUF);
                bzero((char *) command_line, 2048);
            }
        }

        fclose(workstations);
    }
    free(tempmsg);
}

#endif


/****************************************************************************
 *
 * Function: NoAlert(Packet *, char *)
 *
 * Purpose: Don't alert at all
 *
 * Arguments: p => pointer to the packet data struct
 *            msg => the message to not print in the alert
 *
 * Returns: void function
 *
 ***************************************************************************/
void NoAlert(Packet * p, char *msg, void *arg)
{
    return;
}


/****************************************************************************
 *
 * Function: LogPkt(Packet *)
 *
 * Purpose: Log packets that match one of the Snort rules, plus the rules
 *          message
 *
 * Arguments: p => pointer to the packet data structure
 *
 * Returns: void function
 *
 ***************************************************************************/
void LogPkt(Packet * p, char *msg, void *arg)
{
    /*
     * some plugins may pass NULL as 'p' structure here (f.e. if they only
     * want to log message
     */
    if(p)
        OpenLogFile(0, p);
    else
        OpenLogFile(GENERIC_LOG, p);

    if(msg != NULL)
    {
        fwrite("[**] ", 5, 1, log_ptr);
        fwrite(msg, strlen(msg), 1, log_ptr);
        fwrite(" [**]\n", 6, 1, log_ptr);
    }
    if(p)
        PrintIPPkt(log_ptr, p->iph->ip_proto, p);

    fclose(log_ptr);
}



/****************************************************************************
 *
 * Function: LogArpPkt(Packet *)
 *
 * Purpose: Log ARP packets
 *
 * Arguments: p => pointer to the packet data structure
 *
 * Returns: void function
 *
 ***************************************************************************/
void LogArpPkt(Packet * p)
{
    if(p)
    {
        if(pv.logbin_flag)
        {
            /* LogBin(p); */
        }
        else if(!pv.nolog_flag)
        {
            OpenLogFile(ARP, p);

            PrintArpHeader(log_ptr, p);

            fclose(log_ptr);
        }
    }
    else
    {
        /* let's just make sure we don't coredump if we have some logic error in one
         *   of plugins/preprocessors...
         */
        ErrorMessage("WARNING: Null Packet pointer in LogArpPkt. Please report.\n");
    }
}



/****************************************************************************
 *
 * Function: NoLog(Packet *)
 *
 * Purpose: Don't log anything
 *
 * Arguments: p => packet to not log
 *
 * Returns: void function
 *
 ***************************************************************************/
void NoLog(Packet * p, char *msg, void *arg)
{
    return;
}

/****************************************************************************
 *
 * Function: Print2ndHeader(FILE *, Packet p)
 *
 * Purpose: Print2ndHeader -- prints second layber  header info.
 *
 * Arguments: fp => file stream to print to
 *
 * Returns: void function
 *
 ***************************************************************************/


void Print2ndHeader(FILE * fp, Packet * p)
{

    if(p && p->eh)
        PrintEthHeader(fp, p);
    if(p && p->trh)
        PrintTrHeader(fp, p);

}



/****************************************************************************
 *
 * Function: PrintTrHeader(FILE *, Packet p)
 &
 * Purpose: Print the packet TokenRing header to the specified stream
 *
 * Arguments: fp => file stream to print to
 *
 * Returns: void function
 ***************************************************************************/

void PrintTrHeader(FILE * fp, Packet * p)
{

    fprintf(fp, "%X:%X:%X:%X:%X:%X -> ", p->trh->saddr[0],
            p->trh->saddr[1], p->trh->saddr[2], p->trh->saddr[3],
            p->trh->saddr[4], p->trh->saddr[5]);
    fprintf(fp, "%X:%X:%X:%X:%X:%X\n", p->trh->daddr[0],
            p->trh->daddr[1], p->trh->daddr[2], p->trh->daddr[3],
            p->trh->daddr[4], p->trh->daddr[5]);

    fprintf(fp, "access control:0x%X frame control:0x%X\n", p->trh->ac,
            p->trh->fc);
    if(!p->trhllc)
        return;
    fprintf(fp, "DSAP: 0x%X SSAP 0x%X protoID: %X%X%X Ethertype: %X\n",
            p->trhllc->dsap, p->trhllc->ssap, p->trhllc->protid[0],
            p->trhllc->protid[1], p->trhllc->protid[2], p->trhllc->ethertype);
    if(p->trhmr)
    {
        fprintf(fp, "RIF structure is present:\n");
        fprintf(fp, "bcast: 0x%X length: 0x%X direction: 0x%X largest"
                "fr. size: 0x%X res: 0x%X\n",
                p->trhmr->bcast, p->trhmr->len, p->trhmr->dir, p->trhmr->lf,
                p->trhmr->res);
        fprintf(fp, "rseg -> %X:%X:%X:%X:%X:%X:%X:%X\n",
                p->trhmr->rseg[0], p->trhmr->rseg[1], p->trhmr->rseg[2],
                p->trhmr->rseg[3], p->trhmr->rseg[4], p->trhmr->rseg[5],
                p->trhmr->rseg[6], p->trhmr->rseg[7]);
    }
}


/****************************************************************************
 *
 * Function: PrintEthHeader(FILE *)
 *
 * Purpose: Print the packet Ethernet header to the specified stream
 *
 * Arguments: fp => file stream to print to
 *
 * Returns: void function
 *
 ***************************************************************************/
void PrintEthHeader(FILE * fp, Packet * p)
{
    /* src addr */
    fprintf(fp, "%X:%X:%X:%X:%X:%X -> ", p->eh->ether_src[0],
            p->eh->ether_src[1], p->eh->ether_src[2], p->eh->ether_src[3],
            p->eh->ether_src[4], p->eh->ether_src[5]);

    /* dest addr */
    fprintf(fp, "%X:%X:%X:%X:%X:%X ", p->eh->ether_dst[0],
            p->eh->ether_dst[1], p->eh->ether_dst[2], p->eh->ether_dst[3],
            p->eh->ether_dst[4], p->eh->ether_dst[5]);

    /* protocol and pkt size */
    fprintf(fp, "type:0x%X len:0x%X\n", ntohs(p->eh->ether_type), p->pkth->len);
}



void PrintArpHeader(FILE * fp, Packet * p)
{
    struct in_addr ip_addr;
    char timestamp[23];

    bzero((char *) timestamp, 23);
    ts_print((struct timeval *) & p->pkth->ts, timestamp);

    /* dump the timestamp */
    fwrite(timestamp, 22, 1, fp);

    if(ntohs(p->ah->ea_hdr.ar_pro) != ETHERNET_TYPE_IP)
    {
        fprintf(fp, "ARP #%d for protocol #%.4X (%d) hardware #%d (%d)\n",
                ntohs(p->ah->ea_hdr.ar_op), ntohs(p->ah->ea_hdr.ar_pro),
                p->ah->ea_hdr.ar_pln, ntohs(p->ah->ea_hdr.ar_hrd),
                p->ah->ea_hdr.ar_hln);

        return;
    }
    switch(ntohs(p->ah->ea_hdr.ar_op))
    {
        case ARPOP_REQUEST:
            bcopy((void *)p->ah->arp_tpa, (void *) &ip_addr, sizeof(ip_addr));
            fprintf(fp, "ARP who-has %s", inet_ntoa(ip_addr));

            if(memcmp((char *) ezero, (char *) p->ah->arp_tha, 6) != 0)
            {
                fprintf(fp, " (%X:%X:%X:%X:%X:%X)", p->ah->arp_tha[0],
                        p->ah->arp_tha[1], p->ah->arp_tha[2], p->ah->arp_tha[3],
                        p->ah->arp_tha[4], p->ah->arp_tha[5]);
            }
            bcopy((void *)p->ah->arp_spa, (void *) &ip_addr, sizeof(ip_addr));

            fprintf(fp, " tell %s", inet_ntoa(ip_addr));

            if(memcmp((char *) p->eh->ether_src, (char *) p->ah->arp_sha, 6) != 0)
            {
                fprintf(fp, " (%X:%X:%X:%X:%X:%X)", p->ah->arp_sha[0],
                        p->ah->arp_sha[1], p->ah->arp_sha[2], p->ah->arp_sha[3],
                        p->ah->arp_sha[4], p->ah->arp_sha[5]);
            }
            break;

        case ARPOP_REPLY:
            bcopy((void *)p->ah->arp_spa, (void *) &ip_addr, sizeof(ip_addr));
            fprintf(fp, "ARP reply %s", inet_ntoa(ip_addr));

            if(memcmp((char *) p->eh->ether_src, (char *) p->ah->arp_sha, 6) != 0)
            {
                fprintf(fp, " (%X:%X:%X:%X:%X:%X)", p->ah->arp_sha[0],
                        p->ah->arp_sha[1], p->ah->arp_sha[2], p->ah->arp_sha[3],
                        p->ah->arp_sha[4], p->ah->arp_sha[5]);
            }
            fprintf(fp, " is-at %X:%X:%X:%X:%X:%X", p->ah->arp_sha[0],
                    p->ah->arp_sha[1], p->ah->arp_sha[2], p->ah->arp_sha[3],
                    p->ah->arp_sha[4], p->ah->arp_sha[5]);

            if(memcmp((char *) p->eh->ether_dst, (char *) p->ah->arp_tha, 6) != 0)
            {
                fprintf(fp, " (%X:%X:%X:%X:%X:%X)", p->ah->arp_tha[0],
                        p->ah->arp_tha[1], p->ah->arp_tha[2], p->ah->arp_tha[3],
                        p->ah->arp_tha[4], p->ah->arp_tha[5]);
            }
            break;

        case ARPOP_RREQUEST:
            fprintf(fp, "RARP who-is %X:%X:%X:%X:%X:%X tell %X:%X:%X:%X:%X:%X",
                    p->ah->arp_tha[0], p->ah->arp_tha[1], p->ah->arp_tha[2],
                    p->ah->arp_tha[3], p->ah->arp_tha[4], p->ah->arp_tha[5],
                    p->ah->arp_sha[0], p->ah->arp_sha[1], p->ah->arp_sha[2],
                    p->ah->arp_sha[3], p->ah->arp_sha[4], p->ah->arp_sha[5]);

            break;

        case ARPOP_RREPLY:
            bcopy((void *)p->ah->arp_tpa, (void *) &ip_addr, sizeof(ip_addr));
            fprintf(fp, "RARP reply %X:%X:%X:%X:%X:%X at %s",
                    p->ah->arp_tha[0], p->ah->arp_tha[1], p->ah->arp_tha[2],
                    p->ah->arp_tha[3], p->ah->arp_tha[4], p->ah->arp_tha[5],
                    inet_ntoa(ip_addr));

            break;

        default:
            fprintf(fp, "Unknown operation: %d", ntohs(p->ah->ea_hdr.ar_op));
            break;
    }

    fprintf(fp, "\n\n");

}

/****************************************************************************
 *
 * Function: PrintIPHeader(FILE *)
 *
 * Purpose: Dump the IP header info to the specified stream
 *
 * Arguments: fp => stream to print to
 *
 * Returns: void function
 *
 ***************************************************************************/
void PrintIPHeader(FILE * fp, Packet * p)
{

    if(p->iph == NULL)
    {
        fprintf(fp, "IP header truncated\n");
        return;
    }
    if(p->frag_flag)
    {
        /* just print the straight IP header */
        fputs(inet_ntoa(p->iph->ip_src), fp);
        fwrite(" -> ", 4, 1, fp);
        fputs(inet_ntoa(p->iph->ip_dst), fp);
    }
    else
    {
        if(p->iph->ip_proto != IPPROTO_TCP && p->iph->ip_proto != IPPROTO_UDP)
        {
            /* just print the straight IP header */
            fputs(inet_ntoa(p->iph->ip_src), fp);
            fwrite(" -> ", 4, 1, fp);
            fputs(inet_ntoa(p->iph->ip_dst), fp);
        }
        else
        {
            if(!pv.obfuscation_flag)
            {
                /* print the header complete with port information */
                fputs(inet_ntoa(p->iph->ip_src), fp);
                fprintf(fp, ":%d -> ", p->sp);
                fputs(inet_ntoa(p->iph->ip_dst), fp);
                fprintf(fp, ":%d", p->dp);
            }
            else
            {
                /* print the header complete with port information */
                fprintf(fp, "xxx.xxx.xxx.xxx:%d -> xxx.xxx.xxx.xxx:%d", p->sp, p->dp);
            }
        }
    }

    if(!pv.show2hdr_flag)
    {
        fputc('\n', fp);
    }
    else
    {
        fputc(' ', fp);
    }

    fprintf(fp, "%s TTL:%d TOS:0x%X ID:%d IpLen:%d DgmLen:%d",
            protocol_names[p->iph->ip_proto],
            p->iph->ip_ttl,
            p->iph->ip_tos,
            ntohs(p->iph->ip_id),
            p->iph->ip_hlen << 2, ntohs(p->iph->ip_len));

    /* print the reserved bit if it's set */
    if(p->rf)
    {
        fprintf(fp, " RB");
    }
    /* printf more frags/don't frag bits */
    if(p->df)
        fprintf(fp, " DF");

    if(p->mf)
        fprintf(fp, " MF");

    fputc('\n', fp);

    /* print IP options */
    if(p->ip_option_count != 0)
    {
        PrintIpOptions(fp, p);
    }
    /* print fragment info if necessary */
    if(p->frag_flag)
    {
        fprintf(fp, "Frag Offset: 0x%X   Frag Size: 0x%X",
                (p->frag_offset & 0xFFFF), p->dsize);
        fputc('\n', fp);
    }
}



/****************************************************************************
 *
 * Function: PrintTCPHeader(FILE *)
 *
 * Purpose: Dump the TCP header info to the specified stream
 *
 * Arguments: fp => file stream to print data to
 *
 * Returns: void function
 *
 ***************************************************************************/
void PrintTCPHeader(FILE * fp, Packet * p)
{
    char tcpFlags[9];

    if(p->tcph == NULL)
    {
        fprintf(fp, "TCP header truncated\n");
        return;
    }
    /* print TCP flags */
    CreateTCPFlagString(p, tcpFlags);
    fwrite(tcpFlags, 8, 1, fp); /* We don't care about the NULL */

    /* print other TCP info */
    fprintf(fp, " Seq: 0x%lX  Ack: 0x%lX  Win: 0x%X  TcpLen: %d",
            (u_long) ntohl(p->tcph->th_seq),
            (u_long) ntohl(p->tcph->th_ack),
            ntohs(p->tcph->th_win), p->tcph->th_off << 2);

    if((p->tcph->th_flags & TH_URG) != 0)
    {
        fprintf(fp, "  UrgPtr: 0x%X\n", (u_int16_t) ntohs(p->tcph->th_urp));
    }
    else
    {
        fputc((int) '\n', fp);
    }

    /* dump the TCP options */
    if(p->tcp_option_count != 0)
    {
        PrintTcpOptions(fp, p);
    }
}


/* Input is packet and an nine-byte (including NULL) character array.  Results
 * are put into the character array.
 */
void CreateTCPFlagString(Packet * p, char *flagBuffer)
{
    memset(flagBuffer, '\0', 9);

    /* parse TCP flags */
    *flagBuffer++ = (p->tcph->th_flags & TH_RES1) ? '1' : '*';
    *flagBuffer++ = (p->tcph->th_flags & TH_RES2) ? '2' : '*';
    *flagBuffer++ = (p->tcph->th_flags & TH_URG) ? 'U' : '*';
    *flagBuffer++ = (p->tcph->th_flags & TH_ACK) ? 'A' : '*';
    *flagBuffer++ = (p->tcph->th_flags & TH_PUSH) ? 'P' : '*';
    *flagBuffer++ = (p->tcph->th_flags & TH_RST) ? 'R' : '*';
    *flagBuffer++ = (p->tcph->th_flags & TH_SYN) ? 'S' : '*';
    *flagBuffer++ = (p->tcph->th_flags & TH_FIN) ? 'F' : '*';

};


/****************************************************************************
 *
 * Function: PrintUDPHeader(FILE *)
 *
 * Purpose: Dump the UDP header to the specified file stream
 *
 * Arguments: fp => file stream
 *
 * Returns: void function
 *
 ***************************************************************************/
void PrintUDPHeader(FILE * fp, Packet * p)
{

    if(p->udph == NULL)
    {
        fprintf(fp, "UDP header truncated\n");
        return;
    }
    /* not much to do here... */
    fprintf(fp, "Len: %d\n", ntohs(p->udph->uh_len));
}



/****************************************************************************
 *
 * Function: PrintICMPHeader(FILE *)
 *
 * Purpose: Print ICMP header
 *
 * Arguments: fp => file stream
 *
 * Returns: void function
 *
 ***************************************************************************/
void PrintICMPHeader(FILE * fp, Packet * p)
{

    if(p->icmph == NULL)
    {
        fprintf(fp, "ICMP header truncated\n");
        return;
    }

    fprintf(fp, "Type:%d  Code:%d  ", p->icmph->type, p->icmph->code);

    switch(p->icmph->type)
    {
        case ICMP_ECHOREPLY:
            fprintf(fp, "ID:%d  Seq:%d  ", ntohs(p->ext->id), ntohs(p->ext->seqno));
            fwrite("ECHO REPLY\n", 10, 1, fp);
            break;

        case ICMP_DEST_UNREACH:
            fwrite("DESTINATION UNREACHABLE: ", 25, 1, fp);
            switch(p->icmph->code)
            {
                case ICMP_NET_UNREACH:
                    fwrite("NET UNREACHABLE", 15, 1, fp);
                    break;

                case ICMP_HOST_UNREACH:
                    fwrite("HOST UNREACHABLE", 16, 1, fp);
                    break;

                case ICMP_PROT_UNREACH:
                    fwrite("PROTOCOL UNREACHABLE", 20, 1, fp);
                    break;

                case ICMP_PORT_UNREACH:
                    fwrite("PORT UNREACHABLE", 16, 1, fp);
                    break;

                case ICMP_FRAG_NEEDED:
                    fwrite("FRAGMENTATION NEEDED", 20, 1, fp);
                    break;

                case ICMP_SR_FAILED:
                    fwrite("SOURCE ROUTE FAILED", 19, 1, fp);
                    break;

                case ICMP_NET_UNKNOWN:
                    fwrite("NET UNKNOWN", 11, 1, fp);
                    break;

                case ICMP_HOST_UNKNOWN:
                    fwrite("HOST UNKNOWN", 12, 1, fp);
                    break;

                case ICMP_HOST_ISOLATED:
                    fwrite("HOST ISOLATED", 13, 1, fp);
                    break;

                case ICMP_NET_ANO:
                    fwrite("NET ANO", 7, 1, fp);
                    break;

                case ICMP_HOST_ANO:
                    fwrite("HOST ANO", 8, 1, fp);
                    break;

                case ICMP_NET_UNR_TOS:
                    fwrite("NET UNREACHABLE TOS", 19, 1, fp);
                    break;

                case ICMP_HOST_UNR_TOS:
                    fwrite("HOST UNREACHABLE TOS", 20, 1, fp);
                    break;

                case ICMP_PKT_FILTERED:
                    fwrite("PACKET FILTERED", 15, 1, fp);
                    break;

                case ICMP_PREC_VIOLATION:
                    fwrite("PREC VIOLATION", 14, 1, fp);
                    break;

                case ICMP_PREC_CUTOFF:
                    fwrite("PREC CUTOFF", 12, 1, fp);
                    break;

                default:
                    fwrite("UNKNOWN", 7, 1, fp);
                    break;

            }
            {
                Packet orig_p;

                bzero((char *) &orig_p, sizeof(Packet));
                orig_p.iph = p->orig_iph;
                orig_p.tcph = p->orig_tcph;
                orig_p.udph = p->orig_udph;
                orig_p.sp = p->orig_sp;
                orig_p.dp = p->orig_dp;

                if(orig_p.iph != NULL)
                {
                    fprintf(fp, "\n** ORIGINAL DATAGRAM DUMP:\n");
                    PrintIPHeader(fp, &orig_p);
                    switch(orig_p.iph->ip_proto)
                    {
                        case IPPROTO_TCP:
                            if(orig_p.tcph != NULL)
                                PrintTCPHeader(fp, &orig_p);
                            break;

                        case IPPROTO_UDP:
                            if(orig_p.udph != NULL)
                                PrintUDPHeader(fp, &orig_p);
                            break;

                        case IPPROTO_ICMP:
                            if(orig_p.icmph != NULL)
                                PrintICMPHeader(fp, &orig_p);
                            break;

                        default:
                            fprintf(fp, "Protocol: 0x%X (unknown or header truncated)", orig_p.iph->ip_proto);
                            break;
                    }       /* switch */
                    fprintf(fp, "** END OF DUMP");
                }
                /* if (orig_p.iph..) */
                else
                {
                    fprintf(fp, "\nORIGINAL DATAGRAM TRUNCATED");
                }
            }


            break;

        case ICMP_SOURCE_QUENCH:
            fwrite("SOURCE QUENCH", 13, 1, fp);
            break;

        case ICMP_REDIRECT:
            fwrite("REDIRECT", 8, 1, fp);
            break;
        case ICMP_ECHO:
            fprintf(fp, "ID:%d   Seq:%d  ", ntohs(p->ext->id), ntohs(p->ext->seqno));
            fwrite("ECHO", 4, 1, fp);
            break;

        case ICMP_TIME_EXCEEDED:
            fwrite("TTL EXCEEDED", 12, 1, fp);
            break;

        case ICMP_PARAMETERPROB:
            fwrite("PARAMETER PROBLEM", 17, 1, fp);
            break;

        case ICMP_TIMESTAMP:
            fwrite("TIMESTAMP REQUEST", 17, 1, fp);
            break;

        case ICMP_TIMESTAMPREPLY:
            fwrite("TIMESTAMP REPLY", 15, 1, fp);
            break;

        case ICMP_INFO_REQUEST:
            fwrite("INFO REQUEST", 12, 1, fp);
            break;

        case ICMP_INFO_REPLY:
            fwrite("INFO REPLY", 10, 1, fp);
            break;

        case ICMP_ADDRESS:
            fwrite("ADDRESS REQUEST", 15, 1, fp);
            break;

        case ICMP_ADDRESSREPLY:
            fwrite("ADDRESS REPLY", 13, 1, fp);
            break;

        default:
            fwrite("UNKNOWN", 7, 1, fp);

            break;
    }

    putc('\n', fp);

}


void PrintIpOptions(FILE * fp, Packet * p)
{
    int i;
    int j;
    u_long init_offset;
    u_long print_offset;

    init_offset = ftell(fp);

    if(!p->ip_option_count)
        return;

    fprintf(fp, "IP Options (%d) => ", p->ip_option_count);

    for(i = 0; i < (int)p->ip_option_count; i++)
    {
        print_offset = ftell(fp);

        if((print_offset - init_offset) > 60)
        {
            fwrite("\nIP Options => ", 15, 1, fp);
            init_offset = ftell(fp);
        }
            
        switch(p->ip_options[i].code)
        {
            case IPOPT_RR:
                fwrite("RR ", 3, 1, fp);
                break;

            case IPOPT_EOL:
                fwrite("EOL ", 4, 1, fp);
                break;

            case IPOPT_NOP:
                fwrite("NOP ", 4, 1, fp);
                break;

            case IPOPT_TS:
                fwrite("TS ", 3, 1, fp);
                break;

            case IPOPT_SECURITY:
                fwrite("SEC ", 4, 1, fp);
                break;

            case IPOPT_LSRR:
            case IPOPT_LSRR_E:
                fwrite("LSRR ", 5, 1, fp);
                break;

            case IPOPT_SATID:
                fwrite("SID ", 4, 1, fp);
                break;

            case IPOPT_SSRR:
                fwrite("SSRR ", 5, 1, fp);
                break;

            case IPOPT_RTRALT:
                fwrite("RTRALT ", 7, 1, fp);
                break;    

            default:
                fprintf(fp, "Opt %d: ", p->ip_options[i].code);

                if(p->ip_options[i].len)
                {
                    for(j = 0; j < (int)p->ip_options[i].len - 2; j += 2)
                    {
                        fprintf(fp, "%02X%02X ", p->ip_options[i].data[j], p->ip_options[i].data[j + 1]);
                    }
                }
                break;
        }
    }

    fwrite("\n", 1, 1, fp);
}


void PrintTcpOptions(FILE * fp, Packet * p)
{
    int i;
    int j;
    u_char tmp[5];
    u_long init_offset;
    u_long print_offset;

    init_offset = ftell(fp);

    fprintf(fp, "TCP Options (%d) => ", p->tcp_option_count);

    for(i = 0; i < (int)p->tcp_option_count; i++)
    {
        print_offset = ftell(fp);

        if((print_offset - init_offset) > 60)
        {
            fwrite("\nTCP Options => ", 16, 1, fp);
            init_offset = ftell(fp);
        }
            
        switch(p->tcp_options[i].code)
        {
            case TCPOPT_MAXSEG:
                bzero((char *) tmp, 5);
                fwrite("MSS: ", 5, 1, fp);
                strncpy(tmp, p->tcp_options[i].data, 2);
                fprintf(fp, "%u ", EXTRACT_16BITS(tmp));
                break;

            case TCPOPT_EOL:
                fwrite("EOL ", 4, 1, fp);
                break;

            case TCPOPT_NOP:
                fwrite("NOP ", 4, 1, fp);
                break;

            case TCPOPT_WSCALE:
                fprintf(fp, "WS: %u ", p->tcp_options[i].data[0]);
                break;

            case TCPOPT_SACK:
                bzero((char *) tmp, 5);
                memcpy(tmp, p->tcp_options[i].data, 2);
                fprintf(fp, "Sack: %u@", EXTRACT_16BITS(tmp));
                bzero((char *) tmp, 5);
                memcpy(tmp, (p->tcp_options[i].data) + 2, 2);
                fprintf(fp, "%u ", EXTRACT_16BITS(tmp));
                break;

            case TCPOPT_SACKOK:
                fwrite("SackOK ", 7, 1, fp);
                break;

            case TCPOPT_ECHO:
                bzero((char *) tmp, 5);
                memcpy(tmp, p->tcp_options[i].data, 4);
                fprintf(fp, "Echo: %u ", EXTRACT_32BITS(tmp));
                break;

            case TCPOPT_ECHOREPLY:
                bzero((char *) tmp, 5);
                memcpy(tmp, p->tcp_options[i].data, 4);
                fprintf(fp, "Echo Rep: %u ", EXTRACT_32BITS(tmp));
                break;

            case TCPOPT_TIMESTAMP:
                bzero((char *) tmp, 5);
                memcpy(tmp, p->tcp_options[i].data, 4);
                fprintf(fp, "TS: %u ", EXTRACT_32BITS(tmp));
                bzero((char *) tmp, 5);
                memcpy(tmp, (p->tcp_options[i].data) + 4, 4);
                fprintf(fp, "%u ", EXTRACT_32BITS(tmp));
                break;

            case TCPOPT_CC:
                bzero((char *) tmp, 5);
                memcpy(tmp, p->tcp_options[i].data, 4);
                fprintf(fp, "CC %u ", EXTRACT_32BITS(tmp));
                break;

            case TCPOPT_CCNEW:
                bzero((char *) tmp, 5);
                memcpy(tmp, p->tcp_options[i].data, 4);
                fprintf(fp, "CCNEW: %u ", EXTRACT_32BITS(tmp));
                break;

            case TCPOPT_CCECHO:
                bzero((char *) tmp, 5);
                memcpy(tmp, p->tcp_options[i].data, 4);
                fprintf(fp, "CCECHO: %u ", EXTRACT_32BITS(tmp));
                break;

            default:
                if(p->tcp_options[i].len > 2)
                {
                    fprintf(fp, "Opt %d (%d): ", p->tcp_options[i].code,
                            (int) p->tcp_options[i].len);

                    for(j = 0; j < (int)p->tcp_options[i].len - 2; j += 2)
                    {
                        fprintf(fp, "%02X%02X ", p->tcp_options[i].data[j], 
                                p->tcp_options[i].data[j + 1]);
                    }
                }
                else
                {
                    fprintf(fp, "Opt %d ", p->tcp_options[i].code);
                }
                break;
        }
    }

    fwrite("\n", 1, 1, fp);
}




/****************************************************************************
 *
 * Function: LogBin()
 *
 * Purpose: Log packets in binary (tcpdump) format
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ***************************************************************************/
void LogBin(Packet * p, char *msg, void *arg)
{
    if(p != NULL)
    {
        pcap_dump((u_char *) dumpd, p->pkth, p->pkt);
        fflush((FILE *) dumpd);
    }
}



/****************************************************************************
 *
 * Function: IcmpFileName(Packet *p)
 *
 * Purpose: Set the filename of an ICMP output log according to its type
 *
 * Arguments: p => Packet data struct
 *
 * Returns: the name of the file to set
 *
 ***************************************************************************/
char *IcmpFileName(Packet * p)
{
    switch(p->icmph->type)
    {
        case ICMP_ECHOREPLY:
            return "ECHO_REPLY";

        case ICMP_DEST_UNREACH:
            switch(p->icmph->code)
            {
                case ICMP_NET_UNREACH:
                    return "NET_UNRCH";

                case ICMP_HOST_UNREACH:
                    return "HST_UNRCH";

                case ICMP_PROT_UNREACH:
                    return "PROTO_UNRCH";

                case ICMP_PORT_UNREACH:
                    return "PORT_UNRCH";

                case ICMP_FRAG_NEEDED:
                    return "UNRCH_FRAG_NEEDED";

                case ICMP_SR_FAILED:
                    return "UNRCH_SOURCE_ROUTE_FAILED";

                case ICMP_NET_UNKNOWN:
                    return "UNRCH_NETWORK_UNKNOWN";

                case ICMP_HOST_UNKNOWN:
                    return "UNRCH_HOST_UNKNOWN";

                case ICMP_HOST_ISOLATED:
                    return "UNRCH_HOST_ISOLATED";

                case ICMP_NET_ANO:
                    return "UNRCH_NET_ANO";

                case ICMP_HOST_ANO:
                    return "UNRCH_HOST_ANO";

                case ICMP_NET_UNR_TOS:
                    return "UNRCH_NET_UNR_TOS";

                case ICMP_HOST_UNR_TOS:
                    return "UNRCH_HOST_UNR_TOS";

                case ICMP_PKT_FILTERED:
                    return "UNRCH_PACKET_FILT";

                case ICMP_PREC_VIOLATION:
                    return "UNRCH_PREC_VIOL";

                case ICMP_PREC_CUTOFF:
                    return "UNRCH_PREC_CUTOFF";

                default:
                    return "UNKNOWN";

            }

        case ICMP_SOURCE_QUENCH:
            return "SRC_QUENCH";

        case ICMP_REDIRECT:
            return "REDIRECT";

        case ICMP_ECHO:
            return "ECHO";

        case ICMP_TIME_EXCEEDED:
            return "TTL_EXCEED";

        case ICMP_PARAMETERPROB:
            return "PARAM_PROB";

        case ICMP_TIMESTAMP:
            return "TIMESTAMP";

        case ICMP_TIMESTAMPREPLY:
            return "TIMESTAMP_RPL";

        case ICMP_INFO_REQUEST:
            return "INFO_REQ";

        case ICMP_INFO_REPLY:
            return "INFO_RPL";

        case ICMP_ADDRESS:
            return "ADDR";

        case ICMP_ADDRESSREPLY:
            return "ADDR_RPL";

        default:
            return "UNKNOWN";
    }
}



/****************************************************************************
 *
 * Function: InitLogFile(char *logname)
 *
 * Purpose: Initialize the tcpdump log file header
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ***************************************************************************/
void InitBinLogFile(char *logname)
{
    time_t curr_time;       /* place to stick the clock data */
    struct tm *loc_time;    /* place to stick the adjusted clock data */
    char timebuf[10];
    char logdir[STD_BUF];

    bzero((char *) timebuf, 10);
    curr_time = time(NULL);
    loc_time = localtime(&curr_time);

    strftime(timebuf, 91, "%m%d@%H%M", loc_time);

/*    bzero((char *) logdir, STD_BUF);

    if(strlen(pv.log_dir) + strlen(timebuf) + 12 < STD_BUF)
        sprintf(logdir, "%s/snort-%s.log", pv.log_dir, timebuf);*/

    if (logname != NULL && strlen(logname) != 0)
    {
        if (strlen(pv.log_dir) + strlen(logname) + 
            strlen( chrootdir == NULL ? "" : chrootdir) + 2 < sizeof(logdir))
        {
            snprintf (logdir, sizeof(logdir) -1, "%s%s/%s",
                      chrootdir == NULL ? "" : chrootdir, pv.log_dir, logname);
	    }
        else
	    {
            FatalError("ERROR => InitBinLogFile(logname) %s\n", logname);
        }
    }
    else
    {
        bzero((char *) timebuf, 10);
        curr_time = time(NULL);
        loc_time = localtime(&curr_time);
    
        strftime(timebuf, 91, "%m%d@%H%M", loc_time);
    
        bzero((char *) logdir, sizeof(logdir));
    
        if(strlen(pv.log_dir) + strlen(timebuf) + 
           strlen( chrootdir == NULL ? "" : chrootdir) + 12 < sizeof(logdir))
        {
            snprintf(logdir, sizeof(logdir) -1,  "%s%s/snort-%s.log", 
                     chrootdir == NULL ? "" : chrootdir, pv.log_dir, timebuf);
        }
    }

#ifdef DEBUG
    printf("Opening %s\n", logdir);
#endif

    if((dumpd = pcap_dump_open(pd, logdir)) == NULL)
    {
        FatalError("ERROR => InitBinLogFile(%s) pcap_dump_open: %s\n",
			logdir, strerror(errno));
    }
#ifdef DEBUG
    printf("BinLogFile file initialized\n");
#endif

    return;
}
