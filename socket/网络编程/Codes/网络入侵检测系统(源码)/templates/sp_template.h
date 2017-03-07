/* $Id: sp_template.h,v 1.1.1.1 2000/08/07 02:42:59 roesch Exp $ */
/* Snort Detection Plugin Header File Template */

/* This file gets included in plugbase.h when it is integrated into the rest 
 * of the program.  Sometime in The Future, I'll whip up a bad ass Perl script
 * to handle automatically loading all the required info into the plugbase.*
 * files.
 */

#ifndef __SP_TEMPLATE_H__
#define __SP_TEMPLATE_H__

#include "snort.h"

#define PLUGIN_TEMPLATE_NUMBER  0

typedef struct _TemplateData
{
    /* your data structure info goes here */

} TemplateData;

void TemplateInit(char *, OptTreeNode *, int);
void SetupTemplate();
void TemplateRuleParseFunction(char *, OptTreeNode *);
int TemplateDetectorFunction(Packet *, struct _OptTreeNode *, OptFpList *);

#endif  /* __SP_TEMPLATE_H__ */
