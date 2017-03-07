# Microsoft Developer Studio Generated NMAKE File, Based on kp.dsp
!IF "$(CFG)" == ""
CFG=kp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to kp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "kp - Win32 Release" && "$(CFG)" != "kp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "kp.mak" CFG="kp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "kp - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "kp - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "kp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\kp.exe"


CLEAN :
	-@erase "$(INTDIR)\EnumProc.obj"
	-@erase "$(INTDIR)\kp.obj"
	-@erase "$(INTDIR)\kp.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\kp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\kp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=psapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\kp.pdb" /machine:I386 /out:"$(OUTDIR)\kp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\EnumProc.obj" \
	"$(INTDIR)\kp.obj" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\kp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "kp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\kp.exe"


CLEAN :
	-@erase "$(INTDIR)\EnumProc.obj"
	-@erase "$(INTDIR)\kp.obj"
	-@erase "$(INTDIR)\kp.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\kp.exe"
	-@erase "$(OUTDIR)\kp.ilk"
	-@erase "$(OUTDIR)\kp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\kp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=psapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\kp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\kp.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\EnumProc.obj" \
	"$(INTDIR)\kp.obj" \
	"$(INTDIR)\stdafx.obj"

"$(OUTDIR)\kp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("kp.dep")
!INCLUDE "kp.dep"
!ELSE 
!MESSAGE Warning: cannot find "kp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "kp - Win32 Release" || "$(CFG)" == "kp - Win32 Debug"
SOURCE=.\EnumProc.cpp

!IF  "$(CFG)" == "kp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\kp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\EnumProc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\kp.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "kp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\kp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\EnumProc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\kp.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\kp.cpp

!IF  "$(CFG)" == "kp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\kp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\kp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\kp.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "kp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\kp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\kp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\kp.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "kp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\kp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\kp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "kp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_kp" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\kp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\kp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

