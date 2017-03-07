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

/* $Id: decode.h,v 1.12 2001/01/21 20:23:54 fygrave Exp $ */

#include "snort.h"

#ifndef __DECODE_H__
#define __DECODE_H__


/*  I N C L U D E S  **********************************************************/

#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifndef WIN32
	#include <strings.h>
	#include <errno.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>
#include <ctype.h>
#include <pcap-namedb.h>
#include <syslog.h>






/*  D E F I N E S  ************************************************************/
#define ETHERNET_MTU            1500
#define ETHERNET_TYPE_IP        0x0800
#define ETHERNET_TYPE_ARP       0x0806
#define ETHERNET_TYPE_REVARP    0x8035
#define ETHERNET_TYPE_IPV6      0x86dd
#define ETHERNET_TYPE_IPX       0x8137

#define ETHERNET_HEADER_LEN             14
#define MINIMAL_TOKENRING_HEADER_LEN    22
#define TR_HLEN                         MINIMAL_TOKENRING_HEADER_LEN
#define TOKENRING_LLC_LEN                8
#define SLIP_HEADER_LEN                 16

/* ppp header structure */
struct ppp_header {
       unsigned char  address;
       unsigned char  control;
       unsigned short protocol;
};

#ifndef PPP_HDRLEN
    #define PPP_HDRLEN          sizeof(struct ppp_header)
#endif
#define PPP_IP         0x0021          /* Internet Protocol */
#define PPP_VJ_COMP    0x002d          /* VJ compressed TCP/IP */
#define PPP_VJ_UCOMP   0x002f          /* VJ uncompressed TCP/IP */
#define PPP_IPX                0x002b          /* Novell IPX Protocol */

/* otherwise defined in /usr/include/ppp_defs.h */
#ifndef PPP_MTU
    #define PPP_MTU                 1500
#endif

/* NULL aka LoopBack interfaces */
#define NULL_HDRLEN             4

/* otherwise defined in /usr/include/ppp_defs.h */
#define IP_HEADER_LEN           20
#define TCP_HEADER_LEN          20
#define UDP_HEADER_LEN          8
#define ICMP_HEADER_LEN         4

#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
#define TH_RES2 0x40
#define TH_RES1 0x80

/*
 * tcp options stuff. used to be in <netinet/tcp.h> but it breaks
 * things on AIX
 */
#define	TCPOPT_EOL		0
#define	TCPOPT_NOP		1
#define	TCPOPT_MAXSEG		2
#define TCPOLEN_MAXSEG		4
#define TCPOPT_WINDOW		3
#define TCPOLEN_WINDOW		3
#define TCPOPT_SACK_PERMITTED	4	/* Experimental */
#define TCPOLEN_SACK_PERMITTED	2
#define TCPOPT_SACK		5	/* Experimental */
#define TCPOPT_TIMESTAMP	8
#define TCPOLEN_TIMESTAMP	10
#define TCPOLEN_TSTAMP_APPA	(TCPOLEN_TIMESTAMP+2)	/* appendix A */

#define TCPOPT_TSTAMP_HDR	\
    (TCPOPT_NOP<<24|TCPOPT_NOP<<16|TCPOPT_TIMESTAMP<<8|TCPOLEN_TIMESTAMP)

/*
 * Default maximum segment size for TCP.
 * With an IP MSS of 576, this is 536,
 * but 512 is probably more convenient.
 * This should be defined as MIN(512, IP_MSS - sizeof (struct tcpiphdr)).
 */

#ifndef TCP_MSS
    #define	TCP_MSS	512
#endif

#ifndef TCP_MAXWIN
    #define	TCP_MAXWIN	65535	/* largest value for (unscaled) window */
#endif

#ifndef TCP_MAX_WINSHIFT 
    #define TCP_MAX_WINSHIFT	14	/* maximum window shift */
#endif

/*
 * User-settable options (used with setsockopt).
 */
#ifndef TCP_NODELAY
    #define	TCP_NODELAY	0x01	/* don't delay send to coalesce packets */
#endif

#ifndef TCP_MAXSEG
    #define	TCP_MAXSEG	0x02	/* set maximum segment size */
#endif

#define SOL_TCP		6	/* TCP level */



#define L2TP_PORT 1701
#define DHCP_CLIENT_PORT 68
#define DHCP_SERVER_PORT 67

/* IRIX 6.2 hack! */
#ifndef IRIX
    #define SNAPLEN      1514
#else
    #define SNAPLEN      1500
#endif

#define MIN_SNAPLEN  68
#define PROMISC      1
#define READ_TIMEOUT 500

/* Start Token Ring */
#ifdef WIN32 /* Uhm, We need this. -- Mike */

    #define TR_ALEN      6		/* octets in an Ethernet header */
    #define IPARP_SAP 0xaa

    #define AC           0x10
    #define LLC_FRAME    0x40

    #define TRMTU                      2000	/* 2000 bytes            */
    #define TR_RII                     0x80
    #define TR_RCF_DIR_BIT             0x80
    #define TR_RCF_LEN_MASK            0x1f00
    #define TR_RCF_BROADCAST           0x8000	/* all-routes broadcast   */
    #define TR_RCF_LIMITED_BROADCAST   0xC000	/* single-route broadcast */
    #define TR_RCF_FRAME2K             0x20
    #define TR_RCF_BROADCAST_MASK      0xC000

#endif				/* WIN32 */
/* End Token Ring */

/* Start FDDI */
#define FDDI_ALLC_LEN                   13
#define FDDI_ALEN                       6
#define FDDI_MIN_HLEN                   FDDI_ALLC_LEN + 3

#define FDDI_DSAP_SNA                   0x08	/* SNA */
#define FDDI_SSAP_SNA                   0x00	/* SNA */
#define FDDI_DSAP_STP                   0x42	/* Spanning Tree Protocol */
#define FDDI_SSAP_STP                   0x42	/* Spanning Tree Protocol */
#define FDDI_DSAP_IP                    0xaa	/* IP */
#define FDDI_SSAP_IP                    0xaa	/* IP */

#define FDDI_ORG_CODE_ETHR              0x000000	/* Encapsulated Ethernet */
#define FDDI_ORG_CODE_CDP               0x00000c	/* Cisco Discovery
							 * Proto(?) */

#define ETHERNET_TYPE_CDP               0x2000	/* Cisco Discovery Protocol */
/* End FDDI */

#define ARPOP_REQUEST   1	/* ARP request                  */
#define ARPOP_REPLY     2	/* ARP reply                    */
#define ARPOP_RREQUEST  3	/* RARP request                 */
#define ARPOP_RREPLY    4	/* RARP reply                   */

#define ICMP_ECHOREPLY          0	/* Echo Reply                   */
#define ICMP_DEST_UNREACH       3	/* Destination Unreachable      */
#define ICMP_SOURCE_QUENCH      4	/* Source Quench                */
#define ICMP_REDIRECT           5	/* Redirect (change route)      */
#define ICMP_ECHO               8	/* Echo Request                 */
#define ICMP_TIME_EXCEEDED      11	/* Time Exceeded                */
#define ICMP_PARAMETERPROB      12	/* Parameter Problem            */
#define ICMP_TIMESTAMP          13	/* Timestamp Request            */
#define ICMP_TIMESTAMPREPLY     14	/* Timestamp Reply              */
#define ICMP_INFO_REQUEST       15	/* Information Request          */
#define ICMP_INFO_REPLY         16	/* Information Reply            */
#define ICMP_ADDRESS            17	/* Address Mask Request         */
#define ICMP_ADDRESSREPLY       18	/* Address Mask Reply           */
#define NR_ICMP_TYPES           18

/* Codes for ICMP UNREACHABLES */
#define ICMP_NET_UNREACH        0	/* Network Unreachable          */
#define ICMP_HOST_UNREACH       1	/* Host Unreachable             */
#define ICMP_PROT_UNREACH       2	/* Protocol Unreachable         */
#define ICMP_PORT_UNREACH       3	/* Port Unreachable             */
#define ICMP_FRAG_NEEDED        4	/* Fragmentation Needed/DF set  */
#define ICMP_SR_FAILED          5	/* Source Route failed          */
#define ICMP_NET_UNKNOWN        6
#define ICMP_HOST_UNKNOWN       7
#define ICMP_HOST_ISOLATED      8
#define ICMP_NET_ANO            9
#define ICMP_HOST_ANO           10
#define ICMP_NET_UNR_TOS        11
#define ICMP_HOST_UNR_TOS       12
#define ICMP_PKT_FILTERED       13	/* Packet filtered */
#define ICMP_PREC_VIOLATION     14	/* Precedence violation */
#define ICMP_PREC_CUTOFF        15	/* Precedence cut off */
#define NR_ICMP_UNREACH         15	/* instead of hardcoding immediate
					 * value */

/* ip option type codes */
#ifndef IPOPT_EOL
    #define IPOPT_EOL            0x00
#endif

#ifndef IPOPT_NOP
    #define IPOPT_NOP            0x01
#endif

#ifndef IPOPT_RR
    #define IPOPT_RR             0x07
#endif

#ifndef IPOPT_RTRALT
    #define IPOPT_RTRALT         0x14
#endif

#ifndef IPOPT_TS
    #define IPOPT_TS             0x44
#endif

#ifndef IPOPT_SECURITY
    #define IPOPT_SECURITY       0x82
#endif

#ifndef IPOPT_LSRR
    #define IPOPT_LSRR           0x83
#endif

#ifndef IPOPT_LSRR_E
    #define IPOPT_LSRR_E         0x84
#endif

#ifndef IPOPT_SATID
    #define IPOPT_SATID          0x88
#endif

#ifndef IPOPT_SSRR
    #define IPOPT_SSRR           0x89
#endif

/* tcp option codes */
#define TOPT_EOL                0x00
#define TOPT_NOP                0x01
#define TOPT_MSS                0x02
#define TOPT_WS                 0x03
#define TOPT_TS                 0x08
#ifndef TCPOPT_WSCALE
    #define TCPOPT_WSCALE           3	/* window scale factor (rfc1072) */
#endif
#ifndef TCPOPT_SACKOK
    #define	TCPOPT_SACKOK		4	/* selective ack ok (rfc1072) */
#endif
#ifndef TCPOPT_SACK
    #define	TCPOPT_SACK		5	/* selective ack (rfc1072) */
#endif
#ifndef TCPOPT_ECHO
    #define TCPOPT_ECHO             6	/* echo (rfc1072) */
#endif
#ifndef TCPOPT_ECHOREPLY
    #define TCPOPT_ECHOREPLY        7	/* echo (rfc1072) */
#endif
#ifndef TCPOPT_TIMESTAMP
    #define TCPOPT_TIMESTAMP        8	/* timestamps (rfc1323) */
#endif
#ifndef TCPOPT_CC
    #define TCPOPT_CC		11	/* T/TCP CC options (rfc1644) */
#endif
#ifndef TCPOPT_CCNEW
    #define TCPOPT_CCNEW		12	/* T/TCP CC options (rfc1644) */
#endif
#ifndef TCPOPT_CCECHO
    #define TCPOPT_CCECHO		13	/* T/TCP CC options (rfc1644) */
#endif

#define EXTRACT_16BITS(p) ((u_short) ntohs (*(u_short *)(p)))

#ifdef WORDS_MUSTALIGN

/* force word-aligned ntohl parameter */
    #define EXTRACT_32BITS(p)  ({ u_int32_t __tmp; memmove(&__tmp, (p), sizeof(u_int32_t)); (u_int32_t) ntohl(__tmp);})

#else

/* allows unaligned ntohl parameter - dies w/SIGBUS on SPARCs */
    #define EXTRACT_32BITS(p) ((u_int32_t) ntohl (*(u_int32_t *)(p)))

#endif				/* WORDS_MUSTALIGN */

/*  D A T A  S T R U C T U R E S  *********************************************/

/* Start Token Ring Data Structures */
#ifdef WIN32 /* Uhm, We need this. -- Mike */

/* LLC structure */
typedef struct _Trh_llc
{
    u_int8_t dsap;
    u_int8_t ssap;
    u_int8_t protid[3];
    u_int16_t ethertype;
}        Trh_llc;

/* RIF structure
 * Linux/tcpdump patch defines tokenring header in dump way, since not
 * every tokenring header with have RIF data... we define it separately, and
 * a bit more split up
 */

typedef struct _Trh_mr
{
#if defined(WORDS_BIGENDIAN)
    u_int16_t bcast:3, len:5, dir:1, lf:3, res:4;
#else
    u_int16_t len:5,        /* length of RIF field, including RC itself
                 * (bytes) */
    bcast:3,      /* broadcast indicator */
    res:4,        /* reserved */
    lf:3,     /* largest frame size */
    dir:1;        /* direction */

#endif
    u_int16_t rseg[8];
}       Trh_mr;


typedef struct _Trh_hdr
{
    u_int8_t ac;        /* access control field */
    u_int8_t fc;        /* frame control field */
    u_int8_t daddr[TR_ALEN];    /* src address */
    u_int8_t saddr[TR_ALEN];    /* dst address */
}        Trh_hdr;



#endif				/* WIN32 */
/* End Token Ring Data Structures */


/* Start FDDI Data Structures */

/* FDDI header is always this: -worm5er */
typedef struct _Fddi_hdr
{
    u_int8_t fc;        /* frame control field */
    u_int8_t daddr[FDDI_ALEN];  /* src address */
    u_int8_t saddr[FDDI_ALEN];  /* dst address */
}         Fddi_hdr;

/* splitting the llc up because of variable lengths of the LLC -worm5er */
typedef struct _Fddi_llc_saps
{
    u_int8_t dsap;
    u_int8_t ssap;
}              Fddi_llc_saps;

/* I've found sna frames have two addition bytes after the llc saps -worm5er */
typedef struct _Fddi_llc_sna
{
    u_int8_t ctrl_fld[2];
}             Fddi_llc_sna;

/* I've also found other frames that seem to have only one byte...  We're only
really intersted in the IP data so, until we want other, I'm going to say
the data is one byte beyond this frame...  -worm5er */
typedef struct _Fddi_llc_other
{
    u_int8_t ctrl_fld[1];
}               Fddi_llc_other;

/* Just like TR the ip/arp data is setup as such: -worm5er */
typedef struct _Fddi_llc_iparp
{
    u_int8_t ctrl_fld;
    u_int8_t protid[3];
    u_int16_t ethertype;
}               Fddi_llc_iparp;

/* End FDDI Data Structures */

typedef struct _EtherHdr
{
    u_int8_t ether_dst[6];
    u_int8_t ether_src[6];
    u_int16_t ether_type;

}         EtherHdr;

typedef struct _IPHdr
{
#if defined(WORDS_BIGENDIAN)
    u_int8_t ip_ver:4,      /* IP version */
    ip_hlen:4;     /* IP header length */
#else
    u_int8_t ip_hlen:4, ip_ver:4;
#endif
    u_int8_t ip_tos;        /* type of service */
    u_int16_t ip_len;       /* datagram length */
    u_int16_t ip_id;        /* identification  */
    u_int16_t ip_off;       /* fragment offset */
    u_int8_t ip_ttl;        /* time to live field */
    u_int8_t ip_proto;      /* datagram protocol */
    u_int16_t ip_csum;      /* checksum */
    struct in_addr ip_src;  /* source IP */
    struct in_addr ip_dst;  /* dest IP */

}      IPHdr;


typedef struct _TCPHdr
{
    u_int16_t th_sport;     /* source port */
    u_int16_t th_dport;     /* destination port */
    u_int32_t th_seq;       /* sequence number */
    u_int32_t th_ack;       /* acknowledgement number */
#ifdef WORDS_BIGENDIAN
    u_int8_t th_off:4,      /* data offset */
    th_x2:4;       /* (unused) */
#else
    u_int8_t th_x2:4, th_off:4;
#endif
    u_int8_t th_flags;
    u_int16_t th_win;       /* window */
    u_int16_t th_sum;       /* checksum */
    u_int16_t th_urp;       /* urgent pointer */

}       TCPHdr;


typedef struct _UDPHdr
{
    u_int16_t uh_sport;
    u_int16_t uh_dport;
    u_int16_t uh_len;
    u_int16_t uh_chk;

}       UDPHdr;


typedef struct _ICMPHdr
{
    u_int8_t type;
    u_int8_t code;
    u_int16_t csum;

}        ICMPHdr;


typedef struct _echoext
{
    u_int16_t id;
    u_int16_t seqno;

}        echoext;

typedef struct _ARPHdr
{
    u_int16_t ar_hrd;       /* format of hardware address   */
    u_int16_t ar_pro;       /* format of protocol address   */
    u_int8_t ar_hln;        /* length of hardware address   */
    u_int8_t ar_pln;        /* length of protocol address   */
    u_int16_t ar_op;        /* ARP opcode (command)         */
}       ARPHdr;



typedef struct _EtherARP
{
    ARPHdr ea_hdr;      /* fixed-size header */
    u_int8_t arp_sha[6];    /* sender hardware address */
    u_int8_t arp_spa[4];    /* sender protocol address */
    u_int8_t arp_tha[6];    /* target hardware address */
    u_int8_t arp_tpa[4];    /* target protocol address */
}         EtherARP;


typedef struct _Options
{
    u_int8_t code;
    u_int32_t len;
    u_int8_t *data;
}        Options;


typedef struct _Packet
{
    struct pcap_pkthdr *pkth;   /* BPF data */
    u_int8_t *pkt;      /* base pointer to the raw packet data */

    Fddi_hdr *fddihdr;      /* FDDI support headers */
    Fddi_llc_saps *fddisaps;
    Fddi_llc_sna *fddisna;
    Fddi_llc_iparp *fddiiparp;
    Fddi_llc_other *fddiother;

    Trh_hdr *trh;       /* Token Ring support headers */
    Trh_llc *trhllc;
    Trh_mr *trhmr;

    EtherHdr *eh;       /* standard TCP/IP/Ethernet/ARP headers */
    EtherARP *ah;
    IPHdr *iph, *orig_iph;      /* and orig. headers for ICMP_*_UNREACH family */
    TCPHdr *tcph, *orig_tcph;
    UDPHdr *udph, *orig_udph;
    ICMPHdr *icmph, *orig_icmph;

    echoext *ext;       /* ICMP echo extension struct */

    u_int8_t *data;     /* packet payload pointer */
    u_int16_t dsize;        /* packet payload size */

    u_int8_t frag_flag;     /* flag to indicate a fragmented packet */
    u_int16_t frag_offset;  /* fragment offset number */
    u_int8_t mf;            /* more fragments flag */
    u_int8_t df;            /* don't fragment flag */
    u_int8_t rf;                  /* IP reserved bit */

    u_int16_t sp;       /* source port (TCP/UDP) */
    u_int16_t dp;       /* dest port (TCP/UDP) */
    u_int16_t orig_sp;      /* source port (TCP/UDP) of original datagram */
    u_int16_t orig_dp;      /* dest port (TCP/UDP) of original datagram */
    u_int32_t caplen;

    Options ip_options[40]; /* ip options decode structure */
    u_int32_t ip_option_count;  /* number of options in this packet */
    u_char ip_lastopt_bad;  /* flag to indicate that option decoding was
                               halted due to a bad option */
    Options tcp_options[40];    /* tcp options decode struct */
    u_int32_t tcp_option_count;
    u_char tcp_lastopt_bad;  /* flag to indicate that option decoding was
                                halted due to a bad option */

    u_int8_t csum_flags;        /* checksum flags */

}       Packet;


/* this struct is for the alert socket code.... */
typedef struct _Alertpkt
{
    u_int8_t alertmsg[256]; /* variable.. */
    struct pcap_pkthdr pkth;
    u_int32_t dlthdr;       /* datalink header offset. (ethernet, etc.. ) */
    u_int32_t nethdr;       /* network header offset. (ip etc...) */
    u_int32_t transhdr;     /* transport header offset (tcp/udp/icmp ..) */
    u_int32_t data;
    u_int32_t val;  /* which fields are valid. (NULL could be
                                 * valids also) 
                                 */
    /* Packet struct --> was null */
#define NOPACKET_STRUCT 0x1
    /* no transport headers in packet */
#define NO_TRANSHDR	0x2
    u_int8_t pkt[SNAPLEN];
}         Alertpkt;




/*  P R O T O T Y P E S  ******************************************************/
void DecodeTRPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodeFDDIPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodeEthPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodePppPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodeSlipPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodeNullPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodeRawPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodeI4LRawIPPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
void DecodeI4LCiscoIPPkt(Packet *, struct pcap_pkthdr *, u_int8_t *);
#ifndef WIN32
void DecodeIP(u_int8_t *, u_int32_t, Packet *);
#else
void DecodeIP(u_int8_t *, const u_int32_t, Packet *);
#endif
void DecodeARP(u_int8_t *, u_int32_t, Packet *);
void DecodeIPV6(u_int8_t *, u_int32_t);
void DecodeIPX(u_int8_t *, u_int32_t);
#ifndef WIN32
void DecodeTCP(u_int8_t *, u_int32_t, Packet *);
void DecodeUDP(u_int8_t *, u_int32_t, Packet *);
void DecodeICMP(u_int8_t *, u_int32_t, Packet *);
#else
void DecodeTCP(u_int8_t *, const u_int32_t, Packet *);
void DecodeUDP(u_int8_t *, const u_int32_t, Packet *);
void DecodeICMP(u_int8_t *, const u_int32_t, Packet *);
#endif
void DecodeIPOptions(u_int8_t *, u_int32_t, Packet *);
void DecodeTCPOptions(u_int8_t *, u_int32_t, Packet *);
void DecodeIPOptions(u_int8_t *, u_int32_t, Packet *);

#endif				/* __DECODE_H__ */
