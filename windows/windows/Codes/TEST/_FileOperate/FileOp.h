// FileOp.h: interface for the CFileOp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOP_H__050DCD3C_9468_46F0_8B6D_C1A920DF1EC0__INCLUDED_)
#define AFX_FILEOP_H__050DCD3C_9468_46F0_8B6D_C1A920DF1EC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "filebase.h"

//#define __WIN_32

class CFileOp
{
#ifdef __WIN_32

public:
	CFileOp(const char * pFilePath, int nOpenModule);
	virtual ~CFileOp();

public:
	int Write_n(const char *buf, int size, DWORD &dwSize);
	int Read_n(char *buf, int size,  DWORD &dwSize);

	int GetFileSize();
protected:
	HANDLE	m_hFile;
	int		m_FileState;

public:
	enum {  NEW_FILE = 1,
		ADDEND_FILE,
		READ_FILE};
#else

public:
	CFileOp(const char * pPath, const char * mode, int shflag)
	{
		open(pPath, mode, shflag);
	}
	virtual ~CFileOp()
	{
		close();
	}
public:
	int open(const char * pPath, const char * mode, int shflag)
	{
		m_pF = _fsopen(pPath, mode, shflag);
		
		if (NULL == m_pF)
		{
			m_bOpenState = __FILE_CLOSE;
			return __FAILED;
		}
		else
		{
			m_bOpenState = __FILE_OPEN;
		}
		return __SUCCESS;
	}
	int close()
	{
		if (__FILE_OPEN == m_bOpenState)
		{
			m_bOpenState = __FILE_CLOSE;
			fclose(m_pF);
		}
		return __SUCCESS;
	}
	long file_size(const char * pPath)
	{
		FILE * pF_t =_fsopen(pPath, "rb", SH_DENYNO);
		
		if (NULL == pF_t)
		{
			return __FAILED;
		}
		if (fseek(pF_t, 0L, SEEK_END))
		{
			return __FAILED;
		}
		
		long len = ftell(pF_t);
		
		fclose(pF_t);
		
		return len;
	}
public:
	int read_n(char * buf, size_t buf_size, size_t item)
	{
		if (__FILE_CLOSE == get_state())
		{
			return __FAILED;
		}
		int ret = 0;

		memset(buf, 0, (buf_size * item));

		ret = fread(buf, buf_size, item, m_pF);

		if (ret < item)
		{
			return __FAILED;
		}
		return __SUCCESS;
	}
	int write_n(char * buf, size_t buf_size, size_t item)
	{
		if (__FILE_CLOSE == get_state())
		{
			return __FAILED;
		}
		int ret = 0;
		
		ret = fwrite(buf, buf_size, item, m_pF);
		
		if (ret < item)
		{
			return __FAILED;
		}
		return __SUCCESS;
	}

	int loop_file_point(long offset, int whence)
	{
		fseek(m_pF, offset, whence);
		
		return __SUCCESS;
	}

	int set_file_point_pos(const fpos_t * pos)
	{
		if (fsetpos(m_pF, pos))
		{
			return __SUCCESS;
		}
		return __FAILED;
	}

	int get_file_point_pos(fpos_t * pos)
	{
		if (fgetpos(m_pF, pos))
		{
			return __SUCCESS;
		}
		return __FAILED;
	}
protected:
	int get_state()
	{
		if (NULL == m_pF)
		{
			m_bOpenState = __FILE_CLOSE;
		}
		return m_bOpenState;
	}
	
protected:
	FILE * m_pF;
	BOOL m_bOpenState;
#endif//__WIN_32

};

#endif // !defined(AFX_FILEOP_H__050DCD3C_9468_46F0_8B6D_C1A920DF1EC0__INCLUDED_)
