#include ".\package\headers\system_thread.h"


#pragma warning(disable:4096 4996 4013)


/************************************************************************/
/*                                                                      */
/************************************************************************/

_BOOLEAN mutex_lock_0_synch_flag = _false;
int thread_mutex_index = 0;



unsigned int __stdcall test_mutex_lock_entry_0(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index  = 0;
	MUTEX_HANDLE * h	= (MUTEX_HANDLE *)p;

	for ( index = 0; index < 10; index++ )
	{
		__try
		{
			if ( _ok == (ret = mutex_lock(h)) )
			{
				synch_begin(&mutex_lock_0_synch_flag, "\n[synch_flag] --------> mutex_lock_0_synch_flag failed<<\n");

				//MessageBox(NULL, name, "", MB_OK);
				printf("< %s--%d > ---- running %d %d\n", name, u_id, index, ++thread_mutex_index);
			}
		}
		__finally
		{
			synch_end(&mutex_lock_0_synch_flag);
			ret = mutex_unlock(h);
			//ret = mutex_destroy(h);
		}
		if ( _ok != ret )
		{
			break;
		}
	}
	return 0;
}

unsigned int __stdcall test_mutex_lock_entry_1(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index  = 0;
	MUTEX_HANDLE mutex_lock_0;

	for ( index = 0; index < 10; index++ )
	{
		__try
		{
			if ( _ok == (ret = mutex_facility_lock(&mutex_lock_0, "mutex_lock_0")) )
			{
				synch_begin(&mutex_lock_0_synch_flag, "\n[synch_flag] --------> mutex_lock_0_synch_flag failed<<\n");
				//MessageBox(NULL, name, "", MB_OK);
				printf("< %s--%d > ---- running %d %d\n", name, u_id, index, ++thread_mutex_index);
			}
		}
		__finally
		{
			synch_end(&mutex_lock_0_synch_flag);
			ret = mutex_facility_unlock(&mutex_lock_0);
		}
		if ( _ok != ret )
		{
			break;
		}
	}
	return 0;
}

void test_mutex_lock_thread()
{
	_ERROR ret = _failed;

	MUTEX_HANDLE mutex_lock_0;
	THREAD_HANDLE thread_mutex_0;
	THREAD_HANDLE thread_mutex_1;

	THREAD_HANDLE thread_mutex_2;
	THREAD_HANDLE thread_mutex_3;

	ret = mutex_create(&mutex_lock_0, "mutex_lock_0");
	ret = thread_create(&thread_mutex_0, test_mutex_lock_entry_0, (void *)&mutex_lock_0, "thread_mutex_0");
	ret = thread_create(&thread_mutex_1, test_mutex_lock_entry_0, (void *)&mutex_lock_0, "thread_mutex_1");

	ret = thread_create(&thread_mutex_2, test_mutex_lock_entry_1, NULL, "thread_mutex_2");
	ret = thread_create(&thread_mutex_3, test_mutex_lock_entry_1, NULL, "thread_mutex_3");

	switch ( ret )
	{
	case _ok:
	case _err_exist:
		{
			thread_destroy(&thread_mutex_0, -1);
			thread_destroy(&thread_mutex_1, -1);
			thread_destroy(&thread_mutex_2, -1);
			thread_destroy(&thread_mutex_3, -1);
			mutex_destroy(&mutex_lock_0);
			break;
		}
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/


_BOOLEAN event_lock_0_synch_flag = _false;
int thread_event_index = 0;



unsigned int __stdcall test_event_lock_entry_0(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index  = 0;
	EVENT_HANDLE * h	= (EVENT_HANDLE *)p;

	for ( index = 0; index < 10; index++ )
	{
		__try
		{
			/*
			用事件作为锁回存在的问题：
			当某个线程或进程退出时，如果没有调用event_unlock(h)，会导致其他线程或进程中的event_lock(h)无法解锁，主要是由于事件的手动机制下没有开启事件开关导致的
			而互斥在进城中就不会有这种情况，因为互斥体会随着进程的销毁而释放互斥资源
			*/
			if ( _ok == (ret = event_lock(h)) )
			{
				synch_begin(&event_lock_0_synch_flag, "\n[synch_flag] --------> event_lock_0_synch_flag failed<<\n");

				//MessageBox(NULL, name, "", MB_OK);
				printf("< %s--%d > ---- running %d %d\n", name, u_id, index, ++thread_event_index);
			}
		}
		__finally
		{
			synch_end(&event_lock_0_synch_flag);
			ret = event_unlock(h);
		}
		if ( _ok != ret )
		{
			break;
		}
	}
	return 0;
}

unsigned int __stdcall test_event_lock_entry_1(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index  = 0;
	EVENT_HANDLE event_lock_0;

	for ( index = 0; index < 10; index++ )
	{
		__try
		{
			if ( _ok == (ret = event_facility_lock(&event_lock_0, "event_lock_1")) )
			{
				synch_begin(&event_lock_0_synch_flag, "\n[synch_flag] --------> event_lock_0_synch_flag failed<<\n");
				//MessageBox(NULL, name, "", MB_OK);
				printf("< %s--%d > ---- running %d %d\n", name, u_id, index, ++thread_event_index);
			}
		}
		__finally
		{
			synch_end(&event_lock_0_synch_flag);
			ret = event_facility_unlock(&event_lock_0);
		}
		if ( _ok != ret )
		{
			break;
		}
	}
	return 0;
}

void test_event_lock_thread()
{
	_ERROR ret = _failed;

	EVENT_HANDLE event_lock_0;
	THREAD_HANDLE thread_event_0;
	THREAD_HANDLE thread_event_1;

	THREAD_HANDLE thread_event_2;
	THREAD_HANDLE thread_event_3;

	ret = event_lock_create(&event_lock_0, "event_lock_0");
	ret = thread_create(&thread_event_0, test_event_lock_entry_0, (void *)&event_lock_0, "thread_event_0");
	ret = thread_create(&thread_event_1, test_event_lock_entry_0, (void *)&event_lock_0, "thread_event_1");

	ret = thread_create(&thread_event_2, test_event_lock_entry_1, NULL, "thread_event_2");
	ret = thread_create(&thread_event_3, test_event_lock_entry_1, NULL, "thread_event_3");

	switch ( ret )
	{
	case _ok:
	case _err_exist:
		{
			thread_destroy(&thread_event_0, -1);
			thread_destroy(&thread_event_1, -1);
			thread_destroy(&thread_event_2, -1);
			thread_destroy(&thread_event_3, -1);
			event_destroy(&event_lock_0);
			break;
		}
	}
}


/************************************************************************/
/*                                                                      */
/************************************************************************/

int test_count = 0;
#define SEM_MAX_COUNT 100

unsigned int __stdcall test_semaphore_entry_r_0(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index  = 0;
	SEMAPHORE_HANDLE * h	= (SEMAPHORE_HANDLE *)p;

	for ( index = 0; ; index++ )
	{
		if ( _ok == (ret = semaphore_wait(h, -1)) )
			printf("%s ----- %d  %d\n", name, index, test_count);
		else
			printf("semaphore_wait failed\n");

		//Sleep(100);
	}
	return 0;
}



unsigned int __stdcall test_semaphore_entry_w_0(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index = 0;
	SEMAPHORE_HANDLE * h	= (SEMAPHORE_HANDLE *)p;

	//Sleep(1000*2);

	for ( index = 0; index < SEM_MAX_COUNT; index++ )
	{
		test_count ++;
		if ( _ok != (ret = semaphore_set(h)) )
		{
			printf("semaphore_set failed\n");
			break;
		}
		else
		{
			Sleep(1);
		}
	}
	return 0;
}


void test_process_semaphore(int flag)
{
	_ERROR ret = _failed;
	int index = 0;
	SEMAPHORE_HANDLE process_semaphore_0;

	switch ( flag )
	{
	case  _true:
		for ( index = 0; ; index++ )
		{
			if ( _ok == (ret = semaphore_accept(&process_semaphore_0, SEM_MAX_COUNT, "process_semaphore_0", -1)) )
				printf(" ----- %d\n", index);
			else
				printf("semaphore_wait failed\n");

			//Sleep(100);
		}
		break;
	case _false:
		for ( index = 0; index < SEM_MAX_COUNT; index++ )
		{
			if ( _ok != (ret = semaphore_send(&process_semaphore_0, SEM_MAX_COUNT, "process_semaphore_0")) )
			{
				printf("semaphore_set failed\n");
				break;
			}
			else
			{
				printf(" ----- %d  %d\n", index);
				Sleep(1);
			}
		}
		break;
	}	
}

unsigned int __stdcall test_semaphore_entry_r_1(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index  = 0;
	SEMAPHORE_HANDLE semaphore_0;

	for ( index = 0; ; index++ )
	{
		if ( _ok == (ret = semaphore_accept(&semaphore_0, SEM_MAX_COUNT, "semaphore_0", -1)) )
			printf("%s ----- %d  %d\n", name, index, test_count);
		else
			printf("semaphore_wait failed\n");

		//Sleep(100);
	}
	return 0;
}

unsigned int __stdcall test_semaphore_entry_w_1(void * p, const u_char * name, const unsigned int u_id)
{
	_ERROR ret = _failed;
	int index = 0;
	SEMAPHORE_HANDLE semaphore_0;

	//Sleep(1000*2);

	for ( index = 0; index < SEM_MAX_COUNT; index++ )
	{
		test_count ++;
		if ( _ok != (ret = semaphore_send(&semaphore_0, SEM_MAX_COUNT, "semaphore_0")) )
		{
			printf("semaphore_set failed\n");
			break;
		}
		else
		{
			Sleep(1);
		}
	}
	return 0;
}


void test_semaphore_thread()
{
	_ERROR ret;

	SEMAPHORE_HANDLE semaphore_0;

	THREAD_HANDLE thread_semaphore_0;
	THREAD_HANDLE thread_semaphore_1;
	THREAD_HANDLE thread_semaphore_2;
	THREAD_HANDLE thread_semaphore_3;

	ret = semaphore_create(&semaphore_0, SEM_MAX_COUNT, "semaphore_0");

	ret = thread_create(&thread_semaphore_0, test_semaphore_entry_r_0, (void *)&semaphore_0, "thread_semaphore_0");
	ret = thread_create(&thread_semaphore_1, test_semaphore_entry_w_0, (void *)&semaphore_0, "thread_semaphore_1");
	ret = thread_create(&thread_semaphore_2, test_semaphore_entry_r_1, NULL, "thread_semaphore_2");
	ret = thread_create(&thread_semaphore_3, test_semaphore_entry_w_1, NULL, "thread_semaphore_3");

	switch ( ret )
	{
	case _ok:
	case _err_exist:
		{
			thread_destroy(&thread_semaphore_0, -1);
			thread_destroy(&thread_semaphore_1, -1);
			thread_destroy(&thread_semaphore_2, -1);
			thread_destroy(&thread_semaphore_3, -1);
			break;
		}
	}
	semaphore_destroy(&semaphore_0);
}







/************************************************************************/
/*                                                                      */
/************************************************************************/



void test_process_mutex(const char * name)
{
	_ERROR ret = _failed;
	int index  = 0;
	MUTEX_HANDLE process_mutex_lock_0;

	for ( index = 0; /*index < 10*/; index++ )
	{
		__try
		{
			if ( _ok == (ret = mutex_facility_lock(&process_mutex_lock_0, "process_mutex_lock_0")) )
			{
				MessageBox(NULL, name, "", MB_OK);
				//printf("< %s--%d > ---- running %d %d\n", name, u_id, index, ++thread_index);
			}
		}
		__finally
		{
			ret = mutex_facility_unlock(&process_mutex_lock_0);
		}
		if ( _ok != ret )
		{
			break;
		}
	}
}


void test_process_event(const char * name)
{
	_ERROR ret = _failed;
	int index  = 0;
	EVENT_HANDLE process_event_lock_0;

	for ( index = 0; /*index < 10*/; index++ )
	{
		__try
		{
			if ( _ok == (ret = event_facility_lock(&process_event_lock_0, "process_event_lock_0")) )
			{
				MessageBox(NULL, name, "", MB_OK);
				//printf("< %s--%d > ---- running %d %d\n", name, u_id, index, ++thread_index);
			}
		}
		__finally
		{
			ret = event_facility_unlock(&process_event_lock_0);
		}
		if ( _ok != ret )
		{
			break;
		}
	}
}



unsigned int __stdcall test_handle_define_entry_0(void * p, const u_char * name, const unsigned int u_id)
{
	MessageBox(NULL, name, "", MB_OK);
	return 0;
}

void test_handle_define()
{
	_ERROR ret = _failed;

	MUTEX_HANDLE		mutex_lock_00;
	EVENT_HANDLE		event_lock_00;
	SEMAPHORE_HANDLE	semaphore_00;

	THREAD_HANDLE		thread_00;

	ret = mutex_create(&mutex_lock_00, "mutex_lock_00");
	ret = mutex_create(&mutex_lock_00, "mutex_lock_00");
	ret = mutex_destroy(&mutex_lock_00);

	ret = event_lock_create(&event_lock_00, "event_lock_00");
	ret = event_lock_create(&event_lock_00, "event_lock_00");
	ret = event_destroy(&event_lock_00);

	ret = semaphore_create(&semaphore_00, 10, "semaphore_00");
	ret = semaphore_create(&semaphore_00, 10, "semaphore_00");
	ret = semaphore_destroy(&semaphore_00);

	ret = thread_create(&thread_00, test_handle_define_entry_0, NULL, "thread_00");
	ret = thread_create(&thread_00, test_handle_define_entry_0, NULL, "thread_00");
	ret = thread_destroy(&thread_00, -1);
}
