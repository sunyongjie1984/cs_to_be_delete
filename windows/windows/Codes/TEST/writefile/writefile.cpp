#include <windows.h>
#include <stdio.h>

void DetectToLoad( char * szfilepath, int nstrsize );
void RunRecordTask( char * szfilepath );
void WriteFile( char * szfilepath );

#define WRECK_FILE "D:\\Study\\体育\\200605010410\\02.jpg"

int APIENTRY WinMain(	HINSTANCE		hInstance,
						HINSTANCE		hPrevInstance,
						LPSTR			lpCmdLine,
						int				nCmdShow	)
{
#ifdef WRECK_FILE

	for ( int n = 0; n < 1000; n++ )
	{
		WriteFile( WRECK_FILE );
	}

#else

	char szfilepath[MAX_PATH];

	DetectToLoad( szfilepath, sizeof(szfilepath) );

	RunRecordTask( szfilepath );

#endif

	return 0;
}

#define SECOND_T 1000

#define __LOCAL__

#ifdef __LOCAL__
	#define FILE_PATH ":\\Study\\体育\\200605010410\\l.txt"
	#define DETECT_FILE ":\\Study\\体育\\200605010410\\d"
#else
	#define FILE_PATH ":\\Programme\\Language\\Assembly_ L_P\\Technique_Information\\linux Assembly\\L.files\\l.TXT"
	#define DETECT_FILE ":\\Programme\\Language\\Assembly_ L_P\\Technique_Information\\linux Assembly\\L.files\\d"
#endif

#define GET_FILE_PATH( chdrive, szfilepath, strfp)	\
{													\
	memset( szfilepath, 0, nstrsize );				\
	sprintf( szfilepath, "%c", ch );				\
	strcat( szfilepath, strfp );					\
}

void DetectToLoad( char * szfilepath, int nstrsize )
{
	char ch = 'c';

	GET_FILE_PATH( ch, szfilepath, DETECT_FILE )

	FILE * pfDetect;

	while ( TRUE )
	{
		::Sleep( SECOND_T );

		pfDetect = fopen( szfilepath, "r" );

		if ( NULL == pfDetect )
		{
			++ch;

			GET_FILE_PATH( ch, szfilepath, DETECT_FILE )

			if ( 'z' <= ch )
			{
				ch = 'c';
			}

			continue;
		}

		fclose( pfDetect );

		break;
	}

	GET_FILE_PATH( ch, szfilepath, FILE_PATH )
}

#define RECORD_INFO "\r\nENTER DATE : %d-%d-%d TIME : %d:%d:%d:%d"


#define TIME_SPACE 60
#define WRITE_BUFFER 50

void RunRecordTask( char * szfilepath )
{
	while ( TRUE )
	{
		WriteFile( szfilepath );

		::Sleep( SECOND_T * TIME_SPACE );
	}
}


void WriteFile( char * szfilepath )
{
	FILE * pf = NULL;

	pf = fopen( szfilepath, "a+" );

	if ( NULL == pf )
	{
		return;
	}

	SYSTEMTIME systemtime;

	::GetLocalTime( &systemtime );

	char szEnterTime[WRITE_BUFFER];

	memset( szEnterTime, 0, WRITE_BUFFER );

	sprintf(	szEnterTime, RECORD_INFO,
				systemtime.wYear, systemtime.wMonth,
				systemtime.wDay, systemtime.wHour,
				systemtime.wMinute,	systemtime.wSecond,
				systemtime.wMilliseconds					);

	size_t nsize = fwrite( szEnterTime, sizeof(szEnterTime), 1, pf );

	fclose( pf );
}