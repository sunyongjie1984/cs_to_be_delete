#include <string.h>

extern void iocmplt_main(void);
extern void test_server();
extern void test_client();
extern void test_async_server();
extern void test_async_client();

int main(int argc, char * argv[])
{
	switch (argc)
	{
	case 1:
		break;
	case 2:
		if ( 0 == strcmp(argv[1], "test_client") )
		{
			test_client();
		}
		else if ( 0 == strcmp(argv[1], "test_server") )
		{
			test_server();
		}
		else if ( 0 == strcmp(argv[1], "test_async_client") )
		{
			test_async_client();
		}
		else if ( 0 == strcmp(argv[1], "test_async_server") )
		{
			iocmplt_main/*test_async_server*/();
		}
		
		break;
	}
	return 0;
}

#if 0
#include "../package/headers/protocol_interface.h"


#include <stdio.h>
#include <string.h>


extern void select_main(void);
extern void iocmplt_main(void);

int test_main()
{
	u_char p[20] = {0};
	test_func_name( 'c', p );



	printf( "__FILE__[%s], __LINE__[%d], __DATE__[%s], __TIME__[%s]", __FILE__, __LINE__, __DATE__, __TIME__ );
	return 0;
}

#endif//0

