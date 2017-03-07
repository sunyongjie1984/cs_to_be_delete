REM Cleanup VC++ Project and enzip it

DEL /Q Release\*.*
DEL /Q Debug\*.*
DEL /Q WhoSLocking.aps
DEL /Q WhoSLocking.clw
DEL /Q WhoSLocking.ncb
DEL /Q WhoSLocking.opt
DEL /Q WhoSLocking.plg
COPY WhoSLockingKit.exe ..\
DEL /Q WhoSLockingKit.exe
COPY WhoSLockingFullKit.exe ..\
DEL /Q WhoSLockingFullKit.exe
DEL /Q ..\WhoSLocking_src.zip

CD ..
"D:\Program Files\ZipCentral\ZCENTRAL.EXE" WhoSLocking_src.zip
CD WhoSLocking
