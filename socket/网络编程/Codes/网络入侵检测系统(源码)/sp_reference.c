/* $Id: sp_reference.c,v 1.2 2001/01/02 08:06:01 roesch Exp $ */

/*
** Copyright (C) 2000,2001 Joe McAlerney, 
**                         Silicon Defense <joey@silicondefense.com>
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

/* sp_reference, Joe McAlerney, Silicon Defense, joey@silicondefense.com
 * 
 * Purpose:
 *
 * This plugin allows alerts to be associated with attack signatures in 
 * identification systems.  The plugin currently supports Bugtraq, CVE 
 * (and CAN), arachNIDS, McAfee virus, as well as custom systems. This plugin
 * is to be used by output plugins to provide a link to additional information
 * about the alert produced.
 * 
 * Arguments:
 *  
 * As this plugin is based on keywords in rules, there are no arguments. The
 * keyword is "reference".  The value is the ID system, and the ID itself.
 * The rule format is:
 *            
 *      reference: <idsystem>,<id>; [reference: <idsystem>,<id>;] [...]
 *
 * Effect:
 *
 * It stores the ID number and in the case of Bugtraq, CVE, arachNIDS, and
 * McAfee stores a URL to a place to find additional information on the 
 * signature.
 *
 * Here are a few examples.
 *
 * alert TCP any any -> any 80 (msg: "IDS128/web-cgi-phf"; flags: AP; \
 *           content: "phf"; reference: arachNIDS,IDS128; \
 *           reference: cve,CVE-1999-0067;)
 *
 * alert TCP any any -> any 7070 (msg: "IDS411/dos-realaudio"; flags: \
 *           AP; content: "|fff4 fffd 06|"; reference: arachNIDS,IDS411;)
 *
 * alert TCP any any -> any 25 (msg:"VIRUS - Possible Pikachu Pokemon Virus"; \
 *           flags: PA; content: "Pikachu Pokemon"; reference: McAfee,98696;)
 *
 * alert TCP any any -> any 21 (msg: "IDS287/ftp-wuftp260-venglin-linux"; \
 *           flags: AP; content: "|31c031db 31c9b046 cd80 31c031db|"; \
 *           reference: arachNIDS,IDS287; reference: bugtraq,1387; \
 *           reference: cve,CAN-2000-1574; )
 *
 * Comments:
 * 
 * If you would like to add your own reference URL's, see the function
 * "ReferenceRuleParseFunction".  Near the bottom is a template to use.
 * Make sure you define the URL head in the sp_reference.h file.
 */

#include "sp_reference.h"

extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */


/****************************************************************************
 * 
 * Function: SetupReferenceCheck()
 *
 * Purpose: Registers our keywords
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetupReference()
{
    /* map the keyword to an initialization/processing function */
    RegisterPlugin("reference", ReferenceInit);

#ifdef DEBUG
    printf("Plugin: Reference Setup\n");
#endif
}


/****************************************************************************
 * 
 * Function: ReferenceInit(char *, OptTreeNode *)
 *
 * Purpose: rule configuration functions

 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *
 * Returns: void function
 *
 ****************************************************************************/
void ReferenceInit(char *data, OptTreeNode *otn, int protocol)
{
    /* allocate the data structure and attach it to the
       rule's data struct list */

    /* whack a new node onto the list */
    NewReferenceNode(otn);

    /* this is where the keyword arguments are processed and placed into the 
       rule option's data structure */
    ReferenceRuleParseFunction(data, otn);
}

/****************************************************************************
 * 
 * Function: ReferenceRuleParseFunction(char *, OptTreeNode *)
 *
 * Purpose: This is the function that is used to process the option keyword's
 *          arguments and attach them to the rule's data structures.
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
void ReferenceRuleParseFunction(char *data, OptTreeNode *otn)
{
    ReferenceData *ds_ptr;  /* data struct pointer */
    char *url, *system, *id;

    /* set the ds pointer to make it easier to reference the option's
       particular data struct */
    ds_ptr = (ReferenceData *)otn->ds_list[PLUGIN_REFERENCE_NUMBER];

    /* are there any reference's for this one already? */
    while(ds_ptr->next != NULL)
      ds_ptr = ds_ptr->next;

    /* manipulate the option arguments here */
    while (isspace((int)*data)) data++;
    system = strtok(data, ",");
    id = strtok(NULL, ",");

    ds_ptr->system = system;
    ds_ptr->id = id;

    /* Attach a url for some well known ID systems */
    if(!strncasecmp(system, "bugtraq", 7))
    {
       url = calloc(strlen(BUGTRAQ_URL_HEAD) + strlen(id) + 1, sizeof(char));
       strncat(url,BUGTRAQ_URL_HEAD,strlen(BUGTRAQ_URL_HEAD) + 1);
       strncat(url,id,strlen(id) + 1);
       ds_ptr->url = url;
    }
    else if(!strncasecmp(system, "cve", 3))
    {
       url = calloc(strlen(CVE_URL_HEAD) + strlen(id) + 1, sizeof(char));
       strncat(url,CVE_URL_HEAD,strlen(CVE_URL_HEAD) + 1);
       strncat(url,id,strlen(id) + 1);
       ds_ptr->url = url;
    }
    else if(!strncasecmp(system, "arachNIDS", 9))
    {
       url = calloc(strlen(ARACHNIDS_URL_HEAD) + strlen(id) + 1, sizeof(char));
       strncat(url,ARACHNIDS_URL_HEAD,strlen(ARACHNIDS_URL_HEAD) + 1);
       strncat(url,id,strlen(id) + 1);
       ds_ptr->url = url;
    }
    else if(!strncasecmp(system, "McAfee", 6))
    {
       url = calloc(strlen(MCAFEE_URL_HEAD) + strlen(id) + 1, sizeof(char));
       strncat(url,MCAFEE_URL_HEAD,strlen(MCAFEE_URL_HEAD) + 1);
       strncat(url,id,strlen(id) + 1);
       ds_ptr->url = url;
    }
    /** Tag your own ID system url's on here
    else if(!strncasecmp(system, "my_id_system", 12))
    {
       url = calloc(strlen(MY_URL_HEAD) + strlen(id) + 1, sizeof(char));
       strncat(url,MY_URL_HEAD,strlen(MY_URL_HEAD) + 1);
       strncat(url,id,strlen(id) + 1);
       ds_ptr->url = url;
    }
    **/
}

/****************************************************************************
 * 
 * Function: NewReferenceNode(OptTreeNode *)
 *
 * Purpose: This function adds a new node to the ReferenceData linked list.
 *          The code was borrowed from NewNode in sp_pattern_match.c
 *
 * Arguments: otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
void NewReferenceNode(OptTreeNode * otn)
{
    ReferenceData *ds_ptr;

    ds_ptr = (ReferenceData *) otn->ds_list[PLUGIN_REFERENCE_NUMBER];

    if (ds_ptr == NULL)
    {
        if ((otn->ds_list[PLUGIN_REFERENCE_NUMBER] = (ReferenceData *) calloc(sizeof(ReferenceData),
sizeof(char))) == NULL)
        {
            FatalError("ERROR => sp_reference NewReferenceNode() calloc failed!\n");
        }
    } else
    {
        ds_ptr = otn->ds_list[PLUGIN_REFERENCE_NUMBER];

        while (ds_ptr->next != NULL)
            ds_ptr = ds_ptr->next;

        if ((ds_ptr->next = (ReferenceData *) calloc(sizeof(ReferenceData), sizeof(char))) == NULL)
        {
            FatalError("ERROR => sp_reference NewReferenceNode() calloc failed!\n");
        }
    }
}
