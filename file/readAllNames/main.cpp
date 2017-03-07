/*
  target: 读取某目录下的所有文件名
*/
#include <windows.h>
#include <iostream.h>
//using namespace std;

int main(int argc,char *argv[])
{
	WIN32_FIND_DATA FileData;
	HANDLE          hSearch;
	BOOL  bFinished = false;
//	hSearch = FindFirstFile("C:\\test\\*.*", &FileData);
	hSearch = FindFirstFile("d:\\*.*", &FileData);

	if(hSearch == INVALID_HANDLE_VALUE)
	{ 
		cout << "Can't find any file!" << endl;
		return 0;
	}
    cout << FileData.cFileName << endl;

	while(!bFinished)
	{
		if(!FindNextFile(hSearch, &FileData))
		{
			cout << "No more file!" << endl;
			return 0;
		}
		cout << FileData.cFileName << endl;
	}

	return 0;
}

//本文来自CSDN博客，转载请标明出处：file:///N:/网页/读取某目录下文件名的程序%20-%20生于忧患，死于安乐%20-%20CSDN博客.htm