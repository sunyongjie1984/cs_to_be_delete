

olfile readme file.

[1. 文件名解释]
olfile: Offload File
这个工具原本是项目中为测试TOE引擎的效率而设计的，
可以作为socket编程的一个例子来学习。

[2. 文件介绍]
程序中使用socket实现了文件的传输。
在VC6.0中编译通过，目录中olfile.cpp/olfile.h是原文件，可以任意修改，不过请不要改动文件头的作者信息。
有两个目录：server、client，其实编译出来的东西是一样的，当时是为了测试方便才分出来的。
可以直接打开client目录中的工程来编译。

[3. 使用介绍]
程序分client端和server端，server 端监听，client端使用命令行方式发送或接收文件。
在VC6.0中编译生成olfile.exe，使用不同的选项启动client和server。
比如，我们有两台机器10.190.1.1(A), 10.190.1.2(B)，加入都运行windows，想把A的c:\foo.dat传到B，并放在B的c:\foodst.dat，
则需要在B启动server:
	olfile -server
A启动client进行传输：
	olfile -src c:\foo.dat -dst c:\foodst.dat -ip 10.190.1.2 -y
-src 表示源文件的位置
-dst 表示目标文件的位置
-ip 表示远程主机的IP。
-y 表示如果远程主机上的目标文件位置原来有文件，则强制覆盖。

可以看出，可以让A当作Server，B当作Client，使用不同的命令行实现上面的文件传递：
A启动server:
	olfile -server
B启动client 进行文件传输，这时B的c:\foodst.dat是目标：
	olfile -dst c:\foodst.dat -src c:\foo.dat -ip 10.190.1.1 -y

[4.兼容性]
附带的Makefile文件表明，代码可以在Linux下正常编译。所以，可以运行在Linux下，实现Linux与Windows文件的互传。
可能的命令行会变成：
	olfile -dst /home/foodst.dat -src c:\foo.dat -ip 10.190.1.1 -y
	
[5. 局限和可能存在的问题]
1.程序不会对你所使用的系统产生致命影响，因为它仅仅是一个socket 实例。
2.server 在进行一次文件传输之后就退出，因为程序是单一线程的。
3.可以利用程序的打印输出看一下大概的传输速度（因为这时我当时在项目中写这个工具的原因）。
4.有任何问题，请发mail：rtc@eyou.com OICQ: 5325938。
