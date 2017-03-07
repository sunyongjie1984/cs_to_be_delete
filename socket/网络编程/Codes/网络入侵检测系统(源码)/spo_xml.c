/*
** Copyright (C) 2000,2001 Carnegie Mellon University
**
** Snort XML Output Plug-in by the CERT Coordination Center
**       Jed Pickel    <jpickel@cert.org> <jed@pickel.net>
**       Roman Danyliw <rdd@cert.org>     <roman@danyliw.com>
**
** This plugin was developed as a part of the AIRCERT project.
**
** See README.xml for instructions
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

/* $Id: spo_xml.c,v 1.24 2001/01/02 08:06:01 roesch Exp $ */

#include "spo_xml.h"

extern PV pv;

#define ENABLE_SESSION_RESUME

#ifdef ENABLE_SNORT_TIMING
    #define SNORT_TIMING_FILE "snort_clnt.time"
    #include "snort_timing.c"
#endif

/* HTTPS response codes */
const char *https_return_messages[20] =
{
    "200 OK",
    "300 AUTH_CLIENT_OK",           /* AUTH */
    "301 AUTH_CLIENT_DENIED",
    "302 AUTH_CLIENT_UNKNOWN",
    "303 AUTH_CLIENT_IGNORED",
    "400 INPUT_COMMIT_OK",             /* DB */
    "401 INPUT_COMMIT_ERROR",
    "402 INPUT_EMPTY",
    "403 INPUT_MALFORMED",
    "404 INPUT_INVALID",
    "405 INPUT_PARSER_ERROR",
    "406 INPUT_INCOMPLETE",
    "407 INPUT_DB_READ_FAIL",
    "408 INPUT_OVERFLOW",
    "409 INPUT_IGNORED",
    "500 THROTTLE_OK",              /* THROTTLE */
    "501 THROTTLE_CONGESTION",
    "502 THROTTLE_QUENCH",
    "503 THROTTLE_DENIED",
    "504 THROTTLE_IGNORED"
};

unsigned int packet_cnt = 0;         /* counter of # of packets Snort received */

/*
 * Function: SetupXml()
 *
 * Purpose: Registers the output plugin keyword and initialization 
 *          function into the output plugin list.  This is the function that
 *          gets called from InitOutputPlugins() in plugbase.c.
 *
 * Arguments: None.
 *
 * Returns: void function
 *
 */
void SetupXml()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("xml", NT_OUTPUT_LOG, XmlInit);
#ifdef DEBUG
    printf(XMLMOD": Output plugin: xml is registered\n");
#endif
}

/*
 * Function: XmlInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void XmlInit(u_char *args)
{
    XmlData *d;

#ifdef ENABLE_SNORT_TIMING
    SNORT_TIME_START();
#endif 

    /* parse the argument list from the rules file */
    d = ParseXmlArgs(args);

    /* - Do a DNS name lookup if logging to a server,
     * - Setup a signal handler for SIGPIPE for socket errors
     */
    if(d->host)
    {
        d->host_ipaddr = gethostbyname(d->host);
        signal(SIGPIPE, BrokenNetConnection);
    }

    /* initialize output buffer */
    d->root = NULL;
    flush_data(d);

    /* what timezone are we in? */
    d->tz = GetLocalTimezone();

    /* find the IP address we are sniffing from */
    d->sensor_ip = GetIP(pv.interface);
    d->sensor_hostname = GetHostname();

    /* init the SSL context if using https */
#ifdef ENABLE_SSL
    if(d->protocol)
        if(!strcasecmp(d->protocol, "https"))
            init_snort_ssl_ctx(d);
#endif

        /* Add the processor function into the function list */
    if(!strncasecmp(d->facility,"log",3))
    {
        pv.log_plugin_active = 1;
        printf(XMLMOD"Using the \"log\" facility\n");
        AddFuncToOutputList(LogXml, NT_OUTPUT_LOG, d);
    }
    else
    {
        pv.alert_plugin_active = 1;
        printf(XMLMOD"Using the \"alert\" facility\n");
        AddFuncToOutputList(LogXml, NT_OUTPUT_ALERT, d);
    }

    AddFuncToCleanExitList(XmlExit, d);
    AddFuncToRestartList(XmlRestart, d);
}


/*
 * Function: ParseXmlArgs(char *)
 *
 * Purpose: Process the preprocessor arguements from the rules file and 
 *          initialize the preprocessor's data struct.
 *
 * Arguments: args => argument list
 *
 * Returns: void function
 *
 */
XmlData *ParseXmlArgs(char *args)
{
    XmlData *d;
    char * xarg;
    char * tmp;
    char filename[STD_BUF+1];
    time_t curr_time;
    struct tm *loc_time;
    char timebuf[10];
#ifdef ENABLE_SSL
    FILE *server_lst;
    char *ascii_cert;
    X509 *tmp_cert;
    EVP_PKEY *tmp_key;
#endif

    if(args == NULL)
    {
        FatalError(XMLMOD"You must supply arguments for xml plugin\n");
    }

    d = (XmlData *)malloc(sizeof(XmlData));

    /* Initialize default values */
    d->slist = NULL;
    d->sroot = NULL;
    d->file = NULL;
    d->host = NULL;
    d->port = 0;
    d->encoding = ENCODING_HEX;
    d->detail = DETAIL_FULL;
    d->protocol = NULL;
#ifdef ENABLE_SSL
    d->collector_name = NULL;
    d->issuer_cert = NULL;
    d->session = NULL;
    d->ssl_trace = 0; 
#endif


    xarg = strtok(args, ",");
    if(xarg != NULL)
    {
        if((!strncasecmp(xarg,"log",3)) || (!strncasecmp(xarg,"alert",5)))
            d->facility = xarg;
        else
            FatalError(XMLMOD"The first argument needs to be the logging facility");
    }
    else
        FatalError(XMLMOD"Invalid format for first argment");

    xarg = strtok(NULL, " =");
    while(xarg != NULL)
    {
        tmp = NULL;
        tmp = strtok(NULL, " ");
        if(!strncasecmp(xarg,"file",4))
        {
            d->file = tmp;
            printf(XMLMOD"Logging to %s\n", d->file);
        }
        if(!strncasecmp(xarg,"port",4))
        {
            d->port = atoi(tmp);
            printf(XMLMOD"Port set to %i\n", d->port);
        }
        if(!strncasecmp(xarg,"host",4))
        {
            d->host = tmp;
            printf(XMLMOD"Host set to %s\n", d->host);
        }
        if(!strncasecmp(xarg,"protocol",8))
        {
            d->protocol = tmp;
#ifndef ENABLE_SSL
            if(!strcasecmp(d->protocol, "https"))
                FatalError(XMLMOD"https support does not appear to be present in this build.\n");
#endif

            if(!strcasecmp(d->protocol, "http")
#ifdef ENABLE_SSL
               || !strcasecmp(d->protocol, "https")
#endif
               || !strcasecmp(d->protocol, "iap")
               || !strcasecmp(d->protocol, "tcp"))
                printf(XMLMOD"Using %s protocol\n", d->protocol);
            else
                FatalError(XMLMOD"The %s protocol is not supported\n", d->protocol);
        }
        if(!strncasecmp(xarg,"sanitize",8))
        {
            printf(XMLMOD"sanitizing %s\n", tmp);
            if(d->slist != NULL)
            {
                /*d->slist->nextNode = (IPNode*)malloc(sizeof(IPNode));
                d->slist = d->slist->nextNode;*/
                d->slist->next = (IpAddrSet *)calloc(sizeof(IpAddrSet), sizeof(char));
                d->slist = d->slist->next;
            }
            else
            {
                d->slist = (IpAddrSet *)calloc(sizeof(IpAddrSet), sizeof(char));
                d->sroot = d->slist;
                /*d->slist = (IPNode*)malloc(sizeof(IPNode));
                d->sroot = d->slist;*/
            }

            ParseIP(tmp, d->slist);
        }
        if(!strncasecmp(xarg,"encoding",6))
        {
            if(!strncasecmp(tmp, "hex", 3))
            {
                d->encoding = ENCODING_HEX;
            }
            else
            {
                if(!strncasecmp(tmp, "base64", 6))
                {
                    d->encoding = ENCODING_BASE64;
                }
                else
                {
                    if(!strncasecmp(tmp, "ascii", 5))
                    {
                        d->encoding = ENCODING_ASCII;
                    }
                    else
                    {
                        FatalError(XMLMOD"unknown encoding (%s)", tmp);
                    }
                }
            }
            printf(XMLMOD"data encoding = %s\n", tmp);
        }
        if(!strncasecmp(xarg,"detail",6))
        {
            if(!strncasecmp(tmp, "full", 4))
            {
                d->detail = DETAIL_FULL;
            }
            else
            {
                if(!strncasecmp(tmp, "fast", 4))
                {
                    d->detail = DETAIL_FAST;
                }
                else
                {
                    FatalError(XMLMOD"unknown detail level (%s)", tmp);
                }
            } 
            printf(XMLMOD"detail level  = %s\n", tmp);
        }

#ifdef ENABLE_SSL
        if(!strncasecmp(xarg, "cert", 4))
        {
            d->client_cert_filename = tmp;
            printf(XMLMOD"Certificate set to %s\n", d->client_cert_filename);

            tmp_cert = load_crt(d->client_cert_filename);
            if(!tmp_cert)
                FatalError(XMLMOD"invalid client certificate specified\n");

            X509_free(tmp_cert);
        }
        if(!strncasecmp(xarg, "key", 3))
        {
            d->client_key_filename = tmp;
            printf(XMLMOD"Private key set to %s\n", d->client_key_filename);

            tmp_key = load_key(d->client_key_filename);
            if(!tmp_key)
                FatalError(XMLMOD"invalid client key specified\n");

            EVP_PKEY_free(tmp_key);
        }
        if(!strncasecmp(xarg, "ca", 7))
        {
            d->issuer_filename = tmp;
            printf(XMLMOD"Issuer (CA) key set to %s\n", d->issuer_filename);

            /* Load the X.509 certificate of the issuer from disk */
            d->issuer_cert = load_crt(d->issuer_filename);
            if(!d->issuer_cert)
                FatalError(XMLMOD"invalid issuer certificate specified\n");
            ascii_cert = X509_NAME_oneline (X509_get_subject_name (d->issuer_cert),0,0);

            if(!ascii_cert)
                FatalError (XMLMOD"invalid issuer certificate\n");
            else
                printf(XMLMOD"[Issuer]=%s\n", ascii_cert);

            free(ascii_cert);         
        }
        if(!strncasecmp(xarg, "server", 6))
        {
            printf(XMLMOD"Logging server list in %s\n", tmp);
            if((server_lst = fopen ( tmp, "r")) == NULL)
                FatalError(XMLMOD"Could not open server list file (server): %s\n", tmp);
            else
            {
                d->collector_name = (char *) malloc(400);
                fgets(d->collector_name, 399, server_lst);
                if(d->collector_name[strlen(d->collector_name)-1] == '\n')
                    d->collector_name[strlen(d->collector_name)-1] = 0;
            }
            fclose(server_lst);
            if(d->collector_name)
                printf(XMLMOD"[Server]=%s\n", d->collector_name);
            else
                FatalError(XMLMOD"No valid servers found in (server) %s\n", tmp);

        }
        if(!strncasecmp(xarg, "https_trace", 11))
        {
            printf(XMLMOD"HTTPS trace logging file is %s\n", tmp);
            if((d->ssl_trace = fopen ( tmp, "a")) == NULL)
                FatalError(XMLMOD"Could not open HTTPS trace file: %s\n", tmp);
        }
#endif

#ifndef ENABLE_SSL
        /* catch requests for HTTPS support when it was _not_ built into snort */
        if(!strncasecmp(xarg, "cert", 4) || !strncasecmp(xarg, "key", 3) || 
           !strncasecmp(xarg, "ca", 7) || !strncasecmp(xarg, "server", 6))
            FatalError(XMLMOD"Attempting to use an HTTPS parameter ('%s') when this build does not appear to support it\n", xarg);
#endif

        xarg = strtok(NULL, "=");
    }

    if(d->host != NULL)
    {
        if(d->protocol != NULL)
        {
            if(!d->port)
            {
#ifdef ENABLE_SSL
                if(!strcasecmp(d->protocol, "https"))
                    d->port = 443;
#endif
                if(!strcasecmp(d->protocol, "http"))
                    d->port = 80;
                if(!strcasecmp(d->protocol, "iap"))
                    d->port = 8000;
            }
            /* Attempt to connect and post a heartbeat as a test */
        }
        else
            FatalError(XMLMOD"If you supply a host arguement you must also supply a protocol\n");
    }
    else if(d->file != NULL)
    {
        if(d->protocol != NULL) FatalError(XMLMOD"can not use a protocol argument with a file argument\n");
        if(d->port) FatalError(XMLMOD"can not use a port argument with a file argument\n");

        /* generate the unique string to append to the filename.
           liberated from: spo_tcpdump.c */
        bzero(timebuf, 10);
        curr_time = time(NULL);
        loc_time = localtime(&curr_time);
        strftime(timebuf, 91, "%m%d@%H%M", loc_time);

        if(d->file[0] != '/')
        {
            bzero(filename, STD_BUF);
            if(chrootdir)
                strncpy(filename, chrootdir, STD_BUF);
            strncat(filename, pv.log_dir, STD_BUF - strlen(filename));
            strncat(filename, "/", 1);
            strncat(filename, d->file, STD_BUF - strlen(filename));
        }
        else
            strncpy(filename, d->file, STD_BUF - strlen(filename));

        strncat(filename, "-", STD_BUF - strlen(filename));      
        strncat(filename, timebuf, STD_BUF - strlen(filename));      

        /* Create unique filename to log to */
        d->fptr = fopen(filename, "w");

        /* Write XML header info */
        fprintf(d->fptr, "%s", SNORTML_DECLARATION);
        fprintf(d->fptr, "%s", SNORTML_DOCTYPE);
        fprintf(d->fptr, "\n%s", SNORTML_FILE_BEGIN);

        if(!d->fptr) FatalError(XMLMOD"logfile (%s) open error (%s)\n", d->file, strerror(errno));

        setvbuf(d->fptr,(char *)NULL, _IOLBF, (size_t)0);
    }
    else if(d->protocol != NULL)
    {
        if(d->host == NULL) FatalError(XMLMOD" can not use the protocol argument without a host argument\n");
    }
    else FatalError(XMLMOD"Invalid configuration options");

#ifdef ENABLE_SSL
    if(d->protocol != NULL)
    {
        if((!strcasecmp(d->protocol, "https")) && (d->client_cert_filename == NULL))
            FatalError(XMLMOD": must specify a certificate ([cert] parameter) when using https (SSL)\n");

        if(!strcasecmp(d->protocol, "https") && d->client_key_filename == NULL)
            FatalError(XMLMOD": must specify a private key ([key] parameter) when using https (SSL)\n");

        if(!strcasecmp(d->protocol, "https") && d->collector_name == NULL)
            FatalError(XMLMOD": must specify a server ([server] parameter) when using https (SSL)\n");

        if(!strcasecmp(d->protocol, "https") && d->issuer_cert == NULL)
            FatalError(XMLMOD": must specify a CA certificate ([ca] parameter) when using https (SSL)\n");

        if((!strcasecmp(d->protocol, "https") || !strcasecmp(d->protocol, "http"))
           && d->file == NULL)
            FatalError(XMLMOD": must specify a remote script ([file] parameter) with http or https\n");
    }
#endif

    return d;
}

/*
 * Function: LogXml(Packet *, char * msg, void * data)
 *
 * Purpose: Generate the XML for a given packet and msg 
 *
 * Arguments: p   => pointer to the current packet data struct 
 *            msg => pointer to the signature message
 *            data => passed in by snort
 *
 * Returns: void function
 *
 */
void LogXml(Packet *p, char *msg, void *arg)
{
    XmlData *d = (XmlData *)arg;

#ifdef ENABLE_SNORT_TIMING
    SNORT_TIME_MARK_START(packet_cnt);
#endif

    /* if (logging to a file) */
    if((d->host == NULL) && (!d->port) && (d->protocol == NULL))
        d->root = snml(d, p, msg);
    else
        addtag(d->root, snml(d, p, msg));

    d->count++;

    if(d->count >= MAX_QUEUE)
    {
        send_data(d);
        flush_data(d);
    }

#ifdef ENABLE_SNORT_TIMING
    /* #6 : Final Clean-up */
    SNORT_TIME_MARK();
    SNORT_TIME_MARK_END();
#endif
}

/*
 * Function: send_data(XmlData * data)
 *
 * Purpose: Write data to a file or over the network
 *
 * Arguments: data => pointer to an XmlData struct
 *
 * Returns: void function
 *
 */
void send_data(XmlData *d)
{
    char * output;
    char * ptr;
    int indent = 0;

    /* if d->root is empty there is nothing really to send */
    if(d->root == NULL)
        return;

    /* Turn the data into a string */
    output = (char *)malloc(MAX_ALERT_SIZE * (MAX_QUEUE + 2)); 
    ptr = output;

    /* Don't add the SNORTML header if logging to a file */
    if(!( (d->host == NULL) || (!d->port) || (d->protocol == NULL) ))
    {
        strncpy(ptr, SNORTML_DECLARATION, strlen(SNORTML_DECLARATION) + 1);
        strncat(ptr, SNORTML_DOCTYPE, strlen(SNORTML_DOCTYPE) + 1);

        ptr += strlen(SNORTML_DOCTYPE) + strlen(SNORTML_DECLARATION);
    }
    else
        indent = INDENT;

    ptr = tag2string(ptr, MAX_ALERT_SIZE * (MAX_QUEUE + 1), d->root, indent);
    strncat(ptr, "\n", 1);

    /* Write the XML to a file or send it over the network */
    if((d->host == NULL) || (!d->port) || (d->protocol == NULL))
    {
        fprintf(d->fptr, "%s", output);
        /*fflush(d->fptr);*/
    }
    else
    {
#ifdef ENABLE_SNORT_TIMING
        /* #1 : Client Alert Processing Time => Make XML */
        SNORT_TIME_MARK();
#endif
        /* send it over the network */
        send_data_network(d, output);
    }
    free(output); 
}

#ifdef ENABLE_SSL

void init_snort_ssl_ctx(XmlData *d)
/* Initializes an TLSv1 context */
{
    int err;

    SSLeay_add_ssl_algorithms();
    /* d->meth = SSLv2_client_method(); */
    /* d->meth = SSLv3_client_method(); */
    d->meth = TLSv1_client_method();
    SSL_load_error_strings();

    d->ctx = SSL_CTX_new (d->meth);
    CHK_NULL(d->ctx, XMLMOD_SSL": could not get a SSL context");

    SSL_CTX_set_verify(d->ctx, SSL_VERIFY_PEER, CertVerifyCB);
    SSL_CTX_set_default_verify_paths(d->ctx);

    if(! SSL_CTX_load_verify_locations(d->ctx, d->issuer_filename, NULL))
    {
        ErrorMessage(XMLMOD": Could not load the CA chain");
        return;
    }
    SSL_CTX_set_client_CA_list(d->ctx,SSL_load_client_CA_file(d->issuer_filename));

    /* inits Client Authentication parameters; sets the certificate and key */
    err = SSL_CTX_use_certificate_file (d->ctx, d->client_cert_filename, SSL_FILETYPE_PEM);
    CHK_NULL(err, XMLMOD_SSL": invalid client certificate specified in config");

    err = SSL_CTX_use_PrivateKey_file(d->ctx, d->client_key_filename, SSL_FILETYPE_PEM);
    CHK_NULL(err, XMLMOD_SSL": invalid client private key specified in config");

    SSL_CTX_set_session_cache_mode(d->ctx, SSL_SESS_CACHE_CLIENT);
    return;

    end:
    X509_free(d->issuer_cert);
    SSL_CTX_free (d->ctx);

    exit(-1);
}

int CertVerifyCB (int ok, X509_STORE_CTX *ctx)
{
    int errnum;

    errnum   = X509_STORE_CTX_get_error(ctx);
    if(errnum != X509_V_OK)
        ErrorMessage(XMLMOD": Authentication Error: CB : #%d : %s\n", errnum, X509_verify_cert_error_string(errnum));

    return 1;
}

EVP_PKEY * load_key(char *key_fname)
/* Loads a PEM encoded RSA Private key from disk into memory */
{
    BIO *in;
    EVP_PKEY *x=NULL;

    in=BIO_new(BIO_s_file_internal());

    if((in == NULL))
        goto error;

    if(!BIO_read_filename(in, key_fname))
        goto error;

    PEM_read_bio_PrivateKey(in,&x,NULL,NULL);

    error:
    BIO_free(in);

    return(x);
}

X509 * load_crt(char *ca_fname)
/* Loads a PEM encoded .CRT file from disk into memory */
{
    BIO *in;
    X509 *x=NULL;

    in=BIO_new(BIO_s_file_internal());

    if((in == NULL))
        goto error;

    if(!BIO_read_filename(in, ca_fname))
        goto error;

    PEM_read_bio_X509(in,&x,NULL,NULL);

    error:
    BIO_free(in);

    return(x);
}

int VerifyServerCertificate(X509 *current, char *valid_server, X509 *issuer)
/* Validates a certificate based on an issuer certificate. 
  
   By the time this routine is called SSLeay has ensure us that
   the 'current' certificate is signed by _our_ CA.  Therefore,
   we know that the server response at least came from inside our
   community of users.  The question now is whether:
   1. The integrity of the certificate is intact

   2. (TODO) The certificate has not expired or being used before 
      it is valid

   3. (TODO) Some notion of a CRL

   4. The server/user is a valid entity with which to communicate.
*/
{
    char *ascii_cert = NULL;
    int status = X509_V_OK;
    EVP_PKEY *issuer_pkey = NULL;

    /* Get the public key of the issuer (CA) */
    if((issuer_pkey = X509_get_pubkey(issuer)) == NULL)
        status = X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY;
    else
        /* Use the Issuer public key to validate the integrity 
           of the server's certificate */
        if(X509_verify(current, issuer_pkey) <= 0)
        status = X509_V_ERR_CERT_SIGNATURE_FAILURE;
    else
    {
        ascii_cert = X509_NAME_oneline (X509_get_subject_name (current),0,0);

        if(strcmp(ascii_cert, valid_server) != 0)
            status = X509_V_ERR_APPLICATION_VERIFICATION;
#ifdef DEBUG
        printf("Comparing to the expected server'%s' ?= to '%s'\n", 
               valid_server, ascii_cert);
#endif
    }

    EVP_PKEY_free(issuer_pkey);
    free(ascii_cert);

    return status;
}

#endif

void BrokenNetConnection(int signal)
{
    ErrorMessage(XMLMOD" : Remote connection terminated during logging. Alert dropped!\n");
}

void send_data_network(XmlData *d, char *output)
/* Sends the XML-formatted Snort output onto the wire: TCP socket, 
   HTTP, HTTPS
 */
{
#define POST_header_MAX 500

    /* socket data structures */
    struct sockaddr_in remote;
    int err;

    char POST_header[POST_header_MAX],
    *report = NULL;

#ifdef ENABLE_SSL
    /* int sent; */
    /* SSL connection data structures */
    SSL        *ssl = NULL;             /* particular ssl connection */
    X509       *server_cert;            /* X.509 certificate of server */

    /* SSL temporary */
#ifdef DEBUG
    char *ascii_cert_subject, 
    *ascii_cert_issuer;            /* ASCII text of X.509 certificate */
#endif
    SSLServerResponse *response = NULL; /* response codes of the mod_snort server */
    int  success_ssl_connect = 0;

#endif

    /* POST temporary variables */
    char rbuf[4096];                    /* raw HTTP server response */
    char content_line[25];              /* HTTP hdr: Content-Length: */
    char *script = NULL;                /* remote script to be executed */

    /* Catch all the empty alerts triggered by abnormal Snort termination */
    if(strstr(output, EMPTY_ALERT))
        return;

    ++packet_cnt;
    /* Open an socket connection */
    d->sk = socket(AF_INET,SOCK_STREAM,0);
    if(d->sk < 0)
    {
        ErrorMessage(XMLMOD" #%u : could not open connection to %s:%d."
                     "(socket - error #%d)\n",
                     packet_cnt, d->host, d->port, errno);
#ifdef ENABLE_SSL
        LogSSLMessage(d->ssl_trace, "Could not open connection (socket() fail)",
                      "<not stored>", "<not stored>", packet_cnt, d->protocol, d->host, d->port, script);
#endif

        return;
    }

    remote.sin_family=AF_INET;
    bcopy( d->host_ipaddr->h_addr,(char*)&remote.sin_addr, d->host_ipaddr->h_length);
    remote.sin_port= htons((unsigned short)d->port); 
    err = connect(d->sk,(struct sockaddr *)&remote,sizeof(remote));

    if(err != 0)
    {
        if(errno == 111)
            ErrorMessage(XMLMOD" #%u: Connection refused. No server found at %s:%d\n",
                         packet_cnt, d->host, d->port);
        else
            ErrorMessage(XMLMOD" #%u : could not open connection to %s:%d."
                         "(connect - error #%d)\n", 
                         packet_cnt, d->host, d->port, errno);
#ifdef ENABLE_SSL
        if(errno == 111)
            LogSSLMessage(d->ssl_trace, "Connection refused (connect() fail)",
                          "<not stored>", "<not stored>", packet_cnt, d->protocol, d->host, d->port, script);
        else
            LogSSLMessage(d->ssl_trace, "Could not open connection (connect() fail)",
                          "<not stored>", "<not stored>", packet_cnt, d->protocol, d->host, d->port, script);
#endif

        close(d->sk);
        return;
    }

#ifdef ENABLE_SSL
    /* Configure the socket to do SSL if neccessary */
    if(!strcasecmp(d->protocol, "https"))
    {     
        /* Allocate a new SSL connection */
        ssl = SSL_new (d->ctx);
        CHK_NULL(ssl, XMLMOD_SSL": Could not alloc an SSL structure\n");              
        SSL_set_fd (ssl, d->sk);           /* associate a file-desc with SSL */

#ifdef ENABLE_SESSION_RESUME
        /* Re-use (if had one) the previous session whereby preventing _very_ expensive 
         * crypto operations */
        if(d->session)
            if(!SSL_set_session(ssl, d->session))
            {
                /* had an error, most likely the cache has expired. So lets flag
                 * the d->session as NULL so that the newly negotiated session
                 * is saved 
                 */
                printf("Session Dropped from cache already\n");
                d->session = NULL;
            }
#endif

        err = SSL_connect (ssl);           /* connect() */
        CHK_SSL(err, XMLMOD_SSL": Could not open SSL connection (SSL_connect())");

#ifdef ENABLE_SESSION_RESUME
        /* If this is the first SSL_connect()/session, save the session */
        if(!d->session)
            d->session = SSL_get_session(ssl);
#endif
        success_ssl_connect = 1;

#ifdef DEBUG
        fprintf(stdout, " over SSL using [%s]\n", SSL_get_cipher(ssl));  fflush(0);
#endif

#ifdef ENABLE_SNORT_TIMING
        /* #2 : SSL Connection Setup Time */
        SNORT_TIME_MARK();
#endif

        /* Server Authentication - Get the Server's certificate */
        server_cert = SSL_get_peer_certificate (ssl);
        CHK_NULL(server_cert, XMLMOD_SSL": Null Server certificate\n"); 

#ifdef DEBUG
        ascii_cert_subject = X509_NAME_oneline (X509_get_subject_name (server_cert),0,0);
        CHK_NULL(ascii_cert_subject, XMLMOD_SSL": Could not parse the server certificate:subject");

        ascii_cert_issuer = X509_NAME_oneline (X509_get_issuer_name  (server_cert),0,0);
        CHK_NULL(ascii_cert_issuer, XMLMOD_SSL": Could not parse the server certificate:issuer");

        printf ("Server certificate: \n");
        printf ("  [subject]: %s\n", ascii_cert_subject);
        printf ("  [issuer]: %s\n", ascii_cert_issuer);

        free (ascii_cert_subject);
        free (ascii_cert_issuer);
#endif

        /* Validate the Server Certificate 
           
           By this point, SSLeay has given me a callback via CertVerifyCB() 
           on the following concerns:
            - Issuer of the server certificate is the one specified
   
           Now we must verify :
            - the integrity certificate  
            - the expiration dates
            - NO CRL is used
            - we actually want to speak to _this_ particular server.
         */
        if((err = VerifyServerCertificate(server_cert, d->collector_name, d->issuer_cert )) != X509_V_OK)
        {
            if(err == X509_V_ERR_APPLICATION_VERIFICATION)
                ErrorMessage(XMLMOD": #%u : Authentication Error: "
                             "The CN in the server certificate does not match the valid server name\n",
                             packet_cnt);
            else
                ErrorMessage(XMLMOD": #%u  : Authentication Error #%d : %s\n", 
                             packet_cnt, err, X509_verify_cert_error_string(err));
            goto end;
        }
#ifdef DEBUG
        else
            printf(XMLMOD": Authentication OK - (%d)\n", err);
#endif

        X509_free (server_cert);
    }
#endif

#ifdef ENABLE_SNORT_TIMING
    /* #3 : SSL Peer Server Authentication Time */
    SNORT_TIME_MARK();
#endif

    if(!strcasecmp(d->protocol, "http") || !strcasecmp(d->protocol, "https"))
    {
        script = (char *) malloc (strlen(d->file)+2);
        if(d->file[0] != '/')
        {
            strcpy(script, "/");
            strcat(script, d->file);
        }
        else
            strcpy(script, d->file);
    }

    /* Create POST preamble/header information */
    if(!strcasecmp(d->protocol, "http") || !strcasecmp(d->protocol, "https"))
    {
        sprintf(content_line, "Content-Length: %d\n", (int) strlen(output)+1);

        snprintf(POST_header, POST_header_MAX, "%s%s%s%s%s\n",
                 POST_HDR, script, HTTP_VERSION, CONTENT_TYPE, content_line);

        report = (char *) malloc(strlen(POST_header) + strlen(output) + 2);
        sprintf(report, "%s%s\n", POST_header, output);
    }

#ifdef DEBUG
    printf("=======================\n%s\n=============================\n", output);
#endif

    /* Write data on the wire */
    if(!strcasecmp(d->protocol, "tcp"))
    {
        err = write(d->sk, output, strlen(output));
        CHK_POS(err, XMLMOD": error sending Alert over TCP");
    }
    else if(!strcasecmp(d->protocol, "http"))
    {
        err = write(d->sk, report, strlen(report));
        CHK_POS(err, XMLMOD": error sending Alert over HTTP");
    }
#ifdef ENABLE_SSL
    else if(!strcasecmp(d->protocol, "https"))
    {
        err = SSL_write (ssl, report, strlen(report));    
        CHK_SSL(err, XMLMOD_SSL": error sending Alert over HTTPS");
    }
#endif

    /* Get the server response to the POST.
     * There is the underlying assumption that this response all fits in a 4K buffer.
     */
    if(!strcasecmp(d->protocol, "http"))
        err = read(d->sk, rbuf, 4096);
#ifdef ENABLE_SSL
    else if(!strcasecmp(d->protocol, "https"))
        err = SSL_read(ssl, rbuf, 4096);
#endif

    /* Process the Server response to POST */
    if(!strcasecmp(d->protocol, "http") || !strcasecmp(d->protocol, "https"))
    {
        rbuf[err] = '\0'; 

        /* Verify that got some response from the server.  No response
           usually indicates that we were not communicating with an 
           HTTP server */
        if(rbuf[0] == 0)
        {
            ErrorMessage(XMLMOD": #%u : no acknowledgement to the POSTed alert on '%s://%s:%d%s'.\n", 
                         packet_cnt, d->protocol, d->host, d->port, script);
#ifdef ENABLE_SSL
            LogSSLMessage(d->ssl_trace, "No Acknowledgement to POSTed alert",
                          output, "", packet_cnt, d->protocol, d->host, d->port, script);
#endif

            goto end;
        }

#ifdef DEBUG
        printf("\n%s\n", rbuf);
#endif

        /* Check that didn't get a HTTP related error */
        if(!( !strncasecmp(rbuf, HTTP_1_0_OK, strlen(HTTP_1_0_OK)) ||
              !strncasecmp(rbuf, HTTP_1_1_OK, strlen(HTTP_1_1_OK)) ))
        {
            ErrorMessage(XMLMOD": #%u : an HTTP server related error occured :\n"
                         "===========\n%s==========\n", packet_cnt, rbuf);
#ifdef ENABLE_SSL
            LogSSLMessage(d->ssl_trace, "HTTP server related error occured",
                          output, rbuf, packet_cnt, d->protocol, d->host, d->port, script);
#endif

            goto end;
        }
#ifdef ENABLE_SSL
        else if(!strcasecmp(d->protocol, "https"))
        {
            response = ProcessSSLServerResponse(rbuf);
            if(!response->malformed)
            {
                printf("#%u - SERVER SENT: (%d alerts parsed)\n"
                       "   o Auth=%s | Throttle=%s | Parser=%s\n",
                       packet_cnt, response->num_commit,
                       https_return_messages[response->auth], 
                       https_return_messages[response->throttle],
                       https_return_messages[response->commit]);
            }
            else
            {
                printf("SERVER SENT\n [malformed response received from server]\n");
                LogSSLMessage(d->ssl_trace, "Malformed response recieved from server",
                              output, rbuf, packet_cnt, d->protocol, d->host, d->port, script);
#ifdef DEBUG
                printf("%s\n", rbuf);
#endif
            }

            ++success_ssl_connect;
        }
#endif
    }

    end:

#ifdef ENABLE_SNORT_TIMING
    /* #4 : Get and Processes server response */
    SNORT_TIME_MARK();
#endif

    /* Close the connections */
#ifdef ENABLE_SSL
    if(!strcasecmp(d->protocol, "https") && success_ssl_connect)
        SSL_shutdown (ssl);
    else
#endif
        shutdown(d->sk, 2);

    free(script);
    free(report);

    close(d->sk); 

#ifdef ENABLE_SSL
    free(response);

    if(!strcasecmp(d->protocol, "https"))
    {
        SSL_free (ssl);
#ifndef ENABLE_SESSION_RESUME
        SSL_CTX_free (d->ctx);
#else
        /* Clear SSL cache if a successful SSL connection didn't occur.
         * Should a network error occur between the sensor and collector,
         * clearing the cache forces a full SSL key re-negotiation. This
         * is neccessary to prevent an expired key from sitting in the
         * cache and being used repeatedly by the client, despite the 
         * fact that it is no longer valid since the server may have
         * dumped his cache (e.g. due to a restart).
         */
        if(success_ssl_connect != 2)
            d->session = NULL;
#endif
    }
#endif

#ifdef DEBUG
    fprintf(stdout, "Closed the session on %s:%d\n", d->host, d->port);
#endif

#ifdef ENABLE_SNORT_TIMING
    /* #5 : Network Cleanup time */
    SNORT_TIME_MARK();
#endif
}


#ifdef ENABLE_SSL
void LogSSLMessage(FILE *ssl_trace, char *msg, char *output, char *server, unsigned int packet_cnt, 
                   char *protocol, char *host, unsigned int port, char *script)
{
    char str_time[30];
    time_t when;

    if(ssl_trace > 0)
    {
        time(&when);
        strftime (str_time, sizeof(str_time)-1, "%Y-%m-%d %H:%M:%S", localtime(&when));

        fprintf(ssl_trace, "===============================================================\n"
                "[%s] %s\n"
                "#%u - '%s://%s:%d%s'\n\n"
                "---------------------------------------------------------------\n"
                "%s\n"
                "---------------------------------------------------------------\n"
                "%s\n",
                str_time, msg, packet_cnt, protocol, host, port, script, output, server);  
        fflush(0);
    }
}


SSLServerResponse * ProcessSSLServerResponse(char *rbuf)
{
    SSLServerResponse *r;
    char *t, *t2, *error_ptr = NULL;
    int i;

    r = (SSLServerResponse *) malloc ( sizeof(SSLServerResponse) );

    if(!strstr(rbuf, "200 OK"))
        r->malformed = 1;
    else
    {
        r->malformed = 0;

        /* Get Authentication Information */
        r->auth = 0;
        for(i =  snort_return_msg_index(AUTH_CLIENT_OK); 
           i <= snort_return_msg_index(AUTH_CLIENT_IGNORED); i++)
        {
            if(strstr(rbuf, https_return_messages[i]))
            {
                r->auth = i;
                break;
            }
        }

#ifdef DEBUG
        printf("auth = %d  ", r->auth);      
#endif

        /* If server has not authenticated us, no throttle or
         *  input is checked 
         */
        if(r->auth != snort_return_msg_index(AUTH_CLIENT_OK))
        {
            r->throttle = snort_return_msg_index(THROTTLE_IGNORED);
            r->commit = snort_return_msg_index(INPUT_IGNORED);
            r->num_commit = 0;
            return r;
        }

        /* Get Throttle Information */
        r->throttle = 0;
        for(i  = snort_return_msg_index(THROTTLE_OK); 
           i <= snort_return_msg_index(THROTTLE_IGNORED); i++)
            if(strstr(rbuf, https_return_messages[i]))
            {
                r->throttle = i;
                break;
            }

#ifdef DEBUG
        printf("throttle = %d  ", r->throttle);
#endif

        /* If server has quench our stream, it has ignored our input */
        if(r->throttle == snort_return_msg_index(THROTTLE_QUENCH))
        {
            r->commit = snort_return_msg_index(INPUT_IGNORED);
            r->num_commit = 0;
            return r;
        }

        /* Get Parsing Information */
        r->commit = 0;
        for(i  = snort_return_msg_index(INPUT_COMMIT_OK); 
           i <= snort_return_msg_index(INPUT_IGNORED); i++)
            if(strstr(rbuf, https_return_messages[i]))
            {
                r->commit = i;
                break;
            }

        t = strstr(rbuf, https_return_messages[snort_return_msg_index(INPUT_COMMIT_OK)]);
        if(t)
        {
            /* break apart the string '### INPUT_COMMIT_OK (#)' */
            t2 = (char *) malloc ( strlen(t) + 1);
            strcpy(t2, t);
            strtok(t2, "(");        /* eats '### INPUT_COMMIT_OK (' */
            r->num_commit = strtol(strtok(NULL, ")"), &error_ptr, 10);

            /* If could not get the number commited return malformed */
            if(*error_ptr)
                r->malformed = 1;

            free(t2);
        }
        else
            r->num_commit = 0;
    }

#ifdef DEBUG
    printf("commit = %d\n", r->commit);
#endif

    if(!r->throttle || !r->auth)
        r->malformed = 1;

    return r;
}

int snort_return_msg_index(int msg_code)
{
    int index = 0;

    if(msg_code >= 200 && msg_code < 300)
        index += msg_code - 200;

    if(msg_code >= 300 && msg_code < 400)
        index += msg_code - 300 + SNORT_RETURN_MSG_200;

    if(msg_code >= 400 && msg_code < 500)
        index += msg_code - 400 + SNORT_RETURN_MSG_200 + SNORT_RETURN_MSG_300;

    if(msg_code >= 500 && msg_code < 600)
        index += msg_code - 500 + SNORT_RETURN_MSG_200
                 + SNORT_RETURN_MSG_300 + SNORT_RETURN_MSG_400;

    return index;
}

#endif

int srcSanitized(XmlData *d, Packet *p)
{
    /*IPNode * tmp = d->sroot;*/
    IpAddrSet *tmp = d->sroot;

    while(tmp)
    {
        if(p)
        {
            if(CheckAddrPort(tmp, 0, 0, p, ANY_SRC_PORT, CHECK_SRC))
                return 1;
        }
        tmp = tmp->next; 
    }
    return 0;
}

int dstSanitized(XmlData *d, Packet *p)
{
/*  IPNode * tmp = d->sroot;*/
    IpAddrSet *tmp = d->sroot;

    while(tmp)
    {
        if(p)
        {
            if(CheckAddrPort(tmp, 0, 0, p, ANY_DST_PORT, CHECK_DST))
                return 1;
        }
        tmp = tmp->next; 
    }
    return 0;
}

void flush_data(XmlData *d)
{
    if((d->host == NULL) && (!d->port) && (d->protocol != NULL))
        fflush(d->fptr);

    d->count = 0;
    if(d->root) freetag(d->root);

    if((d->host == NULL) && (!d->port) && (d->protocol == NULL))
        d->root = NULL;
    else
        d->root = newtag("report");
}

void freetag(Tag * root)
{
    int x;

    for(x=0; x < root->tags ; x++)
    {
#ifdef DEBUG
        printf(XMLMOD": Freeing tag (%s) %p\n", root->tag[x]->name, root->tag[x]); 
#endif
        freetag(root->tag[x]);
    }
    free(root->name);
    free(root->value);
    free(root->tag);

    for(x=0; x < root->opts ; x++)
    {
#ifdef DEBUG
        printf(XMLMOD": Freeing opt (%s) %p\n", root->opt[x]->name, root->opt[x]); 
#endif 
        if(root->opt[x]->value) free(root->opt[x]->value);
        if(root->opt[x]->name) free(root->opt[x]->name);
        free(root->opt[x]);
    }
    free(root->opt);
    free(root);
}

char *tag2string(char *buf, int size, Tag * ptr, int depth)
{
    int x;
    char *start;

    start = buf;

    buf[0] = '\n'; buf++;

    for(x=0; x < (depth); x++)
    {
        buf[0] = ' '; buf++;
    }

    snprintf(buf, MAX_LEFT, "<%s", ptr->name);
    buf += strlen(buf);

    for(x=0; x < ptr->opts; x++)
    {
        if(ptr->opt[x]->value[0] == '\0')
            snprintf(buf, MAX_LEFT, " %s=\"%d\"", ptr->opt[x]->name, 0);
        else
            snprintf(buf, MAX_LEFT, " %s=\"%s\"", ptr->opt[x]->name, ptr->opt[x]->value);
        buf += strlen(buf);
    }

    if((ptr->value) || (ptr->tag))
    {
        strncpy(buf, ">", MAX_LEFT);
        buf += strlen(buf);

        if(ptr->tag)
            for(x=0; x < ptr->tags; x++)
            {
                if(ptr->tag[x])
                {
                    strncpy(buf, tag2string(buf, MAX_LEFT, ptr->tag[x], depth + INDENT), MAX_LEFT);
                    buf += strlen(buf);
                }
            }

        if(ptr->value)
        {
            snprintf(buf, MAX_LEFT, "%s", ptr->value);
            buf += strlen(buf);
        }

        if(ptr->tag)
        {
            buf[0] = '\n'; buf++;

            for(x=0;x < (depth); x++)
            {
                buf[0] = ' '; buf++;
            }

            snprintf(buf, MAX_LEFT, "</%s>", ptr->name);
            buf += strlen(buf);
        }
        else
            snprintf(buf, MAX_LEFT, "</%s>", ptr->name);
        buf += strlen(buf);
    }
    else
    {
        strncpy(buf, "/>", MAX_LEFT);
        buf += strlen(buf);
    }

    return start;
}

Tag * addtag(Tag *parent, Tag *child)
{
    if(!parent->tag)
    {
        parent->tag = (Tag **)malloc(sizeof(Tag*));
    }
    parent->tag = (Tag **)realloc(parent->tag, sizeof(Tag*) * (parent->tags + 1));
    parent->tag[parent->tags] = child;
    parent->tags++;
    return parent;
} 

Tag * newtag(char * name)
{
    Tag * ptr;

    ptr = (Tag *)malloc(sizeof(Tag)); 
    ptr->name = (char *)malloc(strlen(name) + 1);
    strncpy(ptr->name, name, strlen(name) + 1);
    ptr->value = NULL;
    ptr->tag  = NULL;
    ptr->opt  = NULL;
    ptr->tags = 0;
    ptr->opts = 0;
    return ptr;
}

Tag * addopt(Tag * tag, char * name, char * value)
{
    if(!tag->opt)
    {
        tag->opt = (Attribute **)malloc(sizeof(Attribute *));
    }

    tag->opt = (Attribute **) realloc(tag->opt, sizeof(Attribute*) * (tag->opts + 1));

    tag->opt[tag->opts] = (Attribute *)malloc(sizeof(Attribute));
    tag->opt[tag->opts]->name = name;
    tag->opt[tag->opts]->value = value;
    tag->opts++;
    return tag;
}

Tag * addvalue(Tag * tag, char * val)
{
    if(tag->value)
    {
        free(tag->value);
    }

    if(val)
    {
        tag->value = val;
        strcpy(tag->value, val);
    }

    return tag;
}

Tag *snml(XmlData *d, Packet *p, char *msg)
{
    Tag *root, *sensor, *packet, *iphdr, *tmp, *option;
    int i;
    int sanitized_src;
    int sanitized_dst;

    sanitized_src = srcSanitized(d,p);
    sanitized_dst = dstSanitized(d,p);

    tmp = NULL;

    root = newtag("event");
    addopt(root, str2s("version"), str2s("1.0"));

    sensor = newtag("sensor");
    switch(d->encoding)
    {
        case ENCODING_HEX:
            addopt(sensor, str2s("encoding"), str2s("hex")); break;
        case ENCODING_BASE64:
            addopt(sensor, str2s("encoding"), str2s("base64")); break;
        case ENCODING_ASCII:
            addopt(sensor, str2s("encoding"), str2s("ascii")); break;
    }
    switch(d->detail)
    {
        case DETAIL_FAST:
            addopt(sensor, str2s("detail"), str2s("fast")); break;
        case DETAIL_FULL:
            addopt(sensor, str2s("detail"), str2s("full")); break;
    }

    if(pv.readmode_flag)
    {
        tmp = newtag("file");
        addvalue(tmp, str2s(pv.readfile));
    }
    else
    {
        tmp = newtag("ipaddr");
        addvalue(tmp, str2s(d->sensor_ip));
        addopt(tmp, str2s("version"), int2s(4));
        if(pv.interface)
        {
            addtag(sensor, addvalue(newtag("interface"), str2s(pv.interface)));
        }
    }
    addtag(sensor, tmp);
    addtag(sensor, addvalue(newtag("hostname"), str2s(d->sensor_hostname)));
    if(pv.pcap_cmd) addtag(sensor, addvalue(newtag("filter"), str2s(pv.pcap_cmd)));
    addtag(root, sensor);
    addtag(root, addvalue(newtag("signature"), str2s(msg)));

    if(p)
    {
        addtag(root, addvalue(newtag("timestamp"), GetTimestamp((time_t *)&p->pkth->ts.tv_sec, d->tz)));

        packet = newtag("packet");

        iphdr = newtag("iphdr");
        if(p->iph->ip_proto == IPPROTO_ICMP)
        {
            tmp = newtag("icmphdr");
            addopt(tmp, str2s("type"), int2s(p->icmph->type)); 
            addopt(tmp, str2s("code"), int2s(p->icmph->code)); 
            if(d->detail == DETAIL_FULL)
            {
                addopt(tmp, str2s("csum"), int2s(p->icmph->csum)); 
                if(p->ext)
                {
                    if(p->ext->id)
                        addopt(tmp, str2s("id"), int2s(ntohs(p->ext->id)));
                    if(p->ext->seqno)
                        addopt(tmp, str2s("seq"), int2s(ntohs(p->ext->seqno)));
                }
            }
        }
        else if(p->iph->ip_proto == IPPROTO_TCP)
        {
            tmp = newtag("tcphdr");
            addopt(tmp, str2s("sport"), int2s(ntohs(p->tcph->th_sport)));
            addopt(tmp, str2s("dport"), int2s(ntohs(p->tcph->th_dport)));
            addopt(tmp, str2s("flags"), int2s(p->tcph->th_flags));
            if(d->detail == DETAIL_FULL)
            {
                addopt(tmp, str2s("seq"), int2s(ntohl(p->tcph->th_seq)));
                addopt(tmp, str2s("ack"), int2s(ntohl(p->tcph->th_ack)));
                if(p->tcph->th_off) addopt(tmp, str2s("off"), int2s(p->tcph->th_off));
                if(p->tcph->th_x2) addopt(tmp, str2s("res"), int2s(p->tcph->th_x2));
                addopt(tmp, str2s("win"), int2s(ntohs(p->tcph->th_win)));
                addopt(tmp, str2s("csum"), int2s(ntohs(p->tcph->th_sum)));
                if(ntohs(p->tcph->th_urp)) addopt(tmp, str2s("urp"), int2s(ntohs(p->tcph->th_urp)));
                for(i=0 ; i < (int)p->tcp_option_count; i++)
                {
                    option = newtag("option");
                    addopt(option, str2s("code"), int2s(p->tcp_options[i].code));
                    if(p->tcp_options[i].len)
                    {
                        addopt(option, str2s("len"), int2s(p->tcp_options[i].len));
                        if((d->encoding == ENCODING_HEX) || (d->encoding == ENCODING_ASCII))
                            addvalue(option, hex(p->tcp_options[i].data, p->tcp_options[i].len));
                        else
                            addvalue(option, base64(p->tcp_options[i].data, p->tcp_options[i].len));
                    }
                    addtag(tmp, option);
                }
            }
        }
        else if(p->iph->ip_proto == IPPROTO_UDP)
        {
            tmp = newtag("udphdr");
            addopt(tmp, str2s("sport"), int2s(ntohs(p->udph->uh_sport)));
            addopt(tmp, str2s("dport"), int2s(ntohs(p->udph->uh_dport)));
            if(d->detail == DETAIL_FULL)
            {
                addopt(tmp, str2s("len"), int2s(ntohs(p->udph->uh_len)));
                addopt(tmp, str2s("csum"), int2s(ntohs(p->udph->uh_chk)));
            }
        }

        if(d->detail == DETAIL_FULL)
        {
            if(!(sanitized_src || sanitized_dst))
            {
                if(p->dsize)
                {
                    switch(d->encoding)
                    {
                        case ENCODING_ASCII:
                            addtag(tmp, addvalue(newtag("data"), ascii(p->data, p->dsize))); break;
                        case ENCODING_HEX:
                            addtag(tmp, addvalue(newtag("data"), hex(p->data, p->dsize))); break;
                        case ENCODING_BASE64:
                            addtag(tmp, addvalue(newtag("data"), base64(p->data, p->dsize))); break;
                    }
                }
            }
        }

        addtag(iphdr, tmp);

        if(d->detail == DETAIL_FULL)
        {
            for(i=0 ; i < (int)p->ip_option_count; i++)
            {
                option = newtag("option");
                addopt(option, str2s("code"), int2s(p->ip_options[i].code));
                if(p->ip_options[i].len)
                {
                    addopt(option, str2s("len"), int2s(p->ip_options[i].len));
                    if((d->encoding == ENCODING_HEX) || (d->encoding == ENCODING_ASCII))
                        addvalue(option, hex(p->ip_options[i].data, p->ip_options[i].len));
                    else
                        addvalue(option, base64(p->ip_options[i].data, p->ip_options[i].len));
                }
                addtag(iphdr, option);
            }
        }

        if(sanitized_src)
            addopt(iphdr, str2s("saddr"), str2s("xxx.xxx.xxx.xxx"));
        else
            addopt(iphdr, str2s("saddr"), str2s(inet_ntoa(p->iph->ip_src)));

        if(sanitized_dst)
            addopt(iphdr, str2s("daddr"), str2s("xxx.xxx.xxx.xxx"));
        else
            addopt(iphdr, str2s("daddr"), str2s(inet_ntoa(p->iph->ip_dst)));

        if(p->iph->ip_proto) addopt(iphdr, str2s("proto"), int2s(p->iph->ip_proto));

        if(d->detail == DETAIL_FULL)
        {
            if(p->iph->ip_ver) addopt(iphdr, str2s("ver"), int2s(p->iph->ip_ver));
            if(p->iph->ip_hlen) addopt(iphdr, str2s("hlen"), int2s(p->iph->ip_hlen));
            if(p->iph->ip_tos) addopt(iphdr, str2s("tos"), int2s(p->iph->ip_tos));
            if(p->iph->ip_len) addopt(iphdr, str2s("len"), int2s(ntohs(p->iph->ip_len)));
            if(p->iph->ip_id)  addopt(iphdr, str2s("id"), int2s(ntohs(p->iph->ip_id)));
            if(p->frag_flag)  addopt(iphdr, str2s("flags"), int2s(p->frag_flag));
            if(p->frag_offset) addopt(iphdr, str2s("off"), int2s(ntohs(p->frag_offset)));
            if(p->iph->ip_ttl) addopt(iphdr, str2s("ttl"), int2s(p->iph->ip_ttl));
            if(p->iph->ip_csum) addopt(iphdr, str2s("csum"), int2s(ntohs(p->iph->ip_csum)));
        }

        addtag(packet, iphdr); 
        addtag(root, packet);
    }
    else
    {
        addtag(root, addvalue(newtag("timestamp"), GetCurrentTimestamp()));
    }

    return root;
}

void XmlExit(int signal, void *arg)
{
    XmlData *d = (XmlData *)arg;
#ifdef DEBUG
    printf(XMLMOD":LogXmlExit\n");
#endif

    send_data(d);
    flush_data(d);
    if((d->host == NULL) || (!d->port) || (d->protocol == NULL))
    {
        fprintf(d->fptr, "%s", SNORTML_FILE_END);
        fclose(d->fptr);
    }

#ifdef ENABLE_SSL
    X509_free(d->issuer_cert);
    free(d->collector_name);
    if(d->ssl_trace > 0)
        fclose (d->ssl_trace);
#ifdef ENABLE_SESSION_RESUME
    SSL_CTX_free (d->ctx);
#endif
#endif

#ifdef ENABLE_SNORT_TIMING
    SNORT_TIME_END();
#endif

}

void XmlRestart(int signal, void *arg)
{
    XmlData *d = (XmlData *)arg;
#ifdef DEBUG
    printf(XMLMOD":LogXmlRestart\n");
#endif

    send_data(d);
    flush_data(d);
    if((d->host == NULL) || (!d->port) || (d->protocol == NULL))
    {
        fprintf(d->fptr, "%s", SNORTML_FILE_END);
        fclose(d->fptr);
    }

#ifdef ENABLE_SSL
    if(d->ssl_trace > 0)
        fclose (d->ssl_trace);
    X509_free(d->issuer_cert);
    free(d->collector_name);
#ifdef ENABLE_SESSION_RESUME
    SSL_CTX_free (d->ctx);
#endif
#endif
}
