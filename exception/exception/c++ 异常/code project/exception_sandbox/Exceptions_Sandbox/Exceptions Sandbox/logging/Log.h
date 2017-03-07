/********************************************************************
  Purpose:	Logging utility.
  Created:	8 Aug, 2009
  Author:	Yalon Lotan
*********************************************************************/
#pragma once
#include "LoggingLibExport.h"

#include <string>

using std::string;

/*
 * Logs the given message.
 * Function takes a variable number of arguments, as in sprintf.
 *
 * Parameter: const string messageFormat - either the whole message, or a format control string
 * Parameter: ... - optional additional arguments to fill the messageFormat
 */
void LOGGING_LIB_EXT_API Trace(const string messageFormat, ...);