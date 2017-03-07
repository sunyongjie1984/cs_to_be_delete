/* $Id: sp_respond.c,v 1.5 2001/01/02 08:06:01 roesch Exp $ */
/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 1999,2000,2001 Christian Lademann <cal@zls.de>
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

/* $Id: sp_respond.c,v 1.5 2001/01/02 08:06:01 roesch Exp $ */

/*
** CREDITS:
**
** The functionality presented here was inspired by
** the program "couic" by Michel Arboi <arboi@bigfoot.com>
**
*/


#ifdef ENABLE_RESPONSE

    #include <libnet.h>
    #include "sp_respond.h"

int nd; /* raw socket descriptor */
extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */





/**************************************************************************
 *
 * Function: SetupRespond();
 *
 * Purpose: Initialize repsond plugin
 *
 * Arguments: None.
 *
 * Returns: void
 **************************************************************************/

void SetupRespond()
{
    RegisterPlugin("resp", RespondInit);
#ifdef DEBUG
    printf("Plugin: Respond Setup\n");
#endif
    nd = -1;
}

void RespondInit(char *data, OptTreeNode *otn, int protocol) 
{
    RespondData *rd;
    if(nd == -1) /* need to open it only once */
    {
        if((nd = libnet_open_raw_sock(IPPROTO_RAW)) < 0)
        {
            FatalError("ERROR: cannot open raw socket for libnet, exiting...\n");
        }
    }
    if(( rd = (RespondData *)calloc(sizeof(RespondData), sizeof(char))) == NULL)
    {
        FatalError("ERROR => sp_respnd RespondInit() calloc failed!\n");
    }
    rd->response_flag = ParseResponse(data);
    AddRspFuncToList(Respond, otn->proto_node, (void *)rd );

}

/****************************************************************************
 *
 * Function: ParseResponse(char *)
 *
 * Purpose: Figure out how to handle hostile connection attempts
 *
 * Arguments: type => string of comma-sepatared modifiers
 *
 * Returns: void function
 *
 ***************************************************************************/
int ParseResponse(char *type)
{
    char *p;
    int response_flag;

    while(isspace((int) *type))
        type++;

    if(!type || !(*type))
        return 0;

    response_flag = 0;

    p = strtok(type, ",");
    while(p)
    {
        if(!strncasecmp(p, "rst_snd", 7))
            response_flag |= RESP_RST_SND;
        else if(!strncasecmp(p, "rst_rcv", 7))
            response_flag |= RESP_RST_RCV;
        else if(!strncasecmp(p, "rst_all", 7))
            response_flag |= (RESP_RST_SND | RESP_RST_RCV);
        else if(!strncasecmp(p, "icmp_net", 8))
            response_flag |= RESP_BAD_NET;
        else if(!strncasecmp(p, "icmp_host", 9))
            response_flag |= RESP_BAD_HOST;
        else if(!strncasecmp(p, "icmp_port", 9))
            response_flag |= RESP_BAD_PORT;
        else if(!strncasecmp(p, "icmp_all", 9))
            response_flag |= (RESP_BAD_NET | RESP_BAD_HOST | RESP_BAD_PORT);
        else
        {
            FatalError("ERROR %s (%d): invalid response modifier: %s\n", file_name, file_line, p);
        }

        p = strtok(NULL, ",");
    }
    return response_flag;
}




/****************************************************************************

 *
 * Function: Respond(Packet *p, RspFpList)
 *
 * Purpose: Respond to hostile connection attempts
 *
 * Arguments:
 *
 * Returns: void function
 *
 ***************************************************************************/

int Respond(Packet *p, RspFpList *fp_list)
{
    RespondData *rd = (RespondData *)fp_list->params;

    if(rd->response_flag)
    {
        if(rd->response_flag & (RESP_RST_SND | RESP_RST_RCV))
        {
            if(p->iph->ip_proto == IPPROTO_TCP && p->tcph != NULL)
            {
                int i;

                for(i = 0; i < 5; i++)
                {
                    if(rd->response_flag & RESP_RST_SND)
                        SendTCPRST(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                                   p->tcph->th_dport, p->tcph->th_sport,
                                   ntohl(p->tcph->th_ack), ntohl(p->tcph->th_seq) + p->dsize + i);

                    if(rd->response_flag & RESP_RST_RCV)
                        SendTCPRST(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                                   p->tcph->th_sport, p->tcph->th_dport,
                                   ntohl(p->tcph->th_seq), ntohl(p->tcph->th_ack) + p->dsize + i);
                }
            }
        }
        if(rd->response_flag & RESP_BAD_NET)
            SendICMP_UNREACH(ICMP_UNREACH_NET, p->iph->ip_dst.s_addr,
                             p->iph->ip_src.s_addr, p);

        if(rd->response_flag & RESP_BAD_HOST)
            SendICMP_UNREACH(ICMP_UNREACH_HOST, p->iph->ip_dst.s_addr,
                             p->iph->ip_src.s_addr, p);

        if(rd->response_flag & RESP_BAD_PORT)
            SendICMP_UNREACH(ICMP_UNREACH_PORT, p->iph->ip_dst.s_addr,
                             p->iph->ip_src.s_addr, p);
    }
    return 1; /* always success */
}


int SendICMP_UNREACH(int type, u_long saddr, u_long daddr, Packet * p)
{
    u_char *buf;
    int data_sz, addt_sz, sz;


    if(!p)
        return(-1);

    data_sz = (p->dsize > 8 ? 8 : p->dsize);
    addt_sz = ntohs(p->iph->ip_len) + data_sz;
    sz = IP_H + ICMP_UNREACH_H + addt_sz;

    if(libnet_init_packet(sz, &buf) < 0)
    {
        libnet_error(LIBNET_ERR_CRITICAL, "SendICMP_UNREACH: libnet_init_packet");
        return -1;
    }
    memset(buf, 0, sz);

    libnet_build_ip(ICMP_UNREACH_H + addt_sz, 0xF4,
                    (unsigned short)libnet_get_prand(PRu16) /* IP ID */ ,
                    0 /* fragmentation */ , 64 /* TTL */ , IPPROTO_ICMP,
                    saddr, daddr, NULL, 0, buf);

    libnet_build_icmp_unreach(ICMP_UNREACH, type,
                              p->iph->ip_len, p->iph->ip_tos, p->iph->ip_id,
                              p->iph->ip_off, p->iph->ip_ttl, p->iph->ip_proto,
                              p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                              p->data, data_sz,
                              buf + IP_H);

    libnet_do_checksum(buf, IPPROTO_ICMP, sz - IP_H);

    if(libnet_write_ip(nd, buf, sz) < sz)
    {
        libnet_error(LIBNET_ERR_CRITICAL, "SendICMP_UNREACH: libnet_write_ip");
        return -1;
    }
    return 0;
}


int SendTCPRST(u_long saddr, u_long daddr, u_short sport, u_short dport, u_long seq, u_long ack)
{
    u_char *buf;
    int sz = IP_H + TCP_H;


    if((buf = malloc(sz)) == NULL)
    {
        perror("SendTCPRST: malloc");
        return -1;
    }
    memset(buf, 0, sz);

    libnet_build_ip(TCP_H, 0,
                    (unsigned short)libnet_get_prand(PRu16) /* IP ID */ ,
                    0 /* fragmentation */ , 64 /* TTL */ , IPPROTO_TCP,
                    saddr, daddr, NULL, 0, buf);

    libnet_build_tcp(ntohs(sport), ntohs(dport), seq, ack,
                     TH_RST|TH_ACK, 0, 0, NULL, 0, buf + IP_H);


    libnet_do_checksum(buf, IPPROTO_TCP, sz - IP_H);
    if(libnet_write_ip(nd, buf, sz) < sz)
    {
        libnet_error(LIBNET_ERR_CRITICAL, "SendTCPRST: libnet_write_ip");
        return -1;
    }
    libnet_destroy_packet(&buf);
    return 0;
}

#endif
