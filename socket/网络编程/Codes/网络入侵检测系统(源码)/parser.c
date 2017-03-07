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

/* $Id: parser.c,v 1.6 2001/01/02 08:06:00 roesch Exp $ */

#include "parser.h"
extern char *file_name;
extern char *file_line;
extern RuleListNode *RuleLists;
extern int rule_count;
extern FILE *rule_file;
extern ListHead *head_tmp;

/****************************************************************************
 *
 * Function: ProcessAlertFileOption(char *)
 *
 * Purpose: define the alert file
 *
 * Arguments: filespec => the file specification
 *
 * Returns: void function
 *
 ***************************************************************************/
void ProcessAlertFileOption(char *filespec)
{
    pv.alert_filename = ProcessFileOption(filespec);

#if DEBUG
    printf("alertfile set to: %s\n", pv.alert_filename);
#endif

    return;
}

char *ProcessFileOption(char *filespec)
{
    char *filename;
    char buffer[STD_BUF];

    /* look for ".." in the string and complain and exit if it is found */
    if(strstr(filespec, "..") != NULL)
    {
        FatalError("ERROR: file definition contains \"..\".  Do not do that!\n");
    }

    if(filespec[0] == '/')
    {
        /* absolute filespecs are saved as is */
        filename = strdup(filespec);
    }
    else
    {
        /* relative filespec is considered relative to the log directory */
        /* or /var/log if the log directory has not been set */
        if(pv.log_flag)
        {
            strncpy(buffer, pv.log_dir, STD_BUF - 1);
        }
        else
        {
            strncpy(buffer, "/var/log", STD_BUF - 1);
        }

        strncat(buffer, "/", STD_BUF - strlen(buffer) - 1);
        strncat(buffer, filespec, STD_BUF - strlen(buffer) - 1);
        filename = strdup(buffer);
    }

    printf("ProcessFileOption: %s\n", filename);

    return filename;
}

void ParseConfig(char *rule)
{
    char **toks;
    char **config_decl;
    char *args = NULL;
    char *config;
    int num_toks;

    toks = mSplit(rule, ":", 2, &num_toks, 0);

    if(num_toks >= 1)
    {
        args = toks[1];
    }

    config_decl = mSplit(toks[0], " ", 2, &num_toks, '\\');

    if(num_toks != 2)
    {
        FatalError("Error parsing config: %s\n", rule);
    }

    config = config_decl[1];

#ifdef DEBUG
    printf("Config: %s\n", config);
    printf("Args: %s\n", args);
#endif

    if(!strcasecmp(config, "order"))
    {
        if(!pv.rules_order_flag)
        {
            OrderRuleLists(args);

            return;
        }

#ifdef DEBUG
        else
            printf("Commandline option overiding rule file config\n");
#endif
    }

    if(!strcasecmp(config, "alertfile"))
    {
        toks = mSplit(args, " ", 1, &num_toks, 0);

        ProcessAlertFileOption(toks[0]);

        return;
    }

    FatalError("Error: Unknown config: %s\n", config);

    return;
}

/* verify that we are not reusing some other keyword */
int checkKeyword(char *keyword)
{
    RuleListNode *node = RuleLists;

    if(RuleType(keyword) != RULE_UNKNOWN)
    {
        return 1;
    }

    /* check the declared ruletypes now */
    while(node != NULL)
    {
        if(!strcmp(node->name, keyword))
        {
            return 1;
        }

        node = node->next;
    }

    return 0;
}

void ParseRuleTypeDeclaration(char *rule)
{
    char *input;
    char *keyword;
    char **toks;
    int num_toks;
    int type;
    int rval = 1;
    int i;
    ListHead *listhead = NULL;

    toks = mSplit(rule, " ", 10, &num_toks, 0);
    keyword = strdup(toks[1]);

    /* Verify keyword is unique */
    if(checkKeyword(keyword))
    {
        FatalError("ERROR line %s (%d): Duplicate keyword: %s\n",
                   file_name, file_line, keyword);
    }

#ifdef DEBUG
    printf("Declaring new rule type: %s\n", keyword);
#endif

    if(num_toks > 2)
    {
        if(strcasecmp("{", toks[2]) != 0)
        {
            FatalError("ERROR line %s (%d): Syntax error: %s\n",
                       file_name, file_line, rule);
        }
    }
    else
    {
        input = ReadLine(rule_file);
        for(i=0;i<num_toks;i++)
        {
            free(toks[i]);
        }
        toks = mSplit(input, " ", 2, &num_toks, 0);
        free(input);
    }

    input = ReadLine(rule_file);
    for(i=0;i<num_toks;i++)
    {
        free(toks[i]);
    }
    toks = mSplit(input, " ", 10, &num_toks, 0);

    /* read the type field */
    if(!strcasecmp("type", toks[0]))
    {
        type = RuleType(toks[1]);
        /* verify it is a valid ruletype */
        if((type != RULE_LOG) && (type != RULE_PASS) && (type != RULE_ALERT) &&
           (type != RULE_ACTIVATE) && (type != RULE_DYNAMIC))
        {
            FatalError("ERROR line %s (%d): Invalid type for rule type declaration: %s\n", file_name, file_line, toks[1]);
        }

#ifdef DEBUG
        printf("\ttype(%i): %s\n", type, toks[1]);
#endif

        if(type == RULE_PASS)
        {
            rval = 0;
        }

        listhead = CreateRuleType(keyword, type, rval, NULL);
    }
    else
    {
        FatalError("ERROR line %s (%d): Type not defined for rule file declaration: %s\n", file_name, file_line, keyword);
    }

    free(input);
    input = ReadLine(rule_file);
    for(i=0;i<num_toks;i++)
    {
        free(toks[i]);
    }

    toks = mSplit(input, " ", 2, &num_toks, 0);

    while(strcasecmp("}", toks[0]) != 0)
    {
        if(RuleType(toks[0]) != RULE_OUTPUT)
        {
            FatalError("ERROR line %s (%d): Not an output plugin decleration: %s\n", file_name, file_line, keyword);
        }

        head_tmp = listhead;
        ParseOutputPlugin(input);
        head_tmp = NULL;
        free(input);
        input = ReadLine(rule_file);

        for(i=0;i<num_toks;i++)
        {
            free(toks[i]);
        }
        toks = mSplit(input, " ", 2, &num_toks, 0);
    }

    return;
}


/* Adapted from ParseRule in rules.c */
void ParseDeclaredRuleType(char *rule)
{
    char **toks;
    int num_toks;
    RuleListNode *node;
    int protocol;
    int i;
    RuleTreeNode proto_node;

    toks = mSplit(rule, " ", 10, &num_toks, 0);
    node = RuleLists;

    while(node != NULL)
    {
        if(!strcmp(node->name, toks[0]))
            break;
        node = node->next;
    }

    /* if we did not find a match, then there is no such ruletype */
    if(node == NULL)
    {
        FatalError("ERROR line %s (%d) => Unknown rule type: %s\n",
                   file_name, file_line, toks[0]);
    }

    printf("[**] Rule start\n");
    printf("Rule id: %s\n", toks[0]);
    printf("Rule type: ");

    switch(node->mode)
    {
        case RULE_PASS:
            printf("Pass\n");
            break;
        case RULE_LOG:
            printf("Log\n");
            break;
        case RULE_ALERT:
            printf("Alert\n");
            break;
        default:
            printf("Unknown\n");
    }

    /* the rest of this function is almost identical to code in ParseRule */
    bzero((char *) &proto_node, sizeof(RuleTreeNode));

    proto_node.type = node->mode;

    /* set the rule protocol */
    protocol = WhichProto(toks[1]);

    /* Process the IP address and CIDR netmask */
    /* changed version 1.2.1 */
    /*
     * "any" IP's are now set to addr 0, netmask 0, and the normal rules are
     * applied instead of checking the flag
     */
    /*
     * if we see a "!<ip number>" we need to set a flag so that we can
     * properly deal with it when we are processing packets
     */
    /*
   if( *toks[2] == '!' )    
   {
       proto_node.flags |= EXCEPT_SRC_IP;
       ParseIP(&toks[2][1], (u_long *) & proto_node.sip,
               (u_long *) & proto_node.smask);
   }
   else
   {
       ParseIP(toks[2], (u_long *) & proto_node.sip,
               (u_long *) & proto_node.smask);
   }*/

    ProcessIP(toks[2], &proto_node, SRC);

    /* do the same for the port */
    if(ParsePort(toks[3], (u_short *) & proto_node.hsp,
                 (u_short *) & proto_node.lsp, toks[1],
                 (int *) &proto_node.not_sp_flag))
    {
        proto_node.flags |= ANY_SRC_PORT;
    }

    if(proto_node.not_sp_flag)
        proto_node.flags |= EXCEPT_SRC_PORT;

    /* New in version 1.3: support for bidirectional rules */
    /*
     * this checks the rule "direction" token and sets the bidirectional flag
     * if the token = '<>'
     */
    if(!strncmp("<>", toks[4], 2))
    {
#ifdef DEBUG
        printf("Bidirectional rule!\n");
#endif
        proto_node.flags |= BIDIRECTIONAL;
    }

    /* changed version 1.2.1 */
    /*
     * "any" IP's are now set to addr 0, netmask 0, and the normal rules are
     * applied instead of checking the flag
     */
    /*
     * if we see a "!<ip number>" we need to set a flag so that we can
     * properly deal with it when we are processing packets
     */
    /*
   if( *toks[5] == '!' )    
   {
#ifdef DEBUG
       printf("setting exception flag for dest IP\n");
#endif
       proto_node.flags |= EXCEPT_DST_IP;
       ParseIP(&toks[5][1], (u_long *) & proto_node.dip,
               (u_long *) & proto_node.dmask);
   }
   else
       ParseIP(toks[5], (u_long *) & proto_node.dip,
               (u_long *) & proto_node.dmask);
*/

    ProcessIP(toks[5], &proto_node, DST);

    if(ParsePort(toks[6], (u_short *) & proto_node.hdp,
                 (u_short *) & proto_node.ldp, toks[1],
                 (int *) &proto_node.not_dp_flag))
    {
        proto_node.flags |= ANY_DST_PORT;
    }
    if(proto_node.not_dp_flag)
        proto_node.flags |= EXCEPT_DST_PORT;

#ifdef DEBUG
    printf("proto_node.flags = 0x%X\n", proto_node.flags);
#endif

    if(&proto_node == NULL)
        printf("NULL proto_node\n");

    ProcessHeadNode(&proto_node, node->RuleList, protocol);
    rule_count++;
    ParseRuleOptions(rule, node->mode, protocol);
    for(i=0;i<num_toks;i++)
    {
        free(toks[i]);
    }

    return;
}


/* adapted from ParseRuleFule in rules.c */
char *ReadLine(FILE * file)
{
    char buf[STD_BUF];
    char *index;

    bzero((char *) buf, STD_BUF);

    /*
     * Read a line from file and return it. Skip over lines beginning with #,
     * ;, or a newline
     */
    while((fgets(buf, STD_BUF, file)) != NULL)
    {
        file_line++;
        index = buf;
#ifdef DEBUG2

        printf("Got line %s (%d): %s", file_name, file_line, buf);
#endif
        /* if it's not a comment or a <CR>, we return it */
        if((*index != '#') && (*index != 0x0a) && (*index != ';')
           && (index != NULL))
        {
            /* advance through any whitespace at the beginning of ther line */
            while(isspace((int) *index))
                index++;

            /* return a copy of the line */
            return strdup(buf);
        }
    }

    return NULL;
}
