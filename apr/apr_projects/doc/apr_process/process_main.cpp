#include <apr_pools.h>
//#include <apr_network_io.h>

//extern apr_status_t _block_tcp_task_init(apr_pool_t * mp);
//extern apr_status_t _poll_nonblock_tcp_task_init(apr_pool_t * mp);

#include <apr_thread_proc.h>

#include "apr_errno.h"
#include "apr_general.h"
//#include "apr_lib.h"
//#include "apr_strings.h"
//#include "testutil.h"

//#define TESTSTR "This is a test"


#define QUERY_TICK_COUNT(ret) {			\
LARGE_INTEGER frequency;				\
LARGE_INTEGER counter;					\
double dFreq,dCounter;					\
QueryPerformanceFrequency(&frequency);	\
QueryPerformanceCounter(&counter);		\
dFreq   =(double)(frequency.QuadPart);	\
dCounter=(double)(counter.QuadPart);	\
ret = (dCounter/dFreq*1000.0*1000.0); }


double q01;
double q02;
double q03;
double q04;
double q05;
double q06;
double q07;
double q08;
double q09;
double q10;
double q11;
double q12;

void apr_err_print(apr_status_t rv, char * msg)
{
	char err_buff[1024] = {0};
	apr_strerror(rv, err_buff, sizeof(err_buff));
	printf("%s ->%d -- %s\n", msg, rv, err_buff);
}


static apr_proc_t newproc;


#ifdef WIN32
#define EXTENSION ".exe"
#elif NETWARE
#define EXTENSION ".nlm"
#else
#define EXTENSION
#endif

#ifdef WIN32
#ifdef BINPATH
#define TESTBINPATH APR_STRINGIFY(BINPATH) "/"
#else
#define TESTBINPATH ""
#endif
#else
#define TESTBINPATH "./"
#endif

void test_create_proc(apr_pool_t * mp)
{
    const char *args[2] = {0};
    apr_procattr_t *attr;
    apr_file_t *testfile = NULL;
    apr_status_t rv;
	
    rv = apr_procattr_create(&attr, mp);
    //ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
	
    rv = apr_procattr_io_set(attr, APR_FULL_BLOCK, APR_FULL_BLOCK, 
		APR_NO_PIPE);
    //ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
	
    rv = apr_procattr_dir_set(attr, "data");
    //ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
	
    rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_ENV);
    //ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
	
    //args[0] = "apr_client" EXTENSION;
    //args[1] = NULL;
    
    rv = apr_proc_create(&newproc, /*"../" TESTBINPATH */"apr_client" EXTENSION, args, NULL, 
		attr, mp);
    //ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
	
    //testfile = newproc.in;
	
    //length = strlen(TESTSTR);
   // rv = apr_file_write(testfile, TESTSTR, &length);
    //ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    //ABTS_SIZE_EQUAL(tc, strlen(TESTSTR), length);
	
    /*testfile*///testfile = newproc.out;
    //length = 256;
    //buf = apr_pcalloc(p, length);
   // rv = apr_file_read(testfile, buf, &length);
    //ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    //ABTS_STR_EQUAL(tc, TESTSTR, buf);
}


apr_status_t _create_process(apr_pool_t * mp)
{
	
	test_create_proc(mp);

	return 1;
}

typedef apr_status_t (* __FUNC)(apr_pool_t * mp);

void apr_pool_init(__FUNC func)
{
	//try
	{
		apr_pool_t		* mp	= NULL;
		apr_status_t	rv		= APR_SUCCESS;
		
		apr_initialize();
		if (APR_SUCCESS == (rv = apr_pool_create(&mp, NULL)))
		{
			func(mp);
			
			if (mp)
			{
				apr_pool_destroy(mp);
				mp = NULL;
			}
		}
	}
	//__finally
	{
		apr_terminate();
	}	
}

void create_proc(char * szPath)
{
	STARTUPINFO si = { sizeof(si) };
	SECURITY_ATTRIBUTES saProcess, saThread;
	PROCESS_INFORMATION piProcessB;

	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = TRUE;

	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = FALSE;

	CreateProcess(NULL, szPath, &saProcess, &saThread, FALSE, 0, NULL, NULL, &si, &piProcessB);
}


#include <string>
#include <vector>

void analysisStr(char * str);


#define BUFSIZE 4096
#define CRLF_STR "\r\n"

inline void strtok(char * str, const char *sep, std::vector<std::string> &vec)
{
	char * head = str;
	char * pos = NULL;
	int sep_len = strlen(sep);
	
	while (true)
	{
		pos = strstr(head, sep);
		if (pos) {
			*pos = '\0';
			if (pos != head)
			{
				vec.push_back(head);
				head = pos + sep_len;
			}
			else
			{
				vec.push_back("");
				head = pos;
			}
			continue;
		}
		else
		{
			if ('\0' != *head)
				vec.push_back(head);
			else
				vec.push_back("");
			
		}
		break;
	}
}


void analysisStr(char * str)
{
	//printf("%s\n", str);
	
	QUERY_TICK_COUNT(q01)

	std::vector<std::string> v;
	strtok(str, CRLF_STR, v);
	int vlen = v.size();
	
	QUERY_TICK_COUNT(q02)
	
	const char * sep = "|";
	for (int i=0; i<vlen; i++)
	{
		//printf("....%s\n", v[i].c_str());
		
		std::vector<std::string> v2;
		strtok((char *)v[i].c_str(), sep, v2);
		int v2len = v2.size();
	
		QUERY_TICK_COUNT(q03)

		for (int j=0; j<v2len; j++)
		{
			printf("........%s\n", v2[j].c_str());
		}
		printf(
			"q01 %.9lf \n"
			"q02 %.9lf [q01 - q02 = %.9lf]\n"
			"q03 %.9lf [q02 - q03 = %.9lf]\n",
			q01,
			q02, q02-q01,
			q03, q03-q02
			);
		break;
	}
}


void main(int argc, char * argv[])
{
	std::string ss =
		"51|rid108|1.1.1.1|Xspeed|000200000020|123|false||\r\n"
		"51|rid108|1.1.1.1|Xspeed|000200000020|123|false|0|\r\n"
		"51|rid108|1.1.1.1|Xspeed|000200000020|123|false||stp\r\n"
		"21|000200000020|000000000000000243|a1305|4975.0|1|1|0|1|0|0|0.0|1|0|stp\r\n"
		"21|000200000020|000000000000000246|a1305|4975.0|1|1|0|1|0|0|0.0|1|0|stp\r\n"
		"21|000200000020|000000000000000244|a1305|4975.0|1|1|0|1|0|0|0.0|1|0|stp\r\n"
		"21|000200000020|000000000000000245|a1305|4975.0|1|1|0|1|0|0|0.0|1|0|stp\r\n";

	analysisStr((char *)ss.c_str());

	char cmd[256] = {0};
	if (3 == argc)
	{
		sprintf(cmd, "apr_client %s", argv[1]);
		
		for (int i=0; i<atol(argv[2]); i++)
		{
			create_proc(cmd);
		}
		::system("pause");
	}
	
	//apr_pool_init(_create_process);

	//::system("pause");
}



#include "apr_strings.h"



void test(std::string &s)
{
	const char *sep = "|";

	char buf[BUFSIZE] = {0};
	char *str, *last;
	std::vector<std::string> v;
	std::vector<std::string>::iterator it;

	memset(buf, 0, sizeof(buf));

	str = apr_strtok(buf, CRLF_STR, &last);
	while (str) {
		v.push_back(std::string(str));
		str = apr_strtok(NULL, CRLF_STR, &last);
	}
	
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::vector<std::string> v2;
		strcpy(buf, (*it).c_str());

		char *haystack=buf;
		char *needle="|";
		char* splitpos = strstr( haystack, needle);
		while( splitpos != NULL )
		{
			/* replace '|' to '\0' */
			splitpos[0]='\0';
			v2.push_back(std::string(haystack));
			haystack = splitpos + strlen(needle);
			/* Get next token: */
			splitpos = strstr( haystack, needle);
		}
		v2.push_back(std::string(haystack));
	}
}

void test2(std::string &s)
{
	char buff[BUFSIZE] = {0};

	strcpy(buff, s.c_str());

	
}
