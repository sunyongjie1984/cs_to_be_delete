/* $Id: sp_ip_fragbits.c,v 1.2 2001/01/02 08:06:01 roesch Exp $ */
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

/* Snort Detection Plugin Source File for IP Fragment Bits plugin */

/* sp_ip_fragbits 
 * 
 * Purpose:
 *
 * Check the fragmentation bits of the IP header for set values.  Possible
 * bits are don't fragment (DF), more fragments (MF), and reserved (RB).
 *
 * Arguments:
 *   
 * The keyword to reference this plugin is "fragbits".  Possible arguments are
 * D, M and R for DF, MF and RB, respectively.  
 *
 * Effect:
 *
 * Inidicates whether any of the specified bits have been set.
 *
 * Comments:
 *
 * Ofir Arkin should be a little happier now. :)
 *
 */

#include "sp_ip_fragbits.h"

extern char *file_name;  /* this is the file name from rules.c, generally used
                            for error messages */

extern int file_line;    /* this is the file line number from rules.c that is
                            used to indicate file lines for error messages */

u_int16_t bitmask;

/****************************************************************************
 * 
 * Function: SetupFragBits()
 *
 * Purpose: Assign the keyword to the rules parser.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 ****************************************************************************/
void SetupFragBits()
{
    /* map the keyword to an initialization/processing function */
    RegisterPlugin("fragbits", FragBitsInit);

#ifdef DEBUG
    printf("Plugin: FragBits Setup\n");
#endif
}


/****************************************************************************
 * 
 * Function: FragBitsInit(char *, OptTreeNode *)
 *
 * Purpose: Initialize the detection function and parse the arguments.
 *
 * Arguments: data => rule arguments/data
 *            otn => pointer to the current rule option list node
 *            protocol => protocol that must be specified to use this plugin
 *
 * Returns: void function
 *
 ****************************************************************************/
void FragBitsInit(char *data, OptTreeNode *otn, int protocol)
{
    /* allocate the data structure and attach it to the
       rule's data struct list */
    otn->ds_list[PLUGIN_FRAG_BITS] = (FragBitsData *) calloc(sizeof(FragBitsData), sizeof(char));

    /* this is where the keyword arguments are processed and placed into the 
       rule option's data structure */
    ParseFragBits(data, otn);

    /* 
     * set the bitmask needed to mask off the IP offset field 
     * in the check function
     */
    bitmask = htons(0xE000);

    /* finally, attach the option's detection function to the rule's 
       detect function pointer list */
    AddOptFuncToList(CheckFragBits, otn);
}



/****************************************************************************
 * 
 * Function: ParseFragBits(char *, OptTreeNode *)
 *
 * Purpose: This is the function that is used to process the option keyword's
 *          arguments and attach them to the rule's data structures.
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: void function
 *
 ****************************************************************************/
void ParseFragBits(char *data, OptTreeNode *otn)
{
    char *fptr;
    char *fend;
    FragBitsData *ds_ptr;  /* data struct pointer */

    /* set the ds pointer to make it easier to reference the option's
       particular data struct */
    ds_ptr = otn->ds_list[PLUGIN_FRAG_BITS];

    /* manipulate the option arguments here */
    fptr = data;

    while(isspace((u_char) *fptr))
    {
        fptr++;
    }

    if(strlen(fptr) == 0)
    {
        FatalError("[!] ERROR Line %s (%d): No arguments to the fragbits keyword\n", file_name, file_line);
    }

    fend = fptr + strlen(fptr);

    ds_ptr->mode = FB_NORMAL;  /* default value */

    while(fptr < fend)
    {
        switch((*fptr&0xFF))
        {
            case 'd':
            case 'D': /* don't frag bit */
                ds_ptr->frag_bits |= FB_DF;
                break;

            case 'm':
            case 'M': /* more frags bit */
                ds_ptr->frag_bits |= FB_MF;
                break;
                
            case 'r':
            case 'R': /* reserved bit */
                ds_ptr->frag_bits |= FB_RB;
                break;

            case '!': /* NOT flag, fire if flags are not set */
                ds_ptr->mode = FB_NOT;
                break;
                    
            case '*': /* ANY flag, fire on any of these bits */
                ds_ptr->mode = FB_ANY;
                break;
                    
            case '+': /* ALL flag, fire on these bits plus any others */
                ds_ptr->mode = FB_ALL;
                break;

            default:
                FatalError("[!] ERROR Line %s (%d): Bad Frag Bits = \"%c\"\n"
                           "     Valid options are: RDM+!*\n", file_name, 
                           file_line, *fptr);
        }
        
        fptr++;
    }
                    
    /* put the bits in network order for fast comparisons */
    ds_ptr->frag_bits = htons(ds_ptr->frag_bits);

    /* set the final option arguments here */
}


/****************************************************************************
 * 
 * Function: TemplateDetectorFunction(char *, OptTreeNode *)
 *
 * Purpose: Use this function to perform the particular detection routine
 *          that this rule keyword is supposed to encompass.
 *
 * Arguments: data => argument data
 *            otn => pointer to the current rule's OTN
 *
 * Returns: If the detection test fails, this function *must* return a zero!
 *          On success, it calls the next function in the detection list 
 *
 ****************************************************************************/
int CheckFragBits(Packet *p, struct _OptTreeNode *otn, OptFpList *fp_list)
{
    FragBitsData *fb;

    fb = otn->ds_list[PLUGIN_FRAG_BITS];

#ifdef DEBUG
    printf("           <!!> CheckFragBits: ");
    printf("[rule: 0x%X:%d   pkt: 0x%X] ", fb->frag_bits, fb->mode, (p->iph->ip_off&bitmask));
#endif

    switch(fb->mode)
    {
        case FB_NORMAL:
            /* check if the rule bits match the bits in the packet */
            if(fb->frag_bits == (p->iph->ip_off&bitmask)) 
            {
#ifdef DEBUG
                printf("Got Normal bits match\n");
#endif
                return fp_list->next->OptTestFunc(p, otn, fp_list->next);
            }
#ifdef DEBUG            
            else
            {
                printf("Normal test failed\n");
            }
#endif
            break;

        case FB_NOT:
            /* check if the rule bits don't match the bits in the packet */
            if((fb->frag_bits & (p->iph->ip_off&bitmask)) == 0)
            {
#ifdef DEBUG
                printf("Got NOT bits match\n");
#endif
                return fp_list->next->OptTestFunc(p, otn, fp_list->next);
            }
#ifdef DEBUG            
            else
            {
                printf("NOT test failed\n");
            }
#endif
            break;
            
        case FB_ALL:
            /* check if the rule bits are present in the packet */
            if((fb->frag_bits & (p->iph->ip_off&bitmask)) == fb->frag_bits)
            {
#ifdef DEBUG
                printf("Got ALL bits match\n");
#endif
                return fp_list->next->OptTestFunc(p, otn, fp_list->next);
            }
#ifdef DEBUG            
            else
            {
                printf("ALL test failed\n");
            }
#endif
            break;
            
        case FB_ANY:
            /* check if any of the rule bits match the bits in the packet */
            if((fb->frag_bits & (p->iph->ip_off&bitmask)) != 0)
            {
#ifdef DEBUG
                printf("Got ANY bits match\n");
#endif
                return fp_list->next->OptTestFunc(p, otn, fp_list->next);
            }
#ifdef DEBUG            
            else
            {
                printf("ANY test failed\n");
            }
#endif
            break;
    }

    /* if the test isn't successful, this function *must* return 0 */
    return 0;
}
