// DemoServer.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "DemoServer_i.h"
#include "dlldatax.h"


class CDemoServerModule : public CAtlExeModuleT< CDemoServerModule >
{
public :
	DECLARE_LIBID(LIBID_DemoServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DEMOSERVER, "{A9A1BAA1-57C6-4D35-AFCC-2BEE9436E2C7}")
};

CDemoServerModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

