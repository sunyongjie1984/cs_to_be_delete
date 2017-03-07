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

/* $Id: spp_http_decode.c,v 1.5 2001/01/02 08:06:01 roesch Exp $ */
/* spp_http_decode 
 * 
 * Purpose:
 *
 * This preprocessor normalizes HTTP requests from remote machines by
 * converting any %XX character substitutions to their ASCII equivalent.
 * This is very useful for doing things like defeating hostile attackers
 * trying to stealth themselves from IDSs by mixing these substitutions 
 * in with the request.
 *
 * Arguments:
 *   
 * This plugin takes a list of integers representing the TCP ports that the
 * user is interested in having normalized
 * a "-unicode" disables the IIS unicode check that is enabled by default
 * a "-cginull" disables the CGI NULL check that is enabled by default
 *
 * Effect:
 *
 * Changes the data in the packet payload to a plain ASCII representation 
 * and changes p->dsize to reflect the new (smaller) payload size.
 *
 * Comments:
 *
 * It could be interesting to generate an alert based on the number of
 * characters converted for a single packet, through some sort of threshold
 * setting.
 *
 */
#include "spp_http_decode.h"
#include <ctype.h>

#define MODNAME "spp_http_decode"

#define NOUNICODE "-unicode"
#define NOCGINULL "-cginull"

int check_iis_unicode = 1;
int check_cgi_null = 1;

extern char *file_name;
extern int file_line;

/* Instantiate the list of ports we're going to watch */
PortList HttpDecodePorts;

/*
 * Function: SetupHttpDecode()
 *
 * Purpose: Registers the preprocessor keyword and initialization 
 *          function into the preprocessor list.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 */
void SetupHttpDecode()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterPreprocessor("http_decode", HttpDecodeInit);

#ifdef DEBUG
    printf("Preprocessor: HttpDecode in setup...\n");
#endif
}


/*
 * Function: HttpDecodeInit(u_char *)
 *
 * Purpose: Processes the args sent to the preprocessor, sets up the
 *          port list, links the processing function into the preproc
 *          function list
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void HttpDecodeInit(u_char *args)
{
#ifdef DEBUG
    printf("Preprocessor: HttpDecode Initialized\n");
#endif

    /* parse the argument list into a list of ports to normalize */
    SetPorts(args);

    /* Set the preprocessor function into the function list */
    AddFuncToPreprocList(PreprocUrlDecode);
}



/*
 * Function: SetPorts(char *)
 *
 * Purpose: Reads the list of port numbers from the argument string and 
 *          parses them into the port list data struct
 *
 * Arguments: portlist => argument list
 *
 * Returns: void function
 *
 */
void SetPorts(char *portlist)
{
    char **toks;
    int num_toks;
    int num_ports = 0;
    int num;

    if(portlist == NULL)
    {
        FatalError("ERROR %s (%d)=> No arguments to http_decode preprocessor!\n", file_name, file_line);
    }

    /* tokenize the argument list */
    toks = mSplit(portlist, " ", 31, &num_toks, '\\');

    /* convert the tokens and place them into the port list */
    for(num = 0; num < num_toks; num++)
    {
        if(!strncmp(NOUNICODE, toks[num], sizeof NOUNICODE))
        {
            check_iis_unicode = 0;
        }
        else if(!strncmp(NOCGINULL, toks[num], sizeof NOCGINULL))
        {
            check_cgi_null = 0;
        }
        else
        {
            HttpDecodePorts.ports[num_ports++] = atoi(toks[num]);
        }
    }   

    HttpDecodePorts.num_entries = num_ports;

#ifdef DEBUG
    printf("Decoding HTTP on %d ports: ", HttpDecodePorts.num_entries);

    for(num_ports = 0; num_ports < HttpDecodePorts.num_entries; num_ports++)
    {
        printf("%d ", HttpDecodePorts.ports[num_ports]);
    }

    printf("\n");
#endif

}


/*
 * Function: PreprocUrlDecode(Packet *)
 *
 * Purpose: Inspects the packet's payload for "Escaped" characters and 
 *          converts them back to their ASCII values.  This function
 *          is based on the NCSA code and was contributed by Michael Henry!
 *
 * Arguments: p => pointer to the current packet data struct 
 *
 * Returns: void function
 *
 */
void PreprocUrlDecode(Packet *p)
{
    char *url;       /* this is where the converted data will be written */
    char *index;     /* this is the index pointer to walk thru the data */
    char *end;       /* points to the end of the payload, for loop control */
    u_int16_t psize; /* payload size */
    int i;           /* loop counter */
    char logMessage[180];
    int temp;

#ifdef DEBUG
    printf("http decoder init on %d bytes\n", p->dsize);
#endif

    /* check to make sure we're talking TCP and that the TWH has already
       completed before processing anything */
    if(!PacketIsTCP(p))
    {
#ifdef DEBUG
        printf("It isn't TCP session traffic\n");
#endif
        return;
    }

    if(!IsTcpSessionTraffic(p))
    {
#ifdef DEBUG
        printf("It isn't TCP session traffic\n");
#endif
        return;
    }

    /* check the port against the decode port list */
    for(i = 0; i < HttpDecodePorts.num_entries; i++)
    {
        if(HttpDecodePorts.ports[i] == p->dp)
        {
            /* on match, normalize the data */
#ifdef DEBUG
            printf("Got HTTP traffic (%d bytes)!\n", p->dsize);
            printf("%s\n", p->data);
#endif
            /* setup the pointers */
            url =   (char *) p->data;
            index = (char *) p->data;
            end =   (char *) p->data + p->dsize;
            psize = (u_int16_t) (p->dsize);

            /* walk thru each char in the payload */
            while(index < end)
            {
                /* if it's potentially "escaped" and not too close to the end of 
                   the payload */
                if((*index == '%') && (index < end - 2))
                {
                    /* and if the following two chars are hex digits */
                    if(isxdigit((int)*(index+1)) && isxdigit((int)*(index+2)))
                    {
                        /*convert it and stuff it */
                        temp = (nibble(*(index+1)) << 4) | nibble(*(index+2));
                        if(((temp == 192) || /* c0 */
                            (temp == 193) || /* c1 */
                            (temp == 224) || /* e0 */
                            (temp == 240) || /* f0 */
                            (temp == 248) || /* f8 */
                            (temp == 252)) &&/* fc */
                           check_iis_unicode)
                        {
                            snprintf(logMessage, sizeof(logMessage), 
                                     MODNAME ": IIS Unicode attack detected");

                            /*(*AlertFunc)(p, logMessage);*/
                            CallAlertFuncs(p, logMessage, NULL);
                            CallLogFuncs(p, logMessage, NULL);
                        }

                        if(temp == 0 && check_cgi_null)
                        {
                            snprintf(logMessage, sizeof(logMessage), 
                                     MODNAME ": CGI Null Byte attack detected");

                            /*(*AlertFunc)(p, logMessage);*/
                            CallAlertFuncs(p, logMessage, NULL);
                            CallLogFuncs(p, logMessage, NULL);
                        }

                        *url = temp;

                        index += 3; 
                        url++;
                        psize -= 2;
                    }
                    else
                    {
                        *url = *index;
                        url++;
                        index++;
                    }        
                }
                else
                {
                    *url = *index;
                    url++;
                    index++;
                }
            }

            /* set the payload size to reflect the new size */ 
            p->dsize = psize;

#ifdef DEBUG
            printf("New size: %d\n", p->dsize);
            printf("converted data:\n");
            PrintNetData(stdout, p->data, psize);
#endif

            return;
        }
    }
}




/*
 * Function: nibble(char)
 *
 * Purpose: converts a hex character into a value in the range 0..15
 *
 * Arguments: what => the character in question
 *
 * Returns: The converted character or -1 if the character is not hex
 *
 */
int nibble(char what)
{
    if(isdigit((int)what)) return what - '0';

    if(isxdigit((int)what)) return toupper((int)what) - 'A' + 10;

    return -1;
}
