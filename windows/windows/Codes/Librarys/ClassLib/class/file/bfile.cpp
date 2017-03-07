#include "bfile.h"

#include "../debuglog/debuglog.h"





CBFile::CBFile() : m_pStream (NULL),
				   m_fHandle(__FAILED)
{

}



CBFile::CBFile(
			   const char * strPath,
			   OpenType access,
			   OpenMode mode
			   )
			   : m_pStream (NULL),
			     m_fHandle(__FAILED)
{
	Init(strPath, access, mode);
}



CBFile::~CBFile()
{
	Close();
}



int CBFile::GetOpenState()
{
	if (m_pStream)
		return __SUCCESS;
	else
		return __FAILED;
}



void CBFile::SetOpenType(
						 FileOpenType	&ftype,
						 int			access,
						 int			mode,
						 char			* szType
						 )
{
	ftype.access	= access;
	ftype.mode		= mode;
	
	strcpy(ftype.szMode, szType);
}



void CBFile::ParseOpenType(
						   OpenType		access,
						   OpenMode		mode,
						   FileOpenType &ftype
						   )
{
	int nAccess = 0;

	switch(access)
	{
		case CBFile::APPEND: //在文件末尾添加数据，可读可写权限。
		{
			nAccess = O_CREAT | O_APPEND | O_RDWR | mode;
			SetOpenType(ftype, nAccess, S_IREAD|S_IWRITE, "a+");
			break;
		}
		case CBFile::READ: //只读权限
		{
			nAccess = O_RDONLY | O_BINARY | mode;
			SetOpenType(ftype, nAccess, S_IREAD, "r");
			break;
		}
		case CBFile::WRITE: //只写权限，不清空已存在文件，直接写入。
		{
			nAccess = O_WRONLY | O_BINARY | mode;
			SetOpenType(ftype, nAccess, S_IWRITE, "w");
			break;
		}
		case CBFile::CREATE: //创建文件，可读可写权限。
		{
			nAccess = O_CREAT | O_RDWR | O_TRUNC | O_BINARY | mode;
			SetOpenType(ftype, nAccess, S_IREAD|S_IWRITE, "r+w+");
			break;
		}
	}
}



int CBFile::Init(
				 const char * strPath,
				 OpenType	access,
				 OpenMode	mode
				 )
{
	FileOpenType ftype;
	
	ParseOpenType(access, mode, ftype);

	m_fHandle = _open( strPath, ftype.access, ftype.mode);

	if (__FAILED != m_fHandle)
	{
		if (NULL != (m_pStream = _fdopen( m_fHandle, ftype.szMode )))
		{
			return __SUCCESS;
		}			
		else
		{
			m_fHandle = __FAILED;
		}
	}
	return __FAILED;
}



void CBFile::Close()
{
	if (__FAILED != m_fHandle)
	{
		if (__SUCCESS == _close(m_fHandle))
		{
			m_fHandle = __FAILED;
		}
	}
	if (m_pStream)
	{
		if (__SUCCESS == fclose(m_pStream))
		{
			m_pStream = NULL;
		}
	}
}



int CBFile::Write(char * buf, size_t &len)
{
	int		tLen		= len;
	int		nRet		= __FAILED;
	size_t	count		= 0;
	char    * pBroken	= buf;

	if ((m_pStream)&&(buf))
	{
		while (len)
		{
			count = fwrite(pBroken, sizeof(char), len, m_pStream);

			fflush(m_pStream);
			
			if (0 != ferror(m_pStream))
			{
				nRet = __FAILED;	break;
			}
			len		= len - count;
			pBroken	= pBroken + count;
		}
		nRet = __SUCCESS;
	}
	else
	{
		nRet = __FAILED;
	}
	len = tLen - len;

	return nRet;
}



int CBFile::Read(char * buf, size_t &len)
{
	int		tLen		= len;
	int		nRet		= __FAILED;
	size_t	count		= 0;
	char    * pBroken	= buf;

	if ((m_pStream)&&(buf))
	{
		while (len)
		{
			if (__SUCCESS == feof(m_pStream))
			{
				//如果还没有到文件底端
				count = fread(pBroken, sizeof(char), len, m_pStream);

				//fflush(m_pStream);	//why?

				if (0 != ferror(m_pStream))
				{
					nRet = __FAILED; break;
				}
				len		= len - count;
				pBroken	= pBroken + count;
			}
			else
			{
				nRet = __EXCEPTION;	break;
			}
			nRet = __SUCCESS;
		}
	}
	else
	{
		nRet = __FAILED;
	}
	len = tLen - len;

	return nRet;
}



int CBFile::Puts(char * str)
{
	if (m_pStream)
	{
		int nRet = fputs(str, m_pStream);
		
		fflush(m_pStream);
		
		if (EOF != nRet)
		{
			return __SUCCESS;
		}
	}
	return __FAILED;
}



int CBFile::Gets(char * str, int len)
{
	if (m_pStream)
	{
		if (__SUCCESS == feof(m_pStream))
		{
			char * pRet = fgets(str, len, m_pStream);

			//fflush(m_pStream);	//why?
			
			if (pRet)
			{
				return __SUCCESS;
			}
		}
	}	
	return __FAILED;
}



long CBFile::GetSize()
{
//	long lRet = 0;
//	if (m_pStream)
//	{
//		if (__SUCCESS == fseek(m_pStream, 0L, SEEK_END))
//		{
//			lRet = ftell(m_pStream);
//		}
//		if (__SUCCESS != fseek(m_pStream, 0L, SEEK_SET))
//		{
//			return -1;
//		}
//		return lRet;
//	}
//	return -1;

	if (__FAILED != m_fHandle)
	{
		return _filelength(m_fHandle);
	}
	return __FAILED;
}



long CBFile::GetSize(char * szFilePath)
{
	CBFile	* pf = NULL;
	long	lRet = __FAILED;

	if (pf = new CBFile())
	{
		if (DETECT(pf->Init(szFilePath, CBFile::READ, CBFile::BINARY)))
		{
			lRet = pf->GetSize();
		}
		delete pf;	pf = NULL;
	}
	return lRet;
}



int CBFile::ChangeSize(const long lSize)
{
	if (__FAILED != m_fHandle)
	{
		if (__SUCCESS == _chsize(m_fHandle, lSize))
		{
			return __SUCCESS;
		}
	}
	return __FAILED;
}



int CBFile::DelFile(const char * path)
{
	if (__SUCCESS == remove(path))
	{
		return __SUCCESS;
	}
	else
		return __FAILED;
}



int CBFile::MovFile(const char * strRes, const char * strWhither)
{
	if ((strRes)&&(strWhither))
	{
		switch(rename(strRes, strWhither))
		{
			case __SUCCESS:		return __SUCCESS;
			case __FAILED:		break;
		}
	}
	return __FAILED;
}



int CBFile::CopyFile(const char * strRes, const char * strWhither)
{
	if (::CopyFile(strRes, strWhither, TRUE))
	{
		return __SUCCESS;
	}
	return __FAILED;
}



int CBFile::CopyFile(
					 const char		* strRes,
					 const char		* strWhither,
					 unsigned int	len
					 )
{
	int  nRet;		nRet = __FAILED;
	char * buf;		buf  = new char[len];

	CBFile * pRes	  = NULL;
	CBFile * pWhither = NULL;
	
	int tLen;   tLen = len;

	pRes	 = new CBFile(strRes, CBFile::READ, CBFile::BINARY);
	pWhither = new CBFile(strWhither, CBFile::CREATE, CBFile::BINARY);

	while ((pRes)&&(pWhither)&&(buf))
	{
		memset(buf, 0, len);
		
		if (__FAILED != (nRet = pRes->Read(buf, len)))
		{
			if (DETECT(pWhither->Write(buf, len)))
			{
				len = tLen;
				
				if (__EXCEPTION == nRet)
				{
					nRet = __SUCCESS;	break;
				}
			}
			else
			{
				nRet = __FAILED;	break;
			}
		}
		else
		{
			nRet = __FAILED;	break;
		}
	}
	delete[]  buf;		buf		 = NULL;
	delete    pRes;		pRes	 = NULL;
	delete    pWhither;	pWhither = NULL;

	return nRet;
}

bool CBFile::IsLawlessFileName(char * szPath)
{

	//	\ / : * ? " < > | 是非法字符
	char szLawlessCh[] = {'\\', '/', '<', '>', ':', '*', '?', '"', '|'};
	int nSize = sizeof(szLawlessCh);
	if ((szLawlessCh)&&(szPath))
	{
		char * pTmp = NULL;
		for (int i = 0; i < nSize; i++)
		{
			if ((pTmp = strchr(szPath, szLawlessCh[i])))
			{
				return true;
			}
		}
	}
	return false;
}



//---------------------------------------------------------------------



//---------------------------------------------------------------------



CBWFile::CBWFile()
{
	m_fHandle = NULL;
}



CBWFile::CBWFile(
			   const char * strPath,
			   OpenType access,
			   OpenMode mode
			   )
{
	m_fHandle = NULL;
	Init(strPath, access, mode);
}



CBWFile::~CBWFile()
{
	Close();
}



int CBWFile::GetOpenState()
{
	if (INVALID_HANDLE_VALUE != m_fHandle)
		return __SUCCESS;
	else
		return __FAILED;
}


void CBWFile::ParseOpenType(
						    OpenType		access,
						    OpenMode		mode,
						    FileOpenType	&ftype
						    )
{
	int nAccess = 0;

	switch(access)
	{
		case CBWFile::APPEND: //在文件末尾添加数据，可读可写权限。
		{
			ftype.dwDesiredAccess = GENERIC_WRITE;
			ftype.dwShareMode = FILE_SHARE_WRITE;
			ftype.dwCreationDisposition = OPEN_ALWAYS;
			ftype.dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

			//nAccess = O_CREAT | O_APPEND | O_RDWR | mode;
			break;
		}
		case CBWFile::READ: //只读权限
		{
			ftype.dwDesiredAccess = GENERIC_READ;
			ftype.dwShareMode = FILE_SHARE_READ;
			ftype.dwCreationDisposition = OPEN_EXISTING;
			ftype.dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

			//nAccess = O_RDONLY | O_BINARY | mode;
			break;
		}
		case CBWFile::WRITE: //只写权限，不清空已存在文件，直接写入。
		{
			ftype.dwDesiredAccess = GENERIC_WRITE;
			ftype.dwShareMode = FILE_SHARE_WRITE;
			ftype.dwCreationDisposition = OPEN_EXISTING;
			ftype.dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

			//nAccess = O_WRONLY | O_BINARY | mode;
			break;
		}
		case CBWFile::CREATE: //创建文件，可读可写权限。
		{
			ftype.dwDesiredAccess = GENERIC_WRITE|GENERIC_READ;
			ftype.dwShareMode = FILE_SHARE_WRITE;
			ftype.dwCreationDisposition = CREATE_ALWAYS;
			ftype.dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

			//nAccess = O_CREAT | O_RDWR | O_TRUNC | O_BINARY | mode;
			break;
		}
	}
}



int CBWFile::Init(
				   const char * strPath,
				   OpenType	access,
				   OpenMode	mode
				  )
{
	FileOpenType ftype;
	
	ParseOpenType(access, mode, ftype);

	m_fHandle = CreateFile(
							strPath,
							ftype.dwDesiredAccess,
							ftype.dwShareMode,
							NULL,
							ftype.dwCreationDisposition,
							ftype.dwFlagsAndAttributes,
							ftype.hTemplateFile
							);

	if (INVALID_HANDLE_VALUE != m_fHandle)
	{
		return __SUCCESS;
	}
	return __FAILED;
}



void CBWFile::Close()
{
	if (INVALID_HANDLE_VALUE != m_fHandle)
	{
		if (CloseHandle(m_fHandle))
		{
			m_fHandle = NULL;
		}
	}
}



int CBWFile::Write(char * buf, DWORD &len)
{
	DWORD	tLen		= len;
	int		nRet		= __FAILED;
	DWORD	count		= 0;
	char    * pBroken	= buf;

	if ((INVALID_HANDLE_VALUE != m_fHandle)&&(buf))
	{
		count = len;
		while (count)
		{
			if (WriteFile(m_fHandle, pBroken, len, &count, NULL))
			{
				pBroken = pBroken + count; len = count = len - count;
				nRet = __SUCCESS;
			}
			else
			{
				nRet = __FAILED;	break;
			}
		}
	}
	len = tLen - len;

	return nRet;
}



int CBWFile::Read(char * buf, DWORD &len)
{
	DWORD	tLen		= len;
	int		nRet		= __FAILED;
	DWORD	count		= 0;
	char    * pBroken	= buf;
	DWORD	dwError		= 0;

	if ((INVALID_HANDLE_VALUE != m_fHandle)&&(buf))
	{
		count = len;
		while (count)
		{
			if (ReadFile(m_fHandle, pBroken, len, &count, NULL))
			{
				if (count)
				{
					pBroken	= pBroken + count;	len = count = len - count;
					nRet	= __SUCCESS;
				}
				else
				{
					nRet = __EXCEPTION;	goto ExitReadFlag;
				}
			}
			else
			{
				switch (dwError = GetLastError())
				{
				case ERROR_HANDLE_EOF:
					{
						pBroken	= pBroken + count;	count = len - count;
						nRet = __EXCEPTION;
						goto ExitReadFlag;
					}
				default:
					{
						nRet = __FAILED; break;
					}
				}
			}

		}
	}
ExitReadFlag:
	len = tLen - len;

	return nRet;
}



int CBWFile::Puts(char * str)
{
	if (INVALID_HANDLE_VALUE != m_fHandle)
	{
		DWORD nLen = strlen(str);

		if (DETECT(Write(str, nLen)))
		{
			return __SUCCESS;
		}
	}
	return __FAILED;
}



int CBWFile::Gets(char * str, DWORD len)
{
	if (INVALID_HANDLE_VALUE != m_fHandle)
	{
		if (DETECT(Read(str, len)))
		{
			return __SUCCESS;
		}
	}	
	return __FAILED;
}



__int64 CBWFile::GetSize()
{
	if (INVALID_HANDLE_VALUE != m_fHandle)
	{
		__int64 nFileSize;
		GetFileSizeEx(m_fHandle, (PLARGE_INTEGER)(&nFileSize));

		return nFileSize;
	}
	return __FAILED;
}



__int64 CBWFile::GetSize(char * szFilePath)
{
	CBWFile	* pf = NULL;
	__int64	lRet = __FAILED;

	if (pf = new CBWFile())
	{
		if (DETECT(pf->Init(szFilePath, CBWFile::READ, CBWFile::BINARY)))
		{
			lRet = pf->GetSize();
		}
		delete pf;	pf = NULL;
	}
	return lRet;
}



int CBWFile::DelFile(const char * path)
{
	if (__SUCCESS == remove(path))
	{
		return __SUCCESS;
	}
	else
		return __FAILED;
}



int CBWFile::MovFile(const char * strRes, const char * strWhither)
{
	if ((strRes)&&(strWhither))
	{
		switch(rename(strRes, strWhither))
		{
			case __SUCCESS:		return __SUCCESS;
			case __FAILED:		break;
		}
	}
	return __FAILED;
}



int CBWFile::CopyFile(const char * strRes, const char * strWhither)
{
	if (::CopyFile(strRes, strWhither, TRUE))
	{
		return __SUCCESS;
	}
	return __FAILED;
}



int CBWFile::CopyFile(
					 const char		* strRes,
					 const char		* strWhither,
					 DWORD			len
					 )
{
	int  nRet;		nRet = __FAILED;
	char * buf;		buf  = new char[len];

	CBWFile * pRes	  = NULL;
	CBWFile * pWhither = NULL;
	
	DWORD tLen = len;

	pRes	 = new CBWFile(strRes, CBWFile::READ, CBWFile::BINARY);
	pWhither = new CBWFile(strWhither, CBWFile::CREATE, CBWFile::BINARY);

	while ((pRes)&&(pWhither)&&(buf))
	{
		memset(buf, 0, len);
		
		if (__FAILED != (nRet = pRes->Read(buf, len)))
		{
			if (DETECT(pWhither->Write(buf, len)))
			{
				len = tLen;
				
				if (__EXCEPTION == nRet)
				{
					nRet = __SUCCESS;	break;
				}
			}
			else
			{
				nRet = __FAILED;	break;
			}
		}
		else
		{
			nRet = __FAILED;	break;
		}
	}
	delete[]  buf;		buf		 = NULL;
	delete    pRes;		pRes	 = NULL;
	delete    pWhither;	pWhither = NULL;

	return nRet;
}

bool CBWFile::IsLawlessFileName(char * szPath)
{

	//	\ / : * ? " < > | 是非法字符
	char szLawlessCh[] = {'\\', '/', '<', '>', ':', '*', '?', '"', '|'};
	int nSize = sizeof(szLawlessCh);
	if ((szLawlessCh)&&(szPath))
	{
		char * pTmp = NULL;
		for (int i = 0; i < nSize; i++)
		{
			if ((pTmp = strchr(szPath, szLawlessCh[i])))
			{
				return true;
			}
		}
	}
	return false;
}

