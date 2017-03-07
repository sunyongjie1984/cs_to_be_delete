#ifndef _COMHEAD_H_
#define _COMHEAD_H_

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <malloc.h>

typedef int SOCKET;
typedef struct sockaddr_in 	SOCKADDR;
typedef struct timeval		TIME;	
typedef struct sigaction	SIGACTION;

typedef  unsigned char       UCHAR;
typedef  unsigned short      USHORT;
typedef  char                BYTE;
typedef  unsigned char       UBYTE;
typedef  unsigned int        UINT;

typedef  unsigned long       ULONG;

#ifndef SGN
#define SGN( a ) ((a) >= 0   ? 1   : -1)
#endif

#ifndef MIN
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#endif

#ifndef ABS
#define ABS(x)   ((x) >= 0 ? (x) : -(x))
#endif

#define INVALID_SOCKET		-1

#define ERR_SUCCESS		0
#define ERR_SOCKET		-1
#define ERR_NETWORK	 	2		
#define ERR_NOT_FINISH		3	
#define ERR_TIMEOUT		4
#define ERR_NODATA		5
#define ERR_PACKET_TOOLONG	6
#define ERR_NOT_IMPLEMENT	7
#define ERR_GENERAL		8

#endif

