#include "FileOp.h"

#ifdef __WIN_32

CFileOp::CFileOp(const char * pFilePath, int nOpenModule)
{
	m_hFile		= NULL;
	m_FileState = __FILE_CLOSE;

	switch(nOpenModule)
	{
		case NEW_FILE:
		{
			m_hFile = CreateFile(	pFilePath,
									GENERIC_WRITE,
									0,
									NULL,
									CREATE_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL	);
			break;
		}
		case ADDEND_FILE:
		{
			m_hFile = CreateFile(	pFilePath,
									GENERIC_WRITE,
									FILE_SHARE_WRITE,
									NULL,
									OPEN_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL	);
			break;
		}
		case READ_FILE:
		{
			m_hFile = CreateFile(	pFilePath,
									GENERIC_READ,
									FILE_SHARE_READ,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL	);
			break;
		}
		default:
		{
			break;
		}
	}
	if (INVALID_HANDLE_VALUE == m_hFile) 
	{
		m_FileState = __FILE_CLOSE;
	}
	else
	{
		m_FileState = __FILE_OPEN;
	}
}

CFileOp::~CFileOp()
{
	if (__FILE_OPEN == m_FileState)
	{
		CloseHandle(m_hFile);
	}
}

int CFileOp::GetFileSize()
{
	int nFileSize = ::GetFileSize(m_hFile,NULL);
	
	if (INVALID_FILE_SIZE == nFileSize)
	{
		nFileSize = __FAILED;
	}
	return nFileSize;
}

int CFileOp::Write_n(const char * buf, int size, DWORD &dwSize)
{
	BOOL bStatus = FALSE;
	
	for (int bytes = 0; bytes < size; bytes += dwSize)
	{
		bStatus = WriteFile(m_hFile, (char *)(buf+bytes), (size-bytes), &dwSize, NULL);
		
		if ( bStatus )
		{
			continue;
		}
		return __FAILED;
	}
	return __SUCCESS;
}

int CFileOp::Read_n(char *buf, int size, DWORD &dwSize)
{
	BOOL bStatus = FALSE;
	
	for (int bytes = 0; bytes<size; bytes += dwSize)
	{
		bStatus = ReadFile(m_hFile, (char *)(buf+bytes), (size-bytes), &dwSize, NULL);
		
		if ( bStatus )
		{
			continue;
		}
		return __FAILED;
	}
	return __SUCCESS;
}
#endif//__WIN_32
