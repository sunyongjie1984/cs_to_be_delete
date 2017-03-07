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

/* $Id: rules.h,v 1.10 2001/01/02 08:06:00 roesch Exp $ */

/*  I N C L U D E S  **********************************************************/
#include "snort.h"

/*  D E F I N E S  ************************************************************/
#ifndef __RULES_H__
#define __RULES_H__

#ifdef SUNOS
    #define INADDR_NONE -1
#endif

#ifdef SOLARIS
    #define INADDR_NONE -1
#endif

#define RULE_LOG         0
#define RULE_PASS        1
#define RULE_ALERT       2
#define RULE_VAR         3
#define RULE_INCLUDE     4
#define RULE_PREPROCESS  5
#define RULE_OUTPUT      6
#define RULE_ACTIVATE    7
#define RULE_DYNAMIC     8
#define RULE_CONFIG      9
#define RULE_DECLARE     10
#define RULE_UNKNOWN     11

#define EXCEPT_SRC_IP  0x01
#define EXCEPT_DST_IP  0x02
#define ANY_SRC_PORT   0x04
#define ANY_DST_PORT   0x08
#define ANY_FLAGS      0x10
#define EXCEPT_SRC_PORT 0x20
#define EXCEPT_DST_PORT 0x40
#define BIDIRECTIONAL   0x80
#define ANY_SRC_IP      0x100
#define ANY_DST_IP      0x200

#define EXCEPT_IP      0x01

#define R_FIN          0x01
#define R_SYN          0x02
#define R_RST          0x04
#define R_PSH          0x08
#define R_ACK          0x10
#define R_URG          0x20
#define R_RES2         0x40
#define R_RES1         0x80

#define MODE_EXIT_ON_MATCH   0
#define MODE_FULL_SEARCH     1

#define CHECK_SRC            0x01
#define CHECK_DST            0x02
#define INVERSE              0x04

#define SESSION_PRINTABLE    1
#define SESSION_ALL          2

#define RESP_RST_SND         0x01
#define RESP_RST_RCV         0x02
#define RESP_BAD_NET         0x04
#define RESP_BAD_HOST        0x08
#define RESP_BAD_PORT        0x10

#define MODE_EXIT_ON_MATCH   0
#define MODE_FULL_SEARCH     1

#define SRC                  0
#define DST                  1

#ifndef PARSERULE_SIZE
#define PARSERULE_SIZE	     1024
#endif
/*#define PARSERULE_BIFURCATE   translate a <> b into a -> b, b -> a */

/*  D A T A  S T R U C T U R E S  *********************************************/
/* I'm forward declaring the rules structures so that the function
   pointer lists can reference them internally */
struct _OptTreeNode;      /* forward declaration of OTN data struct */
struct _RuleTreeNode;     /* forward declaration of RTN data struct */
struct _ListHead;    /* forward decleartion of ListHead data struct */

/* function pointer list for rule head nodes */
typedef struct _RuleFpList
{
    /* rule check function pointer */
    int (*RuleHeadFunc)(Packet *, struct _RuleTreeNode *, struct _RuleFpList *);

    /* pointer to the next rule function node */
    struct _RuleFpList *next;

} RuleFpList;

/* same as the rule header FP list */
typedef struct _OptFpList
{
    int (*OptTestFunc)(Packet *, struct _OptTreeNode *, struct _OptFpList *);

    struct _OptFpList *next;

} OptFpList;

typedef struct _RspFpList
{
    int (* ResponseFunc)(Packet *, struct _RspFpList *);
    void *params; /* params for the plugin.. type defined by plugin */
    struct _RspFpList *next;
} RspFpList;


typedef struct _OptTreeNode
{
    /* plugin/detection functions go here */
    OptFpList *opt_func;

    /* the ds_list is absolutely essential for the plugin system to work,
       it allows the plugin authors to associate "dynamic" data structures
       with the rule system, letting them link anything they can come up 
       with to the rules list */
    void *ds_list[512];   /* list of plugin data struct pointers */

    int chain_node_number;

    int type;            /* alert, log, or pass */
    int proto;           /* protocol, added for integrity checks 
                            during rule parsing */
    struct _RuleTreeNode *proto_node; /* ptr to head part... */
    int session_flag;    /* record session data */

    char *logto;         /* log file in which to write packets which 
                            match this rule*/

    char *message;       /* alert message */

    /* stuff for dynamic rules activation/deactivation */
    int active_flag;
    int activation_counter;
    int countdown;
    int activates;
    int activated_by;

    struct _OptTreeNode *OTN_activation_ptr;
    struct _RuleTreeNode *RTN_activation_ptr;

    struct _OptTreeNode *next;
    struct _RuleTreeNode *rtn;

} OptTreeNode;



typedef struct _ActivateList
{
    int activated_by;
    struct _ActivateList *next;
} ActivateList;


typedef struct _IpAddrSet
{
    u_int32_t ip_addr;
    u_int32_t netmask;
    u_int8_t  addr_flags;

    struct _IpAddrSet *next;
} IpAddrSet;

typedef struct _RuleTreeNode
{
    RuleFpList *rule_func; /* match functions.. (Bidirectional etc.. ) */
    RspFpList *rsp_func;  /* response functions */

    int head_node_number;

    int type;

    IpAddrSet *sip;
    IpAddrSet *dip;

    /*u_long sip;          
    u_long smask;       
    u_long dip;        
    u_long dmask;     */

    int not_sp_flag;     /* not source port flag */

    u_short hsp;         /* hi src port */
    u_short lsp;         /* lo src port */

    int not_dp_flag;     /* not dest port flag */

    u_short hdp;         /* hi dest port */
    u_short ldp;         /* lo dest port */

    u_int32_t flags;     /* control flags */

    /* stuff for dynamic rules activation/deactivation */
    int active_flag;
    int activation_counter;
    int countdown;
    ActivateList *activate_list;

    struct _RuleTreeNode *right;

    OptTreeNode *down;   /* list of rule options to associate with this
                            rule node */
    struct _ListHead *listhead;

} RuleTreeNode;


typedef struct _ListHead
{
    RuleTreeNode *TcpList;
    RuleTreeNode *UdpList;
    RuleTreeNode *IcmpList;
    struct _OutputFuncNode *LogList;
    struct _OutputFuncNode *AlertList;
} ListHead; 

typedef struct _RuleListNode
{
    ListHead *RuleList;         /* The rule list associated with this node */
    int mode;                   /* the rule mode */
    int rval;                   /* 0 == no detection, 1 == detection event */
    char *name;                 /* name of this rule list (for debugging)  */
    struct _RuleListNode *next; /* the next RuleListNode */
} RuleListNode;

struct VarEntry
{
    char *name;
    char *value;
    unsigned char flags;
#define VAR_STATIC      1
    struct VarEntry *prev;
    struct VarEntry *next;
};



/*  P R O T O T Y P E S  ******************************************************/

/* rule setup funcs */
void ParseRulesFile(char *, int);
void ParseRule(char *, int);
void ProcessHeadNode(RuleTreeNode *, ListHead *, int);
void ParsePreprocessor(char *);
void ParseOutputPlugin(char *);
void ParseRuleOptions(char *, int, int);
void ParseMessage(char *);
void ParseLogto(char *);
void XferHeader(RuleTreeNode *, RuleTreeNode *);
void DumpRuleChains();
void DumpChain(RuleTreeNode *, char *, char *);
struct VarEntry *VarDefine(char *, char *);
void VarDelete(char *);
void IntegrityCheckRules();
void IntegrityCheck(RuleTreeNode *, char *, char *);
void ParseListFile(char *, char *);
void LinkDynamicRules();
void SetLinks(RuleTreeNode *, RuleTreeNode *);
void ParseActivatedBy(char *);
void ParseActivates(char *);
void ParseCount(char *);
void CreateDefaultRules();
void OrderRuleLists(char *);
void printRuleOrder();
void printRuleListOrder(RuleListNode *);
int ProcessIP(char *, RuleTreeNode *, int );
IpAddrSet *AllocAddrNode(RuleTreeNode *, int );


int CheckRule(char *);
int RuleType(char *);
int WhichProto(char *);
int ParseIP(char *, IpAddrSet *);
int ParsePort(char *, u_short *,  u_short *, char *, int *);
int ConvPort(char *, char *);
int TestHeader(RuleTreeNode *, RuleTreeNode *);

char *VarGet(char *);
char *ExpandVars(char *);
char *CreateRule(char *, char *, char *);

struct VarEntry *VarAlloc();
RuleTreeNode *GetDynamicRTN(int, RuleTreeNode *);
OptTreeNode *GetDynamicOTN(int, RuleTreeNode *);
ListHead *CreateRuleType(char *, int, int, ListHead *);
RuleListNode *addNodeToOrderedList(RuleListNode *, RuleListNode *);


/* rule match action functions */
int PassAction();
int ActivateAction(Packet *, OptTreeNode *);
int AlertAction(Packet *, OptTreeNode *);
int DynamicAction(Packet *, OptTreeNode *);
int LogAction(Packet *, OptTreeNode *);

/* detection/manipulation funcs */
void Preprocess(Packet *);
int  Detect(Packet *);
void CallOutputPlugins(Packet *);
int EvalPacket(ListHead *, int, Packet * );
int EvalHeader(RuleTreeNode *, Packet *);
int EvalOpts(OptTreeNode *, Packet *);
void TriggerResponses(RspFpList *, Packet *);
int CheckAddrPort(IpAddrSet *, u_short, u_short, Packet *, char, int);

void AddrToFunc(RuleTreeNode *, int);
void PortToFunc(RuleTreeNode *, int, int, int);
void SetupRTNFuncList(RuleTreeNode *);
void AddOptFuncToList(int (*func)(Packet *,struct _OptTreeNode*,struct _OptFpList*), OptTreeNode *);
void AddRspFuncToList(int (*func) (Packet *, struct _RspFpList *), RuleTreeNode *, void *);
void AddFuncToPreprocList(void (*func)(Packet *));
void SetOutputList(void (*func)(Packet *, char *, void *), char, void *);
void AddFuncToOutputList(void (*func)(Packet *, char *, void *), char, void *);

/* detection modules */
int CheckBidirectional(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckSrcIP(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckDstIP(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckSrcIPNotEq(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckDstIPNotEq(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckSrcPortEqual(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckDstPortEqual(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckSrcPortNotEq(Packet *, struct _RuleTreeNode *, RuleFpList *);
int CheckDstPortNotEq(Packet *, struct _RuleTreeNode *, RuleFpList *);

int RuleListEnd(Packet *, struct _RuleTreeNode *, RuleFpList *);
int OptListEnd(Packet *, struct _OptTreeNode *, OptFpList *);
void CallLogPlugins(Packet *, char *);
void CallAlertPlugins(Packet *, char *);
void CallLogFuncs(Packet *, char *, ListHead *);
void CallAlertFuncs(Packet *, char *, ListHead *);

#endif /* __RULES_H__ */
