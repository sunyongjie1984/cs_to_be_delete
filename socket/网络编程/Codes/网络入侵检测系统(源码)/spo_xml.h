/*
** Copyright (C) 2000,2001 Carnegie Mellon University
**
** Author: Jed Pickel <jpickel@cert.org>, <jed@pickel.net>
**       : Roman Danyliw <rdd@cert.org>, <roman@danyliw.com>
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


#ifndef __SPO_XML_H__
#define __SPO_XML_H__

#include "snort.h"

#ifdef ENABLE_SSL
/* conflict with m_len definition in sys/mbuf.h on openbsd*/
    #ifdef m_len
        #undef m_len
    #endif
    #include <openssl/crypto.h>
    #include <openssl/x509.h>
    #include <openssl/x509_vfy.h>
    #include <openssl/pem.h>
    #include <openssl/ssl.h>
    #include <openssl/err.h>  
#endif

#define SNORTML_DECLARATION "<?xml version=\"1.0\" encoding=\"UTF-8\">\n"
#define SNORTML_DOCTYPE "<!DOCTYPE snort-message-version-0.1 PUBLIC>\n"
#define SNORTML_FILE_BEGIN "<file>\n"
#define SNORTML_FILE_END "\n</file>\n"

/* HTTP header information */
#define HTTP_1_0_OK "HTTP/1.0 200 OK"
#define HTTP_1_1_OK "HTTP/1.1 200 OK"
#define POST_HDR "POST "
#define HTTP_VERSION " HTTP/1.0\n"
#define CONTENT_TYPE "Content-type: multipart/form-data; boundary= \n"

#define EMPTY_ALERT "<report/>"

#define INDENT 2
#define MAX_TAG_NAME 10
#define MAX_TAG_VALUE 2048
#define MAX_ATTRIBUTE_NAME 10
#define MAX_ATTRIBUTE_VALUE 16
#define MAX_QUEUE 0
#define MAX_ALERT_SIZE 8192
#define MAX_SECOND_WAIT 60
#define MAX_LEFT size - (buf - start)
#define XMLMOD "xml_plugin: "
#define XMLMOD_SSL XMLMOD" SSL_ERROR"

typedef struct _IPNode
{
    u_long address;
    u_long netmask;
    struct _IPNode *nextNode;
} IPNode;

typedef struct _Attribute
{
    char * name;
    char * value;
} Attribute;

typedef struct _Tag
{
    int tags;
    int opts;
    char * name;
    char * value;
    Attribute ** opt;
    struct _Tag ** tag;
} Tag;

typedef struct _XmlData
{
    char * sensor_ip;
    char * sensor_hostname;
    char * host;
    char * file;
    char * facility;
    char * protocol;
    int  encoding;
    int  detail;
    struct hostent *host_ipaddr;

#ifdef ENABLE_SSL
    char * client_key_filename;
    char * client_cert_filename;
    char * issuer_filename;
    X509 * issuer_cert;
    char * collector_name;
    SSL_CTX *ctx;           /* global SSL context */
    SSL_METHOD *meth;       /* SSL CipherSpec */
    SSL_SESSION *session;   /* current SSL session */
    FILE * ssl_trace;
#endif

    Tag * root;
    /*IPNode * slist;
    IPNode * sroot;*/
    IpAddrSet *slist;
    IpAddrSet *sroot;
    FILE * fptr;
    int tz;
    int count;
    int port;
    int sk;
    int max_size;
} XmlData;

#ifdef ENABLE_SSL

    #define SNORT_RETURN_MSG_200 1
    #define SNORT_RETURN_MSG_300 4
    #define SNORT_RETURN_MSG_400 10
    #define SNORT_RETURN_MSG_500 5

    #define   SNORT_OK            200

    #define   AUTH_CLIENT_OK      300
    #define   AUTH_CLIENT_DENIED  301
    #define   AUTH_CLIENT_UNKNOWN 302
    #define   AUTH_CLIENT_IGNORED 303

    #define   INPUT_COMMIT_OK     400
    #define   INPUT_COMMIT_ERROR  401
    #define   INPUT_EMPTY         402
    #define   INPUT_MALFORMED     403
    #define   INPUT_INVALID       404
    #define   INPUT_PARSER_ERROR  405
    #define   INPUT_INCOMPLETE    406
    #define   INPUT_DB_READ_FAIL  407
    #define   INPUT_OVERFLOW      408
    #define   INPUT_IGNORED       409

    #define   THROTTLE_OK         500
    #define   THROTTLE_CONGESTION 501
    #define   THROTTLE_QUENCH     502
    #define   THROTTLE_DENIED     503
    #define   THROTTLE_IGNORED    504

typedef struct _SSLServerResponse
{
    unsigned int  auth,
    throttle,
    commit,
    malformed;
    int num_commit;
} SSLServerResponse;

#endif

/* Required plugin functions */
void SetupXml();
void XmlInit(u_char *);
void LogXml(Packet *, char *, void *);
void XmlExit(int, void *);
void XmlRestart(int, void *);

/* Argument Parsing */
XmlData *ParseXmlArgs(char *);

/* Result data goes here */
void send_data(XmlData *);
void send_data_network(XmlData *, char *);
void BrokenNetConnection(int);

#ifdef ENABLE_SSL
/* HTTPS & X.509 routines */
void                init_snort_ssl_ctx(XmlData *);
X509 *              load_crt(char *);
EVP_PKEY *          load_key(char *);
int                 CertVerifyCB (int, X509_STORE_CTX *);
int                 VerifyServerCertificate(X509 *, char *, X509 *);
SSLServerResponse * ProcessSSLServerResponse(char *rbuf);
int                 snort_return_msg_index(int);
void LogSSLMessage (FILE *, char *, char *, char *, unsigned int, char *, char *, unsigned int, char *);
#endif

/* Functions particular to the Snort DTD */
Tag *snml(XmlData *, Packet *, char *);

/* XML Data Structure Functions */
Tag *newtag(char *);
Tag *addtag(Tag*, Tag*);
Tag *addopt(Tag*, char*, char*);
void freetag(Tag*);
void flush_data(XmlData *);

/* Recursively go through data and generate XML */
char *tag2string(char *, int, Tag *, int);

/* Functions required for sanitization */
int srcSanitized(XmlData *, Packet *);
int dstSanitized(XmlData *, Packet *);

#ifdef ENABLE_SSL

    #define CHK_NULL(x,msg)  if ((x)==0) \
 { ErrorMessage("%s (at #%d). Dropping packet.\n", msg, __LINE__); goto end; }

    #define CHK_ERR(err,msg) \
 if ((err)==-1) \
 { \
   ErrorMessage("SSL Error: %s (at #%d). Dropping packet.\n", msg, __LINE__) \
   goto end; \
 }

    #define CHK_SSL(err,msg) \
 if ((err)==-1) \
 { \
    ErrorMessage("%s (at #%d). Dropping packet.\n", msg, __LINE__); \
    ERR_print_errors_fp(stderr); \
    goto end; \
 }
#endif

#define CHK_POS(err, msg) \
 if ((err) < 1) \
 { \
    ErrorMessage("%s (at #%d). Dropping packet.\n", msg, __LINE__); \
    goto end; \
 }

#endif  /* __SPO_XML_H__ */




