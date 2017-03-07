# Microsoft Developer Studio Project File - Name="CockFight" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CockFight - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CockFight.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CockFight.mak" CFG="CockFight - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CockFight - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CockFight - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CockFight - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CockFight - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CockFight - Win32 Release"
# Name "CockFight - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CockFight.cpp
# End Source File
# Begin Source File

SOURCE=.\CockFight.rc
# End Source File
# Begin Source File

SOURCE=.\CockFightDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ListenSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\SelCSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\CockFight.h
# End Source File
# Begin Source File

SOURCE=.\CockFightDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListenSocket.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SelCSDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CARDS\CARD_TURN.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\CARDS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CockFight.ico
# End Source File
# Begin Source File

SOURCE=.\res\CockFight.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\f9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\f9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\fj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\fk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\fq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\h9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\h9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\hj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\hk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\hq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\m9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\m9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\mj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\mk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\mq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\t9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\tj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tj.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\tk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CARDS\tq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tq.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
