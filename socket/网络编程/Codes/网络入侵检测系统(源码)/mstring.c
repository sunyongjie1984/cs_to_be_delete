/* $Id: mstring.c,v 1.5 2001/01/02 08:06:00 roesch Exp $ */
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

/***************************************************************************
 *
 * File: MSTRING.C
 *
 * Purpose: Provide a variety of string functions not included in libc.  Makes
 *          up for the fact that the libstdc++ is hard to get reference
 *          material on and I don't want to write any more non-portable c++
 *          code until I have solid references and libraries to use.
 *
 * History:
 *
 * Date:      Author:  Notes:
 * ---------- ------- ----------------------------------------------
 *  08/19/98    MFR    Initial coding begun
 *  03/06/99    MFR    Added Boyer-Moore pattern match routine, don't use
 *                     mContainsSubstr() any more if you don't have to
 *  12/31/99	JGW    Added a full Boyer-Moore implementation to increase
 *                     performance. Added a case insensitive version of mSearch
 *
 **************************************************************************/
#include "mstring.h"

#ifdef TEST_MSTRING

int main()
{
    char test[] = "\0\0\0\0\0\0\0\0\0CKAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\0\0";
    char find[] = "CKAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\0\0";

/*   char test[] = "\x90\x90\x90\x90\x90\x90\xe8\xc0\xff\xff\xff/bin/sh\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
     char find[] = "\xe8\xc0\xff\xff\xff/bin/sh";  */
    int i;
    int toks;
    int *shift;
    int *skip;

/*   shift=make_shift(find,sizeof(find)-1);
     skip=make_skip(find,sizeof(find)-1); */

    printf("%d\n",
           mSarch(test, sizeof(test) - 1, find, sizeof(find) - 1, shift, skip));

    return 0;
}

#endif

/****************************************************************
 *
 *  Function: mSplit()
 *
 *  Purpose: Splits a string into tokens non-destructively.
 *
 *  Parameters:
 *      char *str => the string to be split
 *      char *sep => a string of token seperaters
 *      int max_strs => how many tokens should be returned
 *      int *toks => place to store the number of tokens found in str
 *      char meta => the "escape metacharacter", treat the character
 *                   after this character as a literal and "escape" a
 *                   seperator
 *
 *  Returns:
 *      2D char array with one token per "row" of the returned
 *      array.
 *
 ****************************************************************/
char **mSplit(char *str, char *sep, int max_strs, int *toks, char meta)
{
    char **retstr;      /* 2D array which is returned to caller */
    char *idx;          /* index pointer into str */
    char *end;          /* ptr to end of str */
    char *sep_end;      /* ptr to end of seperator string */
    char *sep_idx;      /* index ptr into seperator string */
    int len = 0;        /* length of current token string */
    int curr_str = 0;       /* current index into the 2D return array */
    int last_char = 0xFF;

#ifdef DEBUG
    printf("[*] Splitting string: %s\n", str);
    printf("curr_str = %d\n", curr_str);
#endif

    /*
     * find the ends of the respective passed strings so our while() loops
     * know where to stop
     */
    sep_end = sep + strlen(sep);
    end = str + strlen(str);

    /* remove trailing whitespace */
    while(isspace((int) *(end - 1)) && ((end - 1) >= str))
        *(--end) = '\0';    /* -1 because of NULL */

    /* set our indexing pointers */
    sep_idx = sep;
    idx = str;

    /*
     * alloc space for the return string, this is where the pointers to the
     * tokens will be stored
     */
    retstr = (char **) malloc((sizeof(char **) * max_strs));

    max_strs--;

#ifdef DEBUG
    printf("max_strs = %d  curr_str = %d\n", max_strs, curr_str);
#endif

    /* loop thru each letter in the string being tokenized */
    while(idx < end)
    {
        /* loop thru each seperator string char */
        while(sep_idx < sep_end)
        {
            /*
             * if the current string-indexed char matches the current
             * seperator char...
             */
            if((*idx == *sep_idx) && (last_char != meta))
            {
                /* if there's something to store... */
                if(len > 0)
                {
#ifdef DEBUG
                    printf("Allocating %d bytes for token ", len + 1);
                    fflush(stdout);
#endif
                    if(curr_str <= max_strs)
                    {
                        /* allocate space for the new token */
                        retstr[curr_str] = (char *) malloc((sizeof(char) * len) + 1);

                        /* make sure we got a good allocation */
                        if(retstr[curr_str] == NULL)
                        {
                            fprintf(stderr, "msplit() got NULL substring malloc!\n");
                            exit(1);
                        }
                        /* copy the token into the return string array */
                        memcpy(retstr[curr_str], (idx - len), len);
                        retstr[curr_str][len] = 0;
#ifdef DEBUG
                        printf("tok[%d]: %s\n", curr_str, retstr[curr_str]);
                        fflush(stdout);
#endif
                        /* twiddle the necessary pointers and vars */
                        len = 0;
                        curr_str++;
#ifdef DEBUG
                        printf("curr_str = %d\n", curr_str);
                        printf("max_strs = %d  curr_str = %d\n", max_strs, curr_str);
#endif
                        last_char = *idx;
                        idx++;
                    }
#ifdef DEBUG
                    printf("Checking if curr_str (%d) >= max_strs (%d)\n", curr_str, max_strs);
#endif

                    /*
                     * if we've gotten all the tokens requested, return the
                     * list
                     */
                    if(curr_str >= max_strs)
                    {
                        while(isspace((int) *idx))
                            idx++;

                        len = end - idx;
#ifdef DEBUG
                        printf("Finishing up...\n");
                        printf("Allocating %d bytes for last token ", len + 1);
                        fflush(stdout);
#endif
                        retstr[curr_str] = (char *) malloc((sizeof(char) * len) + 1);

                        if(retstr[curr_str] == NULL)
                            printf("Got NULL back from substr malloc\n");

                        memcpy(retstr[curr_str], idx, len);
                        retstr[curr_str][len] = 0;

#ifdef DEBUG
                        printf("tok[%d]: %s\n", curr_str, retstr[curr_str]);
                        fflush(stdout);
#endif

                        *toks = curr_str + 1;
#ifdef DEBUG
                        printf("max_strs = %d  curr_str = %d\n", max_strs, curr_str);
                        printf("mSplit got %d tokens!\n", *toks);
                        fflush(stdout);
#endif
                        return retstr;
                    }
                }
                else
                /*
                 * otherwise, the previous char was a seperator as well,
                 * and we should just continue
                 */
                {
                    last_char = *idx;
                    idx++;
                    /* make sure to reset this so we test all the sep. chars */
                    sep_idx = sep;
                    len = 0;
                }
            }
            else
            {
                /* go to the next seperator */
                sep_idx++;
            }
        }

        sep_idx = sep;
        len++;
        last_char = *idx;
        idx++;
    }

    /* put the last string into the list */

    if(len > 0)
    {
#ifdef DEBUG
        printf("Allocating %d bytes for last token ", len + 1);
        fflush(stdout);
#endif

        retstr[curr_str] = (char *) malloc((sizeof(char) * len) + 1);

        if(retstr[curr_str] == NULL)
            printf("Got NULL back from substr malloc\n");

        memcpy(retstr[curr_str], (idx - len), len);
        retstr[curr_str][len] = 0;

#ifdef DEBUG
        printf("tok[%d]: %s\n", curr_str, retstr[curr_str]);
        fflush(stdout);
#endif
        *toks = curr_str + 1;
    }
#ifdef DEBUG
    printf("mSplit got %d tokens!\n", *toks);
    fflush(stdout);
#endif

    /* return the token list */
    return retstr;
}




/****************************************************************
 *
 *  Function: mContainsSubstr(char *, int, char *, int)
 *
 *  Purpose: Determines if a string contains a (non-regex)
 *           substring.
 *
 *  Parameters:
 *      buf => data buffer we want to find the data in
 *      b_len => data buffer length
 *      pat => pattern to find
 *      p_len => length of the data in the pattern buffer
 *
 *  Returns:
 *      Integer value, 1 on success (str constains substr), 0 on
 *      failure (substr not in str)
 *
 ****************************************************************/
int mContainsSubstr(char *buf, int b_len, char *pat, int p_len)
{
    char *b_idx;        /* index ptr into the data buffer */
    char *p_idx;        /* index ptr into the pattern buffer */
    char *b_end;        /* ptr to the end of the data buffer */
    int m_cnt = 0;      /* number of pattern matches so far... */

#ifdef DEBUG
    unsigned long loopcnt = 0;

#endif


    /* mark the end of the strs */
    b_end = (char *) (buf + b_len);

    /* init the index ptrs */
    b_idx = buf;
    p_idx = pat;

    do
    {
#ifdef DEBUG
        loopcnt++;
#endif

        if(*p_idx == *b_idx)
        {

            if(m_cnt == (p_len - 1))
            {
#ifdef DEBUG
                printf("\n%ld compares for match\n", loopcnt);
#endif
                return 1;
            }
            m_cnt++;
            b_idx++;
            p_idx++;
        }
        else
        {
            if(m_cnt == 0)
            {
                b_idx++;
            }
            else
            {
                b_idx = b_idx - (m_cnt - 1);
            }

            p_idx = pat;

            m_cnt = 0;
        }

    } while(b_idx < b_end);


    /* if we make it here we didn't find what we were looking for */
    return 0;
}




/****************************************************************
 *
 *  Function: make_skip(char *, int)
 *
 *  Purpose: Create a Boyer-Moore skip table for a given pattern
 *
 *  Parameters:
 *      ptrn => pattern
 *      plen => length of the data in the pattern buffer
 *
 *  Returns:
 *      int * - the skip table
 *
 ****************************************************************/
int *make_skip(char *ptrn, int plen)
{
    int *skip = (int *) malloc(256 * sizeof(int));
    int *sptr = &skip[256];

    while(sptr-- != skip)
        *sptr = plen + 1;

    while(plen != 0)
        skip[(unsigned char) *ptrn++] = plen--;

    return skip;
}



/****************************************************************
 *
 *  Function: make_shift(char *, int)
 *
 *  Purpose: Create a Boyer-Moore shift table for a given pattern
 *
 *  Parameters:
 *      ptrn => pattern
 *      plen => length of the data in the pattern buffer
 *
 *  Returns:
 *      int * - the shift table
 *
 ****************************************************************/
int *make_shift(char *ptrn, int plen)
{
    int *shift = (int *) malloc(plen * sizeof(int));
    int *sptr = shift + plen - 1;
    char *pptr = ptrn + plen - 1;
    char c = ptrn[plen - 1];

    *sptr = 1;

    while(sptr-- != shift)
    {
        char *p1 = ptrn + plen - 2, *p2, *p3;

        do
        {
            while(p1 >= ptrn && *p1-- != c);

            p2 = ptrn + plen - 2;
            p3 = p1;

            while(p3 >= ptrn && *p3-- == *p2-- && p2 >= pptr);
        }
        while(p3 >= ptrn && p2 >= pptr);

        *sptr = shift + plen - sptr + p2 - p3;

        pptr--;
    }

    return shift;
}



/****************************************************************
 *
 *  Function: mSearch(char *, int, char *, int)
 *
 *  Purpose: Determines if a string contains a (non-regex)
 *           substring.
 *
 *  Parameters:
 *      buf => data buffer we want to find the data in
 *      blen => data buffer length
 *      ptrn => pattern to find
 *      plen => length of the data in the pattern buffer
 *      skip => the B-M skip array
 *      shift => the B-M shift array
 *
 *  Returns:
 *      Integer value, 1 on success (str constains substr), 0 on
 *      failure (substr not in str)
 *
 ****************************************************************/
int mSearch(char *buf, int blen, char *ptrn, int plen, int *skip, int *shift)
{
    int b_idx = plen;

#ifdef  DEBUG
    int cmpcnt = 0;

#endif

    if(plen == 0)
        return 1;

    while(b_idx <= blen)
    {
        int p_idx = plen, skip_stride, shift_stride;

        while(buf[--b_idx] == ptrn[--p_idx])
        {
#ifdef	DEBUG
            cmpcnt++;
#endif
            if(p_idx == 0)
            {
#ifdef	DEBUG
                fprintf(stdout, "match: compares = %d.\n", cmpcnt);
#endif
                return 1;
            }
        }

        skip_stride = skip[(unsigned char) buf[b_idx]];
        shift_stride = shift[p_idx];

        b_idx += (skip_stride > shift_stride) ? skip_stride : shift_stride;
    }

#ifdef	DEBUG
    fprintf(stdout, "no match: compares = %d.\n", cmpcnt);
#endif

    return 0;
}



/****************************************************************
 *
 *  Function: mSearchCI(char *, int, char *, int)
 *
 *  Purpose: Determines if a string contains a (non-regex)
 *           substring matching is case insensitive
 *
 *  Parameters:
 *      buf => data buffer we want to find the data in
 *      blen => data buffer length
 *      ptrn => pattern to find
 *      plen => length of the data in the pattern buffer
 *      skip => the B-M skip array
 *      shift => the B-M shift array
 *
 *  Returns:
 *      Integer value, 1 on success (str constains substr), 0 on
 *      failure (substr not in str)
 *
 ****************************************************************/
int mSearchCI(char *buf, int blen, char *ptrn, int plen, int *skip, int *shift)
{
    int b_idx = plen;

#ifdef  DEBUG
    int cmpcnt = 0;

#endif

    if(plen == 0)
        return 1;

    while(b_idx <= blen)
    {
        int p_idx = plen, skip_stride, shift_stride;

        while((unsigned char) ptrn[--p_idx] == toupper((unsigned char) buf[--b_idx]))
        {
#ifdef	DEBUG
            cmpcnt++;
#endif
            if(p_idx == 0)
            {
#ifdef	DEBUG
                fprintf(stdout, "match: compares = %d.\n", cmpcnt);
#endif
                return 1;
            }
        }

        skip_stride = skip[toupper((unsigned char) buf[b_idx])];
        shift_stride = shift[p_idx];

        b_idx += (skip_stride > shift_stride) ? skip_stride : shift_stride;
    }

#ifdef	DEBUG
    fprintf(stdout, "no match: compares = %d.\n", cmpcnt);
#endif

    return 0;
}


/****************************************************************
 *
 *  Function: mSearchREG(char *, int, char *, int)
 *
 *  Purpose: Determines if a string contains a (regex)
 *           substring.
 *
 *  Parameters:
 *      buf => data buffer we want to find the data in
 *      blen => data buffer length
 *      ptrn => pattern to find
 *      plen => length of the data in the pattern buffer
 *      skip => the B-M skip array
 *      shift => the B-M shift array
 *
 *  Returns:
 *      Integer value, 1 on success (str constains substr), 0 on
 *      failure (substr not in str)
 *
 ****************************************************************/
int mSearchREG(char *buf, int blen, char *ptrn, int plen, int *skip, int *shift)
{
    int b_idx = plen;
    int literal = 0;

#ifdef  DEBUG
    int cmpcnt = 0;

#endif

    if(plen == 0)
        return 1;

    while(b_idx <= blen)
    {
        int p_idx = plen, skip_stride, shift_stride;


        while(buf[--b_idx] == ptrn[--p_idx]
              || (ptrn[p_idx] == '?' && !literal)
              || (ptrn[p_idx] == '*' && !literal)
              || (ptrn[p_idx] == '\\' && !literal))
        {
#ifdef	DEBUG
            cmpcnt++;
#endif

            if(literal)
                literal = 0;
            if(!literal && ptrn[p_idx] == '\\')
                literal = 1;
            if(ptrn[p_idx] == '*')
            {
                while(p_idx != 0 && ptrn[--p_idx] == '*'); /* fool-proof */
                if(p_idx == 0)
                {
#ifdef DEBUG
                    fprintf(stdout, "match: compares = %d.\n", cmpcnt);
#endif
                    return 1;
                }
                while(b_idx != 0)
                {
                    int ret = 0;

                    /*
                     * *ooooooch* here we go recurent.. I smell lots of
                     * headaches here. The algorytm is simple though: if
                     * substring which we haven't matched matches
                     * subsctring-to-match before asterick we return `match'
                     * otherwise we consider non-matched symbol a part of
                     * `*', move one symbol left and try to match it again.
                     */
                    if(ret == (mSearchREG(&buf[b_idx--], b_idx,
                                          &ptrn[p_idx], p_idx,
                                          skip, &shift[p_idx])) != 0)
                    {
                        printf("recurs: %i\n", ret);
                        return ret;
                    }
                }
            }
            if(p_idx == 0)
            {
#ifdef	DEBUG
                fprintf(stdout, "match: compares = %d.\n", cmpcnt);
#endif
                return 1;
            }
            if(b_idx == 0)
                break;
        }

        skip_stride = skip[(unsigned char) buf[b_idx]];
        shift_stride = shift[p_idx];

        b_idx += (skip_stride > shift_stride) ? skip_stride : shift_stride;
    }

#ifdef	DEBUG
    fprintf(stdout, "no match: compares = %d.\n", cmpcnt);
#endif

    return 0;
}
