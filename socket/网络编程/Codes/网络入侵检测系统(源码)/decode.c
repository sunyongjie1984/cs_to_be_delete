/* $Id: decode.c,v 1.26 2001/01/26 16:40:44 roesch Exp $ */

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

#include "decode.h"

/*
 * Function: DecodeEthPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decode those fun loving ethernet packets, one at a time!
 *
 * Arguments: p => pointer to the decoded packet struct
 *            user => Utility pointer (unused)
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeEthPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    u_int32_t pkt_len;      /* suprisingly, the length of the packet */
    u_int32_t cap_len;      /* caplen value */

    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;

    /* set the lengths we need */
    pkt_len = pkthdr->len;  /* total packet length */
    cap_len = pkthdr->caplen;   /* captured packet length */

    if(snaplen < pkt_len)
        pkt_len = cap_len;

#ifdef DEBUG
    printf("Packet!\n");
    printf("caplen: %lu    pktlen: %lu\n", (unsigned long)cap_len, (unsigned long)pkt_len);
#endif

    /* do a little validation */
    if(p->pkth->caplen < ETHERNET_HEADER_LEN)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("Captured data length < Ethernet header length! (%d bytes)\n", p->pkth->caplen);
        }
        return;
    }
    /* lay the ethernet structure over the packet data */
    p->eh = (EtherHdr *) pkt;

#ifdef DEBUG
    ErrorMessage("%X   %X\n", *p->eh->ether_src, *p->eh->ether_dst);
#endif

    /* grab out the network type */
    switch(ntohs(p->eh->ether_type))
    {
        case ETHERNET_TYPE_IP:
#ifdef DEBUG
            printf("IP datagram size calculated to be %lu bytes\n",(unsigned long)(cap_len - ETHERNET_HEADER_LEN));
#endif
            DecodeIP(p->pkt + ETHERNET_HEADER_LEN, cap_len - ETHERNET_HEADER_LEN, p);
            /* DecodeIP(p->pkt+ETHERNET_HEADER_LEN, cap_len, p); */
            return;

        case ETHERNET_TYPE_ARP:
        case ETHERNET_TYPE_REVARP:
            pc.arp++;
            if(pv.showarp_flag)
            {
                DecodeARP(p->pkt + ETHERNET_HEADER_LEN, cap_len - ETHERNET_HEADER_LEN, p);
            }
            return;

        case ETHERNET_TYPE_IPV6:
            pc.ipv6++;
            if(pv.showipv6_flag)
                DecodeIPV6(p->pkt + ETHERNET_HEADER_LEN, (cap_len - ETHERNET_HEADER_LEN));
            return;

        case ETHERNET_TYPE_IPX:
            pc.ipx++;
            if(pv.showipx_flag)
                DecodeIPX(p->pkt + ETHERNET_HEADER_LEN, (cap_len - ETHERNET_HEADER_LEN));
            return;

        default:
            pc.other++;
            return;
    }

    return;
}




/*
 * Function: DecodeNullPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decoding on loopback devices.
 *
 * Arguments: p => pointer to decoded packet struct
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeNullPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    u_int32_t len;
    u_int32_t cap_len;

    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;

    len = pkthdr->len;
    cap_len = pkthdr->caplen;

#ifdef DEBUG
    printf("Packet!\n");
#endif

    /* do a little validation */
    if(cap_len < NULL_HDRLEN)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("NULL header length < captured len! (%d bytes)\n",
                          cap_len);
        }

        return;
    }

    DecodeIP(p->pkt + NULL_HDRLEN, cap_len - NULL_HDRLEN, p);
}

/*
 * Function: DecodeTRPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decode Token Ring packets!
 *
 * Arguments: p=> pointer to decoded packet struct
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeTRPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    u_int32_t pkt_len;      /* suprisingly, the length of the packet */
    u_int32_t cap_len;      /* caplen value */
    u_int32_t dataoff;      /* data offset is variable here */


    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;


    /* set the lengths we need */
    pkt_len = pkthdr->len;  /* total packet length */
    cap_len = pkthdr->caplen;   /* captured packet length */

    if(snaplen < pkt_len)
        pkt_len = cap_len;

#ifdef DEBUG
    printf("Packet!\n");
    printf("caplen: %lu    pktlen: %lu\n",(unsigned long)cap_len,(unsigned long) pkt_len);
#endif

    /* do a little validation */
    if(p->pkth->caplen < TR_HLEN)
    {
        if(pv.verbose_flag)
            ErrorMessage("Captured data length < Token Ring header length! (%d < %d bytes)\n", p->pkth->caplen, TR_HLEN);
        return;
    }
    /* lay the tokenring header structure over the packet data */
    p->trh = (Trh_hdr *) pkt;
/*
 * according to rfc 1042:
    The presence of a Routing Information Field is indicated by the Most
    Significant Bit (MSB) of the source address, called the Routing
    Information Indicator (RII).  If the RII equals zero, a RIF is
    not present.  If the RII equals 1, the RIF is present.
    ..
    However the MSB is already zeroed by this moment, so there's no
    real way to figure out whether RIF is presented in packet, so we are
    doing some tricks to find IPARP signature..
*/
    /*
     * first I assume that we have single-ring network with no RIF
     * information presented in frame
     */

    p->trhllc = (Trh_llc *) (pkt + sizeof(Trh_hdr));


    if(p->trhllc->dsap != IPARP_SAP && p->trhllc->ssap != IPARP_SAP)
    {
        /*
         * DSAP != SSAP != 0xAA .. either we are having frame which doesn't
         * carry IP datagrams or has RIF information present. We assume
         * lattest ...
         */
        p->trhmr = (Trh_mr *) (pkt + sizeof(Trh_hdr));
        p->trhllc = (Trh_llc *) (pkt + sizeof(Trh_hdr) + p->trhmr->len);
        dataoff = sizeof(Trh_hdr) + p->trhmr->len + sizeof(Trh_llc);
    }
    else
    {
        p->trhllc = (Trh_llc *) (pkt + sizeof(Trh_hdr));
        dataoff = sizeof(Trh_hdr) + sizeof(Trh_llc);
    }

    /*
     * ideally we would need to check both SSAP, DSAP, and protoid fields: IP
     * datagrams and ARP requests and replies are transmitted in standard
     * 802.2 LLC Type 1 Unnumbered Information format, control code 3, with
     * the DSAP and the SSAP fields of the 802.2 header set to 170, the
     * assigned global SAP value for SNAP [6].  The 24-bit Organization Code
     * in the SNAP is zero, and the remaining 16 bits are the EtherType from
     * Assigned Numbers [7] (IP = 2048, ARP = 2054). .. but we would check
     * SSAP and DSAP and assume this would be enough to trust.
     */
    if(p->trhllc->dsap != IPARP_SAP && p->trhllc->ssap != IPARP_SAP)
    {
#ifdef DEBUG
        ErrorMessage("DSAP and SSAP arent set to SNAP\n");
#endif
        p->trhllc = NULL;
        return;
    }
    pkt_len -= dataoff;
    cap_len -= dataoff;

    switch(htons(p->trhllc->ethertype))
    {
        case ETHERNET_TYPE_IP:
#ifdef DEBUG
            printf("Decoding IP\n");
#endif
            DecodeIP(p->pkt + dataoff, cap_len, p);
            return;

        case ETHERNET_TYPE_ARP:
        case ETHERNET_TYPE_REVARP:
#ifdef DEBUG
            printf("Decoding ARP\n");
#endif
            pc.arp++;

            return;

        default:
#ifdef DEBUG
            printf("Unknown network protocol: %d\n", htons(p->trhllc->ethertype));
#endif
            pc.other++;
            return;
    }

    return;
}


/*
 * Function: DecodeFDDIPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Mainly taken from CyberPsycotic's Token Ring Code -worm5er
 *
 * Arguments: p => pointer to decoded packet struct
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeFDDIPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    u_int32_t pkt_len;      /* length of the packet */
    u_int32_t cap_len;      /* capture length variable */
    u_int32_t dataoff;      /* data offset is variable here */

    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;

    pkt_len = pkthdr->len;
    cap_len = pkthdr->caplen;

    if(snaplen < pkt_len)
    {
        pkt_len = cap_len;
    }
#ifdef DEBUG
    printf("Packet!\n");
    printf("caplen: %lu    pktlen: %lu\n",(unsigned long) cap_len,(unsigned long) pkt_len);
#endif

    /* Bounds checking (might not be right yet -worm5er) */
    if(p->pkth->caplen < FDDI_MIN_HLEN)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("Captured data length < FDDI header length! "
                         "(%d %d bytes)\n", p->pkth->caplen, FDDI_MIN_HLEN);
            return;
        }
    }
    /* let's put this in as the fddi header structure */
    p->fddihdr = (Fddi_hdr *) pkt;

    p->fddisaps = (Fddi_llc_saps *) (pkt + sizeof(Fddi_hdr));

    /* First we'll check and see if it's an IP/ARP Packet... */
    /* Then we check to see if it's a SNA packet */
    /*
     * Lastly we'll declare it none of the above and just slap something
     * generic on it to discard it with (I know that sucks, but heck we're
     * only looking for IP/ARP type packets currently...  -worm5er
     */
    if((p->fddisaps->dsap == FDDI_DSAP_IP) && (p->fddisaps->ssap == FDDI_SSAP_IP))
    {
        p->fddiiparp = (Fddi_llc_iparp *) (pkt + sizeof(Fddi_hdr) +
                                           sizeof(Fddi_llc_saps));

        dataoff = sizeof(Fddi_hdr) + sizeof(Fddi_llc_saps) +
                  sizeof(Fddi_llc_iparp);
    }
    else if((p->fddisaps->dsap == FDDI_DSAP_SNA) &&
            (p->fddisaps->ssap == FDDI_SSAP_SNA))
    {
        p->fddisna = (Fddi_llc_sna *) (pkt + sizeof(Fddi_hdr) +
                                       sizeof(Fddi_llc_saps));
        dataoff = sizeof(Fddi_hdr) + sizeof(Fddi_llc_saps) +
                  sizeof(Fddi_llc_sna);
    }
    else
    {
        p->fddiother = (Fddi_llc_other *) (pkt + sizeof(Fddi_hdr) +
                                           sizeof(Fddi_llc_other));

        dataoff = sizeof(Fddi_hdr) + sizeof(Fddi_llc_saps) +
                  sizeof(Fddi_llc_other);
    }

    /*
     * Now let's see if we actually care about the packet... If we don't,
     * throw it out!!!
     */
    if((p->fddisaps->dsap != FDDI_DSAP_IP) && (p->fddisaps->ssap != FDDI_SSAP_IP))
    {
#ifdef DEBUG
        ErrorMessage("This FDDI Packet isn't an IP/ARP packet...\n");
#endif
        return;
    }
    pkt_len -= dataoff;
    cap_len -= dataoff;

    switch(htons(p->fddiiparp->ethertype))
    {
        case ETHERNET_TYPE_IP:
#ifdef DEBUG
            printf("Decoding IP\n");
#endif
            DecodeIP(p->pkt + dataoff, cap_len, p);

            return;

        case ETHERNET_TYPE_ARP:
        case ETHERNET_TYPE_REVARP:
#ifdef DEBUG
            printf("Decoding ARP\n");
#endif
            pc.arp++;

            return;

        default:
#ifdef DEBUG
            printf("Unknown network protocol: %d\n",
                   htons(p->fddiiparp->ethertype));
#endif
            pc.other++;

            return;
    }

    return;
}




/*
 * Function: DecodePppPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decoded PPP traffic
 *
 * Arguments: p => pointer to decoded packet struct 
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodePppPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    static int had_vj = 0;
    u_int32_t len;
    u_int32_t cap_len;
    struct ppp_header *ppphdr;

    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;
    ppphdr = (struct ppp_header *)pkt;

    len = pkthdr->len;
    cap_len = pkthdr->caplen;

#ifdef DEBUG
    printf("Packet!\n");
#endif

    /* do a little validation */
    if(cap_len < PPP_HDRLEN)
    {
        ErrorMessage("PPP header length < captured len! (%d bytes)\n",
                     cap_len);
        return;
    }
    /* 
     * We only handle uncompressed packets. Handling VJ compression would mean
     * to implement a PPP state machine.
     */
    switch (ntohs(ppphdr->protocol)) {
    case PPP_VJ_COMP:
	    if (!had_vj)
		    ErrorMessage("PPP link seems to use VJ compression, cannot handle compressed packets!\n");
	    had_vj = 1;
	    break;
    case PPP_VJ_UCOMP:
	    /* VJ compression modifies the protocol field. It must be set
	     * to tcp (only TCP packets can be VJ compressed) */
	    if(cap_len < PPP_HDRLEN + IP_HEADER_LEN)
	    {
		    ErrorMessage("PPP VJ min packet length > captured len! (%d bytes)\n",
				 cap_len);
		    return;
	    }
	    ((IPHdr *)(p->pkt + PPP_HDRLEN))->ip_proto = IPPROTO_TCP;
	    /* fall through */
    case PPP_IP:
	    DecodeIP(p->pkt + PPP_HDRLEN, cap_len - PPP_HDRLEN, p);
	    break;
    case PPP_IPX:
	    DecodeIPX(p->pkt + PPP_HDRLEN, cap_len - PPP_HDRLEN);
	    break;
    }
}


/*
 * Function: DecodeSlipPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decode SLIP traffic
 *
 * Arguments: p => pointer to decoded packet struct 
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeSlipPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    u_int32_t len;
    u_int32_t cap_len;

    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;

    len = pkthdr->len;
    cap_len = pkthdr->caplen;

#ifdef DEBUG
    printf("Packet!\n");
#endif

    /* do a little validation */
    if(cap_len < SLIP_HEADER_LEN)
    {
        ErrorMessage("SLIP header length < captured len! (%d bytes)\n",
                     cap_len);
        return;
    }
    DecodeIP(p->pkt + SLIP_HEADER_LEN, cap_len - SLIP_HEADER_LEN, p);
}



/*
 * Function: DecodeRawPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decodes packets coming in raw on layer 2, like PPP.  Coded and
 *          in by Jed Pickle (thanks Jed!) and modified for a few little tweaks
 *          by me.
 *
 * Arguments: p => pointer to decoded packet struct 
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeRawPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;

#ifdef DEBUG
    printf("Packet!\n");
#endif

    DecodeIP(pkt, p->pkth->caplen, p);

    return;
}



/*
 * Function: DecodeI4LRawIPPkt(Packet *, char *, struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decodes packets coming in raw on layer 2, like PPP.  Coded and
 *          in by Jed Pickle (thanks Jed!) and modified for a few little tweaks
 *          by me.
 *
 * Arguments: p => pointer to decoded packet struct
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeI4LRawIPPkt(Packet * p, struct pcap_pkthdr * pkthdr, u_int8_t * pkt)
{
    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;

#ifdef DEBUG
    printf("Packet!\n");
#endif

    DecodeIP(pkt + 2, p->pkth->len - 2, p);

    return;
}



/*
 * Function: DecodeI4LCiscoIPPkt(Packet *, char *, 
 *                               struct pcap_pkthdr*, u_int8_t*)
 *
 * Purpose: Decodes packets coming in raw on layer 2, like PPP.  Coded and
 *          in by Jed Pickle (thanks Jed!) and modified for a few little tweaks
 *          by me.
 *
 * Arguments: p => pointer to decoded packet struct 
 *            user => Utility pointer, unused
 *            pkthdr => ptr to the packet header
 *            pkt => pointer to the real live packet data
 *
 * Returns: void function
 */
void DecodeI4LCiscoIPPkt(Packet *p, struct pcap_pkthdr *pkthdr, u_int8_t *pkt)
{
    bzero((char *) p, sizeof(Packet));

    p->pkth = pkthdr;
    p->pkt = pkt;

#ifdef DEBUG
    printf("Packet!\n");
#endif

    DecodeIP(pkt + 4, p->pkth->caplen - 4, p);

    return;
}



/*
 * Function: DecodeIP(u_int8_t *, const u_int32_t, Packet *)
 *
 * Purpose: Decode the IP network layer
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *            p   => pointer to the packet decode struct
 *
 * Returns: void function
 */
void DecodeIP(u_int8_t * pkt, const u_int32_t len, Packet * p)
{
    u_int32_t ip_len;       /* length from the start of the ip hdr to the
                 * pkt end */
    u_int32_t hlen;             /* ip header length */
    u_int16_t csum;             /* checksum */


    /* lay the IP struct over the raw data */
    p->iph = (IPHdr *) pkt;

#ifdef DEBUG
    printf("ip header starts at: %p, length is %lu\n", p->iph, (unsigned long) len);
#endif

    /* do a little validation */
    if(len < IP_HEADER_LEN)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("IP header truncated! (%d bytes)\n", len);
        }
        p->iph = NULL;

        return;
    }

    /*
     * with datalink DLT_RAW it's impossible to differ ARP datagrams from IP.
     * So we are just ignoring non IP datagrams
     */
    if(p->iph->ip_ver != 4)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("[!] WARNING: Not IPv4 datagram! ([ver: 0x%x][len: 0x%x])\n", p->iph->ip_ver, p->iph->ip_len);
        }
        if(pv.logbin_flag) LogBin(p, NULL, NULL);

        p->iph = NULL;
        pc.discards++;

        return;
    }

    /* set the IP datagram length */
    ip_len = ntohs(p->iph->ip_len);

    /* set the IP header length */
    hlen = p->iph->ip_hlen << 2;

    if (ip_len != len)
    {
        if (ip_len > len) 
        {
#ifdef DEBUG
            if (pv.verbose_flag)
                 ErrorMessage("[!] WARNING: IP Len field is %d bytes bigger than captured length.\n"
                              "    (ip.len: %lu, cap.len: %lu)\n",
                             ip_len - len, ip_len, len);
#endif
            ip_len = len;
        }
        else
        {
#ifdef DEBUG
            if (pv.verbose_flag)
                 ErrorMessage("[!] WARNING: IP Len field is %d bytes smaller than captured length.\n"
                              "    (ip.len: %lu, cap.len: %lu)\n",
                             len - ip_len, ip_len, len);
#endif
       
        }
    }

    if(ip_len < hlen)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("[!] WARNING: IP dgm len (%d bytes) < IP hdr len (%d bytes), packet discarded\n", ip_len, hlen);
        }
        if(pv.logbin_flag) LogBin(p, NULL, NULL);

        p->iph = NULL;

        pc.discards++;

        return;
    }
        
 
    csum = checksum((u_short *)p->iph, hlen, (u_short *)NULL, 0);

    if(csum)
    {
        p->csum_flags |= CSE_IP;

#ifdef DEBUG
        printf("Bad IP checksum\n");
#endif
    }
#ifdef DEBUG
    else
    {
        printf("IP Checksum: OK\n");
    }
#endif

    /* test for IP options */
    if(p->iph->ip_hlen > 5)
    {
        DecodeIPOptions((pkt + IP_HEADER_LEN), hlen - IP_HEADER_LEN, p);
    }
    else
    {
        p->ip_option_count = 0;
    }

    /* set the remaining packet length */
    ip_len -= hlen;

    /* check for fragmented packets */
    p->frag_offset = ntohs(p->iph->ip_off);

    /* get the values of the reserved, more fragments and don't fragment flags */
    p->rf = (p->frag_offset & 0x8000) >> 15;
    p->df = (p->frag_offset & 0x4000) >> 14;
    p->mf = (p->frag_offset & 0x2000) >> 13;

    /* mask off the high bits in the fragment offset field */
    p->frag_offset &= 0x1FFF;

    if(p->frag_offset || p->mf)
    {
        /* set the packet fragment flag */
        p->frag_flag = 1;
        pc.frags++;
    }

    /* if this packet isn't a fragment */
    if(!(p->frag_flag))
    {
        /* set the packet fragment flag */
        p->frag_flag = 0;

#ifdef DEBUG
        printf("IP header length: %lu\n", (unsigned long)hlen);
#endif

        switch(p->iph->ip_proto)
        {
            case IPPROTO_TCP:
                pc.tcp++;
                DecodeTCP(pkt + hlen, ip_len, p);
                ClearDumpBuf();
                return;

            case IPPROTO_UDP:
                pc.udp++;
                DecodeUDP(pkt + hlen, ip_len, p);
                ClearDumpBuf();
                return;

            case IPPROTO_ICMP:
                pc.icmp++;
                DecodeICMP(pkt + hlen, ip_len, p);
                ClearDumpBuf();
                return;

            default:
                pc.other++;
                p->data = pkt + hlen;
                p->dsize = ip_len;
                ClearDumpBuf();
                return;
        }
    }
    else
    {
        /* set the payload pointer and payload size */
        p->data = pkt + hlen;
        p->dsize = ip_len;

    }
}
/*
 * Function: DecodeIPOnly(u_int8_t *, const u_int32_t, Packet *)
 *
 * Purpose: Decode the IP network layer but not recurse
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *            p   => pointer to dummy packet decode struct
 *
 * Returns: void function
 */
int DecodeIPOnly(u_int8_t * pkt, const u_int32_t len, Packet * p)
{
    u_int32_t ip_len;       /* length from the start of the ip hdr to the
                 * pkt end */
    u_int32_t hlen;             /* ip header length */

    /* lay the IP struct over the raw data */
    p->iph = (IPHdr *) pkt;

#ifdef DEBUG
    printf("DecodeIPOnly: ip header starts at: %p, length is %lu\n", p->iph, (unsigned long) len);
#endif

    /* do a little validation */
    if(len < IP_HEADER_LEN)
    {
        ErrorMessage("ICMP Unreachable IP short header (%d bytes)\n", len);
        p->iph = NULL;
        return(0);
    }

    /*
     * with datalink DLT_RAW it's impossible to differ ARP datagrams from IP.
     * So we are just ignoring non IP datagrams
     */
    if(p->iph->ip_ver != 4)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("[!] WARNING: ICMP Unreachable not IPv4 datagram ([ver: 0x%x][len: 0x%x])\n", p->iph->ip_ver, p->iph->ip_len);
        }

        p->iph = NULL;

        return(0);
    }

    /* set the IP datagram length */
    ip_len = ntohs(p->iph->ip_len);

    /* set the IP header length */
    hlen = p->iph->ip_hlen << 2;

    if(len < hlen)
    {
        ErrorMessage("[!] WARNING: ICMP Unreachable IP len (%d bytes) < IP hdr len (%d bytes), packet discarded\n", ip_len, hlen);
        p->iph = NULL;

        return(0);
    }

    /* don't try to recalculate the checksum of the encapsulated packet, 
     * it will almost always be wrong and we already tested it on the 
     * packet that spawned this UNREACH packet -MFR
     */
    /*csum = checksum((u_short *)p->iph, hlen, (u_short *)NULL, 0);

    if(csum)
    {
        p->csum_flags |= CSE_IP;

#ifdef DEBUG
        printf("Bad IP checksum\n");
#endif
    }
#ifdef DEBUG
    else
    {
        printf("IP Checksum: OK\n");
    }
#endif*/

    /* we probably aren't real interested in IP options, we already put them
     * out for the originating packet so it'd probably be best to advance the 
     * packet pointer up to the next layer if it's available -MFR
     */
    /* test for IP options */
    /*if(p->iph->ip_hlen > 5)
    {
        DecodeIPOptions((pkt + IP_HEADER_LEN), hlen - IP_HEADER_LEN, p);
    }
    else
    {*/
    p->ip_option_count = 0;
    /*}*/

    /* set the remaining packet length */
    ip_len = len - hlen;

    /* check for fragmented packets */
    p->frag_offset = ntohs(p->iph->ip_off);

    /* get the values of the reserved, more fragments and don't fragment flags */
    p->rf = (p->frag_offset & 0x8000) >> 15;
    p->df = (p->frag_offset & 0x4000) >> 14;
    p->mf = (p->frag_offset & 0x2000) >> 13;

    /* mask off the high bits in the fragment offset field */
    p->frag_offset &= 0x1FFF;

    if(p->frag_offset || p->mf)
    {
        /* set the packet fragment flag */
        p->frag_flag = 1;

        /* set the payload pointer and payload size */
        p->data = pkt + hlen;
        p->dsize = ip_len;
    }
    else
    {
        p->frag_flag = 0;

#ifdef DEBUG
        printf("ICMP Unreachable IP header length: %lu\n", (unsigned long)hlen);
#endif
        switch(p->iph->ip_proto)
        {
            case IPPROTO_TCP: /* decode the interesting part of the header */
                if(ip_len > 4)
                {
                    p->tcph =(TCPHdr *)(pkt + hlen);
                    /* stuff more data into the printout data struct */
                    p->sp = ntohs(p->tcph->th_sport);
                    p->dp = ntohs(p->tcph->th_dport);
                }

                break;

            case IPPROTO_UDP:
                if(ip_len > 4)
                {
                    p->udph = (UDPHdr *)(pkt + hlen);
                    /* fill in the printout data structs */
                    p->sp = ntohs(p->udph->uh_sport);
                    p->dp = ntohs(p->udph->uh_dport);
                }

                break;
        }
    }

    return(1);
}



/*
 * Function: DecodeTCP(u_int8_t *, const u_int32_t, Packet *)
 *
 * Purpose: Decode the TCP transport layer
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *            p   => Pointer to packet decode struct
 *
 * Returns: void function
 */
void DecodeTCP(u_int8_t * pkt, const u_int32_t len, Packet * p)
{
    struct pseudoheader       /* pseudo header for TCP checksum calculations */
    {
        u_int32_t sip, dip;   /* IP addr */
        u_int8_t  zero;       /* checksum placeholder */
        u_int8_t  protocol;   /* protocol number */
        u_int16_t tcplen;     /* tcp packet length */
    };
    u_int32_t hlen;            /* TCP header length */
    u_short csum;              /* checksum */
    struct pseudoheader ph;    /* pseudo header declaration */


    if(len < 20)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("[!] WARNING: TCP packet (len = %d) cannot contain 20 byte header\n", len);
        }
        if(pv.logbin_flag) LogBin(p, NULL, NULL);
	p->tcph = NULL;
	pc.discards++;
    }

    /* lay TCP on top of the data cause there is enough of it! */
    p->tcph = (TCPHdr *) pkt;

    /* multiply the payload offset value by 4 */
    hlen = p->tcph->th_off << 2;

#ifdef DEBUG
    printf("TCP th_off is %d, passed len is %lu\n", p->tcph->th_off, (unsigned long)len);
#endif

    if(hlen < 20)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("[!] WARNING: TCP Data Offset %d < 5 \n",
			    p->tcph->th_off);
        }
        if(pv.logbin_flag) LogBin(p, NULL, NULL);
	hlen = 20;
    }

    /* setup the pseudo header for checksum calculation */
    ph.sip = (u_int32_t)(p->iph->ip_src.s_addr);
    ph.dip = (u_int32_t)(p->iph->ip_dst.s_addr);
    ph.zero = 0;
    ph.protocol = p->iph->ip_proto;
    ph.tcplen = htons((unsigned short)len);

    /* calculate the checksum */
    csum = checksum((u_int16_t *)&ph, 12, (u_int16_t *)(p->tcph), len);

    if(csum)
    {
        p->csum_flags |= CSE_TCP;
#ifdef DEBUG
        printf("Bad TCP checksum\n");
#endif
    }
#ifdef DEBUG
    else
    {
        printf("TCP Checksum: OK\n");
    }
#endif

#ifdef DEBUG
    printf("tcp header starts at: %p\n", p->tcph);
#endif

    /* if options are present, decode them */
    if(hlen > 20)
    {
#ifdef DEBUG
        printf("%lu bytes of tcp options....\n", (unsigned long)(hlen - 20));
#endif
        DecodeTCPOptions((u_int8_t *) (pkt + 20), (hlen - 20), p);
    }
    else
    {
        p->tcp_option_count = 0;
    }

    /* stuff more data into the printout data struct */
    p->sp = ntohs(p->tcph->th_sport);
    p->dp = ntohs(p->tcph->th_dport);

    /* set the data pointer and size */
    p->data = (u_int8_t *) (pkt + hlen);

    if(hlen < len)
    {
        p->dsize = len - hlen;
    }
    else
    {
        p->dsize = 0;
    }
}


/*
 * Function: DecodeUDP(u_int8_t *, const u_int32_t, Packet *)
 *
 * Purpose: Decode the UDP transport layer
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *            p   => pointer to decoded packet struct  
 *
 * Returns: void function
 */
void DecodeUDP(u_int8_t * pkt, const u_int32_t len, Packet * p)
{
    struct pseudoheader 
    {
        u_int32_t sip, dip;
        u_int8_t  zero;
        u_int8_t  protocol;
        u_int16_t udplen;
    };
    u_short csum;
    struct pseudoheader ph;

    if(len < sizeof(UDPHdr))
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("[!] WARNING: Truncated UDP header (%d bytes)\n", len);
        }
        if(pv.logbin_flag) LogBin(p, NULL, NULL);

        p->udph = NULL;
        pc.discards++;

        return;
    }

    /* set the ptr to the start of the UDP header */
    p->udph = (UDPHdr *) pkt;

    /* look at the UDP checksum to make sure we've got a good packet */
    ph.sip = (u_int32_t)(p->iph->ip_src.s_addr);
    ph.dip = (u_int32_t)(p->iph->ip_dst.s_addr);
    ph.zero = 0;
    ph.protocol = p->iph->ip_proto;
    ph.udplen = htons((unsigned short)len);

    csum = checksum((u_short *)&ph, 12, (u_short *)(p->udph), len);

    if(csum)
    {
        p->csum_flags |= CSE_UDP;

#ifdef DEBUG
        printf("Bad UDP Checksum\n");
#endif
    }
#ifdef DEBUG
    else
    {
        printf("UDP Checksum: OK\n");
    }
#endif

#ifdef DEBUG
    printf("UDP header starts at: %p\n", p->udph);
#endif

    /* fill in the printout data structs */
    p->sp = ntohs(p->udph->uh_sport);
    p->dp = ntohs(p->udph->uh_dport);

    p->data = (u_int8_t *) (pkt + UDP_HEADER_LEN);

    if((len - UDP_HEADER_LEN) > 0)
    {
        p->dsize = len - UDP_HEADER_LEN;
    }
    else
    {
        p->dsize = 0;
    }

}



/*
 * Function: DecodeICMP(u_int8_t *, const u_int32_t, Packet *)
 *
 * Purpose: Decode the ICMP transport layer
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *            p   => pointer to the decoded packet struct
 *
 * Returns: void function
 */
void DecodeICMP(u_int8_t * pkt, const u_int32_t len, Packet * p)
{
    u_int16_t csum;

    if(len < sizeof(ICMPHdr))
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("[!] WARNING: Truncated ICMP header(%d bytes)\n", len);
        }
        if(pv.logbin_flag) LogBin(p, NULL, NULL);

        p->icmph = NULL;
        pc.discards++;

        return;
    }

    /* set the header ptr first */
    p->icmph = (ICMPHdr *) pkt;

    csum = checksum((u_int16_t *)p->icmph, len, NULL, 0);

    if(csum)
    {
        p->csum_flags |= CSE_ICMP;

#ifdef DEBUG
        printf("Bad ICMP Checksum\n");
#endif
    }
#ifdef DEBUG
    else
    {
        printf("ICMP Checksum: OK\n");
    }
#endif

    p->dsize = len - ICMP_HEADER_LEN;
    p->data = pkt + ICMP_HEADER_LEN;

#ifdef DEBUG
    printf("ICMP type: %d   code: %d\n", p->icmph->code, p->icmph->type);
#endif
    switch(p->icmph->type)
    {
        case ICMP_ECHOREPLY:
            /* setup the pkt id ans seq numbers */
            p->ext = (echoext *) (pkt + ICMP_HEADER_LEN);
            p->dsize -= sizeof(echoext);
            p->data += sizeof(echoext);
            break;
        case ICMP_ECHO:
            /* setup the pkt id ans seq numbers */
            p->ext = (echoext *) (pkt + ICMP_HEADER_LEN);
            p->dsize -= 4;      /* add the size of the echo ext to the data
                         * ptr and subtract it from the data size */
            p->data += 4;
            break;
        case ICMP_DEST_UNREACH:
            {
                Packet orig_p;

                /* if unreach packet is smaller than expected! */
                if(len < 16)
                {
                    if(pv.verbose_flag)
                        ErrorMessage("[!] WARNING: Truncated ICMP-UNREACH header (%d bytes)\n", len);
                    /* if it is less than 8 we are in trouble */
                    if(len < 8)
                        break;
                }

                bzero((char *)&orig_p, sizeof(Packet));
                orig_p.caplen = len - 8;
                if(DecodeIPOnly(pkt + 8, orig_p.caplen, &orig_p))
                {

                    /*
                     * that's probably what we need to know about an original
                     * datagram
                     */
                    p->orig_iph = orig_p.iph;
                    p->orig_tcph = orig_p.tcph;
                    p->orig_udph = orig_p.udph;
                    p->orig_icmph = orig_p.icmph;
                    p->orig_sp = orig_p.sp;
                    p->orig_dp = orig_p.dp;
                }
                else
                {
                    if(pv.logbin_flag) LogBin(p, NULL, NULL);
                }
                break;
            }
    }

    return;
}



/*
 * Function: DecodeARP(u_int8_t *, u_int32_t, Packet *)
 *
 * Purpose: Decode ARP stuff
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *            p   => pointer to decoded packet struct
 *
 * Returns: void function
 */
void DecodeARP(u_int8_t * pkt, u_int32_t len, Packet * p)
{
    p->ah = (EtherARP *) pkt;

    if(len < sizeof(EtherARP))
    {
        if(pv.verbose_flag)
            printf("Truncated packet\n");
        if(pv.logbin_flag) LogBin(p, NULL, NULL);

        pc.discards++;
        return;
    }

    return;
}


/*
 * Function: DecodeIPV6(u_int8_t *, u_int32_t)
 *
 * Purpose: Just like IPX, it's just for counting.
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *
 * Returns: void function
 */
void DecodeIPV6(u_int8_t *pkt, u_int32_t len)
{
    if(pv.verbose_flag)
    {
        puts("IPV6 packet");
    }
    return;
}


/*
 * Function: DecodeIPX(u_int8_t *, u_int32_t)
 *
 * Purpose: Well, it doesn't do much of anything right now...
 *
 * Arguments: pkt => ptr to the packet data
 *            len => length from here to the end of the packet
 *
 * Returns: void function
 *
 */
void DecodeIPX(u_int8_t *pkt, u_int32_t len)
{
    if(pv.verbose_flag)
    {
        puts("IPX packet");
    }
    return;
}


/*
 * Function: DecodeTCPOptions(u_int8_t *, u_int32_t, Packet *)
 *
 * Purpose: Fairly self explainatory name, don't you think?
 *
 * Arguments: o_list => ptr to the option list
 *            o_len => length of the option list
 *            p     => pointer to decoded packet struct
 *
 * Returns: void function
 */
void DecodeTCPOptions(u_int8_t *o_list, u_int32_t o_len, Packet *p)
{
    u_int8_t *option_ptr;
    u_int32_t bytes_processed;
    u_int32_t current_option;
    u_char done = 0;

    option_ptr = o_list;
    bytes_processed = 0;
    current_option = 0;

    while((bytes_processed < o_len) && (current_option < 40) && !done)
    {
        p->tcp_options[current_option].code = *option_ptr;

        switch(*option_ptr)
        {
            case TCPOPT_NOP:
            case TCPOPT_EOL:
                if(*option_ptr == TCPOPT_EOL)
                    done = 1;
                    
                p->tcp_options[current_option].len = 0;
                p->tcp_options[current_option].data = NULL;
                bytes_processed++;
                current_option++;
                option_ptr++;

                break;

            case TCPOPT_SACKOK:
                p->tcp_options[current_option].len = 0;
                p->tcp_options[current_option].data = NULL;
                bytes_processed += 2;
                option_ptr += 2;
                current_option++;
                break;

            case TCPOPT_WSCALE:
                p->tcp_options[current_option].len = 3;
                p->tcp_options[current_option].data = option_ptr + 2;
                option_ptr += 3;
                bytes_processed += 3;
                current_option++;
                break;

            default:
                p->tcp_options[current_option].len = *(option_ptr + 1);

                if(p->tcp_options[current_option].len > 40)
                {
                    p->tcp_options[current_option].len = 40;
                }
                else if( p->tcp_options[current_option].len == 0)
                {
                    /* got a bad option, we're all done */
                    done = 1;
                    p->tcp_lastopt_bad = 1;
                }

                p->tcp_options[current_option].data = option_ptr + 2;
                option_ptr += p->tcp_options[current_option].len;
                bytes_processed += p->tcp_options[current_option].len;
                current_option++;
                break;
        }
    }

    if(bytes_processed > o_len)
    {
        p->tcp_options[current_option].len =
        p->tcp_options[current_option].len - (bytes_processed - o_len);
        /*
         * in reality shouldn't happen until we got the option type and len
         * on the packet header boundary.. then we just drop last option (as
         * it is corrupted anyway).
         */
        if(p->tcp_options[current_option].len < 0)
            current_option--;
    }

    p->tcp_option_count = current_option;

    return;
}


/*
 * Function: DecodeIPOptions(u_int8_t *, u_int32_t, Packet *)
 *
 * Purpose: Once again, a fairly self-explainatory name
 *
 * Arguments: o_list => ptr to the option list
 *            o_len => length of the option list
 *            p     => pointer to decoded packet struct
 *
 * Returns: void function
 */
void DecodeIPOptions(u_int8_t *o_list, u_int32_t o_len, Packet *p)
{
    u_int8_t *option_ptr;
    u_int32_t bytes_processed;
    u_int32_t current_option;
    u_char done = 0;

    option_ptr = o_list;
    bytes_processed = 0;
    current_option = 0;

#ifdef DEBUG
    printf("Decoding %d bytes of IP options\n", o_len);
#endif

    while((bytes_processed < o_len) && (current_option < 40) && !done)
    {
#ifdef DEBUG
        printf("    => %d bytes processed\n", bytes_processed);
#endif

        p->ip_options[current_option].code = *option_ptr;

        switch(*option_ptr)
        {
            case IPOPT_RTRALT:
            case IPOPT_NOP:
            case IPOPT_EOL:
                /* if we hit an EOL, we're done */
                if(*option_ptr == IPOPT_EOL)
                    done = 1;

                p->ip_options[current_option].len = 0;
                p->ip_options[current_option].data = NULL;
                bytes_processed++;
                current_option++;
                option_ptr++;

                break;

            default:
                p->ip_options[current_option].len = *(option_ptr + 1);

                if(p->ip_options[current_option].len > 40)
                {
                    p->ip_options[current_option].len = 40;
                }
                else if(p->ip_options[current_option].len == 0)
                {
                    /* 
                     * this shouldn't happen, indicates a bad option list 
                     * so we bail
                     */
                     done = 1;
                     p->ip_lastopt_bad = 1;
                }

                p->ip_options[current_option].data = option_ptr + 2;
                option_ptr += p->ip_options[current_option].len;
#ifdef DEBUG
                printf("        => Adding %d bytes\n", 
                       p->ip_options[current_option].len);
#endif
                bytes_processed += p->ip_options[current_option].len;
                current_option++;
                break;

        }
    }

#ifdef DEBUG
    printf("    => %d total bytes processed\n", bytes_processed);
#endif

    if(bytes_processed > o_len)
    {
        p->ip_options[current_option].len =
        p->ip_options[current_option].len - (bytes_processed - o_len);
        /*
         * in reality shouldn't happen until we got the option type and len
         * on the packet header boundary.. then we just drop last option (as
         * it is corrupted anyway).
         */
        if(p->ip_options[current_option].len < 0)
            current_option--;
    }

    p->ip_option_count = current_option;

    return;
}
