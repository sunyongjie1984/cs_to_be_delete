#include "stdAfx.h"
#include "SockServer.h"
#include <Winsock2.h>
#include <iostream.h>

//***************************************************************************
//
// ?@?\		:?N???X????êã
//
// ???	:???
//			   		
// ??	:
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
CSockServer::CSockServer()
{
	pGuarder = NULL;
	m_nGuarderLen = 0;
}

//***************************************************************************
//
// ?@?\		:?N???X???\???êã
//
// ???	:???
//			   		
// ??	:
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
CSockServer::~CSockServer()
{
	if(	NULL != pGuarder )
		delete[] pGuarder;

	TCPUnLoad();
}

//***************************************************************************
//
// ?@?\		:Ws2_32.dll??g?p????ï≈B
//
// ???	:?????????A???s??1????
//			   		
// ??	:
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::TCPLoad()
{
	WSADATA wsaD;
	WORD m_wVersion = MAKEWORD(2,2);
	int iRet = WSAStartup(m_wVersion, &wsaD);
	if( iRet != 0 )
        return -1;
	else
		return 1;
}

//***************************************************************************
//
// ?@?\		:?\?P?b?g????ï≈B
//
// ???	:????\?P?b?g?????A???s??1????
//			   		
// ??	:nPort-?|?[?g??(I)
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::InitSock(int nPort)
{
	int ServSock;
	struct sockaddr_in serv_addr;
	unsigned long ul = 1;

	TCPLoad();
	ServSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if (ServSock < 0)
	{
		TRACE("Socket init failure!\n");
		return -1;
	}
	if( ioctlsocket( ServSock, FIONBIO, (unsigned long *) &ul ) != 0 )
	{
		TRACE("Setting I/O mode of a socket happen faiture!\n");
		return -1;
	}

	memset( ( char* )&serv_addr, 0, sizeof( serv_addr ) );
	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = ( int )htonl( INADDR_ANY );
	serv_addr.sin_port        = htons( nPort );
	if( bind( ServSock, ( struct sockaddr* )&serv_addr, sizeof( serv_addr ) ) < 0 )
	{
		TRACE("Bind failure!\n");
		return -1;
	} 

	listen( ServSock, LISTENS );
	return ServSock;
}

//***************************************************************************
//
// ?@?\		:SS_SockGuarder?\?????z???????ï≈B
//
// ???	:????1?????A???s??????
//			   		
// ??	:nLen-????(I)
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::InitGuarderArr(int nLen)
{
	m_nGuarderLen = nLen;
	pGuarder = new SH_SockGuarder[nLen];
	
	/* modified by qianss 2004-6-26 -- start -- */
	//if(NULL == pGuarder)
	if(pGuarder == NULL)
	{
		return -1;
	}
	/* modified by qianss 2004-6-26 -- end   -- */
	else
	{
    	/* modified by qianss 2004-6-26 -- start -- */
    	memset(pGuarder , '\0' , nLen*sizeof(SH_SockGuarder));
    	
		for( int i = 0; i < nLen; i++ )
		{
			pGuarder[i].iStatus = NEXT_RECV_NEW_SOCK;
		}
    	/* modified by qianss 2004-6-26 -- end   -- */
    	
		return 1;
	}
}

//***************************************************************************
//
// ?@?\		:?V?????\?P?b?g??}??B
//
// ???	:????1?????A???s??????
//			   		
// ??	:sock-?V?????\?P?b?g(I)
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::InsertSock(int sock)
{
	int i = 0;
	
	for(i=0; i < m_nGuarderLen; i++)
	{
		if( NEXT_RECV_NEW_SOCK == pGuarder[i].iStatus )
		{
			pGuarder[i].iSock = sock;
			pGuarder[i].iStatus = NEXT_RECV_FST_PACK;
			pGuarder[i].iCount = -1;
			pGuarder[i].pUpRec = NULL;  //????????????????
			memset( ( char* )&pGuarder[i].UpFstPack, '0', sizeof( SH_UploadFstPack ) );
			break;
		}
	}
	
	if (i == m_nGuarderLen)
		return -1;
	else
		return 1;
}

//***************************************************************************
//
// ?@?\		:???????A???????[?^?????îY?B
//
// ???	:?????????A???s??1?????A??????f?[?^??s??0?????
//			   		
// ??	:sock-?\?P?b?g(I)
//			 buf-?o?b?t?@(I)
//			 len-?f?[?^?????îY?????
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::PeekRead(int sock, char* buf, int len)
{
	int nRead = 0;
	int nCanRead = recv( sock, buf, len, MSG_PEEK );
	TRACE( "Iosteam can read %d.", nCanRead );
	if( nCanRead >= len )
	{
		nRead = recv( sock, buf, len, 0 );
		if( nRead == len )
			return 1;
		else
			return -1;
	}
	else
	{
		return 0;
	}
}

//***************************************************************************
//
// ?@?\		:?ãÅ?f?[?^?p?b?N????êã
//
// ???	:?????????A???s??1?????A??????f?[?^??s??0?????
//			   		
// ??	:SH_SockGuarder-SH_SockGuarder?\?????z???
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::RecvUploadFstPack(SH_SockGuarder& Guarder)
{
	int	nRet = PeekRead(Guarder.iSock, ( char* )&Guarder.UpFstPack, sizeof( SH_UploadFstPack ) );
	if( nRet < 0 )
		return -1;
	else if ( 0 == nRet )
		return 0;
	else
	{
		Guarder.UpFstPack.lPad = 0;
		nRet = DeleteFilesInFolder( Guarder.UpFstPack.szFolder );
		if( nRet < 0 )
		{
			char c = FAIL_FLAG;
			TCPWrite( Guarder.iSock, &c, sizeof( FAIL_FLAG ) ); //?????????
			closesocket( Guarder.iSock );
			Guarder.iSock = NEXT_RECV_NEW_SOCK; //??????????
			return -1;
		}
		else
		{
			char c = SUCC_FLAG;
			TCPWrite( Guarder.iSock, &c, sizeof( FAIL_FLAG ) ); //?????????
		}

		int nSum = (int)Guarder.UpFstPack.lSum;
		if( NULL == ( Guarder.pUpRec = new SH_UploadRec[nSum] ) )   //?????????
			return -1;

		for( int i = 0; i < nSum; i++ )
		{
			Guarder.pUpRec[i].hFile= NULL;
			Guarder.pUpRec[i].lWritten = 0;
			memset( ( char* )&Guarder.pUpRec[i].FileInfo, '\0', sizeof( SH_FileInfoPack ) );
		}
		Guarder.iStatus = NEXT_RECV_FILE_NAME;
	}

	return 1;
}

//***************************************************************************
//
// ?@?\		:?t?@?C???˜é????êã
//
// ???	:?????????A???s??1?????A??????f?[?^??s??0??????B
//			   		
// ??	:SH_SockGuarder-SH_SockGuarder?\?????z????B
//
// ?@?\??	:?t?@?C?????????ìŸ?t?@?C???????ìŸ?T?[?o?[??t?@?C?????????êã
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::RecvFileInfoPack( SH_SockGuarder& Guarder )
{
	int nCount;
	nCount = Guarder.iCount + 1;
	int nRet = PeekRead( Guarder.iSock, ( char* )&Guarder.pUpRec[nCount].FileInfo, sizeof( SH_FileInfoPack ) );
	if( nRet < 0 )
		return -1;
	else if( 0 == nRet )
		return 0;
	else
	{
		char szFile[FILE_MAX_PATH];
		Guarder.pUpRec[nCount].FileInfo.lPad = 0;
		sprintf( szFile, "%s\\%s", Guarder.UpFstPack.szFolder, 
				Guarder.pUpRec[nCount].FileInfo.szName );

		HANDLE hFile = CreateFile( szFile, GENERIC_WRITE, FILE_SHARE_READ,
				NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
		if ( INVALID_HANDLE_VALUE == hFile  )
			return -1;

		Guarder.pUpRec[nCount].hFile = hFile;
		Guarder.pUpRec[nCount].lWritten = 0;
		Guarder.iCount++;
		Guarder.iStatus = NEXT_RECV_FILE_CONTENT;
		return 1;
	}
}

//***************************************************************************
//
// ?@?\		:?t?@?C????????êã
//
// ???	:?????????A???s??1????
//			   		
// ??	:SH_SockGuarder-SH_SockGuarder?\?????z???
//
// ?@?\??	:?t?@?C???????ìŸ?T?[?o?[??t?@?C????????
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::RecvFileContent( SH_SockGuarder& Guarder )
{
	char szBuff[DATA_BUFSIZE];
	int nCount = Guarder.iCount;
	long lToReadLen;
	long lLeft = Guarder.pUpRec[nCount].FileInfo.lSize - Guarder.pUpRec[nCount].lWritten;
	if( ( int )lLeft >= DATA_BUFSIZE )
		lToReadLen = DATA_BUFSIZE;
	else
		lToReadLen = lLeft;

	int nRead = recv( Guarder.iSock, szBuff, ( int )lToReadLen, 0 );

	if( nRead < 0 )
		return -1;
	else
	{
		int nToWrite = nRead;
		int nWrittenSum = 0;
		HANDLE hFile = Guarder.pUpRec[nCount].hFile;
		if(NULL == hFile)
			return -1;

		while( nToWrite > 0)
		{
			DWORD dwBytesWritten = 0;
			WriteFile( hFile, &szBuff[nWrittenSum], nToWrite, &dwBytesWritten, NULL );
			nWrittenSum += ( int )dwBytesWritten;
			nToWrite -= ( int )dwBytesWritten;
		}

		Guarder.pUpRec[nCount].lWritten += nWrittenSum;
		if( Guarder.pUpRec[nCount].lWritten == Guarder.pUpRec[nCount].FileInfo.lSize )
		{
			TRACE("A File has finished uploading, Written Num: %d!\n", Guarder.pUpRec[nCount].lWritten);
			CloseHandle( hFile );
			Guarder.pUpRec[nCount].hFile = NULL;
			/*
			Guarder.iStatus = TEMP_STATUS
			*/
			if( Guarder.UpFstPack.lSum == ( unsigned long )( Guarder.iCount + 1 ) )
			{
				char c = SUCC_FLAG;
				TCPWrite( Guarder.iSock, &c, sizeof( SUCC_FLAG ) );
				closesocket( Guarder.iSock );
				Guarder.iStatus = NEXT_RECV_NEW_SOCK;

				if( NULL != Guarder.pUpRec )
					delete[] Guarder.pUpRec;    //?????????
			}
			else
			{
				Guarder.iStatus = NEXT_RECV_FILE_NAME;
			}
		}
		return 1;
	}
}

//***************************************************************************
//
// ?@?\		:?t?\?P?b?g????B
//
// ???	:?????????A???s??1?????A??????f?[?^??s??0??????B
//			   		
// ??	:SH_SockGuarder-SH_SockGuarder?\?????z????B
//
// ?@?\??	:?\?P?b?g?????????????A?t?\?P?b?g????B
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::ReadSock( SH_SockGuarder& Guarder )
{
	int nRet = -1;
	switch( Guarder.iStatus )
	{
	case NEXT_RECV_FST_PACK:
		nRet = RecvUploadFstPack( Guarder );
		break;
	case NEXT_RECV_FILE_NAME:
		nRet = RecvFileInfoPack( Guarder );
		break;
	case NEXT_RECV_FILE_CONTENT:
		nRet = RecvFileContent( Guarder );
		break;
	}

	return nRet;
}

//***************************************************************************
//
// ?@?\		:?t?\?P?b?g????B
//
// ???	:?????????A???s??1?????B
//			   		
// ??	:sock-?\?P?b?g(I)
//			 buf-?o?b?t?@(I)
//			 len-?f?[?^????????
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::TCPWrite( int sock, char* buf, int len )
{
	int nLeft = len;
	int nWriteSum = 0;
	int nSend;

	while ( nLeft > 0 )
	{
		nSend = send( sock, &buf[nWriteSum], nLeft, 0 );
		if ( nSend < 0 )
		{
			return -1;
		}
		nWriteSum += nSend;
		nLeft -= nSend;
	}
	return 1;
}

//***************************************************************************
//
// ?@?\		:?G???[??????êã
//
// ???	:
//			   		
// ??	:nErrFlg-?G???[?W??
//			 SH_SockGuarder-SH_SockGuarder?\?????z????B
//
// ?@?\??	:?t?@?C????n???h??????A?N???C?A???g????b?Z?[?W??????
//			 ?\?P?b?g????A?t?@?C?????????A
//			 ?t?@?C????A?b?v???[?h??L?^?|?C???^?[??????êã
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
void CSockServer::ErrorHandler( int nErrFlg, SH_SockGuarder& Guarder )
{
	char c = FAIL_FLAG;
	TCPWrite( Guarder.iSock, &c, sizeof( FAIL_FLAG ) );
	closesocket( Guarder.iSock );
	Guarder.iStatus = NEXT_RECV_NEW_SOCK;

	for( int i = 0; i <= Guarder.iCount; i++ )
	{
		if( NULL != Guarder.pUpRec[i].hFile )
			CloseHandle( Guarder.pUpRec[i].hFile );

		CString strFile;
		strFile.Format("%s\\%s", Guarder.UpFstPack.szFolder, Guarder.pUpRec[i].FileInfo.szName );
		strFile.ReleaseBuffer();
		DeleteFile( strFile );
	}

	if( NULL != Guarder.pUpRec )
		delete[] Guarder.pUpRec;
}

//***************************************************************************
//
// ?@?\		:Ws2_32.dll??????[?h????//
// ???	:?????????A???s??1?????A??????f?[?^??s??0??????B
//			   		
// ??	:
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::TCPUnLoad()
{
	WSACleanup();
	return 1;
}

//***************************************************************************
//
// ?@?\		:?t?H???_??????????t?@?C????????êã
//
// ???	:?????????A???s??1?????B
//			   		
// ??	:pszFolder-?t?H???_(I)?B
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::DeleteFilesInFolder( char* pszFolder )
{
	CFileFind FileFinder;
	CString strWildcard = CString( pszFolder );
	strWildcard += "\\*.*";
	FileFinder.FindFile( strWildcard );
	BOOL bWorking = FileFinder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = FileFinder.FindNextFile();
		if( FileFinder.IsDots() )
         continue;
		if( !FileFinder.IsDirectory() ) 
		{
			CString strFile = FileFinder.GetFilePath(); //????????
			BOOL bSuc = DeleteFile( strFile );          //????????
			if( !bSuc )
				return -1;
		}
	}

	return 1;
}

//***************************************************************************
//
// ?@?\		:?T?[?o?[????B
//
// ???	:?????????A???s??1?????B
//			   		
// ??	:
//
// ?@?\??	:
//			   
// ?O????	:
//
// ????????:
//
// ??????	:
//
// ??	:
//           
//***************************************************************************
int CSockServer::DoTask( int nPort )
{
	int ServerSock;
	int ClientSock;
	fd_set fdread;
	int nRet;

	if( ( ServerSock = InitSock( nPort ) ) < 0 )
		return -1;

	FD_ZERO( &fdread );
	FD_SET( ( unsigned int )ServerSock, &fdread );

	InitGuarderArr( FD_SETSIZE );
	
	while ( 1 )
	{
		if( ( nRet = select( 0, &fdread, NULL, NULL, NULL ) ) > 0 )
		{
			if( FD_ISSET( ServerSock, &fdread ) )
			{
				ClientSock = accept( ServerSock, NULL, NULL );
				if( ClientSock > 0 )
				{
					if( InsertSock( ClientSock ) < 0)
					{
						closesocket( ClientSock );
					}
				}
			}

			for( int i = 0;  i < m_nGuarderLen; i++ )
			{
				if( FD_ISSET( pGuarder[i].iSock,  &fdread ) )
				{
					nRet = ReadSock( pGuarder[i] );     //?????????????

					if( nRet < 0 )
						ErrorHandler( nRet, pGuarder[i] );
					
				}
			}
			FD_ZERO( &fdread );
			FD_SET( ( unsigned int )ServerSock,  &fdread );
			for (i = 0; i < m_nGuarderLen; i++)
			{
				if ( NEXT_RECV_NEW_SOCK != pGuarder[i].iStatus )
					FD_SET( ( unsigned int )pGuarder[i].iSock, &fdread );
			}
		}
	}

	return 0;
}
