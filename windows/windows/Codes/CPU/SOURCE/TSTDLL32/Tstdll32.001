# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Tstdll32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tstdll32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Tstdll32 - Win32 Release" && "$(CFG)" !=\
 "Tstdll32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tstdll32.mak" CFG="Tstdll32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tstdll32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tstdll32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Tstdll32 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Tstdll32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Tstdll32.exe"

CLEAN : 
	-@erase "$(INTDIR)\Tstdll32.obj"
	-@erase "$(INTDIR)\Tstdll32.res"
	-@erase "$(OUTDIR)\Tstdll32.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Z<none> /O<none>
CPP_PROJ=/nologo /ML /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Tstdll32.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Tstdll32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tstdll32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib libc.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib advapi32.lib libc.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Tstdll32.pdb" /machine:I386\
 /nodefaultlib /def:".\Tstdll32.def" /out:"$(OUTDIR)/Tstdll32.exe" 
DEF_FILE= \
	".\Tstdll32.def"
LINK32_OBJS= \
	"$(INTDIR)\Tstdll32.obj" \
	"$(INTDIR)\Tstdll32.res"

"$(OUTDIR)\Tstdll32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tstdll32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Tstdll32"
# PROP BASE Intermediate_Dir "Tstdll32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Tstdll32.exe"

CLEAN : 
	-@erase "$(INTDIR)\Tstdll32.obj"
	-@erase "$(INTDIR)\Tstdll32.res"
	-@erase "$(OUTDIR)\Tstdll32.exe"
	-@erase "$(OUTDIR)\Tstdll32.ilk"
	-@erase "$(OUTDIR)\Tstdll32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /ML /W3 /GX /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Z<none> /O<none>
CPP_PROJ=/nologo /ML /W3 /GX /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Tstdll32.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Tstdll32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tstdll32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib libc.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib advapi32.lib libc.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Tstdll32.pdb" /debug\
 /machine:I386 /nodefaultlib /def:".\Tstdll32.def" /out:"$(OUTDIR)/Tstdll32.exe"\
 
DEF_FILE= \
	".\Tstdll32.def"
LINK32_OBJS= \
	"$(INTDIR)\Tstdll32.obj" \
	"$(INTDIR)\Tstdll32.res"

"$(OUTDIR)\Tstdll32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Tstdll32 - Win32 Release"
# Name "Tstdll32 - Win32 Debug"

!IF  "$(CFG)" == "Tstdll32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Tstdll32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Tstdll32.c
DEP_CPP_TSTDL=\
	".\tstdll32.h"\
	

"$(INTDIR)\Tstdll32.obj" : $(SOURCE) $(DEP_CPP_TSTDL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tstdll32.rc
DEP_RSC_TSTDLL=\
	".\tstdll32.ico"\
	

"$(INTDIR)\Tstdll32.res" : $(SOURCE) $(DEP_RSC_TSTDLL) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tstdll32.def

!IF  "$(CFG)" == "Tstdll32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Tstdll32 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
