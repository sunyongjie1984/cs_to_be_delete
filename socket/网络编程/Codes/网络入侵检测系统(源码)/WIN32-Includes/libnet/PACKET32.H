/*
 * Copyright (c) 1999, 2000
 *	Politecnico di Torino.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the Politecnico
 * di Torino, and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef __PACKET32
#define __PACKET32

#include "ntddpack.h"
#include "ntddndis.h"
#include <winsock.h>

//working modes
#define MODE_CAPT 0
#define MODE_STAT 1

//ioctls
#define	 pBIOCSETBUFFERSIZE 9592
#define	 pBIOCSETF 9030
#define  pBIOCGSTATS 9031
#define	 pBIOCSRTIMEOUT 7416
#define	 pBIOCSMODE 7412
#define	 pBIOCSWRITEREP 7413


//Network type structure

typedef struct NetType
{
	UINT LinkType;
	UINT LinkSpeed;
}NetType;


// Alignment macros.  Packet_WORDALIGN rounds up to the next 
// even multiple of Packet_ALIGNMENT. 
#define Packet_ALIGNMENT sizeof(int)
#define Packet_WORDALIGN(x) (((x)+(Packet_ALIGNMENT-1))&~(Packet_ALIGNMENT-1))


//some definitions from libpcap
#ifndef BPF_MAJOR_VERSION

struct bpf_program {
	UINT bf_len;
	struct bpf_insn *bf_insns;
};
struct bpf_insn {
	USHORT	code;
	UCHAR 	jt;
	UCHAR 	jf;
	int k;
};
struct bpf_stat {
	UINT bs_recv;		/* number of packets received */
	UINT bs_drop;		/* number of packets dropped */
};

struct bpf_hdr {
	struct timeval	bh_tstamp;	/* time stamp */
	UINT	bh_caplen;	/* length of captured portion */
	UINT	bh_datalen;	/* original length of packet */
	USHORT		bh_hdrlen;	/* length of bpf header (this struct
					   plus alignment padding) */
};

#endif

#define        DOSNAMEPREFIX   TEXT("Packet_")
#define        MAX_LINK_NAME_LENGTH   64
#define        NMAX_PACKET 65535  

typedef struct _ADAPTER  { 
						   HANDLE hFile;
                           TCHAR  SymbolicLink[MAX_LINK_NAME_LENGTH];
						   int NumWrites;
						 }  ADAPTER, *LPADAPTER;

typedef struct _PACKET {  
						  HANDLE       hEvent;
                          OVERLAPPED   OverLapped;
                          PVOID        Buffer;
                          UINT         Length;
//                          PVOID        Next;
						  UINT         ulBytesReceived;
						  BOOLEAN      bIoComplete;
						}  PACKET, *LPPACKET;

#ifdef __cplusplus
extern "C" {
#endif

BOOLEAN PacketSetNumWrites(LPADAPTER AdapterObject,int nwrites);
BOOLEAN PacketSetMode(LPADAPTER AdapterObject,int mode);
BOOLEAN PacketSetMaxLookaheadsize (LPADAPTER AdapterObject);
BOOLEAN PacketSetReadTimeout(LPADAPTER AdapterObject,int timeout);
BOOLEAN PacketSetBpf(LPADAPTER AdapterObject,struct bpf_program *fp);
BOOLEAN PacketGetStats(LPADAPTER AdapterObject,struct bpf_stat *s);
BOOLEAN PacketSetBuff(LPADAPTER AdapterObject,int dim);
BOOLEAN PacketGetNetType (LPADAPTER AdapterObject,NetType *type);
LPADAPTER PacketOpenAdapter(LPTSTR AdapterName);
BOOLEAN PacketSendPacket(LPADAPTER AdapterObject,LPPACKET pPacket,BOOLEAN Sync);
LPPACKET PacketAllocatePacket(void);
LPPACKET PacketAllocateNPacket(UINT n);
VOID PacketInitPacket(LPPACKET lpPacket,PVOID  Buffer,UINT  Length);
VOID PacketFreePacket(LPPACKET lpPacket);
BOOLEAN PacketResetAdapter(LPADAPTER AdapterObject);
BOOLEAN PacketWaitPacket(LPADAPTER AdapterObject,LPPACKET lpPacket);
BOOLEAN PacketReceiveNPacket(LPADAPTER AdapterObject,LPPACKET headLPacket,UINT n,UINT length,BYTE* buffer,BOOLEAN Sync);
BOOLEAN PacketReceivePacket(LPADAPTER AdapterObject,LPPACKET lpPacket,BOOLEAN Sync);
VOID PacketCloseAdapter(LPADAPTER lpAdapter);
BOOLEAN PacketSetHwFilter(LPADAPTER AdapterObject,ULONG Filter);
ULONG PacketGetAdapterNames(PTSTR pStr,PULONG  BufferSize);
BOOLEAN PacketRequest(LPADAPTER  AdapterObject,BOOLEAN Set,PPACKET_OID_DATA  OidData);
VOID PacketSetNextPacket(LPPACKET lpPacket, LPPACKET next);
VOID PacketSetLengthBuffer(LPPACKET lpPacket, UINT dim);
VOID PacketSetLengthPacket(LPPACKET lpPacket, UINT numBytes);
LPPACKET PacketGetNextPacket(LPPACKET lpPacket);

#ifdef __cplusplus
}
#endif 

#endif //__PACKET32
