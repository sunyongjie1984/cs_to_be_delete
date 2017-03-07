#ifndef _BFILE_H_
#define _BFILE_H_




#include "../share/share.h"



class __EXPORT_DLL CBFile
{
public:
	enum OpenType
	{
		CREATE	= 0x00000001,
		APPEND	= 0x00000002,
		READ	= 0x00000004,
		WRITE	= 0x00000008
	};

	enum OpenMode
	{
		TEXT	= O_TEXT,
		BINARY	= O_BINARY
	};


	CBFile();

	CBFile(
			const char * strPath,
			OpenType access,
			OpenMode mode = CBFile::BINARY
			);


	virtual ~CBFile();



public:
	int Write(char * buf, size_t &len);
	int Read(char * buf, size_t &len);

	int Puts(char * str);				//在后面加'\n'
	int Gets(char * str, int len);

	int ChangeSize(const long lSize);
	long GetSize();
	
	void Close();


	int Init(
				const char	* strPath,
				OpenType	access,
				OpenMode	mode
				);


	
	inline int GetOpenState();

	static int DelFile(const char * path);
	static int MovFile(const char * strRes, const char * strWhither);
	static int CopyFile(const char * strRes, const char * strWhither);
	
	static int CopyFile(
						const char		* strRes,
						const char		* strWhither,
						unsigned int	len
						);

	static long GetSize(char * szFilePath);

	static bool IsLawlessFileName(char * szPath);
protected:
	struct FileOpenType 
	{
		int  access;
		int	 mode;
		char szMode[10];
		
		FileOpenType()
		{
			access	= 0;
			mode	= 0;
			memset(szMode, 0, sizeof(szMode));
		}
	};


	void SetOpenType(
						FileOpenType	&ftype,
						int				access,
						int				mode,
						char			* szType
						);

	void ParseOpenType(
						OpenType		access,
						OpenMode		mode,
						FileOpenType	&ftype
						);


protected:
	FILE	* m_pStream;
	int		m_fHandle;
};



class __EXPORT_DLL CBWFile
{
public:
	enum OpenType
	{
		CREATE	= 0x00000001,
		APPEND	= 0x00000002,
		READ	= 0x00000004,
		WRITE	= 0x00000008
	};

	enum OpenMode
	{
		TEXT	= O_TEXT,
		BINARY	= O_BINARY
	};


	CBWFile();

	CBWFile(
			const char * strPath,
			OpenType access,
			OpenMode mode = CBWFile::BINARY
			);


	virtual ~CBWFile();



public:
	int Write(char * buf, DWORD &len);
	int Read(char * buf, DWORD &len);

	int Puts(char * str);				//在后面加'\n'
	int Gets(char * str, DWORD len);

	__int64 GetSize();
	
	void Close();


	int Init(
				const char	* strPath,
				OpenType	access,
				OpenMode	mode
				);


	
	inline int GetOpenState();

	static int DelFile(const char * path);
	static int MovFile(const char * strRes, const char * strWhither);
	static int CopyFile(const char * strRes, const char * strWhither);
	
	static int CopyFile(
						const char		* strRes,
						const char		* strWhither,
						DWORD			len
						);

	static __int64 GetSize(char * szFilePath);

	static bool IsLawlessFileName(char * szPath);
protected:
	struct FileOpenType 
	{		
		DWORD dwDesiredAccess;
		DWORD dwShareMode;
		DWORD dwCreationDisposition;
		DWORD dwFlagsAndAttributes;
		HANDLE hTemplateFile;
		
		FileOpenType()
		{
			dwDesiredAccess = 0;
			dwShareMode = 0;
			dwCreationDisposition = 0;
			dwFlagsAndAttributes = 0;
			hTemplateFile = NULL;
		}
	};

	void ParseOpenType(
						OpenType		access,
						OpenMode		mode,
						FileOpenType	&ftype
						);


protected:
	HANDLE		m_fHandle;
};



#endif//_BFILE_H_