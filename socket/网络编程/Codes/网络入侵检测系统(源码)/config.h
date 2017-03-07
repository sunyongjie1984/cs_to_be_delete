/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* #undef _ALL_SOURCE */
#endif

/* Define if you have the ANSI C header files.  */
/* #undef STDC_HEADERS */

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
#define WORDS_LITTLEENDIAN 1

/* $Id: acconfig.h,v 1.3 2000/10/31 11:38:43 fygrave Exp $ */
#define PACKAGE "snort"
/* #undef BSDI */
/* #undef FREEBSD */
/* #undef IRIX */
/* #undef AIX */
/* #undef LINUX */
/* #undef OPENBSD */
#define WIN32 1
/* #undef PCAP_TIMEOUT_IGNORED */
/* #undef SOLARIS */
/* #undef STUPID_SOLARIS_CHECKSUM_BUG */
/* #undef SUNOS */
/* #undef HPUX */
/* #undef OSF1 */
/* #undef WORDS_MUSTALIGN */
/* #undef ENABLE_POSTGRESQL */
/* #undef u_int8_t */
/* #undef u_int16_t */
/* #undef u_int32_t */
/* #undef NEED_DECL_PRINTF */
/* #undef NEED_DECL_FPRINTF */
/* #undef NEED_DECL_SYSLOG */
/* #undef NEED_DECL_PUTS */
/* #undef NEED_DECL_PUTC */
/* #undef NEED_DECL_FPUTS */
/* #undef NEED_DECL_FPUTC */
/* #undef NEED_DECL_FOPEN */
/* #undef NEED_DECL_FCLOSE */
/* #undef NEED_DECL_FWRITE */
/* #undef NEED_DECL_FFLUSH */
/* #undef NEED_DECL_GETOPT */
/* #undef NEED_DECL_BZERO */
/* #undef NEED_DECL_BCOPY */
/* #undef NEED_DECL_MEMSET */
/* #undef NEED_DECL_STRTOL */
/* #undef NEED_DECL_STRCASECMP */
/* #undef NEED_DECL_STRNCASECMP */
/* #undef NEED_DECL_STRERROR */
/* #undef NEED_DECL_PERROR */
/* #undef NEED_DECL_SOCKET */
/* #undef NEED_DECL_SENDTO */
/* #undef NEED_DECL_VSNPRINTF */
/* #undef NEED_DECL_STRTOUL */
#define ERRLIST_PREDEFINED 1

/* Define if you have the snprintf function.  */
#define HAVE_SNPRINTF 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the strtoul function.  */
/* #undef HAVE_STRTOUL */

/* Define if you have the vsnprintf function.  */
/* #undef HAVE_VSNPRINTF */

/* Define if you have the <paths.h> header file.  */
/* #undef HAVE_PATHS_H */

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <strings.h> header file.  */
/* #undef HAVE_STRINGS_H */

/* Define if you have the <sys/sockio.h> header file.  */
/* #undef HAVE_SYS_SOCKIO_H */

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the m library (-lm).  */
/* #undef HAVE_LIBM */

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the pcap library (-lpcap).  */
#define HAVE_LIBPCAP 1

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */

/* Name of package */
#define PACKAGE "snort"

/* Version number of package */
#ifdef ENABLE_MYSQL
	#define VERSION "1.7-MySQL-WIN32"
#else
	#ifdef ENABLE_RESPONSE
		#define VERSION "1.7-FlexRESP-WIN32"
	#else
		#define VERSION "1.7-WIN32"
	#endif
#endif

/* you have this cuz autoheader is dumb */
/* #undef NEED_DECL_ */
