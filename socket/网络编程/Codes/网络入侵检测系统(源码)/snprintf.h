#ifndef __SNPRINTF_H__
#define __SNPRINTF_H__

#ifndef HAVE_SNPRINTF

#include <stdio.h>
#include "config.h"
#include <sys/types.h>
#include <string.h>

#ifdef __STDC__

#include <stdarg.h>

# define VA_LOCAL_DECL  va_list ap;
# define VA_START(f)    va_start(ap, f)
# define VA_END         va_end(ap)

#else /* __STDC__ */

#ifndef WIN32 /* If included it will produce macro redefintion errors. All needed macros are in stdio.h */
	#include <varargs.h>
#endif

# define VA_LOCAL_DECL  va_list ap;
# define VA_START(f)    va_start(ap)
# define VA_END         va_end(ap)

#endif /* __STDC__ */

#ifndef __P
#include "cdefs.h"
#endif /* ! __P */

#ifndef QUAD_T
# define QUAD_T unsigned long
#endif /* ! QUAD_T */



#define tTd(flag, level)        (tTdvect[flag] >= (u_char)level)
#define MAXSHORTSTR  203             /* max short string length */

u_char   tTdvect[100];   /* trace vector */

int snprintf(char *, size_t , const char *, ...);
int vsnprintf(char *, size_t, const char *, va_list);
char *shortenstring(register const char *, int);


#endif /* HAVE_SNPRINTF */
#endif /* __SNPRINTF_H__ */
