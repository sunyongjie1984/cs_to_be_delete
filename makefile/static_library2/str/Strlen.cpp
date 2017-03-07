#include <stdio.h>
#include <assert.h>
int Strlen(char * pStr)
{
	unsigned long ulLength;
	assert(NULL != pStr);

	ulLength = 0;
	while (* pStr++)
	{
		ulLength++;
	}

	return ulLength;
}
