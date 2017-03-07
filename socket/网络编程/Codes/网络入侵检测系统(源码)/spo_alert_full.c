/*
** Copyright (C) 1998,1999,2000,2001 Martin Roesch <roesch@clark.net>
** Copyright (C) 2000,2001 Andrew R. Baker <andrewb@uab.edu>
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

/* $Id: spo_alert_full.c,v 1.4 2001/01/02 08:06:01 roesch Exp $ */

/* spo_alert_full
 * 
 * Purpose:  output plugin for full alerting
 *
 * Arguments:  alert file (eventually)
 *   
 * Effect:
 *
 * Alerts are written to a file in the snort full alert format
 *
 * Comments:   Allows use of full alerts with other output plugin types
 *
 */

/* output plugin header file */
#include "spo_alert_full.h"

/* external globals from rules.c */
extern char *file_name;
extern int file_line;

/*
 * Function: SetupFullAlert()
 *
 * Purpose: Registers the output plugin keyword and initialization 
 *          function into the output plugin list.  This is the function that
 *          gets called from InitOutputPlugins() in plugbase.c.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 */
void SetupFullAlert()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("alert_full", NT_OUTPUT_ALERT, FullAlertInit);

#ifdef DEBUG
    printf("Output plugin: FullAlert is setup...\n");
#endif
}


/*
 * Function: FullAlertInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void FullAlertInit(u_char *args)
{
    SpoAlertFullData *data;
#ifdef DEBUG
    printf("Output: FullAlert Initialized\n");
#endif

    pv.alert_plugin_active = 1;

    /* parse the argument list from the rules file */
    data = ParseFullAlertArgs(args);

/*#ifdef DEBUG*/
    printf("Linking FullAlert functions to call lists...\n");
/*#endif*/

    /* Set the preprocessor function into the function list */
    AddFuncToOutputList(SpoAlertFull, NT_OUTPUT_ALERT, data);
    AddFuncToCleanExitList(FullAlertCleanExitFunc, data);
    AddFuncToRestartList(FullAlertRestartFunc, data);
}

void SpoAlertFull(Packet *p, char *msg, void *arg)
{
    SpoAlertFullData *data = (SpoAlertFullData *)arg;
    return AlertFull(p, msg, data->file);
}


/*
 * Function: ParseFullAlertArgs(char *)
 *
 * Purpose: Process the preprocessor arguements from the rules file and 
 *          initialize the preprocessor's data struct.  This function doesn't
 *          have to exist if it makes sense to parse the args in the init 
 *          function.
 *
 * Arguments: args => argument list
 *
 * Returns: void function
 *
 */
SpoAlertFullData *ParseFullAlertArgs(char *args)
{
    char **toks;
    int num_toks;
    char *filename;
    SpoAlertFullData *data;

    data = (SpoAlertFullData *)malloc(sizeof(SpoAlertFullData));
#ifdef DEBUG
    printf("ParseFullAlertArgs: %s\n", args);
#endif
    if(args == NULL)
    {
        data->file = OpenAlertFile(NULL);
        return data;
    }

    toks = mSplit(args, " ", 2, &num_toks, 0);
    filename = ProcessFileOption(toks[0]);
    data->file = OpenAlertFile(filename);
    free(filename);
    return data;
}

void FullAlertCleanExitFunc(int signal, void *arg)
{
    SpoAlertFullData *data = (SpoAlertFullData *)arg;
    /* close alert file */
#ifdef DEBUG
    printf("FullAlertCleanExitFunc\n");
#endif
    fclose(data->file);
    /* free memory from SpoAlertFullData */
    free(data);
}

void FullAlertRestartFunc(int signal, void *arg)
{
    SpoAlertFullData *data = (SpoAlertFullData *)arg;
    /* close alert file */
#ifdef DEBUG
    printf("FullAlertRestartFunc\n");
#endif
    fclose(data->file);
    /* free memory from SpoAlertFullData */
    free(data);
}

