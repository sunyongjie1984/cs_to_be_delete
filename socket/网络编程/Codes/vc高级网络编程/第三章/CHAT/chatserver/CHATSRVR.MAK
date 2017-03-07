# Microsoft Developer Studio Generated NMAKE File, Based on chatsrvr.dsp
!IF "$(CFG)" == ""
CFG=ChatSrvr - Win32 Release
!MESSAGE No configuration specified.  Defaulting to ChatSrvr - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ChatSrvr - Win32 Release" && "$(CFG)" !=\
 "ChatSrvr - Win32 Debug" && "$(CFG)" != "ChatSrvr - Win32 Unicode Release" &&\
 "$(CFG)" != "ChatSrvr - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "chatsrvr.mak" CFG="ChatSrvr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ChatSrvr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ChatSrvr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ChatSrvr - Win32 Unicode Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "ChatSrvr - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\chatsrvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatsrvr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/chatsrvr.pdb" /machine:I386 /out:"$(OUTDIR)/chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Chatsrvr.res" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\chatsrvr.exe"
	-@erase "$(OUTDIR)\chatsrvr.ilk"
	-@erase "$(OUTDIR)\chatsrvr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatsrvr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/chatsrvr.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Chatsrvr.res" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"

OUTDIR=.\UniRelease
INTDIR=.\UniRelease
# Begin Custom Macros
OutDir=.\.\UniRelease
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\chatsrvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniRelease/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatsrvr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/chatsrvr.pdb" /machine:I386\
 /out:"$(OUTDIR)/chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Chatsrvr.res" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"

OUTDIR=.\UniDebug
INTDIR=.\UniDebug
# Begin Custom Macros
OutDir=.\.\UniDebug
# End Custom Macros

ALL : "$(OUTDIR)\chatsrvr.exe"

CLEAN : 
	-@erase "$(INTDIR)\Chatsrvr.obj"
	-@erase "$(INTDIR)\chatsrvr.pch"
	-@erase "$(INTDIR)\Chatsrvr.res"
	-@erase "$(INTDIR)\Clntsock.obj"
	-@erase "$(INTDIR)\Dialogs.obj"
	-@erase "$(INTDIR)\Lstnsock.obj"
	-@erase "$(INTDIR)\Mainfrm.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Srvrdoc.obj"
	-@erase "$(INTDIR)\Srvrvw.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\chatsrvr.exe"
	-@erase "$(OUTDIR)\chatsrvr.ilk"
	-@erase "$(OUTDIR)\chatsrvr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\UniDebug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Chatsrvr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/chatsrvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/chatsrvr.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/chatsrvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chatsrvr.obj" \
	"$(INTDIR)\Chatsrvr.res" \
	"$(INTDIR)\Clntsock.obj" \
	"$(INTDIR)\Dialogs.obj" \
	"$(INTDIR)\Lstnsock.obj" \
	"$(INTDIR)\Mainfrm.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Srvrdoc.obj" \
	"$(INTDIR)\Srvrvw.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\chatsrvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  


!IF "$(CFG)" == "ChatSrvr - Win32 Release" || "$(CFG)" ==\
 "ChatSrvr - Win32 Debug" || "$(CFG)" == "ChatSrvr - Win32 Unicode Release" ||\
 "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"
SOURCE=.\Chatsrvr.cpp
DEP_CPP_CHATS=\
	".\Chatsrvr.h"\
	".\Clntsock.h"\
	".\Lstnsock.h"\
	".\Mainfrm.h"\
	".\Srvrdoc.h"\
	".\Srvrvw.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Chatsrvr.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Chatsrvr.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Chatsrvr.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Chatsrvr.obj" : $(SOURCE) $(DEP_CPP_CHATS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Chatsrvr.rc
DEP_RSC_CHATSR=\
	".\Res\Chatsrvr.ico"\
	".\Res\Chatsrvr.rc2"\
	".\Res\Toolbar.bmp"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Chatsrvr.res" : $(SOURCE) $(DEP_RSC_CHATSR) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Chatsrvr.res" : $(SOURCE) $(DEP_RSC_CHATSR) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Chatsrvr.res" : $(SOURCE) $(DEP_RSC_CHATSR) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Chatsrvr.res" : $(SOURCE) $(DEP_RSC_CHATSR) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Clntsock.cpp
DEP_CPP_CLNTS=\
	".\Clntsock.h"\
	".\Lstnsock.h"\
	".\Msg.h"\
	".\Srvrdoc.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Clntsock.obj" : $(SOURCE) $(DEP_CPP_CLNTS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Clntsock.obj" : $(SOURCE) $(DEP_CPP_CLNTS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Clntsock.obj" : $(SOURCE) $(DEP_CPP_CLNTS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Clntsock.obj" : $(SOURCE) $(DEP_CPP_CLNTS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Dialogs.cpp
DEP_CPP_DIALO=\
	".\Chatsrvr.h"\
	".\Dialogs.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Dialogs.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Dialogs.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Dialogs.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Dialogs.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Lstnsock.cpp
DEP_CPP_LSTNS=\
	".\Clntsock.h"\
	".\Lstnsock.h"\
	".\Srvrdoc.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Lstnsock.obj" : $(SOURCE) $(DEP_CPP_LSTNS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Lstnsock.obj" : $(SOURCE) $(DEP_CPP_LSTNS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Lstnsock.obj" : $(SOURCE) $(DEP_CPP_LSTNS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Lstnsock.obj" : $(SOURCE) $(DEP_CPP_LSTNS) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Mainfrm.cpp
DEP_CPP_MAINF=\
	".\Chatsrvr.h"\
	".\Mainfrm.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Msg.cpp
DEP_CPP_MSG_C=\
	".\Msg.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Srvrdoc.cpp
DEP_CPP_SRVRD=\
	".\Chatsrvr.h"\
	".\Clntsock.h"\
	".\Dialogs.h"\
	".\Lstnsock.h"\
	".\Msg.h"\
	".\Srvrdoc.h"\
	".\Srvrvw.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Srvrdoc.obj" : $(SOURCE) $(DEP_CPP_SRVRD) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Srvrdoc.obj" : $(SOURCE) $(DEP_CPP_SRVRD) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Srvrdoc.obj" : $(SOURCE) $(DEP_CPP_SRVRD) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Srvrdoc.obj" : $(SOURCE) $(DEP_CPP_SRVRD) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Srvrvw.cpp
DEP_CPP_SRVRV=\
	".\Chatsrvr.h"\
	".\Clntsock.h"\
	".\Lstnsock.h"\
	".\Srvrdoc.h"\
	".\Srvrvw.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Srvrvw.obj" : $(SOURCE) $(DEP_CPP_SRVRV) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Srvrvw.obj" : $(SOURCE) $(DEP_CPP_SRVRV) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Srvrvw.obj" : $(SOURCE) $(DEP_CPP_SRVRV) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Srvrvw.obj" : $(SOURCE) $(DEP_CPP_SRVRV) "$(INTDIR)"\
 "$(INTDIR)\chatsrvr.pch"


!ENDIF 

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "ChatSrvr - Win32 Release"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Debug"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yc"Stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Release"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yc\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ChatSrvr - Win32 Unicode Debug"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\chatsrvr.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/chatsrvr.pch" /Yc"Stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\Chatsrvr.h
SOURCE=.\Clntsock.h
SOURCE=.\Dialogs.h
SOURCE=.\Lstnsock.h
SOURCE=.\Mainfrm.h
SOURCE=.\Msg.h
SOURCE=.\Resource.h
SOURCE=.\Srvrdoc.h
SOURCE=.\Srvrvw.h
SOURCE=.\Stdafx.h
SOURCE=.\Res\Chatsrvr.ico
SOURCE=.\Res\Chatsrvr.rc2
SOURCE=.\Res\Toolbar.bmp

!ENDIF 

