REM BUILD A WhoSLocking KIT

@ECHO Building WhoSLocking Self-Installing Kit

MKDIR Kit
DEL WhoSLockingKit.zip
DEL /Q Kit\*.*

COPY Empty.zip WhoSLockingKit.zip
IF ERRORLEVEL 1 GOTO ERROROCCURED
ATTRIB -R WhoSLockingKit.zip
IF ERRORLEVEL 1 GOTO ERROROCCURED
COPY %1 Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
COPY Readme.txt Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
COPY Readme.htm Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
COPY WhoSLocking1.jpg Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
COPY WhoSLocking2.jpg Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
COPY SimpleProcessAPI.h Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
REM Ship DLLs version > 4 (non-standard)
COPY %SYSTEMROOT%\SYSTEM32\MFC42.DLL Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
COPY %SYSTEMROOT%\SYSTEM32\MSVCRT.DLL Kit\
IF ERRORLEVEL 1 GOTO ERROROCCURED
REM COPY %SYSTEMROOT%\SYSTEM32\COMCTL32.DLL Kit\
REM IF ERRORLEVEL 1 GOTO ERROROCCURED

@ECHO Browse to Path E:\Emmanuel\DVP\Tools\WhoSLocking\Kit
@ECHO Add all files in archive (.zip)
@ECHO When converting to self-extracting archive (.exe), specify the following options:
@ECHO Default extraction folder:
@ECHO      "C:\Program Files\WhoSLocking"
@ECHO Execute following command after extraction: 
@ECHO      "WhoSLocking.exe"

CD Kit
"D:\Program Files\ZipCentral\ZCENTRAL.EXE" ..\WhoSLockingKit.zip
CD ..

COPY WhoSLockingKit.exe WhoSLockingFullKit.exe
IF ERRORLEVEL 1 GOTO ERROROCCURED
@ECHO DO NOT FORGET: 
@ECHO                 REMOVE DLLs from WhoSLockingKit.zip (they're in the Full Kit)
"D:\Program Files\ZipCentral\ZCENTRAL.EXE" WhoSLockingKit.exe

IF ERRORLEVEL 1 GOTO ERROROCCURED
REM Cleanup the kit directory
DEL /Q Kit\*.*

:END
EXIT 0

:ERROROCCURED
EXIT 1
