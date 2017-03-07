#pragma once

#include "public.h"
#include "system_synch.h"




typedef unsigned int (__stdcall * INITIAL_CODE) (void * argument, const u_char * thread_name, const unsigned int u_id);


#ifdef _windows_sys_
typedef struct __tag_THREAD_HANDLE
{
	_STATUS			status_;
	HANDLE			handle_;
	unsigned int 	u_id_;
	INITIAL_CODE	initialcode_;
	void			* argument_;
	u_char			name_[64];
}
THREAD_HANDLE;
#endif//_windows_sys_

#ifdef _linux_sys_
typedef struct __tag_THREAD_HANDLE
{
	_STATUS			status_;
	pthread_t		handle_;
	unsigned int 	u_id_;
	INITIAL_CODE	initialcode_;
	void			* argument_;
	u_char			name_[64];
}
THREAD_HANDLE;
#endif//_linux_sys_




extern _ERROR __cdecl thread_create		(
											_in_ _out_ THREAD_HANDLE * h,
											_in_ INITIAL_CODE initialcode,
											_in_ void * argument,
											_in_ const u_char * thread_name 
										);


extern _ERROR __cdecl thread_destroy	(
											_in_ THREAD_HANDLE * h,
											_in_ const long ms
										);

