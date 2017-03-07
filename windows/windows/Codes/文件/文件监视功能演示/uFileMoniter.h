//---------------------------------------------------------------------------
// 文件监视单元
// by ccrun(老妖) - info@ccrun.com
// Last modify: ***
//---------------------------------------------------------------------------
// Welcome C++Builder Study - http://www.ccrun.com
//---------------------------------------------------------------------------
#ifndef uFileMoniterH
#define uFileMoniterH

long g_HSHNotify;
LPITEMIDLIST g_pidlDesktop;

typedef struct _IDLSTRUCT
{
	LPITEMIDLIST pidl;
	long bWatchSubFolders;
}IDLSTRUCT, *PIDLSTRUCT;

typedef struct _SHNOTIFYSTRUCT
{
	LPITEMIDLIST dwItem1;
    LPITEMIDLIST dwItem2;
}SHNOTIFYSTRUCT, *PSHNOTIFYSTRUCT;

// 定义未公开API函数
typedef int (WINAPI *SHCHANGENOTIFYREGISTER)(long, int, DWORD, int, DWORD, PIDLSTRUCT);
typedef int (WINAPI *SHCHANGENOTIFYDEREGISTER)(int);
SHCHANGENOTIFYREGISTER   SHChangeNotifyRegister;
SHCHANGENOTIFYDEREGISTER SHChangeNotifyDeregister;

// 注册通知消息
bool __fastcall RegSHNotify(HANDLE hWnd);
// 解除通知注册
bool __fastcall UnregSHNotify();
// 获取消息具体内容
String __fastcall NotifyReceipt(WPARAM wParam, LPARAM lParam);

// 通知消息
#define WM_SHNOTIFY 0x401

//---------------------------------------------------------------------------
bool __fastcall RegSHNotify(HANDLE hWnd)
{
    IDLSTRUCT ps;

    HINSTANCE hDll = LoadLibrary("SHELL32");
    if(hDll)
    {
        SHChangeNotifyRegister = (SHCHANGENOTIFYREGISTER)GetProcAddress(hDll, (char *)2);
        if(!SHChangeNotifyRegister)
        {
        	ShowMessage("GetProcAddr register error!");
        	return false;
        }
    }
    else
    	return false;
    if(g_HSHNotify == 0)
    {
        // 取得桌面的IDL
        // SHGetSpecialFolderLocation(0, CSIDL_DESKTOP, &g_pidlDesktop);
		SHGetSpecialFolderLocation(0, CSIDL_DRIVES, &g_pidlDesktop);
        if(g_pidlDesktop)
        {
			memset(&ps, 0x00, sizeof(ps));
            ps.pidl = g_pidlDesktop;
            ps.bWatchSubFolders = 1;
            // 注册Windows监视
            g_HSHNotify = SHChangeNotifyRegister(
            		long(hWnd),
                    SHCNF_TYPE | SHCNF_IDLIST,
		            SHCNE_ALLEVENTS | SHCNE_INTERRUPT,
    		        WM_SHNOTIFY,
                    1,
                    &ps
                    );
            FreeLibrary(hDll);
            return bool(g_HSHNotify);
        }
        else
            CoTaskMemFree(g_pidlDesktop);
    }
    FreeLibrary(hDll);
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall UnregSHNotify()
{
    HINSTANCE hDll = LoadLibrary("SHELL32.dll");
    if(hDll)
    {
        SHChangeNotifyDeregister = (SHCHANGENOTIFYDEREGISTER)
                GetProcAddress(hDll, (char *)4);
        if(!SHChangeNotifyDeregister)
        {
        	ShowMessage("GetProcAddr deregister error!");
        	return false;
        }
    }
    else
    	return false;

	if(g_HSHNotify)
    {
    	if(SHChangeNotifyDeregister(g_HSHNotify))
        {
            g_HSHNotify = 1;
            CoTaskMemFree(g_pidlDesktop);
            g_pidlDesktop = 0;
            FreeLibrary(hDll);
            return true;
        }
    }
    FreeLibrary(hDll);
    return false;
}
//---------------------------------------------------------------------------
String __fastcall NotifyReceipt(WPARAM wParam, LPARAM lParam)
{
	String strEvent;
	char szBuf[MAX_PATH];
	String strPath1, strPath2;

	SHNOTIFYSTRUCT *pidlItem = PSHNOTIFYSTRUCT(wParam);
  	SHGetPathFromIDList(pidlItem->dwItem1, szBuf);
    strPath1 = String(szBuf);
	SHGetPathFromIDList(pidlItem->dwItem2, szBuf);
    strPath2 = String(szBuf);

    switch(lParam)
    {
        case SHCNE_RENAMEITEM:
			strEvent = "重命名文件: " + strPath1 + " 为 " + strPath2;
            break;
        case SHCNE_CREATE:
        	strEvent = "建立文件, 文件名: " + strPath1 + strPath2;
            break;
        case SHCNE_DELETE:
        	strEvent = "删除文件, 文件名: " + strPath1;
            break;
        case SHCNE_MKDIR:
        	strEvent = "建立目录, 目录名: " + strPath1;
            break;
        case SHCNE_RMDIR:
            strEvent = "删除目录,目录名: " + strPath1;
            break;
        case SHCNE_MEDIAINSERTED:
        	strEvent = strPath1 + " 中插入可移动存储介质";
            break;
        case SHCNE_MEDIAREMOVED:
        	strEvent = strPath1 + " 中移去可移动存储介质";
            break;
        case SHCNE_DRIVEREMOVED:
        	strEvent = "移去驱动器: " + strPath1;
            break;
        case SHCNE_DRIVEADD:
        	strEvent = "添加驱动器: " + strPath1;
            break;
        case SHCNE_NETSHARE:
        	strEvent = "改变目录 " + strPath1 + " 的共享属性";
            break;
        case SHCNE_UPDATEDIR:
        	strEvent = "更新目录: " + strPath1;
            break;
        case SHCNE_UPDATEITEM:
        	strEvent = "更新文件, 文件名: " + strPath1;
            break;
        case SHCNE_SERVERDISCONNECT:
        	strEvent = "断开与服务器的连接: " + strPath1 + " " + strPath2;
            break;
        case SHCNE_UPDATEIMAGE:
        	strEvent = "更新图标:" + strPath1 + " " + strPath2;
        	break;
        case SHCNE_DRIVEADDGUI:
        	strEvent = "添加并显示驱动器: " + strPath1;
            break;
        case SHCNE_RENAMEFOLDER:
        	strEvent = "重命名文件夹: " + strPath1 + " 为 " + strPath2;
            break;
        case SHCNE_FREESPACE:
			strEvent = "磁盘空间大小改变: " + strPath1 + strPath2;
            break;
        case SHCNE_ASSOCCHANGED:
        	strEvent = "改变文件关联: " + strPath1 + " " + strPath2;
            break;
        default:
        	strEvent = "其他操作.";
        	break;
    }
    return strEvent;
}



//---------------------------------------------------------------------------
#endif
