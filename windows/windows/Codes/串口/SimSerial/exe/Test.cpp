// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
//#include <ntddser.h>

#include <winioctl.h>

#include <setupapi.h>
#include "objbase.h"
#include <initguid.h>
#include "..\inc\wdmioctl.h"

DEFINE_GUID(GUID_CLASS_COMPORT,          0x86e0d1e0L, 0x8089, 0x11d0, 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73);

typedef struct _Dev_Desc{
	BOOL bIsUsed;
	int ComX;
	int Instance;
	char InterfaceName[ MAX_PATH ];
}DEV_DESC, *LPDEV_DESC;
#define MAX_NUM	256

DEV_DESC gDevDesc[ MAX_NUM ] = { 0 };

//void ConnectPorts();
void Useage();
int ScanDevice();
BOOL IsVSD( char* lpDevicePath );
void AddDevDesc( char* lpDevicePath );
void SetComX();
void ConnectPorts();
void Disconnect();
int  gTotalNum = 0;

int main(int argc, char* argv[])
{
	Useage();
	if( 0 == ScanDevice() ){
		printf("don't find out virtual serial device\n");
		return 0;
	}
	SetComX();
	ConnectPorts();
	//Disconnect();
	return 0;
}
void Useage()
{
	printf("------   Virtual serial device controller   ------\n");
}
int ScanDevice()
{
	int	n, nVSD;
	DWORD		needed;
	HDEVINFO	info;
	SP_INTERFACE_DEVICE_DATA			ifdata;
	PSP_INTERFACE_DEVICE_DETAIL_DATA	detail = NULL;

	n = 0;
	nVSD = 0;
	// 首先得到该ClassGUID值下的设备信息句柄 info. 本程序中ClassGUID代表串口设备类
	// HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses\{86e0d1e0-8089-11d0-9ce4-08003e301f73}
	info = SetupDiGetClassDevs( (LPGUID) &GUID_CLASS_COMPORT,//(LPGUID)&GUID_WDMSAMPLE_DEVICE_INTERFACE_CLASS,
		NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if( info == INVALID_HANDLE_VALUE ){
		printf("Error %d trying to open enumeration handle for \n", GetLastError() );
		return 0;
	}
    ifdata.cbSize = sizeof(ifdata);
	// 使用该 info 依次枚举当前该ClassGUID下的所有设备接口，将该接口信息放在ifdata
    while( SetupDiEnumDeviceInterfaces(info, NULL, (LPGUID)&GUID_CLASS_COMPORT,//(LPGUID) &GUID_WDMSAMPLE_DEVICE_INTERFACE_CLASS,
		n, &ifdata))
	{
		// 第一次调用 SetupDiGetDeviceInterfaceDetail，得到ifdata所需空间大小
		SetupDiGetDeviceInterfaceDetail(info, &ifdata, NULL, 0, &needed, NULL);
		detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA) malloc(needed);
		if (!detail)
		{
			printf("Error %d trying to get memory for interface detail\n", GetLastError());
			goto FAILED;
		}
		// 第二次调用 SetupDiGetDeviceInterfaceDetail，得到ifdata指代的设备的详细信息
		detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		if (!SetupDiGetDeviceInterfaceDetail(info, &ifdata, detail, needed, NULL, NULL))
		{
			printf("Error %d getting interface detail\n", GetLastError());
			goto FAILED;
		}
		printf("%d. %s", n, detail->DevicePath );
		// 判断是否我们的虚拟串口设备
		if( IsVSD( detail->DevicePath ) ){
			printf("  Virtual serial\n");
			nVSD++;
			AddDevDesc( detail->DevicePath );
		}else{
			printf("  Real serial\n");
		}
		free( detail );
		detail = NULL;
		n++;
	}
FAILED:
	if( detail != NULL ){
		free( detail );
	}
	SetupDiDestroyDeviceInfoList( info );
	return nVSD;
}
BOOL IsVSD( char* lpDevicePath )
{
	HANDLE	hfile;
	DWORD	dwIdentifier = 0;
	BOOL	bIsVSD = FALSE;
	DWORD	junk;
	hfile = CreateFile( lpDevicePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        printf("Error %d trying to open %s\n", GetLastError(), lpDevicePath);
        return bIsVSD;
    }
	if( DeviceIoControl( hfile, IOCTL_GET_IDENTITIER, NULL, 0, &dwIdentifier, sizeof( DWORD ), &junk, NULL ) ){
		if( dwIdentifier == VIRTUAL_SERIAL_DEVICE_ID ){
			bIsVSD = TRUE;
		}
	}
	CloseHandle( hfile );
	return bIsVSD;
}
void AddDevDesc( char* lpDevicePath )
{
	HANDLE	hfile;
	int		instance;
	DWORD	junk;
	hfile = CreateFile( lpDevicePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        printf("Error %d trying to open %s\n", GetLastError(), lpDevicePath);
        return;
    }
	instance = 0;
	if( DeviceIoControl( hfile, IOCTL_GET_CURRENT_INSTANCE, NULL, 0, &instance, sizeof( DWORD ), &junk, NULL ) ){
		gDevDesc[ instance ].Instance = instance;
		strcpy( gDevDesc[ instance ].InterfaceName, lpDevicePath );
		gDevDesc[ instance ].bIsUsed = TRUE;
	}
	CloseHandle( hfile );
}
void SetComX()
{
	int		i;
	HANDLE	hfile;
	int		ComX;
	DWORD	junk;
	ComX = 15;

	printf("\n------          Set COMn( 1~255 )           ------\n");
	for( i = 0; i < MAX_NUM; i++)
	{
		if( gDevDesc[ i ].bIsUsed ){
			printf("\\Device\\SiSerial%d ---> ", gDevDesc[ i ].Instance );
			hfile = CreateFile( gDevDesc[ i ].InterfaceName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hfile == INVALID_HANDLE_VALUE)
			{
				printf("Error %d trying to open %s\n", GetLastError(), gDevDesc[ i ].InterfaceName);
				return;
			}
			ComX = -1;
			if( DeviceIoControl( hfile, IOCTL_GET_CURRENT_COMX, NULL, 0, &ComX, sizeof( DWORD ), &junk, NULL ) ){
				printf("COM%d\n", ComX );
			}else{
				ComX = 20 + i;
				if( DeviceIoControl( hfile, IOCTL_CREATE_DOS_NAME, &ComX, sizeof( DWORD ), NULL, 0, &junk, NULL ) ){
					printf("COM%d\n", ComX );
				}else
					printf("  Failed\n");
			}
			CloseHandle( hfile );
		}
	}
}
void ConnectPorts()
{
	int		i;
	HANDLE	hfile, hRemotefile;
	int		ComX;
	DWORD	junk;
	DWORD	remoteInstance, remoteComX;
	
	printf("\n------        Connect COM ports             ------\n");
	for( i = 0; i < MAX_NUM; i++)
	{
		if( gDevDesc[ i ].bIsUsed ){
			printf("\\Device\\SiSerial%d <---> ", gDevDesc[ i ].Instance );
			hfile = CreateFile( gDevDesc[ i ].InterfaceName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hfile == INVALID_HANDLE_VALUE)
			{
				printf("Error %d trying to open %s\n", GetLastError(), gDevDesc[ i ].InterfaceName);
				return;
			}
			if( !DeviceIoControl( hfile, IOCTL_GET_CURRENT_COMX, NULL, 0, &ComX, sizeof( DWORD ), &junk, NULL ) ){
				printf("Don't create dos device name\n");
				CloseHandle( hfile );
				continue;
			}
			if( DeviceIoControl( hfile, IOCTL_GET_REMOTE_INSTANCE, NULL, 0, &remoteInstance, sizeof( DWORD ), &junk, NULL ) ){
				printf("\\Device\\SiSerial%d   ", remoteInstance );
				printf("COM%d <---> ", ComX );
				hRemotefile = CreateFile( gDevDesc[ remoteInstance ].InterfaceName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
				if( hRemotefile == INVALID_HANDLE_VALUE )
				{
					printf("????\n");
					CloseHandle( hfile );
					continue;
				}
				if( DeviceIoControl( hRemotefile, IOCTL_GET_CURRENT_COMX, NULL, 0, &remoteComX, sizeof( DWORD ), &junk, NULL ) ){
					printf(" COM%d\n", remoteComX );
				}else{
					printf(" COM?\n" );
				}
				CloseHandle( hRemotefile );
			}else{
				remoteInstance = i + 1;
				if( DeviceIoControl( hfile, IOCTL_SET_REMOTE_INSTANCE, &remoteInstance, sizeof( ULONG ), NULL, 0, &junk, NULL ) ){
					printf("\\Device\\SiSerial%d   ", remoteInstance );
					printf("COM%d <---> ", ComX );
					hRemotefile = CreateFile( gDevDesc[ remoteInstance ].InterfaceName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
					if( hRemotefile == INVALID_HANDLE_VALUE )
					{
						printf("????\n");
						CloseHandle( hfile );
						continue;
					}
					if( DeviceIoControl( hRemotefile, IOCTL_GET_CURRENT_COMX, NULL, 0, &remoteComX, sizeof( DWORD ), &junk, NULL ) ){
						printf(" COM%d\n", remoteComX );
					}else{
						printf(" COM?\n" );
					}
					CloseHandle( hRemotefile );
				}else{
					printf("Set remote ports failed\n");
					CloseHandle( hfile );
					continue;
				}
			}
			CloseHandle( hfile );
		}
	}
}
void Disconnect()
{
	int i;
	DWORD	junk;
	HANDLE	hfile;
	ULONG	remoteInstance;
	for( i = 0; i < MAX_NUM; i++)
	{
		if( gDevDesc[ i ].bIsUsed ){
			printf("\\Device\\SiSerial%d <---> ", gDevDesc[ i ].Instance );
			hfile = CreateFile( gDevDesc[ i ].InterfaceName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hfile == INVALID_HANDLE_VALUE)
			{
				printf("Error %d trying to open %s\n", GetLastError(), gDevDesc[ i ].InterfaceName);
				return;
			}

			if( DeviceIoControl( hfile, IOCTL_GET_REMOTE_INSTANCE, NULL, 0, &remoteInstance, sizeof( DWORD ), &junk, NULL ) ){
				printf("\\Device\\SiSerial%d   Disconnect...", remoteInstance );
				if( DeviceIoControl( hfile, IOCTL_DISCONNECT, NULL, 0, NULL, 0, &junk, NULL ) ){
					printf(" OK\n");
				}else{
					printf(" Failed\n");
				}
			}else{
				printf("NULL\n");
			}
		}
	}
}
#if 0

void HandleDevice( PSP_INTERFACE_DEVICE_DETAIL_DATA detail )
{
    char	name[ MAX_PATH ];
	DWORD	junk;
	INT		ComX;
	int		i;
	int		instance;

	// 打开设备，此处的设备名称为Kernel mode下IoRegisterDeviceInterface后OS自动生成名称。如下形式
	// ##?#Toaster#MsToaster#1&1aafb3d5&2&01#{86e0d1e0-8089-11d0-9ce4-08003e301f73}
	strncpy(name, detail->DevicePath, sizeof(name));
	for( i = 0; i < 2 ; i++)
	{
		if( !gDevDesc[ i ].bIsUsed ) break;
	}
	ComX = gDevDesc[ i ].ComX;

	if(!DeviceIoControl(hfile,IOCTL_INIT_SETTING, &ComX, sizeof( INT ), NULL , 0, &junk, NULL))
    {
		printf("Direct IOCTL failed with code %d\n", GetLastError());
	}else{
		if( DeviceIoControl( hfile, IOCTL_GET_CURRENT_INSTANCE, NULL, 0, &instance, sizeof( ULONG ), &junk, NULL ) ){
			gDevDesc[ i ].Instance = instance;
			strcpy( gDevDesc[ i ].InterfaceName, detail->DevicePath );
			gDevDesc[ i ].bIsUsed = TRUE;
		}
	}
	if(!DeviceIoControl(hfile,IOCTL_FINISH_SETTING,NULL,0,NULL,0,&junk,NULL))
    {
		printf("Direct IOCTL failed with code %d\n", GetLastError());
	}

	CloseHandle( hfile );
	return;
}
#endif
