#include "bdirectory.h"




CBDirectory::CBDirectory()
{

}



CBDirectory::~CBDirectory()
{

}



int CBDirectory::CreateDirectory(char * strPath)
{
	if (strPath)
	{
		switch(mkdir(strPath))
		{
		case __SUCCESS:
			return __SUCCESS;
		case __FAILED:
			break;
		}
	}
	return __FAILED;
}



int CBDirectory::DeleteDirectory(char * strPath)
{
	if (strPath)
	{
		switch(rmdir(strPath))
		{
		case __SUCCESS:
			return __SUCCESS;
		case __FAILED:
			break;
		}
	}
	return __FAILED;
}



int CBDirectory::GetCurrentDirObjPath(
									  int			nPathLen,
									  char			* szPath,
									  const char	* szFileName
									  )
{
	if ((nPathLen > 0)&&(szPath)&&(szFileName))
	{
		::GetModuleFileName(NULL, szPath, nPathLen);

		if (nPathLen > (int)strlen(szPath) + (int)strlen(szFileName))
		{
			char * p = strrchr(szPath, '\\');
			
			*(++p) = '\0';
			
			strcat(szPath, szFileName);

			return __SUCCESS;
		}	
	}
	return __FAILED;
}



int CBDirectory::GetCurrentDir(char * strPath, int nPathLen)
{
	if (strPath)
	{
		if (getcwd(strPath, nPathLen))
		{
			return __SUCCESS;
		}
	}
	return __FAILED;
}



int CBDirectory::GetEnvionmentVar(
								  const char	* strEnvName,
								  char			* strRetEnvVar
								  )
{
	if ((strEnvName)&&(strRetEnvVar))
	{
		char * p = getenv(strEnvName);
		if (p)
		{
			strcpy(strRetEnvVar, p);
			return __SUCCESS;
		}
	}
	return __FAILED;
}



int CBDirectory::GetUtterlyPathDriveLetter(
										   const char	* szPath,
										   char			* szDriveLetter
										   )
{
	if ((szPath)&&(szDriveLetter))
	{
		char * p = strstr(szPath, ":\\");

		if (p)
		{
			int n = p - szPath + 1;

			strncpy(szDriveLetter, szPath, n);

			szDriveLetter += n;

			*szDriveLetter = '\0';
		}
		return __SUCCESS;
	}
	return __FAILED;
}


