/* $Id: spp_template.c,v 1.2 2000/11/13 06:01:25 roesch Exp $ */
/* Snort Preprocessor Plugin Source File Template */

/* spp_template 
 * 
 * Purpose:
 *
 * Preprocessors perform some function *once* for *each* packet.  This is
 * different from detection plugins, which are accessed depending on the
 * standard rules.  When adding a plugin to the system, be sure to 
 * add the "Setup" function to the InitPreprocessors() function call in 
 * plugbase.c!
 *
 * Arguments:
 *   
 * This is the list of arguements that the plugin can take at the 
 * "preprocessor" line in the rules file
 *
 * Effect:
 *
 * What the preprocessor does.  Check out some of the default ones 
 * (e.g. spp_http_decode) for a good example of this description.
 *
 * Comments:
 *
 * Any comments?
 *
 */

/* your preprocessor header file goes here */
#include "spp_template.h"

/* external globals from rules.c */
extern char *file_name;
extern int file_line;

/* If you need to instantiate the preprocessor's data structure, do it here */
TemplateData SomeData;

/*
 * Function: SetupTemplate()
 *
 * Purpose: Registers the preprocessor keyword and initialization 
 *          function into the preprocessor list.  This is the function that
 *          gets called from InitPreprocessors() in plugbase.c.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 */
void SetupTemplate()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterPreprocessor("keyword", TemplateInit);

#ifdef DEBUG
    printf("Preprocessor: Template is setup...\n");
#endif
}


/*
 * Function: TemplateInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void TemplateInit(u_char *args)
{
#ifdef DEBUG
    printf("Preprocessor: Template Initialized\n");
#endif

    /* parse the argument list from the rules file */
    ParseTemplateArgs(args);

    /* Set the preprocessor function into the function list */
    AddFuncToPreprocList(PreprocFunction);
    AddFuncToCleanExitList(PreprocCleanExitFunction);
    AddFuncToRestartList(PreprocRestartFunction);
}



/*
 * Function: ParseTemplateArgs(char *)
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
void ParseTemplateArgs(char *args)
{
    /* your parsing function goes here, check out the other spp files
       for examples */
}


/*
 * Function: PreprocFunction(Packet *)
 *
 * Purpose: Perform the preprocessor's intended function.  This can be
 *          simple (statistics collection) or complex (IP defragmentation)
 *          as you like.  Try not to destroy the performance of the whole
 *          system by trying to do too much....
 *
 * Arguments: p => pointer to the current packet data struct 
 *
 * Returns: void function
 *
 */
void PreprocFunction(Packet *p)
{

    /* your preproc function goes here.... */

}


void PreprocCleanExitFunction(int signal)
{
       /* clean exit code goes here */
}

void PreprocRestartFunction(int signal)
{
       /* restart code goes here */
}
