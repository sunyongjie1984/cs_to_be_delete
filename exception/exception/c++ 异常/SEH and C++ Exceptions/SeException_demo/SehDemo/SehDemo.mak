# Microsoft Developer Studio Generated NMAKE File, Based on SehDemo.dsp
!IF "$(CFG)" == ""
CFG=SehDemo - Win32 Debug UNICODE
!MESSAGE No configuration specified. Defaulting to SehDemo - Win32 Debug\
 UNICODE.
!ENDIF 

!IF "$(CFG)" != "SehDemo - Win32 Release" && "$(CFG)" !=\
 "SehDemo - Win32 Debug" && "$(CFG)" != "SehDemo - Win32 Debug UNICODE" &&\
 "$(CFG)" != "SehDemo - Win32 Release UNICODE"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SehDemo.mak" CFG="SehDemo - Win32 Debug UNICODE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SehDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SehDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SehDemo - Win32 Debug UNICODE" (based on "Win32 (x86) Application")
!MESSAGE "SehDemo - Win32 Release UNICODE" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "SehDemo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SehDemo.exe"

!ELSE 

ALL : "$(OUTDIR)\SehDemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\SehDemo.obj"
	-@erase "$(INTDIR)\SehDemo.pch"
	-@erase "$(INTDIR)\SehDemo.res"
	-@erase "$(INTDIR)\SehDemoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SehDemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\SehDemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x41b /fo"$(INTDIR)\SehDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SehDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\SehDemo.pdb" /machine:I386 /out:"$(OUTDIR)\SehDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\SehDemo.obj" \
	"$(INTDIR)\SehDemo.res" \
	"$(INTDIR)\SehDemoDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SehDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SehDemo.exe"

!ELSE 

ALL : "$(OUTDIR)\SehDemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\SehDemo.obj"
	-@erase "$(INTDIR)\SehDemo.pch"
	-@erase "$(INTDIR)\SehDemo.res"
	-@erase "$(INTDIR)\SehDemoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SehDemo.exe"
	-@erase "$(OUTDIR)\SehDemo.ilk"
	-@erase "$(OUTDIR)\SehDemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\SehDemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x41b /fo"$(INTDIR)\SehDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SehDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\SehDemo.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SehDemo.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\SehDemo.obj" \
	"$(INTDIR)\SehDemo.res" \
	"$(INTDIR)\SehDemoDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SehDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug UNICODE"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SehDemo.exe"

!ELSE 

ALL : "$(OUTDIR)\SehDemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\SehDemo.obj"
	-@erase "$(INTDIR)\SehDemo.pch"
	-@erase "$(INTDIR)\SehDemo.res"
	-@erase "$(INTDIR)\SehDemoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SehDemo.exe"
	-@erase "$(OUTDIR)\SehDemo.ilk"
	-@erase "$(OUTDIR)\SehDemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\SehDemo.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x41b /fo"$(INTDIR)\SehDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SehDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\SehDemo.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\SehDemo.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\SehDemo.obj" \
	"$(INTDIR)\SehDemo.res" \
	"$(INTDIR)\SehDemoDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SehDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SehDemo - Win32 Release UNICODE"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SehDemo.exe"

!ELSE 

ALL : "$(OUTDIR)\SehDemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\SehDemo.obj"
	-@erase "$(INTDIR)\SehDemo.pch"
	-@erase "$(INTDIR)\SehDemo.res"
	-@erase "$(INTDIR)\SehDemoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SehDemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /GX /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\SehDemo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x41b /fo"$(INTDIR)\SehDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SehDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\SehDemo.pdb" /machine:I386\
 /out:"$(OUTDIR)\SehDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\SehDemo.obj" \
	"$(INTDIR)\SehDemo.res" \
	"$(INTDIR)\SehDemoDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SehDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "SehDemo - Win32 Release" || "$(CFG)" ==\
 "SehDemo - Win32 Debug" || "$(CFG)" == "SehDemo - Win32 Debug UNICODE" ||\
 "$(CFG)" == "SehDemo - Win32 Release UNICODE"
SOURCE=.\SeException.cpp
DEP_CPP_SEEXC=\
	".\SEException.h"\
	

"$(INTDIR)\SeException.obj" : $(SOURCE) $(DEP_CPP_SEEXC) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


SOURCE=.\SehDemo.cpp

!IF  "$(CFG)" == "SehDemo - Win32 Release"

DEP_CPP_SEHDE=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemo.obj" : $(SOURCE) $(DEP_CPP_SEHDE) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug"

DEP_CPP_SEHDE=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemo.obj" : $(SOURCE) $(DEP_CPP_SEHDE) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug UNICODE"

DEP_CPP_SEHDE=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemo.obj" : $(SOURCE) $(DEP_CPP_SEHDE) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Release UNICODE"

DEP_CPP_SEHDE=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemo.obj" : $(SOURCE) $(DEP_CPP_SEHDE) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ENDIF 

SOURCE=.\SehDemo.rc
DEP_RSC_SEHDEM=\
	".\res\SehDemo.ico"\
	".\res\SehDemo.rc2"\
	

"$(INTDIR)\SehDemo.res" : $(SOURCE) $(DEP_RSC_SEHDEM) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SehDemoDlg.cpp

!IF  "$(CFG)" == "SehDemo - Win32 Release"

DEP_CPP_SEHDEMO=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemoDlg.obj" : $(SOURCE) $(DEP_CPP_SEHDEMO) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug"

DEP_CPP_SEHDEMO=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemoDlg.obj" : $(SOURCE) $(DEP_CPP_SEHDEMO) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug UNICODE"

DEP_CPP_SEHDEMO=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemoDlg.obj" : $(SOURCE) $(DEP_CPP_SEHDEMO) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Release UNICODE"

DEP_CPP_SEHDEMO=\
	".\SEException.h"\
	".\SehDemo.h"\
	".\SehDemoDlg.h"\
	

"$(INTDIR)\SehDemoDlg.obj" : $(SOURCE) $(DEP_CPP_SEHDEMO) "$(INTDIR)"\
 "$(INTDIR)\SehDemo.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SehDemo - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\mssdk\include\basetsd.h"\
	"d:\mssdk\include\guiddef.h"\
	"d:\mssdk\include\tvout.h"\
	
CPP_SWITCHES=/nologo /MD /W4 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\SehDemo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SehDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\mssdk\include\basetsd.h"\
	"d:\mssdk\include\guiddef.h"\
	"d:\mssdk\include\tvout.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\SehDemo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SehDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Debug UNICODE"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\mssdk\include\basetsd.h"\
	"d:\mssdk\include\guiddef.h"\
	"d:\mssdk\include\tvout.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\SehDemo.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SehDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SehDemo - Win32 Release UNICODE"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	"d:\mssdk\include\basetsd.h"\
	"d:\mssdk\include\guiddef.h"\
	"d:\mssdk\include\tvout.h"\
	
CPP_SWITCHES=/nologo /MD /W4 /GX /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\SehDemo.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SehDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

