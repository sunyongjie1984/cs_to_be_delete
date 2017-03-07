/* $Id: rules.c,v 1.38 2001/01/26 19:03:07 roesch Exp $ */
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

#include "rules.h"

ListHead Alert;         /* Alert Block Header */
ListHead Log;           /* Log Block Header */
ListHead Pass;          /* Pass Block Header */
ListHead Activation;    /* Activation Block Header */
ListHead Dynamic;       /* Dynamic Block Header */

RuleTreeNode *rtn_tmp;      /* temp data holder */
OptTreeNode *otn_tmp;       /* OptTreeNode temp ptr */
ListHead *head_tmp = NULL;  /* ListHead temp ptr */

RuleListNode *RuleLists;

struct VarEntry *VarHead = NULL;

char *file_name;        /* current rules file being processed */
int file_line;          /* current line being processed in the rules
                         * file */
int list_file_line;     /* current line being processed in the list
                         * file */
int rule_count;         /* number of rules generated */
int head_count;         /* number of header blocks (chain heads?) */
int opt_count;          /* number of chains */
int do_detect;

int dynamic_rules_present;
int active_dynamic_nodes;

extern KeywordXlateList *KeywordList;   /* detection/response plugin keywords */
extern PreprocessKeywordList *PreprocessKeywords;   /* preprocessor plugin
                             * keywords */
extern PreprocessFuncNode *PreprocessList;  /* Preprocessor function list */
extern OutputKeywordList *OutputKeywords;   /* Output plugin keyword list */
extern OutputFuncNode *AlertList;   /* Alert function list */
extern OutputFuncNode *LogList; /* log function list */

/* Local Function Declarations */
OutputFuncNode *AppendOutputFuncList(void (*) (Packet *, char *, void *), void *,
                                     OutputFuncNode *);

#ifdef BENCHMARK
int check_count;        /* number of tests for a given rule to
                         * determine a match */
int cmpcount;           /* compare counter */
#endif


/****************************************************************************
 *
 * Function: ParseRulesFile(char *, int)
 *
 * Purpose:  Read the rules file a line at a time and send each rule to
 *           the rule parser
 *
 * Arguments: file => rules file filename
 *            inclevel => nr of stacked "include"s
 *
 * Returns: void function
 *
 ***************************************************************************/
FILE *rule_file;

void ParseRulesFile(char *file, int inclevel)
{
    FILE *thefp;        /* file pointer for the rules file */
    char buf[STD_BUF];      /* file read buffer */
    char *index;        /* buffer indexing pointer */
    char *stored_file_name = file_name;
    int stored_file_line = file_line;

#ifdef DEBUG
    printf("Opening rules file: %s\n", file);
#endif

    if(inclevel == 0)
    {
        if(!pv.quiet_flag)
        {
            printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("Initializing rule chains...\n");
        }

        file_name = strdup(file);
    }

    /* open the rules file */
    if((thefp = fopen(file, "r")) == NULL)
    {
        FatalError("ERROR: Unable to open rules file: %s\n", file);
    }

    /* clear the line buffer */
    bzero((char *) buf, STD_BUF);

    stored_file_line = file_line;
    stored_file_name = file_name;
    file_name = strdup(file);
    file_line = 0;

    rule_file = thefp;

    /* loop thru each file line and send it to the rule parser */
    while((fgets(buf, STD_BUF, thefp)) != NULL)
    {
        /*
         * inc the line counter so the error messages know which line to
         * bitch about
         */
        file_line++;

        index = buf;


#ifdef DEBUG2
        printf("Got line %s (%d): %s", file_name, file_line, buf);
#endif
        /* advance through any whitespace at the beginning of the line */
        while(*index == ' ' || *index == '\t')
            index++;

        /* if it's not a comment or a <CR>, send it to the parser */
        if((*index != '#') && (*index != 0x0a) && (*index != ';') && (index != NULL))
        {
            ParseRule(index, inclevel);
        }

        bzero((char *) buf, STD_BUF);
    }

    if(file_name)
        free(file_name);

    file_name = stored_file_name;
    file_line = stored_file_line;

    if(inclevel == 0 && !pv.quiet_flag)
    {
        printf("%d Snort rules read...\n", rule_count);
        printf("%d Option Chains linked into %d Chain Headers\n", opt_count, head_count);
        printf("%d Dynamic rules\n", dynamic_rules_present);
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
    }

    rule_file = NULL;
    fclose(thefp);

    /* plug all the dynamic rules together */
    if(dynamic_rules_present)
    {
        LinkDynamicRules();
    }

    if(inclevel == 0)
    {
#ifdef DEBUG
        DumpRuleChains();
#endif

        IntegrityCheckRules();

    }

    return;
}


int CheckRule(char *str)
{
    int len;
    int got_paren = 0;
    int got_semi = 0;
    char *index;

    len = strlen(str);

    index = str + len - 1; /* go to the end of the string */

    while((isspace((int)*index)))
    {
        if(index > str)
            index--;
        else
            return 0;
    }

    /* the last non-whitspace character should be a ')' */
    if(*index == ')')
    {
        got_paren = 1;
        index--;
    }

    while((isspace((int)*index)))
    {
        if(index > str)
            index--;
        else
            return 0;
    }

    /* the next to last char should be a semicolon */
    if(*index == ';')
    {
        got_semi = 1;
    }

    if(got_semi && got_paren)
    {
        return 1;
    }
    else
    {
        /* check for a '(' to make sure that rule options are being used... */
        for(index = str; index < str+len; index++)
        {
            if(*index == '(')
            {
                return 0;
            }
        }

        return 1;
    }

    return 0;
}

void DumpRuleChains()
{
    RuleListNode *rule;

    rule = RuleLists;

    while(rule != NULL)
    {
        DumpChain(rule->RuleList->TcpList, rule->name, "TCP Chains");
        DumpChain(rule->RuleList->UdpList, rule->name, "UDP Chains");
        DumpChain(rule->RuleList->IcmpList, rule->name, "ICMP Chains");
        rule = rule->next;
    }
}

void IntegrityCheckRules()
{
    RuleListNode *rule;

    rule = RuleLists;

#ifdef DEBUG
    if(!pv.quiet_flag)
    {
        printf("Performing Rule List Integrity Tests...\n");
        printf("---------------------------------------\n");
    }
#endif

    while(rule != NULL)
    {
        IntegrityCheck(rule->RuleList->TcpList, rule->name, "TCP Chains");
        IntegrityCheck(rule->RuleList->UdpList, rule->name, "UDP Chains");
        IntegrityCheck(rule->RuleList->IcmpList, rule->name, "ICMP Chains");
        rule = rule->next;
    }

#ifdef DEBUG
    if(!pv.quiet_flag)
    {
        printf("---------------------------------------\n\n");
    }
#endif

}

/****************************************************************************
 *
 * Function: ParseRule(char *, int)
 *
 * Purpose:  Process an individual rule and add it to the rule list
 *
 * Arguments: rule => rule string
 *            inclevel => nr of stacked "include"s
 *
 * Returns: void function
 *
 ***************************************************************************/

void ParseRule(char *prule, int inclevel)
{
    char **toks;        /* dbl ptr for mSplit call, holds rule tokens */
    int num_toks;       /* holds number of tokens found by mSplit */
    int rule_type;      /* rule type enumeration variable */
    char rule[PARSERULE_SIZE];
    int protocol;
    RuleTreeNode proto_node;
    int i;
#ifdef PARSERULE_BIFURCATE
    int bid = 0;
#endif
#ifdef PARSERULE_REVERSED
    char *tmp_tok_host, *tmp_tok_port; /* 2 tmps for clarity */
#endif    
    /* chop off the <CR/LF> from the string */
    strip(prule);

    /* expand all variables */
    bzero((void *)rule, sizeof(rule));
    strncpy(rule, ExpandVars(prule), PARSERULE_SIZE-1);

    /* break out the tokens from the rule string */
    toks = mSplit(rule, " ", 10, &num_toks, 0);

#ifdef PARSERULE_REVERSED
    if(num_toks > 5 && (strncmp("<-", toks[4], 2) == 0))
    {
#ifdef DEBUG
	printf("Reversing rule %s %s %s %s %s %s %s ( into )\n",
	       toks[0],toks[1],toks[2],toks[3],toks[4],toks[5],toks[6]);
#endif /* DEBUG */
	/* Switch the src and dst port/ips and change the direction */
	tmp_tok_host = toks[2];
	tmp_tok_port = toks[3];
	toks[2] = toks[5];
	toks[3] = toks[6];
	toks[5] = tmp_tok_host;
	toks[6] = tmp_tok_port;
	/* the == 0 makes sure this has room to copy */
	strncpy (toks[4], "->", 2); 
#ifdef DEBUG
	printf("Reversed rule: %s %s %s %s %s %s %s\n",
	       toks[0],toks[1],toks[2],toks[3],toks[4],toks[5],toks[6]);
#endif /* DEBUG */
    }
#endif /*  PARSERULE_REVERSED */

#ifdef PARSERULE_BIFURCATE
    if(num_toks > 5 && (bid = !strncmp("<>", toks[4], 2)))
    {
#ifdef DEBUG
        printf("Generating bid rules for: %s %s %s %s %s %s %s\n",
               toks[0],toks[1],toks[2],toks[3],toks[4],toks[5],toks[6]);
#endif
        strncpy (toks[4], "->", 2);
    }
    bidog:
#endif

    /* clean house */
    bzero((char *) &proto_node, sizeof(RuleTreeNode));

#ifdef DEBUG
    printf("[*] Rule start\n");
#endif

    /* figure out what we're looking at */
    rule_type = RuleType(toks[0]);

#ifdef DEBUG
    printf("Rule type: ");
#endif

    /* handle non-rule entries */
    switch(rule_type)
    {
        case RULE_PASS:
#ifdef DEBUG
            printf("Pass\n");
#endif
            break;

        case RULE_LOG:
#ifdef DEBUG
            printf("Log\n");
#endif
            break;

        case RULE_ALERT:
#ifdef DEBUG
            printf("Alert\n");
#endif
            break;

        case RULE_INCLUDE:
#ifdef DEBUG
            printf("Include\n");
#endif
            ParseRulesFile(toks[1], inclevel + 1);
            return;

        case RULE_VAR:
#ifdef DEBUG
            printf("Variable\n");
#endif
            VarDefine(toks[1], toks[2]);
            return;

        case RULE_PREPROCESS:
#ifdef DEBUG
            printf("Preprocessor\n");
#endif
            ParsePreprocessor(rule);
            return;

        case RULE_OUTPUT:
#ifdef DEBUG
            printf("Output Plugin\n");
#endif
            ParseOutputPlugin(rule);
            return;

        case RULE_ACTIVATE:
#ifdef DEBUG
            printf("Activation rule\n");
#endif
            break;

        case RULE_DYNAMIC:
#ifdef DEBUG
            printf("Dynamic rule\n");
#endif
            break;

        case RULE_CONFIG:
#ifdef DEBUG
            printf("Rule file config\n");
#endif
            ParseConfig(rule);
            return;

        case RULE_DECLARE:
#ifdef DEBUG
            printf("Rule type declaration\n");
#endif
            ParseRuleTypeDeclaration(rule);
            return;

        case RULE_UNKNOWN:
#ifdef DEBUG
            printf("Unknown rule type, might be declared\n");
#endif
            ParseDeclaredRuleType(rule);
            return;

        default:
            printf("Invalid input: %s\n", prule);
            return;
    }

    if(!CheckRule(prule))
    {
        ErrorMessage("[!] ERROR: Unterminated rule in file %s, line %d\n", file_name, file_line);
        ErrorMessage("   (Snort rules must be contained on a single line, make sure\n");
        FatalError("   there are no carriage returns before the end of this line)\n");
        return;
    }


    proto_node.type = rule_type;

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
    /* we found a negated address */
    /* if( *toks[2] == '!' )    
     {
         proto_node.flags |= EXCEPT_SRC_IP;
         ProcessIP(&toks[2][1], &proto_node, SRC);
     }
     else
     {*/
    ProcessIP(toks[2], &proto_node, SRC);
    /*}*/

    /* check to make sure that the user entered port numbers */
    /* sometimes they forget/don't know that ICMP rules need them */
    if(!strncasecmp(toks[3], "->", 2) ||
       !strncasecmp(toks[3], "<>", 2))
    {
        FatalError("ERROR %s:%d => Port value missing in rule!\n", file_name, file_line);
    }

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
    /* we found a negated address */
    /* if( *toks[5] == '!' )    
     {
 #ifdef DEBUG
         printf("setting exception flag for dest IP\n");
 #endif
         proto_node.flags |= EXCEPT_DST_IP;
         ProcessIP(&toks[5][1], &proto_node, DST);
     }
     else
     {*/
    ProcessIP(toks[5], &proto_node, DST);
    /*}*/

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
    printf("Processing Head Node....\n");
#endif

    switch(rule_type)
    {
        case RULE_ALERT:
            ProcessHeadNode(&proto_node, &Alert, protocol);
            break;

        case RULE_LOG:
            ProcessHeadNode(&proto_node, &Log, protocol);
            break;

        case RULE_PASS:
            ProcessHeadNode(&proto_node, &Pass, protocol);
            break;

        case RULE_ACTIVATE:
            ProcessHeadNode(&proto_node, &Activation, protocol);
            break;

        case RULE_DYNAMIC:
            ProcessHeadNode(&proto_node, &Dynamic, protocol);
            break;

        default:
            FatalError("Unable to determine rule type (%s) for processing, exiting!\n", toks[0]);
    }

    rule_count++;

#ifdef DEBUG
    printf("Parsing Rule Options...\n");
#endif

    ParseRuleOptions(rule, rule_type, protocol);

#ifdef PARSERULE_BIFURCATE
    if(bid)
    {
        char *iptemp = toks[2];
        char *porttemp = toks[3];
        toks[2] = toks[5];
        toks[3] = toks[6];
        toks[5] = iptemp;
        toks[6] = porttemp;
        bid = 0;
        goto bidog;
    }
#endif

    for(i=0;i<num_toks;i++)
    {
        free(toks[i]);
    }

    return;
}


/****************************************************************************
 *
 * Function: ProcessHeadNode(RuleTreeNode *, ListHead *, int)
 *
 * Purpose:  Process the header block info and add to the block list if
 *           necessary
 *
 * Arguments: test_node => data generated by the rules parsers
 *            list => List Block Header refernece
 *            protocol => ip protocol
 *
 * Returns: void function
 *
 ***************************************************************************/
void ProcessHeadNode(RuleTreeNode * test_node, ListHead * list, int protocol)
{
    int match = 0;
    RuleTreeNode *rtn_idx;
    int count = 0;

    /* select the proper protocol list to attach the current rule to */
    switch(protocol)
    {
        case IPPROTO_TCP:
            rtn_idx = list->TcpList;
            break;

        case IPPROTO_UDP:
            rtn_idx = list->UdpList;
            break;

        case IPPROTO_ICMP:
            rtn_idx = list->IcmpList;
            break;

        default:
            rtn_idx = NULL;
            break;
    }

    /*
     * if the list head is NULL (empty), make a new one and attach the
     * ListHead to it
     */
    if(rtn_idx == NULL)
    {
        head_count++;

        switch(protocol)
        {
            case IPPROTO_TCP:
                list->TcpList = (RuleTreeNode *) calloc(sizeof(RuleTreeNode), sizeof(char));
                rtn_tmp = list->TcpList;
                break;

            case IPPROTO_UDP:
                list->UdpList = (RuleTreeNode *) calloc(sizeof(RuleTreeNode), sizeof(char));
                rtn_tmp = list->UdpList;
                break;

            case IPPROTO_ICMP:
                list->IcmpList = (RuleTreeNode *) calloc(sizeof(RuleTreeNode), sizeof(char));
                rtn_tmp = list->IcmpList;
                break;
        }

        /* copy the prototype header data into the new node */
        XferHeader(test_node, rtn_tmp);

        rtn_tmp->head_node_number = head_count;

        /* null out the down (options) pointer */
        rtn_tmp->down = NULL;

        /* add the function list to the new rule */
        SetupRTNFuncList(rtn_tmp);

        /* add link to parent listhead */
        rtn_tmp->listhead = list;

        return;
    }
    /* see if this prototype node matches any of the existing header nodes */
    match = TestHeader(rtn_idx, test_node);

    while((rtn_idx->right != NULL) && !match)
    {
        count++;
        match = TestHeader(rtn_idx, test_node);

        if(!match)
            rtn_idx = rtn_idx->right;
        else
            break;
    }

    /*
     * have to check this twice since my loop above exits early, which sucks
     * but it's not performance critical
     */
    match = TestHeader(rtn_idx, test_node);

    /*
     * if it doesn't match any of the existing nodes, make a new node and
     * stick it at the end of the list
     */
    if(!match)
    {
#ifdef DEBUG
        printf("Building New Chain head node\n");
#endif

        head_count++;

        /* build a new node */
        rtn_idx->right = (RuleTreeNode *) calloc(sizeof(RuleTreeNode), sizeof(char));

        /* set the global ptr so we can play with this from anywhere */
        rtn_tmp = rtn_idx->right;

        /* uh oh */
        if(rtn_tmp == NULL)
        {
            FatalError("ERROR: Unable to allocate Rule Head Node!!\n");
        }
        /* copy the prototype header info into the new header block */
        XferHeader(test_node, rtn_tmp);

        rtn_tmp->head_node_number = head_count;
        rtn_tmp->down = NULL;

        /* initialize the function list for the new RTN */
        SetupRTNFuncList(rtn_tmp);

        /* add link to parent listhead */
        rtn_tmp->listhead = list;
#ifdef DEBUG
        printf("New Chain head flags = 0x%X\n", rtn_tmp->flags);
#endif
    }
    else
    {
        rtn_tmp = rtn_idx;
#ifdef DEBUG
        printf("Chain head %d  flags = 0x%X\n", count, rtn_tmp->flags);
#endif

#ifdef DEBUG
        printf("Adding options to chain head %d\n", count);
#endif
    }
}


/****************************************************************************
 *
 * Function: AddRuleFuncToList(int (*func)(), RuleTreeNode *)
 *
 * Purpose:  Adds RuleTreeNode associated detection functions to the
 *          current rule's function list
 *
 * Arguments: *func => function pointer to the detection function
 *            rtn   => pointer to the current rule
 *
 * Returns: void function
 *
 ***************************************************************************/
void AddRuleFuncToList(int (*func) (Packet *, struct _RuleTreeNode *, struct _RuleFpList *), RuleTreeNode * rtn)
{
    RuleFpList *idx;

#ifdef DEBUG
    printf("Adding new rule to list\n");
#endif

    idx = rtn->rule_func;

    if(idx == NULL)
    {
        rtn->rule_func = (RuleFpList *) calloc(sizeof(RuleFpList), sizeof(char));

        rtn->rule_func->RuleHeadFunc = func;
    }
    else
    {
        while(idx->next != NULL)
            idx = idx->next;

        idx->next = (RuleFpList *) calloc(sizeof(RuleFpList), sizeof(char));

        idx = idx->next;
        idx->RuleHeadFunc = func;
    }
}


/****************************************************************************
 *
 * Function: SetupRTNFuncList(RuleTreeNode *)
 *
 * Purpose: Configures the function list for the rule header detection
 *          functions (addrs and ports)
 *
 * Arguments: rtn => the pointer to the current rules list entry to attach to
 *
 * Returns: void function
 *
 ***************************************************************************/
void SetupRTNFuncList(RuleTreeNode * rtn)
{
#ifdef DEBUG
    printf("Initializing RTN function list!\n");
    printf("Functions: ");
#endif

    if(rtn->flags & BIDIRECTIONAL)
    {
#ifdef DEBUG
        printf("CheckBidirectional->\n");
#endif
        AddRuleFuncToList(CheckBidirectional, rtn);
    }
    else
    {
        /* link in the proper IP address detection function */
        /*
         * the in-line "if" determines whether or not the negation operator
         * has been set for this rule and tells the AddrToFunc call which
         * function it should be linking in
         */
        AddrToFunc(rtn, SRC);

        /* last verse, same as the first (but for dest IP) ;) */
        AddrToFunc(rtn, DST);

        /* Attach the proper port checking function to the function list */
        /*
         * the in-line "if's" check to see if the "any" or "not" flags have
         * been set so the PortToFunc call can determine which port testing
         * function to attach to the list
         */
        PortToFunc(rtn, (rtn->flags & ANY_SRC_PORT ? 1 : 0),
                   (rtn->flags & EXCEPT_SRC_PORT ? 1 : 0), SRC);

        /* as above */
        PortToFunc(rtn, (rtn->flags & ANY_DST_PORT ? 1 : 0),
                   (rtn->flags & EXCEPT_DST_PORT ? 1 : 0), DST);
    }

#ifdef DEBUG
    printf("RuleListEnd\n");
#endif

    /* tack the end (success) function to the list */
    AddRuleFuncToList(RuleListEnd, rtn);
}



/****************************************************************************
 *
 * Function: AddrToFunc(RuleTreeNode *, u_long, u_long, int, int)
 *
 * Purpose: Links the proper IP address testing function to the current RTN
 *          based on the address, netmask, and addr flags
 *
 * Arguments: rtn => the pointer to the current rules list entry to attach to
 *            ip =>  IP address of the current rule
 *            mask => netmask of the current rule
 *            exception_flag => indicates that a "!" has been set for this
 *                              address
 *            mode => indicates whether this is a rule for the source
 *                    or destination IP for the rule
 *
 * Returns: void function
 *
 ***************************************************************************/
void AddrToFunc(RuleTreeNode * rtn, int mode)
{
    /*
     * if IP and mask are both 0, this is a "any" IP and we don't need to
     * check it
     */

    switch(mode)
    {
        case SRC:
#ifdef DEBUG
            printf("CheckSrcIP -> ");
#endif
            if((rtn->flags & ANY_SRC_IP) == 0)
            {
                AddRuleFuncToList(CheckSrcIP, rtn);
            }

            break;

        case DST:
#ifdef DEBUG
            printf("CheckDstIP -> ");
#endif
            if((rtn->flags & ANY_DST_IP) == 0)
            {
                AddRuleFuncToList(CheckDstIP, rtn);
            }

            break;
    }
}



/****************************************************************************
 *
 * Function: PortToFunc(RuleTreeNode *, int, int, int)
 *
 * Purpose: Links in the port analysis function for the current rule
 *
 * Arguments: rtn => the pointer to the current rules list entry to attach to
 *            any_flag =>  accept any port if set
 *            except_flag => indicates negation (logical NOT) of the test
 *            mode => indicates whether this is a rule for the source
 *                    or destination port for the rule
 *
 * Returns: void function
 *
 ***************************************************************************/
void PortToFunc(RuleTreeNode * rtn, int any_flag, int except_flag, int mode)
{
    /*
     * if the any flag is set we don't need to perform any test to match on
     * this port
     */
    if(any_flag)
        return;

    /* if the except_flag is up, test with the "NotEq" funcs */
    if(except_flag)
    {
        switch(mode)
        {
            case SRC:
#ifdef DEBUG
                printf("CheckSrcPortNotEq -> ");
#endif
                AddRuleFuncToList(CheckSrcPortNotEq, rtn);
                break;

            case DST:
#ifdef DEBUG
                printf("CheckDstPortNotEq -> ");
#endif
                AddRuleFuncToList(CheckDstPortNotEq, rtn);
                break;
        }

        return;
    }
    /* default to setting the straight test function */
    switch(mode)
    {
        case SRC:
#ifdef DEBUG
            printf("CheckSrcPortEqual -> ");
#endif
            AddRuleFuncToList(CheckSrcPortEqual, rtn);
            break;

        case DST:
#ifdef DEBUG
            printf("CheckDstPortEqual -> ");
#endif
            AddRuleFuncToList(CheckDstPortEqual, rtn);
            break;
    }

    return;
}




/****************************************************************************
 *
 * Function: AddOptFuncToList(int (*func)(), OptTreeNode *)
 *
 * Purpose: Links the option detection module to the OTN
 *
 * Arguments: (*func)() => function pointer to the detection module
 *            otn =>  pointer to the current OptTreeNode
 *
 * Returns: void function
 *
 ***************************************************************************/
void AddOptFuncToList(int (*func) (Packet *, struct _OptTreeNode *, struct _OptFpList *), OptTreeNode * otn)
{
    OptFpList *idx;     /* index pointer */

#ifdef DEBUG
    printf("Adding new rule to list\n");
#endif

    /* set the index pointer to the start of this OTN's function list */
    idx = otn->opt_func;

    /* if there are no nodes on the function list... */
    if(idx == NULL)
    {
        /* calloc the list head */
        otn->opt_func = (OptFpList *) calloc(sizeof(OptFpList), sizeof(char));

        if(otn->opt_func == NULL)
        {
            FatalError("ERROR => AddOptFuncToList new node calloc failed: %s\n", strerror(errno));
        }

        /* set the head function */
        otn->opt_func->OptTestFunc = func;
    }
    else
    {
        /* walk to the end of the list */
        while(idx->next != NULL)
        {
            idx = idx->next;
        }

        /* allocate a new node on the end of the list */
        idx->next = (OptFpList *) calloc(sizeof(OptFpList), sizeof(char));

        if(idx->next == NULL)
        {
            FatalError("ERROR => AddOptFuncToList new node calloc failed: %s\n", strerror(errno));
        }

        /* move up to the new node */
        idx = idx->next;

        /* link the function to the new node */
        idx->OptTestFunc = func;

#ifdef DEBUG
        printf("Set OptTestFunc to %p\n", func);
#endif
    }
}


/****************************************************************************
 *
 * Function: AddRspFuncToList(int (*func)(), OptTreeNode *)
 *
 * Purpose: Adds Response function to OTN
 *
 * Arguments: (*func)() => function pointer to the response module
 *            otn =>  pointer to the current OptTreeNode
 *
 * Returns: void function
 *
 ***************************************************************************/
void AddRspFuncToList(int (*func) (Packet *, struct _RspFpList *), RuleTreeNode * rtn, void *params)
{
    RspFpList *idx;     /* index pointer */

#ifdef DEBUG
    printf("Adding response to list\n");
#endif

    /* set the index pointer to the start of this OTN's function list */
    idx = rtn->rsp_func;

    /* if there are no nodes on the function list... */
    if(idx == NULL)
    {
        /* calloc the list head */
        rtn->rsp_func = (RspFpList *) calloc(sizeof(RspFpList), sizeof(char));

        if(rtn->rsp_func == NULL)
        {
            FatalError("ERROR => AddRspFuncToList new node calloc failed: %s\n", strerror(errno));
        }
        /* set the head function */
        rtn->rsp_func->ResponseFunc = func;
        rtn->rsp_func->params = params;
    }
    else
    {
        /* walk to the end of the list */
        while(idx->next != NULL)
        {
            idx = idx->next;
        }

        /* allocate a new node on the end of the list */
        idx->next = (RspFpList *) calloc(sizeof(RspFpList), sizeof(char));

        if(idx->next == NULL)
        {
            FatalError("ERROR => AddRspFuncToList new node calloc failed: %s\n", strerror(errno));
        }
        /* link the function to the new node */
        idx->next->ResponseFunc = func;
        idx->next->params = params;

#ifdef DEBUG
        printf("Set ResponseFunc to %p\n", func);
#endif
    }
}



/****************************************************************************
 *
 * Function: ParsePreprocessor(char *)
 *
 * Purpose: Walks the preprocessor function list looking for the user provided
 *          keyword.  Once found, call the preprocessor's initialization
 *          function.
 *
 * Arguments: rule => the preprocessor initialization string from the rules file
 *
 * Returns: void function
 *
 ***************************************************************************/
void ParsePreprocessor(char *rule)
{
    char **toks;        /* pointer to the tokenized array parsed from
                         * the rules list */
    char **pp_head;     /* parsed keyword list, with preprocessor
                         * keyword being the 2nd element */
    char *funcname;     /* the ptr to the actual preprocessor keyword */
    char *pp_args = NULL;   /* parsed list of arguments to the
                             * preprocessor */
    int num_toks;       /* number of tokens returned by the mSplit
                         * function */
    int found = 0;      /* flag var */
    PreprocessKeywordList *pl_idx;  /* index into the preprocessor
                                     * keyword/func list */

    /* break out the arguments from the keywords */
    toks = mSplit(rule, ":", 2, &num_toks, '\\');

    if(num_toks >= 1)
    {
        /*
#ifdef DEBUG
        printf("toks[1] = %s\n", toks[1]);
#endif
        */
        /* the args are everything after the ":" */
        pp_args = toks[1];
    }

    /* split the head section for the preprocessor keyword */
    pp_head = mSplit(toks[0], " ", 2, &num_toks, '\\');

    /* set a pointer to the actual keyword */
    funcname = pp_head[1];

    /* set the index to the head of the keyword list */
    pl_idx = PreprocessKeywords;

    /* walk the keyword list */
    while(pl_idx != NULL)
    {
#ifdef DEBUG
        printf("comparing: \"%s\" => \"%s\"\n", funcname, pl_idx->entry.keyword);
#endif
        /* compare the keyword against the current list element's keyword */
        if(!strcasecmp(funcname, pl_idx->entry.keyword))
        {
            pl_idx->entry.func(pp_args);
            found = 1;
        }
        if(!found)
        {
            pl_idx = pl_idx->next;
        }
        else
            break;
    }

    if(!found)
    {
        printf("\n*WARNING*: unknown preprocessor \"%s\", ignoring!\n\n",
               funcname);
    }
}



void AddFuncToPreprocList(void (*func) (Packet *))
{
    PreprocessFuncNode *idx;

    idx = PreprocessList;

    if(idx == NULL)
    {
        PreprocessList = (PreprocessFuncNode *) calloc(sizeof(PreprocessFuncNode), sizeof(char));

        PreprocessList->func = func;
    }
    else
    {
        while(idx->next != NULL)
            idx = idx->next;

        idx->next = (PreprocessFuncNode *) calloc(sizeof(PreprocessFuncNode), sizeof(char));

        idx = idx->next;
        idx->func = func;
    }

    return;
}


void ParseOutputPlugin(char *rule)
{
    char **toks;
    char **pp_head;
    char *funcname;
    char *pp_args = NULL;
    int num_toks;
    int found = 0;
    OutputKeywordList *pl_idx;

    toks = mSplit(rule, ":", 2, &num_toks, '\\');

    if(num_toks >= 1)
    {
        pp_args = toks[1];
    }
    pp_head = mSplit(toks[0], " ", 2, &num_toks, '\\');

    funcname = pp_head[1];

    pl_idx = OutputKeywords;

    while(pl_idx != NULL)
    {
#ifdef DEBUG
        printf("comparing: \"%s\" => \"%s\"\n", funcname, pl_idx->entry.keyword);
#endif
        if(!strcasecmp(funcname, pl_idx->entry.keyword))
        {
            switch(pl_idx->entry.node_type)
            {
                case NT_OUTPUT_ALERT:
                    if(!pv.alert_cmd_override)
                    {
                        if(AlertFunc == NULL)
                        {
                            AlertFunc = CallAlertPlugins;
                        }

                        /* call the configuration function for the plugin */
                        pl_idx->entry.func(pp_args);
                    }
                    else
                    {
                        ErrorMessage("WARNING: command line overrides rules file alert plugin!\n");
                    }

                    break;

                case NT_OUTPUT_LOG:
                    if(!pv.log_cmd_override)
                    {
                        if(LogFunc == NULL)
                        {
                            LogFunc = CallLogPlugins;
                        }

                        /* call the configuration function for the plugin */
                        pl_idx->entry.func(pp_args);
                    }
                    else
                    {
                        ErrorMessage("WARNING: command line overrides rules file logging plugin!\n");
                    }

                    break;
            }

            found = 1;
        }

        if(!found)
        {
            pl_idx = pl_idx->next;
        }
        else
        {
            break;
        }
    }

    if(!found)
    {
        printf("\n*WARNING*: unknown output plugin \"%s\", ignoring!\n\n", funcname);
    }
}



/*
 * frees the existing OutputList ands sets it a single node for the
 * function argument
 */
void SetOutputList(void (*func) (Packet *, char *, void *), char node_type,
                   void *arg)
{
    OutputFuncNode *idx;
    OutputFuncNode *prev;

    switch(node_type)
    {
        case NT_OUTPUT_ALERT:
            prev = AlertList;
            break;

        case NT_OUTPUT_LOG:
            prev = LogList;
            break;

        default:
            return;
    }

    while(prev != NULL)
    {
        idx = prev->next;
        free(prev);
        prev = idx;
    }

    AddFuncToOutputList(func, node_type, arg);

    return; 
}

void AddFuncToOutputList(void (*func) (Packet *, char *, void *), char node_type,
                         void *arg)
{
    switch(node_type)
    {
        case NT_OUTPUT_ALERT:
            if(head_tmp != NULL)
                head_tmp->AlertList = AppendOutputFuncList(func, arg,
                                                           head_tmp->AlertList);
            else
                AlertList = AppendOutputFuncList(func, arg, AlertList);
            break;

        case NT_OUTPUT_LOG:
            if(head_tmp != NULL)
                head_tmp->LogList = AppendOutputFuncList(func, arg,
                                                         head_tmp->LogList);
            else
                LogList = AppendOutputFuncList(func, arg, LogList);
            break;

        default:
            /* just to be error-prone */
            FatalError("Unknown nodetype: %i. Possible bug, please report\n",
                       node_type);
    }

    return;
}

OutputFuncNode *AppendOutputFuncList(void (*func) (Packet *, char *, void *),
                                     void *arg, OutputFuncNode * list)
{
    OutputFuncNode *idx = list;

    if(idx == NULL)
    {
        idx = (OutputFuncNode *) calloc(sizeof(OutputFuncNode), sizeof(char));
        idx->func = func;
        idx->arg = arg;
        list = idx;
    }
    else
    {
        while(idx->next != NULL)
            idx = idx->next;

        idx->next = (OutputFuncNode *) calloc(sizeof(OutputFuncNode), sizeof(char));
        idx = idx->next;
        idx->func = func;
        idx->arg = arg;
    }

    idx->next = NULL;

    return list;
}




/****************************************************************************
 *
 * Function: ParseRuleOptions(char *, int)
 *
 * Purpose:  Process an individual rule's options and add it to the
 *           appropriate rule chain
 *
 * Arguments: rule => rule string
 *            rule_type => enumerated rule type (alert, pass, log)
 *
 * Returns: void function
 *
 ***************************************************************************/
void ParseRuleOptions(char *rule, int rule_type, int protocol)
{
    char **toks = NULL;
    char **opts;
    char *idx;
    char *aux;
    int num_toks;
    int i;
    int num_opts;
    int found = 0;
    OptTreeNode *otn_idx;
    KeywordXlateList *kw_idx;

    /* set the OTN to the beginning of the list */
    otn_idx = rtn_tmp->down;

    /*
     * make a new one and stick it either at the end of the list or hang it
     * off the RTN pointer
     */
    if(otn_idx != NULL)
    {
        /* loop to the end of the list */
        while(otn_idx->next != NULL)
        {
            otn_idx = otn_idx->next;
        }

        /* setup the new node */
        otn_idx->next = (OptTreeNode *) calloc(sizeof(OptTreeNode), sizeof(char));

        /* set the global temp ptr */
        otn_tmp = otn_idx->next;

        if(otn_tmp == NULL)
        {
            FatalError("ERROR: Unable to alloc OTN: %s", strerror(errno));
        }
        otn_tmp->next = NULL;
        opt_count++;

    }
    else
    {
        /* first entry on the chain, make a new node and attach it */
        otn_idx = (OptTreeNode *) calloc(sizeof(OptTreeNode), sizeof(char));

        bzero((char *) otn_idx, sizeof(OptTreeNode));

        otn_tmp = otn_idx;

        if(otn_tmp == NULL)
        {
            FatalError("ERROR: Unable to alloc OTN!\n");
        }
        otn_tmp->next = NULL;
        rtn_tmp->down = otn_tmp;
        opt_count++;
    }

    otn_tmp->chain_node_number = opt_count;
    otn_tmp->type = rule_type;
    otn_tmp->proto_node = rtn_tmp;

    /* add link to parent RuleTreeNode */
    otn_tmp->rtn = rtn_tmp;

    /* find the start of the options block */
    idx = index(rule, '(');
    i = 0;

    if(idx != NULL)
    {
        idx++;

        /* find the end of the options block */
        aux = strrchr(idx, ')');

        /* get rid of the trailing ")" */
        if(aux == NULL)
        {
            ErrorMessage("Problem rule: %s\n", rule);
            FatalError("ERROR %s(%d): Missing trailing ')' in rule options.\n", file_name, file_line);
        }
        *aux = 0;


        /* seperate all the options out, the seperation token is a semicolon */
        /*
         * NOTE: if you want to include a semicolon in the content of your
         * rule, it must be preceeded with a '\'
         */
        toks = mSplit(idx, ";", 64, &num_toks, '\\');

#ifdef DEBUG
        printf("   Got %d tokens\n", num_toks);
#endif
        /* decrement the number of toks */
        num_toks--;

#ifdef DEBUG
        printf("Parsing options list: ");
#endif

        while(num_toks)
        {
#ifdef DEBUG
            printf("   option: %s\n", toks[i]);
#endif

            /* break out the option name from its data */
            opts = mSplit(toks[i], ":", 4, &num_opts, '\\');

#ifdef DEBUG
            printf("   option name: %s\n", opts[0]);
            printf("   option args: %s\n", opts[1]);
#endif

            /* advance to the beginning of the data (past the whitespace) */
            while(isspace((int) *opts[0]))
                opts[0]++;

            /* figure out which option tag we're looking at */
            if(!strncasecmp(opts[0], "msg", 3))
            {
                ParseMessage(opts[1]);
            }
            else if(!strncasecmp(opts[0], "logto", 5))
            {
                ParseLogto(opts[1]);
            }
            else if(!strncasecmp(opts[0], "activates", 9))
            {
                ParseActivates(opts[1]);
                dynamic_rules_present++;
            }
            else if(!strncasecmp(opts[0], "activated_by", 12))
            {
                ParseActivatedBy(opts[1]);
                dynamic_rules_present++;
            }
            else if(!strncasecmp(opts[0], "count", 5))
            {
                if(otn_tmp->type != RULE_DYNAMIC)
                    FatalError("The \"count\" option may only be used with the dynamic rule type!\n");

                ParseCount(opts[1]);
            }
            else
            {
                kw_idx = KeywordList;
                found = 0;

                while(kw_idx != NULL)
                {
#ifdef DEBUG
                    printf("comparing: \"%s\" => \"%s\"\n", opts[0], kw_idx->entry.keyword);
#endif
                    if(!strcasecmp(opts[0], kw_idx->entry.keyword))
                    {
                        kw_idx->entry.func(opts[1], otn_tmp, protocol);
                        found = 1;
#ifdef DEBUG
                        printf("%s->", kw_idx->entry.keyword);
#endif
                    }

                    if(!found)
                    {
                        kw_idx = kw_idx->next;
                    }
                    else
                    {
                        break;
                    }
                }

                if(!found)
                {
                    if(!strcasecmp(opts[0], "minfrag"))
                    {
                        FatalError("\nERROR: %s (%d) => Minfrag is no longer a rule option, it is a\npreprocessor (please remove it from your rules file).  See RULES.SAMPLE or\nsnort-lib for examples of using the new preprocessors!\n", file_name, file_line);
                    }
                    else
                    {
                        FatalError("\nERROR: %s (%d) => Unknown keyword \"%s\" in rule!\n", file_name, file_line, opts[0]);
                    }
                }
            }

            free(opts);
            --num_toks;
            i++;
        }
#ifdef DEBUG
        printf("OptListEnd\n");
#endif

        AddOptFuncToList(OptListEnd, otn_tmp);
    }
    else
    {
#ifdef DEBUG
        printf("OptListEnd\n");
#endif

        AddOptFuncToList(OptListEnd, otn_tmp);
    }


    if(idx != NULL)
        for(i=0;i<num_toks;i++)
            free(toks[i]);

}


/****************************************************************************
 *
 * Function: RuleType(char *)
 *
 * Purpose:  Determine what type of rule is being processed and return its
 *           equivalent value
 *
 * Arguments: func => string containing the rule type
 *
 * Returns: The rule type designation
 *
 ***************************************************************************/
int RuleType(char *func)
{
    if(func == NULL)
    {
        FatalError("ERROR line %s (%d) => Unknown rule type (%s)\n", file_name, file_line, func);
    }
    if(!strncasecmp(func, "log", 3))
        return RULE_LOG;

    if(!strncasecmp(func, "alert", 5))
        return RULE_ALERT;

    if(!strncasecmp(func, "pass", 4))
        return RULE_PASS;

    if(!strncasecmp(func, "var", 3))
        return RULE_VAR;

    if(!strncasecmp(func, "include", 7))
        return RULE_INCLUDE;

    if(!strncasecmp(func, "preprocessor", 12))
        return RULE_PREPROCESS;

    if(!strncasecmp(func, "output", 6))
        return RULE_OUTPUT;

    if(!strncasecmp(func, "activate", 8))
        return RULE_ACTIVATE;

    if(!strncasecmp(func, "dynamic", 7))
        return RULE_DYNAMIC;

    if(!strncasecmp(func, "config", 6))
        return RULE_CONFIG;

    if(!strncasecmp(func, "ruletype", 8))
        return RULE_DECLARE;

    return RULE_UNKNOWN;
}



/****************************************************************************
 *
 * Function: WhichProto(char *)
 *
 * Purpose: Figure out which protocol the current rule is talking about
 *
 * Arguments: proto_str => the protocol string
 *
 * Returns: The integer value of the protocol
 *
 ***************************************************************************/
int WhichProto(char *proto_str)
{
    if(!strncasecmp(proto_str, "tcp", 3))
        return IPPROTO_TCP;

    if(!strncasecmp(proto_str, "udp", 3))
        return IPPROTO_UDP;

    if(!strncasecmp(proto_str, "icmp", 4))
        return IPPROTO_ICMP;

    /*
     * if we've gotten here, we have a protocol string we din't recognize and
     * should exit
     */
    FatalError("ERROR %s (%d) => Bad protocol: %s\n", file_name, file_line, proto_str);

    return 0;
}



int ProcessIP(char *addr, RuleTreeNode *rtn, int mode)
{
    char **toks = NULL;
    int num_toks;
    int i;
    IpAddrSet *tmp_addr;
    char *tmp;

#ifdef DEBUG
    printf("Got address string: %s\n", addr);
#endif

    if(*addr == '!')
    {
        switch(mode)
        {
            case SRC:
                rtn->flags |= EXCEPT_SRC_IP;
                break;

            case DST:
                rtn->flags |= EXCEPT_DST_IP;
                break;
        }

        addr++;
    }

    if(*addr == '$')
    {
        if((tmp = VarGet(addr + 1)) == NULL)
        {
            FatalError("ERROR %s (%d) => Undefined variable %s\n", file_name, file_line, addr);
        }
    }
    else
    {
        tmp = addr;
    }

    /* check to see if the first char is a 
     * bracket, which signifies a list 
     */
    if(*tmp == '[')
    {
#ifdef DEBUG
        printf("Found IP list!\n");
#endif

        /* *(tmp+strlen(tmp)) = ' ';*/
        *(strrchr(tmp, (int)']')) = 0; /* null out the en-bracket */

        toks = mSplit(tmp+1, ",", 128, &num_toks, 0);

#ifdef DEBUG
        printf("mSplit got %d tokens...\n", num_toks);
#endif

        for(i=0; i< num_toks; i++)
        {
#ifdef DEBUG
            printf("adding %s to IP address list\n", toks[i]);
#endif
            tmp = toks[i];
            while (isspace((int)*tmp)) tmp++;
            if (strlen(tmp) == 0)
                continue;
                
            tmp_addr = AllocAddrNode(rtn, mode); 
            ParseIP(tmp, tmp_addr);
            if(tmp_addr->ip_addr == 0 && tmp_addr->netmask == 0)
            {
                switch(mode)
                {
                    case SRC:
                        rtn->flags |= ANY_SRC_IP;
                        break;

                    case DST:
                        rtn->flags |= ANY_DST_IP;
                        break;
                }
            }
        }

#ifdef DEBUG
        printf("Freeing %d tokens...\n", num_toks);
#endif

        for(i=0;i<num_toks;i++)
        {
            free(toks[i]);
        }
    }
    else
    {
#ifdef DEBUG
        printf("regular IP address, processing...\n");
#endif
        tmp_addr = AllocAddrNode(rtn, mode);
        ParseIP(tmp, tmp_addr);
        if(tmp_addr->ip_addr == 0 && tmp_addr->netmask == 0)
        {
            switch(mode)
            {
                case SRC:
                    rtn->flags |= ANY_SRC_IP;
                    break;

                case DST:
                    rtn->flags |= ANY_DST_IP;
                    break;
            }
        }
    }

    return 0;
}



IpAddrSet *AllocAddrNode(RuleTreeNode *rtn, int mode)
{
    IpAddrSet *idx; /* indexing pointer */

    switch(mode)
    {
        case SRC:
            if(rtn->sip == NULL)
            {
                rtn->sip = (IpAddrSet *)calloc(sizeof(IpAddrSet), sizeof(char));
                if(rtn->sip == NULL)
                {
                    FatalError("[!] ERROR: Unable to allocate node for IP list\n");
                }
                return rtn->sip;
            }
            else
            {
                idx = rtn->sip;

                while(idx->next != NULL)
                {
                    idx = idx->next;
                }

                idx->next = (IpAddrSet *)calloc(sizeof(IpAddrSet), sizeof(char));
                if(idx->next == NULL)
                {
                    FatalError("[!] ERROR: Unable to allocate node for IP list\n");
                }
                return idx->next;
            }

            break;

        case DST:
            if(rtn->dip == NULL)
            {
                rtn->dip = (IpAddrSet *)calloc(sizeof(IpAddrSet), sizeof(char));
                if(rtn->dip == NULL)
                {
                    FatalError("[!] ERROR: Unable to allocate node for IP list\n");
                }
                return rtn->dip;
            }
            else
            {
                idx = rtn->dip;

                while(idx->next)
                {
                    idx = idx->next;
                }

                idx->next = (IpAddrSet *)calloc(sizeof(IpAddrSet), sizeof(char));
                if(idx->next == NULL)
                {
                    FatalError("[!] ERROR: Unable to allocate node for IP list\n");
                }
                return idx->next;
            }
            break;
    }

    return NULL;
}


/*
 * Function: ParseIP(char *, u_long *, u_long *)
 *
 * Purpose: Convert a supplied IP address to it's network order 32-bit long
           value.  Also convert the CIDR block notation into a real
 *          netmask.
 *
 * Arguments: addr => address string to convert
 *            ip_addr => storage point for the converted ip address
 *            netmask => storage point for the converted netmask
 *
 * Returns: 0 for normal addresses, 1 for an "any" address
 */
int ParseIP(char *paddr, IpAddrSet *address_data)
{
    int i;
    char **toks;        /* token dbl buffer */
    int num_toks;       /* number of tokens found by mSplit() */
    int cidr = 1;       /* is network expressed in CIDR format */
    int nmask;          /* netmask temporary storage */
    char *addr;         /* string to parse, eventually a
                         * variable-contents */
    struct hostent *host_info;  /* various struct pointers for stuff */
    struct sockaddr_in sin; /* addr struct */

    addr = paddr;

    if(*addr == '!')
    {
        address_data->addr_flags |= EXCEPT_IP;

        addr++;  /* inc past the '!' */
    }

    /* check for wildcards */
    if(!strncasecmp(addr, "any", 3))
    {
        address_data->ip_addr = 0;
        address_data->netmask = 0;
        return 1;
    }

    /* break out the CIDR notation from the IP address */
    toks = mSplit(addr, "/", 2, &num_toks, 0);

    /* "/" was not used as a delimeter, try ":" */
    if(num_toks == 1)
        toks = mSplit(addr, ":", 2, &num_toks, 0);

    /*
     * if we have a mask spec and it is more than two characters long, assume
     * it is netmask format
     */
    if((num_toks > 1) && strlen(toks[1]) > 2)
    {
        cidr = 0;
    }

    switch(num_toks)
    {
        case 1:
            address_data->netmask = netmasks[32];
            break;

        case 2:
            if(cidr)
            {
                /* convert the CIDR notation into a real live netmask */
                nmask = atoi(toks[1]);

                /* it's pain to differ whether toks[1] is correct if netmask */
                /* is /0, so we deploy some sort of evil hack with isdigit */

                if(!isdigit((int) toks[1][0]))
                    nmask = -1;

                if((nmask > -1) && (nmask < 33))
                {
                    address_data->netmask = netmasks[nmask];
                }
                else
                {
                    FatalError("ERROR %s (%d) => Invalid CIDR block for IP addr %s\n", file_name, file_line, addr);
                }
            }
            else
            {
                /* convert the netmask into its 32-bit value */

                /* broadcast address fix from 
                 * Steve Beaty <beaty@emess.mscd.edu> 
                 */

                /*
                 * * if the address is the (v4) broadcast address, inet_addr *
                 * returns -1 which usually signifies an error, but in the *
                 * broadcast address case, is correct.  we'd use inet_aton() *
                 * here, but it's less portable.
                 */
                if(!strncmp(toks[1], "255.255.255.255", 15))
                {
                    address_data->netmask = INADDR_BROADCAST;
                }
                else if((address_data->netmask = inet_addr(toks[1])) == -1)
                {
                    FatalError("ERROR %s (%d) => Rule netmask (%s) didn't x-late, WTF?\n", file_name, file_line, toks[1]);
                }
            }
            break;

        default:
            FatalError("ERROR %s (%d) => Unrecognized IP address/netmask %s\n", file_name, file_line, addr);
            break;
    }

#ifndef WORDS_BIGENDIAN
    /*
     * since PC's store things the "wrong" way, shuffle the bytes into the
     * right order.  Non-CIDR netmasks are already correct.
     */
    if(cidr)
    {
        address_data->netmask = htonl(address_data->netmask);
    }
#endif

    /* convert names to IP addrs */
    if(isalpha((int) toks[0][0]))
    {
        /* get the hostname and fill in the host_info struct */
        if((host_info = gethostbyname(toks[0])))
        {
            bcopy(host_info->h_addr, (char *) &sin.sin_addr, host_info->h_length);
        }
        else if((sin.sin_addr.s_addr = inet_addr(toks[0])) == INADDR_NONE)
        {
            FatalError("ERROR %s (%d) => Couldn't resolve hostname %s\n",
                       file_name, file_line, toks[0]);
        }

        address_data->ip_addr = ((u_long) (sin.sin_addr.s_addr) & 
                                 (address_data->netmask));
        return 1;
    }

    /* convert the IP addr into its 32-bit value */

    /* broadcast address fix from Steve Beaty <beaty@emess.mscd.edu> */

    /*
     * * if the address is the (v4) broadcast address, inet_addr returns -1 *
     * which usually signifies an error, but in the broadcast address case, *
     * is correct.  we'd use inet_aton() here, but it's less portable.
     */
    if(!strncmp(toks[0], "255.255.255.255", 15))
    {
        address_data->ip_addr = INADDR_BROADCAST;
    }
    else if((address_data->ip_addr = inet_addr(toks[0])) == -1)
    {
        FatalError("ERROR %s (%d) => Rule IP addr (%s) didn't x-late, WTF?\n", file_name, file_line, toks[0]);
    }
    else
    {
        /* set the final homenet address up */
        address_data->ip_addr = ((u_long) (address_data->ip_addr) & 
                                 (address_data->netmask));
    }

    for(i=0;i<num_toks;i++)
    {
        free(toks[i]);
    }

    return 0;
}



/****************************************************************************
 *
 * Function: ParsePort(char *, u_short *)
 *
 * Purpose:  Convert the port string over to an integer value
 *
 * Arguments: prule_port => port rule string
 *            port => converted integer value of the port
 *
 * Returns: 0 for a normal port number, 1 for an "any" port
 *
 ***************************************************************************/
int ParsePort(char *prule_port, u_short * hi_port, u_short * lo_port, char *proto, int *not_flag)
{
    int i;
    char **toks;        /* token dbl buffer */
    int num_toks;       /* number of tokens found by mSplit() */
    char *rule_port;    /* port string */

    *not_flag = 0;

    /* check for variable */
    if(!strncmp(prule_port, "$", 1))
    {
        if((rule_port = VarGet(prule_port + 1)) == NULL)
        {
            FatalError("ERROR %s (%d) => Undefined variable %s\n", file_name, file_line, prule_port);
        }
    }
    else
        rule_port = prule_port;

    if(rule_port[0] == '(')
    {
        /* user forgot to put a port number in for this rule */
        FatalError("[!] ERROR %s(%d) => Bad port number: \"%s\"\n", 
                   file_name, file_line, rule_port);
    }


    /* check for wildcards */
    if(!strncasecmp(rule_port, "any", 3))
    {
        *hi_port = 0;
        *lo_port = 0;
        return 1;
    }

    if(rule_port[0] == '!')
    {
        *not_flag = 1;
        rule_port++;
    }

    if(rule_port[0] == ':')
    {
        *lo_port = 0;
    }

    toks = mSplit(rule_port, ":", 2, &num_toks, 0);

    switch(num_toks)
    {
        case 1:
            *hi_port = ConvPort(toks[0], proto);

            if(rule_port[0] == ':')
            {
                *lo_port = 0;
            }
            else
            {
                *lo_port = *hi_port;

                if(index(rule_port, ':') != NULL)
                {
                    *hi_port = 65535;
                }
            }

            break;

        case 2:
            *lo_port = ConvPort(toks[0], proto);

            if(toks[1][0] == 0)
                *hi_port = 65535;
            else
                *hi_port = ConvPort(toks[1], proto);

            break;

        default:
            FatalError("[!] ERROR %s (%d) => port conversion failed on \"%s\"\n",
                       file_name, file_line, rule_port);
    }

    for(i=0;i<num_toks;i++)
    {
        free(toks[i]);
    }

    return 0;
}


/****************************************************************************
 *
 * Function: ConvPort(char *, char *)
 *
 * Purpose:  Convert the port string over to an integer value
 *
 * Arguments: port => port string
 *            proto => converted integer value of the port
 *
 * Returns:  the port number
 *
 ***************************************************************************/
int ConvPort(char *port, char *proto)
{
    int conv;           /* storage for the converted number */
    struct servent *service_info;

    /*
     * convert a "word port" (http, ftp, imap, whatever) to its corresponding
     * numeric port value
     */
    if(isalpha((int) port[0]) != 0)
    {
        service_info = getservbyname(port, proto);

        if(service_info != NULL)
        {
            conv = ntohs(service_info->s_port);
            return conv;
        }
        else
        {
            FatalError("ERROR %s (%d) => getservbyname() failed on \"%s\"\n",
                       file_name, file_line, port);
        }
    }
    if(!isdigit((int) port[0]))
    {
        FatalError("ERROR %s (%d) => Invalid port: %s\n", file_name,
                   file_line, port);
    }
    /* convert the value */
    conv = atoi(port);

    /* make sure it's in bounds */
    if((conv >= 0) && (conv < 65536))
    {
        return conv;
    }
    else
    {
        FatalError("ERROR %s (%d) => bad port number: %s", file_name,
                   file_line, port);
    }

    return 0;
}



/****************************************************************************
 *
 * Function: ParseMessage(char *)
 *
 * Purpose: Stuff the alert message onto the rule
 *
 * Arguments: msg => the msg string
 *
 * Returns: void function
 *
 ***************************************************************************/
void ParseMessage(char *msg)
{
    char *ptr;
    char *end;
    int size;

    /* figure out where the message starts */
    ptr = index(msg, '"');

    if(ptr == NULL)
    {
        ptr = msg;
    }
    else
        ptr++;

    end = index(ptr, '"');

    if(end != NULL)
        *end = 0;

    while(isspace((int) *ptr))
        ptr++;

    /* find the end of the alert string */
    size = strlen(msg) + 1;

    /* alloc space for the string and put it in the rule */
    if(size > 0)
    {
        otn_tmp->message = strdup(ptr);

        /*otn_tmp->message = (char *) calloc((sizeof(char) * size), sizeof(char));
        strncpy(otn_tmp->message, ptr, size);
        otn_tmp->message[size] = 0;*/

#ifdef DEBUG
        printf("Rule message set to: %s\n", otn_tmp->message);
#endif

    }
    else
    {
        ErrorMessage("ERROR %s (%d): bad alert message size %d\n", file_name, file_line, size);
    }

    return;
}



/****************************************************************************
 *
 * Function: ParseLogto(char *)
 *
 * Purpose: stuff the special log filename onto the proper rule option
 *
 * Arguments: filename => the file name
 *
 * Returns: void function
 *
 ***************************************************************************/
void ParseLogto(char *filename)
{
    char *sptr;
    char *eptr;

    /* grab everything between the starting " and the end one */
    sptr = index(filename, '"');
    eptr = strrchr(filename, '"');

    if(sptr != NULL && eptr != NULL)
    {
        /* increment past the first quote */
        sptr++;

        /* zero out the second one */
        *eptr = 0;
    }
    else
    {
        sptr = filename;
    }

    /* malloc up a nice shiny clean buffer */
    otn_tmp->logto = (char *) calloc(strlen(sptr) + 1, sizeof(char));

    bzero((char *) otn_tmp->logto, strlen(sptr) + 1);

    strncpy(otn_tmp->logto, sptr, strlen(sptr)+1);

    return;
}




/****************************************************************************
 *
 * Function: ParseActivates(char *)
 *
 * Purpose: Set an activation link record
 *
 * Arguments: act_num => rule number to be activated
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseActivates(char *act_num)
{
    /*
     * allocate a new node on the RTN get rid of whitespace at the front of
     * the list
     */
    while(!isdigit((int) *act_num))
        act_num++;

    otn_tmp->activates = atoi(act_num);

    return;
}




/****************************************************************************
 *
 * Function: ParseActivatedBy(char *)
 *
 * Purpose: Set an activation link record
 *
 * Arguments: act_by => rule number to be activated
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseActivatedBy(char *act_by)
{
    ActivateList *al_ptr;

    al_ptr = rtn_tmp->activate_list;

    if(al_ptr == NULL)
    {
        rtn_tmp->activate_list = (ActivateList *) calloc(sizeof(ActivateList), sizeof(char));

        if(rtn_tmp->activate_list == NULL)
        {
            FatalError("ERROR: ParseActivatedBy() calloc failed: %s\n", strerror(errno));
        }

        al_ptr = rtn_tmp->activate_list;
    }
    else
    {
        while(al_ptr->next != NULL)
        {
            al_ptr = al_ptr->next;
        }

        al_ptr->next = (ActivateList *) calloc(sizeof(ActivateList), sizeof(char));

        al_ptr = al_ptr->next;

        if(al_ptr == NULL)
        {
            FatalError("ERROR: ParseActivatedBy() calloc failed: %s\n", strerror(errno));
        }
    }

    /* get rid of whitespace at the front of the list */
    while(!isdigit((int) *act_by))
        act_by++;

    /* set the RTN list node number */
    al_ptr->activated_by = atoi(act_by);

    /* set the OTN list node number */
    otn_tmp->activated_by = atoi(act_by);

    return;
}



void ParseCount(char *num)
{
    while(!isdigit((int) *num))
        num++;

    otn_tmp->activation_counter = atoi(num);

#ifdef DEBUG
    printf("Set activation counter to %d\n", otn_tmp->activation_counter);
#endif

    return;
}



/****************************************************************************
 *
 * Function: XferHeader(RuleTreeNode *, RuleTreeNode *)
 *
 * Purpose: Transfer the rule block header data from point A to point B
 *
 * Arguments: rule => the place to xfer from
 *            rtn => the place to xfer to
 *
 * Returns: void function
 *
 ***************************************************************************/
void XferHeader(RuleTreeNode * rule, RuleTreeNode * rtn)
{
    rtn->type = rule->type;
    rtn->sip = rule->sip;
    rtn->dip = rule->dip;
    rtn->hsp = rule->hsp;
    rtn->lsp = rule->lsp;
    rtn->hdp = rule->hdp;
    rtn->ldp = rule->ldp;
    rtn->flags = rule->flags;
}



/****************************************************************************
 *
 * Function: TestHeader(RuleTreeNode *, RuleTreeNode *)
 *
 * Purpose: Check to see if the two header blocks are identical
 *
 * Arguments: rule => uh
 *            rtn  => uuuuhhhhh....
 *
 * Returns: 1 if they match, 0 if they don't
 *
 ***************************************************************************/
int TestHeader(RuleTreeNode * rule, RuleTreeNode * rtn)
{
    IpAddrSet *rule_idx;  /* ip struct indexer */
    IpAddrSet *rtn_idx;   /* ip struct indexer */

    rtn_idx = rtn->sip;
    for(rule_idx=rule->sip;rule_idx!=NULL;rule_idx=rule_idx->next)
    {
        if(!memcmp(rtn_idx, rule_idx, sizeof(IpAddrSet)))
        {
            rtn_idx = rtn_idx->next;
        }
        else
        {
            return 0;
        }
    }

    rtn_idx = rtn->dip;
    for(rule_idx=rule->dip;rule_idx!=NULL;rule_idx=rule_idx->next)
    {
        if(!memcmp(rtn_idx, rule_idx, sizeof(IpAddrSet)))
        {
            rtn_idx = rtn_idx->next;
        }
        else
        {
            return 0;
        }
    }

    if(rtn->hsp == rule->hsp)
    {
        if(rtn->lsp == rule->lsp)
        {
            if(rtn->hdp == rule->hdp)
            {
                if(rtn->ldp == rule->ldp)
                {
                    if(rtn->flags == rule->flags)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}


/****************************************************************************
 *
 * Function: VarAlloc()
 *
 * Purpose: allocates memory for a variable
 *
 * Arguments: none
 *
 * Returns: pointer to new VarEntry
 *
 ***************************************************************************/
struct VarEntry *VarAlloc()
{
    struct VarEntry *new;

    if((new = (struct VarEntry *) calloc(sizeof(struct VarEntry), sizeof(char))) == NULL)
    {
        FatalError("ERROR: cannot allocate memory for VarEntry.");
    }
    new->name = NULL;
    new->value = NULL;
    new->prev = NULL;
    new->next = NULL;

    return(new);
}

/****************************************************************************
 *
 * Function: VarDefine(char *, char *)
 *
 * Purpose: define the contents of a variable
 *
 * Arguments: name => the name of the variable
 *            value => the contents of the variable
 *
 * Returns: void function
 *
 ***************************************************************************/
struct VarEntry *VarDefine(char *name, char *value)
{
    struct VarEntry *p;
    int found = 0;

    if(value == NULL)
    {
        ErrorMessage("[!] ERROR: Bad value in variable definition!\n");
        FatalError("        Make sure you don't have a \"$\" in the var name\n");
    }

    if(!VarHead)
    {
        p = VarAlloc();
        p->name = strdup(name);
        p->value = strdup(value);
        p->prev = p;
        p->next = p;

        VarHead = p;

        return p;
    }
    p = VarHead;

    do
    {
        if(strcasecmp(p->name, name) == 0)
        {
            found = 1;
            break;
        }
        p = p->next;
    } while(p != VarHead);

    if( found && !(p->flags & VAR_STATIC))
    {
        if( p->value )
            free(p->value);
 
         p->value = strdup(value);
     }
     else
    {
        p = VarAlloc();
        p->name = strdup(name);
        p->value = strdup(value);
        p->prev = VarHead;
        p->next = VarHead->next;
        p->next->prev = p;
        VarHead->next = p;
    }
    return p;
}


/****************************************************************************
 *
 * Function: VarDelete(char *)
 *
 * Purpose: deletes a defined variable
 *
 * Arguments: name => the name of the variable
 *
 * Returns: void function
 *
 ***************************************************************************/
void VarDelete(char *name)
{
    struct VarEntry *p;


    if(!VarHead)
        return;

    p = VarHead;

    do
    {
        if(strcasecmp(p->name, name) == 0)
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;

            if(VarHead == p)
                if((VarHead = p->next) == p)
                    VarHead = NULL;

            if(p->name)
                free(p->name);

            if(p->value)
                free(p->value);

            free(p);

            return;
        }
        p = p->next;

    } while(p != VarHead);
}


/****************************************************************************
 *
 * Function: VarGet(char *)
 *
 * Purpose: get the contents of a variable
 *
 * Arguments: name => the name of the variable
 *
 * Returns: char * to contents of variable or NULL
 *
 ***************************************************************************/
char *VarGet(char *name)
{
    struct VarEntry *p;


    if(!VarHead)
        return(NULL);

    p = VarHead;

    do
    {
        if(strcasecmp(p->name, name) == 0)
            return(p->value);

        p = p->next;

    } while(p != VarHead);

    return(NULL);
}



/****************************************************************************
 *
 * Function: ExpandVars(char *)
 *
 * Purpose: expand all variables in a string
 *
 * Arguments: string => the name of the variable
 *
 * Returns: char * to the expanded string
 *
 ***************************************************************************/
char *ExpandVars(char *string)
{
    static char estring[PARSERULE_SIZE];
    char rawvarname[128], varname[128], varaux[128], varbuffer[128], varmodifier, *varcontents;
    int varname_completed, c, i, j, iv, jv, l_string, name_only;


    if(!string || !*string || !strchr(string, '$'))
        return(string);

    bzero((char *) estring, sizeof(estring));

    i = j = 0;
    l_string = strlen(string);
#ifdef DEBUG
    printf ("ExpandVars, Before: %s\n", string);
#endif

    while(i < l_string && j < sizeof(estring) - 1)
    {
        c = string[i++];

        if(c == '$')
        {
            bzero((char *) rawvarname, sizeof(rawvarname));
            varname_completed = 0;
            name_only = 1;
            iv = i;
            jv = 0;

            if(string[i] == '(')
            {
                name_only = 0;
                iv = i + 1;
            }

            while(!varname_completed
                  && iv < l_string
                  && jv < sizeof(rawvarname) - 1)
            {
                c = string[iv++];

                if((name_only && !(isalnum(c) || c == '_'))
                   || (!name_only && c == ')'))
                {
                    varname_completed = 1;

                    if(name_only)
                        iv--;
                }
                else
                {
                    rawvarname[jv++] = c;
                }
            }

            if(varname_completed || iv == l_string)
            {
                char *p;

                i = iv;

                varcontents = NULL;

                bzero((char *) varname, sizeof(varname));
                bzero((char *) varaux, sizeof(varaux));
                varmodifier = ' ';

                if((p = strchr(rawvarname, ':')))
                {
                    strncpy(varname, rawvarname, p - rawvarname);

                    if(strlen(p) >= 2)
                    {
                        varmodifier = *(p + 1);
                        strcpy(varaux, p + 2);
                    }
                }
                else
                    strcpy(varname, rawvarname);

                bzero((char *) varbuffer, sizeof(varbuffer));

                varcontents = VarGet(varname);

                switch(varmodifier)
                {
                    case '-':
                        if(!varcontents || !strlen(varcontents))
                            varcontents = varaux;
                        break;

                    case '?':
                        if(!varcontents || !strlen(varcontents))
                        {
                            ErrorMessage("ERROR %s (%d): ", file_name, file_line);

                            if(strlen(varaux))
                                ErrorMessage("%s\n", varaux);
                            else
                                FatalError("ERROR: Undefined variable \"%s\"\n", varname);
                        }
                        break;
                }

                if(varcontents)
                {
                    int l_varcontents = strlen(varcontents);

                    iv = 0;

                    while(iv < l_varcontents && j < sizeof(estring) - 1)
                        estring[j++] = varcontents[iv++];
                }
            }
            else
            {
                estring[j++] = '$';
            }
        }
        else
        {
            estring[j++] = c;
        }
    }

#ifdef DEBUG
    printf ("ExpandVars, After: %s\n", estring);
#endif

    return(estring);
}



/******************************************************************
 *
 * Function: LinkDynamicRules()
 *
 * Purpose: Move through the activation and dynamic lists and link
 *          the activation rules to the rules that they activate.
 *
 * Arguments: None
 *
 * Returns: void function
 *
 ******************************************************************/
void LinkDynamicRules()
{
    SetLinks(Activation.TcpList, Dynamic.TcpList);
    SetLinks(Activation.UdpList, Dynamic.UdpList);
    SetLinks(Activation.IcmpList, Dynamic.IcmpList);
}




/******************************************************************
 *
 * Function: SetLinks()
 *
 * Purpose: Move through the activation and dynamic lists and link
 *          the activation rules to the rules that they activate.
 *
 * Arguments: activator => the activation rules
 *            activatee => the rules being activated
 *
 * Returns: void function
 *
 ******************************************************************/
void SetLinks(RuleTreeNode * activator, RuleTreeNode * activated_by)
{
    RuleTreeNode *act_idx;
    RuleTreeNode *dyn_idx;
    OptTreeNode *act_otn_idx;

    act_idx = activator;
    dyn_idx = activated_by;

    /* walk thru the RTN list */
    while(act_idx != NULL)
    {
        if(act_idx->down != NULL)
        {
            act_otn_idx = act_idx->down;

            while(act_otn_idx != NULL)
            {
                act_otn_idx->RTN_activation_ptr = GetDynamicRTN(act_otn_idx->activates, dyn_idx);

                if(act_otn_idx->RTN_activation_ptr != NULL)
                {
                    act_otn_idx->OTN_activation_ptr = GetDynamicOTN(act_otn_idx->activates, act_otn_idx->RTN_activation_ptr);
                }
                act_otn_idx = act_otn_idx->next;
            }
        }
        act_idx = act_idx->right;
    }
}



RuleTreeNode *GetDynamicRTN(int link_number, RuleTreeNode * dynamic_rule_tree)
{
    RuleTreeNode *rtn_idx;
    ActivateList *act_list;

    rtn_idx = dynamic_rule_tree;

    while(rtn_idx != NULL)
    {
        act_list = rtn_idx->activate_list;

        while(act_list != NULL)
        {
            if(act_list->activated_by == link_number)
            {
                return rtn_idx;
            }
            act_list = act_list->next;
        }

        rtn_idx = rtn_idx->right;
    }

    return NULL;
}




OptTreeNode *GetDynamicOTN(int link_number, RuleTreeNode * dynamic_rule_tree)
{
    OptTreeNode *otn_idx;

    otn_idx = dynamic_rule_tree->down;

    while(otn_idx != NULL)
    {
        if(otn_idx->activated_by == link_number)
        {
            return otn_idx;
        }
        otn_idx = otn_idx->next;
    }

    return NULL;
}



/***************************************************************/
/**  D E T E C T I O N   E N G I N E   S T A R T S   H E R E  **/
/***************************************************************/
void Preprocess(Packet * p)
{
    PreprocessFuncNode *idx;

    do_detect = 1;
    idx = PreprocessList;

    while(idx != NULL)
    {
        idx->func(p);
        idx = idx->next;
    }

    if(!p->frag_flag && do_detect)
    {
        Detect(p);
    }
}

void CallLogFuncs(Packet * p, char *message, ListHead * head)
{
    OutputFuncNode *idx = NULL;

    pc.log_pkts++;

    if(head == NULL)
    {
        CallLogPlugins(p, message);
        return;
    }

    idx = head->LogList;
    if(idx == NULL)
        idx = LogList;

    while(idx != NULL)
    {
        idx->func(p, message, idx->arg);
        idx = idx->next;
    }

    return;
}

void CallLogPlugins(Packet * p, char *message)
{
    OutputFuncNode *idx;

    idx = LogList;

    while(idx != NULL)
    {
        idx->func(p, message, idx->arg);
        idx = idx->next;
    }

    return;
}

void CallAlertFuncs(Packet * p, char *message, ListHead * head)
{
    OutputFuncNode *idx = NULL;

    pc.alert_pkts++;

    if(head == NULL)
    {
        CallAlertPlugins(p, message);
        return;
    }

    idx = head->AlertList;
    if(idx == NULL)
        idx = AlertList;

    while(idx != NULL)
    {
        idx->func(p, message, idx->arg);
        idx = idx->next;
    }

    return;
}


void CallAlertPlugins(Packet * p, char *message)
{
    OutputFuncNode *idx;

    idx = AlertList;

    while(idx != NULL)
    {
        idx->func(p, message, idx->arg);
        idx = idx->next;
    }

    return;
}



/****************************************************************************
 *
 * Function: Detect(Packet *)
 *
 * Purpose: Apply the rules lists to the current packet
 *
 * Arguments: p => ptr to the decoded packet struct
 *
 * Returns: 1 == detection event
 *          0 == no detection
 *
 ***************************************************************************/
int Detect(Packet * p)
{
#ifdef BENCHMARK
    cmpcount = 0;
#endif


    RuleListNode *rule;

    rule = RuleLists;

    while(rule != NULL)
    {
#ifdef DEBUG
        printf("[*] Evaluating rule list: %s\n", rule->name);
#endif                                /* DEBUG */
        if(EvalPacket(rule->RuleList, rule->mode, p))
            return rule->rval;
        rule = rule->next;
    }
    return 0;
}



/****************************************************************************
 *
 * Function: EvalPacket(ListHead *, int )
 *
 * Purpose: Figure out which rule tree to call based on protocol
 *
 * Arguments: List => the rule list to check
 *            mode => the rule mode (alert, log, etc)
 *
 * Returns: 1 on a match, 0 on a miss
 *
 ***************************************************************************/
int EvalPacket(ListHead * List, int mode, Packet * p)
{
    RuleTreeNode *rtn_idx;

    if(p->iph == NULL)
    {
        return 0;
    }
    /* figure out which list to look at */

    rtn_idx = NULL;

    switch(p->iph->ip_proto)
    {
        case IPPROTO_TCP:
#ifdef DEBUG
            printf("Detecting on TcpList\n");
#endif
            if(p->tcph != NULL)
                rtn_idx = List->TcpList;
            break;

        case IPPROTO_UDP:
#ifdef DEBUG
            printf("Detecting on UdpList\n");
#endif
            if(p->udph != NULL)
                rtn_idx = List->UdpList;
            break;

        case IPPROTO_ICMP:
#ifdef DEBUG
            printf("Detecting on IcmpList\n");
#endif
            if(p->icmph != NULL)
                rtn_idx = List->IcmpList;
            break;

        default:
            break;
    }

    return EvalHeader(rtn_idx, p);
}



/****************************************************************************
 *
 * Function: EvalHeader(RuleTreeNode *, Packet * )
 *
 * Purpose: Implement two dimensional recursive linked-list-of-function-pointers
 *          detection engine!  This part looks at the IP header info (and
 *          ports if necessary) and decides whether or not to proceed down
 *          the rule option chain.  Did I mention it's recursive?  For all
 *          you fans of the old goto system, sorry.... :)
 *
 * Arguments: rtn_idx => the rule block node to test
 *            p => ptr to the packet data structure
 *
 * Returns: 1 on a match, 0 on a miss
 *
 ***************************************************************************/
int EvalHeader(RuleTreeNode * rtn_idx, Packet * p)
{
    int rule_match = 0;

    if(rtn_idx == NULL)
    {
        return 0;
    }
    if(rtn_idx->type == RULE_DYNAMIC)
    {
        if(!active_dynamic_nodes)
        {
            return 0;
        }
        if(rtn_idx->active_flag == 0)
        {
            return EvalHeader(rtn_idx->right, p);
        }
    }
#ifdef DEBUG
    printf("[*] Rule Head %d\n", rtn_idx->head_node_number);
#endif

    if(!rtn_idx->rule_func->RuleHeadFunc(p, rtn_idx, rtn_idx->rule_func))
    {
#ifdef DEBUG
        printf("   => Header check failed, checking next node\n");
#endif
        return EvalHeader(rtn_idx->right, p);
#ifdef DEBUG
        printf("   => returned from next node check\n");
#endif
    }
    else
    {

#ifdef DEBUG
        printf("   => Got head match, checking options chain\n");
#endif

        rule_match = EvalOpts(rtn_idx->down, p);

        if(rule_match)
        {
#ifdef DEBUG
            printf("   => Got rule match, rtn_idx type = %d\n", rtn_idx->type);
#endif
            TriggerResponses(rtn_idx->rsp_func, p);

            switch(rtn_idx->type)
            {
                case RULE_PASS:
                    return PassAction();

                case RULE_ACTIVATE:
                    return ActivateAction(p, otn_tmp);

                case RULE_ALERT:
                    return AlertAction(p, otn_tmp);

                case RULE_DYNAMIC:
                    return DynamicAction(p, otn_tmp);

                case RULE_LOG:
                    return LogAction(p, otn_tmp);
            }
        }

        if(!rule_match)
        {
#ifdef DEBUG
            printf("No match, continuing...\n");
#endif
            return EvalHeader(rtn_idx->right, p);
        }
    }
#ifdef BENCHMARK
    printf(" **** cmpcount: %d **** \n", cmpcount);
#endif

    return 0;


}

void TriggerResponses(RspFpList * func, Packet * p)
{

    RspFpList *idx;

    idx = func;

#ifdef DEBUG
    printf("Triggering responses %p\n",idx);
#endif

    while(idx != NULL)
    {
        idx->ResponseFunc(p, idx);
        idx = idx->next;
    }

}

int CheckAddrPort(IpAddrSet *rule_addr, u_int16_t hi_port, u_int16_t lo_port, Packet * p, char flags, int mode)
{
    u_long pkt_addr;         /* packet IP address */
    u_short pkt_port;        /* packet port */
    int global_except_addr_flag = 0; /* global exception flag is set */
    int any_port_flag = 0;           /* any port flag set */
    int except_addr_flag = 0;        /* any addr flag set */
    int except_port_flag = 0;        /* port exception flag set */
    int ip_match = 0;                /* flag to indicate addr match made */
    IpAddrSet *idx;  /* ip addr struct indexer */

#ifdef DEBUG
    printf ("CheckAddrPort: ");
#endif
    /* set up the packet particulars */
    if(mode & CHECK_SRC)
    {
        pkt_addr = p->iph->ip_src.s_addr;
        pkt_port = p->sp;

#ifdef DEBUG
        printf ("SRC ");
#endif

        if(mode & INVERSE)
        {
            global_except_addr_flag = flags & EXCEPT_DST_IP;
            any_port_flag = flags & ANY_DST_PORT;
            except_port_flag = flags & EXCEPT_DST_PORT;
        }
        else
        {
            global_except_addr_flag = flags & EXCEPT_SRC_IP;
            any_port_flag = flags & ANY_SRC_PORT;
            except_port_flag = flags & EXCEPT_SRC_PORT;
        }
    }
    else
    {
        pkt_addr = p->iph->ip_dst.s_addr;
        pkt_port = p->dp;

#ifdef DEBUG
        printf ("DST ");
#endif

        if(mode & INVERSE)
        {
            global_except_addr_flag = flags & EXCEPT_SRC_IP;
            any_port_flag = flags & ANY_SRC_PORT;
            except_port_flag = flags & EXCEPT_SRC_PORT;
        }
        else
        {
            global_except_addr_flag = flags & EXCEPT_DST_IP;
            any_port_flag = flags & ANY_DST_PORT;
            except_port_flag = flags & EXCEPT_DST_PORT;
        }
    }
#ifdef DEBUG
    printf ("addr %lx, port %d", pkt_addr, pkt_port);
#endif

    idx = rule_addr;
    if(!(global_except_addr_flag)) /*modeled after Check{Src,Dst}IP function*/
    {
        while(idx != NULL)
        {
            except_addr_flag = idx->addr_flags & EXCEPT_IP;

            /* test the rule address vs. the packet address */
            if(!((idx->ip_addr==(pkt_addr & idx->netmask)) ^ except_addr_flag))
            {
                idx = idx->next;
            }
            else
            {
                ip_match = 1;
                goto bail;
            }
        }
    }
    else
    {
#ifdef DEBUG
        printf(", global exception flag set");
#endif
        /* global exception flag is up, we can't match on *any* 
         * of the source addresses 
         */
        while(idx != NULL)
        {
            except_addr_flag = idx->addr_flags & EXCEPT_IP;

            /* test the rule address vs. the packet address */
            if(((idx->ip_addr == (pkt_addr & idx->netmask)) ^ except_addr_flag))
            {
#ifdef DEBUG
                printf(", address matched, packet rejected\n");
#endif
                /* got address match on globally negated rule, fail */
                return 0;
            }
            idx = idx->next;
        }
        ip_match = 1;
    }

    bail:
    if(!ip_match)
    {
#ifdef DEBUG
        printf(", no address match,  packet rejected\n");
#endif
        return 0;
    }

#ifdef DEBUG
    printf(", addresses accepted");
#endif

    /* if the any port flag is up, we're all done (success) */
    if(any_port_flag)
    {
#ifdef DEBUG
        printf(", any port match, packet accepted\n");
#endif
        return 1;
    }

    /* check the packet port against the rule port */
    if((pkt_port > hi_port) || (pkt_port < lo_port))
    {
        /* if the exception flag isn't up, fail */
        if(!except_port_flag)
        {
#ifdef DEBUG
            printf(", port mismatch,  packet rejected\n");
#endif
            return 0;
        }
#ifdef DEBUG
        printf(", port mismatch exception");
#endif
    }
    else
    {
        /* if the exception flag is up, fail */
        if(except_port_flag)
        {
#ifdef DEBUG
            printf(", port match exception,  packet rejected\n");
#endif
            return 0;
        }
#ifdef DEBUG
        printf(", ports match");
#endif
    }

    /* ports and address match */
#ifdef DEBUG
    printf(", packet accepted!\n");
#endif
    return 1;

}


/****************************************************************************
 *
 * Function: EvalOpts(OptTreeNode *, Packet *)
 *
 * Purpose: Implements section 2 of recursive detection engine.  Goes
 *          thru the options chain and see if the current packet matches
 *          any of the rules
 *
 * Arguments: List => the OTN list
 *            p => pointer to the packet data struct
 *
 * Returns: 1 on a match, 0 on no match
 *
 ***************************************************************************/
int EvalOpts(OptTreeNode * List, Packet * p)
{
    if(List == NULL)
        return 0;

#ifdef DEBUG
    printf("   => Checking Option Node %d\n", List->chain_node_number);
#endif

    if(List->type == RULE_DYNAMIC && !List->active_flag)
    {
        return EvalOpts(List->next, p);
    }

    if(List->opt_func == NULL)
    {
        FatalError("List->opt_func was NULL on option #%d!\n", List->chain_node_number);
    }

    if(!List->opt_func->OptTestFunc(p, List, List->opt_func))
    {
        return EvalOpts(List->next, p);
    }
    else
    {
        /* rule match actions are called from EvalHeader */
        otn_tmp = List;
        return 1;
    }

    return 0;
}


/****************************************************************************
 *
 * Function: DumpChain(RuleTreeNode *, char *, char *)
 *
 * Purpose: print out the chain lists by header block node group
 *
 * Arguments: rtn_idx => the RTN index pointer
 *                       rulename => the name of the rule the list belongs to
 *            listname => the name of the list being printed out
 *
 * Returns: void function
 *
 ***************************************************************************/
void DumpChain(RuleTreeNode * rtn_head, char *rulename, char *listname)
{
    RuleTreeNode *rtn_idx;
    OptTreeNode *otn_idx;
    IpAddrSet *idx;  /* indexing pointer */
    int i;

    printf("%s %s\n", rulename, listname);

    rtn_idx = rtn_head;

    if(rtn_idx == NULL)
        printf("    Empty!\n\n");

    /* walk thru the RTN list */
    while(rtn_idx != NULL)
    {
        printf("Rule type: %d\n", rtn_idx->type);
        printf("SRC IP List:\n");
        idx = rtn_idx->sip;
        i = 0;
        while(idx != NULL)
        {
            printf("[%d]    0x%.8lX / 0x%.8lX", i++, (u_long) idx->ip_addr, (u_long) idx->netmask);
            if(idx->addr_flags & EXCEPT_IP)
            {
                printf("    (EXCEPTION_FLAG Active)\n");
            }
            else
            {
                printf("\n");
            }
            idx = idx->next;
        }

        printf("DST IP List:\n");
        idx = rtn_idx->dip;
        i = 0;
        while(idx != NULL)
        {
            printf("[%d]    0x%.8lX / 0x%.8lX", i++,(u_long)  idx->ip_addr,(u_long)  idx->netmask);
            if(idx->addr_flags & EXCEPT_IP)
            {
                printf("    (EXCEPTION_FLAG Active)\n");
            }
            else
            {
                printf("\n");
            }
            idx = idx->next;
        }
        printf("SRC PORT: %d - %d \n", rtn_idx->lsp, rtn_idx->hsp);
        printf("DST PORT: %d - %d \n", rtn_idx->ldp, rtn_idx->hdp);
        printf("Flags: ");
        if(rtn_idx->flags & EXCEPT_SRC_IP)
            printf("EXCEPT_SRC_IP ");
        if(rtn_idx->flags & EXCEPT_DST_IP)
            printf("EXCEPT_DST_IP ");
        if(rtn_idx->flags & ANY_SRC_PORT)
            printf("ANY_SRC_PORT ");
        if(rtn_idx->flags & ANY_DST_PORT)
            printf("ANY_DST_PORT ");
        if(rtn_idx->flags & EXCEPT_SRC_PORT)
            printf("EXCEPT_SRC_PORT ");
        if(rtn_idx->flags & EXCEPT_DST_PORT)
            printf("EXCEPT_DST_PORT ");
        printf("\n");

        otn_idx = rtn_idx->down;

        /* print the RTN header number */
        printf("Head: %d (type: %d)\n", rtn_idx->head_node_number, otn_idx->type);
        printf("      |\n");
        printf("       ->");


        /* walk thru the OTN chain */
        while(otn_idx != NULL)
        {
            printf(" %d", otn_idx->chain_node_number);
            otn_idx = otn_idx->next;
        }

        printf("|=-\n");

        rtn_idx = rtn_idx->right;
    }
}



void IntegrityCheck(RuleTreeNode * rtn_head, char *rulename, char *listname)
{
    RuleTreeNode *rtn_idx = NULL;
    OptTreeNode *otn_idx;
    OptFpList *ofl_idx;
    int opt_func_count;

#ifdef DEBUG
    char chainname[STD_BUF];

    snprintf(chainname, STD_BUF - 1, "%s %s", rulename, listname);

    if(!pv.quiet_flag)
        printf("%-20s: ", chainname);
#endif

    if(rtn_head == NULL)
    {
#ifdef DEBUG
        if(!pv.quiet_flag)
            printf("Empty list...\n");
#endif
        return;
    }

    rtn_idx = rtn_head;

    while(rtn_idx != NULL)
    {
        otn_idx = rtn_idx->down;

        while(otn_idx != NULL)
        {
            ofl_idx = otn_idx->opt_func;
            opt_func_count = 0;

            while(ofl_idx != NULL)
            {
                opt_func_count++;

#ifdef DEBUG
                printf("%p->", ofl_idx->OptTestFunc);
#endif

                ofl_idx = ofl_idx->next;
            }

            if(opt_func_count == 0)
            {
                ErrorMessage("ERROR: Got Zero Length List, please tell Marty!\n");
#ifndef JUSTDOIT
                exit(1);
#endif
            }
#ifdef DEBUG
            printf("\n");
#endif

            otn_idx = otn_idx->next;
        }

        rtn_idx = rtn_idx->right;
    }

#ifdef DEBUG
    if(!pv.quiet_flag)
        printf("OK\n");
#endif

}



int CheckBidirectional(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
#ifdef DEBUG
    printf("Checking bidirectional rule...\n");
#endif
    if(CheckAddrPort(rtn_idx->sip, rtn_idx->hsp, rtn_idx->lsp, p,
                     (char)rtn_idx->flags, CHECK_SRC))
    {
#ifdef DEBUG
        printf("   Src->Src check passed\n");
#endif
        if(! CheckAddrPort(rtn_idx->dip, rtn_idx->hdp, rtn_idx->ldp, p,
                           (char)rtn_idx->flags, CHECK_DST))
        {
#ifdef DEBUG
            printf("   Dst->Dst check failed, checking inverse combination\n");
#endif
            if(CheckAddrPort(rtn_idx->dip, rtn_idx->hdp, rtn_idx->ldp, p,
                             (char)rtn_idx->flags, (CHECK_SRC | INVERSE)))
            {
#ifdef DEBUG
                printf("   Inverse Dst->Src check passed\n");
#endif
                if(!CheckAddrPort(rtn_idx->sip, rtn_idx->hsp, rtn_idx->lsp, p,
                                  (char)rtn_idx->flags, (CHECK_DST | INVERSE)))
                {
#ifdef DEBUG
                    printf("   Inverse Src->Dst check failed\n");
#endif
                    return 0;
                }
#ifdef DEBUG
                else
                {
                    printf("Inverse addr/port match\n");
                }
#endif
            }
            else
            {
#ifdef DEBUG
                printf("   Inverse Dst->Src check failed, trying next rule\n");
#endif
                return 0;
            }
        }
#ifdef DEBUG
        else
        {
            printf("dest IP/port match\n");
        }
#endif
    }
    else
    {
#ifdef DEBUG
        printf("   Src->Src check failed, trying inverse test\n");
#endif
        if(CheckAddrPort(rtn_idx->dip, rtn_idx->hdp, rtn_idx->ldp, p,
                         (char)rtn_idx->flags, CHECK_SRC | INVERSE))
        {
#ifdef DEBUG
            printf("   Dst->Src check passed\n");
#endif
            if(! CheckAddrPort(rtn_idx->sip, rtn_idx->hsp, rtn_idx->lsp, p, (char)rtn_idx->flags, CHECK_DST | INVERSE))
            {
#ifdef DEBUG
                printf("   Src->Dst check failed\n");
#endif
                return 0;
            }
#ifdef DEBUG
            else
            {
                printf("Inverse addr/port match\n");
            }
#endif
        }
        else
        { 
#ifdef DEBUG
            printf("   Inverse test failed, testing next rule...\n");
#endif
            return 0;
        }
    }
#ifdef DEBUG
    printf("   Bidirectional success!\n");
#endif
          return 1;
}



/****************************************************************************
 *
 * Function: CheckSrcIpEqual(Packet *, struct _RuleTreeNode *, RuleFpList *)
 *
 * Purpose: Test the source IP and see if it equals the SIP of the packet
 *
 * Arguments: p => ptr to the decoded packet data structure
 *            rtn_idx => ptr to the current rule data struct
 *            fp_list => ptr to the current function pointer node
 *
 * Returns: 0 on failure (no match), 1 on success (match)
 *
 ***************************************************************************/
int CheckSrcIP(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
    IpAddrSet *idx; /* ip address indexer */

#ifdef DEBUG
    printf("CheckSrcIPEqual: ");
#endif

    /* check for global exception flag */
    if(!(rtn_idx->flags & EXCEPT_SRC_IP))
    {
        /* do the check */
        for(idx=rtn_idx->sip; idx != NULL; idx=idx->next)
        {
            if( ((idx->ip_addr == (p->iph->ip_src.s_addr & idx->netmask)) 
                        ^ (idx->addr_flags & EXCEPT_IP)) )
            {
#ifdef DEBUG
                if(idx->addr_flags & EXCEPT_IP)
                    printf("  SIP exception match\n");
                else    
                    printf("  SIP match\n");

                printf("Rule: 0x%X     Packet: 0x%X\n", idx->ip_addr, 
                        (p->iph->ip_src.s_addr & idx->netmask));
#endif
                /* the packet matches this test, proceed to the next test */
                return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
            }
        }
    }
    else
    {
        /* global exception flag is up, we can't match on *any* 
         * of the source addresses 
         */
#ifdef DEBUG
        printf("  global exception flag, \n");
#endif

        /* do the check */
        for(idx=rtn_idx->sip; idx != NULL; idx=idx->next)
        {
            if( ((idx->ip_addr == (p->iph->ip_src.s_addr & idx->netmask)) 
                        ^ (idx->addr_flags & EXCEPT_IP)) )
            {
#ifdef DEBUG
                printf("address matched, failing on SIP\n");
#endif
                /* got address match on globally negated rule, fail */
                return 0;
            }
        }
#ifdef DEBUG
        printf("no matches on SIP, passed\n");
#endif

        return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);}

#ifdef DEBUG
        printf("  Mismatch on SIP\n");
#endif

        /* return 0 on a failed test */
        return 0;
}



/****************************************************************************
 *
 * Function: CheckSrcIpNotEq(Packet *, struct _RuleTreeNode *, RuleFpList *)
 *
 * Purpose: Test the source IP and see if it's unequal to the SIP of the
 *          packet
 *
 * Arguments: p => ptr to the decoded packet data structure
 *            rtn_idx => ptr to the current rule data struct
 *            fp_list => ptr to the current function pointer node
 *
 * Returns: 0 on failure (no match), 1 on success (match)
 *
 ***************************************************************************/
int CheckSrcIPNotEq(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
    IpAddrSet *idx;  /* IP address indexer */
#ifdef DEBUG
    printf("CheckSrcIPNotEq: ");
#endif

    /* do the check */
    for(idx=rtn_idx->sip; idx != NULL; idx=idx->next)
    {
        if( idx->ip_addr != (p->iph->ip_src.s_addr & idx->netmask) )
        {
#ifdef DEBUG
            printf("  SIP exception match\n");
#endif
            /* the packet matches this test, proceed to the next test */
            return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
        }
    }

#ifdef DEBUG
    printf("  Mismatch on SIP\n");
#endif

    /* return 0 on a failed test */
    return 0;
}



/****************************************************************************
 *
 * Function: CheckDstIpEqual(Packet *, struct _RuleTreeNode *, RuleFpList *)
 *
 * Purpose: Test the dest IP and see if it equals the DIP of the packet
 *
 * Arguments: p => ptr to the decoded packet data structure
 *            rtn_idx => ptr to the current rule data struct
 *            fp_list => ptr to the current function pointer node
 *
 * Returns: 0 on failure (no match), 1 on success (match)
 *
 ***************************************************************************/
int CheckDstIP(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
    IpAddrSet *idx;  /* ip address indexer */

#ifdef DEBUG
    printf("CheckDstIPEqual: ");
#endif

    /* check for global exception flag */
    if(!(rtn_idx->flags & EXCEPT_DST_IP))
    {
        /* do the check */
        for(idx=rtn_idx->dip; idx != NULL; idx=idx->next)
        {
            if( ((idx->ip_addr == (p->iph->ip_dst.s_addr & idx->netmask)) 
                        ^ (idx->addr_flags & EXCEPT_IP)) )
            {
#ifdef DEBUG
                if(idx->addr_flags & EXCEPT_IP)
                    printf("  DIP exception match\n");
                else    
                    printf("  DIP match\n");

                printf("Rule: 0x%X     Packet: 0x%X\n", idx->ip_addr, 
                        (p->iph->ip_src.s_addr & idx->netmask));
#endif
                /* the packet matches this test, proceed to the next test */
                return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
            }
        }
    }
    else
    {
        /* global exception flag is up, we can't match on *any* 
         * of the source addresses 
         */
#ifdef DEBUG
        printf("  global exception flag, \n");
#endif

        /* do the check */
        for(idx=rtn_idx->dip; idx != NULL; idx=idx->next)
        {
            if( ((idx->ip_addr == (p->iph->ip_dst.s_addr & idx->netmask)) 
                        ^ (idx->addr_flags & EXCEPT_IP)) )
            {
#ifdef DEBUG
                printf("address matched, failing on DIP\n");
#endif
                /* got address match on globally negated rule, fail */
                return 0;
            }
        }
#ifdef DEBUG
        printf("no matches on DIP, passed\n");
#endif

        return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
    }

#ifdef DEBUG
    printf("  Mismatch on DIP\n");
#endif

    /* return 0 on a failed test */
    return 0;
}


/****************************************************************************
 *
 * Function: CheckDstIpNotEq(Packet *, struct _RuleTreeNode *, RuleFpList *)
 *
 * Purpose: Test the dest IP and see if it equals the DIP of the packet
 *
 * Arguments: p => ptr to the decoded packet data structure
 *            rtn_idx => ptr to the current rule data struct
 *            fp_list => ptr to the current function pointer node
 *
 * Returns: 0 on failure (no match), 1 on success (match)
 *
 ***************************************************************************/
int CheckDstIPNotEq(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
    IpAddrSet *idx; /* ip address indexer */

#ifdef DEBUG
    printf("CheckDstIPNotEq: ");
#endif

    /* same as above */
    for(idx=rtn_idx->dip;idx != NULL; idx=idx->next)
    {
        if( idx->ip_addr != (p->iph->ip_dst.s_addr & idx->netmask) )
        {
#ifdef DEBUG
            printf("  DIP exception match\n");
#endif
            return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
        }
    }

#ifdef DEBUG
    printf("  Mismatch on DIP\n");
#endif

    return 0;
}



int CheckSrcPortEqual(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
#ifdef DEBUG
    printf("CheckSrcPortEqual: ");
#endif

    if( (p->sp <= rtn_idx->hsp) && (p->sp >= rtn_idx->lsp) )
    {
#ifdef DEBUG
        printf("  SP match!\n");
#endif
        return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        printf("   SP mismatch!\n");
    }
#endif

    return 0;
}





int CheckSrcPortNotEq(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
#ifdef DEBUG
    printf("CheckSrcPortNotEq: ");
#endif

    if( (p->sp > rtn_idx->hsp) || (p->sp < rtn_idx->lsp) )
    {
#ifdef DEBUG
        printf("  SP exception match!\n");
#endif
        return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        printf("   SP mismatch!\n");
    }
#endif

    return 0;
}





int CheckDstPortEqual(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
#ifdef DEBUG
    printf("CheckDstPortEqual: ");
#endif

    if( (p->dp <= rtn_idx->hdp) && (p->dp >= rtn_idx->ldp) )
    {
#ifdef DEBUG
        printf(" DP match!\n");
#endif

        return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        printf(" DP mismatch!\n");
    }
#endif

    return 0;
}




int CheckDstPortNotEq(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
#ifdef DEBUG
    printf("CheckDstPortNotEq: ");
#endif

    if( (p->dp > rtn_idx->hdp) || (p->dp < rtn_idx->ldp) )
    {
#ifdef DEBUG
        printf(" DP exception match!\n");
#endif

        return fp_list->next->RuleHeadFunc(p, rtn_idx, fp_list->next);
    }
#ifdef DEBUG
    else
    {
        printf(" DP mismatch!\n");
    }
#endif

    return 0;
}



int RuleListEnd(Packet * p, struct _RuleTreeNode * rtn_idx, RuleFpList * fp_list)
{
    return 1;
}


int OptListEnd(Packet * p, struct _OptTreeNode * otn_idx, OptFpList * fp_list)
{
    return 1;
}


void CreateDefaultRules()
{
    CreateRuleType("activation", RULE_ACTIVATE, 1, &Activation);
    CreateRuleType("dynamic", RULE_DYNAMIC, 1, &Dynamic);
    CreateRuleType("alert", RULE_ALERT, 1, &Alert);
    CreateRuleType("pass", RULE_PASS, 0, &Pass);
    CreateRuleType("log", RULE_LOG, 1, &Log);
}

void printRuleOrder()
{
    printf("Rule application order: ");
    printRuleListOrder(RuleLists);
}

/****************************************************************************
 *
 * Function: CreateRuleType
 *
 * Purpose: Creates a new type of rule and adds it to the end of the rule list
 *
 * Arguments: name = name of this rule type
 *                       mode = the mode for this rule type
 *                   rval = return value for this rule type (for detect events)
 *                       head = list head to use (or NULL to create a new one)
 *
 * Returns: the ListHead for the rule type
 *
 ***************************************************************************/
ListHead *CreateRuleType(char *name, int mode, int rval, ListHead * head)
{
    RuleListNode *node;

    /*
     * if this is the first rule list node, then we need to create a new
     * list. we do not allow multiple rules with the same name.
     */
    if( RuleLists == NULL )
    {
        RuleLists = (RuleListNode *) malloc(sizeof(RuleListNode));
        node = RuleLists;
    }
    else
    {
        node = RuleLists;

        while( 1 )
        {
            if( !strcmp(node->name, name) )
                return NULL;
            if( node->next == NULL )
                break;
            node = node->next;
        }

        node->next = (RuleListNode *) malloc(sizeof(RuleListNode));
        node = node->next;
    }

    if( head == NULL )
    {
        node->RuleList = (ListHead *) malloc(sizeof(ListHead));
        node->RuleList->TcpList = NULL;
        node->RuleList->UdpList = NULL;
        node->RuleList->IcmpList = NULL;
        node->RuleList->LogList = NULL;
        node->RuleList->AlertList = NULL;
    }
    else
    {
        node->RuleList = head;
    }

    node->mode = mode;
    node->rval = rval;
    node->name = strdup(name);
    node->next = NULL;

    return node->RuleList;
}



/****************************************************************************
 *
 * Function: OrderRuleLists
 *
 * Purpose: Orders the rule lists into the specefied order.
 *
 * Returns: void function
 *
 ***************************************************************************/
void OrderRuleLists(char *order)
{
    int i;
    RuleListNode *ordered_list = NULL;
    RuleListNode *prev;
    RuleListNode *node;
    static int called = 0;
    char **toks;
    int num_toks;

    if( called > 0 )
        printf("Warning: multiple rule order directives.\n");

    toks = mSplit(order, " ", 10, &num_toks, 0);

    for( i = 0; i < num_toks; i++ )
    {
        prev = NULL;
        node = RuleLists;

        while( 1 )
        {
            if( node == NULL )
            {
                printf("ERROR: ruletype %s does not exist or has already been ordered.\n", toks[i]);
                break;
            }
            if( !strcmp(toks[i], node->name) )
            {
                if( prev == NULL )
                    RuleLists = node->next;
                else
                    prev->next = node->next;
                /* Add node to ordered list */
                ordered_list = addNodeToOrderedList(ordered_list, node);
                break;
            }
            else
            {
                prev = node;
                node = node->next;
            }
        }
    }

    /* anything left in the rule lists needs to be moved to the ordered lists */
    while( RuleLists != NULL )
    {
        node = RuleLists;
        RuleLists = node->next;
        /* Add node to ordered list */
        ordered_list = addNodeToOrderedList(ordered_list, node);
    }

    /* set the rulelists to the ordered list */
    RuleLists = ordered_list;
    called = 1;
}

RuleListNode *addNodeToOrderedList(RuleListNode * ordered_list, RuleListNode * node)
{
    RuleListNode *prev;

    prev = ordered_list;

    if( prev == NULL )
    {
        ordered_list = node;}
    else{
        while( prev->next != NULL )
            prev = prev->next;
        prev->next = node;
    }

    node->next = NULL;

    return ordered_list;
}


void printRuleListOrder(RuleListNode * node)
{
    while( node != NULL )
    {
        printf("->%s", node->name);
        node = node->next;
    }

    printf("\n");
}

/* Rule Match Action Functions */
int PassAction()
{
    pc.pass_pkts++;

#ifdef DEBUG
    printf("   => Pass rule, returning...\n");
#endif

#ifdef BENCHMARK
    printf(" **** cmpcount: %d **** \n", cmpcount);
#endif
    return 1;
}

int ActivateAction(Packet * p, OptTreeNode * otn)
{
#ifdef DEBUG
    printf("        <!!> Activating and generating alert! \"%s\"\n", otn->message);
#endif
    CallAlertFuncs(p, otn->message, otn->rtn->listhead);

    if (otn->OTN_activation_ptr == NULL)
    {
        LogMessage("WARNING: an activation rule with no dynamic rules matched!\n");
        return 0;
    }

    otn->OTN_activation_ptr->active_flag = 1;
    otn->OTN_activation_ptr->countdown = otn->OTN_activation_ptr->activation_counter;

    otn->RTN_activation_ptr->active_flag = 1;
    otn->RTN_activation_ptr->countdown += otn->OTN_activation_ptr->activation_counter;

    active_dynamic_nodes++;
#ifdef DEBUG
    printf("   => Finishing activation packet!\n");
#endif

    CallLogFuncs(p, otn->message, otn->rtn->listhead);
#ifdef DEBUG
    printf("   => Activation packet finished, returning!\n");
#endif
    return 1;
}

int AlertAction(Packet * p, OptTreeNode * otn)
{
#ifdef DEBUG
          printf("        <!!> Generating alert! \"%s\"\n", otn->message);
#endif

          CallAlertFuncs(p, otn->message, otn->rtn->listhead);

#ifdef DEBUG
          printf("   => Finishing alert packet!\n");
#endif

          CallLogFuncs(p, otn->message, otn->rtn->listhead);

#ifdef DEBUG
          printf("   => Alert packet finished, returning!\n");
#endif

          return 1;
}

int DynamicAction(Packet * p, OptTreeNode * otn)
{
    RuleTreeNode *rtn = otn->rtn;

#ifdef DEBUG
    printf("   => Logging packet data and adjusting dynamic counts (%d/%d)...\n", rtn->countdown, otn->countdown);
#endif

    CallLogFuncs(p, otn->message, otn->rtn->listhead);

    otn->countdown--;
    if( otn->countdown <= 0 )
    {
        otn->active_flag = 0;
        active_dynamic_nodes--;
#ifdef DEBUG
        printf("   <!!> Shutting down dynamic OTN node\n");
#endif
    }
    rtn->countdown--;
    if( rtn->countdown <= 0 )
    {
        rtn->active_flag = 0;
#ifdef DEBUG
        printf("   <!!> Shutting down dynamic RTN node\n");
#endif
    }
    return 1;
}

int LogAction(Packet * p, OptTreeNode * otn)
{

#ifdef DEBUG
    printf("   => Logging packet data and returning...\n");
#endif

    CallLogFuncs(p, otn->message, otn->rtn->listhead);

#ifdef BENCHMARK
    printf("        <!!> Check count = %d\n", check_count);
    check_count = 0;
    printf(" **** cmpcount: %d **** \n", cmpcount);
#endif

    return 1;
}

/* end of rule action functions */
          
