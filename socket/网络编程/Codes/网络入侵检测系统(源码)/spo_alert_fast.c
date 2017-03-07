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

/* $Id: spo_alert_fast.c,v 1.3 2001/01/02 08:06:01 roesch Exp $ */

/* spo_alert_fast
 * 
 * Purpose:  output plugin for fast alerting
 *
 * Arguments:  alert file
 *   
 * Effect:
 *
 * Alerts are written to a file in the snort fast alert format
 *
 * Comments:   Allows use of fast alerts with other output plugin types
 *
 */

/* output plugin header file */
#include "spo_alert_fast.h"

/* external globals from rules.c */
extern char *file_name;
extern int file_line;

/*
 * Function: SetupFastAlert()
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
void SetupFastAlert()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("alert_fast", NT_OUTPUT_ALERT, FastAlertInit);

#ifdef DEBUG
    printf("Output plugin: FastAlert is setup...\n");
#endif
}


/*
 * Function: FastAlertInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void FastAlertInit(u_char *args)
{
    SpoAlertFastData *data;

#ifdef DEBUG
    printf("Output: FastAlert Initialized\n");
#endif

    pv.alert_plugin_active = 1;

    /* parse the argument list from the rules file */
    data = ParseFastAlertArgs(args);

#ifdef DEBUG
    printf("Linking FastAlert functions to call lists...\n");
#endif

    /* Set the preprocessor function into the function list */
    AddFuncToOutputList(SpoAlertFast, NT_OUTPUT_ALERT, data);
    AddFuncToCleanExitList(FastAlertCleanExitFunc, data);
    AddFuncToRestartList(FastAlertRestartFunc, data);
}

void SpoAlertFast(Packet *p, char *msg, void *arg)
{
    SpoAlertFastData *data = (SpoAlertFastData *)arg;
    return AlertFast(p, msg, data->file);
}

/*
 * Function: ParseFastAlertArgs(char *)
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
SpoAlertFastData *ParseFastAlertArgs(char *args)
{
    char **toks;
    int num_toks;
    char *filename;
    SpoAlertFastData *data;

    data = (SpoAlertFastData *)malloc(sizeof(SpoAlertFastData));

#ifdef DEBUG
    printf("ParseFastAlertArgs: %s\n", args);
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

void FastAlertCleanExitFunc(int signal, void *arg)
{
    SpoAlertFastData *data = (SpoAlertFastData *)arg;
    /* close alert file */
#ifdef DEBUG
    printf("FastAlertCleanExitFunc\n");
#endif
    fclose(data->file);
    /*free memory from SpoAlertFastData */
    free(data);
}

void FastAlertRestartFunc(int signal, void *arg)
{
    SpoAlertFastData *data = (SpoAlertFastData *)arg;
    /* close alert file */
#ifdef DEBUG
    printf("FastAlertRestartFunc\n");
#endif
    fclose(data->file);
    /*free memory from SpoAlertFastData */
    free(data);
}

