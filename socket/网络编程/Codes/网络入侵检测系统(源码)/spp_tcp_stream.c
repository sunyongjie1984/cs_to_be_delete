/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 1999,2000,2001 Christopher E. Cramer <cec@ee.duke.edu>
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

/* $Id: spp_tcp_stream.c,v 1.14 2001/01/18 21:49:06 cec Exp $ */

/* spp_tcp_stream
 * 
 * Purpose:
 *
 * Construct tcp streams from observed packets
 *
 * Usage:
 *
 * preprocessor stream: <arg set 1>, <arg set 2>, ...
 *
 * Arguments:  one or more of the following separated by commas
 *
 * timeout <timeout value>
 *
 * ports <port 1> ... <port N>
 *
 * maxbytes <maxbytes>
 *
 * <timeout>  - the max time in seconds for which a stream will be 
 *            kept alive if we haven't seen a packet for it
 * <port x>   - a server port to monitor.  we don't want to monitor 
 *            all tcp streams (do we?)
 * <maxbytes> - maximum bytes in our reconstructed packets
 *
 *     example: 
 *       preprocessor stream: timeout 5, ports 21 23 80 8080, maxbytes 16384
 *
 * Effect:
 *
 * creates a buffer for each observed tcp stream.  upon seeing a RETURN 
 * or receiving a maximum number of bytes, generate a packet containing 
 * the reconstructed data
 *
 * Comments:
 *
 * the size of <timeout> will directly impact the amount of memory used.  
 * The longer the timeout the more streams kept in memory, the greater 
 * the memory usage.
 *
 * To Do: 
 *    make buffers circular to avoid copying
 *    check RST packets to verify sequence number
 *    allow tighter checks on what we monitor - reduce memory usage.
 *
 */

#include "spp_tcp_stream.h"
#ifndef WIN32
       #include <strings.h>
       #include <sys/time.h>
#else
       #include <time.h>
#endif
#include <sys/types.h>

#undef HAVE_64

/* external globals from rules.c */
extern char *file_name;
extern int file_line;

TcpStreamData StreamData;
FILE *TcpStreamFile;
int sesscount = 0;

/*
 * Function: SetupTcpStream()
 *
 * Purpose: Registers the preprocessor keyword and initialization 
 *          function into the preprocessor list.  This is the function that
 *          gets called from InitPreprocessors() in plugbase.c.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 */
void SetupTcpStream()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterPreprocessor("stream", TcpStreamInit);

#ifdef DEBUG
    printf("Preprocessor: TcpStream is setup...\n");
#endif
}


/*
 * Function: TcpStreamInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void TcpStreamInit(u_char *args)
{
    int i;
#ifdef DEBUG
    printf("Preprocessor: TcpStream Initialized\n");
#endif

    /* parse the argument list from the rules file */
    for(i=0;i<256;i++)
        StreamData.heads[i] = (TcpStreamSession *)NULL;
    ParseTcpStreamArgs(args);

    /* Set the preprocessor function into the function list */
    AddFuncToPreprocList(TcpStreamPacket);
}



/*
 * Function: ParseTcpStreamArgs(char *)
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
void ParseTcpStreamArgs(char *args)
{
    /* your parsing function goes here, check out the other spp files
       for examples */

    char **toks, **secs;
    int num_toks, num_secs;
    int i,j;


    if(args == NULL)
    {
        FatalError("ERROR %s (%d)=> No arguments to TcpStream preprocessor!\n", file_name, file_line);
    }
    StreamData.maxbytes = 0x01<<12;
    StreamData.prunetime = 10;
    /* tokenize the argument list */
    secs = mSplit(args, ",", 33, &num_secs, '\\');

    for(i=0;i<num_secs;i++)
    {
        toks = mSplit(secs[i], " ", 33, &num_toks, '\\');
        if(strcmp(toks[0],"timeout") == 0)
        {
            if(num_toks != 2) FatalError("ERROR %s (%d)=> timeout takes 1 argument!\n",file_name,file_line);
            StreamData.prunetime = atoi(toks[1]);
            if(StreamData.prunetime <= 0)
            {
                FatalError("ERROR %s (%d)=> Time between prunings must be >0 seconds!\n",file_name,file_line);
            }
        }
        else if(strcmp(toks[0],"maxbytes") == 0)
        {
            if(num_toks != 2) FatalError("ERROR %s (%d)=> maxbytes takes 1 argument!\n",file_name,file_line);
            StreamData.maxbytes = atoi(toks[1]);
            if(StreamData.maxbytes < 0 || StreamData.maxbytes > (0x1 << 15))
            {
                FatalError("ERROR %s (%d)=> maxbytes must be >= 0 and <= 32K bytes!\n",file_name,file_line);
            }
        }
        else if(strcmp(toks[0],"ports") == 0)
        {
            for(j = 1; j < num_toks; j++)
            {
                StreamData.ports[j-1] = atoi(toks[j]);
            }   
            StreamData.num_entries = num_toks-1;
        }
        else
        {
            FatalError("ERROR %s (%d)=> unknown argument to preprocessor stream: %s!\n",file_name,file_line,toks[0]);
        }
        for(j=0;j<num_toks;j++)
            free(toks[j]);
    }
    for(i=0;i<num_secs;i++)
        free(secs[i]);
}


/*
 * Function: TcpStreamPacket(Packet *)
 *
 * Purpose:  take a packet, determine if it is tcp.  if so, is it the start of a stream?
 *           yes - create new stream.  no - do we have that stream?  yes - deal w/ packet.
 *           no - return
 *
 *
 * Arguments: p => pointer to the current packet data struct 
 *
 * Returns: void function
 *
 */
void TcpStreamPacket(Packet *p)
{
    int i;
    int pos;
#ifdef DEBUG
    char sip[16];
    char dip[16];
#endif
    u_long tm;
    TcpStreamSession * sptr = NULL;
    u_int32_t lack, lseq;
    int server_packet;
    u_long bytes_in_buf, made_packet;
    int bin;

    /* statuses (client-status & server-status) from TCP/IP Illustrated v1, p 241:
       0 - closed
       1 - listen
       2 - SYN_RCVD
       3 - SYN_SENT
       4 - ESTABLISHED  (data xfer mode)
       5 - CLOSE_WAIT
       6 - LAST_ACK
       7 - FIN_WAIT_1
       8 - CLOSING
       9 - FIN_WAIT_2
       10- TIME_WAIT
    */

    if(!PacketIsTCP(p))
    {
#ifdef DEBUG
        printf("It isn't TCP session traffic\n");
#endif
        return;
    }

    /* don't accept packets w/ bad checksums */
    if(p->csum_flags & CSE_IP || p->csum_flags & CSE_TCP)
    {
#ifdef DEBUG
        printf("Discarding packet based on checksum errors!\n");
#endif
        return;
    }

    if(p->tcph->th_ack == 0 && p->tcph->th_seq == 0)
    {
#ifdef DEBUG
        printf("TcpStream Preprocessor shouldn't be handling it's own packets! :-)\n");
#endif
        return;
    }

    for(i = 0; i < StreamData.num_entries; i++)
        if((StreamData.ports[i] == p->dp) || (StreamData.ports[i] == p->sp)) break;
    if(i == StreamData.num_entries) return;  /* not a monitored port */

    pc.tcp_stream_pkts ++;  /* a packet we use */

    if(StreamData.ports[i] == p->sp)
    {
        server_packet = 1;
    }
    else
    {
        server_packet = 0;
    }

    tm = TcpStreamTime();
    if(tm - StreamData.timestamp >= StreamData.prunetime)
    {
        TcpStreamPruneSessions();
        StreamData.timestamp = tm;
    }

    lack = ntohl(p->tcph->th_ack);
    lseq = ntohl(p->tcph->th_seq);
#if DEBUG
    strncpy(sip, inet_ntoa(p->iph->ip_src), 16);
    strncpy(dip, inet_ntoa(p->iph->ip_dst), 16);
    printf("Packet (%x %u/%u %i) - %s:%i -> %s:%i (%i)\n",p->tcph->th_flags,lseq,lack,p->tcph->th_win,sip,p->sp,dip,p->dp,p->dsize);
#endif 

    sptr = TcpStreamCheckSession(p,StreamData.ports[i], &bin);
    if(sptr == (TcpStreamSession *)NULL)
    {
        if(p->tcph->th_flags == R_SYN)
        { /* new stream, SYN packet */
            sptr = (TcpStreamSession *)malloc(sizeof(TcpStreamSession));
            sptr->next = StreamData.heads[bin];
            StreamData.heads[bin] = sptr;
            pc.tcp_streams ++;  /* new tcp stream */
            sptr->client_status = SYN_SENT;
            sptr->server_status = SYN_RCVD;
            sptr->c_inbuf = sptr->s_inbuf = 0;
            sptr->cip = p->iph->ip_src.s_addr;
            sptr->cp = p->sp;
            sptr->sip = p->iph->ip_dst.s_addr;
            sptr->sp = p->dp;
            sptr->c_first_seq = lseq + 1;
            sptr->c_last_acked = lseq + 1; /* cheat mode */
            sptr->c_buf_start = lseq + 1;
            sptr->c_last_byte = sptr->s_last_byte = 0;
            sptr->timestamp = tm;
            sptr->c_buf = NULL;
            sptr->s_buf = NULL;
            if(p->tcph->th_win > 0)
            {
                sptr->c_buf_siz = ntohs(p->tcph->th_win) + StreamData.maxbytes;
                sptr->c_buf = (u_char *)malloc(sptr->c_buf_siz);
                sptr->c_buf_allocd = 1;
            }
            else
            {
                sptr->c_buf_allocd = 0;
            }
            sptr->s_buf_allocd = 0;
        }
        return; /* either way, we are done here */
    }
    sptr->timestamp = tm;

    if(p->tcph->th_flags == R_SYN)    /* j'accuse - we have a stream, but */
        return;                           /* we've been sent a SYN - spoofer */

    if(p->tcph->th_flags & R_RST)
    {  /* handle RST by putting going to CLOSED state */
        sptr->client_status = CLOSED;
        sptr->server_status = CLOSED;
        sptr->c_inbuf = sptr->s_inbuf = 0;
        sptr->c_first_seq = lseq + 1;
        sptr->c_last_acked = lseq + 1; /* cheat mode */
        sptr->c_last_byte = sptr->s_last_byte = 0;
        sptr->timestamp = tm;
        return;
    }

    if(p->tcph->th_flags == (R_SYN | R_ACK))
    { /* SYN/ACK */
        if(!server_packet) return;  /* Client should not SYN/ACK */
        if(lack != sptr->c_first_seq) return; /* False SYN/ACK - bad seq*/
        if((sptr->client_status == SYN_SENT) && (sptr->server_status = SYN_RCVD))
        {
            sptr->s_first_seq = lseq+1;
            sptr->s_last_acked = lseq+1; /* cheat mode on */
            sptr->s_buf_start = lseq+1;
            sptr->client_status = ESTABLISHED; /* client happy, should send ACK */
            if(p->tcph->th_win != 0)
            {
                sptr->s_buf_siz = ntohs(p->tcph->th_win) + StreamData.maxbytes;
                sptr->s_buf = (u_char *) malloc(sptr->s_buf_siz);
                sptr->s_buf_allocd = 1;
            }
        }
        return;
    }

    /* If buffers haven't been allocated, try to do so here */
    if(!server_packet && !sptr->c_buf_allocd)
    {
        if(p->tcph->th_win != 0)
        {
            sptr->c_buf_siz = ntohs(p->tcph->th_win) + StreamData.maxbytes;
            sptr->c_buf = (u_char *) malloc(sptr->c_buf_siz);
            sptr->c_buf_allocd = 1;
        }
    }

    if(server_packet && !sptr->s_buf_allocd)
    {
        if(p->tcph->th_win != 0)
        {
            sptr->s_buf_siz = ntohs(p->tcph->th_win) + StreamData.maxbytes;
            sptr->s_buf = (u_char *) malloc(sptr->s_buf_siz);
            sptr->s_buf_allocd = 1;
        }
    }

#if DEBUG
    printf("statuses: %i/%i\n",sptr->server_status, sptr->client_status);
#endif

    /* Check here to see if we inject new server packet */
    if(!server_packet && sptr->server_status >= ESTABLISHED)
    {  /* check to see if server buffer has proper data */

        if(lack - sptr->s_first_seq > 0x7fffffff) bytes_in_buf = 0;
        else bytes_in_buf = lack - sptr->s_first_seq;

        /* shouldn't happen in a sane world */
        if(bytes_in_buf > sptr->s_buf_siz)
        {
#ifdef DEBUG
            ErrorMessage("[!] WARNING: TCP stream reassembler, Server Bytes in Buffer > Buffer Size (%i > %i)\n", bytes_in_buf, sptr->s_buf_siz);
#endif
            bytes_in_buf = sptr->s_buf_siz;
        }

        made_packet = 0;
        if(bytes_in_buf >= StreamData.maxbytes)
        {
            TcpStreamPacketize(p, sptr->s_buf, StreamData.maxbytes, server_packet);
            made_packet = StreamData.maxbytes;
        }
        else
        {
            if (!sptr->s_buf_allocd)
            {
#ifdef DEBUG
                printf("WARNING: TCP stream reassembler never got proper window size, setting to max!\n");
#endif
                sptr->s_buf_siz = 65536 + StreamData.maxbytes;
                sptr->s_buf = (u_char *) malloc(sptr->s_buf_siz);
                sptr->s_buf_allocd = 1;
            }
            
            for(i=bytes_in_buf; i > (int)(sptr->s_last_acked - sptr->s_first_seq); i--)
                if(sptr->s_buf[i-1] == 0xa || sptr->s_buf[i-1] == 0xd)
                {
                    TcpStreamPacketize(p, sptr->s_buf, i, server_packet);
                    made_packet = i;
                    break;
                }
        }

        if(sptr->s_buf_allocd == 1)
        {
            if(made_packet >= 0)
            {  /* shuffle data */
                for(i=made_packet; i<(int)bytes_in_buf; i++)
                {
                    sptr->s_buf[i-made_packet] = sptr->s_buf[i];
                }

                sptr->s_first_seq += made_packet;
                sptr->s_last_byte -= made_packet;
            }
        }
    }

    /* Check here to see if we inject client new packet */
    if(server_packet && sptr->client_status >= ESTABLISHED)
    {  /* check to see if client buffer has proper data */

        if(lack - sptr->c_first_seq > 0x7fffffff) bytes_in_buf = 0;
        else bytes_in_buf = lack - sptr->c_first_seq;

        /* shouldn't happen in a sane world */
        if(bytes_in_buf > sptr->c_buf_siz)
        {
#ifdef DEBUG
            ErrorMessage("[!] WARNING: TCP stream reassembler, Client Bytes in Buffer > Buffer Size (%i > %i)\n", bytes_in_buf, sptr->c_buf_siz);
#endif
            bytes_in_buf = sptr->c_buf_siz;
        }

        made_packet = 0;
        if(bytes_in_buf >= StreamData.maxbytes)
        {
            TcpStreamPacketize(p, sptr->c_buf, StreamData.maxbytes, server_packet);
            made_packet = StreamData.maxbytes;
        }
        else
        {
            if (!sptr->c_buf_allocd)
            {
#ifdef DEBUG
                printf("WARNING: TCP stream reassembler never got proper window size, setting to max!\n");
#endif
                sptr->c_buf_siz = 65536 + StreamData.maxbytes;
                sptr->c_buf = (u_char *) malloc(sptr->c_buf_siz);
                sptr->c_buf_allocd = 1;
            }
            
            for(i=bytes_in_buf; i > (int)(sptr->c_last_acked - sptr->c_first_seq); i--)
            {
                if(sptr->c_buf[i-1] == 0xa || sptr->c_buf[i-1] == 0xd)
                {
                    TcpStreamPacketize(p, sptr->c_buf, i, server_packet);
                    made_packet = i;
                    break;
                }
            }
        }
        if(made_packet >= 0)
        {  /* shuffle data */
            for(i=made_packet; i<(int)bytes_in_buf; i++)
            {
                sptr->c_buf[i-made_packet] = sptr->c_buf[i];
            }
            sptr->c_first_seq += made_packet;
            sptr->c_last_byte -= made_packet;    
        }
    }

    /* if something's been acknowledged, update last_acked 
       only if side being acked is in data transmission state
       this keeps us from acknowledging FIN and having 1 extra
       data byte in buffer
     */
    if(p->tcph->th_flags & R_ACK)
    {
        if(server_packet)
            sptr->c_last_acked = lack;
        if(!server_packet)
            sptr->s_last_acked = lack;
    }

    if((sptr->client_status == ESTABLISHED) && (sptr->server_status == SYN_RCVD))
    {
        if(server_packet) return; /* shouldn't see a server packet here */
        if(lack != sptr->s_first_seq) return; /* False ACK - bad seq */
        if(p->tcph->th_flags == R_ACK) sptr->server_status = ESTABLISHED;
        return;
    }

    if((sptr->client_status == ESTABLISHED || 
        sptr->client_status == CLOSE_WAIT) && 
       !server_packet)
    {
        /* Let's put new data in the buffers */
        pos = lseq - sptr->c_first_seq;
        if((unsigned long)(pos + p->dsize) < sptr->c_buf_siz && pos >= 0)
        {
            if((unsigned long)(pos + p->dsize) > sptr->c_last_byte) sptr->c_last_byte = pos + p->dsize;
#if DEBUG
            printf("Copying %i bytes to Client buffer at %i, lb now: %lu\n",p->dsize,pos,sptr->c_last_byte);
#endif
            /* make sure we have a buffer to write to */
            if(sptr->c_buf_allocd)
            {
                memcpy(sptr->c_buf + pos,p->data,p->dsize);
            }
            else
            {
                /* make a buffer based on the current window size */
                if (p->tcph->th_win != 0)
                {
                    sptr->c_buf_siz = ntohs(p->tcph->th_win) + StreamData.maxbytes;
                }
                else
                {
                    sptr->c_buf_siz = 65536 + StreamData.maxbytes;
                }
                sptr->c_buf = (u_char *) malloc(sptr->c_buf_siz);
                sptr->c_buf_allocd = 1;
                memcpy(sptr->c_buf + pos,p->data,p->dsize);
            }
        }
    }

    if((sptr->server_status == ESTABLISHED || 
        sptr->server_status == CLOSE_WAIT) && server_packet)
    {
        pos = lseq - sptr->s_first_seq;
        if((unsigned long)(pos + p->dsize) < sptr->s_buf_siz && pos >= 0)
        {
            if((unsigned long)(pos + p->dsize) > sptr->s_last_byte) sptr->s_last_byte = pos + p->dsize;
#if DEBUG
            printf("Copying %i bytes to Server buffer at %i, lb now: %lu\n",p->dsize,pos,sptr->s_last_byte);
#endif
            if(sptr->s_buf_allocd == 1)
            {
                memcpy(sptr->s_buf + pos,p->data,p->dsize);
            }
            else
            {
                if(p->tcph->th_win != 0)
                {
                    sptr->s_buf_siz = ntohs(p->tcph->th_win) + StreamData.maxbytes;
                }
                else
                {
                    sptr->s_buf_siz = 65536 + StreamData.maxbytes;
                }
                sptr->s_buf = (u_char *) malloc(sptr->s_buf_siz);
                sptr->s_buf_allocd = 1;
                memcpy(sptr->s_buf + pos,p->data,p->dsize);
            }
        }
    }

    if((sptr->server_status == ESTABLISHED) && 
       (sptr->client_status == ESTABLISHED) && 
       (p->tcph->th_flags & R_FIN))
    {
        if(server_packet)
        {
            sptr->server_status = FIN_WAIT_1;  /* server does active close */
            sptr->client_status = CLOSE_WAIT;
            sptr->s_fin_seq = lseq;
        }
        else
        {
            sptr->client_status = FIN_WAIT_1; /* client does active close */
            sptr->server_status = CLOSE_WAIT;
            sptr->c_fin_seq = lseq;
        }
    }

    if(sptr->server_status == CLOSE_WAIT && 
       server_packet && p->tcph->th_flags & R_FIN)
    {
        sptr->server_status = LAST_ACK;
        sptr->client_status = TIME_WAIT;
        sptr->c_fin_seq = lseq;
    }
    if(sptr->client_status == CLOSE_WAIT && 
       !server_packet && p->tcph->th_flags & R_FIN)
    {
        sptr->server_status = TIME_WAIT;
        sptr->client_status = LAST_ACK;
        sptr->s_fin_seq = lseq;
    }

    return;
}


/*
 * Function: TcpStreamTime()
 *
 * Purpose:  what can i say, i like having my own timing routines
 *
 * Arguments: none
 *
 * Returns: u_long number of seconds since beginning of time (unix-centric)
 *
 */
u_long TcpStreamTime()
{
    struct timeval t;
    gettimeofday(&t, (struct timezone *)NULL);
    return(t.tv_sec);
}

/*
 * Function: TcpStreamCheckSession(Packet *, int sp)
 *
 * Purpose:  return the TcpStreamSession of current packet (if any) w/ 
 * respect to server port sp
 *
 *
 * Arguments: 
 *
 * Returns: appropriate TcpStreamSession (or null)
 *
 */
TcpStreamSession * TcpStreamCheckSession(Packet *p, int sp, int *bin)
{
    TcpStreamSession *sptr;
    u_char hash;
    u_char *ptr;
    int i;

    for(ptr=(u_char *)&p->iph->ip_src, i=0, hash=0; i<8; i++,ptr++)
        hash += *ptr;  
    *bin = hash;

#if DEBUG
    printf("HASH: %x\n", hash);
#endif

    if(sp == p->sp)
    {  /* this is coming from the server */
        for(sptr=StreamData.heads[hash]; sptr!=NULL; sptr=sptr->next)
        {
            if(sptr->sip == p->iph->ip_src.s_addr && sptr->cip == p->iph->ip_dst.s_addr && sptr->sp == sp && sptr->cp == p->dp)
            {
                return sptr;
            }
        }
    }
    else
    {  /* data from the client */
        for(sptr=StreamData.heads[hash]; sptr!=NULL; sptr=sptr->next)
        {
            if(sptr->sip == p->iph->ip_dst.s_addr && sptr->cip == p->iph->ip_src.s_addr && sptr->sp == sp && sptr->cp == p->sp)
            {
                return sptr;
            }
        }
    }
    return(TcpStreamSession *)NULL;
}


/*
 * Function: TcpStreamPruneSessions()
 *
 * Purpose:  kill all inactive sessions
 *
 * Arguments: none
 *
 * Returns: void function
 *
 */
void TcpStreamPruneSessions()
{
    TcpStreamSession * sptr = NULL;
    TcpStreamSession * lastptr, *tmpptr;
    u_long tm;
    int i;
#if DEBUG
    int prunecount = 0;
    int remain=0;
    int orig=0;
#endif

#if DEBUG
    for(i=0;i<256;i++)
        for(sptr=StreamData.heads[i]; sptr!=NULL; sptr=sptr->next)
        {
            orig++;
        }

    printf("Trying to PRUNE!   %i streams\n",orig);
#endif

    tm = TcpStreamTime();

    for(i=0;i<256;i++)
    {
        for(sptr=StreamData.heads[i], lastptr=NULL; sptr!=NULL;)
        {
            if(tm - sptr->timestamp >= StreamData.prunetime)
            {
                tmpptr = sptr->next;

                if(lastptr == NULL)
                    StreamData.heads[i] = sptr->next;
                else
                    lastptr->next = sptr->next;

                if(sptr != NULL)
                {
                    if(sptr->c_buf != NULL)
                        free(sptr->c_buf);

                    if(sptr->s_buf != NULL)
                        free(sptr->s_buf);

                    free(sptr);

#if DEBUG
                    prunecount++;
#endif
                }

                sptr = tmpptr;
            }
            else
            {
                lastptr = sptr;
                sptr = sptr->next;
            }
        }
    }

#if DEBUG
    for(i=0;i<256;i++)
    {
        for(sptr=StreamData.heads[i]; sptr!=NULL; sptr=sptr->next)
        {
            remain++;
        }
    }

    printf("Done PRUNING!  %i deleted, %i remain\n",prunecount,remain);
#endif
    return;
}

void TcpStreamPacketize(Packet *pb, u_char *buf, u_long psize, int server_packet)
{
    Packet *p;
    int pcaplen;
    int hdrsize;
    struct pseudoheader       /* pseudo header for TCP checksum calculations */
    {
        u_int32_t sip, dip;   /* IP addr */
        u_int8_t  zero;       /* checksum placeholder */
        u_int8_t  protocol;   /* protocol number */
        u_int16_t tcplen;     /* tcp packet length */
    };
    struct pseudoheader ph;    /* pseudo header declaration */
    grinder_t tmp_grinder;

#ifdef DEBUG
    printf("Trying to make a new packet!  psize: %lu\n", psize);
#endif

    pc.rebuilt_tcp ++;  /* new phoney packet */

#ifdef DEBUG
    printf("Alignments: pb->pkth: %lx, pb->iph: %lx, pb->tcph: %lx\n",(u_long)pb->pkth & 0x03, (u_long)pb->iph & 0x03, (u_long)pb->tcph & 0x03);
#endif

    p = (Packet *) malloc(sizeof(Packet));
    if(p == NULL) return;

    pcaplen = 8 + sizeof(struct timeval);
#ifdef DEBUG
    printf("pcaplen = %i\n",pcaplen);
#endif

/* creating a fake NULL/IP/TCP packet */

    p->pkth = (struct pcap_pkthdr *)malloc(pcaplen + 4 + 40 + psize);  

    if(p->pkth == NULL)
    {
        free(p);
        return;
    }

    p->iph = (IPHdr *)((u_char*)p->pkth + pcaplen + 4);
    hdrsize = 40 + NULL_HDRLEN;

    p->tcph = (TCPHdr *)((u_char *) p->iph + 20);

#ifdef DEBUG
    printf("Alignments: p->pkth: %lx, p->iph: %lx, p->tcph: %lx\n",(u_long)p->pkth & 0x03, (u_long)p->iph & 0x03, (u_long)p->tcph & 0x03);
#endif

    memcpy((u_char *)p->pkth, (u_char *)pb->pkth, pcaplen);
    p->pkth->caplen = p->pkth->len = hdrsize + psize;

    p->pkt = ((u_char*)p->pkth + pcaplen);

    /* IP stuff */
    p->iph->ip_ver = 0x04;
    p->iph->ip_hlen = 0x05;
    p->iph->ip_src = pb->iph->ip_dst;
    p->iph->ip_dst = pb->iph->ip_src;
    p->iph->ip_tos = pb->iph->ip_tos;
    p->iph->ip_len = htons((unsigned short)(40 + psize));
    p->iph->ip_id = 0;
    p->iph->ip_off = htons(0);
    p->iph->ip_ttl = 255;
    p->iph->ip_proto = pb->iph->ip_proto;
    p->iph->ip_csum = 0;
    p->iph->ip_csum = checksum((u_short *)p->iph, 20, (u_short *)NULL, 0);

    /* TCP Stuff */

    memset(p->tcph,0,sizeof(TCPHdr));
    p->tcph->th_sport = pb->tcph->th_dport;
    p->tcph->th_dport = pb->tcph->th_sport;
    p->tcph->th_flags = R_PSH | R_ACK;
    p->tcph->th_off = 0x05;

    /* setup the pseudo header for checksum calculation */
    ph.sip = (u_int32_t)(p->iph->ip_src.s_addr);
    ph.dip = (u_int32_t)(p->iph->ip_dst.s_addr);
    ph.zero = 0;
    ph.protocol = p->iph->ip_proto;
    ph.tcplen = htons((unsigned short)(20 + psize));

    memcpy((u_char *)p->pkth+hdrsize+pcaplen, buf, psize);

    /* calculate the checksum */
    p->tcph->th_sum = checksum((u_int16_t *)&ph, 12, (u_int16_t *)(p->tcph), 20 + psize);

    tmp_grinder = grinder;
    grinder = DecodeNullPkt;
    ProcessPacket(NULL, p->pkth, p->pkt);
    grinder = tmp_grinder;

    free(p->pkth);
    free(p);
}
