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
#include <apr_file_io.h>
#include <apr_strings.h>
#include <apr_network_io.h>

/* default listen port number */
#define DEF_LISTEN_PORT		8081

/* default socket backlog number. SOMAXCONN is a system default value */
#define DEF_SOCKET_BACKLOG	SOMAXCONN

/* default buffer size */
#define BUFSIZE			4096

/* useful macro */
#define CRLF_STR		"\r\n"

static apr_status_t do_listen(apr_socket_t **sock, apr_pool_t *mp);
static int do_serv_task(apr_socket_t *serv_sock, apr_pool_t *mp);

/**
 * Network server sample code
 * Just response to an HTTP GET request, but this is not a true HTTP server.
 * For example, you can test this program as follows,
 *  $ wget http://localhost:8081/etc/hosts
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    apr_socket_t *s;/* listening socket */

    apr_initialize();
    apr_pool_create(&mp, NULL);

    rv = do_listen(&s, mp);
    if (rv != APR_SUCCESS) {
        goto error;
    }

    while (1) {
        apr_socket_t *ns;/* accepted socket */
    
        rv = apr_socket_accept(&ns, s, mp);
        if (rv != APR_SUCCESS) {
            goto error;
        }
        /* it is a good idea to specify socket options for the newly accepted socket explicitly */
        apr_socket_opt_set(ns, APR_SO_NONBLOCK, 0);
        apr_socket_timeout_set(ns, -1);
        
        if (!do_serv_task(ns, mp)) {
            goto error;
        }
        apr_socket_close(ns);
    }

    apr_pool_destroy(mp);
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
 * Create a listening socket, and listen it.
 */
static apr_status_t do_listen(apr_socket_t **sock, apr_pool_t *mp)
{
    apr_status_t rv;
    apr_socket_t *s;
    apr_sockaddr_t *sa;
    
    rv = apr_sockaddr_info_get(&sa, NULL, APR_INET, DEF_LISTEN_PORT, 0, mp);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    
    rv = apr_socket_create(&s, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* it is a good idea to specify socket options explicitly.
     * in this case, we make a blocking socket as the listening socket */
    apr_socket_opt_set(s, APR_SO_NONBLOCK, 0);
    apr_socket_timeout_set(s, -1);
    apr_socket_opt_set(s, APR_SO_REUSEADDR, 1);/* this is useful for a server(socket listening) process */

    rv = apr_socket_bind(s, sa);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    rv = apr_socket_listen(s, DEF_SOCKET_BACKLOG);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    *sock = s;
    return rv;
}

/**
 * Response a file content as a simple HTTP response protocol.
 * We assume that the request's first line is 'GET file-path HTTP/1.x'
 */
static int do_serv_task(apr_socket_t *sock, apr_pool_t *mp)
{
    int is_firstline = TRUE;
    const char *filepath = NULL;

    /* read all inputs from the client */
    /* XXX This is not a precise parser of HTTP requests.
     * Don't misunderstand that apr_socket_recv() returns a line. It just returns a chunk of bytes */
    while (1) {
	char buf[BUFSIZE];
	apr_size_t len = sizeof(buf) - 1;/* -1 for a null-terminated */

	apr_status_t rv = apr_socket_recv(sock, buf, &len);
	if (rv == APR_EOF || len == 0) {
	    break;
        }
        buf[len] = '\0';/* apr_socket_recv() doesn't return a null-terminated string */
        
        if (is_firstline) {
            char **tokens;
            apr_tokenize_to_argv(buf, &tokens, mp);
            if (tokens[0] && tokens[1] && strcmp(tokens[0], "GET") == 0) {
                filepath = tokens[1];
            }
            is_firstline = FALSE;
        }
        if (strstr(buf, CRLF_STR CRLF_STR)) {/* expect the end of the request. no guarantee */
            break;
        }
    }

    if (filepath) {
        apr_status_t rv;
        apr_file_t *fp;
        
        if ((rv = apr_file_open(&fp, filepath, APR_READ, APR_OS_DEFAULT, mp)) == APR_SUCCESS) {
            const char *resp_hdr;
            apr_size_t len;
            const char *resp_body;

            apr_finfo_t finfo;
            apr_file_info_get(&finfo, APR_FINFO_SIZE, fp);
            
            resp_hdr = apr_psprintf(mp, "HTTP/1.0 200 OK" CRLF_STR "Content-Length: %" APR_OFF_T_FMT CRLF_STR CRLF_STR, finfo.size);
            len = strlen(resp_hdr);
            apr_socket_send(sock, resp_hdr, &len);
            
            resp_body = apr_palloc(mp, finfo.size);
            len = finfo.size;
            apr_file_read(fp, (void*)resp_body, &len);
            apr_socket_send(sock, resp_body, &len);
            
            return TRUE;
        }
    }
    
    /* error case */
    {
        const char *resp_hdr = "HTTP/1.0 404 Not Found" CRLF_STR CRLF_STR;
        apr_size_t len = strlen(resp_hdr);
        apr_socket_send(sock, resp_hdr, &len);
        return TRUE;
    }
}
