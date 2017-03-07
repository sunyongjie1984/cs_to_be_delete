
	虚拟串口设备驱动
	Virtual Serial Device Driver
		ver 04.1.15

Windows2K下虚拟串口设备驱动程序及相关应用程序

内容列表
===========

主要功能
使用说明
各模块说明
工作机制
亟待改进之处
跟我联系

主要功能
===========

基本上跟商业软件Virtual Serial Ports Driver XP3类似。

1.在操作系统中，虚拟出若干串口。可以使用串口工具（比如操作系统自带的超级终端软件）对串口进行打开、发送、接收、关闭等操作。
2.  由于是虚拟串口，所以可以设置任意波特率、数据位、奇偶校验、停止位等端口操作。
3.  通过协议传送、接收数据。

使用说明
===========

1. 安装toaster( win2k ddk sample)总线驱动程序：BusEnum.sys。安装步骤详见DDK的toaster\bus例子
2. 控制台上运行enum -p 1，对新的硬件设备指定 SimSerial\inf目录，安装我们的虚拟串口驱动程序。
安装完毕以后在“设备管理器”中应该多出一类设备“VirtualSerial”。enum程序由DDK的toaster\exe\enum例子编译。只是改动了toaster\inc\public.h中的#define BUS_HARDWARE_IDS L"Toaster\\MsToaster\0"
3. 控制台上运行enum -p 2，添加第二个虚拟串口设备
4. 控制台上运行test.exe，枚举并且互连刚刚生成的两个串口。
5. 打开“超级终端”，在“连接到”对话框上“连接时使用”中选择“COM20”
6. 打开“超级终端”，在“连接到”对话框上“连接时使用”中选择“COM21”
7. 卸载设备可以在控制台上运行 enum -u 1, enum -u 2
8. 更新驱动程序时，只需要将所有的虚拟串口卸载，然后再编译驱动程序，build -ceZ，运行cc.bat即可。

各模块说明
===========

DebugLog	Debug日志
exe		参考其目录的说明.txt
filter		过滤程序。监视各种串口的操作。在开发过程中帮助很大
inc		app 和 sys都要用到的若干宏定义和其他
inf		最终安装所需要的.inf and .sys
OptSerial		采用传统的方式访问串口的win32 app
readme		本文件所在目录
sys		WDM类型的驱动程序，虚拟串口驱动程序的主体


工作机制
===========

原理
----------------

跟商业软件Virtual Serial Ports Driver XP3类似。
首先利用DDK的toaster bus例子安装toaser bus总线，然后利用该总线驱动程序生成一个（或几个）虚拟PDO。对这些虚拟的PDO，加载这个虚拟串口驱动程序。
注意：toaster bus driver安装以后不会自动生成虚拟设备PDO，需要运行相应的enum程序。
“enum -p 1“会生成一个新的虚拟设备。该设备的Hardware ID基于NTDDK\src\general\toaster\inc\public.h里的#define BUS_HARDWARE_IDS L"Toaster\\MsToaster\0"的定义。这个Hardware ID和我们的虚拟串口驱动程序inf文件(MySerial.inf)里边指定的Hardware ID必须一致。否则安装本驱动程序的时候，会提示“未发现相关的硬件信息”。


具体实现
----------------

DriverEntry:
和普通的WDM程序一样。添加了对gDeviceArray, gPacketPool, gIdleQueue等全局变量的初始化

AddDevice:
生成Kernel mode下的DeviceName
初始化ReadIrp CancelSpinlock and ReadQueue Spinlock
创建三个Queue: ReadIrpQueue, WriteIrpQueue, ReadDataQueue
deviceExtension中的其他变量的初始化

IRP_MN_START_DEVICE

调用AddInterface，给win32 App提供访问接口

IOCTL_CREATE_DOS_NAME
调用SerialDoExternalNaming，生成符号连接和DosName

ReadFile & WriteFile
使用Packet队列。主要实现全部在ReadWrite.c中的三个函数。时间紧迫，做得比较粗糙。


亟待改进之处
=============

1、ReadFile和WriteFile两处需要改进。目前使用的是Packet队列的形式进行数据的传递，效率方面不高。跟IOCTL_SERIAL_SET_QUEUE_SIZE中设置的缓冲区的大小目前没有联系起来。
2、超时处理目前没有进行处理
3、控制线Line control还没有处理
4、Win32 app界面不友好，需要改进成窗口界面

跟我联系
=============

Email:	czzhou@sohu.com
acidfish@driverdevelop.com
