#pragma once

#include "protocol_interface.h"
#include <windows.h>
#include <process.h>


enum
{
	_test = 0,
	_err_event_wait_time_out,
	_err_mutex_wait_time_out
};

typedef struct __tag_MUTEX_HANDLE
{
	_STATUS			status_;
	HANDLE			handle_;
	u_char			name_[64];
}
MUTEX_HANDLE;

extern u_long __cdecl mutex_init				( _in_ _out_ MUTEX_HANDLE * h, const u_char * name );

extern u_long __cdecl mutex_open				( _in_ _out_ MUTEX_HANDLE * h, const u_char * name );

extern u_long __cdecl mutex_create				(
													_in_ _out_ MUTEX_HANDLE * h,
													_in_ const int initial_owner,
													_in_ const u_char * name
												);

extern u_long __cdecl mutex_wait				(
													_in_ const MUTEX_HANDLE * h,
													_in_ const long ms
												);

extern u_long __cdecl mutex_release				(
													_in_ const MUTEX_HANDLE * h
												);

extern u_long __cdecl mutex_destroy				( _in_ _out_ MUTEX_HANDLE * h );

extern u_long __cdecl mutex_lock_create			(
													_in_ _out_ MUTEX_HANDLE * h,
													_in_ const u_char * name
												);

extern u_long __cdecl mutex_lock				( _in_ _out_ MUTEX_HANDLE * h );

extern u_long __cdecl mutex_unlock				( _in_ _out_ MUTEX_HANDLE * h );



typedef struct __tag_EVENT_HANDLE
{
	_STATUS		status_;
	HANDLE			handle_;
	u_char			name_[64];
}
EVENT_HANDLE;

extern u_long __cdecl event_init				(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const u_char * name
												);

extern u_long __cdecl event_create				(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const int manual_reset,
													_in_ const int initial_owner,
													_in_ const u_char * name
												);

extern u_long __cdecl event_destroy				( _in_ _out_ EVENT_HANDLE * h );

extern u_long __cdecl event_wait				(
													_in_ const EVENT_HANDLE * h,
													_in_ const long ms
												);



extern u_long __cdecl event_set					(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const _BOOLEAN owner_flag
												);

extern u_long __cdecl event_lock_create			(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const u_char * name
												);

extern u_long __cdecl event_lock				( _in_ _out_ EVENT_HANDLE * h );

extern u_long __cdecl event_unlock				( _in_ _out_ EVENT_HANDLE * h );




typedef struct __tag_SEMAPHORE_HANDLE
{
	_STATUS			status_;
	HANDLE			handle_;
	u_char			name_[64];
}
SEMAPHORE_HANDLE;

extern u_long __cdecl semaphore_init			( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const u_char * name );

extern u_long __cdecl semaphore_open			( _in_ _out_ SEMAPHORE_HANDLE * h, _in_ const u_char * name );

extern u_long __cdecl semaphore_create			(
													_in_ _out_ SEMAPHORE_HANDLE * h,
													_in_ const int initial_owner,
													_in_ const u_char * name
												);

extern u_long __cdecl semaphore_wait			(
													_in_ const SEMAPHORE_HANDLE * h,
													_in_ const long ms
												);

extern u_long __cdecl semaphore_set				(
													_in_ const SEMAPHORE_HANDLE * h
												);

extern u_long __cdecl semaphore_destroy			( _in_ _out_ SEMAPHORE_HANDLE * h );