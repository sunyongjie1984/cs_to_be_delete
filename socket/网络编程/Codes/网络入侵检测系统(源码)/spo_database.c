/*
** Copyright (C) 2000,2001 Carnegie Mellon University
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

/* $Id: spo_database.c,v 1.14 2001/01/18 20:46:59 jpickel Exp $ */

/* Snort Database Output Plug-in by Jed Pickel <jed@pickel.net>
 * 
 * See the README.database file with this distribution 
 * documentation or the snortdb web site for configuration
 * information
 *
 * Web Site: http://www.incident.org/snortdb
 * */

#include "spo_database.h"
extern PV pv;

/* If you want extra debugging information for solving database 
   configuration problems, uncomment the following line. */
/* #define DEBUG */

/*
 * Function: SetupDatabase()
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
void SetupDatabase()
{
    /* link the preprocessor keyword to the init function in 
       the preproc list */
    RegisterOutputPlugin("database", NT_OUTPUT_ALERT, DatabaseInit);

#ifdef DEBUG
    printf("database(debug): database plugin is registered...\n");
#endif
}

/*
 * Function: DatabaseInit(u_char *)
 *
 * Purpose: Calls the argument parsing function, performs final setup on data
 *          structs, links the preproc function into the function list.
 *
 * Arguments: args => ptr to argument string
 *
 * Returns: void function
 *
 */
void DatabaseInit(u_char *args)
{
    DatabaseData *data;
    char * select0;
    char * select1;
    char * insert0;

    /* parse the argument list from the rules file */
    data = ParseDatabaseArgs(args);

    /* find a unique name for sensor if one was not supplied as an option */
    if(!data->sensor_name)
    {
#ifdef WIN32
	data->sensor_name = GetUniqueName((char *)print_interface(pv.interfaces[0]));
#else
        data->sensor_name = GetUniqueName((char *)pv.interfaces[0]);
#endif
        printf("database:   sensor name = %s\n", data->sensor_name);
    }

    data->tz = GetLocalTimezone();

    /* allocate memory for configuration queries */
    select0 = (char *)calloc(MAX_QUERY_LENGTH, sizeof(char));
    select1 = (char *)calloc(MAX_QUERY_LENGTH, sizeof(char));
    insert0 = (char *)calloc(MAX_QUERY_LENGTH, sizeof(char));

    if(pv.pcap_cmd == NULL)
    {
        snprintf(insert0, MAX_QUERY_LENGTH, 
                 "INSERT INTO sensor (hostname, interface, detail, encoding) "
                 "VALUES ('%s','%s','%u','%u')", 
#ifdef WIN32
		 data->sensor_name, print_interface(pv.interfaces[0]), data->detail, data->encoding);
#else
                 data->sensor_name, pv.interfaces[0], data->detail, data->encoding);
#endif
        snprintf(select0, MAX_QUERY_LENGTH, 
                 "SELECT sid FROM sensor WHERE hostname = '%s' "
                 "AND interface = '%s' AND detail = '%u' AND "
                 "encoding = '%u' AND filter IS NULL",
#ifdef WIN32
		 data->sensor_name, print_interface(pv.interfaces[0]), data->detail, data->encoding);
#else
                 data->sensor_name, pv.interfaces[0], data->detail, data->encoding);
#endif
    }
    else
    {
        snprintf(select0, MAX_QUERY_LENGTH, 
                 "SELECT sid FROM sensor WHERE hostname = '%s' "
                 "AND interface = '%s' AND filter ='%s' AND "
                 "detail = '%u' AND encoding = '%u'",
#ifdef WIN32
		 data->sensor_name, print_interface(pv.interfaces[0]), pv.pcap_cmd,
#else
                 data->sensor_name, pv.interfaces[0], pv.pcap_cmd,
#endif
                 data->detail, data->encoding);
        snprintf(insert0, MAX_QUERY_LENGTH, 
                 "INSERT INTO sensor (hostname, interface, filter,"
                 "detail, encoding) "
                 "VALUES ('%s','%s','%s','%u','%u')", 
#ifdef WIN32
		 data->sensor_name, print_interface(pv.interfaces[0]), pv.pcap_cmd,
#else
                 data->sensor_name, pv.interfaces[0], pv.pcap_cmd,
#endif
                 data->detail, data->encoding);
    }

    Connect(data);

    data->sid = Select(select0,data);
    if(data->sid == 0)
    {
        Insert(insert0,data);
        data->sid = Select(select0,data);
        if(data->sid == 0)
        {
            ErrorMessage("database: Problem obtaining SENSOR ID (sid) from %s->%s->sensor\n", data->dbtype,data->dbname);
            FatalError("\n When this plugin starts, a SELECT query is run to find the sensor id for the\n currently running sensor. If the sensor id is not found, the plugin will run\n an INSERT query to insert the proper data and generate a new sensor id. Then a\n SELECT query is run to get the newly allocated sensor id. If that fails then\n this error message is generated.\n\n Some possible causes for this error are:\n   * the user does not have proper INSERT or SELECT privileges\n   * the sensor table does not exist\n\n If you are _absolutly_ certain that you have the proper privileges set and\n that your database structure is built properly please let me know if you\n continue to get this error. You can contact me at (jed@pickel.net).\n\n");
        }
    }

    printf("database:     sensor id = %u\n", data->sid);

    snprintf(select1, MAX_QUERY_LENGTH,
             "SELECT max(cid) FROM event WHERE sid = '%u'", data->sid);

    data->cid = Select(select1,data);
    data->cid++;

    /* free memory */
    free(select0);
    free(select1);
    free(insert0);

    /* Add the processor function into the function list */
    if(!strncasecmp(data->facility,"log",3))
    {
        pv.log_plugin_active = 1;
        printf("database: using the \"log\" facility\n");
        AddFuncToOutputList(Database, NT_OUTPUT_LOG, data);
    }
    else
    {
        pv.alert_plugin_active = 1;
        printf("database: using the \"alert\" facility\n");
        AddFuncToOutputList(Database, NT_OUTPUT_ALERT, data);
    }

    AddFuncToCleanExitList(SpoDatabaseCleanExitFunction, data);
    AddFuncToRestartList(SpoDatabaseRestartFunction, data); 
}

/*
 * Function: ParseDatabaseArgs(char *)
 *
 * Purpose: Process the preprocessor arguements from the rules file and 
 *          initialize the preprocessor's data struct.
 *
 * Arguments: args => argument list
 *
 * Returns: void function
 *
 */
DatabaseData *ParseDatabaseArgs(char *args)
{
    DatabaseData *data;
    char *dbarg;
    char *a1;
    char *type;
    char *facility;

    data = (DatabaseData *)calloc(1, sizeof(DatabaseData));

    if(args == NULL)
    {
        ErrorMessage("database: you must supply arguments for database plugin\n");
        DatabasePrintUsage();
        FatalError("");
    }

    data->dbtype = NULL;
    data->sensor_name = NULL;
    data->facility = NULL;
    data->encoding = ENCODING_HEX;
    data->detail = DETAIL_FULL;

    facility = strtok(args, ", ");
    if(facility != NULL)
    {
        if((!strncasecmp(facility,"log",3)) || (!strncasecmp(facility,"alert",5)))
        {
            data->facility = facility;
        }
        else
        {
            ErrorMessage("database: The first argument needs to be the logging facility\n");
            DatabasePrintUsage();
            FatalError("");
        }
    }
    else
    {
        ErrorMessage("database: Invalid format for first argment\n"); 
        DatabasePrintUsage();
        FatalError("");
    }

    type = strtok(NULL, ", ");

    if(type == NULL)
    {
        ErrorMessage("database: you must enter the database type in configuration file as the second argument\n");
        DatabasePrintUsage();
        FatalError("");
    }

    /* print out and test the capability of this plugin */
    printf("database: compiled support for ( ");


#ifdef ENABLE_MYSQL
    printf("%s ",MYSQL);
    if(!strncasecmp(type,MYSQL,5))
    {
        data->dbtype = type; 
    }
#endif
#ifdef ENABLE_POSTGRESQL
    printf("%s ",POSTGRESQL);
    if(!strncasecmp(type,POSTGRESQL,10))
    {
        data->dbtype = type; 
    }
#endif
#ifdef ENABLE_UNIXODBC
    printf("%s ",UNIXODBC);
    if(!strncasecmp(type,UNIXODBC,8))
    {
        data->dbtype = type; 
    }
#endif
#ifdef ENABLE_ORACLE
    printf("%s ",ORACLE);
    if(!strncasecmp(type,ORACLE,5))
    {
      data->dbtype = type; 
    }
#endif

    printf(")\n");

    printf("database: configured to use %s\n", type);

    if(data->dbtype == NULL)
    {
        ErrorMessage("database: %s support is not compiled in this copy\n\n", type);
        FatalError(" Check your configuration file to be sure you did not mis-spell \"%s\".\n If you did not, you will need to reconfigure and recompile ensuring that\n you have set the correct options to the configure script. Type \n \"./configure --help\" to see options for the configure script.\n\n", type);
    }

    dbarg = strtok(NULL, " =");
    while(dbarg != NULL)
    {
        a1 = NULL;
        a1 = strtok(NULL, ", ");
        if(!strncasecmp(dbarg,"host",4))
        {
            data->host = a1;
            printf("database:          host = %s\n", data->host);
        }
        if(!strncasecmp(dbarg,"port",4))
        {
            data->port = a1;
            printf("database:          port = %s\n", data->port);
        }
        if(!strncasecmp(dbarg,"user",4))
        {
            data->user = a1;
            printf("database:          user = %s\n", data->user);
        }
        if(!strncasecmp(dbarg,"password",8))
        {
            printf("database: password is set\n");
            data->password = a1;
        }
        if(!strncasecmp(dbarg,"dbname",6))
        {
            data->dbname = a1;
            printf("database: database name = %s\n", data->dbname);
        }
        if(!strncasecmp(dbarg,"sensor_name",11))
        {
            data->sensor_name = a1;
            printf("database:   sensor name = %s\n", data->sensor_name);
        }
        if(!strncasecmp(dbarg,"encoding",6))
        {
            if(!strncasecmp(a1, "hex", 3))
            {
                data->encoding = ENCODING_HEX;
            }
            else
            {
                if(!strncasecmp(a1, "base64", 6))
                {
                    data->encoding = ENCODING_BASE64;
                }
                else
                {
                    if(!strncasecmp(a1, "ascii", 5))
                    {
                        data->encoding = ENCODING_ASCII;
                    }
                    else
                    {
                        FatalError("database: unknown  (%s)", a1);
                    }
                }
            }
            printf("database: data encoding = %s\n", a1);
        }
        if(!strncasecmp(dbarg,"detail",6))
        {
            if(!strncasecmp(a1, "full", 4))
            {
                data->detail = DETAIL_FULL;
            }
            else
            {
                if(!strncasecmp(a1, "fast", 4))
                {
                    data->detail = DETAIL_FAST;
                }
                else
                {
                    FatalError("database: unknown detail level (%s)", a1);
                }
            } 
            printf("database: detail level  = %s\n", a1);
        }
        dbarg = strtok(NULL, "=");
    } 

    if(data->dbname == NULL)
    {
        ErrorMessage("database: must enter database name in configuration file\n\n");
        DatabasePrintUsage();
        FatalError("");
    }

    return data;
}

void FreeQueryNode(SQLQuery * node)
{
    if(node)
    {
        FreeQueryNode(node->next);
        free(node->val);
        free(node);
    }
}

SQLQuery * NewQueryNode(SQLQuery * parent, int query_size)
{
    SQLQuery * rval;

    if(query_size == 0)
    {
        query_size = MAX_QUERY_LENGTH;
    }

    if(parent)
    {
        while(parent->next)
        {
            parent = parent->next;
        } 
        parent->next = (SQLQuery *)malloc(sizeof(SQLQuery));
        rval = parent->next;
    }
    else
    {
        rval = (SQLQuery *)malloc(sizeof(SQLQuery));
    }

    rval->val = (char *)malloc(query_size);
    rval->next = NULL;

    return rval;
}  

/*
 * Function: Database(Packet *, char * msg, void *arg)
 *
 * Purpose: Insert data into the database
 *
 * Arguments: p   => pointer to the current packet data struct 
 *            msg => pointer to the signature message
 *
 * Returns: void function
 *
 */
void Database(Packet *p, char *msg, void *arg)
{
    DatabaseData *data = (DatabaseData *)arg;
    SQLQuery * query;
    SQLQuery * root;
    char * tmp;
    char * tmp_not_escaped;
    int i;

    char sip[16];
    char dip[16];
    char *s0,*s1,*s2,*s3,*d0,*d1,*d2,*d3;


    query = NewQueryNode(NULL, 0);
    root = query;

    if(msg == NULL)
    {
        msg = "";
    }

    /*** Build the query for the Event Table ***/
    if(p != NULL)
    {
        tmp = GetTimestamp((time_t *)&p->pkth->ts.tv_sec, data->tz);
    }
    else
    {
        tmp = GetCurrentTimestamp();
    }
    snprintf(query->val, MAX_QUERY_LENGTH, 
             "INSERT INTO event (sid,cid,signature,timestamp) VALUES "
             "('%u', '%u', '%s', '%s')",
             data->sid, data->cid, msg, tmp);
    free(tmp); 

/* We do not log fragments! They are assumed to be handled 
    by the fragment reassembly pre-processor */

    if(p != NULL)
    {
/* THE FOLLOWING BLOCK OF CODE IS GOING TO GET WIPED OUT IF TRANSITION
   TO THE ONE FOUR BYTE INTEGER REPRESENTATION FOR IP ADDRESSES */
/******************************************************************/
            /* have to do this since inet_ntoa is f^@%&d up and writes to
               a static memory location */
            strncpy(sip, inet_ntoa(p->iph->ip_src), 16);
            strncpy(dip, inet_ntoa(p->iph->ip_dst), 16);
            s0 = strtok(sip,".");
            s1 = strtok(NULL,".");
            s2 = strtok(NULL,".");
            s3 = strtok(NULL,".");
            d0 = strtok(dip,".");
            d1 = strtok(NULL,".");
            d2 = strtok(NULL,".");
            d3 = strtok(NULL,".");
/******************************************************************/

        if(!p->frag_flag)
        {
            query = NewQueryNode(query, 0);
            if(p->iph->ip_proto == IPPROTO_ICMP)
            {
                /*** Build a query for the ICMP Header ***/
                if(data->detail)
                {
                    if(p->ext)
                    {
                        snprintf(query->val, MAX_QUERY_LENGTH, 
                                 "INSERT INTO icmphdr (sid, cid, icmp_type, icmp_code, "
                                 "icmp_csum, icmp_id, icmp_seq) "
                                 "VALUES ('%u','%u','%u','%u','%u','%u','%u')",
                                 data->sid, data->cid, p->icmph->type, p->icmph->code,
                                 ntohs(p->icmph->csum), ntohs(p->ext->id), ntohs(p->ext->seqno));
                    }
                    else
                    {
                        snprintf(query->val, MAX_QUERY_LENGTH, 
                                 "INSERT INTO icmphdr (sid, cid, icmp_type, icmp_code, "
                                 "icmp_csum) "
                                 "VALUES ('%u','%u','%u','%u','%u')",
                                 data->sid, data->cid, p->icmph->type, p->icmph->code,
                                 ntohs(p->icmph->csum));
                    }
                }
                else
                {
                    snprintf(query->val, MAX_QUERY_LENGTH, 
                             "INSERT INTO icmphdr (sid, cid, icmp_type, icmp_code) "
                             "VALUES ('%u','%u','%u','%u')",
                             data->sid, data->cid, p->icmph->type, p->icmph->code);
                }
            }
            else if(p->iph->ip_proto == IPPROTO_TCP)
            {
                /*** Build a query for the TCP Header ***/
                if(data->detail)
                {
                    snprintf(query->val, MAX_QUERY_LENGTH, 
                             "INSERT INTO tcphdr "

                             "(sid, cid, tcp_sport, tcp_dport, tcp_seq,"
                             " tcp_ack, tcp_off, tcp_res, tcp_flags, tcp_win,"
                             " tcp_csum, tcp_urp) "

                             "VALUES ('%u','%u','%u','%u','%lu','%lu','%u',"
                             "'%u','%u','%u','%u','%u')",

                             data->sid, data->cid, ntohs(p->tcph->th_sport), 
                             ntohs(p->tcph->th_dport), (u_long)ntohl(p->tcph->th_seq),
                             (u_long)ntohl(p->tcph->th_ack), p->tcph->th_off, 
                             p->tcph->th_x2, p->tcph->th_flags, 
                             ntohs(p->tcph->th_win), ntohs(p->tcph->th_sum),
                             ntohs(p->tcph->th_urp));
                }
                else
                {
                    snprintf(query->val, MAX_QUERY_LENGTH, 
                             "INSERT INTO tcphdr "
                             "(sid,cid,tcp_sport,tcp_dport,tcp_flags) "
                             "VALUES ('%u','%u','%u','%u','%u')",
                             data->sid, data->cid, ntohs(p->tcph->th_sport), 
                             ntohs(p->tcph->th_dport), p->tcph->th_flags);
                }


                if(data->detail)
                {
                    /*** Build the query for TCP Options ***/
                    for(i=0; i < (int)p->tcp_option_count; i++)
                    {
                        query = NewQueryNode(query, 0);
                        if((data->encoding == ENCODING_HEX) || (data->encoding == ENCODING_ASCII))
                        {
                            tmp = hex(p->tcp_options[i].data, p->tcp_options[i].len); 
                        }
                        else
                        {
                            tmp = base64(p->tcp_options[i].data, p->tcp_options[i].len); 
                        }
                        snprintf(query->val, MAX_QUERY_LENGTH, 
                                 "INSERT INTO opt "
                                 "(sid,cid,optid,opt_proto,opt_code,opt_len,opt_data) "
                                 "VALUES ('%u','%u','%u','%u','%u','%u','%s')",
                                 data->sid, data->cid, i, 6, p->tcp_options[i].code,
                                 p->tcp_options[i].len, tmp); 
                        free(tmp);
                    }
                }
            }
            else if(p->iph->ip_proto == IPPROTO_UDP)
            {
                /*** Build the query for the UDP Header ***/
                if(data->detail)
                {
                    snprintf(query->val, MAX_QUERY_LENGTH,
                             "INSERT INTO udphdr "
                             "(sid, cid, udp_sport, udp_dport, udp_len, udp_csum) "
                             "VALUES ('%u', '%u', '%u', '%u', '%u', '%u')",
                             data->sid, data->cid, ntohs(p->udph->uh_sport), 
                             ntohs(p->udph->uh_dport), ntohs(p->udph->uh_len),
                             ntohs(p->udph->uh_chk));
                }
                else
                {
                    snprintf(query->val, MAX_QUERY_LENGTH,
                             "INSERT INTO udphdr "
                             "(sid, cid, udp_sport, udp_dport) "
                             "VALUES ('%u', '%u', '%u', '%u')",
                             data->sid, data->cid, ntohs(p->udph->uh_sport), 
                             ntohs(p->udph->uh_dport));
                }
            }
        }   

        /*** Build the query for the IP Header ***/
        query = NewQueryNode(query, 0);

        if(data->detail)
        {
            snprintf(query->val, MAX_QUERY_LENGTH, 

                     "INSERT INTO iphdr "
                     "(sid, cid, ip_src, ip_src0, ip_src1, ip_src2, ip_src3,"
                     "ip_dst, ip_dst0, ip_dst1, ip_dst2, ip_dst3, ip_ver,"
                     "ip_hlen, ip_tos, ip_len, ip_id, ip_flags, ip_off,"
                     "ip_ttl, ip_proto, ip_csum) "

                     "VALUES ('%u','%u','%lu','%s','%s','%s','%s',"
                     "'%lu','%s','%s','%s','%s','%u',"
                     "'%u','%u','%u','%u','%u','%u',"
                     "'%u','%u','%u')",

                     data->sid, data->cid, (u_long)ntohl(p->iph->ip_src.s_addr), 
                     s0, s1, s2, s3, (u_long)ntohl(p->iph->ip_dst.s_addr), 
                     d0, d1, d2, d3, p->iph->ip_ver, p->iph->ip_hlen, 
                     p->iph->ip_tos, ntohs(p->iph->ip_len), ntohs(p->iph->ip_id), 
                     p->frag_flag, ntohs(p->frag_offset), p->iph->ip_ttl, 
                     p->iph->ip_proto, ntohs(p->iph->ip_csum));
        }
        else
        {
            snprintf(query->val, MAX_QUERY_LENGTH, 

                     "INSERT INTO iphdr "
                     "(sid, cid, ip_src, ip_dst, ip_proto) "

                     "VALUES ('%u','%u','%lu','%lu','%u')",

                     data->sid, data->cid, (u_long)ntohl(p->iph->ip_src.s_addr),
                     (u_long)ntohl(p->iph->ip_dst.s_addr), p->iph->ip_proto);
        }

        /*** Build querys for the IP Options ***/
        if(data->detail)
        {
            for(i=0 ; i < (int)p->ip_option_count; i++)
            {
                if(&p->ip_options[i])
                {
                    query = NewQueryNode(query, 0);
                    if((data->encoding == ENCODING_HEX) || (data->encoding == ENCODING_ASCII))
                    {
                        tmp = hex(p->ip_options[i].data, p->ip_options[i].len); 
                    }
                    else
                    {
                        tmp = base64(p->ip_options[i].data, p->ip_options[i].len); 
                    }
                    snprintf(query->val, MAX_QUERY_LENGTH, 
                             "INSERT INTO opt "
                             "(sid,cid,optid,opt_proto,opt_code,opt_len,opt_data) "
                             "VALUES ('%u','%u','%u','%u','%u','%u','%s')",
                             data->sid, data->cid, i, 0, p->ip_options[i].code,
                             p->ip_options[i].len, tmp); 
                    free(tmp);
                }
            }
        }

        /*** Build query for the payload ***/
        if(data->detail)
        {
            if(p->dsize)
            {
                query = NewQueryNode(query, p->dsize * 2 + MAX_QUERY_LENGTH);
                if(data->encoding == ENCODING_BASE64)
                {
                    tmp_not_escaped = base64(p->data, p->dsize);
                }
                else
                {
                    if(data->encoding == ENCODING_ASCII)
                    {
                        tmp_not_escaped = ascii(p->data, p->dsize);
                    }
                    else
                    {
                        tmp_not_escaped = hex(p->data, p->dsize);
                    }
                }

                tmp = snort_escape_string(tmp_not_escaped, data);

                snprintf(query->val, MAX_QUERY_LENGTH - 3, 
                         "INSERT INTO data "
                         "(sid,cid,data_payload) "
                         "VALUES ('%u','%u','%s",
                         data->sid, data->cid, tmp);
                strcat(query->val, "')");
                free (tmp);
                free (tmp_not_escaped);
            }
        }
    }

    /* Execute the qureies */
    query = root;
    while(query)
    {
        Insert(query->val,data); 
        query = query->next;
    }

    FreeQueryNode(root); 

    data->cid++;

    /* A Unixodbc bugfix */
#ifdef ENABLE_UNIXODBC
    if(data->cid == 600)
    {
        data->cid = 601;
    }
#endif
}

/* Some of the code in this function is from the 
   mysql_real_escape_string() function distributed with mysql.

   Those portions of this function remain
   Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB

   We needed a more general case that was not MySQL specific so there
   were small modifications made to the mysql_real_escape_string() 
   function. */

char * snort_escape_string(char * from, DatabaseData * data)
{
    char * to;
    char * to_start;
    char * end; 
    int from_length;

    from_length = (int)strlen(from);

    to = (char *)malloc(strlen(from) * 2 + 1);
    to_start = to;
#ifdef ENABLE_ORACLE
    if (!strcasecmp(data->dbtype,ORACLE))
    {
      for (end=from+from_length; from != end; from++)
      {
        switch(*from)
        {
          case '\n':                               /* Must be escaped for logs */
            *to++= '\\';
            *to++= 'n';
            break;
          case '\r':
            *to++= '\\';
            *to++= 'r';
            break;
          case '\'':
            *to++= '\'';
            *to++= '\'';
            break;
          case '\032':                     /* This gives problems on Win32 */
            *to++= '\\';
            *to++= 'Z';
            break;
          default:
            *to++= *from;
        }
      }
    }
    else
#endif
    {
      for(end=from+from_length; from != end; from++)
      {
        switch(*from)
        {
          case 0:             /* Must be escaped for 'mysql' */
            *to++= '\\';
            *to++= '0';
            break;
          case '\n':              /* Must be escaped for logs */
            *to++= '\\';
            *to++= 'n';
            break;
          case '\r':
            *to++= '\\';
            *to++= 'r';
            break;
          case '\\':
            *to++= '\\';
            *to++= '\\';
            break;
          case '\'':
            *to++= '\\';
            *to++= '\'';
            break;
          case '"':               /* Better safe than sorry */
            *to++= '\\';
            *to++= '"';
            break;
          case '\032':            /* This gives problems on Win32 */
            *to++= '\\';
            *to++= 'Z';
            break;
          default:
            *to++= *from; 
        }
      }
    }
    *to=0;
    return(char *)to_start;
}

/* Function: Insert(char * query, DatabaseData * data)
 *
 * Purpose: Database independent function for SQL inserts
 * 
 * Arguments: query (An SQL insert)
 *
 * Returns: 1 if successful, 0 if fail
 */
int Insert(char * query, DatabaseData * data)
{
    int result = 0;

#ifdef ENABLE_POSTGRESQL
    if(!strcasecmp(data->dbtype,POSTGRESQL))
    {
        data->p_result = PQexec(data->p_connection,query);
        if(!(PQresultStatus(data->p_result) != PGRES_COMMAND_OK))
        {
            result = 1;
        }
        else
        {
            if(PQerrorMessage(data->p_connection)[0] != '\0')
            {
                ErrorMessage("database: postgresql_error: %s\n", PQerrorMessage(data->p_connection));
            }
        } 
    }
#endif

#ifdef ENABLE_MYSQL
    if(!strcasecmp(data->dbtype,MYSQL))
    {
        if(!(mysql_query(data->m_sock,query)))
        {
            result = 1;
        }
        else
        {
            if(mysql_errno(data->m_sock))
            {
                ErrorMessage("database: mysql_error: %s\n", mysql_error(data->m_sock));
            }
        }
    }
#endif

#ifdef ENABLE_UNIXODBC
    if(!strcasecmp(data->dbtype,UNIXODBC))
    {
        if(SQLAllocStmt(data->u_connection, &data->u_statement) == SQL_SUCCESS)
            if(SQLPrepare(data->u_statement, query, SQL_NTS) == SQL_SUCCESS)
                if(SQLExecute(data->u_statement) == SQL_SUCCESS)
                    result = 1;
    }
#endif

#ifdef ENABLE_ORACLE
    if(!strcasecmp(data->dbtype,ORACLE))
    {
        if (OCIStmtPrepare(data->o_statement, data->o_error, query, strlen(query), OCI_NTV_SYNTAX, OCI_DEFAULT) || 
	    OCIStmtExecute(data->o_servicecontext, data->o_statement, data->o_error, 1,  0, NULL, NULL, OCI_COMMIT_ON_SUCCESS))
        {
	    OCIErrorGet(data->o_error, 1, NULL, &data->o_errorcode, data->o_errormsg, sizeof(data->o_errormsg), OCI_HTYPE_ERROR);
	    ErrorMessage("database: oracle_error: %s\n", data->o_errormsg);
        } 
	else 
        {
  	    result = 1;
	}
    }
#endif

#ifdef DEBUG
    if(result)
    {
        printf("database(debug): (%s) executed\n", query);
    }
    else
    {
        printf("database(debug): (%s) failed\n", query);
    }
#endif

    return result;
}

/* Function: Select(char * query, DatabaeData * data)
 *
 * Purpose: Database independent function for SQL selects that 
 *          return a non zero int
 * 
 * Arguments: query (An SQL insert)
 *
 * Returns: result of query if successful, 0 if fail
 */
int Select(char * query, DatabaseData * data)
{
    int result = 0;

#ifdef ENABLE_POSTGRESQL
    if(!strcasecmp(data->dbtype,POSTGRESQL))
    {
        data->p_result = PQexec(data->p_connection,query);
        if((PQresultStatus(data->p_result) == PGRES_TUPLES_OK))
        {
            if(PQntuples(data->p_result))
            {
                if((PQntuples(data->p_result)) > 1)
                {
                    ErrorMessage("database: warning (%s) returned more than one result\n", query);
                    result = 0;
                }
                else
                {
                    result = atoi(PQgetvalue(data->p_result,0,0));
                } 
            }
        }
        if(!result)
        {
            if(PQerrorMessage(data->p_connection)[0] != '\0')
            {
                ErrorMessage("database: postgresql_error: %s\n",PQerrorMessage(data->p_connection));
            }
        }
    }
#endif

#ifdef ENABLE_MYSQL
    if(!strcasecmp(data->dbtype,MYSQL))
    {
        if(mysql_query(data->m_sock,query))
        {
            result = 0;
        }
        else
        {
            if(!(data->m_result = mysql_use_result(data->m_sock)))
            {
                result = 0;
            }
            else
            {
                if((data->m_row = mysql_fetch_row(data->m_result)))
                {
                    if(data->m_row[0] != NULL)
                    {
                        result = atoi(data->m_row[0]);
                    }
                }
            }
        }
        mysql_free_result(data->m_result);
        if(!result)
        {
            if(mysql_errno(data->m_sock))
            {
                ErrorMessage("database: mysql_error: %s\n", mysql_error(data->m_sock));
            }
        }
    }
#endif

#ifdef ENABLE_UNIXODBC
    if(!strcasecmp(data->dbtype,UNIXODBC))
    {
        if(SQLAllocStmt(data->u_connection, &data->u_statement) == SQL_SUCCESS)
            if(SQLPrepare(data->u_statement, query, SQL_NTS) == SQL_SUCCESS)
                if(SQLExecute(data->u_statement) == SQL_SUCCESS)
                    if(SQLRowCount(data->u_statement, &data->u_rows) == SQL_SUCCESS)
                        if(data->u_rows)
                        {
                            if(data->u_rows > 1)
                            {
                                ErrorMessage("database: warning (%s) returned more than one result\n", query);
                                result = 0;
                            }
                            else
                            {
                                if(SQLFetch(data->u_statement) == SQL_SUCCESS)
                                    if(SQLGetData(data->u_statement,1,SQL_INTEGER,&data->u_col,
                                                  sizeof(data->u_col), NULL) == SQL_SUCCESS)
                                        result = (int)data->u_col;
                            }
                        }
    }
#endif

#ifdef ENABLE_ORACLE
    if(!strcasecmp(data->dbtype,ORACLE))
    {
        if (OCIStmtPrepare(data->o_statement, data->o_error, query, strlen(query), OCI_NTV_SYNTAX, OCI_DEFAULT) ||
	    OCIStmtExecute(data->o_servicecontext, data->o_statement, data->o_error, 0, 0, NULL, NULL, OCI_DEFAULT) ||
	    OCIDefineByPos (data->o_statement, &data->o_define, data->o_error, 1, &result, sizeof(result), SQLT_INT, 0, 0, 0, OCI_DEFAULT) ||
	    OCIStmtFetch (data->o_statement, data->o_error, 1, OCI_FETCH_NEXT, OCI_DEFAULT))
	{
	    OCIErrorGet(data->o_error, 1, NULL, &data->o_errorcode, data->o_errormsg, sizeof(data->o_errormsg), OCI_HTYPE_ERROR);
	    ErrorMessage("database: oracle_error: %s\n", data->o_errormsg);
	}
    }
#endif

#ifdef DEBUG
    if(result)
    {
        printf("database(debug): (%s) returned %u\n", query, result);
    }
    else
    {
        printf("database(debug): (%s) failed\n", query);
    }
#endif

    return result;
}


/* Function: Connect(DatabaseData * data)
 *
 * Purpose: Database independent function to initiate a database 
 *          connection
 */

void Connect(DatabaseData * data)
{
#ifdef ENABLE_MYSQL
    int x; 
#endif

#ifdef ENABLE_POSTGRESQL
    if(!strcasecmp(data->dbtype,POSTGRESQL))
    {
        data->p_connection = PQsetdbLogin(data->host,data->port,NULL,NULL,data->dbname,data->user,data->password);
        if(PQstatus(data->p_connection) == CONNECTION_BAD)
        {
            PQfinish(data->p_connection);
            FatalError("database: Connection to database '%s' failed\n", data->dbname);
        }
    }
#endif

#ifdef ENABLE_MYSQL
    if(!strcasecmp(data->dbtype,MYSQL))
    {
        data->m_sock = mysql_init(NULL);
        if(data->m_sock == NULL)
        {
            FatalError("database: Connection to database '%s' failed\n", data->dbname);
        }
        if(data->port != NULL)
        {
            x = atoi(data->port);
        }
        else
        {
            x = 0;
        }
        if(mysql_real_connect(data->m_sock, data->host, data->user, data->password, data->dbname, x, NULL, 0) == 0)
        {
            if(mysql_errno(data->m_sock))
            {
                FatalError("database: mysql_error: %s\n", mysql_error(data->m_sock));
            }
            FatalError("database: Failed to logon to database '%s'\n", data->dbname);
        }
    }
#endif

#ifdef ENABLE_UNIXODBC
    if(!strcasecmp(data->dbtype,UNIXODBC))
    {
        if(!(SQLAllocEnv(&data->u_handle) == SQL_SUCCESS))
        {
            exit(-5);
        }
        if(!(SQLAllocConnect(data->u_handle, &data->u_connection) ==
             SQL_SUCCESS))
        {
            exit(-6);
        }
        if(!(SQLConnect(data->u_connection, data->dbname, SQL_NTS, data->user, SQL_NTS, data->password, SQL_NTS) == SQL_SUCCESS))
        {
            exit(-7);
        }
    }
#endif

#ifdef ENABLE_ORACLE
    if(!strcasecmp(data->dbtype,ORACLE))
    {
      if (OCIInitialize(OCI_DEFAULT, NULL, NULL, NULL, NULL) ||
         OCIEnvInit(&data->o_environment, OCI_DEFAULT, 0, NULL) ||
         OCIEnvInit(&data->o_environment, OCI_DEFAULT, 0, NULL) ||
         OCIHandleAlloc(data->o_environment, (dvoid **)&data->o_error, OCI_HTYPE_ERROR, (size_t) 0, NULL) ||
         OCILogon(data->o_environment, data->o_error, &data->o_servicecontext,
data->user, strlen(data->user), data->password, strlen(data->password), data->dbname, strlen(data->dbname)) ||
         OCIHandleAlloc(data->o_environment, (dvoid **)&data->o_statement, OCI_HTYPE_STMT, 0, NULL))
      {
         FatalError("database: Connection to database '%s' failed\n", data->dbname);
      }
    }
#endif
}

/* Function: Disconnect(DatabaseData * data)
 *
 * Purpose: Database independent function to close a connection
 */

void Disconnect(DatabaseData * data)
{
    printf("database: Closing %s connection to database \"%s\"\n", data->dbtype, data->dbname);

    if(data)
    {
#ifdef ENABLE_POSTGRESQL
        if(!strcasecmp(data->dbtype,POSTGRESQL))
        {
            if(data->p_connection) PQfinish(data->p_connection);
        }
#endif

#ifdef ENABLE_MYSQL
        if(!strcasecmp(data->dbtype,MYSQL))
        {
            if(data->m_sock) mysql_close(data->m_sock);
        }
#endif

#ifdef ENABLE_UNIXODBC
        if(!strcasecmp(data->dbtype,UNIXODBC))
        {
            if(data->u_handle)
            {
                SQLDisconnect(data->u_connection); 
                SQLFreeHandle(SQL_HANDLE_ENV, data->u_handle); 
            }
        }
#endif
    }
}

void DatabasePrintUsage()
{
    puts("\nUSAGE: database plugin\n");

    puts(" output database: [log | alert], [type of database], [parameter list]\n");
    puts(" [log | alert] selects whether the plugin will use the alert or");
    puts(" log facility.\n");

    puts(" For the first argument, you must supply the type of database.");
    puts(" The possible values are mysql, postgresql, unixodbc, and oracle.");
    puts(" (oracle support is beta in snort release 1.7)\n");

    puts(" The parameter list consists of key value pairs. The proper");
    puts(" format is a list of key=value pairs each separated a space.\n");

    puts(" The only parameter that is absolutely necessary is \"dbname\"."); 
    puts(" All other parameters are optional but may be necessary");
    puts(" depending on how you have configured your RDBMS.\n");

    puts(" dbname - the name of the database you are connecting to\n"); 

    puts(" host - the host the RDBMS is on\n");

    puts(" port - the port number the RDBMS is listening on\n"); 

    puts(" user - connect to the database as this user\n");

    puts(" password - the password for given user\n");

    puts(" sensor_name - specify your own name for this snort sensor. If you");
    puts("        do not specify a name one will be generated automatically\n");

    puts(" encoding - specify a data encoding type (hex, base64, or ascii)\n");

    puts(" detail - specify a detail level (full or fast)\n");

    puts(" The configuration I am currently using is MySQL with the database");
    puts(" name of \"snort\". The user \"jed@localhost\" has INSERT and SELECT");
    puts(" privileges on the \"snort\" database and does not require a password.");
    puts(" The following line enables snort to log to this database.\n");

    puts(" output database: log, mysql, dbname=snort user=jed host=localhost\n");
}

void SpoDatabaseCleanExitFunction(int signal, void *arg)
{
    DatabaseData *data = (DatabaseData *)arg;
#ifdef DEBUG
    printf("database(debug): entered SpoDatabaseCleanExitFunction\n");
#endif
    Disconnect(data); 
    if(data) free(data);
}

void SpoDatabaseRestartFunction(int signal, void *arg)
{
    DatabaseData *data = (DatabaseData *)arg;
#ifdef DEBUG
    printf("database(debug): entered SpoDatabaseRestartFunction\n");
#endif
    Disconnect(data);
    if(data) free(data);
}
