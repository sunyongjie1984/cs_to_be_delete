#pragma once



#include <apr_pools.h>
#include <apr_network_io.h>
#include <apr_poll.h>
#include <apr_errno.h>

#include "log.h"


#define __END_FLAG__ "\r\n"
#define __ERROR_INFO_LEN__ 4096
//#define __LOGX_INFO_LEN__ 4096
#define __IO_BUFFER_LEN__ 1024 * 100
#define __RECV_BUFF_LEN__ 256
// 
// typedef void (* __PRINTX)(char *);
// 
// extern void __cdecl LOGX(const int level, const char * f, ...);


#define IS_FAILED_RETURN(ok_val, rv, err_msg) { if ((ok_val) != (rv)) { apr_err_print(0, rv, (err_msg)); return (rv); } }

#define BUFSIZE			4096


typedef apr_status_t (* __REACTOR_ENTRY)(apr_pool_t * mp, apr_socket_t * descriptor, apr_pollset_t * reactor, apr_socket_t * acceptor, void * data);
typedef apr_status_t (* __IOCP_REACTOR_ENTRY)(apr_pool_t * mp, apr_socket_t * channel, apr_pollcb_t * iocp_reactor, void * data);


#define __QUERY_TICK_COUNT_FLAG__ 1
#define __SEND_UDP_TEST__ 0

extern apr_sockaddr_t * g_udp_sa;
extern apr_socket_t * g_udp_connector;


extern void UDPTest_send(const char * log, double t);

#define __QUERY_TICK_COUNT(log, ret) {  \
if (__QUERY_TICK_COUNT_FLAG__) {		\
LARGE_INTEGER frequency;				\
LARGE_INTEGER counter;					\
double dFreq,dCounter;					\
QueryPerformanceFrequency(&frequency);	\
QueryPerformanceCounter(&counter);		\
dFreq   =(double)(frequency.QuadPart);	\
dCounter=(double)(counter.QuadPart);	\
(ret) = (dCounter/dFreq*1000.0*1000.0);	\
if (__SEND_UDP_TEST__)					\
UDPTest_send((log), ret);}}


typedef struct __tagCHANNEL
{
	apr_socket_t	* channel;
	apr_pool_t		* mpchild;
	apr_time_exp_t	time_exp;
}
CHANNEL;

extern void
apr_err_print(
						const int				level,
						apr_status_t			rv,
						char					* msg
						);


extern apr_status_t
TCPAcceptor_create(
						apr_pool_t				* mp,
						const apr_port_t		listen_port,
						apr_socket_t			** acceptor
						);

extern apr_status_t
TCPAcceptor_start(
						apr_pool_t				* mp,
						apr_socket_t			* acceptor,
						apr_socket_t			** channel,
						apr_pool_t				** mp_child
						);

extern void
TCPChannel_init(
						apr_socket_t			* channel
						);

extern apr_status_t
TCPConnector_create(
						apr_pool_t				* mp,
						const char				* hostname,
						const apr_port_t		listen_port,
						apr_socket_t			** connector
						);

extern apr_status_t
Reactor_append_fd(
						apr_pool_t				* mp,
						apr_pollset_t			* reactor,
						apr_socket_t			* s
						);

extern apr_status_t
Reactor_remove_fd(
						apr_pool_t				* mp,
						apr_pollset_t			* reactor,
						apr_socket_t			* s
						);

extern apr_status_t
Reactor_create(
						apr_pool_t				* mp,
						apr_uint32_t			size,
						apr_pollset_t			** reactor,
						apr_uint32_t			wakeup_flags = 0/*APR_POLLSET_WAKEABLE*/
						);

extern apr_status_t
Reactor_destroy(
						apr_pollset_t			* reactor
						);

extern apr_status_t
Reactor_wakeup(
						apr_pollset_t			* reactor
						);

extern apr_status_t
Reactor_await(
						apr_pool_t				* mp,
						apr_pollset_t			* reactor,
						apr_socket_t			* acceptor,
						apr_interval_time_t		timeout,
						__REACTOR_ENTRY			__reactor_entry,
						void					* data
						);


extern apr_status_t
IOCPReactor_create(
						apr_pool_t				* mp,
						apr_uint32_t			size,
						apr_pollcb_t			** iocp_reactor
						);

extern apr_status_t
IOCPReactor_await(
						apr_pollcb_t			* iocp_reactor,
						apr_interval_time_t		timeout,
						apr_pollcb_cb_t			__IOCP_REACTOR_ENTRY,
						void					* baton
						);

extern apr_status_t
IOCPReactor_append_fd(
						apr_pool_t				* mp,
						apr_pollcb_t			* iocp_reactor,
						apr_socket_t			* s
						);

extern apr_status_t
IOCPReactor_remove_fd(
						apr_pool_t				* mp,
						apr_pollcb_t			* iocp_reactor,
						apr_socket_t			* s
						);


extern apr_status_t
UDPConnector_create(
						apr_pool_t				* mp,
						const char				* hostname,
						const apr_port_t		listen_port,
						apr_sockaddr_t			** sa,
						apr_socket_t			** connector
						);

extern apr_status_t
UDPConnector_send(
						apr_socket_t			* connector,
						apr_sockaddr_t			* where,
						apr_int32_t				flags,
						const char				* buf,
						apr_size_t				* len
						);

extern apr_status_t
UDPAcceptor_create(
						apr_pool_t				* mp,
						const apr_port_t		listen_port,
						apr_sockaddr_t			** sa,
						apr_socket_t			** acceptor
						);

extern apr_status_t
UDPAcceptor_recv(
						apr_sockaddr_t			* from,
						apr_socket_t			* acceptor,
						apr_int32_t				flags,
						char					* buf,
						apr_size_t				* len
						);