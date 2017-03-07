#include <stddef.h>
#include <string.h>
#include <windows.h>

size_t strlen( char * string );
void TestFind( char * pString );

void main( void )
{
	char strTest[20] = {"alsdfjg.h.t"};
	TestFind( strTest );
	size_t nLen = strlen ( "gfedcba" );
	::MessageBox( NULL, strTest, "", MB_OK );
}

size_t strlen ( char * string )
{
	int iLen;
	for ( iLen = 0; *(string++) != '\0'; iLen++)
	{
		
	}
	return iLen;
}

void TestFind( char * pString )
{
	char szTemp[20];
	memset( szTemp, 0, 20 );
	pString = strrchr( pString, '.' );
	strcpy( szTemp, pString );
	memset( pString, 0, strlen(pString) );
	strcpy( pString, szTemp );
}