# Microsoft Developer Studio Project File - Name="snort" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=snort - Win32 Flexresp Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "snort.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "snort.mak" CFG="snort - Win32 Flexresp Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "snort - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 MySQL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 Flexresp Release" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 Flexresp Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 MySQL Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "snort - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /machine:I386 /libpath:"..\Win32-Libraries"

!ELSEIF  "$(CFG)" == "snort - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmt.lib" /pdbtype:sept /libpath:"..\Win32-Libraries"

!ELSEIF  "$(CFG)" == "snort - Win32 MySQL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "snort___Win32_MySQL_Debug"
# PROP BASE Intermediate_Dir "snort___Win32_MySQL_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "snort___Win32_MySQL_Debug"
# PROP Intermediate_Dir "snort___Win32_MySQL_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\Win32-Includes\mysql" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_MYSQL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmt.lib" /pdbtype:sept /libpath:"..\Win32-Libraries"
# ADD LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib mysqlclient.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\mysql"

!ELSEIF  "$(CFG)" == "snort - Win32 Flexresp Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "snort___Win32_Flexresp_Release"
# PROP BASE Intermediate_Dir "snort___Win32_Flexresp_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "snort___Win32_Flexresp_Release"
# PROP Intermediate_Dir "snort___Win32_Flexresp_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\Win32-Includes" /I "..\\" /I "..\Win32-Includes\libnet" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_RESPONSE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libcmt.lib" /libpath:"..\Win32-Libraries"
# ADD LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib libnetnt.lib /nologo /subsystem:console /machine:I386 /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\libnet"

!ELSEIF  "$(CFG)" == "snort - Win32 Flexresp Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "snort___Win32_Flexresp_Debug"
# PROP BASE Intermediate_Dir "snort___Win32_Flexresp_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "snort___Win32_Flexresp_Debug"
# PROP Intermediate_Dir "snort___Win32_Flexresp_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\\" /I "..\Win32-Includes\libnet" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_RESPONSE" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmt.lib" /pdbtype:sept /libpath:"..\Win32-Libraries"
# ADD LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib libnetnt.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmt.lib" /pdbtype:sept /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\libnet"

!ELSEIF  "$(CFG)" == "snort - Win32 MySQL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "snort___Win32_MySQL_Release"
# PROP BASE Intermediate_Dir "snort___Win32_MySQL_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "snort___Win32_MySQL_Release"
# PROP Intermediate_Dir "snort___Win32_MySQL_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\Win32-Includes" /I "..\Win32-Includes\mysql" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_MYSQL" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libcmt.lib" /libpath:"..\Win32-Libraries"
# ADD LINK32 user32.lib wsock32.lib libpcap.lib advapi32.lib mysqlclient.lib /nologo /subsystem:console /machine:I386 /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\mysql"

!ENDIF 

# Begin Target

# Name "snort - Win32 Release"
# Name "snort - Win32 Debug"
# Name "snort - Win32 MySQL Debug"
# Name "snort - Win32 Flexresp Release"
# Name "snort - Win32 Flexresp Debug"
# Name "snort - Win32 MySQL Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\checksum.c
# End Source File
# Begin Source File

SOURCE=..\decode.c
# End Source File
# Begin Source File

SOURCE="..\WIN32-Code\getopt.c"
# End Source File
# Begin Source File

SOURCE=..\log.c
# End Source File
# Begin Source File

SOURCE="..\WIN32-Code\misc.c"
# End Source File
# Begin Source File

SOURCE=..\mstring.c
# End Source File
# Begin Source File

SOURCE=..\parser.c
# End Source File
# Begin Source File

SOURCE=..\plugbase.c
# End Source File
# Begin Source File

SOURCE=..\rules.c
# End Source File
# Begin Source File

SOURCE=..\snort.c
# End Source File
# Begin Source File

SOURCE=..\sp_dsize_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_code_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_id_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_seq_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_type_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_ip_fragbits.c
# End Source File
# Begin Source File

SOURCE=..\sp_ip_id_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_ip_tos_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_ipoption_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_pattern_match.c
# End Source File
# Begin Source File

SOURCE=..\sp_react.c
# End Source File
# Begin Source File

SOURCE=..\sp_reference.c
# End Source File
# Begin Source File

SOURCE=..\sp_respond.c
# End Source File
# Begin Source File

SOURCE=..\sp_rpc_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_session.c
# End Source File
# Begin Source File

SOURCE=..\sp_tcp_ack_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_tcp_flag_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_tcp_seq_check.c
# End Source File
# Begin Source File

SOURCE=..\sp_ttl_check.c
# End Source File
# Begin Source File

SOURCE=..\spo_alert_fast.c
# End Source File
# Begin Source File

SOURCE=..\spo_alert_full.c
# End Source File
# Begin Source File

SOURCE=..\spo_alert_smb.c
# End Source File
# Begin Source File

SOURCE=..\spo_alert_syslog.c
# End Source File
# Begin Source File

SOURCE=..\spo_alert_unixsock.c
# End Source File
# Begin Source File

SOURCE=..\spo_database.c
# End Source File
# Begin Source File

SOURCE=..\spo_log_tcpdump.c
# End Source File
# Begin Source File

SOURCE=..\spo_xml.c
# End Source File
# Begin Source File

SOURCE=..\spp_anomsensor.c
# End Source File
# Begin Source File

SOURCE=..\spp_defrag.c
# End Source File
# Begin Source File

SOURCE=..\spp_http_decode.c
# End Source File
# Begin Source File

SOURCE=..\spp_minfrag.c
# End Source File
# Begin Source File

SOURCE=..\spp_portscan.c
# End Source File
# Begin Source File

SOURCE=..\spp_tcp_stream.c
# End Source File
# Begin Source File

SOURCE="..\WIN32-Code\syslog.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\acconfig.h
# End Source File
# Begin Source File

SOURCE=..\cdefs.h
# End Source File
# Begin Source File

SOURCE=..\checksum.h
# End Source File
# Begin Source File

SOURCE=..\config.h
# End Source File
# Begin Source File

SOURCE=..\decode.h
# End Source File
# Begin Source File

SOURCE="..\WIN32-Includes\getopt.h"
# End Source File
# Begin Source File

SOURCE=..\log.h
# End Source File
# Begin Source File

SOURCE=..\mstring.h
# End Source File
# Begin Source File

SOURCE="..\WIN32-Code\name.h"
# End Source File
# Begin Source File

SOURCE=..\parser.h
# End Source File
# Begin Source File

SOURCE=..\plugbase.h
# End Source File
# Begin Source File

SOURCE=..\prototypes.h
# End Source File
# Begin Source File

SOURCE=..\rules.h
# End Source File
# Begin Source File

SOURCE=..\snort.h
# End Source File
# Begin Source File

SOURCE=..\snprintf.h
# End Source File
# Begin Source File

SOURCE=..\sp_dsize_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_code_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_id_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_seq_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_icmp_type_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_ip_fragbits.h
# End Source File
# Begin Source File

SOURCE=..\sp_ip_id_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_ip_tos_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_ipoption_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_pattern_match.h
# End Source File
# Begin Source File

SOURCE=..\sp_react.h
# End Source File
# Begin Source File

SOURCE=..\sp_reference.h
# End Source File
# Begin Source File

SOURCE=..\sp_respond.h
# End Source File
# Begin Source File

SOURCE=..\sp_rpc_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_session.h
# End Source File
# Begin Source File

SOURCE=..\sp_tcp_ack_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_tcp_flag_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_tcp_seq_check.h
# End Source File
# Begin Source File

SOURCE=..\sp_ttl_check.h
# End Source File
# Begin Source File

SOURCE=..\spo_alert_fast.h
# End Source File
# Begin Source File

SOURCE=..\spo_alert_full.h
# End Source File
# Begin Source File

SOURCE=..\spo_alert_smb.h
# End Source File
# Begin Source File

SOURCE=..\spo_alert_syslog.h
# End Source File
# Begin Source File

SOURCE=..\spo_alert_unixsock.h
# End Source File
# Begin Source File

SOURCE=..\spo_database.h
# End Source File
# Begin Source File

SOURCE=..\spo_log_tcpdump.h
# End Source File
# Begin Source File

SOURCE=..\spo_xml.h
# End Source File
# Begin Source File

SOURCE=..\spp_anomsensor.h
# End Source File
# Begin Source File

SOURCE=..\spp_defrag.h
# End Source File
# Begin Source File

SOURCE=..\spp_http_decode.h
# End Source File
# Begin Source File

SOURCE=..\spp_minfrag.h
# End Source File
# Begin Source File

SOURCE=..\spp_portscan.h
# End Source File
# Begin Source File

SOURCE=..\spp_tcp_stream.h
# End Source File
# Begin Source File

SOURCE="..\WIN32-Includes\syslog.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE="..\WIN32-Code\name.rc"
# End Source File
# End Group
# End Target
# End Project
