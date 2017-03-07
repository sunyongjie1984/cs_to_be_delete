#ifndef _BDIRECTORY_H_
#define _BDIRECTORY_H_


#include "../share/share.h"


class __EXPORT_DLL CBDirectory
{
public:
	CBDirectory();
	virtual ~CBDirectory();

public:
	static int CreateDirectory(char * strPath);
	static int DeleteDirectory(char * strPath);
	

	/* 获得当前工作目录 */
	static int GetCurrentDir(char * strPath, int nPathLen);
	

	/* 获得环境变量值 */
	static int GetEnvionmentVar(
								const char * strEnvName,
								char * strRetEnvVar
								);


	/* 获得当前工作目录下其他文件路径 */
	static int GetCurrentDirObjPath(
									int			nPathLen,
									char		* szPath,
									const char	* szFileName
									);


	/* 获得输入绝对路径的驱动器名 */
	static int GetUtterlyPathDriveLetter(
											const char	* szPath,
											char		* szDriveLetter
											);
};




#endif//_BDIRECTORY_H_