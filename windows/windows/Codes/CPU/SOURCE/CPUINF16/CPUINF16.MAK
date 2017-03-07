# Microsoft Visual C++ generated build script - Do not modify

PROJ = CPUINF16
DEBUG = 0
PROGTYPE = 1
CALLER = tstdll16.exe
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\CPUINF16\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = CPUID.C     
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /G3 /W3 /Zi /ALw /Od /D "_DEBUG" /FR /GD /Fd"CPUSPD16.PDB"
CFLAGS_R_WDLL = /nologo /G3 /W3 /AHw /O1 /D "NDEBUG" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /LINE /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = lafxdwd oldnames libw ldllcew commdlg.lib mmsystem.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = lafxdw oldnames libw ldllcew commdlg.lib mmsystem.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = CPUINF16.DEF
OBJS_EXT = TIMEPROC.OBJ 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = CPUID.SBR \
		SPEED.SBR


TIMEPROC_DEP = 

CPUID_DEP = c:\cpuinf16\cpuid.h \
	c:\cpuinf16\speed.h


SPEED_DEP = c:\cpuinf16\speed.h \
	c:\cpuinf16\cpuid.h


all:	$(PROJ).DLL

CPUID.OBJ:	CPUID.C $(CPUID_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c CPUID.C

SPEED.OBJ:	SPEED.C $(SPEED_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c SPEED.C


$(PROJ).DLL::	CPUID.OBJ SPEED.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
CPUID.OBJ +
SPEED.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@
	implib /nowep $(PROJ).LIB $(PROJ).DLL


run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
