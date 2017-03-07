/* $Id: sp_react.c,v 1.8 2001/01/02 08:06:01 roesch Exp $ */

/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 2000,2001 Maciej Szarpak
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

/* Snort React Plugin by Maciej Szarpak, Warsaw University of Technology */

/* sp_react.c 
 * 
 * Purpose:
 *
 * React! Deny the access to some unsuitable web-sites (like porn sites) or
 * close the offending connections.
 *
 * Arguments:
 *   
 * This plugin can take two basic arguments:
 *    block => closes the connection and sends a suitable HTML page to the
 *             browser (if got tcp 80 port packet)
 *    warn  => sends a HTML/JavaScript warning to the browser
 *
 * The following additional arguments are valid for this option:
 *    msg   	      => puts the msg option comment into the HTML page
 *    proxy <port_nr> => sends the respond code to the proxy port_nr
 *
 * Effect:
 *
 * Closes the connections by sending TCP RST packets (similar to resp option).
 * If the connection uses http or proxy server ports a visible information
 * to a browser user is send (HTML code).
 *
 */

#ifdef ENABLE_RESPONSE

    #include <libnet.h>
    #include "sp_react.h"

extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */
extern int nd; /* raw socket */

#endif

/****************************************************************************
 * 
 * Function: SetupReact()
 *
 * Purpose: Flexible response plugin. Registers the configuration function 
 *	    and links it to a rule keyword.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetupReact()
{

#ifdef ENABLE_RESPONSE
/* we need an empty plug otherwise. To avoid #ifdef in plugbase */

    RegisterPlugin("react", ReactInit);

#ifdef DEBUG
    printf("Plugin: React Initialized!\n");
#endif
#endif
}

#ifdef ENABLE_RESPONSE

/****************************************************************************
 * 
 * Function: ReactInit(char *, OptTreeNode *, int protocol)
 *
 * Purpose: React rule configuration function.  Handles parsing the rule 
 *          information and attaching the associated structures to the OTN.
 *
 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *	      protocol => current rule protocol
 *
 * Returns: void function
 *
 ****************************************************************************/
void ReactInit(char *data, OptTreeNode *otn, int protocol)
{
    ReactData *idx;

#ifdef DEBUG
    printf("In ReactInit()\n");
#endif


    if((idx = (ReactData *) calloc(sizeof(ReactData), sizeof(char))) == NULL)
    {
        FatalError("ERROR => sp_react ReactInit() calloc failed!\n");
    }

    /* parse the react keywords */
    ParseReact(data, otn, idx);

    /* finally, attach the option's detection function to the rule's 
       detect function pointer list */
    AddRspFuncToList(React, otn->proto_node, (void *)idx);

    return;
}



/****************************************************************************
 * 
 * Function: ParseReact(char *, OptTreeNode *)
 *
 * Purpose: React rule configuration function. Handles parsing the rule 
 *          information.
 *
 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseReact(char *data, OptTreeNode *otn, ReactData *rd)
{
    ReactData *idx;
    char *tok;      /* token buffer */
    u_int buf_size; 

    char tmp_buf1[] = "<HTML><HEAD><TITLE>Snort</TITLE></HEAD><BODY BGCOLOR=\"#FFFFFF\"><CENTER><BR><H1>Snort!</H1>Version ";
    char tmp_buf2[] = "<H1><BR><BR><FONT COLOR=\"#FF0000\">You are not authorized to open this site!</FONT><BR><BR></H1><H2>";
    char tmp_buf3[] = "<BR></H2><BR><A HREF=\"mailto:mszarpak@elka.pw.edu.pl\">Any questions?</A></CENTER></BODY></HTML>";    
    char tmp_buf4[]="<HTML><HEAD><SCRIPT LANGUAGE=\"JavaScript\"><!-- Hiding function pop() { alert(\"Snort, ver. ";
    char tmp_buf5[] = "\\n\\nThis page contents ...!\\n\\n";
    char tmp_buf6[] = "\"); } // --></SCRIPT></HEAD><BODY ONLOAD=\"pop()\"></BODY></HTML>";

#ifdef DEBUG
    printf("In ParseReact()\n");
#endif

    idx = rd;

    /* set the standard proxy port */
    idx->proxy_port_nr = 8080;

    /* parse the react option keywords */
    while(isspace((int)*data)) data++;

    tok = strtok(data, ",");
    while(tok)
    {
        if(!strncasecmp(tok, "block", 5))
            idx->reaction_flag = REACT_BLOCK;
        else if(!strncasecmp(tok, "warn", 4))
/*	    idx->reaction_flag = REACT_WARN*/;
        else if(!strncasecmp(tok, "msg", 3))
            if(otn->message == NULL)
                FatalError( "ERROR %s (%d) => msg option missed or react keyword placed before msg!\n", file_name, file_line);
            else
                idx->html_resp_size = 1;
        else if(!strncasecmp(tok, "proxy", 5))
        {
            /* convert the string port nr to int */
            idx->proxy_port_nr = atoi(tok+5);

            /* make sure it's in bounds */
            if((idx->proxy_port_nr < 0) || (idx->proxy_port_nr >= 65536))
            {
                FatalError("ERROR %s (%d) => bad proxy port number: %d\n", file_name, file_line, idx->proxy_port_nr);
            }
        }
        else
        {
            FatalError("ERROR %s (%d): invalid react modifier: %s\n", file_name, file_line, tok);
        }
        tok = strtok(NULL, ","); 

        /* get rid of spaces */
        if(tok != NULL)
            while(isspace((int)*tok)) tok++;
    }

    /* test the basic modifier */
    if(idx->reaction_flag == 0)
        FatalError("ERROR %s (%d): missing react basic modifier\n", file_name, file_line);
    else
    {
        /* prepare the html response data */
        buf_size = 0;
        if(idx->reaction_flag == REACT_BLOCK)
        {
            /* count the respond buf size (max TCP_DATA_BUF) */
            buf_size = strlen(tmp_buf1) + strlen(tmp_buf2) + strlen(tmp_buf3)
                       + strlen(VERSION);

            if(buf_size > TCP_DATA_BUF)
            {
                FatalError("ERROR %s (%d): invalid html response buffer size: %d\n", file_name, file_line, buf_size);
            }
            else
            {
                /* msg included */
                if((idx->html_resp_size == 1) && (buf_size + strlen(otn->message) < TCP_DATA_BUF))
                {
                    buf_size += strlen(otn->message);
                }

                /* create html response buffer */
                if((idx->html_resp_buf=(char *)malloc(sizeof(char)*buf_size))==NULL)
                {
                    FatalError( "ERROR => ParseReact() html_resp_buf malloc filed!\n");
                }
                bzero((char *)idx->html_resp_buf, buf_size);
                tok = strcat(idx->html_resp_buf, tmp_buf1);
                tok = strcat(idx->html_resp_buf, VERSION);
                tok = strcat(idx->html_resp_buf, tmp_buf2);      
                if(idx->html_resp_size == 1)
                {
                    tok = strcat(idx->html_resp_buf, otn->message);     
                }
                tok = strcat(idx->html_resp_buf, tmp_buf3);      
            }
        }
        else if(idx->reaction_flag == REACT_WARN)
        {
            /* count the respond buf size (max TCP_DATA_BUF) */
            buf_size = strlen(tmp_buf4) + strlen(tmp_buf5) + strlen(tmp_buf6)
                       + strlen(VERSION);

            if(buf_size > TCP_DATA_BUF)
            {
                FatalError("ERROR %s (%d): invalid html response buffer size: %d\n", file_name, file_line, buf_size);
            }
            else
            {
                /* msg included */
                if((idx->html_resp_size == 1) && (buf_size + strlen(otn->message) < TCP_DATA_BUF))
                {
                    buf_size += strlen(otn->message);
                }

                /* create html response buffer */
                if((idx->html_resp_buf=(char *)malloc(sizeof(char)*buf_size))==NULL)
                {
                    FatalError( "ERROR => ParseReact() html_resp_buf malloc filed!\n");
                }
                bzero((char *)idx->html_resp_buf, buf_size);
                tok = strcat(idx->html_resp_buf, tmp_buf4);
                tok = strcat(idx->html_resp_buf, VERSION);
                tok = strcat(idx->html_resp_buf, tmp_buf5);      
                if(idx->html_resp_size == 1)
                {
                    tok = strcat(idx->html_resp_buf, otn->message);     
                }
                tok = strcat(idx->html_resp_buf, tmp_buf6);      
            }
        }

        /* set the html response buffer size */
        idx->html_resp_size = buf_size;
    }

    return;
}



/****************************************************************************
 *
 * Function: React(Packet *p, OptTreeNode *otn_tmp)
 *
 * Purpose: React to hostile connection attempts according to reaction_flag
 *
 * Arguments: p => pointer to the current packet
 *	      otn => pointer to the current rule option list node
 *
 * Returns: Always calls the next function (this one doesn't test the data,
 *          it just closes the connection...)
 *
 ***************************************************************************/
int React(Packet *p,  RspFpList *fp_list)
{
    ReactData *idx;
    int i;

#ifdef DEBUG
    printf("In React()\n");
#endif

    idx = (ReactData *)fp_list->params;

    if(idx == NULL)
    {
#ifdef DEBUG
        printf("Nothing to do ... leaving");
#endif
        return 1;
    }

    /* check the reaction flag */
    if(idx->reaction_flag == REACT_BLOCK)
    {
        /* send HTML page buffer to a rude browser user and close the connection */
        /* incoming */
        if((ntohs(p->tcph->th_sport)) == 80 || (ntohs(p->tcph->th_sport)) == idx->proxy_port_nr)
        {
            for(i = 0; i < 5; i++)
            {
                SendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_FIN, idx->html_resp_buf, idx->html_resp_size);
            }
            for(i = 0; i < 5; i++)
            {
                SendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_RST, idx->html_resp_buf, 0);
            }
        }
        /* outgoing */
        else if(ntohs(p->tcph->th_dport) == 80 || (ntohs(p->tcph->th_dport)) == idx->proxy_port_nr)
        {
            for(i = 0; i < 5; i++)
            {
                SendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_FIN, idx->html_resp_buf, idx->html_resp_size);
                SendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_RST, idx->html_resp_buf, 0);
            }
        }
        else
        /* reset the connection */
        {
            for(i = 0; i < 5; i++)
            {
                SendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_RST, idx->html_resp_buf, 0);
                SendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_RST, idx->html_resp_buf, 0);
            }
        }
    }
    else if(idx->reaction_flag == REACT_WARN)
    { 
        /* send HTML warning page buffer to a rude browser user */
        /* incoming */
        if((ntohs(p->tcph->th_sport)) == 80 || (ntohs(p->tcph->th_sport)) == idx->proxy_port_nr)
        {
            for(i = 0; i < 5; i++)
            {
                SendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_URG, idx->html_resp_buf, idx->html_resp_size);
            }
        }
        /* outgoing */
        else if(ntohs(p->tcph->th_dport) == 80 || (ntohs(p->tcph->th_dport)) == idx->proxy_port_nr)
        {
            for(i = 0; i < 5; i++)
            {
                SendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_URG, idx->html_resp_buf, idx->html_resp_size);
            }
        }
    }
    return 1;
}    




int SendTCP(u_long saddr, u_long daddr, u_short sport, u_short dport, int seq,
            int ack, u_char bits, const u_char *data_buf, int data_size)
{
    u_char *buf;
    int sz = data_size + IP_H + TCP_H;

#ifdef DEBUG
    printf("In SendTCP()\n");
#endif

    if((buf = malloc(sz)) == NULL)
    {
        perror("SendTCPRST: malloc");
        return -1;
    }

    memset(buf, 0, sz);

    libnet_build_ip(TCP_H,
                    0xF4,
                    (unsigned short)libnet_get_prand(PRu16) /* IP ID */,
                    0 /* fragmentation */,
                    64 /* TTL */,
                    IPPROTO_TCP,
                    saddr, 
                    daddr, 
                    NULL, 
                    0,
                    (unsigned char *)buf);

    libnet_build_tcp(ntohs(sport), 
                     ntohs(dport),
                     ntohl(seq),
                     ntohl(ack),
                     bits,
                     1024,
                     0,
                     data_buf,
                     data_size,
                     buf + IP_H);

    libnet_do_checksum(buf, IPPROTO_TCP, sz - IP_H);

    if(libnet_write_ip(nd, buf, sz) < sz)
    {
        libnet_error(LIBNET_ERR_CRITICAL, "SendTCP: libnet_write_ip");
        return -1;
    }

    libnet_destroy_packet(&buf);

    return 0;

}

#endif
