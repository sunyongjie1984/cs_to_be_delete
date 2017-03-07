#include "example.h"
CExample::CExample()
{
	pBuffer = NULL;
	nSize = 0;
}

void CExample::Init(int n)
{
	pBuffer = new char[n];
    memcpy(pBuffer, "hello", 10);
	nSize = n;
}
