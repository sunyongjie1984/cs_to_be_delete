/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 2000,2001 Dragos Ruiu <dr@dursec.com/dr@v-wave.com>
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
 * spp_defrag v1.0b24 - 9 Nov 2000
 * 
 * Purpose: IP defragmentation preprocessor
 * Author:  Dragos Ruiu (dr@dursec.com/dr@v-wave.com)
 * Acknowledgements:    Code skeleton from diphen@agitation.net
 *                  There's a good paper about splay trees
 *                  by the developer and they rock.
 *                  Marty Roesch(roesch@md.prestige.net)
 *                  and Ron Gula(rgula@networksecuritywizards.com)
 *                  helped and did something few in the security
 *                  community do, shared knowledge.  Thanks.
 *
 * notes:
 *            This defragger implementation differs from the usual
 *            hash table and linked list technique in that it uses
 *            self caching splay trees. My hypothesis is that this
 *            provides substantial performance improvements.  I
 *            hope this module will be able to demonstrate or debunk
 *            this hypothesis. 
 * 
 * Splay Tree:
 * `A self-organizing data structure which uses rotations to move an
 *  accessed key to the root. This leaves recently accessed nodes near
 *  the top of the tree, making them very quickly searchable (Skiena 1997, p. 177). 
 * 
 * All splay tree operations run in O(log n) time _on_average_, where n is the
 * number of items in the tree, assuming you start with an empty tree.  Any single
 * operation can take Theta(n) time in the worst-case, but operations slower than
 * O(log n) time happen rarely enough that they don't affect the average.
 * 
 * Although 2-3-4 trees make a stronger guarantee (_every_ operation on a 2-3-4
 * tree takes O(log n) time), splay trees have several advantages.  Splay trees
 * are simpler and easier to program, and they can take advantage of circumstances
 * in which lots of find operations occur on a small number of items.  Because of
 * their simplicity, splay tree insertions and deletions are typically faster in
 * practice (sometimes by a constant factor, sometimes asymptotically).  Find
 * operations can be faster or slower, depending on circumstances.  Splay trees
 * really excel in applications where a fraction of the items are the targets of
 * most of the find operations, because they're designed to give especially fast
 * access to items that have been accessed recently.
 *
 * a good reference on splay trees is:
 * http://www.cs.umbc.edu/courses/undergraduate/341/fall98/frey/ClassNotes/Class17/splay.html
 * 
 * References 
 * Skiena, S. S. The Algorithm Design Manual. New York: Springer-Verlag, pp. 177 and 179, 1997. 
 * Sleator, D. and Tarjan, R. "Self-Adjusting Binary Search Trees." J. ACM 32, 652-686, 1985. 
 * Tarjan, R. Data Structures and Network Algorithms. Philadelphia, PA: SIAM Press, 1983. 
 * Wood, D. Data Structures, Algorithms, and Performance. Reading, MA: Addison-Wesley, 1993. 
 * 
 */


#include <pcap.h>
#include "decode.h"

/* Warning these are only valid for IPv4
   also note that these are still 
   in raw network order (see htons)  
   and these may fail on 64 bit machines 
*/
#define ID(x)       *((u_int16_t *)((u_int8_t *)x->iph+4))
#define PROTO(x)    *((u_int8_t *)x->iph+9)
#define SADDR(x)    *((u_int32_t *)((u_int8_t *)x->iph+12))
#define DADDR(x)    *((u_int32_t *)((u_int8_t *)x->iph+16))
#define DATA(x)     ((u_int8_t *)x->iph+20)

/* Uh-oh hope this wierdness is right :-) */
#define FOFF(x)     (u_int32_t)((x->frag_offset)<<3)
#define DF(x)       (x->df)
#define MF(x)       (x->mf)


/* fragment ID structure  */
typedef Packet *frag;

typedef struct tree_node Tree;
struct tree_node
{
    Tree * left, * right;
    frag key;
    int size;   /* maintained to be the number of nodes rooted here */
};

Tree *froot;

u_int32_t mem_locked;
u_int32_t mem_freed;


/*  These next declarations are for the fragment timeout and 
    and cleanup/sweeping process... time math routines are from
    an obscure piece of old code for a defunct video camera product
*/

#define FRAGTIMEOUTSEC      10      /* 10 seconds let's play safe for now */
#define FRAGTIMEOUTUSEC      0      /* 0 micro seconds                  */
#define FASTSWEEPLIM      16000000      /* memory use threhold for fast sweep */

long int fragmemuse;
int fragsweep;  /* the packet timeout / garbage collection stuff  */

typedef struct _timestruct
{
    u_int32_t tv_sec;
    u_int32_t tv_usec;
} time_struct;

time_struct fragtimeout;
time_struct last_frag_time;



/******Timestamp Routines******/

#define TIME_LT(x,y) (x tv_sec<(unsigned long)y tv_sec||(x tv_sec==(unsigned long)y tv_sec&&x tv_usec<(unsigned long)y tv_usec))

void addtime(time_struct *op1, time_struct *op2, time_struct *result)
{
    result->tv_usec = op1->tv_usec+op2->tv_usec;
    if(result->tv_usec > 999999)
    {
        result->tv_usec -= 1000000;
        op1->tv_sec++;
    }
    result->tv_sec = op1->tv_sec+op2->tv_sec;
}



/******Splay Tree Stuff******/

/* Function: fragcompare(i,j)                            */
/* This is the splay tree comparison.           */
/* Returns 1 if i>j; 0 if i=j; -1 if i<j;       */

int fragcompare(i,j)
frag i,j;
{
    if(!j)
    {
        if(!i)
            return(0);
        else
            return(1);
    }
    else
    {
        if(!i)
            return(-1);
    }
    if(SADDR(i) > SADDR(j))
    {
        return(1);
    }
    else if(SADDR(i) < SADDR(j))
    {
        return(-1);
    }
    else if(DADDR(i) > DADDR(j))
    {
        return(1);
    }
    else if(DADDR(i) < DADDR(j))
    {
        return(-1);
    }
    else if(PROTO(i) > PROTO(j))
    {
        return(1);
    }
    else if(PROTO(i) < PROTO(j))
    {
        return(-1);
    }
    else if(ID(i) > ID(j))
    {
        return(1);
    }
    else if(ID(i) < ID(j))
    {
        return(-1);
    }
    else if(FOFF(i) > FOFF(j))
    {
        return(1);
    }
    else if(FOFF(i) < FOFF(j))
    {
        return(-1);
    }
    else if(i->dsize > j->dsize)
    {
        return(1);
    }
    else if(i->dsize < j->dsize)
    {
        return(-1);
    }
    return(0);
}

/* This macro returns the size of a node.  Unlike "x->size",     */
/* it works even if x=NULL.  The test could be avoided by using  */
/* a special version of NULL which was a real node with size 0.  */

#define node_size(x) ((!x) ? 0 : ((x)->size))

/* Function: fragsplay(i, t)                              */
/* Splay using the key i (which may or may not be in the tree.) */
/* The starting root is t, size fields are maintained            */

Tree *fragsplay(frag i, Tree *t) 
{
    Tree N, *l, *r, *y;
    int comp, root_size, l_size, r_size;
    if(!t) return t;
    N.left = N.right = NULL;
    l = r = &N;
    root_size = node_size(t);
    l_size = r_size = 0;

    for(;;)
    {
        comp = fragcompare(i, t->key);
        if(comp < 0)
        {
            if(!t->left) break;
            if(fragcompare(i, t->left->key) < 0)
            {
                y = t->left;                           /* rotate right */
                t->left = y->right;
                y->right = t;
                t->size = node_size(t->left) + node_size(t->right) + 1;
                t = y;
                if(!t->left) break;
            }
            r->left = t;                               /* link right */
            r = t;
            t = t->left;
            r_size += 1+node_size(r->right);
        }
        else if(comp > 0)
        {
            if(!t->right) break;
            if(fragcompare(i, t->right->key) > 0)
            {
                y = t->right;                          /* rotate left */
                t->right = y->left;
                y->left = t;
                t->size = node_size(t->left) + node_size(t->right) + 1;
                t = y;
                if(!t->right) break;
            }
            l->right = t;                              /* link left */
            l = t;
            t = t->right;
            l_size += 1+node_size(l->left);
        }
        else
        {
            break;
        }
    }
    l_size += node_size(t->left);  /* Now l_size and r_size are the sizes of */
    r_size += node_size(t->right); /* the left and right trees we just built.*/
    t->size = l_size + r_size + 1;

    l->right = r->left = NULL;

    /* The following two loops correct the size fields of the right path  */
    /* from the left child of the root and the right path from the left   */
    /* child of the root.                                                 */
    for(y = N.right; y; y = y->right)
    {
        y->size = l_size;
        l_size -= 1+node_size(y->left);
    }
    for(y = N.left; y; y = y->left)
    {
        y->size = r_size;
        r_size -= 1+node_size(y->right);
    }

    l->right = t->left;                                /* assemble */
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;

    return t;
}

/* Function: Tree * fraginsert(frag i, Tree * t)             */
/* Insert frag i into the tree t, if it is not already there.       */
/* Return a pointer to the resulting tree.                         */

Tree *fraginsert(frag i, Tree * t)
{
    Tree * new_tree_node;
    if(t)
    {
        t = fragsplay(i,t);
        if(fragcompare(i, t->key)==0)
        {
            return t;  /* it's already there */
        }
    }

    new_tree_node = (Tree *) malloc (sizeof (Tree));
    fragmemuse += sizeof(Tree);
#ifdef DEBUG
    fprintf(stderr, "+++++++++++++++++++++++++\n");
    fprintf(stderr, "%p + Tree Alloc\n", new_tree_node);
    fprintf(stderr, "+++++++++++++++++++++++++\n");
    fflush(stderr);
    mem_locked += sizeof(Tree);
#endif

    if(!new_tree_node)
    {
        ErrorMessage("Ran out of space\n");
        return(t);
    }
    if(!t)
    {
        new_tree_node->left = new_tree_node->right = NULL;
    }
    else
        if(fragcompare(i, t->key) < 0)
    {
        new_tree_node->left = t->left;
        new_tree_node->right = t;
        t->left = NULL;
        t->size = 1+node_size(t->right);
    }
    else
    {
        new_tree_node->right = t->right;
        new_tree_node->left = t;
        t->right = NULL;
        t->size = 1+node_size(t->left);
    }
    new_tree_node->key = i;
    new_tree_node->size = 1 + node_size(new_tree_node->left) + node_size(new_tree_node->right);
    return new_tree_node;
}

/* Function: Tree * fragdelete(frag i, Tree *t)       */
/* Deletes i from the tree if it's there.               */
/* Return a pointer to the resulting tree.              */

Tree *fragdelete(frag i, Tree *t)
{
    Tree * x;
    int tsize;

    if(!t) return NULL;
    tsize = t->size;
    t = fragsplay(i,t);
    if(fragcompare(i, t->key) == 0)
    {               /* found it */
        if(!t->left)
        {
            x = t->right;
        }
        else
        {
            x = fragsplay(i, t->left);
            x->right = t->right;
        }

        if(t->key != NULL)
        {
#ifdef DEBUG
            fprintf(stderr, "------------------------\n");
            fprintf(stderr,"%p - p-struct Free\n", t->key);
            fprintf(stderr, "------------------------\n");
            fflush(stderr);        
            mem_freed += sizeof(Packet);
#endif
            fragmemuse -= sizeof(Packet);
            free(t->key);
        }

#ifdef DEBUG
        fprintf(stderr, "------------------------\n");
        fprintf(stderr,"%p - Tree Free\n", t);
        fprintf(stderr, "------------------------\n");
        fflush(stderr);        
        mem_freed += sizeof(Tree);
#endif
        fragmemuse -= sizeof(Tree);
        free(t);

        if(x)
        {
            x->size = tsize-1;
        }
        return x;
    }
    else
    {
        return t;                         /* It wasn't there */
    }
}

/* Function: Tree *fragfind_rank(int r, Tree *t)               */ 
/* Returns a pointer to the node in the tree with the given rank.  */
/* Returns NULL if there is no such node.                          */
/* Does not change the tree.  To guarantee logarithmic behavior,   */
/* the node found here should be splayed to the root.              */

Tree *fragfind_rank(int r, Tree *t)
{
    int lsize;
    if((r < 0) || (r >= node_size(t))) return NULL;
    for(; t != 0 ;)
    {
        lsize = node_size(t->left);
        if(r < lsize)
        {
            t = t->left;
        }
        else if(r > lsize)
        {
            r = r - lsize -1;
            t = t->right;
        }
        else
        {
            return t;
        }
    }
    return NULL;
}

/* Function: fragget_rank(t)                                 */
/* returns the rank of a tree element                           */

int fragget_rank(Tree *t)
{
    if(!t)
        return(0);
    return(node_size(t->left)+1);
}


/* Function: treedump(t)                                        */
/* dumps the tree in table form                                 */
void treedump(Tree *t)
{
    int loc;
    Tree *temp;
    fprintf(stdout,"Rank Ptr      ID       Lptr      Rptr \n");
    fprintf(stdout,"========================================== \n");
    for(loc = 0; loc < node_size(t); loc++)
    {
        temp = fragfind_rank(loc, t);
        fprintf(stdout,"%3d %p %d %p %p\n", loc, temp, ID(temp->key), temp->left, temp->right);
    }
    fflush(stdout);
}

/******Snort Stuff******/

/*
 * Function: SetupDefrag()
 * Purpose:
 * Registers the preprocessor keyword and initialization function
 * into the preprocessor list.  This is the function that gets called from
 * InitPreprocessors() in plugbase.c.
 * Arguments: None.
 * Returns: void function
 */
void SetupDefrag()
{
    RegisterPreprocessor("defrag", DefragInit);
}

/*
 * Function: DefragInit(u_char *)
 * Purpose:
 * Calls the argument parsing function, performs final setup on data
 * structs, links the preproc function into the function list.
 * Arguments: args => ptr to argument string
 * Returns: void function
 */
void DefragInit(u_char *args)
{
    AddFuncToPreprocList(PreprocDefrag);

    froot = NULL;  /* initialize empty fragment tree */
    fragmemuse = 0;      /* No memory yet */
    fragtimeout.tv_sec = FRAGTIMEOUTSEC;
    fragtimeout.tv_usec = FRAGTIMEOUTUSEC;
    fragsweep = 0;
}



/******Fragmentation Stuff******/

/* Function: fragaddrmatch(i,j)                         */
/* returns true if the fragments belong to the same reassembly      */
int fragaddrmatch(i,j)
frag i,j;
/* This is the comparison.                                   */
/* Returns 1 if i j have matching addresses else 0           */
{
#ifdef DEBUG
    printf("   =>  sip1 = 0x%X, sip2 = 0x%X\n", SADDR(i), SADDR(j));
    printf("   =>  dip1 = 0x%X, dip2 = 0x%X\n", DADDR(i), DADDR(j));
    printf("   =>  id1 = %d, id2 = %d\n", ID(i), ID(j));
    printf("   =>  proto1 = %d, proto2 = %d\n", PROTO(i), PROTO(j));
#endif    

    if(( SADDR(i) == SADDR(j) )
       && ( DADDR(i) == DADDR(j) )
       && ( ID(i) == ID(j) )
       && ( PROTO(i) == PROTO(j) ))
    {
        return(1);
    }

    return(0);
}

/*
 * Function: Packet *ReassembleIP(frag *froot)
 * Purpose: Generate a Packet * and pass it to ProcessPacket, then deallocate packet
 * Arguments: froot - root of the tree containing the last packet of the frame
 * Returns: tree with reassembled fragments deleted
 */
Tree *ReassembleIP(Tree *froot)
{
    Packet *p;
    int writecount = 0;
    char *np;
    u_char *tmp;
    u_int psize;
    int fragrank;
    unsigned int overhead, moreoverhead;
    IPHdr slowarisfix;

    psize = (froot->key)->dsize + FOFF(froot->key); /* last frag is at top of tree */

#ifdef DEBUG
    printf("psize calculated to be %d bytes (last payload: %d)(last offset: %d)\n", psize, (froot->key)->dsize, FOFF(froot->key));
#endif        

    /* we've got to have a packet at least as large as an ICMP header */
    if(psize < 4)
    {
        ErrorMessage("[!] ERROR: Defrag plugin is fucked up, calculated packet size too small\n");
    }

    /* hopefully moreoverhead here finds out about all the wierd MAC sizes like FDDI and ATM */
    moreoverhead = (char*)froot->key->iph - (char*)froot->key->pkt;
    overhead = (char*)froot->key->pkt - (char*)froot->key->pkth;
    /* Linux fix code */
    if(overhead < sizeof(struct pcap_pkthdr) || overhead > sizeof( struct pcap_pkthdr) + 2)
    {
        overhead = sizeof(struct pcap_pkthdr) + 2;
    }

#ifdef DEBUG
    printf("Overhead = %d, struct size = %d\n", overhead, sizeof(struct pcap_pkthdr));
#endif        

    p = (Packet *)malloc(sizeof(Packet));
    fragmemuse += sizeof(Packet);

#ifdef DEBUG
    fprintf(stderr, "+++++++++++++++++++++++++\n");
    fprintf(stderr, "%p + p-struct Alloc\n", p);
    fprintf(stderr, "+++++++++++++++++++++++++\n");
    fflush(stderr);
    mem_locked += sizeof(Packet);
#endif

    if(!p)
    {
        ErrorMessage("[!] ERROR: Unable to allocate memory for fragment rebuild!\n");
        return NULL;
    }

    /* MFR: Why are we copying this header if we're in the reassembly phase?
     *  Why not use the original and modify its data in place?
     */
    memcpy(p, froot->key, sizeof(Packet));

    /* SEMI BOGUS - setting up ethernet time header - required by one of the
     * decode routines - we set the timestamp equal to froot (last fragment)
     * note also that our bogus reassembledgrams may not have the bpf header
     * contiguous and datagram access through this pointer is suspect. Been warned.
     */
    p->pkth = (struct pcap_pkthdr *)malloc(psize + overhead + moreoverhead + sizeof(IPHdr) + 32);
    fragmemuse += (psize + overhead + moreoverhead + sizeof(IPHdr) + 32);

#ifdef DEBUG
    fprintf(stderr, "+++++++++++++++++++++++++\n");
    fprintf(stderr, "%p + frankenpacket Alloc\n", p->pkth);
    fprintf(stderr, "+++++++++++++++++++++++++\n");
    fflush(stderr);
    mem_locked += sizeof(psize+overhead+moreoverhead+sizeof(IPHdr)+32);
#endif

    if(!p->pkth)
    {
        ErrorMessage("[!] ERROR: Unable to allocate memory for fragment rebuild!\n");
#ifdef DEBUG
        fprintf(stderr, "------------------------\n");
        fprintf(stderr, "%p - p-struct Free\n", p);
        fprintf(stderr, "------------------------\n");
        fflush(stderr);
        mem_freed += sizeof(Packet);
#endif
        fragmemuse -= sizeof(Packet);
        free(p);
        return NULL;
    }

    p->iph = (IPHdr *)((u_char*)p->pkth + overhead + moreoverhead);
    p->pkt = (u_char*)p->iph - moreoverhead;

    /*
     * Now copy the header and fragments into the newly-allocated buffer,
     * reconstructing the packet chunk by chunk. Current algorithm is first 
     * write to an area wins, play with splay order to change.
     * we start from the last fragment and work back....
     */

    /* fill in packet header bpf header first*/
    memcpy(p->pkth, froot->key->pkth, overhead); 

    /* then the mac junk, split into two copies for Linux 
     * non-contiguous headers 
     */
    memcpy((char*)p->pkth + overhead, froot->key->pkt, moreoverhead); 

    /*
     * then the IP header just to be paranoid for debugging because in the
     * real world we would do these in one copy
     */
    tmp = (u_char *) froot->key->iph;
    memcpy(p->iph, tmp, sizeof(IPHdr)); 

    p->pkth->caplen = psize + overhead + moreoverhead + sizeof(IPHdr);
    p->pkth->len = p->pkth->caplen;

    /*
     * Clear the more fragments bit, and set the length in the ip header
     * (in network byte order).
     */
    p->iph->ip_len = htons((unsigned short)psize);
    p->iph->ip_off = 0;
    p->frag_flag = 0;

    fragrank = fragget_rank(froot);

#ifdef DEBUG
    printf("fragrank = %d, froot = %p, fragaddrmatch = %d\n", fragrank, froot, 
           fragaddrmatch(p, froot->key));
#endif        

    while(fragrank > 0 && froot && fragaddrmatch(p,froot->key))
    {
        if(FOFF(froot->key) + froot->key->dsize <= psize)
        {
#ifdef DEBUG
            printf("Writing %d bytes from %p at %p\n", froot->key->dsize, 
                   DATA(froot->key), (u_int8_t *) DATA(p)+FOFF(froot->key));        
#endif            
            memcpy((u_int8_t *)DATA(p)+FOFF(froot->key), DATA(froot->key), 
                   froot->key->dsize);

            writecount += froot->key->dsize;

#ifdef DEBUG
            printf("reassembly writecount: %d\n", writecount);
#endif                        
        }
        else
        {
#ifdef DEBUG
            printf("Overflow attack in rebuild!\n");
#endif                        
            /*(*AlertFunc)(p, "Fragmentation Overflow Attack");*/
            CallAlertFuncs(p, "Fragmentation Overflow Attack", NULL);
        }

        /* clear the fragment store of the frag that was just put into the
         * reassembly
         */
        if(froot)
        {
            /*fragmemuse -= froot->key->pkth->caplen + sizeof(Packet);*/
            np = (char *)froot->key->pkth;  /* address for free later */

            fragrank = fragget_rank(froot);

            if(np)
            {
#ifdef DEBUG
                fprintf(stderr, "------------------------\n");
                fprintf(stderr, "%p - packet Free\n", np);
                fprintf(stderr, "------------------------\n");
                fflush(stderr);
                mem_freed += ((struct pcap_pkthdr *)np)->caplen + overhead + 20;
#endif                
                /* this fragment was an element of a rebuilt packet */
                pc.rebuild_element++;
                fragmemuse -= (((struct pcap_pkthdr *)np)->caplen + overhead + 20);
                free(np);
            }

            froot = fragdelete(froot->key, froot);
        }
    }

    memcpy(&slowarisfix, p->iph, sizeof(IPHdr));
    p->iph = &slowarisfix; 

    /* and now some jolt2proofing */
    if(psize > 8192)  /* only kick in for monstergrams */
    {
        if((unsigned int)writecount > (psize>>1))      /*packets have to be half full for us to look at them */
        {
            if(p)
            {
#ifdef DEBUG
                printf("Fragmented packet rebuilt, processing...\n");
                printf("BPF header (%d bytes):\n", overhead);
                PrintNetData(stdout,(char *) p->pkth, overhead);
                ClearDumpBuf();
                printf("Packet dump (%d bytes):\n", p->pkth->caplen);
                PrintNetData(stdout, (char *)p->pkt, p->pkth->caplen);
                ClearDumpBuf();
#endif                                    
                /* keep stats for the packet counter struct -MFR */
                pc.rebuilt_frags++;  /* Marty... Huh?? --dr */
                ProcessPacket(NULL,p->pkth, p->pkt);
            }
        }
        else
        {
            /*(*AlertFunc)(p, "Mostly Empty Fragmented Packet Discarded!");*/
            CallAlertFuncs(p, "Incomplete Packet Fragments Discarded", NULL);
        }
    }
    else
    {
        if(p)
        {
#ifdef DEBUG
            printf("Fragmented packet rebuilt, processing...\n");
            printf("BPF header (%d bytes):\n", overhead);
            ClearDumpBuf();
            PrintNetData(stdout,(char *) p->pkth, overhead);
            ClearDumpBuf();
            printf("Packet dump (%d bytes):\n", p->pkth->caplen);
            PrintNetData(stdout,(char *) p->pkt, p->pkth->caplen);
            ClearDumpBuf();
#endif                            
            /* keep stats for the packet counter struct -MFR */
            pc.rebuilt_frags++;  /* Marty... Huh?? --dr */
            ProcessPacket(NULL, p->pkth, p->pkt);
        }
    }

#ifdef DEBUG
    fprintf(stderr, "------------------------\n");
    fprintf(stderr, "%p - frankenpacket Free\n",(p->pkth));
    fprintf(stderr, "%p - p-struct Free\n", p);
    fprintf(stderr, "------------------------\n");
    fflush(stderr);
    treedump(froot);
    mem_freed += psize+overhead+moreoverhead+sizeof(IPHdr)+32;
    mem_freed += sizeof(Packet);
#endif    
    fragmemuse -= (psize+overhead+moreoverhead+sizeof(IPHdr)+32+sizeof(Packet));
    free(p->pkth);      /* set the frankensteingram free.... */
    free(p);

    return(froot);
}

/*
 * Function: PreprocDefrag(Packet *)
 * Purpose:
 * Driver function for the IP defragmentation preprocessor.
 * Arguments: p => pointer to the current packet data struct
 * Returns: void function
 */
void PreprocDefrag(Packet *p)
{
    Packet *packet_copy;
    time_struct timecheck;
    Tree *found;
    struct pcap_pkthdr *freetemp;
    int overhead;
    int cap;
    u_char *tmp;

#ifdef DEBUG
    printf("fragments =>\n");
    printf("    mem used: %u\n", mem_locked);
    printf("    mem freed: %u\n", mem_freed);
    printf("    fragmemuse: %u\n", fragmemuse);
#endif    

    if(!p || !p->pkth || !p->pkt)
    {
        if(pv.verbose_flag)
        {
            ErrorMessage("%s\n","Garbage Packet with Null Pointer discarded!");
        }

        return;
    }

    /* check to make sure the IP header exists and that 
     * there isn't a bad IP checksum
     */
    if(!p->iph || (p->csum_flags & CSE_IP))
    {
        return;      
    }

    if(p->frag_flag)
    {  /* heads up, live fragments inbound  */
        overhead = (char*)p->pkt - (char*)p->pkth; /* +4 mystery points */
        /* Linux fix code */
        if(overhead < 1 || overhead > sizeof(struct pcap_pkthdr) + 2)
            overhead = sizeof(struct pcap_pkthdr) + 2;

        packet_copy = malloc(sizeof(Packet));
        fragmemuse += sizeof(Packet);

#ifdef DEBUG
        fprintf(stderr, "++++++++++++++++++++++++\n");
        fprintf(stderr, "%p + p-struct Alloc (%d bytes) ", packet_copy, sizeof(Packet));

        fflush(stderr);
        mem_locked += sizeof(Packet);
#endif

        if(!packet_copy)
        {
            ErrorMessage("[!] ERROR: Cannot allocate fragment buffer(usage 0x%X)\n",fragmemuse);
            return;
        }

        /* cleared by MFR, accounted for below */
        /*fragmemuse += sizeof(Packet);*/

        memcpy(packet_copy, p, sizeof(Packet));
        cap = p->pkth->caplen + overhead;
        tmp = calloc(cap + 20, sizeof(char));
        fragmemuse += (cap + 20);
        packet_copy->pkth = (struct pcap_pkthdr *) tmp;

#ifdef DEBUG
        fprintf(stderr, " && %p + packet Alloc\n", packet_copy->pkth);
        fprintf(stderr, "++++++++++++++++++++++++\n");
        fflush(stderr);
        mem_locked += cap+20;
#endif
        if(!packet_copy->pkth)
        {
            ErrorMessage("[!] ERROR: Cannot allocate fragment buffer(usage %X)\n",fragmemuse);
            return;
        }

        packet_copy->pkt = (u_char*)packet_copy->pkth + overhead;
        packet_copy->iph = (IPHdr*)((u_char*)packet_copy->pkt + ((u_char*)p->iph - (u_char*)p->pkt));

        /* cleared by MFR, accounted for below */
        /*fragmemuse += p->pkth->caplen + overhead;*/
        last_frag_time.tv_sec = p->pkth->ts.tv_sec;
        last_frag_time.tv_usec = p->pkth->ts.tv_usec;

        /* we do this with two memcopies to cope with Linux non-contiguous bpf headers */
        memcpy(packet_copy->pkth, p->pkth, overhead);
        memcpy(packet_copy->pkt, p->pkt, p->pkth->caplen);
        froot = fraginsert(packet_copy, froot); 

        /* now check if we have to reassemble anything... */
        if(!MF(p))
            froot = ReassembleIP(froot);

        /* OK now check for a fragment timeout - sweeping the clutter away :-) */
        if(froot)
        {
            if(++fragsweep > node_size(froot)+1)
                fragsweep = 1;
            found = fragfind_rank(fragsweep,froot);
            if(found)
            {
                froot = fragsplay(found->key, froot);
                addtime((time_struct *)&(froot->key->pkth->ts), &fragtimeout, &timecheck);
                if(TIME_LT(timecheck. , p->pkth->ts.))
                {
#ifdef DEBUGg                    
                    fprintf(stderr, "Generic timeout cleanup in progress...\n");
#endif
                    /* cleared by MFR */
                    /*fragmemuse -= froot->key->pkth->caplen + sizeof(Packet);*/
                    freetemp = froot->key->pkth;
#ifdef DEBUG    
                    fprintf(stderr, "------------------------\n");
                    fprintf(stderr, "%p - packet Free\n", freetemp);
                    fprintf(stderr, "------------------------\n");
                    fflush(stderr);
                    mem_freed += freetemp->caplen + overhead + 20;
#endif
                    fragmemuse -= freetemp->caplen + overhead + 20;
                    free(freetemp);
                    froot = fragdelete(froot->key, froot);
                    fragsweep--;
                    pc.frag_timeout++;
                }
            }

            /* and now do the whole thing again if we are being a memory hog */
            if(froot && fragmemuse > FASTSWEEPLIM)
            {
                if(++fragsweep > node_size(froot))
                    fragsweep = 1;
                found = fragfind_rank(fragsweep,froot);
                if(found)
                {
                    froot = fragsplay(found->key, froot);
                    addtime((time_struct *)&(froot->key->pkth->ts), &fragtimeout, &timecheck);
                    if(TIME_LT(timecheck. , p->pkth->ts. ))
                    {
#ifdef DEBUG
                        fprintf(stderr, "Frag memory overcommitted, cleanup in progress...\n");
#endif
                        /*fragmemuse -= froot->key->pkth->caplen + sizeof(Packet);*/
                        freetemp = froot->key->pkth;
#ifdef DEBUG
                        fprintf(stderr, "------------------------\n");
                        fprintf(stderr, "%p - packet Free\n", freetemp);
                        fprintf(stderr, "------------------------\n");
                        fflush(stderr);
                        mem_freed += freetemp->caplen + overhead + 20;
#endif
                        fragmemuse -= freetemp->caplen + overhead + 20;
                        free(freetemp);
                        froot = fragdelete(froot->key, froot);
                        fragsweep--;
                        pc.frag_incomp++;
                    }
                }
            }
        }
    }

    /* check to see if we've gotten any frags in the last n seconds
     * and if we haven't, start clearing out old data
     *
     * this works best with a realistic timeout value...
     */
    if(froot)
    {
        /* add the timeout value to the last fragment time */
        addtime(&last_frag_time, &fragtimeout, &timecheck);

        /* check the global timeout vs. the latest packet's timestamp */
        if(TIME_LT(timecheck. , p->pkth->ts. ))
        {
#ifdef DEBUG            
            fprintf(stderr, "Packets have timedout, cleaning [%d, %d]...\n", fragsweep, node_size(froot));
#endif
            if(++fragsweep > node_size(froot))
            {
                fragsweep = 1;
            }

            found = fragfind_rank(fragsweep,froot);   

            if(found)
            {
                /* is it really necessary to calculate this for every packet?
                 * can't we just calculate it at init time?
                 */
                overhead = (char*)p->pkt - (char*)p->pkth; 

                /* Linux fix code */
                if(overhead < 1 || overhead > sizeof(struct pcap_pkthdr) + 2)
                {
                    overhead = sizeof(struct pcap_pkthdr) + 2;       
                }

                froot = fragsplay(found->key, froot);
                /* cleared by MFR */
                /*fragmemuse -= froot->key->pkth->caplen + sizeof(Packet);*/
                freetemp = froot->key->pkth;
#ifdef DEBUG
                fprintf(stderr, "------------------------\n");
                fprintf(stderr, "%p - packet Free\n", freetemp);
                fprintf(stderr, "------------------------\n");
                fflush(stderr);
                mem_freed += freetemp->caplen + overhead + 20;
                treedump(froot);
#endif
                fragmemuse -= freetemp->caplen + overhead + 20;
                free(freetemp);
                froot = fragdelete(froot->key, froot);
                fragsweep--;
                pc.frag_timeout++;
            }
#ifdef DEBUG            
            else
            {
                fprintf(stderr, "Nothing found to clean...\n");
            }
#endif
        }
    }

    return;
}



