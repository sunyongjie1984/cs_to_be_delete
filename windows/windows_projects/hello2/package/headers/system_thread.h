#pragma once

#include "protocol_interface.h"
#include <windows.h>
#include <process.h>


enum
{
	_err_thread_wait_time_out = _err_thread_start + 1,
}
_THREAD_ERROR;

enum
{
	_thread_running = _thread_status_start + 1,
	_thread_waitting,
	_thread_stop
}
_THREAD_STATUS;

typedef struct __tag_THREAD_HANDLE
{
	_STATUS			status_;
	HANDLE			handle_;
	unsigned		u_id;
	u_char			name_[64];
}
THREAD_HANDLE;




extern u_long __cdecl thread_init		(
											_in_ _out_ THREAD_HANDLE * h,
											_in_ const u_char * name
										);

extern u_long __cdecl thread_create		(
											_in_ _out_ THREAD_HANDLE * h,
											_in_ unsigned (__stdcall * initialcode) (void *),
											_in_ void * argument,
											_in_ const u_char * thread_name 
										);

extern u_long __cdecl thread_wait		(
											_in_ const THREAD_HANDLE * h,
											_in_ const long ms
										);

extern u_long __cdecl thread_exit		(
											_in_ const unsigned retval
										);

extern u_long __cdecl thread_destroy	(
											_in_ THREAD_HANDLE * h,
											_in_ const long ms
										);