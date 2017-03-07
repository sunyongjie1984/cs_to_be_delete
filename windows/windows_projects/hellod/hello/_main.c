#pragma warning(disable:4096 4996 4013)

extern void test_mutex_lock_thread();
extern void test_event_lock_thread();
extern void test_semaphore_thread();
extern void test_handle_define();
extern void test_process_mutex(const char * name);
extern void test_process_event(const char * name);
extern void test_process_semaphore(int flag);

void main(int argc, char * argv[])
{
	switch (argc)
	{
	case 1:
		break;
	case 2:
		if ( 0 == strcmp(argv[1], "test_mutex_lock_thread") )
		{
			test_mutex_lock_thread();
		}
		else if ( 0 == strcmp(argv[1], "test_event_lock_thread") )
		{
			test_event_lock_thread();
		}
		else if ( 0 == strcmp(argv[1], "test_semaphore_thread") )
		{
			test_semaphore_thread();
		}
		else if ( 0 == strcmp(argv[1], "test_handle_define") )
		{
			test_handle_define();
		}
		break;
	case 3:
		if ( 0 == strcmp(argv[1], "test_process_mutex") )
		{
			test_process_mutex(argv[2]);
		}
		if ( 0 == strcmp(argv[1], "test_process_event") )
		{
			test_process_event(argv[2]);
		}
		if ( 0 == strcmp(argv[1], "test_process_semaphore") )
		{
			test_process_semaphore(atoi(argv[2]));
		}
	}
	system("pause");
}