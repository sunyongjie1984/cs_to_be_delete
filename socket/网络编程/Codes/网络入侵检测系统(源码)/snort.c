/* $Id: snort.c,v 1.52 2001/01/26 16:40:44 roesch Exp $ */
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

/*
 *
 * Program: Snort
 *
 * Purpose: Check out the README file for info on what you can do
 *          with Snort.
 *
 * Author: Martin Roesch (roesch@clark.net)
 *
 * Comments: Ideas and code stolen liberally from Mike Borella's IP Grab
 *           program. Check out his stuff at http://www.borella.net.  I
 *           also have ripped some util functions from TCPdump, plus Mike's
 *           prog is derived from it as well.  All hail TCPdump....
 *
 * HP-UX 10.x note from Chris Sylvain:
 * if you run snort and receive the error message
 *  "ERROR: OpenPcap() device lan0 open:
 *                    recv_ack: promisc_phys: Invalid argument"
 * it's because there's another program running using the DLPI service.
 * The HP-UX implementation doesn't allow more than one libpcap program
 * at a time to run, unlike Linux.
 *
 */

/*  I N C L U D E S  **********************************************************/
#include "snort.h"

/*  G L O B A L S  ************************************************************/
extern OutputFuncNode *AlertList;
extern OutputFuncNode *LogList;
/*extern char *malloc_options;*/

/*
 *
 * Function: main(int, char *)
 *
 * Purpose:  Handle program entry and exit, call main prog sections
 *
 * Arguments: See command line args in README file
 *
 * Returns: 0 => normal exit, 1 => exit on error
 *
 */
int main(int argc, char *argv[])
{
#ifdef USE_PTHREADS
    int i;

#endif
#ifndef WIN32
	#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD) || defined(SOLARIS)
		sigset_t set;

		sigemptyset(&set);
		sigprocmask(SIG_SETMASK, &set, NULL);
	#else
		sigsetmask(0);
	#endif
#endif
/*    malloc_options = "AX";*/

    /* make this prog behave nicely when signals come along */
    signal(SIGKILL, CleanExit);
    signal(SIGTERM, CleanExit);
    signal(SIGINT, CleanExit);
    signal(SIGQUIT, CleanExit);
    signal(SIGHUP, CleanExit);
    signal(SIGUSR1, DropStats);

    /* sane permissions */
    umask(077);

    /*
     * set a global ptr to the program name so other functions can tell what
     * the program name is
     */
    progname = argv[0];
    progargs = argv;

#ifdef WIN32
	if (!init_winsock())
		FatalError("[!] ERROR: Could not Initialize Winsock!\n");
#endif

    /*
     * setup some lookup data structs
     */
    InitNetmasks();
    InitProtoNames();

    /* initialize the packet counter to loop forever */
    pv.pkt_cnt = -1;

    /* set the alert filename to NULL */
    pv.alert_filename = NULL;

    /* set the default alert mode */
    pv.alert_mode = ALERT_FULL;
    pv.use_utc = 0;

    /*
     * provide (limited) status messages by default
     */
    pv.quiet_flag = 0;

    ifr_count = 0;

#ifdef USE_PTHREADS
    pt_lock = PTHREAD_MUTEX_INITIALIZER;
#endif

    /* chew up the command line */
    ParseCmdLine(argc, argv);

    if(pv.use_utc == 1)
    {
        thiszone = 0;
    }
    else
    {
        /* set the timezone (ripped from tcpdump) */
        thiszone = gmt2local(0);
    }

    /*
     * make sure we've got the privs to continue
     */
    if(!pv.readmode_flag && geteuid() != SNIFFUSER)
    {
        DisplayBanner();
        ShowUsage(progname);
        printf("\n\nDude, you need root priveleges to run Snort in this mode!\n\n");
        exit(1);
    }
    if(!pv.quiet_flag)
    {
        printf("\n        --== Initializing Snort ==--\n");
    }
    /* if the logging flag hasn't been set yet... */
    if(!pv.log_flag)
    {
        /* ...set the default logging dir */
        strncpy(pv.log_dir, DEFAULT_LOG_DIR, strlen(DEFAULT_LOG_DIR) + 1);
    }
    if(pv.use_rules || pv.log_flag || pv.daemon_flag)
    {
        /* perform some sanity checks on the output directory, etc */
        /* first perform some sanity checks on the output directory, etc ... */
        SanityChecks();

        /* ... then create a PID file if not reading from a file */
        if (!pv.readmode_flag && pv.daemon_flag)
#ifdef WIN32
	    CreatePidFile("WIN32");
#else
            CreatePidFile(pv.interfaces[0]);
#endif
    }
    if(pv.use_rules && pv.rules_order_flag)
    {
        if(!pv.quiet_flag)
        {
            printf("Rule application order changed to Pass->Alert->Log\n");
        }
    }
    /*
     * we're not using rules, sniffing to the screen, or logging packets so
     * we don't really need to run...
     */
    if(!pv.use_rules && !pv.verbose_flag && !pv.log_flag)
    {
        /*
         * give them a nice little reminder that Snort needs to be told what
         * to do
         */
        DisplayBanner();
        ShowUsage(progname);
        PrintError("\n\nUh, you need to tell me to do something....\n\n");
        exit(0);
    }
    /*
     * if daemon mode requested, fork daemon first, otherwise on linux
     * interface will be reset.
     */
    if(pv.daemon_flag)
    {
#ifdef DEBUG
        printf("Entering daemon mode\n");
#endif
        GoDaemon();
    }
    /*
     * if no interfaces were specified we would need one anyway
     */
    if(!ifr_count)
        ifr_count++;

    /*
     * if we're not reading packets from a file, open the network interface
     * for reading
     */
    if(!pv.readmode_flag)
    {
#ifdef DEBUG
#ifdef WIN32
		printf("Opening interface: %s\n", print_interface(pv.interfaces[0]));
#else
        printf("Opening interface: %s\n", pv.interfaces[0]);
#endif
#endif
        /* open up our libpcap packet capture interface */
        InitializeInterfaces();
    }
    else
    {
#ifdef DEBUG
        printf("Opening file: %s\n", pv.readfile);
#endif

        /* open the packet file for readback */
        OpenPcap(pv.readfile, 0);
    }

    /*
     * creating a PID file before setting its proper
     * path (in SanityChecks()) is not a good idea
     */
    if((!(pv.use_rules || pv.log_flag) || pv.daemon_flag) && !pv.readmode_flag)
    {
#ifdef WIN32
		CreatePidFile("WIN32");
#else
        CreatePidFile(pv.interfaces[0]);
#endif
    }

#ifndef WIN32
    /* Don't need root privelege anymore, so lets drop ownership
     * and chroot if requested....
     */

    if(chrootdir != NULL)
    {
        if(chdir(chrootdir) < 0)
            FatalError("Can not chdir to \"%s\"\n", chrootdir);
        if(chroot(chrootdir) < 0)
            FatalError("Can not chroot to %s\n", chrootdir);
        if(chdir("/") < 0)
            FatalError("Can not chdir to \"/\"\n");

        chrootdir = NULL;        /* we don't need chrootdir anymore so all
                                 * other routines should use fullpath. */
    }
    /* set safe userID/groupID if needed */
    SetUidGid();
#endif
#ifdef DEBUG
    printf("Setting Packet Processor\n");
#endif

    /* set the packet processor (ethernet, slip, t/r, etc ) */
    SetPktProcessors();

    /* if we're using the rules system, it gets initialized here */
    if(pv.use_rules)
    {
        /* initialize all the plugin modules */
        InitPreprocessors();
        InitPlugIns();
        InitOutputPlugins();

#ifdef DEBUG
        DumpPreprocessors();
        DumpPlugIns();
        DumpOutputPlugins();
#endif

        /* setup the default rule action anchor points */
        CreateDefaultRules();

        if(pv.rules_order_flag)
        {
            OrderRuleLists("pass alert log");
        }
        ParseRulesFile(pv.config_file, 0);

        if(!pv.quiet_flag)
        {
            printRuleOrder();
        }
    }
    if(!pv.quiet_flag)
    {
        printf("\n        --== Initialization Complete ==--\n");
    }
    /* Tell 'em who wrote it, and what "it" is */
    if(!pv.quiet_flag)
        DisplayBanner();

    if(pv.alert_cmd_override)
    {
        /*
         * if a command line alert override has been specified, setup the
         * appropriate function pointer
         */

        /*
         * if we're using syslog alerting set the alert function pointer to
         * the syslog alerting function
         */
        if(pv.syslog_flag)
        {
            AddFuncToOutputList(SyslogAlert, NT_OUTPUT_ALERT, NULL);
            openlog("snort", LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_AUTH);
        }
        else if(pv.smbmsg_flag)
        {
#ifdef ENABLE_SMB_ALERTS
            AddFuncToOutputList(SmbAlert, NT_OUTPUT_ALERT, NULL);
#else
            FatalError("[!] ERROR: SMB support not compiled into program, exiting...\n");
#endif
        }
        else
        {
            switch(pv.alert_mode)
            {
                case ALERT_FAST:
                    alert = OpenAlertFile(pv.alert_filename);
                    AddFuncToOutputList(FastAlert, NT_OUTPUT_ALERT, NULL);
                    break;

                case ALERT_FULL:
                    alert = OpenAlertFile(pv.alert_filename);
                    AddFuncToOutputList(FullAlert, NT_OUTPUT_ALERT, NULL);
                    break;

                case ALERT_NONE:
                    SetOutputList(NoAlert, NT_OUTPUT_ALERT, NULL);

                    break;

                case ALERT_UNSOCK:
                    AddFuncToOutputList(SpoAlertUnixSock, NT_OUTPUT_ALERT, NULL);
                    OpenAlertSock();

                    break;
            }
        }
    }
    /* set the default alert function (alert full) */
    if(AlertList == NULL && pv.use_rules == 1)
    {
        alert = OpenAlertFile(pv.alert_filename);
        AddFuncToOutputList(FullAlert, NT_OUTPUT_ALERT, NULL);
    }
    /* set the alert function pointer list to call all the output plugins */
    AlertFunc = CallAlertPlugins;

    if(pv.log_cmd_override)
    {
        /* logging to a tcpdump file, initialize the output file and pointer */
        if(pv.logbin_flag)
        {
#ifdef DEBUG
            printf("Initializing output file\n");
#endif
            InitBinLogFile(pv.binLogFile);

            AddFuncToOutputList(LogBin, NT_OUTPUT_LOG, NULL);
        }
        else
        {                        /* if we're not logging in tcpdump format...
                                 * set the logging function pointer */
            if(!pv.nolog_flag)
                AddFuncToOutputList(LogPkt, NT_OUTPUT_LOG, NULL);
            else
                SetOutputList(NoLog, NT_OUTPUT_LOG, NULL);
        }
    }
    if(LogList == NULL)
    {
        AddFuncToOutputList(LogPkt, NT_OUTPUT_LOG, NULL);
    }
    LogFunc = CallLogPlugins;


#ifdef DEBUG
    printf("Entering pcap loop\n");
#endif

#ifdef USE_PTHREADS
    /*
     * With pthreads each interface gets a thread of its own.
     * 
     */
    for(i = 0; i < ifr_count; i++)
    {
        pthread_create(&pt[i], NULL, InterfaceThread, NULL);
    }

    while(1)
    {
        sleep(10);
    }

#else
    /* Without pthreads one interface goes in main thread */
    InterfaceThread(NULL);
#endif

    return 0;
}




void ProcessPacket(char *user, struct pcap_pkthdr * pkthdr, u_char * pkt)
{
    Packet p;

#ifdef USE_PTHREADS
    pthread_mutex_lock(&pt_lock);
#endif
    /* call the packet decoder */
    (*grinder) (&p, pkthdr, pkt);

    /* print the packet to the screen */
    if(pv.verbose_flag)
    {
        if(p.iph != NULL)
        {
            PrintIPPkt(stdout, p.iph->ip_proto, &p);
        }
        else if(p.ah != NULL)
        {
            PrintArpHeader(stdout, &p);

            if(pv.log_flag)
            {
                LogArpPkt(&p);
            }
        }
    }
    /* check or log the packet as necessary */
    if(!pv.use_rules)
    {
        if(pv.log_flag)
        {
            if(pv.logbin_flag)
            {
                LogBin(&p, NULL, NULL);
            }
            else
            {
                if(p.iph != NULL)
                    LogPkt(&p, NULL, NULL);

                if(p.ah != NULL)
                {
                    if(!pv.nolog_flag)
                    {
                        OpenLogFile(ARP, &p);

                        PrintArpHeader(log_ptr, &p);

                        fclose(log_ptr);
                    }
                }
            }
        }
    }
    else
    {
        Preprocess(&p);
    }

    ClearDumpBuf();

#ifdef USE_PTHREADS
    pthread_mutex_unlock(&pt_lock);
#endif
}


/*
 * Function: ShowUsage(char *)
 *
 * Purpose:  Display the program options and exit
 *
 * Arguments: progname => name of the program (argv[0])
 *
 * Returns: 0 => success
 */
int ShowUsage(char *progname)
{
    fprintf(stderr, "USAGE: %s [-options] <filter options>\n", progname);
    fputs("Options:\n", stderr);
    fputs("        -A         Set alert mode: fast, full, or none "
          " (alert file alerts only)"
#ifdef WIN32
		  "\n                  \"unsock\" enables UNIX socket logging (experimental). *\n", stderr);
#else
          "\n                  \"unsock\" enables UNIX socket logging (experimental).\n", stderr);
#endif
    fputs("        -a         Display ARP packets\n", stderr);
    fputs("        -b         Log packets in tcpdump format (much faster!)\n", stderr);
    fputs("        -c <rules> Use Rules File <rules>\n", stderr);
    fputs("        -C         Print out payloads with character data only (no hex)\n", stderr);
    fputs("        -d         Dump the Application Layer\n", stderr);
    fputs("        -D         Run Snort in background (daemon) mode\n", stderr);
    fputs("        -e         Display the second layer header info\n", stderr);
#ifdef WIN32
	fputs("        -E         Log alert messages to NT Eventlog.\n", stderr);
#endif
    fputs("        -F <bpf>   Read BPF filters from file <bpf>\n", stderr);
#ifdef WIN32
	fputs("        -g <gname> Run snort gid as `gname' user or uid after initialization *\n", stderr);
#else
    fputs("        -g <gname> Run snort gid as <gname> group (or gid) after initialization\n", stderr);
#endif
    fputs("        -h <hn>    Home network = <hn>\n", stderr);
    fputs("        -i <if>    Listen on interface <if>\n", stderr);
    fputs("        -I         Add Interface name to alert output\n", stderr);
    fputs("        -l <ld>    Log to directory <ld>\n", stderr);
#ifdef ENABLE_SMB_ALERTS
    fputs("        -M <wrkst> Sends SMB message to workstations in file <wrkst>\n", stderr);
    fputs("                   (Requires smbclient to be in PATH)\n", stderr);
#endif
    fputs("        -n <cnt>   Exit after receiving <cnt> packets\n", stderr);
    fputs("        -N         Turn off logging (alerts still work)\n", stderr);
    fputs("        -o         Change the rule testing order to Pass|Alert|Log\n", stderr);
    fputs("        -O         Obfuscate the logged IP addresses\n", stderr);
    fputs("        -p         Disable promiscuous mode sniffing\n", stderr);
    fprintf(stderr, "        -P <snap>  set explicit snaplen of packet (default: %d)\n",
            SNAPLEN);
    fputs("        -q         Quiet. Don't show banner and status report\n", stderr);
    fputs("        -r <tf>    Read and process tcpdump file <tf>\n", stderr);
#ifdef WIN32
	fputs("        -s <server:port> Log alert messages to syslog server (default port: 514)", stderr);
#else
    fputs("        -s         Log alert messages to syslog\n", stderr);
#endif
    fputs("        -S <n=v>   Set rules file variable n equal to value v\n", stderr);
    fputs("        -t <dir>   Chroots process to <dir> after initialization\n", stderr);
    fputs("        -u <uname> Run snort uid as <uname> user (or uid) after initialization\n", stderr);
    fputs("        -U         Use UTC for timestamps\n", stderr);
    fputs("        -v         Be verbose\n", stderr);
#ifdef WIN32
	fputs("        -W         Lists available interfaces.\n", stderr);
#endif
    fputs("        -V         Show version number\n", stderr);
    fputs("        -X         Dump the raw packet data starting at the link layer\n", stderr);
/* Nobody really uses this, do they?
    fputs( "        -6         Display IPv6 packets\n", stderr);
    fputs( "        -x         Display IPX packets\n", stderr);
*/
    fputs("        -?         Show this information\n", stderr);
    fputs("<Filter Options> are standard BPF options, as seen in TCPDump\n", stderr);
#ifdef WIN32
	fputs("\n* denotes an option that is NOT SUPPORTED in this WIN32 port of snort.", stderr);
#endif
    return 0;
}



/*
 * Function: ParseCmdLine(int, char *)
 *
 * Purpose:  Parse command line args
 *
 * Arguments: argc => count of arguments passed to the routine
 *            argv => 2-D character array, contains list of command line args
 *
 * Returns: 0 => success, 1 => exit on error
 */
extern char *optarg;                /* for getopt */
extern int optind;                /* for getopt */

int ParseCmdLine(int argc, char *argv[])
{
    int ch;                        /* storage var for getopt info */
    int read_bpf = 0;
    char bpf_file[STD_BUF];
    char *eq_n;
    char *eq_p;
    char errorbuf[PCAP_ERRBUF_SIZE];
#ifdef WIN32
	char *devicet;
	int adaplen;
	char **toks;
	int num_toks;
#endif

#ifdef DEBUG
    printf("Parsing command line...\n");
#endif
    /* generally speaking, Snort works best when it's in promiscuous mode */
    pv.promisc_flag = 1;

    /* just to be sane.. */
    username = NULL;
    groupname = NULL;
    chrootdir = NULL;

    /* loop through each command line var and process it */
    while((ch = getopt(argc, argv,
#ifdef WIN32
					   "XL:IOCWqS:pNA:F:DM:br:xeh:l:dc:n:P:i:vV?aEo6u:g:s:t:U")) != -1)
#else
                       "XL:IOCqS:pNA:F:DM:br:xeh:l:dc:n:P:i:vV?aso6u:g:t:U")) != -1)
#endif
    {
#ifdef DEBUG
        printf("Processing cmd line switch: %c\n", ch);
#endif
        switch(ch)
        {
            case 'a':                /* show ARP packets */
#ifdef DEBUG
                printf("Show ARP active\n");
#endif
                pv.showarp_flag = 1;

                break;

            case 'A':                /* alert mode */
                if(!strncasecmp(optarg, "none", 4))
                {
                    pv.alert_mode = ALERT_NONE;
                }
                else if(!strncasecmp(optarg, "full", 4))
                {
                    pv.alert_mode = ALERT_FULL;
                }
                else if(!strncasecmp(optarg, "fast", 4))
                {
                    pv.alert_mode = ALERT_FAST;
                }
                else if(!strncasecmp(optarg, "unsock", 4))
                {
                    pv.alert_mode = ALERT_UNSOCK;
                }
                else
                {
                    FatalError("ERROR => Unknown command line alert option: %s\n", optarg);
                }

                pv.alert_cmd_override = 1;

                break;

            case 'b':                /* log packets in binary format for
                                     * post-processing */
#ifdef DEBUG
                printf("Tcpdump logging mode active\n");
#endif
                pv.logbin_flag = 1;
                pv.log_cmd_override = 1;

                break;

            case 'c':                /* use configuration file x */
                strncpy(pv.config_file, optarg, STD_BUF - 1);
                pv.use_rules = 1;
#ifdef DEBUG
                printf("Config file = %s\n", pv.config_file);
#endif
                break;

            case 'C':                /* dump the application layer as text only */
                pv.char_data_flag = 1;
                break;

            case 'd':                /* dump the application layer data */
                pv.data_flag = 1;
#ifdef DEBUG
                printf("Data Flag active\n");
#endif
                break;

            case 'D':                /* daemon mode */
#ifdef DEBUG
                printf("Daemon mode flag set\n");
#endif
                pv.daemon_flag = 1;
                pv.quiet_flag = 1;
                break;

            case 'e':                /* show second level header info */
#ifdef DEBUG
                printf("Show 2nd level active\n");
#endif
                pv.show2hdr_flag = 1;

                break;
#ifdef WIN32
            case 'E': /* log alerts to Event Log */
                pv.syslog_flag = 1;
				pv.syslog_remote_flag = 0;
#ifdef DEBUG
                printf("Logging alerts to Event Log\n");
#endif
                pv.alert_cmd_override = 1;
#endif
				break;

            case 'F':                /* read BPF filter in from a file */
#ifdef DEBUG
                printf("Tcpdump logging mode active\n");
#endif
                strncpy(bpf_file, optarg, STD_BUF - 1);

                read_bpf = 1;

                break;
#ifndef WIN32
            case 'g':                /* setgid handler */
#ifdef WIN32
			   FatalError("[!] ERROR: Setting the group id is not supported in the WIN32 port of snort!\n");
#endif

                if(groupname != NULL)
                    free(groupname);
                if((groupname = calloc(strlen(optarg) + 1, 1)) == NULL)
                    FatalPrintError("malloc");

                bcopy(optarg, groupname, strlen(optarg));

                if((groupid = atoi(groupname)) == 0)
                {
                    gr = getgrnam(groupname);
                    if(gr == NULL)
                        FatalError("Group \"%s\" unknown\n", groupname);

                    groupid = gr->gr_gid;
                }
                break;
#endif
            case 'h':                /* set home network to x, this will help
                                     * determine what to set logging diectories
                                     * to */
                GenHomenet(optarg);

                break;
#ifdef WIN32
			case 'i':
          
          devicet=NULL;

          if(((adaplen = atoi(optarg)) > 0)){
			
			if ((devicet = pcap_lookupdev(errorbuf)) == NULL){
				perror(errorbuf);
				exit(-1);
            }
			
            if ((pv.interface = GetAdapterFromList(devicet, adaplen)) == NULL){
				printf("Invalid interface '%d'.", atoi(optarg));
				exit(-1);
			}

#ifdef DEBUG
			printf("Interface = %s\n", print_interface(pv.interface));
#endif
            break;
          }
		  else {
					printf("Invalid interface '%d'.", atoi(optarg));
					exit(-1);
		  }
#else      
            case 'i':                /* without PTHREADS we support only single
                                     * listen on interface x interface */
#ifndef USE_PTHREADS
                if(ifr_count)
                {
                    ErrorMessage(
                                "\nMultiple interfaces are not supported. %s is used\n"
#ifdef WIN32
								,print_interface(pv.interfaces[0]));
#else
                                ,pv.interfaces[0]);
#endif
                    break;
                }
#endif
                if(ifr_count == MAX_INTERFACES)
                {
                    ErrorMessage(
                                "\nMaximum number of interfaces (%i) exceeded."
                                "Please recompile to extend it (oops)\n",
                                MAX_INTERFACES);
                    break;
                }
                pv.interfaces[ifr_count] = (char *) malloc(strlen(optarg) + 1);
                bzero((char *) pv.interfaces[ifr_count], strlen(optarg) + 1);
                strncpy(pv.interfaces[ifr_count], optarg, strlen(optarg)+1);
                ifr_count++;
#ifdef DEBUG
                printf("Interface = %s\n", pv.interfaces[ifr_count - 1]);
#endif
                break;
#endif

            case 'I':       /* add interface name to alert string */
                pv.alert_interface_flag = 1;
                break;

            case 'l':                /* use log dir <X> */
                strncpy(pv.log_dir, optarg, STD_BUF - 1);
#ifdef DEBUG
                printf("Log directory = %s\n", pv.log_dir);
#endif
                pv.log_flag = 1;
                break;

            case 'L':              /* set BinLogFile name */
			                       /* implies tcpdump format logging */
                if (strlen(optarg) < 256)
                {
                     pv.binLogFile = strdup(optarg);
			         pv.logbin_flag = 1;
			         pv.log_cmd_override = 1;
                }
                else
                {
                     FatalError("ERROR =>ParseCmdLine, log file: %s, > than 256 characters\n",
			                     optarg);
                }
                break;

            case 'M':                /* SMB Message Option */

                pv.smbmsg_flag = 1;
                strncpy(pv.smbmsg_dir, optarg, STD_BUF - 1);
                pv.alert_cmd_override = 1;

                break;

            case 'n':                /* grab x packets and exit */
                pv.pkt_cnt = atoi(optarg);
#ifdef DEBUG
                printf("Exiting after %d packets\n", pv.pkt_cnt);
#endif
                break;

            case 'N':                /* no logging mode */
#ifdef DEBUG
                printf("Logging deactivated\n");
#endif

                pv.nolog_flag = 1;
                pv.log_cmd_override = 1;

                break;

            case 'o':                /* change the rules processing order to
                                     * passlist first */
                pv.rules_order_flag = 1;
#ifdef DEBUG
                printf("Rule application order changed to Pass->Alert->Log\n");
#endif
                break;

            case 'O':                /* obfuscate the logged IP addresses for
                                     * privacy */
                pv.obfuscation_flag = 1;

                break;

            case 'p':                /* disable explicit promiscuous mode */
                pv.promisc_flag = 0;
#ifdef DEBUG
                printf("Promiscuous mode disabled!\n");
#endif
                break;

            case 'P':                /* explicitly define snaplength of packets */
                pv.pkt_snaplen = atoi(optarg);
#ifdef DEBUG
                printf("Snaplength of Packets set to: %d\n", pv.pkt_snaplen);
#endif
                break;

            case 'q':                /* no stdout output mode */
                pv.quiet_flag = 1;
                break;

            case 'r':                /* read packets from a TCPdump file instead
                                     * of the net */
                strncpy(pv.readfile, optarg, STD_BUF - 1);
                pv.readmode_flag = 1;

                break;

            case 's':                /* log alerts to syslog */
                pv.syslog_flag = 1;
#ifdef DEBUG
                printf("Logging alerts to syslog\n");
#endif
                pv.alert_cmd_override = 1;
#ifdef WIN32
				pv.syslog_remote_flag = 1;
				toks = mSplit(optarg, ":", 2, &num_toks, 0);
				strncpy(pv.syslog_server, toks[0], STD_BUF-1);
				pv.syslog_server_port = (num_toks == 1) ? 514 : atoi(toks[1]);
#ifdef DEBUG
				printf("Logging alerts to syslog server %s on port %d\n", pv.syslog_server, pv.syslog_server_port);
#endif
#endif
                break;

            case 'S':                /* set a rules file variable */
                if((eq_p = strchr(optarg, '=')) != NULL)
                {
                    struct VarEntry *p;
                    eq_n = (char *) malloc(eq_p - optarg + 1);
                    bzero(eq_n, eq_p - optarg + 1);
                    strncpy(eq_n, optarg, eq_p - optarg);
                    p = VarDefine(eq_n, eq_p + 1);
                    p->flags |= VAR_STATIC;
                    free(eq_n);
                }
                break;

            case 't':
#ifdef WIN32
				FatalError("[!] ERROR: Setting the chroot directory is not supported in the WIN32 port of snort!\n");
#endif

                if((chrootdir = calloc(strlen(optarg) + 2, 1)) == NULL)
                    FatalPrintError("malloc");

                /* make sure '/' is appended */
                sprintf(chrootdir, "%s/", optarg);
                break;
#ifndef WIN32
            case 'u':
#ifdef WIN32
	FatalError("[!] ERROR: Setting the user id is not supported in the WIN32 port of snort!\n");
#endif

                if((username = calloc(strlen(optarg) + 1, 1)) == NULL)
                    FatalPrintError("malloc");

                bcopy(optarg, username, strlen(optarg));

                if((userid = atoi(username)) == 0)
                {
                    pw = getpwnam(username);
                    if(pw == NULL)
                        FatalError("User \"%s\" unknown\n", username);

                    userid = pw->pw_uid;
                }
                else
                {
                    pw = getpwuid(userid);
                    if(pw == NULL)
                        FatalError(
                                  "Can not obtain username for uid: %lu\n",
                                  (u_long) userid);
                }

                if(groupname == NULL)
                {
                    char name[256];

                    snprintf(name, 255, "%lu", (u_long) pw->pw_gid);

                    if((groupname = calloc(strlen(name) + 1, 1)) == NULL)
                    {
                        FatalPrintError("malloc");
                    }
                    groupid = pw->pw_gid;
                }
#if DEBUG
                printf("UserID: %lu GroupID: %lu\n",
                       (unsigned long) userid, (unsigned long) groupid);
#endif
                break;
#endif

            case 'U':               /* use UTC */
                pv.use_utc = 1;
                break;

#ifdef WIN32
			case 'W':
				      
				if ((pv.interface = pcap_lookupdev(errorbuf)) == NULL)
					perror(errorbuf);

				DisplayBanner();
				PrintDeviceList(pv.interface);
				exit(0);
				break;
#endif
            case 'v':                /* be verbose */
                pv.verbose_flag = 1;
#ifdef DEBUG
                printf("Verbose Flag active\n");
#endif
                break;

            case 'V':                /* prog ver already gets printed out, so we
                                     * just exit */
                DisplayBanner();
                exit(0);

            case 'x':                /* display IPX packets (decoder not
                                     * implemented yet) */
#ifdef DEBUG
                printf("Show IPX active\n");
#endif
                pv.showipx_flag = 1;

                break;

            case 'X':                /* display verbose packet bytecode dumps */
#ifdef DEBUG
                printf("Verbose packet bytecode dumps enabled\n");
#endif
                pv.verbose_bytedump_flag = 1;
                break;

            case '?':                /* show help and exit */
                DisplayBanner();
                ShowUsage(progname);
                exit(0);

            case '6':                /* display IPv6 packets (decoder not
                                     * implemented yet) */
#ifdef DEBUG
                printf("Show IPv6 active\n");
#endif
                pv.showipv6_flag = 1;

                break;

        }
    }

    /* if we're reading in BPF filters from a file */
    if(read_bpf)
    {
        /* suck 'em in */
        pv.pcap_cmd = read_infile(bpf_file);
    }
    else
    {
        /* set the BPF rules string (thanks Mike!) */
        pv.pcap_cmd = copy_argv(&argv[optind]);
    }


    if(pv.interfaces[0] == NULL)
    {
        pv.interfaces[0] = pcap_lookupdev(errorbuf);

        if(pv.interfaces[0] == NULL)
            FatalError( "Failed to lookup for interface: %s."
                        " Please specify one with -i switch\n", errorbuf);
    }




#ifdef DEBUG
    if(pv.pcap_cmd != NULL)
    {
        printf("pcap_cmd = %s\n", pv.pcap_cmd);
    }
    else
    {
        printf("pcap_cmd is NULL!\n");
    }
#endif

    return 0;
}



/*
 * Function: GenHomenet(char *)
 *
 * Purpose: Translate the command line character string into its equivalent
 *          32-bit network byte ordered value (with netmask)
 *
 * Arguments: netdata => The address/CIDR block
 *
 * Returns: void function
 */
void GenHomenet(char *netdata)
{
    struct in_addr net;                /* place to stick the local network data */
    char **toks;                /* dbl ptr to store mSplit return data in */
    int num_toks;                /* number of tokens mSplit returns */
    int nmask;                        /* temporary netmask storage */
    int i;

    /* break out the CIDR notation from the IP address */
    toks = mSplit(optarg, "/", 2, &num_toks, 0);

    if(num_toks > 1)
    {
        /* convert the CIDR notation into a real live netmask */
        nmask = atoi(toks[1]);

        if((nmask > 0) && (nmask < 33))
        {
            pv.netmask = netmasks[nmask];
        }
        else
        {
            FatalError("ERROR: Bad CIDR block [%s:%d], 1 to 32 please!\n",
                       toks[1], nmask);
        }
    }
    else
    {
        FatalError("ERROR: No netmask specified for home network!\n");
    }

    pv.netmask = htonl(pv.netmask);

#ifdef DEBUG
    printf("homenet netmask = %#8lX\n", pv.netmask);
#endif
    /* convert the IP addr into its 32-bit value */
    if((net.s_addr = inet_addr(toks[0])) == -1)
    {
        FatalError("ERROR: Homenet (%s) didn't x-late, WTF?\n",
                   toks[0]);
    }
    else
    {
#ifdef DEBUG
        struct in_addr sin;

        printf("Net = %s (%X)\n", inet_ntoa(net), net.s_addr);
#endif
        /* set the final homenet address up */
        pv.homenet = ((u_long) net.s_addr & pv.netmask);

#ifdef DEBUG
        sin.s_addr = pv.homenet;
        printf("Homenet = %s (%X)\n", inet_ntoa(sin), sin.s_addr);
#endif
    }

    for(i = 0; i < num_toks; i++)
    {
        free(toks[i]);
    }
}


/*
 * Function: SetPktProcessors()
 *
 * Purpose: initializes PktProcessors per-interface
 */
void SetPktProcessors()
{
    int i;

    for(i = 0; i < ifr_count; i++)
    {
        SetPktProcessor(i);
    }

}

/*
 * Function: SetPktProcessor()
 *
 * Purpose:  Set which packet processing function we're going to use based on
 *           what type of datalink layer we're using
 *
 * Arguments: int num => number of interface
 *
 * Returns: 0 => success
 */
int SetPktProcessor(int num)
{
    switch(datalinks[num])
    {
        case DLT_EN10MB:        /* Ethernet */
            if(!pv.readmode_flag)
            {
                if(!pv.quiet_flag)
                    printf("Decoding Ethernet on interface %s\n", 
#ifdef WIN32
						   print_interface(pv.interfaces[num]));
#else
                           pv.interfaces[num]);
#endif
            }

            grinders[num] = DecodeEthPkt;
            break;

        case 13:
        case DLT_IEEE802:                /* Token Ring */
            if(!pv.readmode_flag)
            {
                if(!pv.quiet_flag)
                    printf("Decoding Token Ring on interface %s\n", 
#ifdef WIN32
						   print_interface(pv.interfaces[num]));
#else
                           pv.interfaces[num]);
#endif
            }

            grinders[num] = DecodeTRPkt;

            break;

        case DLT_FDDI:                /* FDDI */
            if(!pv.readmode_flag)
            {
                if(!pv.quiet_flag)
#ifdef WIN32
					printf("Decoding FDDI on interface %s\n", print_interface(pv.interfaces[num]));
#else
                    printf("Decoding FDDI on interface %s\n", pv.interfaces[num]);
#endif
            }

            grinders[num] = DecodeFDDIPkt;

            break;


        case DLT_SLIP:                /* Serial Line Internet Protocol */
            if(!pv.readmode_flag)
            {
                if(!pv.quiet_flag)
                    printf("Decoding Slip on interface %s\n", 
#ifdef WIN32
						   print_interface(pv.interfaces[num]));
#else
                           pv.interfaces[num]);
#endif
            }

            if(pv.show2hdr_flag == 1)
            {
                printf("Second layer header parsing for this datalink "
                       "isn't implemented yet\n");

                pv.show2hdr_flag = 0;
            }

            grinders[num] = DecodeSlipPkt;

            break;

        case DLT_PPP:                /* point-to-point protocol */
            if(!pv.readmode_flag)
            {
                if(!pv.quiet_flag)
                    printf("Decoding PPP on interface %s\n", 
#ifdef WIN32
						   print_interface(pv.interfaces[num]));
#else
                           pv.interfaces[num]);
#endif
            }

            if(pv.show2hdr_flag == 1)
            {
                /* do we need ppp header showup? it's only 4 bytes anyway ;-) */
                printf("Second layer header parsing for this datalink "
                       "isn't implemented yet\n");
                pv.show2hdr_flag = 0;
            }

            grinders[num] = DecodePppPkt;

            break;

#ifdef DLT_LOOP
        case DLT_LOOP:
#endif
#ifdef DLT_LINUX_SLL
        case DLT_LINUX_SLL:
#endif
        case DLT_NULL:            /* loopback and stuff.. you wouldn't perform
                             * intrusion detection on it, but it's ok for
                             * testing. */
            if(!pv.readmode_flag)
            {
                if(!pv.quiet_flag)
                {
#ifdef WIN32
					printf("Decoding LoopBack on interface %s\n", print_interface(pv.interfaces[num]));
#else
                    printf("Decoding LoopBack on interface %s\n", pv.interfaces[num]);
#endif
                }
            }

            if(pv.show2hdr_flag == 1)
            {
                printf("Data link layer header parsing for this network type "
                       "isn't implemented yet\n");
                pv.show2hdr_flag = 0;
            }
            grinders[num] = DecodeNullPkt;

            break;

#ifdef DLT_RAW /* Not supported in some arch or older pcap
                * versions */
        case DLT_RAW:
            if(!pv.readmode_flag)
            {
                if(!pv.quiet_flag)
                    printf("Decoding raw data on interface %s\n", 
#ifdef WIN32
						   print_interface(pv.interfaces[num]));
#else
                           pv.interfaces[num]);
#endif
            }

            if(pv.show2hdr_flag == 1)
            {
                printf("There's no second layer header available for this datalink\n");
                pv.show2hdr_flag = 0;
            }
            grinders[num] = DecodeRawPkt;

            break;
#endif
            /*
             * you need the I4L modified version of libpcap to get this stuff
             * working
             */
#ifdef DLT_I4L_RAWIP
        case DLT_I4L_RAWIP:
            if (! pv.readmode_flag && !pv.quiet_flag)
#ifdef WIN32
				printf("Decoding I4L-rawip on interface %s\n", print_interface(pv.interfaces[num]));
#else
                printf("Decoding I4L-rawip on interface %s\n", pv.interfaces[num]);
#endif

            grinders[num] = DecodeI4LRawIPPkt;

            break;
#endif

#ifdef DLT_I4L_IP
        case DLT_I4L_IP:
            if (! pv.readmode_flag && !pv.quiet_flag)
#ifdef WIN32
				printf("Decoding I4L-ip on interface %s\n", print_interface(pv.interfaces[num]));
#else
                printf("Decoding I4L-ip on interface %s\n", pv.interfaces[num]);
#endif

            grinders[num] = DecodeEthPkt;

            break;
#endif

#ifdef DLT_I4L_CISCOHDLC
        case DLT_I4L_CISCOHDLC:
            if (! pv.readmode_flag && !pv.quiet_flag)
                printf("Decoding I4L-cisco-h on interface %s\n", 
#ifdef WIN32
						   print_interface(pv.interfaces[num]));
#else
                           pv.interfaces[num]);
#endif

            grinders[num] = DecodeI4LCiscoIPPkt;

            break;
#endif

        default:                        /* oops, don't know how to handle this one */
            ErrorMessage("\n%s cannot handle data link type %d",
                         progname, datalink);
            CleanExit(SIGQUIT);
    }

    return 0;
}

/*
 * Function: InitializeInterfaces(void)
 *
 * Purpose - initialize all specified in command line interface(s)
 */
void InitializeInterfaces(void)
{
    int i;

    for(i = 0; i < ifr_count; i++)        /* going through all interfaces */
    {
        OpenPcap(pv.interfaces[i], i);
    }
}



/*
 * Function: void *InterfaceThread(void *arg)
 *
 * Purpose: wrapper for pthread_create() to create a thread per interface
 */
void *InterfaceThread(void *arg)
{
    static int intnum = 0;
    int myint;

#ifdef USE_PTHREADS
    pthread_mutex_lock(&pt_lock);        /* just to make sure we don't skip
                                         * any interfaces, and no threads
                                         * would start on the same interface
                                         * simultaneously */
#endif

    myint = intnum;
    intnum++;

#ifdef USE_PTHREADS
    pthread_mutex_unlock(&pt_lock);
#endif

    /* Read all packets on the device.  Continue until cnt packets read */
    if(pcap_loop(pds[myint], pv.pkt_cnt, (pcap_handler) ProcessPacket, NULL) < 0)
    {
        if(pv.daemon_flag)
            syslog(LOG_CONS | LOG_DAEMON, "pcap_loop: %s", pcap_geterr(pd));
        else
            ErrorMessage("pcap_loop: %s", pcap_geterr(pd));

        CleanExit(SIGQUIT);
    }
    CleanExit(SIGQUIT);

    return NULL;                /* avoid warnings */
}



/****************************************************************************
 *
 * Function: OpenPcap(char *, int)
 *
 * Purpose:  Open the libpcap interface
 *
 * Arguments: intf => name of the interface to open
 *            num  => number of the interface (to fill-in datalink and pd)
 *
 * Returns: 0 => success, exits on problems
 *
 ****************************************************************************/
int OpenPcap(char *intf, int num)
{
    bpf_u_int32 localnet, netmask;        /* net addr holders */
    struct bpf_program fcode;        /* Finite state machine holder */
    char errorbuf[PCAP_ERRBUF_SIZE];        /* buffer to put error strings in */
    bpf_u_int32 defaultnet = 0xFFFFFF00;

    /* if we're not reading packets from a file */
    if(pv.interfaces[num] == NULL)
    {
        if (!pv.readmode_flag)
        {
#ifdef DEBUG
            printf("pv.interface is NULL, looking up interface....   ");
#endif
            /* look up the device and get the handle */
            pv.interfaces[num] = pcap_lookupdev(errorbuf);
    
#ifdef DEBUG
#ifdef WIN32
			printf("found interface %s\n", print_interface(pv.interfaces[num]));
#else
            printf("found interface %s\n", pv.interfaces[num]);
#endif
#endif
            /* uh oh, we couldn't find the interface name */
            if(pv.interfaces[num] == NULL)
            {
                FatalError("ERROR: OpenPcap() interface lookup: \n\t%s\n", errorbuf);
            }
        }
        else
        {
            /* interface is null and we are in readmode */
         pv.interfaces[num] = "[reading from a file]"; /* some routines would hate it to be NULL */
        }
    }

    if(!pv.quiet_flag)
    {
        if (!pv.readmode_flag)
#ifdef WIN32
			printf("\nInitializing Network Interface %s\n", print_interface(pv.interfaces[num]));
#else
            printf("\nInitializing Network Interface %s\n", pv.interfaces[num]);
#endif
        else 
            printf("TCPDUMP file reading mode.\n");
    }
    if (!pv.readmode_flag)
    {
        if(pv.pkt_snaplen)        /* if it's set let's try it... */
        {
            if(pv.pkt_snaplen < MIN_SNAPLEN)        /* if it's < MIN set it to
                                                     * MIN */
            {
                 snaplen = MIN_SNAPLEN;
            }
            else
            {
                 snaplen = pv.pkt_snaplen;
            }
         }
         else
         {
             snaplen = SNAPLEN;        /* otherwise let's put the compiled value in */
         }
        
#ifdef DEBUG
        printf("snaplength info: set=%d/compiled=%d/wanted=%d\n", snaplen,
                   SNAPLEN, pv.pkt_snaplen);
#endif
    
        /* get the device file descriptor */
        pds[num] = pcap_open_live(pv.interfaces[num], snaplen,
                                      pv.promisc_flag ? PROMISC : 0, READ_TIMEOUT, errorbuf);

        /* lookup mtu */
        pv.mtus[num] = GetIfrMTU(pv.interfaces[num]);
            
        if (pv.mtus[num] == -1)
        {
#ifdef WIN32
			FatalError("ERROR: Can not get MTU of an interface %s!\n", print_interface(pv.interfaces[num]));
#else
            FatalError("ERROR: Can not get MTU of an interface %s!\n", pv.interfaces[num]);
#endif
        }
 
        
    }
    else
    {   /* reading packets from a file */

        if (!pv.quiet_flag)
        {
    	    printf("Reading network traffic from \"%s\" file.\n", intf);
        }
        /* open the file */
        pds[num] = pcap_open_offline(intf, errorbuf);

        /* the file didn't open correctly */
        if(pds[num] == NULL)
        {
            FatalError("ERROR => unable to open file %s for readback: %s\n",
                       intf, errorbuf);
        }
        /*
         * set the snaplen for the file (so we don't get a lot of extra crap
         * in the end of packets
         */
        snaplen = pcap_snapshot(pds[num]);

        /* captured framesize can not be bigger than snaplen */
        pv.mtus[num] = snaplen;

        printf("snaplen = %d\n", snaplen);
    }

    /* something is wrong with the opened packet socket */
    if(pds[num] == NULL)
    {
        FatalError("ERROR: OpenPcap() device %s open: \n\t%s\n",
#ifdef WIN32
				   print_interface(pv.interfaces[num]), errorbuf);
#else
                   pv.interfaces[num], errorbuf);
#endif
    }
    /* get local net and netmask */
    if(pcap_lookupnet(pv.interfaces[num], &localnet, &netmask, errorbuf) < 0)
    {
        ErrorMessage("WARNING: OpenPcap() device %s network lookup: \n\t%s\n",
#ifdef WIN32
				   print_interface(pv.interfaces[num]), errorbuf);
#else
                   pv.interfaces[num], errorbuf);
#endif
        /*
         * set the default netmask to 255.255.255.0 (for stealthed
         * interfaces)
         */
        netmask = htonl(defaultnet);
    }
    DefineIfaceVar(pv.interfaces[num], (u_char *) & localnet, (u_char *) & netmask);

    /* compile BPF filter spec info fcode FSM */
    if(pcap_compile(pds[num], &fcode, pv.pcap_cmd, 1, netmask) < 0)
    {
        ErrorMessage("ERROR: OpenPcap() FSM compilation failed: \n\t%s\n",
                     pcap_geterr(pds[num]));
        FatalError("PCAP command: %s\n", pv.pcap_cmd);
    }
    /* set the pcap filter */
    if(pcap_setfilter(pds[num], &fcode) < 0)
    {
        FatalError("ERROR: OpenPcap() setfilter: \n\t%s\n",
                   pcap_geterr(pds[num]));
    }
    /* get data link type */
    datalinks[num] = pcap_datalink(pds[num]);

    if(datalinks[num] < 0)
    {
        FatalError("ERROR: OpenPcap() datalink grab: \n\t%s\n",
                   pcap_geterr(pds[num]));
    }
    return 0;
}


/****************************************************************************
 *
 * Function  : GetIfrMTU()
 * Purpose   : Get Interface MTU value
 * Arguments : interface name (string)
 * Returns   : MTU (or -1)
 *
 ****************************************************************************/


int GetIfrMTU(char *name) {
#ifndef WIN32  
    int fd;
    struct ifreq ifr;
    int retval;


    retval = -1;

#ifdef LINUX
    /*
     * on linux platform with interface type 'any'
     * there's no way to automagically pick up mtu,
     * so we fall back to ETHERNET_MTU size....
     *
     * later it should be replaced to a more sophisticated
     * routine: lookup for all interfaces, lookup for all
     * MTUs, pick up the biggest... :)
     */
    if (!strcmp("any",name)) {
        return ETHERNET_MTU;
    }
#endif
 
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( fd < 0) {
        PrintError("socket");
        return -1;
    }

    strncpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));

#ifndef OSF1
#ifdef SIOCGIFMTU
    if (ioctl(fd, SIOCGIFMTU, &ifr) == 0)
        retval = ifr.ifr_metric;
#else
    if(1)
    {
        retval = ETHERNET_MTU;
    }
#endif
#else
    if (ioctl(fd, SIOCRIPMTU, &ifr) == 0)
        retval = ifr.ifr_metric;
#endif
    else
        PrintError("ioctl(SIOCGIFMTU)");    

    close(fd);
 
 return retval;
#else
 /* Winpcap pnly supports Ethernet Interfaces currently. Ethernet has 1MTU of 1500.*/
 return 1500;
#endif
}

/****************************************************************************
 *
 * Function  : DefineIfaceVar()
 * Purpose   : Assign network address and network mast to IFACE_ADDR_VARNAME
 *             variable.
 * Arguments : interface name (string) netaddress and netmask (4 octets each)
 * Returns   : void function
 *
 ****************************************************************************/
void DefineIfaceVar(char *iname, u_char * network, u_char * netmask)
{
    char valbuf[32];
    char varbuf[BUFSIZ + 1];

    snprintf(varbuf, BUFSIZ, "%s_ADDRESS", iname);

    snprintf(valbuf, 31, "%d.%d.%d.%d/%d.%d.%d.%d",
             network[0] & 0xff, network[1] & 0xff, network[2] & 0xff, network[3] & 0xff,
             netmask[0] & 0xff, netmask[1] & 0xff, netmask[2] & 0xff, netmask[3] & 0xff);
    VarDefine(varbuf, valbuf);
}

/****************************************************************************
 *
 * Function: CleanExit()
 *
 * Purpose:  Clean up misc file handles and such and exit
 *
 * Arguments: Signal
 *
 * Returns: void function
 *
 ****************************************************************************/
extern PluginSignalFuncNode *PluginCleanExitList;
extern PluginSignalFuncNode *PluginRestartList;

void CleanExit(int sig)
{
    PluginSignalFuncNode *idx;

    if(sig != SIGHUP)
        LogMessage("\nExiting...\n");
    else
        LogMessage("\nRestarting...\n");

    if(pv.logbin_flag)
    {
        pcap_dump_close(dumpd);
    }
    unlink(pv.pid_filename);

    pv.pid_filename[0] = 0;

    if(pv.alert_mode == ALERT_FAST || pv.alert_mode == ALERT_FULL)
    {
        if(alert != NULL)
        {
            fclose(alert);
        }
    }
    /* carry signals down to plugins */
    if(sig != SIGHUP)
    {
        idx = PluginCleanExitList;
    }
    else
    {
        idx = PluginRestartList;
    }

    while(idx != NULL)
    {
        idx->func(sig, idx->arg);
        idx = idx->next;
    }

#ifndef WIN32
    DropStats();
#else
	DropStats(0);
#endif
    /*
     * you will hardly run snort in daemon mode and read from file i that is
     * why no `LogMessage()' here
     */
/*    if( pv.readmode_flag )
    {
        puts("\n\n===============================================================================\n");

        recv = pc.tcp + pc.udp + pc.icmp + pc.arp + pc.ipx + pc.ipv6 + pc.other;

        printf("Snort processed %d packets.\n", (int) recv);

        puts("Breakdown by protocol:\n");
        printf("    TCP: %-10ld (%.3f%%)\n", pc.tcp, CalcPct((float) pc.tcp, recv));
        printf("    UDP: %-10ld (%.3f%%)\n", pc.udp, CalcPct((float) pc.udp, recv));
        printf("   ICMP: %-10ld (%.3f%%)\n", pc.icmp, CalcPct((float) pc.icmp, recv));
        printf("  FRAGS: %-10ld (%.3f%%)\n", pc.icmp, CalcPct((float) pc.frags, recv));
        printf("    ARP: %-10ld (%.3f%%)\n", pc.arp, CalcPct((float) pc.arp, recv));
        printf("   IPv6: %-10ld (%.3f%%)\n", pc.ipv6, CalcPct((float) pc.ipv6, recv));
        printf("    IPX: %-10ld (%.3f%%)\n", pc.ipx, CalcPct((float) pc.ipx, recv));
        printf("  OTHER: %-10ld (%.3f%%)\n", pc.other, CalcPct((float) pc.other, recv));
        puts("\n\n===============================================================================\n");

        exit_or_exec(0, sig);
        exit(0);
    }  */

    if(pd == NULL)
        exit(1);

    /* collect the packet stats */
/*    if( pcap_stats(pd, &ps) )
    {
        pcap_perror(pd, "pcap_stats");
    }
    else
    {
        recv = ps.ps_recv;
        drop = ps.ps_drop;

        LogMessage("\n\n===============================================================================\n");
        LogMessage("Snort received %d packets", ps.ps_recv);

        if( ps.ps_recv )
        {
#ifndef LINUX
            LogMessage(" and dropped %d(%.3f%%) packets\n\n", ps.ps_drop,
                       CalcPct(drop, recv));
#else
            LogMessage(".\nPacket loss statistics are unavailable under Linux.  Sorry!\n\n");
#endif
        }
        else
        {
            LogMessage(".\n");
        }
        LogMessage("Breakdown by protocol:\n");
        LogMessage("    TCP: %-10ld (%.3f%%)\n", pc.tcp, CalcPct((float) pc.tcp, recv));
        LogMessage("    UDP: %-10ld (%.3f%%)\n", pc.udp, CalcPct((float) pc.udp, recv));
        LogMessage("   ICMP: %-10ld (%.3f%%)\n", pc.icmp, CalcPct((float) pc.icmp, recv));
        LogMessage("  FRAGS: %-10ld (%.3f%%)\n", pc.icmp, CalcPct((float) pc.frags, recv));
        LogMessage("    ARP: %-10ld (%.3f%%)\n", pc.arp, CalcPct((float) pc.arp, recv));
        LogMessage("   IPv6: %-10ld (%.3f%%)\n", pc.ipv6, CalcPct((float) pc.ipv6, recv));
        LogMessage("    IPX: %-10ld (%.3f%%)\n", pc.ipx, CalcPct((float) pc.ipx, recv));
        LogMessage("  OTHER: %-10ld (%.3f%%)\n", pc.other, CalcPct((float) pc.other, recv));

        LogMessage("===============================================================================\n");
    }*/

#ifdef WIN32
	WSACleanup();
#endif
    pcap_close(pd);

    exit_or_exec(0, sig);
    exit(0);
}


/*
 *
 * exit_or_exec()
 * Arguments: status, signal received.
 *
 * This function performs exec on SIGHUP signal and exit otherwise
 *
 */
void exit_or_exec(int stat, int sig)
{
    /* make sure everything that needs to go to the screen gets there */
    fflush(stdout);

    if(sig != SIGHUP)
    {
        exit(stat);
    }
    else
    {
        LogMessage("Received SIGHUP. Restarting");
#ifdef PARANOID
        execv(progname, progargs);
#else
        execvp(progname, progargs);
#endif
        LogMessage("Restarting %s failed", progname);
        exit(1);
    }
}

/****************************************************************************
 *
 * Function: CalcPct(float, float)
 *
 * Purpose:  Calculate the percentage of a value compared to a total
 *
 * Arguments: cnt => the numerator in the equation
 *            total => the denominator in the calculation
 *
 * Returns: pct -> the percentage of cnt to value
 *
 ****************************************************************************/
float CalcPct(float cnt, float total)
{
    float pct;

    if(cnt > 0.0)
        pct = cnt / total;
    else
        return 0.0;

    pct *= 100.0;

    return pct;
}


/****************************************************************************
 *
 * Function: DisplayBanner()
 *
 * Purpose:  Show valuable proggie info
 *
 * Arguments: None.
 *
 * Returns: 0 all the time
 *
 ****************************************************************************/
int DisplayBanner()
{
#ifdef WIN32
	/* Give me credit too ;) -- Mike Davis */
	fprintf(stderr, "\n-*> Snort! <*-\nVersion %s\nBy Martin Roesch (roesch@clark.net, www.snort.org)\nWIN32 Port By Michael Davis (mike@datanerds.net, www.datanerds.net/~mike)\n", VERSION);
#else
    fprintf(stderr, "\n-*> Snort! <*-\nVersion %s\nBy Martin Roesch (roesch@clark.net, www.snort.org)\n", VERSION);
#endif
    return 0;
}



/****************************************************************************
 *
 * Function: ts_print(register const struct, char *)
 *
 * Purpose: Generate a time stamp and stuff it in a buffer.  This one has
 *          millisecond precision.  Oh yeah, I ripped this code off from
 *          TCPdump, props to those guys.
 *
 * Arguments: timeval => clock struct coming out of libpcap
 *            timebuf => buffer to stuff timestamp into
 *
 * Returns: void function
 *
 ****************************************************************************/
void ts_print(register const struct timeval * tvp, char *timebuf)
{
    register int s;
    struct timeval tv;
    struct timezone tz;
    struct tm *lt;                /* place to stick the adjusted clock data */

    /* if null was passed, we use current time */
    if(!tvp)
    {
        /* manual page (for linux) says tz is never used, so.. */
        bzero((char *) &tz, sizeof(tz));
        gettimeofday(&tv, &tz);
        tvp = &tv;
    }
    lt = localtime((time_t *) & tvp->tv_sec);

    s = (tvp->tv_sec + thiszone) % 86400;

    (void) sprintf(timebuf, "%02d/%02d-%02d:%02d:%02d.%06u ", lt->tm_mon + 1,
                   lt->tm_mday, s / 3600, (s % 3600) / 60, s % 60,
                   (u_int) tvp->tv_usec);
}



/****************************************************************************
 *
 * Function: gmt2local(time_t)
 *
 * Purpose: Figures out how to adjust the current clock reading based on the
 *          timezone you're in.  Ripped off from TCPdump.
 *
 * Arguments: time_t => offset from GMT
 *
 * Returns: offset seconds from GMT
 *
 ****************************************************************************/
int gmt2local(time_t t)
{
    register int dt, dir;
    register struct tm *gmt, *loc;
    struct tm sgmt;

    if(t == 0)
        t = time(NULL);

    gmt = &sgmt;
    *gmt = *gmtime(&t);
    loc = localtime(&t);

    dt = (loc->tm_hour - gmt->tm_hour) * 60 * 60 +
         (loc->tm_min - gmt->tm_min) * 60;

    /*
     * If the year or julian day is different, we span 00:00 GMT and must add
     * or subtract a day. Check the year first to avoid problems when the
     * julian day wraps.
     */

    dir = loc->tm_year - gmt->tm_year;

    if(dir == 0)
        dir = loc->tm_yday - gmt->tm_yday;

    dt += dir * 24 * 60 * 60;

    return(dt);
}




/****************************************************************************
 *
 * Function: copy_argv(u_char **)
 *
 * Purpose: Copies a 2D array (like argv) into a flat string.  Stolen from
 *          TCPDump.
 *
 * Arguments: argv => 2D array to flatten
 *
 * Returns: Pointer to the flat string
 *
 ****************************************************************************/
char *copy_argv(char **argv)
{
    char **p;
    u_int len = 0;
    char *buf;
    char *src, *dst;
    void ftlerr(char *,...);

    p = argv;
    if(*p == 0)
        return 0;

    while(*p)
        len += strlen(*p++) + 1;

    buf = (char *) malloc(len);

    if(buf == NULL)
    {
        FatalError("malloc() failed: %s\n", strerror(errno));
    }
    p = argv;
    dst = buf;

    while((src = *p++) != NULL)
    {
        while((*dst++ = *src++) != '\0');
        dst[-1] = ' ';
    }

    dst[-1] = '\0';

    return buf;
}


/****************************************************************************
 *
 * Function: strip(char *)
 *
 * Purpose: Strips a data buffer of CR/LF/TABs.  Replaces CR/LF's with
 *          NULL and TABs with spaces.
 *
 * Arguments: data => ptr to the data buf to be stripped
 *
 * Returns: size of the newly stripped string
 *
 ****************************************************************************/
int strip(char *data)
{
    int size;
    char *end;
    char *idx;

    idx = data;
    end = data + strlen(data);
    size = end - idx;

    while(idx != end)
    {
        if((*idx == '\n') ||
           (*idx == '\r'))
        {
            *idx = 0;
            size--;
        }
        if(*idx == '\t')
        {
            *idx = ' ';
        }
        idx++;
    }

    return size;
}


/****************************************************************************
 *
 * Function: InitNetMasks()
 *
 * Purpose: Loads the netmask struct in network order.  Yes, I know I could
 *          just load the array when I define it, but this is what occurred
 *          to me when I wrote this at 3:00 AM.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void InitNetmasks()
{
    netmasks[0] = 0x0;
    netmasks[1] = 0x80000000;
    netmasks[2] = 0xC0000000;
    netmasks[3] = 0xE0000000;
    netmasks[4] = 0xF0000000;
    netmasks[5] = 0xF8000000;
    netmasks[6] = 0xFC000000;
    netmasks[7] = 0xFE000000;
    netmasks[8] = 0xFF000000;
    netmasks[9] = 0xFF800000;
    netmasks[10] = 0xFFC00000;
    netmasks[11] = 0xFFE00000;
    netmasks[12] = 0xFFF00000;
    netmasks[13] = 0xFFF80000;
    netmasks[14] = 0xFFFC0000;
    netmasks[15] = 0xFFFE0000;
    netmasks[16] = 0xFFFF0000;
    netmasks[17] = 0xFFFF8000;
    netmasks[18] = 0xFFFFC000;
    netmasks[19] = 0xFFFFE000;
    netmasks[20] = 0xFFFFF000;
    netmasks[21] = 0xFFFFF800;
    netmasks[22] = 0xFFFFFC00;
    netmasks[23] = 0xFFFFFE00;
    netmasks[24] = 0xFFFFFF00;
    netmasks[25] = 0xFFFFFF80;
    netmasks[26] = 0xFFFFFFC0;
    netmasks[27] = 0xFFFFFFE0;
    netmasks[28] = 0xFFFFFFF0;
    netmasks[29] = 0xFFFFFFF8;
    netmasks[30] = 0xFFFFFFFC;
    netmasks[31] = 0xFFFFFFFE;
    netmasks[32] = 0xFFFFFFFF;
}




/****************************************************************************
 *
 * Function: GoDaemon()
 *
 * Purpose: Puts the program into daemon mode, nice and quiet like....
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void GoDaemon(void)
{
#ifndef WIN32
    pid_t fs;

    printf("Initializing daemon mode\n");

    if(getppid() != 1)
    {
        fs = fork();

        if(fs > 0)
            exit(0);                /* parent */

        if(fs < 0)
        {
            perror("fork");
            exit(1);
        }
        setsid();
    }
    /* redirect stdin/stdout/stderr to /dev/null */
    close(0);
    close(1);
    close(2);

#ifdef DEBUG
    open("/tmp/snort.debug", O_CREAT | O_RDWR);
#else
    open("/dev/null", O_RDWR);
#endif

    dup(0);
    dup(0);
    umask(077);
#endif
    return;
}


/****************************************************************************
 *
 * Function: SanityChecks()
 *
 * Purpose: CyberPsychotic sez: basically we only check if logdir exist and
 *          writable, since it might screw the whole thing in the middle. Any
 *          other checks could be performed here as well.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SanityChecks(void)
{
    struct stat st;
    struct stat pt;
    char log_dir[STD_BUF + 1];
#ifdef WIN32
	char dir[STD_BUF + 1];
#endif

    snprintf(log_dir, STD_BUF, "%s%s", chrootdir == NULL ? "" : chrootdir, pv.log_dir);
    stat(log_dir, &st);

    if(!S_ISDIR(st.st_mode) || access(log_dir, W_OK) == -1)
    {
        FatalError("\n[!] ERROR: "
                   "Can not get write access to logging directory %s.\n"
                   "(directory doesn't exist or permissions are set incorrectly\n"
                   /*
                    * let us add this comment. Too many people seem to confuse it
                    * otherwise :-)
                    */
                   "or it is not a directory at all)\n\n",
                   log_dir);
    }
    if (!pv.readmode_flag) {
#ifndef _PATH_VARRUN
#ifdef WIN32
	if (GetCurrentDirectory(sizeof (dir)-1, dir))
        strncpy (_PATH_VARRUN, dir, sizeof(dir));
#else
        strncpy(_PATH_VARRUN, "/var/run/", 10);
#endif
#endif

        stat(_PATH_VARRUN, &pt);
    
        if(!S_ISDIR(pt.st_mode) || access(_PATH_VARRUN, W_OK) == -1)
        {
            ErrorMessage("WARNING: _PATH_VARRUN is invalid, logging Snort PID to"
                         " log directory (%s)\n", pv.log_dir);
    
            snprintf(pv.pid_path, STD_BUF - 1, "%s/", log_dir);
        }
        else
        {
            strncpy(pv.pid_path, _PATH_VARRUN, strlen(_PATH_VARRUN)+1);
        }
    }
}



/****************************************************************************
 *
 * Function: read_infile(char *)
 *
 * Purpose: Reads the BPF filters in from a file.  Ripped from tcpdump.
 *
 * Arguments: fname => the name of the file containing the BPF filters
 *
 * Returns: the processed BPF string
 *
 ****************************************************************************/
char *read_infile(char *fname)
{
    register int fd, cc;
    register char *cp;
    struct stat buf;

    fd = open(fname, O_RDONLY);

    if(fd < 0)
        ErrorMessage("can't open %s: %s", fname, pcap_strerror(errno));

    if(fstat(fd, &buf) < 0)
        ErrorMessage("can't stat %s: %s", fname, pcap_strerror(errno));

    cp = malloc((u_int) buf.st_size + 1);

    cc = read(fd, cp, (int) buf.st_size);

    if(cc < 0)
        ErrorMessage("read %s: %s", fname, pcap_strerror(errno));

    if(cc != buf.st_size)
        ErrorMessage("short read %s (%d != %d)", fname, cc, (int) buf.st_size);

    cp[(int) buf.st_size] = '\0';

    return(cp);
}



/****************************************************************************
 *
 * Function: InitProtoNames()
 *
 * Purpose: Initializes the protocol names
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void InitProtoNames()
{
    int i;
    struct protoent *pt;
    unsigned char *tmp;
    u_char protoname[11];

    for(i = 0; i < 256; i++)
    {
        pt = getprotobynumber(i);

        if(pt)
        {
            protocol_names[i] = strdup(pt->p_name);

            tmp = protocol_names[i];

            for(tmp = protocol_names[i]; *tmp != 0; tmp++)
                *tmp = (unsigned char) toupper(*tmp);
        }
        else
        {
            snprintf(protoname, 10, "PROTO%03d", i);
            protocol_names[i] = strdup(protoname);
        }
    }
}

/*
 * error message printing routines. in daemon mode these would go into
 * syslog.
 *
 * first would allow to print formatted error messages (similar to printf) and
 * the second is similar to perror.
 *
 */

void PrintError(char *str)
{
    if(pv.daemon_flag)
        syslog(LOG_CONS | LOG_DAEMON | LOG_ERR, "%s:%m", str);
    else
        perror(str);
}


/*
 * Function: ErrorMessage(const char *, ...)
 *
 * Purpose: Print a message to stderr.
 *
 * Arguments: format => the formatted error string to print out
 *            ... => format commands/fillers
 *
 * Returns: void function
 */
void ErrorMessage(const char *format,...)
{
    char buf[STD_BUF + 1];
    va_list ap;

    va_start(ap, format);

    if(pv.daemon_flag)
    {
        vsprintf(buf, format, ap);
        syslog(LOG_DAEMON | LOG_ERR, "%s", buf);
    }
    else
    {
        vfprintf(stderr, format, ap);
    }
}

/*
 * Function: LogMessage(const char *, ...)
 *
 * Purpose: Print a message to stdout or with logfacility.
 *
 * Arguments: format => the formatted error string to print out
 *            ... => format commands/fillers
 *
 * Returns: void function
 */
void LogMessage(const char *format,...)
{
    char buf[STD_BUF + 1];
    va_list ap;

    if(pv.quiet_flag)
        return;

    va_start(ap, format);

    if(pv.daemon_flag)
    {
        vsprintf(buf, format, ap);
        syslog(LOG_DAEMON | LOG_NOTICE, "%s", buf);
    }
    else
    {
        vfprintf(stderr, format, ap);
    }
}


/*
 * Function: FatalError(const char *, ...)
 *
 * Purpose: When a fatal error occurs, this function prints the error message
 *          and cleanly shuts down the program
 *
 * Arguments: format => the formatted error string to print out
 *            ... => format commands/fillers
 *
 * Returns: void function
 */
void FatalError(const char *format,...)
{
    char buf[STD_BUF];
    va_list ap;

    va_start(ap, format);

    if(pv.daemon_flag)
    {
        vsprintf(buf, format, ap);
        syslog(LOG_CONS | LOG_DAEMON | LOG_ERR, "%s", buf);
    }
    else
    {
        vfprintf(stderr, format, ap);
    }

    exit(1);
}

void FatalPrintError(char *msg)
{
    PrintError(msg);

    exit(1);
}

/****************************************************************************
 *
 * Function: CreatePidFile(char *)
 *
 * Purpose:  Creates a PID file
 *
 * Arguments: Interface opened.
 *
 * Returns: void function
 *
 ****************************************************************************/
void CreatePidFile(char *intf)
{
    FILE *pid_file;

    if(intf == NULL || pv.pid_path == NULL)
    {
        /* pv.pid_path should have some value by now
         * so let us just be sane.
         */
        FatalError("ERROR: CreatePidFile() failed to lookup interface or pid_path is unknown!\n");
    }
    snprintf(pv.pid_filename, STD_BUF - 1,  "%s/snort_%s.pid", pv.pid_path, intf);

    pid_file = fopen(pv.pid_filename, "w");

    if(pid_file)
    {
        fprintf(pid_file, "%d\n", (int) getpid());
        fclose(pid_file);
    }
    else
    {
        ErrorMessage("Failed to create pid file %s", pv.pid_filename);
        pv.pid_filename[0] = 0;
    }
}


/****************************************************************************
 *
 * Function: SetUidGid(char *)
 *
 * Purpose:  Sets safe UserID and GroupID if needed
 *
 * Arguments: none
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetUidGid(void)
{
#ifndef WIN32
    if(groupname != NULL)
    {
        if(setgid(groupid) < 0)
            FatalError("Can not set gid: %lu\n", (u_long) groupid);

#ifdef DEBUG
        printf("Set gid to %lu\n", groupid);
#endif

    }
    if(username != NULL)
    {
        if(getuid() == 0 && initgroups(username, groupid) < 0)
            FatalError("Can not initgroups(%s,%lu)",
                       username, (u_long) groupid);

        /** just to be on a safe side... **/
        endgrent();
        endpwent();

        if(setuid(userid) < 0)
            FatalError("Can not set uid: %lu\n", (u_long) userid);
#ifdef DEBUG
        printf("Set gid to %lu\n", groupid);
#endif
    }
#endif
}


void DropStats(int sig)
{
    struct pcap_stat ps;
    float drop;
    float recv;

    /*
     * you will hardly run snort in daemon mode and read from file i that is
     * why no `LogMessage()' here
     */
    if(pv.readmode_flag)
    {
        puts("\n\n===============================================================================\n");

        recv = (float)(pc.tcp + pc.udp + pc.icmp + pc.arp + pc.ipx + pc.ipv6 + pc.other + pc.frags);

        printf("Snort processed %d packets.\n", (int) recv);

        puts("Breakdown by protocol:                Action Stats:\n");
        printf("    TCP: %-10ld (%.3f%%)%-*sALERTS: %-10ld\n", 
               pc.tcp, CalcPct((float) pc.tcp, recv), 
               CalcPct((float)pc.tcp,recv)<10?10:9 , " ", pc.alert_pkts);
        printf("    UDP: %-10ld (%.3f%%)%-*sLOGGED: %-10ld\n", 
               pc.udp, CalcPct((float) pc.udp, recv),  
               CalcPct((float)pc.udp,recv)<10?10:9, " ", pc.log_pkts);
        printf("   ICMP: %-10ld (%.3f%%)%-*sPASSED: %-10ld\n", 
               pc.icmp, CalcPct((float) pc.icmp, recv), 
               CalcPct((float)pc.icmp,recv)<10?10:9, " ", pc.pass_pkts);
        printf("    ARP: %-10ld (%.3f%%)\n", pc.arp, CalcPct((float) pc.arp, recv));
        printf("   IPv6: %-10ld (%.3f%%)\n", pc.ipv6, CalcPct((float) pc.ipv6, recv));
        printf("    IPX: %-10ld (%.3f%%)\n", pc.ipx, CalcPct((float) pc.ipx, recv));
        printf("  OTHER: %-10ld (%.3f%%)\n", pc.other, CalcPct((float) pc.other, recv));
        printf("===============================================================================\n");
        printf("Fragmentation Stats:\n");
        printf("Fragmented IP Packets: %-10ld (%-3.3f%%)\n", pc.frags, CalcPct((float) pc.frags, recv));
        printf("   Rebuilt IP Packets: %-10ld\n", pc.rebuilt_frags);
        printf("   Frag elements used: %-10ld\n", pc.rebuild_element);
        printf("Discarded(incomplete): %-10ld\n", pc.frag_incomp);
        printf("   Discarded(timeout): %-10ld\n", pc.frag_timeout);
        puts("===============================================================================\n");
        printf("TCP Stream Reassembly Stats:\n");
        printf("   TCP Packets Used:      %-10ld (%-3.3f%%)\n", pc.tcp_stream_pkts, CalcPct((float) pc.tcp_stream_pkts, recv));
        printf("   Reconstructed Packets: %-10ld (%-3.3f%%)\n", pc.rebuilt_tcp,CalcPct((float) pc.rebuilt_tcp, recv));
        printf("   Streams Reconstructed: %-10ld\n", pc.tcp_streams);
        puts("===============================================================================\n");

    }
    else
    {
        /* collect the packet stats */
        if(pcap_stats(pd, &ps))
        {
            pcap_perror(pd, "pcap_stats");
        }
        else
        {
            recv = (float)ps.ps_recv;
            drop = (float)ps.ps_drop;

            LogMessage("\n\n===============================================================================\n");
            LogMessage("Snort received %d packets", ps.ps_recv);

            if(ps.ps_recv)
            {
                LogMessage(" and dropped %d(%.3f%%) packets\n\n", ps.ps_drop, CalcPct(drop, recv));
            }
            else
            {
                LogMessage(".\n");
            }

            LogMessage("Breakdown by protocol:                Action Stats:\n");
            LogMessage("    TCP: %-10ld (%.3f%%)%-*sALERTS: %-10ld\n", 
                       pc.tcp, CalcPct((float) pc.tcp, recv), 
                       CalcPct((float)pc.tcp,recv)<10?10:9 , " ", pc.alert_pkts);
            LogMessage("    UDP: %-10ld (%.3f%%)%-*sLOGGED: %-10ld\n", 
                       pc.udp, CalcPct((float) pc.udp, recv),  
                       CalcPct((float)pc.udp,recv)<10?10:9, " ", pc.log_pkts);
            LogMessage("   ICMP: %-10ld (%.3f%%)%-*sPASSED: %-10ld\n", 
                       pc.icmp, CalcPct((float) pc.icmp, recv), 
                       CalcPct((float)pc.icmp,recv)<10?10:9, " ", pc.pass_pkts);
            LogMessage("    ARP: %-10ld (%.3f%%)\n", pc.arp, CalcPct((float) pc.arp, recv));
            LogMessage("   IPv6: %-10ld (%.3f%%)\n", pc.ipv6, CalcPct((float) pc.ipv6, recv));
            LogMessage("    IPX: %-10ld (%.3f%%)\n", pc.ipx, CalcPct((float) pc.ipx, recv));
            LogMessage("  OTHER: %-10ld (%.3f%%)\n", pc.other, CalcPct((float) pc.other, recv));
            LogMessage("DISCARD: %-10ld (%.3f%%)\n", pc.discards, CalcPct((float) pc.discards, recv));
            LogMessage("===============================================================================\n");
            LogMessage("Fragmentation Stats:\n");
            LogMessage("Fragmented IP Packets: %-10ld (%.3f%%)\n", pc.frags, CalcPct((float) pc.frags, recv));
            LogMessage("   Rebuilt IP Packets: %-10ld\n", pc.rebuilt_frags);
            LogMessage("   Frag elements used: %-10ld\n", pc.rebuild_element);
            LogMessage("Discarded(incomplete): %-10ld\n", pc.frag_incomp);
            LogMessage("   Discarded(timeout): %-10ld\n", pc.frag_timeout);

            LogMessage("===============================================================================\n");
            LogMessage("TCP Stream Reassembly Stats:\n");
            LogMessage("   TCP Packets Used:      %-10ld (%-3.3f%%)\n", pc.tcp_stream_pkts, CalcPct((float) pc.tcp_stream_pkts, recv));
            LogMessage("   Reconstructed Packets: %-10ld (%-3.3f%%)\n", pc.rebuilt_tcp,CalcPct((float) pc.rebuilt_tcp, recv));
            LogMessage("   Streams Reconstructed: %-10ld\n", pc.tcp_streams);
            LogMessage("===============================================================================\n");
        }    
    }

    return;
}

/* vim: smartindent:expandtab:sw=4:ts=4:tw=0
 */
