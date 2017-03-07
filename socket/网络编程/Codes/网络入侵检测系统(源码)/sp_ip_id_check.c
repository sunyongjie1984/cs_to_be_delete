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

/* $Id: sp_ip_id_check.c,v 1.5 2001/01/27 05:09:08 roesch Exp $ */
#include "sp_ip_id_check.h"

extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */


/****************************************************************************
 * 
 * Function: SetupIpIdCheck()
 *
 * Purpose: Associate the id keyword with IpIdCheckInit
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetupIpIdCheck()
{
    /* map the keyword to an initialization/processing function */
    RegisterPlugin("id", IpIdCheckInit);

#ifdef DEBUG
    printf("Plugin: IpIdCheck Initialized\n");
#endif
}


/****************************************************************************
 * 
 * Function: IpIdCheckInit(char *, OptTreeNode *)
 *
 * Purpose: Setup the id data struct and link the function into option
 *          function pointer list
 *
 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *
 * Returns: void function
 *
 ****************************************************************************/
void IpIdCheckInit(char *data, OptTreeNode *otn, int protocol)
{
    /* allocate the data structure and attach it to the
       rule's data struct list */
    otn->ds_list[PLUGIN_IP_ID_CHECK] = (IpIdData *) calloc(sizeof(IpIdData), sizeof(char));

    /* this is where the keyword arguments are processed and placed into the 
       rule option's data structure */
    ParseIpId(data, otn);

    /* finally, attach the option's detection function to the rule's 
       detect function pointer list */
    AddOptFuncToList(IpIdCheckEq, otn);
}



/****************************************************************************
 * 
 * Function: ParseIpId(char *, OptTreeNode *)
 *
 * Purpose: Convert the id option argument to data and plug it into the 
 *          data structure
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseIpId(char *data, OptTreeNode *otn)
{
    IpIdData *ds_ptr;  /* data struct pointer */

    /* set the ds pointer to make it easier to reference the option's
       particular data struct */
    ds_ptr = otn->ds_list[PLUGIN_IP_ID_CHECK];

    /* get rid of any whitespace */
    while(isspace((int)*data))
    {
        data++;
    }

    ds_ptr->ip_id = htons((unsigned short)atoi(data));

#ifdef DEBUG
    printf("ID set to %ld\n", ds_ptr->ip_id);
#endif

}


/****************************************************************************
 * 
 * Function: IpIdCheckEq(char *, OptTreeNode *)
 *
 * Purpose: Test the ip header's id field to see if its value is equal to the
 *          value in the rule.  This is useful to detect things like "elite"
 *          numbers, oddly repeating numbers, etc.
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
int IpIdCheckEq(Packet *p, struct _OptTreeNode *otn, OptFpList *fp_list)
{
    if(!p->iph)
        return 0; /* if error occured while ip header
                   * was processed, return 0 automagically.
               */
    if(((IpIdData *)otn->ds_list[PLUGIN_IP_ID_CHECK])->ip_id == p->iph->ip_id)
    {
        /* call the next function in the function list recursively */
        return fp_list->next->OptTestFunc(p, otn, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        /* you can put debug comments here or not */
        printf("No match\n");
    }
#endif

    /* if the test isn't successful, return 0 */
    return 0;
}
