/*
** Copyright (C) 2000,2001 Carnegie Mellon University
**
** Author: Jed Pickel <jed@pickel.net>
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

/* $Id: spo_database.h,v 1.5 2001/01/02 08:06:01 roesch Exp $ */

#ifndef __SPO_DATABASE_H__
#define __SPO_DATABASE_H__

#include "snort.h"

#ifdef ENABLE_POSTGRESQL
    #include <libpq-fe.h>
#endif
#ifdef ENABLE_MYSQL
    #if defined(_WIN32) || defined(_WIN64)
        #include <windows.h>
    #endif
    #include <mysql.h>
#endif
#ifdef ENABLE_UNIXODBC
    #include <sql.h>
    #include <sqlext.h>
    #include <sqltypes.h>
#endif
#ifdef ENABLE_ORACLE
    #include <oci.h>
#endif

typedef struct _SQLQuery
{
    char * val;
    struct _SQLQuery * next;
} SQLQuery;

typedef struct _DatabaseData
{
    char * facility;
    char * dbtype;
    char * dbname;
    char * password;
    char * host;
    char * user;
    char * port;
    char * sensor_name;
    int  encoding;
    int  detail;
    int  tz;
    int  sid;
    int  cid;
#ifdef ENABLE_POSTGRESQL
    PGconn * p_connection;
    PGresult * p_result;
#endif
#ifdef ENABLE_MYSQL
    MYSQL * m_sock;
    MYSQL_RES * m_result;
    MYSQL_ROW m_row;
#endif
#ifdef ENABLE_UNIXODBC
    SQLHENV u_handle;
    SQLHDBC u_connection;
    SQLHSTMT u_statement;
    SQLINTEGER  u_col;
    SQLINTEGER  u_rows;
#endif
#ifdef ENABLE_ORACLE
    OCIEnv *o_environment;
    OCISvcCtx *o_servicecontext;
    OCIError *o_error;
    OCIStmt *o_statement;
    OCIDefine *o_define;
    text o_errormsg[512];
    sb4 o_errorcode;
#endif
} DatabaseData;

/* constants */
#define MAX_QUERY_LENGTH 8192
#define POSTGRESQL   "postgresql"
#define MYSQL        "mysql"
#define UNIXODBC     "unixodbc"
#define ORACLE       "oracle"

/* prototypes */
void SetupDatabase();
void DatabaseInit(u_char *);
DatabaseData *ParseDatabaseArgs(char *);
void Database(Packet *, char *, void *);
char * snort_escape_string(char *, DatabaseData *);
void SpoDatabaseCleanExitFunction(int, void *);
void SpoDatabaseRestartFunction(int, void *);
void InitDatabase();
int Insert(char *, DatabaseData *);
int Select(char *, DatabaseData *);
void Connect(DatabaseData *);
void DatabasePrintUsage();

#endif  /* __SPO_DATABASE_H__ */
