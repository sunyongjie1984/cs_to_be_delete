# Microsoft Visual C++ generated build script - Do not modify

PROJ = TSTDLL16
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\TSTDLL16\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = TSTDLL16.C  
FIRSTCPP =             
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"TESTDLL.PDB"
CFLAGS_R_WEXE = /nologo /G3 /W3 /AM /O1 /Ob1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /LINE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg.lib mmsystem.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = mafxcw libw mlibcew oldnames commdlg.lib mmsystem.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = TSTDLL16.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = TSTDLL16.SBR


TSTDLL16_DEP = c:\tstdll16\tstdll16.h


TSTDLL16_RCDEP = c:\tstdll16\tstdll16.ico


all:	$(PROJ).EXE $(PROJ).BSC

TSTDLL16.OBJ:	TSTDLL16.C $(TSTDLL16_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c TSTDLL16.C

TSTDLL16.RES:	TSTDLL16.RC $(TSTDLL16_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r TSTDLL16.RC


$(PROJ).EXE::	TSTDLL16.RES

$(PROJ).EXE::	TSTDLL16.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
TSTDLL16.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) TSTDLL16.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	TSTDLL16.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) TSTDLL16.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
