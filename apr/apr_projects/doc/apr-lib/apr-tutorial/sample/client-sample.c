/**
 * apr tutorial sample code
 * http://dev.ariel-networks.com/apr/
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <assert.h>

#include <apr_general.h>
#include <apr_network_io.h>
#include <apr_strings.h>

/* default connect hostname */
#define DEF_REMOTE_HOST		"localhost"

/* default connect port number */
#define DEF_REMOTE_PORT		8081

/* default socket timeout */
#define DEF_SOCK_TIMEOUT	(APR_USEC_PER_SEC * 30)

/* default buffer size */
#define BUFSIZE			4096

/* useful macro */
#define CRLF_STR		"\r\n"

static apr_status_t do_connect(apr_socket_t **sock, apr_pool_t *mp);
static int do_client_task(apr_socket_t *sock, const char *filepath, apr_pool_t *mp);

/**
 * Network client sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    apr_socket_t *s;

    if (argc != 2) {
        printf("usage: %s filepath\n", argv[0]);
        return -1;
    }
    
    apr_initialize();
    apr_pool_create(&mp, NULL);

    rv = do_connect(&s, mp);
    if (rv != APR_SUCCESS) {
        goto error;
    }
    
    rv = do_client_task(s, argv[1], mp);
    if (rv != APR_SUCCESS) {
        goto error;
    }
    apr_socket_close(s);
    
    apr_terminate();
    return 0;

 error:
    {
        char errbuf[256];
        apr_strerror(rv, errbuf, sizeof(errbuf));
        printf("error: %d, %s\n", rv, errbuf);
    }
    apr_terminate();
    return -1;
}

/**
 * Connect to the remote host
 */
static apr_status_t do_connect(apr_socket_t **sock, apr_pool_t *mp)
{
    apr_sockaddr_t *sa;
    apr_socket_t *s;
    apr_status_t rv;
    
    rv = apr_sockaddr_info_get(&sa, DEF_REMOTE_HOST, APR_INET, DEF_REMOTE_PORT, 0, mp);
    if (rv != APR_SUCCESS) {
	return rv;
    }
    
    rv = apr_socket_create(&s, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp);
    if (rv != APR_SUCCESS) {
	return rv;
    }

    /* it is a good idea to specify socket options explicitly.
     * in this case, we make a blocking socket with timeout. */
    apr_socket_opt_set(s, APR_SO_NONBLOCK, 1);
    apr_socket_timeout_set(s, DEF_SOCK_TIMEOUT);

    rv = apr_socket_connect(s, sa);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* see the tutorial about the reason why we have to specify options again */
    apr_socket_opt_set(s, APR_SO_NONBLOCK, 0);
    apr_socket_timeout_set(s, DEF_SOCK_TIMEOUT);

    *sock = s;
    return APR_SUCCESS;
}

/**
 * Send a request as a simple HTTP request protocol.
 * Write the received response to the standard output until the EOF.
 */
static apr_status_t do_client_task(apr_socket_t *sock, const char *filepath, apr_pool_t *mp)
{
    apr_status_t rv;
    const char *req_hdr = apr_pstrcat(mp, "GET ", filepath, " HTTP/1.0" CRLF_STR CRLF_STR, NULL);
    apr_size_t len = strlen(req_hdr);
    rv = apr_socket_send(sock, req_hdr, &len);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    {
        apr_file_t *stdout;
        apr_file_open_stdout(&stdout, mp);

        while (1) {
            char buf[BUFSIZE];
            apr_size_t len = sizeof(buf);
            
            apr_status_t rv = apr_socket_recv(sock, buf, &len);
            if (rv == APR_EOF || len == 0) {
                break;
            }
            apr_file_write(stdout, buf, &len);
        }
        apr_file_close(stdout);
    }

    return rv;
}
