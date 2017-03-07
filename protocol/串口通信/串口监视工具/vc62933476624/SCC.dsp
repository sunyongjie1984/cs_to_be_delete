# Microsoft Developer Studio Project File - Name="SCC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SCC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SCC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SCC.mak" CFG="SCC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SCC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SCC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SCC - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SCC - Win32 Debug"

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

# Name "SCC - Win32 Release"
# Name "SCC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CheckSum.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\CoolMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectoryDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAutoSave.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSend.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiButtonTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiCapOutBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuicheckBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiComboBoxExt.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiComboFont.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiDocBarExten.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiDockContext.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiDockToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiDocSpecial.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiDrawLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiDropDownEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiFDir.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiFolderFlat.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiGroupBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiImageLinkButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiLabelButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiLinkButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiListEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiMDIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiMDITabbed.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiMiniFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiMiniFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiMiniSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiMiniTool.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiNormalButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiOfficeBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiOutLook.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiOutLookView.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiPanelAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiPowerPointView.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiSplitterWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiStaticStandar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiSysTray.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiTabbed.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiTabPowerPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiTabWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiToolBarWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiToolButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiView.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiViewWorkTab.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiVisioFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiWorkPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\GuiWorkTab.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\NewMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\SCC.cpp
# End Source File
# Begin Source File

SOURCE=.\SCC.rc
# End Source File
# Begin Source File

SOURCE=.\SCCSendEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SCCView.cpp
# End Source File
# Begin Source File

SOURCE=.\SendFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SerialPort.cpp
# End Source File
# Begin Source File

SOURCE=.\StatLink.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\GUILIB\SRC\Subclass.cpp
# End Source File
# Begin Source File

SOURCE=.\Transmit.cpp
# End Source File
# Begin Source File

SOURCE=.\XRichEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\XRichEditView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\GUILIB\HEADER\CBaseTab.h
# End Source File
# Begin Source File

SOURCE=.\CheckSum.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\CoolMenu.h
# End Source File
# Begin Source File

SOURCE=.\DirectoryDialog.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoSave.h
# End Source File
# Begin Source File

SOURCE=.\DlgFilter.h
# End Source File
# Begin Source File

SOURCE=.\DlgSend.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiBaseTab.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiButton.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiButtonTimer.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiCapOutBar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuicheckBox.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiColors.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiComboBoxExt.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiComboFont.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiContainer.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiControlBar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiDocBarExten.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiDockBar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiDockContext.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiDockToolBar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiDocSpecial.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiDrawLayer.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiDropDownEdit.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiEdit.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiFDir.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiFile.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiFolder.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiFolderFlat.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiGroupBox.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiImageLinkButton.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiLabelButton.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiLib.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiLinkButton.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiListEdit.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiMDIFrame.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiMDITabbed.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiMiniFrame.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiMiniFrameWnd.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiMiniSplitter.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiMiniTool.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiNormalButton.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiOfficeBar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiOutLook.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiOutLookView.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiPanelAccess.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiPowerPointView.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiRadioButton.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiSplitter.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiSplitterWnd.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiStaticStandar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiStatusBar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiSysTray.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiTabbed.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiTabPowerPoint.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiTabWnd.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiToolBarWnd.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiToolButton.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiView.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiViewWorkTab.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiVisioFolder.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiWorkPanel.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\GuiWorkTab.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\MenuBar.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\NewMenu.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SCC.h
# End Source File
# Begin Source File

SOURCE=.\SCCSendEdit.h
# End Source File
# Begin Source File

SOURCE=.\SCCView.h
# End Source File
# Begin Source File

SOURCE=.\SendFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\SerialPort.h
# End Source File
# Begin Source File

SOURCE=.\StatLink.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\GUILIB\HEADER\Subclass.h
# End Source File
# Begin Source File

SOURCE=.\Transmit.h
# End Source File
# Begin Source File

SOURCE=.\XRichEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\XRichEditView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DockOffice.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_scct.ico
# End Source File
# Begin Source File

SOURCE=.\res\save.ico
# End Source File
# Begin Source File

SOURCE=.\res\SCC.ico
# End Source File
# Begin Source File

SOURCE=.\res\SCC.rc2
# End Source File
# Begin Source File

SOURCE=.\res\scc_tool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCCDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
