#pragma once

#include "public.h"

#ifdef _windows_sys_
#include <windows.h>
#include <process.h>
#endif//_windows_sys_

#ifdef _linux_sys_
#include <pthread.h>
#endif//_linux_sys_

extern void synch_begin(_BOOLEAN * synch_flag, const char * debug_out);
extern void synch_end(_BOOLEAN * synch_flag);


enum
{
	_err_time_out = _err_synch_start + 1,
}
_SYNCH_ERROR;


#ifdef _windows_sys_
typedef struct __tag_MUTEX_HANDLE
{
	_STATUS			status_;
	HANDLE			handle_;
	u_char			name_[64];
}
MUTEX_HANDLE;
#endif//_windows_sys_

#ifdef _linux_sys_
typedef struct __tag_MUTEX_HANDLE
{
	_STATUS				status_;
	pthread_mutex_t		handle_;
	pthread_mutexattr_t	attr_;
	u_char				name_[64];
}
MUTEX_HANDLE;
#endif//_linux_sys_


extern _ERROR __cdecl mutex_create				(
													_in_ _out_ MUTEX_HANDLE * h,
													_in_ const u_char * mutex_name
												);

extern _ERROR __cdecl mutex_destroy				( _in_ _out_ MUTEX_HANDLE * h );


extern _ERROR __cdecl mutex_lock				( _in_ const MUTEX_HANDLE * h );

extern _ERROR __cdecl mutex_unlock				( _in_ const MUTEX_HANDLE * h );

extern _ERROR __cdecl mutex_facility_lock		(
													_in_ _out_ MUTEX_HANDLE * h,
													_in_ const u_char * lock_name
												);

extern _ERROR __cdecl mutex_facility_unlock		(
													_in_ _out_ MUTEX_HANDLE * h
												);



typedef struct __tag_EVENT_HANDLE
{
	_STATUS			status_;
	HANDLE			handle_;
	u_char			name_[64];
}
EVENT_HANDLE;


extern _ERROR __cdecl event_create				(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const int manual_reset,
													_in_ const int initial_owner,
													_in_ const u_char * event_name
												);

extern _ERROR __cdecl event_destroy				( _in_ _out_ EVENT_HANDLE * h );

extern _ERROR __cdecl event_wait				(
													_in_ const EVENT_HANDLE * h,
													_in_ const long ms
												);



extern _ERROR __cdecl event_set					(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const _BOOLEAN owner_flag
												);

extern _ERROR __cdecl event_lock_create			(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const u_char * name
												);

extern _ERROR __cdecl event_lock				( _in_ _out_ EVENT_HANDLE * h );

extern _ERROR __cdecl event_unlock				( _in_ _out_ EVENT_HANDLE * h );

extern _ERROR __cdecl event_facility_lock		(
													_in_ _out_ EVENT_HANDLE * h,
													_in_ const u_char * lock_name
												);

extern _ERROR __cdecl event_facility_unlock		(
													_in_ _out_ EVENT_HANDLE * h
												);


typedef struct __tag_SEMAPHORE_HANDLE
{
	_STATUS			status_;
	HANDLE			handle_;
	u_char			name_[64];
}
SEMAPHORE_HANDLE;


extern _ERROR __cdecl semaphore_create			(
													_in_ _out_ SEMAPHORE_HANDLE * h,
													_in_ const u_long maximum_count,
													_in_ const u_char * semaphore_name
												);

extern _ERROR __cdecl semaphore_wait			(
													_in_ const SEMAPHORE_HANDLE * h,
													_in_ const long ms
												);

extern _ERROR __cdecl semaphore_set				(
													_in_ const SEMAPHORE_HANDLE * h
												);

extern _ERROR __cdecl semaphore_destroy			(
													_in_ _out_ SEMAPHORE_HANDLE * h
												);

extern _ERROR __cdecl semaphore_accept			(
													_in_ _out_ SEMAPHORE_HANDLE * h,
													_in_ const u_long maximum_count,
													_in_ const u_char * semaphore_name,
													_in_ const long ms
												);

extern _ERROR __cdecl semaphore_send			(
													_in_ _out_ SEMAPHORE_HANDLE * h,
													_in_ const u_long maximum_count,
													_in_ const u_char * semaphore_name
												);