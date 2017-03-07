#include "stdio.h"
#include "String.h"
int main()
{
	char str[] = {"hello world"};
	unsigned long ulLength = 0;

	printf("the string is: %s\n", str);
	ulLength = Strlen(str);
	printf("the string length is: %d(use Strlen)\n", ulLength);

	ulLength = StrNlen(str, 10);
	printf("the string length is: %d(use StrNlen)\n", ulLength);

	return 0;
}
