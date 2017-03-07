#pragma once




enum
{
	__printf,
	__win_outputdebugstr,
	__write_file,
	__write_file_and_view
};


typedef void (* __PRINT)(char *);


extern void __cdecl set_log_out_func(int min_level, __PRINT func);
extern bool __cdecl set_log_out_conf(int min_level, int out_func);
extern void __cdecl LOG(const int level, const char * f, ...);

extern bool __cdecl out2_create(const char * path);
extern void __cdecl out2_destroy(void);

