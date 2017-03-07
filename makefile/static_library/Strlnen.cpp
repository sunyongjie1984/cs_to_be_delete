#include <stdio.h>
#include <assert.h>
int StrNlen(char * pStr, unsigned long ulMaxLen)
{
	unsigned long ulLength;
	assert(NULL != pStr);

	if (ulMaxLen <= 0)
	{
		printf("Wrong Max Length!\n");
		return -1;
	}

	ulLength = 0;

	while (*pStr++ && ulLength < ulMaxLen)
	{
		ulLength++;
	}

	return ulLength;
}
