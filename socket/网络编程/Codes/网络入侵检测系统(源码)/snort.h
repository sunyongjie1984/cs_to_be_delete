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

/* $Id: snort.h,v 1.19 2001/01/04 11:33:41 fygrave Exp $ */

#ifndef __SNORT_H__
#define __SNORT_H__

#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif

/*  I N C L U D E S  **********************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <pcap.h>
#include <net/bpf.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifndef WIN32
	#include <strings.h>
	#include <netdb.h>
	#include <errno.h>
	#include <time.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/un.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
#endif
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <rpc/rpc_msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef HAVE_SYS_SOCKIO_H
    #include <sys/sockio.h>
#endif
#include <fcntl.h>
#include <signal.h>
#include <math.h>
#include <ctype.h>
#include <pcap-namedb.h>
/*#include <db.h>*/
#ifndef WIN32
	#include <syslog.h>
	#include <netdb.h>
	#include <pwd.h>
	#include <grp.h>
#else
	#include "syslog.h"
#endif

#ifdef HAVE_PATHS_H
    #include <paths.h>
#endif

#ifdef USE_PTHREADS
    #include <pthread.h>
#endif

/* This is basically everything needed to make snort work under WIN32. -- Mike Davis */
#ifdef WIN32
	#include <winsock.h>
	#include <windows.h>
	#include <io.h>
	#include <sys/timeb.h>
	#include <process.h>
	#include <direct.h>
	#include <getopt.h>
	typedef unsigned char  u_int8_t;
	typedef unsigned short u_int16_t;
	typedef unsigned int   u_int32_t;
	typedef int	pid_t;

	#undef TCP_NODELAY
	#undef interface
	#define SIGKILL         9       /* kill (cannot be caught or ignored) */
	#define SIGQUIT         3       /* quit */
	#define SIGHUP          1       /* hangup */
	#define SIGUSR1 30      /* user defined signal 1 */
	#define SIGPIPE 13      /* write on a pipe with no one to read it */
	#define EEXIST          17              /* File exists */
	#define W_OK            0x02    /* test for write permission */
	#define S_ISDIR(x)      (((x) & 0170000) == 0040000)    /* directory */
	#define S_IRWXU         0000700                 /* RWX mask for owner */
	#define S_IRWXG         0000070                 /* RWX mask for group */
	#define S_IROTH         0000004                 /* R for other */
	#define S_IXOTH         0000001                 /* X for other */
	#define strncasecmp strnicmp
	#define strcasecmp stricmp
	#define snprintf _snprintf
	#define vsnprintf _vsnprintf
	#define bzero(x, y) memset((x), 0, (y))
	#define execv _execv
	#define getpid _getpid
	#define index strchr
	#define bcopy(x, y, z) memcpy((void *)x, (const void *)y, (size_t) z)
	#define mkdir(x, y) _mkdir(x)
	#define IXDR_GET_LONG(buf)                ((long)ntohl((u_long)*(buf)++))
	#define IXDR_GET_ENUM(buf, t)             ((t)IXDR_GET_LONG(buf))
	#define RPC_MSG_VERSION         ((u_long) 2)

	/*
	 * Definitions for UNIX IPC domain.
	 */
	struct  sockaddr_un {
			u_char  sun_len;                /* sockaddr len including null */
			u_char  sun_family;             /* AF_UNIX */
			char    sun_path[104];          /* path name (gag) */
	};

	struct timezone {
			int     tz_minuteswest; /* minutes west of Greenwich */
			int     tz_dsttime;     /* type of dst correction */
	};

	/*
	 * Interface request structure used for socket
	 * ioctl's.  All interface ioctl's must have parameter
	 * definitions which begin with ifr_name.  The
	 * remainder may be interface specific.
	 */
	struct  ifreq {
			char    ifr_name[128];             /* if name, e.g. "en0" */
			union {
					struct  sockaddr ifru_addr;
					struct  sockaddr ifru_dstaddr;
					struct  sockaddr ifru_broadaddr;
					short   ifru_flags;
					int     ifru_metric;
					caddr_t ifru_data;
			} ifr_ifru;
	#define ifr_addr        ifr_ifru.ifru_addr      /* address */
	#define ifr_dstaddr     ifr_ifru.ifru_dstaddr   /* other end of p-to-p link */
	#define ifr_broadaddr   ifr_ifru.ifru_broadaddr /* broadcast address */
	#define ifr_flags       ifr_ifru.ifru_flags     /* flags */
	#define ifr_metric      ifr_ifru.ifru_metric    /* metric */
	#define ifr_mtu         ifr_ifru.ifru_metric    /* mtu (overload) */
	#define ifr_media       ifr_ifru.ifru_metric    /* media options (overload) */
	#define ifr_data        ifr_ifru.ifru_data      /* for use by interface */
	};

	int gettimeofday(struct timeval *,struct timezone *);
	void *GetAdapterFromList(void *, int);
	char *print_interface(char *);
	void PrintDeviceList(const char *);
	int init_winsock(void);
	int geteuid(void);
#endif

#include "decode.h"
#include "plugbase.h"
#include "rules.h"
#include "log.h"
#include "mstring.h"
#include "parser.h"
#include "checksum.h"

#ifndef HAVE_SNPRINTF
    #include "snprintf.h"
#endif

#ifdef HAVE_CONFIG_H 
/* otherwise it will cause errors */
    #include "prototypes.h"
#endif


/*  D E F I N E S  ************************************************************/
#define STD_BUF  1024

#define RF_ANY_SIP    0x01
#define RF_ANY_DIP    0x02
#define RF_ANY_SP     0x04
#define RF_ANY_DP     0x10
#define RF_ANY_FLAGS  0x20

/*
 * you may need to ajust this on the systems which don't have standard
 * paths defined
 */
#ifndef _PATH_VARRUN
char _PATH_VARRUN[STD_BUF];
#endif

#ifdef WIN32
	#define DEFAULT_LOG_DIR   "log"
	#define DEFAULT_DAEMON_ALERT_FILE  "log/alert.ids"
	#define UNSOCK_FILE       "snort_alert"
#else
	#define DEFAULT_LOG_DIR   "/var/log/snort"
	#define DEFAULT_DAEMON_ALERT_FILE  "alert"
	#define UNSOCK_FILE       "/dev/snort_alert"
#endif

/* you can redefine the user ID which is allowed to
 * initialize interfaces using pcap and read from them
 */
#ifndef SNIFFUSER
    #define SNIFFUSER 0
#endif

#define MAX_INTERFACES	10

#define ALERT_FULL     0x01
#define ALERT_FAST     0x02
#define ALERT_NONE     0x03
#define ALERT_UNSOCK   0x04

/*  D A T A  S T R U C T U R E S  *********************************************/
/* struct to contain the program variables and command line args */
typedef struct _progvars
{
    int alert_interface_flag;
    int verbose_bytedump_flag;
    int obfuscation_flag;
    int log_cmd_override;
    int alert_cmd_override;
    int char_data_flag;
    int data_flag;
    int verbose_flag;
    int showarp_flag;
    int showipv6_flag;
    int showipx_flag;
    int readmode_flag;
    int logbin_flag;
    int log_flag;
    int nolog_flag;
    int show2hdr_flag;
    int syslog_flag;
#ifdef WIN32
	int syslog_remote_flag;
	char syslog_server[STD_BUF];
	int syslog_server_port;
#endif
    int promisc_flag;
    int rules_order_flag;
    int smbmsg_flag;
    int track_flag;
    int daemon_flag;
    int quiet_flag;
    int pkt_cnt;
    int pkt_snaplen;
    u_long homenet;
    u_long netmask;
    int use_rules;
    int alert_mode;
    int log_plugin_active;
    int alert_plugin_active;
    char pid_filename[STD_BUF];
    char config_file[STD_BUF];
    char log_dir[STD_BUF];
    char readfile[STD_BUF];
    char smbmsg_dir[STD_BUF];
    char pid_path[STD_BUF];
    char *interfaces[MAX_INTERFACES]; 
    int   mtus[MAX_INTERFACES];
#define interface interfaces[0] /* backwards compatibility */
    char *pcap_cmd;
    char *alert_filename;
    char *binLogFile;
    int use_utc;
} PV;

/* struct to collect packet statistics */
typedef struct _PacketCount
{
    u_long other;
    u_long tcp;
    u_long udp;
    u_long icmp;
    u_long arp;
    u_long ipv6;
    u_long ipx;
    u_long discards;
    u_long alert_pkts;
    u_long log_pkts;
    u_long pass_pkts;

    u_long frags;           /* number of frags that have come in */
    u_long rebuilt_frags;   /* number of packets rebuilt */
    u_long frag_incomp;     /* number of frags cleared due to memory issues */
    u_long frag_timeout;    /* number of frags cleared due to timeout */
    u_long rebuild_element; /* frags that were element of rebuilt pkt */

    u_long tcp_stream_pkts; /* number of packets tcp reassembly touches */
    u_long rebuilt_tcp;     /* number of phoney tcp packets generated */
    u_long tcp_streams;     /* number of tcp streams created */
} PacketCount;

/*  G L O B A L S  ************************************************************/
PV pv;                 /* program vars (command line args) */
int datalinks[MAX_INTERFACES];          /* the datalink value */
#define datalink datalinks[0]
int ifr_count;         /* number of interfaces to monitor */
char *progname;        /* name of the program (from argv[0]) */
char **progargs;
char *username;
char *groupname;
char *chrootdir;
unsigned long userid;
unsigned long groupid;
struct passwd *pw;
struct group *gr;
char *pcap_cmd;        /* the BPF command string */
char *pktidx;          /* index ptr for the current packet */
pcap_t *pds[MAX_INTERFACES]; /* array of packet descriptors per interface */

#define pd pds[0]

/* backwards compatibility */
pcap_dumper_t *dumpd;  /* the pcap dumper descriptor */
FILE *log_ptr;         /* log file ptr */
FILE *alert;           /* alert file ptr */
FILE *binlog_ptr;      /* binary log file ptr */
int flow;              /* flow var (probably obsolete) */
int thiszone;          /* time zone info */
PacketCount pc;        /* packet count information */
u_long netmasks[33];   /* precalculated netmask array */
struct pcap_pkthdr *g_pkthdr; /* packet header ptr */
u_char *g_pkt;         /* ptr to the packet data */
u_long g_caplen;       /* length of the current packet */
char *protocol_names[256];
u_int snaplen;
int alertsd;           /* socket descriptor for unix-socket logging */
struct sockaddr_un alertaddr; /* where we send all alert packets */


#ifdef USE_PTHREADS
pthread_mutex_t pt_lock;
pthread_t pt[MAX_INTERFACES];
#endif

typedef void (*grinder_t)(Packet *, struct pcap_pkthdr *, u_char *);  /* ptr to the packet processor */

grinder_t grinders[MAX_INTERFACES];
#define grinder grinders[0]

/*  P R O T O T Y P E S  ******************************************************/
int ParseCmdLine(int, char**);
void InitializeInterfaces(void);
void *InterfaceThread(void *);
int OpenPcap(char *, int);
int GetIfrMTU(char *);
void DefineIfaceVar(char *,u_char *, u_char *);
int DisplayBanner();
int SetPktProcessor();
void SetPktProcessors();
void GetTime(char *);
int gmt2local(time_t);
void ts_print(register const struct timeval *, char *);
void CleanExit(int);
void exit_or_exec(int, int);
char *copy_argv(char **);
int strip(char *);
int ShowUsage(char *);
float CalcPct(float, float);
void ReadPacketsFromFile();
void GenHomenet(char *);
void InitNetmasks();
void InitBinFrag();
void GoDaemon();
void SanityChecks();
char *read_infile(char *);
void InitProtoNames();
void ProcessPacket(char *, struct pcap_pkthdr *, u_char *);
void PrintError(char *);
void ErrorMessage(const char *, ...);
void LogMessage(const char *, ...);
void FatalError(const char *, ...);
void FatalPrintError(char *);
void CreatePidFile(char *);
void SetUidGid(void);
void DropStats(int);

#endif  /* __SNORT_H__ */
