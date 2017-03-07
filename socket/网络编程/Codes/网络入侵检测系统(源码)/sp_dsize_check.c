/* $Id: sp_dsize_check.c,v 1.4 2001/01/02 08:06:00 roesch Exp $ */
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

#include "sp_dsize_check.h"

extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */


/****************************************************************************
 * 
 * Function: SetupDsizeCheck()
 *
 * Purpose: Attach the dsize keyword to the rule parse function
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetupDsizeCheck()
{
    /* map the keyword to an initialization/processing function */
    RegisterPlugin("dsize", DsizeCheckInit);

#ifdef DEBUG
    printf("Plugin: DsizeCheck Initialized\n");
#endif
}


/****************************************************************************
 * 
 * Function: DsizeCheckInit(char *, OptTreeNode *)
 *
 * Purpose: Parse the rule argument and attach it to the rule data struct, 
 *          then attach the detection function to the function list
 *
 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *
 * Returns: void function
 *
 ****************************************************************************/
void DsizeCheckInit(char *data, OptTreeNode *otn, int protocol)
{
    /* allocate the data structure and attach it to the
       rule's data struct list */
    otn->ds_list[PLUGIN_DSIZE_CHECK] = (DsizeCheckData *) calloc(sizeof(DsizeCheckData), sizeof(char));

    /* this is where the keyword arguments are processed and placed into the 
       rule option's data structure */
    ParseDsize(data, otn);

    /* NOTE: I moved the AddOptFuncToList call to the parsing function since
       the linking is best determined within that function */
}



/****************************************************************************
 * 
 * Function: ParseDsize(char *, OptTreeNode *)
 *
 * Purpose: Parse the dsize function argument and attach the detection
 *          function to the rule list as well.  
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseDsize(char *data, OptTreeNode *otn)
{
    DsizeCheckData *ds_ptr;  /* data struct pointer */

    /* set the ds pointer to make it easier to reference the option's
       particular data struct */
    ds_ptr = (DsizeCheckData *)otn->ds_list[PLUGIN_DSIZE_CHECK];

    while(isspace((int)*data)) data++;

    if(*data == '>')
    {
        data++;
        AddOptFuncToList(CheckDsizeGT, otn);
    }
    else if(*data == '<')
    {
        data++;
        AddOptFuncToList(CheckDsizeLT, otn);
    }
    else
    {
        AddOptFuncToList(CheckDsizeEq, otn);
    }

    while(isspace((int)*data)) data++;

    ds_ptr->dsize = atoi(data);

#ifdef DEBUG
    printf("Payload length = %d\n", ds_ptr->dsize);
#endif

}


/****************************************************************************
 * 
 * Function: CheckDsizeEq(char *, OptTreeNode *)
 *
 * Purpose: Test the packet's payload size against the rule payload size value
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns:  0 on failure, return value of next list function on success
 *
 ****************************************************************************/
int CheckDsizeEq(Packet *p, struct _OptTreeNode *otn, OptFpList *fp_list)
{
    if(((DsizeCheckData *)otn->ds_list[PLUGIN_DSIZE_CHECK])->dsize == p->dsize)
    {
        /* call the next function in the function list recursively */
        return fp_list->next->OptTestFunc(p, otn, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        /* you can put debug comments here or not */
        printf("Not equal\n");
    }
#endif

    /* if the test isn't successful, return 0 */
    return 0;
}



/****************************************************************************
 * 
 * Function: CheckDsizeGT(char *, OptTreeNode *)
 *
 * Purpose: Test the packet's payload size against the rule payload size 
 *          value.  This test determines if the packet payload size is 
 *          greater than the rule dsize.
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns:  0 on failure, return value of next list function on success
 *
 ****************************************************************************/
int CheckDsizeGT(Packet *p, struct _OptTreeNode *otn, OptFpList *fp_list)
{
    if(((DsizeCheckData *)otn->ds_list[PLUGIN_DSIZE_CHECK])->dsize < p->dsize)
    {
        /* call the next function in the function list recursively */
        return fp_list->next->OptTestFunc(p, otn, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        /* you can put debug comments here or not */
        printf("Not equal\n");
    }
#endif

    /* if the test isn't successful, return 0 */
    return 0;
}




/****************************************************************************
 * 
 * Function: CheckDsizeLT(char *, OptTreeNode *)
 *
 * Purpose: Test the packet's payload size against the rule payload size 
 *          value.  This test determines if the packet payload size is 
 *          less than the rule dsize.
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns:  0 on failure, return value of next list function on success
 *
 ****************************************************************************/
int CheckDsizeLT(Packet *p, struct _OptTreeNode *otn, OptFpList *fp_list)
{
    if(((DsizeCheckData *)otn->ds_list[PLUGIN_DSIZE_CHECK])->dsize > p->dsize)
    {
        /* call the next function in the function list recursively */
        return fp_list->next->OptTestFunc(p, otn, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        /* you can put debug comments here or not */
        printf("Not equal\n");
    }
#endif

    /* if the test isn't successful, return 0 */
    return 0;
}
