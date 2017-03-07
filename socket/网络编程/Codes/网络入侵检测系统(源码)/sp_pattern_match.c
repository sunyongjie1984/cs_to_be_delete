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

/* $Id: sp_pattern_match.c,v 1.8 2001/01/13 07:31:14 roesch Exp $ */
#include "sp_pattern_match.h"

extern int file_line;

int list_file_line;     /* current line being processed in the list
                 * file */

void SetupPatternMatch()
{
    RegisterPlugin("content", PayloadSearchInit);
    RegisterPlugin("content-list", PayloadSearchListInit);
    RegisterPlugin("offset", PayloadSearchOffset);
    RegisterPlugin("depth", PayloadSearchDepth);
    RegisterPlugin("nocase", PayloadSearchNocase);
    RegisterPlugin("regex", PayloadSearchRegex);

#ifdef DEBUG
    printf("Plugin: PatternMatch Initialized!\n");
#endif
}


void PayloadSearchListInit(char *data, OptTreeNode * otn, int protocol)
{
    char *sptr;
    char *eptr;


#ifdef DEBUG
    printf("In PayloadSearchListInit()\n");
#endif

    /* content-list can appear separately in rules */
    NewNode(otn);

    /* get the path/file name from the data */
    while(isspace((int) *data))
        data++;

    /* grab everything between the starting " and the end one */
    sptr = index(data, '"');
    eptr = strrchr(data, '"');

    if(sptr != NULL && eptr != NULL)
    {
        /* increment past the first quote */
        sptr++;

        /* zero out the second one */
        *eptr = 0;
    }
    else
    {
        sptr = data;
    }

    /* read the content keywords from the list file */
    ParseContentListFile(sptr, otn, protocol);


    /* link the plugin function in to the current OTN */
    AddOptFuncToList(CheckORPatternMatch, otn);

    return;
}


void PayloadSearchInit(char *data, OptTreeNode * otn, int protocol)
{
#ifdef DEBUG
    printf("In PayloadSearchInit()\n");
#endif

    /* whack a new node onto the list */
    NewNode(otn);

    /* set up the pattern buffer */
    ParsePattern(data, otn);

    /* link the plugin function in to the current OTN */
    AddOptFuncToList(CheckANDPatternMatch, otn);

#ifdef DEBUG
    printf("OTN function PatternMatch Added to rule!\n");
#endif
}



void PayloadSearchOffset(char *data, OptTreeNode * otn, int protocol)
{
    PatternMatchData *idx;

#ifdef DEBUG
    printf("In PayloadSearch()\n");
#endif

    idx = otn->ds_list[PLUGIN_PATTERN_MATCH];

    if(idx == NULL)
    {
        FatalError("ERROR Line %d => Please place \"content\" rules before depth, nocase or offset modifiers.\n", file_line);
    }
    while(idx->next != NULL)
        idx = idx->next;

    while(isspace((int) *data))
        data++;
    idx->offset = atoi(data);

#ifdef DEBUG
    printf("Pattern offset = %d\n", idx->offset);
#endif

    return;
}



void PayloadSearchDepth(char *data, OptTreeNode * otn, int protocol)
{
    PatternMatchData *idx;

    idx = (PatternMatchData *) otn->ds_list[PLUGIN_PATTERN_MATCH];

    if(idx == NULL)
    {
        FatalError("ERROR Line %d => Please place \"content\" rules before depth, nocase or offset modifiers.\n", file_line);
    }
    while(idx->next != NULL)
        idx = idx->next;

    while(isspace((int) *data))
        data++;
    idx->depth = atoi(data);

#ifdef DEBUG
    printf("Pattern offset = %d\n", idx->offset);
#endif

    return;
}



void PayloadSearchNocase(char *data, OptTreeNode * otn, int protocol)
{
    PatternMatchData *idx;
    int i;

    idx = (PatternMatchData *) otn->ds_list[PLUGIN_PATTERN_MATCH];

    if(idx == NULL)
    {
        FatalError("ERROR Line %d => Please place \"content\" rules before depth, nocase or offset modifiers.\n", file_line);
    }
    while(idx->next != NULL)
        idx = idx->next;

    idx->search = mSearchCI;

    i = idx->pattern_size;

    while(--i >= 0)
        idx->pattern_buf[i] = toupper((unsigned char) idx->pattern_buf[i]);

    free(idx->skip_stride);
    idx->skip_stride = make_skip(idx->pattern_buf, idx->pattern_size);

    free(idx->shift_stride);
    idx->shift_stride = make_shift(idx->pattern_buf, idx->pattern_size);

    return;
}



void PayloadSearchRegex(char *data, OptTreeNode * otn, int protocol)
{
    PatternMatchData *idx;
    int i;

    idx = (PatternMatchData *) otn->ds_list[PLUGIN_PATTERN_MATCH];

    if(idx == NULL)
    {
        FatalError("ERROR Line %d => Please place \"content\" rules before depth, nocase or offset modifiers.\n", file_line);
    }
    while(idx->next != NULL)
        idx = idx->next;

    idx->search = mSearchREG;

    i = idx->pattern_size;

    while(--i >= 0)
        idx->pattern_buf[i] = toupper((unsigned char) idx->pattern_buf[i]);

    free(idx->skip_stride);
    idx->skip_stride = make_skip(idx->pattern_buf, idx->pattern_size);

    free(idx->shift_stride);
    idx->shift_stride = make_shift(idx->pattern_buf, idx->pattern_size);

    return;
}




void NewNode(OptTreeNode * otn)
{
    PatternMatchData *idx;

    idx = (PatternMatchData *) otn->ds_list[PLUGIN_PATTERN_MATCH];

    if(idx == NULL)
    {
        if((otn->ds_list[PLUGIN_PATTERN_MATCH] = (PatternMatchData *) calloc(sizeof(PatternMatchData), sizeof(char))) == NULL)
        {
            FatalError("ERROR => sp_pattern_match NewNode() calloc failed!\n");
        }
    }
    else
    {
        idx = otn->ds_list[PLUGIN_PATTERN_MATCH];

        while(idx->next != NULL)
            idx = idx->next;

        if((idx->next = (PatternMatchData *) calloc(sizeof(PatternMatchData), sizeof(char))) == NULL)
        {
            FatalError("ERROR => sp_pattern_match NewNode() calloc failed!\n");
        }
    }
}



/****************************************************************************
 *
 * Function: ParsePattern(char *)
 *
 * Purpose: Process the application layer patterns and attach them to the
 *          appropriate rule.  My god this is ugly code.
 *
 * Arguments: rule => the pattern string
 *
 * Returns: void function
 *
 ***************************************************************************/
void ParsePattern(char *rule, OptTreeNode * otn)
{
    unsigned char tmp_buf[2048];

    /* got enough ptrs for you? */
    char *start_ptr;
    char *end_ptr;
    char *idx;
    char *dummy_idx;
    char *dummy_end;
    char hex_buf[9];
    u_int dummy_size = 0;
    u_int size;
    int hexmode = 0;
    int hexsize = 0;
    int pending = 0;
    int cnt = 0;
    int literal = 0;
    PatternMatchData *ds_idx;

    /* clear out the temp buffer */
    bzero(tmp_buf, 2048);

    /* find the start of the data */
    start_ptr = index(rule, '"');

    if(start_ptr == NULL)
    {
        FatalError("ERROR Line %d => Content data needs to be enclosed in quotation marks (\")!\n", file_line);
    }
    /* move the start up from the beggining quotes */
    start_ptr++;

    /* find the end of the data */
    end_ptr = strrchr(start_ptr, '"');

    if(end_ptr == NULL)
    {
        FatalError("ERROR Line %d => Content data needs to be enclosed in quotation marks (\")!\n", file_line);
    }
    /* set the end to be NULL */
    *end_ptr = 0;

    /* how big is it?? */
    size = end_ptr - start_ptr;

    /* uh, this shouldn't happen */
    if(size <= 0)
    {
        FatalError("ERROR Line %d => Bad pattern length!\n", file_line);
    }
    /* set all the pointers to the appropriate places... */
    idx = start_ptr;

    /* set the indexes into the temp buffer */
    dummy_idx = tmp_buf;
    dummy_end = (dummy_idx + size);

    /* why is this buffer so small? */
    bzero(hex_buf, 9);
    memset(hex_buf, '0', 8);

    /* BEGIN BAD JUJU..... */
    while(idx < end_ptr)
    {
#ifdef DEBUG
        printf("processing char: %c\n", *idx);
#endif
        switch(*idx)
        {
            case '|':
#ifdef DEBUG
                printf("Got bar... ");
#endif
                if(!literal)
                {
#ifdef DEBUG
                    printf("not in literal mode... ");
#endif
                    if(!hexmode)
                    {
#ifdef DEBUG
                        printf("Entering hexmode\n");
#endif
                        hexmode = 1;
                    }
                    else
                    {
#ifdef DEBUG
                        printf("Exiting hexmode\n");
#endif
                        hexmode = 0;
                    }

                    if(hexmode)
                        hexsize = 0;
                }
                else
                {
#ifdef DEBUG
                    printf("literal set, Clearing\n");
#endif
                    literal = 0;
                    tmp_buf[dummy_size] = start_ptr[cnt];
                    dummy_size++;
                }

                break;

            case '\\':
#ifdef DEBUG
                printf("Got literal char... ");
#endif
                if(!literal)
                {
#ifdef DEBUG
                    printf("Setting literal\n");
#endif
                    literal = 1;
                }
                else
                {
#ifdef DEBUG
                    printf("Clearing literal\n");
#endif
                    tmp_buf[dummy_size] = start_ptr[cnt];
                    literal = 0;
                    dummy_size++;
                }

                break;

            default:
                if(hexmode)
                {
                    if(isxdigit((int) *idx))
                    {
                        hexsize++;

                        if(!pending)
                        {
                            hex_buf[7] = *idx;
                            pending++;
                        }
                        else
                        {
                            hex_buf[8] = *idx;
                            pending--;

                            if(dummy_idx < dummy_end)
                            {
                                tmp_buf[dummy_size] = (u_char) strtol(hex_buf, (char **) NULL, 16);

                                dummy_size++;
                                bzero(hex_buf, 9);
                                memset(hex_buf, '0', 8);
                            }
                            else
                            {
                                FatalError("ERROR => ParsePattern() dummy buffer overflow, make a smaller pattern please! (Max size = 2048)\n");
                            }
                        }
                    }
                    else
                    {
                        if(*idx != ' ')
                        {
                            FatalError("ERROR Line %d => What is this \"%c\"(0x%X) doing in your binary buffer?  Valid hex values only please! (0x0 - 0xF) Position: %d\n", file_line, (char) *idx, (char) *idx, cnt);
                        }
                    }
                }
                else
                {
                    if(*idx >= 0x1F && *idx <= 0x7e)
                    {
                        if(dummy_idx < dummy_end)
                        {
                            tmp_buf[dummy_size] = start_ptr[cnt];
                            dummy_size++;
                        }
                        else
                        {
                            FatalError("ERROR Line %d=> ParsePattern() dummy buffer overflow!\n", file_line);
                        }

                        if(literal)
                        {
                            literal = 0;
                        }
                    }
                    else
                    {
                        if(literal)
                        {
                            tmp_buf[dummy_size] = start_ptr[cnt];
                            dummy_size++;
#ifdef DEBUG
                            printf("Clearing literal\n");
#endif
                            literal = 0;
                        }
                        else
                        {
                            FatalError("ERROR Line %d=> character value out of range, try a binary buffer dude\n", file_line);
                        }
                    }
                }

                break;
        }

        dummy_idx++;
        idx++;
        cnt++;
    }

    /* ...END BAD JUJU */

    ds_idx = (PatternMatchData *) otn->ds_list[PLUGIN_PATTERN_MATCH];

    while(ds_idx->next != NULL)
        ds_idx = ds_idx->next;

    if((ds_idx->pattern_buf = (char *) malloc(sizeof(char) * dummy_size)) == NULL)
    {
        FatalError("ERROR => ParsePattern() pattern_buf malloc filed!\n");
    }
    memcpy(ds_idx->pattern_buf, tmp_buf, dummy_size);

    ds_idx->pattern_size = dummy_size;

    ds_idx->search = mSearch;

    ds_idx->skip_stride = make_skip(ds_idx->pattern_buf, ds_idx->pattern_size);
    ds_idx->shift_stride = make_shift(ds_idx->pattern_buf, ds_idx->pattern_size);

    return;
}




int CheckORPatternMatch(Packet * p, struct _OptTreeNode * otn_idx, OptFpList * fp_list)
{
    int sub_depth;
    int found = 0;
    PatternMatchData *idx;

#ifdef DEBUG
    printf("CheckPatternMatch: ");
#endif

    idx = otn_idx->ds_list[PLUGIN_PATTERN_MATCH];

    while(idx != NULL)
    {
        if(idx->offset > p->dsize)
        {
#ifdef DEBUG
            printf("Initial offset larger than payload!\n");
#endif
            return 0;
        }
        else
        {
            /* do some tests to make sure we stay in bounds */
            if((idx->depth + idx->offset) > p->dsize)
            {
                /* we want to check only depth bytes anyway */
                sub_depth = p->dsize - idx->offset; 

                if((sub_depth > 0) && (sub_depth >= (int)idx->pattern_size))
                {
#ifdef DEBUG
                    printf("testing pattern: %s\n", idx->pattern_buf);
#endif
                    found = idx->search((char *)(p->data + idx->offset), 
                                        sub_depth, idx->pattern_buf,
                                        idx->pattern_size, idx->skip_stride, 
                                        idx->shift_stride);

#ifdef DEBUG
                    if(!found)
                    {
                        printf("Pattern Match failed!\n");
                    }
#endif
                }
            }
            else
            {
#ifdef DEBUG
                printf("Testing pattern (lower section): %s\n", 
                        idx->pattern_buf);
#endif
                if(idx->depth && (p->dsize-idx->offset> idx->depth))
                {
                    found = idx->search((char *)(p->data + idx->offset), 
                                        idx->depth, idx->pattern_buf,
                                        idx->pattern_size, idx->skip_stride, 
                                        idx->shift_stride);
                }
                else
                {
                    found = idx->search((char *)(p->data + idx->offset), 
                                        p->dsize - idx->offset ,
                                        idx->pattern_buf, idx->pattern_size, 
                                        idx->skip_stride, idx->shift_stride);
                }

                if(!found)
                {
#ifdef DEBUG
                    printf("Pattern Match failed! Exit the loop.\n");
#endif
                }
            }
        }


#ifdef DEBUG
        printf("Checking the results\n");
#endif

        if(found)
        {
#ifdef DEBUG
            printf("Pattern Match successful:i %s!\n", idx->pattern_buf);
#endif

            return fp_list->next->OptTestFunc(p, otn_idx, fp_list->next);

        }
#ifdef DEBUG
        else
        {
            printf("Pattern match failed\n");
        }
#endif

#ifdef DEBUG
        printf("Stepping to next content keyword...\n");
#endif

        idx = idx->next;
    }

#ifdef DEBUG
    printf("No more keywords, exiting... \n");
#endif


    return 0;
}



int CheckANDPatternMatch(Packet *p, struct _OptTreeNode *otn_idx, OptFpList *fp_list)
{
    int sub_depth;
    int found = 0;
    PatternMatchData *idx;

#ifdef DEBUG
    printf("CheckPatternMatch: ");
#endif

    idx = otn_idx->ds_list[PLUGIN_PATTERN_MATCH];

    while(idx != NULL)
    {
        if(idx->offset > p->dsize)
        {
#ifdef DEBUG
            printf("Initial offset larger than payload!\n");
#endif
            return 0;
        }
        else
        {
            /* do some tests to make sure we stay in bounds */
            if((idx->depth + idx->offset) > p->dsize)
            {
                /* we want to match depth bytes anyway */
                sub_depth = p->dsize - idx->offset; 

                if((sub_depth > 0) && (sub_depth >= (int)idx->pattern_size))
                {
#ifdef DEBUG
                    printf("testing pattern: %s\n", idx->pattern_buf);
#endif
                    found = idx->search((char *)(p->data+idx->offset), sub_depth,idx->pattern_buf,
                                        idx->pattern_size, idx->skip_stride, idx->shift_stride);

                    if(!found)
                    {
#ifdef DEBUG
                        printf("Pattern Match failed!\n");
#endif
                        return 0;
                    }
                }
            }
            else
            {
#ifdef DEBUG
                printf("Testing pattern (lower section): %s\n", idx->pattern_buf);
#endif
                /* if depth field is present and we don't go over the dsize boundary with it */
                if(idx->depth && (p->dsize-idx->offset> idx->depth))
                {
                    found = idx->search((char *)(p->data+idx->offset), idx->depth, idx->pattern_buf,
                                        idx->pattern_size, idx->skip_stride, idx->shift_stride);
                }
                else
                {
                    found = idx->search((char *)(p->data+idx->offset), p->dsize - idx->offset,
                                        idx->pattern_buf, idx->pattern_size, idx->skip_stride,
                                        idx->shift_stride);
                }

                if(!found)
                {
#ifdef DEBUG
                    printf("Pattern Match failed!\n");
#endif
                    return 0;
                }
            }
        }

        idx = idx->next;

#ifdef DEBUG
        printf("Stepping to next content keyword...\n");
#endif
    }

    if(found)
    {
#ifdef DEBUG
        printf("Pattern Match successful!\n");
#endif

        return fp_list->next->OptTestFunc(p, otn_idx, fp_list->next);

    }
#ifdef DEBUG
    else
    {
        printf("Pattern match failed\n");
    }
#endif

    return 0;
}



/****************************************************************************
 *
 * Function: ParseContentListFile(char *, OptTreeNode *, int protocol)
 *
 * Purpose:  Read the content_list file a line at a time, put the content of
 *           the line into buffer
 *
 * Arguments:otn => rule including the list
 *           file => list file filename
 *	     protocol => protocol
 *
 * Returns: void function
 *
 ***************************************************************************/
void ParseContentListFile(char *file, OptTreeNode * otn, int protocol)
{
    FILE *thefp;        /* file pointer for the content_list file */
    char buf[STD_BUF+1];        /* file read buffer */
    char rule_buf[STD_BUF+1];   /* content keyword buffer */
    int frazes_count;       /* frazes counter */


#ifdef DEBUG
    printf("Opening content_list file: %s\n", file);
#endif

    /* open the list file */
    if((thefp = fopen(file, "r")) == NULL)
    {
        FatalError("Unable to open list file: %s\n", file);
    }
    /* clear the line and rule buffers */
    bzero((char *) buf, STD_BUF);
    bzero((char *) rule_buf, STD_BUF);
    frazes_count = 0;

    /* loop thru each list_file line and content to the rule */
    while((fgets(buf, STD_BUF-2, thefp)) != NULL)
    {
        /* inc the line counter */
        list_file_line++;

#ifdef DEBUG2
        printf("Got line %d: %s", list_file_line, buf);
#endif

        /* if it's not a comment or a <CR>, send it to the parser */
        if((buf[0] != '#') && (buf[0] != 0x0a) && (buf[0] != ';'))
        {

#ifdef DEBUG
            printf("Adding content keyword: %s", buf);
#endif

            frazes_count++;
            strip(buf);
            snprintf(rule_buf, STD_BUF, "\"%s\"",buf);

            /* check and add content keyword */
            ParsePattern(rule_buf, otn);

#ifdef DEBUG
            printf("Content keyword %s\" added!\n", rule_buf);
#endif
        }
    }

#ifdef DEBUG
    printf("%d frazes read...\n", frazes_count);
#endif

    fclose(thefp);

    return;
}
