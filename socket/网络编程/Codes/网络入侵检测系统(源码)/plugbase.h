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

/* $Id: plugbase.h,v 1.20 2001/01/02 08:06:00 roesch Exp $ */
#ifndef __PLUGBASE_H__
#define __PLUGBASE_H__

#include "snort.h"

#include "rules.h"
#include "sp_pattern_match.h"
#include "sp_tcp_flag_check.h"
#include "sp_icmp_type_check.h"
#include "sp_icmp_code_check.h"
#include "sp_ttl_check.h"
#include "sp_ip_id_check.h"
#include "sp_tcp_ack_check.h"
#include "sp_tcp_seq_check.h"
#include "sp_dsize_check.h"
#include "sp_ipoption_check.h"
#include "sp_rpc_check.h"
#include "sp_icmp_id_check.h"
#include "sp_icmp_seq_check.h"
#include "sp_session.h"
#include "sp_react.h"
#include "sp_ip_tos_check.h"
#include "sp_reference.h"
#include "sp_ip_fragbits.h"
#ifdef ENABLE_RESPONSE
    #include "sp_respond.h"
#endif

#include "spp_http_decode.h"
#include "spp_minfrag.h"
#include "spp_portscan.h"
#include "spp_defrag.h"
#include "spp_tcp_stream.h"
#include "spp_anomsensor.h"

#include "spo_alert_syslog.h"
#include "spo_log_tcpdump.h"
#include "spo_database.h"
#include "spo_alert_fast.h"
#include "spo_alert_full.h"
#include "spo_alert_smb.h"
#include "spo_alert_unixsock.h"
#include "spo_xml.h"

#ifndef WIN32
	#include <sys/ioctl.h>
#endif

#ifndef OPENBSD

    #ifdef ENABLE_SSL
        #ifdef Free
/* Free macro in radix.h if defined, will conflict with OpenSSL definition */
            #undef Free
        #endif
    #endif

	#ifndef WIN32
		#include <net/route.h>
	#endif
    #ifdef ENABLE_SSL
        #undef Free
    #endif

#endif

#if defined(FREEBSD) || defined(OPENBSD)
    #include <machine/param.h>
#endif

#if defined(SOLARIS)
    #include <sys/param.h>
#endif

#if defined(FREEBSD) || defined(OPENBSD) || defined(NETBSD) || defined(OSF1)
    #include <sys/mbuf.h>
#endif

#ifdef WIN32 /* I think this is correct, may be a problem in the future. */
	#define IFNAMSIZ MAX_ADAPTER_NAME
#endif

#ifndef IFNAMSIZ /* IFNAMSIZ is defined in all platforms I checked.. */
	#include <net/if.h>
#endif

#define SMALLBUFFER 32

#define NT_OUTPUT_ALERT  0   /* output node type alert */
#define NT_OUTPUT_LOG    1   /* output node type log */

#define OUPUT_LEVEL_0     0
#define OUPUT_LEVEL_1     1
#define OUPUT_LEVEL_2     2
#define OUPUT_LEVEL_3     3
#define OUPUT_LEVEL_4     4


#define DETECTION_KEYWORD 0
#define RESPONSE_KEYWORD 1

typedef struct _KeywordXlate
{
    char *keyword;
    void (*func)(char *, OptTreeNode *, int);
} KeywordXlate;



typedef struct _KeywordXlateList
{
    KeywordXlate entry;
    struct _KeywordXlateList *next;
} KeywordXlateList;


/* preprocessor data struct */
typedef struct _PreprocessKeywordNode
{
    char *keyword;
    void (*func)(char *);

} PreprocessKeywordNode;




typedef struct _PreprocessKeywordList
{
    PreprocessKeywordNode entry;
    struct _PreprocessKeywordList *next;

} PreprocessKeywordList;




typedef struct _PreprocessFuncNode
{
    void (*func)(Packet *);
    struct _PreprocessFuncNode *next;

} PreprocessFuncNode;

typedef struct _PluginSignalFuncNode
{
    void (*func)(int, void*);
    void *arg;
    struct _PluginSignalFuncNode *next;

} PluginSignalFuncNode;

/*
 * Output data struct 
 */
typedef struct _OutputKeywordNode
{
    char *keyword;
    char node_type;
    void (*func)(char *);

} OutputKeywordNode;



typedef struct _OutputKeywordList
{
    OutputKeywordNode entry;
    struct _OutputKeywordList *next;

} OutputKeywordList;


typedef struct _OutputFuncNode
{
    void (*func)(Packet *, char *, void *);
    void *arg;
    struct _OutputFuncNode *next;

} OutputFuncNode;



void InitPlugIns();
void InitPreprocessors();
void InitOutputPlugins();
void RegisterPlugin(char *, void (*func)(char *, OptTreeNode *, int));
void DumpPlugIns();
void RegisterPreprocessor(char *, void (*func)(u_char *));
void DumpPreprocessors();
void RegisterOutputPlugin(char *, int, void (*func)(u_char *));
void DumpOutputPlugins();
int PacketIsIP(Packet *);
int PacketIsTCP(Packet *);
int PacketIsUDP(Packet *);
int PacketIsICMP(Packet *);
int DestinationIpIsHomenet(Packet *);
int SourceIpIsHomenet(Packet *);
int IsTcpSessionTraffic(Packet *);
int CheckNet(struct in_addr *, struct in_addr *);
void AddFuncToRestartList(void (*func)(int, void*), void*);
void AddFuncToCleanExitList(void (*func)(int, void*), void*);
PluginSignalFuncNode *AddFuncToSignalList(void (*func)(int, void*), void*, PluginSignalFuncNode *);

#define ENCODING_HEX 0
#define ENCODING_BASE64 1
#define ENCODING_ASCII 2
#define DETAIL_FAST  0 
#define DETAIL_FULL  1

char *GetUniqueName(char *);
char *GetIP(char *);
char *GetHostname();
int GetLocalTimezone();

/***********************************************************
 If you use any of the functions in this section, you need 
 to call free() on the char * that is returned after you are 
 done using it. Otherwise, you will have created a memory 
 leak.
***********************************************************/
char *TCPOptionCode(Options *);
char *TCPOptionValue(Options *);
char *IPOptionCode(Options *);
char *IPOptionValue(Options *);

char *GetTimestamp(time_t *, int);
char *GetCurrentTimestamp();
char *base64(u_char *, int);
char *ascii(u_char *, int);
char *hex(u_char *, int);
char *int2s(int);
char *hex2s(int);
char *str2s(char *);
/**********************************************************/

#endif /* __PLUGBASE_H__ */
