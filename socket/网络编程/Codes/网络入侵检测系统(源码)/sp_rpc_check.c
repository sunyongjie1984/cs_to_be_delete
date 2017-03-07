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

/* $Id: sp_rpc_check.c,v 1.4 2001/01/02 08:06:01 roesch Exp $ */
#include "sp_rpc_check.h"

extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */


/****************************************************************************
 * 
 * Function: SetupRpcCheck()
 *
 * Purpose: Register the rpc option keyword with its setup function
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetupRpcCheck()
{
    /* map the keyword to an initialization/processing function */
    RegisterPlugin("rpc", RpcCheckInit);

#ifdef DEBUG
    printf("Plugin: RPCCheck Initialized\n");
#endif
}


/****************************************************************************
 * 
 * Function: RpcCheckInit(char *, OptTreeNode *)
 *
 * Purpose: Parse the rpc keyword arguments and link the detection module
 *          into the function list
 *
 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *
 * Returns: void function
 *
 ****************************************************************************/
void RpcCheckInit(char *data, OptTreeNode *otn, int protocol)
{
    /* allocate the data structure and attach it to the
       rule's data struct list */
    otn->ds_list[PLUGIN_RPC_CHECK] = (RpcCheckData *) calloc(sizeof(RpcCheckData), sizeof(char));

    /* this is where the keyword arguments are processed and placed into the 
       rule option's data structure */
    ParseRpc(data, otn);

    /* finally, attach the option's detection function to the rule's 
       detect function pointer list */
    AddOptFuncToList(CheckRpc, otn);
}



/****************************************************************************
 * 
 * Function: ParseRpc(char *, OptTreeNode *)
 *
 * Purpose: Parse the RPC keyword's arguments
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseRpc(char *data, OptTreeNode *otn)
{
    RpcCheckData *ds_ptr;  /* data struct pointer */
    char *tmp;

    /* set the ds pointer to make it easier to reference the option's
       particular data struct */
    ds_ptr = otn->ds_list[PLUGIN_RPC_CHECK];
    ds_ptr->flags=0;

    /* advance past whitespace */
    while(isspace((int)*data)) data++;

    if(*data != '*')
    {
        ds_ptr->program = strtoul(data,&tmp,0);
        ds_ptr->flags|=RPC_CHECK_PROG;
#ifdef DEBUG
        printf("Set RPC program to %lu\n", ds_ptr->program);
#endif
    }
    if(*tmp == '\0') return;
    data=++tmp;
    if(*data != '*')
    {
        ds_ptr->vers = strtoul(data,&tmp,0);
        ds_ptr->flags|=RPC_CHECK_VERS;
#ifdef DEBUG
        printf("Set RPC vers to %lu\n", ds_ptr->vers);
#endif
    }
    else
    {
        tmp++;
    }
    if(*tmp == '\0') return;
    data=++tmp;
    if(*data != '*')
    {
        ds_ptr->proc = strtoul(data,&tmp,0);
        ds_ptr->flags|=RPC_CHECK_PROC;
#ifdef DEBUG
        printf("Set RPC proc to %lu\n", ds_ptr->proc);
#endif
    }
}


/****************************************************************************
 * 
 * Function: CheckRpc(char *, OptTreeNode *)
 *
 * Purpose: Test if the packet RPC equals the rule option's rpc
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: 0 on failure, return value of next list function on success
 *
 ****************************************************************************/
int CheckRpc(Packet *p, struct _OptTreeNode *otn, OptFpList *fp_list)
{
    RpcCheckData *ds_ptr;  /* data struct pointer */
    unsigned char* c=(unsigned char*)p->data;
    u_long xid, rpcvers, prog, vers, proc;
    enum msg_type direction;
#ifdef DEBUG
    int i;
#endif
    if(!p->iph || (p->iph->ip_proto == IPPROTO_TCP && !p->tcph)
       || (p->iph->ip_proto == IPPROTO_UDP && !p->udph))
        return 0; /* if error occured while ip header
                   * was processed, return 0 automagically.
               */

    if(p->iph->ip_proto == IPPROTO_TCP)
    {
        /* offset to rpc_msg */
        c+=4;
        /* Fail if the packet is too short to match */
        if(p->dsize<28)
        {
#ifdef DEBUG
            puts("RPC packet too small");
#endif
            return 0;
        }
    }
    else
    { /* must be UDP */
        /* Fail if the packet is too short to match */
        if(p->dsize<24)
        {
#ifdef DEBUG
            puts("RPC packet too small");
#endif
            return 0;
        }
    }

#ifdef DEBUG
    printf("<---xid---> <---dir---> <---rpc---> <---prog--> <---vers--> "
           "<---proc-->\n");
    for(i=0; i<24; i++)
    {
        printf("%02X ",c[i]);
    }
    printf("\n");
#endif

    /* Read xid */
    xid = IXDR_GET_LONG (c);

    /* Read direction : CALL or REPLY */
    direction = IXDR_GET_ENUM (c, enum msg_type);

    /* We only look at calls */
    if(direction != CALL)
    {
#ifdef DEBUG
        puts("RPC packet not a call");
#endif
        return 0;
    }

    /* Read the RPC message version */
    rpcvers = IXDR_GET_LONG (c);

    /* Fail if it is not right */
    if(rpcvers != RPC_MSG_VERSION)
    {
#ifdef DEBUG
        puts("RPC msg version invalid");
#endif
        return 0;
    }

    /* Read the program number, version, and procedure */
    prog = IXDR_GET_LONG (c);
    vers = IXDR_GET_LONG (c);
    proc = IXDR_GET_LONG (c);

#ifdef DEBUG
    printf("RPC decoded to: %lu %lu %lu\n",
           prog,vers,proc);
#endif

    ds_ptr=(RpcCheckData *)otn->ds_list[PLUGIN_RPC_CHECK];
#ifdef DEBUG
    printf("RPC matching on: %d %d %d\n",
           ds_ptr->flags & RPC_CHECK_PROG,ds_ptr->flags & RPC_CHECK_VERS,
           ds_ptr->flags & RPC_CHECK_PROC);
#endif

    if(!(ds_ptr->flags & RPC_CHECK_PROG) ||
       ds_ptr->program == prog)
    {
#ifdef DEBUG
        puts("RPC program matches");
#endif
        if(!(ds_ptr->flags & RPC_CHECK_VERS) ||
           ds_ptr->vers == vers)
        {
#ifdef DEBUG
            puts("RPC version matches");
#endif
            if(!(ds_ptr->flags & RPC_CHECK_PROC) ||
               ds_ptr->proc == proc)
            {
#ifdef DEBUG
                puts("RPC proc matches");
                puts("Yippee! Found one!");
#endif

                /* call the next function in the function list recursively */
                return fp_list->next->OptTestFunc(p, otn, fp_list->next);
            }
        }
    }
#ifdef DEBUG
    else
    {
        /* you can put debug comments here or not */
        printf("RPC not equal\n");
    }
#endif

    /* if the test isn't successful, return 0 */
    return 0;
}
