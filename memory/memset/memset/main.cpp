/**/
#include <memory.h>
#include <stdio.h>
int main()
{
//	float a[2][2] = {0.2, 0.3, 0.4, 0.5};
	int c = 1;
	int d = 10;
	int e = 100;
	int f = 1024;
	int g = 1025;
	int a[2][2] = {2, 3, 4, 5};
	int b = sizeof(a);
	memset(a, 1, sizeof(a));
	return 0;
}

/* MEMSET.C: This program uses memset to
 * set the first four bytes of buffer to "*".
 
#include <memory.h>
#include <stdio.h>

void main( void )
{
   char buffer[] = "This is a test of the memset function";

   printf( "Before: %s\n", buffer );
   memset( buffer, '*', 4 );
   printf( "After:  %s\n", buffer );
}

*/
