#include <stdio.h>
int main()
{
	char a[] = "ËïnÖĞ¹ú";
	for (int i = 0; i < 7; i++)
	{
		a[i] -= 160;
	}
	char b[100]; 
	b[0] = 0xCB;
	b[1] = 0xEF;
	char bufTem2[20];
	char szTemp[4] = "001";
	int nDevTem;
	sprintf(bufTem2, "%C%C", szTemp[1], szTemp[2]);
	sscanf(bufTem2,"%x", &nDevTem);
	return 0;
}