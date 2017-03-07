// FileOperateClass.cpp: implementation of the CFileOperateClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileOperateClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOperateClass::CFileOperateClass()
{
	int i = 0;
}

CFileOperateClass::~CFileOperateClass()
{

}


VOID  CFileOperateClass::GetFilePath( IN  OUT   PCHAR  lpFileName )
{
	char szFilePath[MAX_PATH] = {0};

	::GetModuleFileName( NULL, szFilePath, MAX_PATH );
	
	string strTempMemoryPath = szFilePath;

	///////////////////////////整型和位域变量（number）前缀 -- n
	int nPos = strTempMemoryPath.find_last_of( "\\" );

	strTempMemoryPath = strTempMemoryPath.substr( 0, (nPos + 1) );

	strTempMemoryPath.append( lpFileName );

	memset( lpFileName, 0, MAX_PATH );
	
	strcpy( lpFileName, strTempMemoryPath.c_str() );

	_strlwr( lpFileName );
}


VOID  CFileOperateClass::GetFilePath( IN  OUT   string  &strFileName )
{
 	char szFilePath[MAX_PATH] = {0};

	::GetModuleFileName( NULL, szFilePath, MAX_PATH );

	string strFilePath = szFilePath;
	
	///////////////////////////整型和位域变量（number）前缀 -- n
	int nPos = strFilePath.find_last_of( "\\" );
	
	strFilePath = strFilePath.substr( 0, (nPos + 1) );
	
	strFilePath.append( strFileName );

	strFileName = strFilePath;
}


BOOL  CFileOperateClass::ReadFile( IN        PCHAR             lpFileFullPath,
								   IN  OUT   PDATA_STRUCTURE   &pDataStructure )
{	
	return TRUE;
}

BOOL  CFileOperateClass::WriteFile( IN        PCHAR             lpFileFullPath,
									IN        PDATA_STRUCTURE   pDateStructure )
{
	return TRUE;
}

BOOL  CFileOperateClass::WriteFile( IN        unsigned char       *pchBuffer,
								    IN 	      const UINT           nDataLength,
								    IN        string               strFileFullPath )
{
	//打开文件
	FILE *pFileW = NULL;
	
	pFileW = fopen( strFileFullPath.c_str(), "w+" );

	if ( NULL == pFileW )
	{
		return FALSE;
	}

	//写入文件
	fseek(pFileW, 0, SEEK_CUR); 

	fwrite( pchBuffer, sizeof(char), nDataLength, pFileW);

	char szTemp[1024] = {0};
	
	for( int i = 0; i < 1433; i++ )
	{
		fwrite( szTemp, sizeof(char), nDataLength, pFileW );
	}

	//关闭文件
	if ( fclose(pFileW) )
	{
		return FALSE;
	}
	
	return TRUE;
}

int CFileOperateClass::ReadFile( IN OUT    unsigned char       *pchBuffer,
								 IN 	   const UINT           nDataLength,
								 IN        string               strFileFullPath )
{
//	ACE_GUARD_RETURN( ACE_Process_Mutex, obj, m_FileOpeateProcessMutex, -1 );
	
	FILE *pFile = NULL;

	pFile = fopen( strFileFullPath.c_str(), "rb" );

	if( NULL == pFile)
	{
		return -1;
	}

	fseek( pFile, 0, SEEK_SET );				//////////Moves the file pointer to a specified location
	
	int numread = fread( (PCHAR)pchBuffer,
						 nDataLength,
						 1,
						 pFile );

	long lPos = ftell(pFile);					//////////Gets the current position of a file pointer.

	if ( fclose(pFile) )
	{
		return -1;
	}
	
	return 0;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
int CFileOperateClass::ParseConnectDbConfigurationFile(
									IN    OUT   string    &strConnection,
									IN          string     strIp,
									IN    OUT   string    &strUseID,
									IN    OUT   string	  &strPassWord,
									IN          string     strFileFullPathName )
{	
	PCONNECT_DB_CONFIGURATION_FILE pBuffer = new CONNECT_DB_CONFIGURATION_FILE;
	
	int nDataLength = sizeof( CONNECT_DB_CONFIGURATION_FILE );
	
	memset( (PCHAR)pBuffer, 0, nDataLength );
	
	int nStatus = CFileOperateClass::ReadFile( (unsigned char*)pBuffer,
											   nDataLength,
											   strFileFullPathName );
	
	if ( 0 == nStatus )
	{		
		strConnection  =  "Provider=";
		strConnection +=  pBuffer->Provider;
		strConnection +=  ";";
		strConnection +=  "Persist Security Info=";
		strConnection +=  pBuffer->PerSInfo;
		strConnection +=  ";";
		strConnection +=  "NETWORK=DBMSSOCN;";
		strConnection +=  "User ID=";
		strConnection +=  pBuffer->UserID;
		strConnection +=  ";";
		strConnection +=  "Initial Catalog=";
		strConnection +=  pBuffer->InitialCatalog;
		strConnection +=  ";";
		strConnection +=  "Data Source=";
		strConnection +=  pBuffer->DataSource;
		strConnection +=  ",";
		strConnection +=  pBuffer->port;
		
		if( strlen(pBuffer->Other) > 0 )
		{
			strConnection +=  ";";
			strConnection +=  pBuffer->Other;
			strConnection +=  ";";
		}
		strUseID     = pBuffer->UserID;
		strPassWord  = pBuffer->PassWord;
		
		strIp.assign(pBuffer->DataSource);
	}
	
	strConnection += "\n" + strUseID + "\n" + strPassWord + "\n" + strIp;
	
	::MessageBox( NULL, strConnection.c_str(), "", MB_OK );

	delete pBuffer;
	
	return nStatus;
}


//首先要确定屏幕截取的区域,用LPRECT结构来定义.可以截取一个窗口,或整个屏幕.以下代码把选定的屏幕区域拷贝到位图中. 
HBITMAP CFileOperateClass::CopyScreenToBitmap(LPRECT lpRect)
//lpRect 代表选定区域
{
	HDC hScrDC, hMemDC;
	// 屏幕和内存设备描述表

	HBITMAP hBitmap, hOldBitmap;
	// 位图句柄

	int nX, nY, nX2, nY2;
	// 选定区域坐标

	int nWidth, nHeight;
	// 位图宽度和高度

	int xScrn, yScrn;
	// 屏幕分辨率

	// 确保选定区域不为空矩形
	if ( IsRectEmpty(lpRect) )
	{
		return NULL;
	}
	
	//为屏幕创建设备描述表
	hScrDC = CreateDC( "DISPLAY", NULL, NULL, NULL );

	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC( hScrDC );

	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	
	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);

	//确保选定区域是可见的
	if (nX < 0)
	{
		nX = 0;
	}
	
	if (nY < 0)
	{
		nY = 0;
	}
	
	if (nX2 > xScrn)
	{
		nX2 = xScrn;
	}

	if (nY2 > yScrn)
	{
		nY2 = yScrn;
	}
	
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);

	// 把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);

	//得到屏幕位图的句柄
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);

	//清除
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

	// 返回位图句柄
	return hBitmap;
}


//我们也可以把屏幕内容以位图格式存到磁盘文件上.
int CFileOperateClass::SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap 为刚才的屏幕位图句柄
{
	//lpFileName 为位图文件名
	HDC hDC;
	//设备描述表
	int iBits;
	//当前显示分辨率下每个像素所占字节数
	WORD wBitCount;
	//位图中每个像素所占字节数
	//定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数
	DWORD dwPaletteSize=0, dwBmBitsSize, dwDIBSize, dwWritten;

	BITMAP Bitmap;
	//位图属性结构
	BITMAPFILEHEADER bmfHdr;
	//位图文件头结构
	BITMAPINFOHEADER bi;
	//位图信息头结构
	LPBITMAPINFOHEADER lpbi;
	//指向位图信息头结构
	HANDLE fh, hDib, hPal,hOldPal=NULL;
	//定义文件，分配内存句柄，调色板句柄

	//计算位图文件每个像素所占字节数
	hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) *
	GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	
	if (iBits <= 1)
	wBitCount = 1;
	else if (iBits <= 4)
	wBitCount = 4;
	else if (iBits <= 8)
	wBitCount = 8;
	else if (iBits <= 24)
	wBitCount = 24;
	
	//计算调色板大小
	if (wBitCount <= 8)
	{
		dwPaletteSize = (1 << wBitCount)*sizeof(RGBQUAD);
	}

	//设置位图信息头结构
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;

	//为位图内容分配内存
	hDib = GlobalAlloc( GHND,
						dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER) );

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);

	*lpbi = bi;

	// 处理调色板
	hPal = GetStockObject(DEFAULT_PALETTE);

	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal = (HANDLE)SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	// 获取该调色板下新的像素值
	GetDIBits( hDC,
			   hBitmap,
			   0,
			   (UINT)Bitmap.bmHeight,
			   (LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize,
			   (LPBITMAPINFO)lpbi,
			   DIB_RGB_COLORS );

	//恢复调色板
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	//创建位图文件
	fh = CreateFile( lpFileName,
					 GENERIC_WRITE,
					 0,
					 NULL,
					 CREATE_ALWAYS,
					 FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,
					 NULL );

	if (fh == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	// 设置位图文件头
	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;

	// 写入位图文件头
	::WriteFile( fh,
			     (LPSTR)&bmfHdr,
			     sizeof(BITMAPFILEHEADER),
			     &dwWritten,
			     NULL );

	// 写入位图文件其余内容
	::WriteFile( fh,
			     (LPSTR)lpbi,
			     dwDIBSize,
			     &dwWritten,
			     NULL );
	
	//清除
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return 0;
}
