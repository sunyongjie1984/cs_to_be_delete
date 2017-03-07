#include <apr_time.h>
#include "log.h"

//#include "stdarg.h"

/* default buffer size */
#define __LOG_BUF_SIZE__			4096



typedef struct __tagLOG_CONF_ITEM
{
	__PRINT out_func;
	int min_level;	
}LOG_CONF_ITEM;


LOG_CONF_ITEM g_log_conf;





void out0(char * s)
{
	printf("%s\r\n", s);
}


void out1(char * s)
{
	strcat(s, "\r\n");
	OutputDebugString(s);
}



void out2(char * s);




void outx(char * s)
{
	//LOG4CXX_INFO(logger, s)
	out1(s);
	out2(s);
	//AxNote(0, s);
}








void __cdecl LOG(const int level, const char * f, ...)
{
	if (level > g_log_conf.min_level)
	{
		va_list _va_list;
		/* 初始化变长参数列表 */
		va_start(_va_list, f);
		char buf[__LOG_BUF_SIZE__] = {0};
		
		apr_time_exp_t now;
		apr_time_exp_lt(&now, apr_time_now());
		
		sprintf(buf, "%.2d/%.2d %.2d:%.2d:%.2d:%d ", now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, now.tm_usec);
		int len = vsprintf(buf + strlen(buf), f, _va_list);
		va_end(_va_list);
		
		if (g_log_conf.out_func)
			g_log_conf.out_func(buf);
	}
}




bool __cdecl set_log_out_conf(int min_level, int out_func)
{
	g_log_conf.min_level = min_level;

	switch (out_func)
	{
		case __printf:
			g_log_conf.out_func = out0; break;
		case __win_outputdebugstr:
			g_log_conf.out_func = out1; break;
		case __write_file:
			g_log_conf.out_func = out2; break;
		case __write_file_and_view:
			g_log_conf.out_func = outx; break;
		default:
			return false;
	}
	return true;
}


void __cdecl set_log_out_func(int min_level, __PRINT func)
{
	g_log_conf.min_level = min_level;
	g_log_conf.out_func = func;
}







typedef struct __tagOUT2_HANDLE
{
	char log_path[512];
	FILE * pf;
	int create_flag;

	enum
	{
		__create_ok = 0x000000f0
	};
}OUT2_HANDLE;

OUT2_HANDLE g_out2_mode;



void out2(char * s)
{
	if (OUT2_HANDLE::__create_ok == g_out2_mode.create_flag)
	{
		strcat(s, "\n");
		fputs(s, g_out2_mode.pf);
		fflush(g_out2_mode.pf);
	}
}

void __cdecl out2_destroy(void)
{
	if ((OUT2_HANDLE::__create_ok == g_out2_mode.create_flag) && (g_out2_mode.pf))
	{
		fclose(g_out2_mode.pf);
		memset(&g_out2_mode, 0, sizeof(g_out2_mode));
	}
}

bool __cdecl out2_create(const char * path)
{
	out2_destroy();
	memset(&g_out2_mode, 0, sizeof(g_out2_mode));

	strcpy(g_out2_mode.log_path, path);
	g_out2_mode.pf = fopen(g_out2_mode.log_path, "w+");
	if (g_out2_mode.pf)
	{
		g_out2_mode.create_flag = OUT2_HANDLE::__create_ok;
		return true;
	}
	return false;
}

