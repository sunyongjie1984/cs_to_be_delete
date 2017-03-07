#include <string>
using namespace std;
int main()
{
// 	char a[3] = { 0 };
// 	int b[3] = { 0 };
// 	int c[3] = { 1 };
// 	float d[3] = { 0.0 };
// 	float e[3] = { 1 };
// 	memset(c , 0, 3);
// 	memset(e , 0, 3);
	char buffer[] = "This is a test of the memset function";
	
	printf( "Before: %s\n", buffer );
	memset( buffer, '*', 4 );
	printf( "After:  %s\n", buffer );
	return 0;
}