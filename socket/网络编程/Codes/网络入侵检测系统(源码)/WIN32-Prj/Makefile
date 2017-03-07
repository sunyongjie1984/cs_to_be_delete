# Microsoft Developer Studio Generated NMAKE File, Based on snort.dsp
!IF "$(CFG)" != "snort - Win32 Release" && "$(CFG)" != "snort - Win32 Debug" && "$(CFG)" != "snort - Win32 MySQL Debug" && "$(CFG)" != "snort - Win32 Flexresp Release" && "$(CFG)" != "snort - Win32 Flexresp Debug" && "$(CFG)" != "snort - Win32 MySQL Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "snort.mak" CFG="snort - Win32 Flexresp Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "snort - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 MySQL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 MySQL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 Flexresp Release" (based on "Win32 (x86) Console Application")
!MESSAGE "snort - Win32 Flexresp Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "snort - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\snort.exe"


CLEAN :
	-@erase "$(INTDIR)\checksum.obj"
	-@erase "$(INTDIR)\decode.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\mstring.obj"
	-@erase "$(INTDIR)\name.res"
	-@erase "$(INTDIR)\parser.obj"
	-@erase "$(INTDIR)\plugbase.obj"
	-@erase "$(INTDIR)\rules.obj"
	-@erase "$(INTDIR)\snort.obj"
	-@erase "$(INTDIR)\sp_dsize_check.obj"
	-@erase "$(INTDIR)\sp_icmp_code_check.obj"
	-@erase "$(INTDIR)\sp_icmp_id_check.obj"
	-@erase "$(INTDIR)\sp_icmp_seq_check.obj"
	-@erase "$(INTDIR)\sp_icmp_type_check.obj"
	-@erase "$(INTDIR)\sp_ip_fragbits.obj"
	-@erase "$(INTDIR)\sp_ip_id_check.obj"
	-@erase "$(INTDIR)\sp_ip_tos_check.obj"
	-@erase "$(INTDIR)\sp_ipoption_check.obj"
	-@erase "$(INTDIR)\sp_pattern_match.obj"
	-@erase "$(INTDIR)\sp_react.obj"
	-@erase "$(INTDIR)\sp_reference.obj"
	-@erase "$(INTDIR)\sp_respond.obj"
	-@erase "$(INTDIR)\sp_rpc_check.obj"
	-@erase "$(INTDIR)\sp_session.obj"
	-@erase "$(INTDIR)\sp_tcp_ack_check.obj"
	-@erase "$(INTDIR)\sp_tcp_flag_check.obj"
	-@erase "$(INTDIR)\sp_tcp_seq_check.obj"
	-@erase "$(INTDIR)\sp_ttl_check.obj"
	-@erase "$(INTDIR)\spo_alert_fast.obj"
	-@erase "$(INTDIR)\spo_alert_full.obj"
	-@erase "$(INTDIR)\spo_alert_smb.obj"
	-@erase "$(INTDIR)\spo_alert_syslog.obj"
	-@erase "$(INTDIR)\spo_alert_unixsock.obj"
	-@erase "$(INTDIR)\spo_database.obj"
	-@erase "$(INTDIR)\spo_log_tcpdump.obj"
	-@erase "$(INTDIR)\spo_xml.obj"
	-@erase "$(INTDIR)\spp_anomsensor.obj"
	-@erase "$(INTDIR)\spp_defrag.obj"
	-@erase "$(INTDIR)\spp_http_decode.obj"
	-@erase "$(INTDIR)\spp_minfrag.obj"
	-@erase "$(INTDIR)\spp_portscan.obj"
	-@erase "$(INTDIR)\spp_tcp_stream.obj"
	-@erase "$(INTDIR)\syslog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\snort.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /Fp"$(INTDIR)\snort.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\name.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\snort.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\snort.pdb" /machine:I386 /out:"$(OUTDIR)\snort.exe" /libpath:"..\Win32-Libraries" 
LINK32_OBJS= \
	"$(INTDIR)\checksum.obj" \
	"$(INTDIR)\decode.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mstring.obj" \
	"$(INTDIR)\parser.obj" \
	"$(INTDIR)\plugbase.obj" \
	"$(INTDIR)\rules.obj" \
	"$(INTDIR)\snort.obj" \
	"$(INTDIR)\sp_dsize_check.obj" \
	"$(INTDIR)\sp_icmp_code_check.obj" \
	"$(INTDIR)\sp_icmp_id_check.obj" \
	"$(INTDIR)\sp_icmp_seq_check.obj" \
	"$(INTDIR)\sp_icmp_type_check.obj" \
	"$(INTDIR)\sp_ip_fragbits.obj" \
	"$(INTDIR)\sp_ip_id_check.obj" \
	"$(INTDIR)\sp_ip_tos_check.obj" \
	"$(INTDIR)\sp_ipoption_check.obj" \
	"$(INTDIR)\sp_pattern_match.obj" \
	"$(INTDIR)\sp_react.obj" \
	"$(INTDIR)\sp_reference.obj" \
	"$(INTDIR)\sp_respond.obj" \
	"$(INTDIR)\sp_rpc_check.obj" \
	"$(INTDIR)\sp_session.obj" \
	"$(INTDIR)\sp_tcp_ack_check.obj" \
	"$(INTDIR)\sp_tcp_flag_check.obj" \
	"$(INTDIR)\sp_tcp_seq_check.obj" \
	"$(INTDIR)\sp_ttl_check.obj" \
	"$(INTDIR)\spo_alert_fast.obj" \
	"$(INTDIR)\spo_alert_full.obj" \
	"$(INTDIR)\spo_alert_smb.obj" \
	"$(INTDIR)\spo_alert_syslog.obj" \
	"$(INTDIR)\spo_alert_unixsock.obj" \
	"$(INTDIR)\spo_database.obj" \
	"$(INTDIR)\spo_log_tcpdump.obj" \
	"$(INTDIR)\spo_xml.obj" \
	"$(INTDIR)\spp_anomsensor.obj" \
	"$(INTDIR)\spp_defrag.obj" \
	"$(INTDIR)\spp_http_decode.obj" \
	"$(INTDIR)\spp_minfrag.obj" \
	"$(INTDIR)\spp_portscan.obj" \
	"$(INTDIR)\spp_tcp_stream.obj" \
	"$(INTDIR)\syslog.obj" \
	"$(INTDIR)\name.res"

"$(OUTDIR)\snort.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "snort - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\snort.exe"


CLEAN :
	-@erase "$(INTDIR)\checksum.obj"
	-@erase "$(INTDIR)\decode.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\mstring.obj"
	-@erase "$(INTDIR)\name.res"
	-@erase "$(INTDIR)\parser.obj"
	-@erase "$(INTDIR)\plugbase.obj"
	-@erase "$(INTDIR)\rules.obj"
	-@erase "$(INTDIR)\snort.obj"
	-@erase "$(INTDIR)\sp_dsize_check.obj"
	-@erase "$(INTDIR)\sp_icmp_code_check.obj"
	-@erase "$(INTDIR)\sp_icmp_id_check.obj"
	-@erase "$(INTDIR)\sp_icmp_seq_check.obj"
	-@erase "$(INTDIR)\sp_icmp_type_check.obj"
	-@erase "$(INTDIR)\sp_ip_fragbits.obj"
	-@erase "$(INTDIR)\sp_ip_id_check.obj"
	-@erase "$(INTDIR)\sp_ip_tos_check.obj"
	-@erase "$(INTDIR)\sp_ipoption_check.obj"
	-@erase "$(INTDIR)\sp_pattern_match.obj"
	-@erase "$(INTDIR)\sp_react.obj"
	-@erase "$(INTDIR)\sp_reference.obj"
	-@erase "$(INTDIR)\sp_respond.obj"
	-@erase "$(INTDIR)\sp_rpc_check.obj"
	-@erase "$(INTDIR)\sp_session.obj"
	-@erase "$(INTDIR)\sp_tcp_ack_check.obj"
	-@erase "$(INTDIR)\sp_tcp_flag_check.obj"
	-@erase "$(INTDIR)\sp_tcp_seq_check.obj"
	-@erase "$(INTDIR)\sp_ttl_check.obj"
	-@erase "$(INTDIR)\spo_alert_fast.obj"
	-@erase "$(INTDIR)\spo_alert_full.obj"
	-@erase "$(INTDIR)\spo_alert_smb.obj"
	-@erase "$(INTDIR)\spo_alert_syslog.obj"
	-@erase "$(INTDIR)\spo_alert_unixsock.obj"
	-@erase "$(INTDIR)\spo_database.obj"
	-@erase "$(INTDIR)\spo_log_tcpdump.obj"
	-@erase "$(INTDIR)\spo_xml.obj"
	-@erase "$(INTDIR)\spp_anomsensor.obj"
	-@erase "$(INTDIR)\spp_defrag.obj"
	-@erase "$(INTDIR)\spp_http_decode.obj"
	-@erase "$(INTDIR)\spp_minfrag.obj"
	-@erase "$(INTDIR)\spp_portscan.obj"
	-@erase "$(INTDIR)\spp_tcp_stream.obj"
	-@erase "$(INTDIR)\syslog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\snort.exe"
	-@erase "$(OUTDIR)\snort.ilk"
	-@erase "$(OUTDIR)\snort.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /Fp"$(INTDIR)\snort.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\name.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\snort.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib wsock32.lib libpcap.lib advapi32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\snort.pdb" /debug /machine:I386 /nodefaultlib:"libcmt.lib" /out:"$(OUTDIR)\snort.exe" /pdbtype:sept /libpath:"..\Win32-Libraries" 
LINK32_OBJS= \
	"$(INTDIR)\checksum.obj" \
	"$(INTDIR)\decode.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mstring.obj" \
	"$(INTDIR)\parser.obj" \
	"$(INTDIR)\plugbase.obj" \
	"$(INTDIR)\rules.obj" \
	"$(INTDIR)\snort.obj" \
	"$(INTDIR)\sp_dsize_check.obj" \
	"$(INTDIR)\sp_icmp_code_check.obj" \
	"$(INTDIR)\sp_icmp_id_check.obj" \
	"$(INTDIR)\sp_icmp_seq_check.obj" \
	"$(INTDIR)\sp_icmp_type_check.obj" \
	"$(INTDIR)\sp_ip_fragbits.obj" \
	"$(INTDIR)\sp_ip_id_check.obj" \
	"$(INTDIR)\sp_ip_tos_check.obj" \
	"$(INTDIR)\sp_ipoption_check.obj" \
	"$(INTDIR)\sp_pattern_match.obj" \
	"$(INTDIR)\sp_react.obj" \
	"$(INTDIR)\sp_reference.obj" \
	"$(INTDIR)\sp_respond.obj" \
	"$(INTDIR)\sp_rpc_check.obj" \
	"$(INTDIR)\sp_session.obj" \
	"$(INTDIR)\sp_tcp_ack_check.obj" \
	"$(INTDIR)\sp_tcp_flag_check.obj" \
	"$(INTDIR)\sp_tcp_seq_check.obj" \
	"$(INTDIR)\sp_ttl_check.obj" \
	"$(INTDIR)\spo_alert_fast.obj" \
	"$(INTDIR)\spo_alert_full.obj" \
	"$(INTDIR)\spo_alert_smb.obj" \
	"$(INTDIR)\spo_alert_syslog.obj" \
	"$(INTDIR)\spo_alert_unixsock.obj" \
	"$(INTDIR)\spo_database.obj" \
	"$(INTDIR)\spo_log_tcpdump.obj" \
	"$(INTDIR)\spo_xml.obj" \
	"$(INTDIR)\spp_anomsensor.obj" \
	"$(INTDIR)\spp_defrag.obj" \
	"$(INTDIR)\spp_http_decode.obj" \
	"$(INTDIR)\spp_minfrag.obj" \
	"$(INTDIR)\spp_portscan.obj" \
	"$(INTDIR)\spp_tcp_stream.obj" \
	"$(INTDIR)\syslog.obj" \
	"$(INTDIR)\name.res"

"$(OUTDIR)\snort.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "snort - Win32 MySQL Debug"

OUTDIR=.\snort___Win32_MySQL_Debug
INTDIR=.\snort___Win32_MySQL_Debug
# Begin Custom Macros
OutDir=.\snort___Win32_MySQL_Debug
# End Custom Macros

ALL : "$(OUTDIR)\snort.exe"


CLEAN :
	-@erase "$(INTDIR)\checksum.obj"
	-@erase "$(INTDIR)\decode.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\mstring.obj"
	-@erase "$(INTDIR)\name.res"
	-@erase "$(INTDIR)\parser.obj"
	-@erase "$(INTDIR)\plugbase.obj"
	-@erase "$(INTDIR)\rules.obj"
	-@erase "$(INTDIR)\snort.obj"
	-@erase "$(INTDIR)\sp_dsize_check.obj"
	-@erase "$(INTDIR)\sp_icmp_code_check.obj"
	-@erase "$(INTDIR)\sp_icmp_id_check.obj"
	-@erase "$(INTDIR)\sp_icmp_seq_check.obj"
	-@erase "$(INTDIR)\sp_icmp_type_check.obj"
	-@erase "$(INTDIR)\sp_ip_fragbits.obj"
	-@erase "$(INTDIR)\sp_ip_id_check.obj"
	-@erase "$(INTDIR)\sp_ip_tos_check.obj"
	-@erase "$(INTDIR)\sp_ipoption_check.obj"
	-@erase "$(INTDIR)\sp_pattern_match.obj"
	-@erase "$(INTDIR)\sp_react.obj"
	-@erase "$(INTDIR)\sp_reference.obj"
	-@erase "$(INTDIR)\sp_respond.obj"
	-@erase "$(INTDIR)\sp_rpc_check.obj"
	-@erase "$(INTDIR)\sp_session.obj"
	-@erase "$(INTDIR)\sp_tcp_ack_check.obj"
	-@erase "$(INTDIR)\sp_tcp_flag_check.obj"
	-@erase "$(INTDIR)\sp_tcp_seq_check.obj"
	-@erase "$(INTDIR)\sp_ttl_check.obj"
	-@erase "$(INTDIR)\spo_alert_fast.obj"
	-@erase "$(INTDIR)\spo_alert_full.obj"
	-@erase "$(INTDIR)\spo_alert_smb.obj"
	-@erase "$(INTDIR)\spo_alert_syslog.obj"
	-@erase "$(INTDIR)\spo_alert_unixsock.obj"
	-@erase "$(INTDIR)\spo_database.obj"
	-@erase "$(INTDIR)\spo_log_tcpdump.obj"
	-@erase "$(INTDIR)\spo_xml.obj"
	-@erase "$(INTDIR)\spp_anomsensor.obj"
	-@erase "$(INTDIR)\spp_defrag.obj"
	-@erase "$(INTDIR)\spp_http_decode.obj"
	-@erase "$(INTDIR)\spp_minfrag.obj"
	-@erase "$(INTDIR)\spp_portscan.obj"
	-@erase "$(INTDIR)\spp_tcp_stream.obj"
	-@erase "$(INTDIR)\syslog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\snort.exe"
	-@erase "$(OUTDIR)\snort.ilk"
	-@erase "$(OUTDIR)\snort.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\Win32-Includes\mysql" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_MYSQL" /Fp"$(INTDIR)\snort.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\name.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\snort.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib wsock32.lib libpcap.lib advapi32.lib mysqlclient.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\snort.pdb" /debug /machine:I386 /out:"$(OUTDIR)\snort.exe" /pdbtype:sept /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\mysql" 
LINK32_OBJS= \
	"$(INTDIR)\checksum.obj" \
	"$(INTDIR)\decode.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mstring.obj" \
	"$(INTDIR)\parser.obj" \
	"$(INTDIR)\plugbase.obj" \
	"$(INTDIR)\rules.obj" \
	"$(INTDIR)\snort.obj" \
	"$(INTDIR)\sp_dsize_check.obj" \
	"$(INTDIR)\sp_icmp_code_check.obj" \
	"$(INTDIR)\sp_icmp_id_check.obj" \
	"$(INTDIR)\sp_icmp_seq_check.obj" \
	"$(INTDIR)\sp_icmp_type_check.obj" \
	"$(INTDIR)\sp_ip_fragbits.obj" \
	"$(INTDIR)\sp_ip_id_check.obj" \
	"$(INTDIR)\sp_ip_tos_check.obj" \
	"$(INTDIR)\sp_ipoption_check.obj" \
	"$(INTDIR)\sp_pattern_match.obj" \
	"$(INTDIR)\sp_react.obj" \
	"$(INTDIR)\sp_reference.obj" \
	"$(INTDIR)\sp_respond.obj" \
	"$(INTDIR)\sp_rpc_check.obj" \
	"$(INTDIR)\sp_session.obj" \
	"$(INTDIR)\sp_tcp_ack_check.obj" \
	"$(INTDIR)\sp_tcp_flag_check.obj" \
	"$(INTDIR)\sp_tcp_seq_check.obj" \
	"$(INTDIR)\sp_ttl_check.obj" \
	"$(INTDIR)\spo_alert_fast.obj" \
	"$(INTDIR)\spo_alert_full.obj" \
	"$(INTDIR)\spo_alert_smb.obj" \
	"$(INTDIR)\spo_alert_syslog.obj" \
	"$(INTDIR)\spo_alert_unixsock.obj" \
	"$(INTDIR)\spo_database.obj" \
	"$(INTDIR)\spo_log_tcpdump.obj" \
	"$(INTDIR)\spo_xml.obj" \
	"$(INTDIR)\spp_anomsensor.obj" \
	"$(INTDIR)\spp_defrag.obj" \
	"$(INTDIR)\spp_http_decode.obj" \
	"$(INTDIR)\spp_minfrag.obj" \
	"$(INTDIR)\spp_portscan.obj" \
	"$(INTDIR)\spp_tcp_stream.obj" \
	"$(INTDIR)\syslog.obj" \
	"$(INTDIR)\name.res"

"$(OUTDIR)\snort.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "snort - Win32 Flexresp Release"

OUTDIR=.\snort___Win32_Flexresp_Release
INTDIR=.\snort___Win32_Flexresp_Release
# Begin Custom Macros
OutDir=.\snort___Win32_Flexresp_Release
# End Custom Macros

ALL : "$(OUTDIR)\snort.exe"


CLEAN :
	-@erase "$(INTDIR)\checksum.obj"
	-@erase "$(INTDIR)\decode.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\mstring.obj"
	-@erase "$(INTDIR)\name.res"
	-@erase "$(INTDIR)\parser.obj"
	-@erase "$(INTDIR)\plugbase.obj"
	-@erase "$(INTDIR)\rules.obj"
	-@erase "$(INTDIR)\snort.obj"
	-@erase "$(INTDIR)\sp_dsize_check.obj"
	-@erase "$(INTDIR)\sp_icmp_code_check.obj"
	-@erase "$(INTDIR)\sp_icmp_id_check.obj"
	-@erase "$(INTDIR)\sp_icmp_seq_check.obj"
	-@erase "$(INTDIR)\sp_icmp_type_check.obj"
	-@erase "$(INTDIR)\sp_ip_fragbits.obj"
	-@erase "$(INTDIR)\sp_ip_id_check.obj"
	-@erase "$(INTDIR)\sp_ip_tos_check.obj"
	-@erase "$(INTDIR)\sp_ipoption_check.obj"
	-@erase "$(INTDIR)\sp_pattern_match.obj"
	-@erase "$(INTDIR)\sp_react.obj"
	-@erase "$(INTDIR)\sp_reference.obj"
	-@erase "$(INTDIR)\sp_respond.obj"
	-@erase "$(INTDIR)\sp_rpc_check.obj"
	-@erase "$(INTDIR)\sp_session.obj"
	-@erase "$(INTDIR)\sp_tcp_ack_check.obj"
	-@erase "$(INTDIR)\sp_tcp_flag_check.obj"
	-@erase "$(INTDIR)\sp_tcp_seq_check.obj"
	-@erase "$(INTDIR)\sp_ttl_check.obj"
	-@erase "$(INTDIR)\spo_alert_fast.obj"
	-@erase "$(INTDIR)\spo_alert_full.obj"
	-@erase "$(INTDIR)\spo_alert_smb.obj"
	-@erase "$(INTDIR)\spo_alert_syslog.obj"
	-@erase "$(INTDIR)\spo_alert_unixsock.obj"
	-@erase "$(INTDIR)\spo_database.obj"
	-@erase "$(INTDIR)\spo_log_tcpdump.obj"
	-@erase "$(INTDIR)\spo_xml.obj"
	-@erase "$(INTDIR)\spp_anomsensor.obj"
	-@erase "$(INTDIR)\spp_defrag.obj"
	-@erase "$(INTDIR)\spp_http_decode.obj"
	-@erase "$(INTDIR)\spp_minfrag.obj"
	-@erase "$(INTDIR)\spp_portscan.obj"
	-@erase "$(INTDIR)\spp_tcp_stream.obj"
	-@erase "$(INTDIR)\syslog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\snort.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\Win32-Includes" /I "..\\" /I "..\Win32-Includes\libnet" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_RESPONSE" /Fp"$(INTDIR)\snort.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\name.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\snort.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib wsock32.lib libpcap.lib advapi32.lib libnetnt.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\snort.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /out:"$(OUTDIR)\snort.exe" /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\libnet" 
LINK32_OBJS= \
	"$(INTDIR)\checksum.obj" \
	"$(INTDIR)\decode.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mstring.obj" \
	"$(INTDIR)\parser.obj" \
	"$(INTDIR)\plugbase.obj" \
	"$(INTDIR)\rules.obj" \
	"$(INTDIR)\snort.obj" \
	"$(INTDIR)\sp_dsize_check.obj" \
	"$(INTDIR)\sp_icmp_code_check.obj" \
	"$(INTDIR)\sp_icmp_id_check.obj" \
	"$(INTDIR)\sp_icmp_seq_check.obj" \
	"$(INTDIR)\sp_icmp_type_check.obj" \
	"$(INTDIR)\sp_ip_fragbits.obj" \
	"$(INTDIR)\sp_ip_id_check.obj" \
	"$(INTDIR)\sp_ip_tos_check.obj" \
	"$(INTDIR)\sp_ipoption_check.obj" \
	"$(INTDIR)\sp_pattern_match.obj" \
	"$(INTDIR)\sp_react.obj" \
	"$(INTDIR)\sp_reference.obj" \
	"$(INTDIR)\sp_respond.obj" \
	"$(INTDIR)\sp_rpc_check.obj" \
	"$(INTDIR)\sp_session.obj" \
	"$(INTDIR)\sp_tcp_ack_check.obj" \
	"$(INTDIR)\sp_tcp_flag_check.obj" \
	"$(INTDIR)\sp_tcp_seq_check.obj" \
	"$(INTDIR)\sp_ttl_check.obj" \
	"$(INTDIR)\spo_alert_fast.obj" \
	"$(INTDIR)\spo_alert_full.obj" \
	"$(INTDIR)\spo_alert_smb.obj" \
	"$(INTDIR)\spo_alert_syslog.obj" \
	"$(INTDIR)\spo_alert_unixsock.obj" \
	"$(INTDIR)\spo_database.obj" \
	"$(INTDIR)\spo_log_tcpdump.obj" \
	"$(INTDIR)\spo_xml.obj" \
	"$(INTDIR)\spp_anomsensor.obj" \
	"$(INTDIR)\spp_defrag.obj" \
	"$(INTDIR)\spp_http_decode.obj" \
	"$(INTDIR)\spp_minfrag.obj" \
	"$(INTDIR)\spp_portscan.obj" \
	"$(INTDIR)\spp_tcp_stream.obj" \
	"$(INTDIR)\syslog.obj" \
	"$(INTDIR)\name.res"

"$(OUTDIR)\snort.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "snort - Win32 Flexresp Debug"

OUTDIR=.\snort___Win32_Flexresp_Debug
INTDIR=.\snort___Win32_Flexresp_Debug
# Begin Custom Macros
OutDir=.\snort___Win32_Flexresp_Debug
# End Custom Macros

ALL : "$(OUTDIR)\snort.exe"


CLEAN :
	-@erase "$(INTDIR)\checksum.obj"
	-@erase "$(INTDIR)\decode.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\mstring.obj"
	-@erase "$(INTDIR)\name.res"
	-@erase "$(INTDIR)\parser.obj"
	-@erase "$(INTDIR)\plugbase.obj"
	-@erase "$(INTDIR)\rules.obj"
	-@erase "$(INTDIR)\snort.obj"
	-@erase "$(INTDIR)\sp_dsize_check.obj"
	-@erase "$(INTDIR)\sp_icmp_code_check.obj"
	-@erase "$(INTDIR)\sp_icmp_id_check.obj"
	-@erase "$(INTDIR)\sp_icmp_seq_check.obj"
	-@erase "$(INTDIR)\sp_icmp_type_check.obj"
	-@erase "$(INTDIR)\sp_ip_fragbits.obj"
	-@erase "$(INTDIR)\sp_ip_id_check.obj"
	-@erase "$(INTDIR)\sp_ip_tos_check.obj"
	-@erase "$(INTDIR)\sp_ipoption_check.obj"
	-@erase "$(INTDIR)\sp_pattern_match.obj"
	-@erase "$(INTDIR)\sp_react.obj"
	-@erase "$(INTDIR)\sp_reference.obj"
	-@erase "$(INTDIR)\sp_respond.obj"
	-@erase "$(INTDIR)\sp_rpc_check.obj"
	-@erase "$(INTDIR)\sp_session.obj"
	-@erase "$(INTDIR)\sp_tcp_ack_check.obj"
	-@erase "$(INTDIR)\sp_tcp_flag_check.obj"
	-@erase "$(INTDIR)\sp_tcp_seq_check.obj"
	-@erase "$(INTDIR)\sp_ttl_check.obj"
	-@erase "$(INTDIR)\spo_alert_fast.obj"
	-@erase "$(INTDIR)\spo_alert_full.obj"
	-@erase "$(INTDIR)\spo_alert_smb.obj"
	-@erase "$(INTDIR)\spo_alert_syslog.obj"
	-@erase "$(INTDIR)\spo_alert_unixsock.obj"
	-@erase "$(INTDIR)\spo_database.obj"
	-@erase "$(INTDIR)\spo_log_tcpdump.obj"
	-@erase "$(INTDIR)\spo_xml.obj"
	-@erase "$(INTDIR)\spp_anomsensor.obj"
	-@erase "$(INTDIR)\spp_defrag.obj"
	-@erase "$(INTDIR)\spp_http_decode.obj"
	-@erase "$(INTDIR)\spp_minfrag.obj"
	-@erase "$(INTDIR)\spp_portscan.obj"
	-@erase "$(INTDIR)\spp_tcp_stream.obj"
	-@erase "$(INTDIR)\syslog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\snort.exe"
	-@erase "$(OUTDIR)\snort.ilk"
	-@erase "$(OUTDIR)\snort.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\Win32-Includes" /I "..\\" /I "..\Win32-Includes\libnet" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_RESPONSE" /Fp"$(INTDIR)\snort.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\name.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\snort.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib wsock32.lib libpcap.lib advapi32.lib libnetnt.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\snort.pdb" /debug /machine:I386 /nodefaultlib:"libcmt.lib" /out:"$(OUTDIR)\snort.exe" /pdbtype:sept /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\libnet" 
LINK32_OBJS= \
	"$(INTDIR)\checksum.obj" \
	"$(INTDIR)\decode.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mstring.obj" \
	"$(INTDIR)\parser.obj" \
	"$(INTDIR)\plugbase.obj" \
	"$(INTDIR)\rules.obj" \
	"$(INTDIR)\snort.obj" \
	"$(INTDIR)\sp_dsize_check.obj" \
	"$(INTDIR)\sp_icmp_code_check.obj" \
	"$(INTDIR)\sp_icmp_id_check.obj" \
	"$(INTDIR)\sp_icmp_seq_check.obj" \
	"$(INTDIR)\sp_icmp_type_check.obj" \
	"$(INTDIR)\sp_ip_fragbits.obj" \
	"$(INTDIR)\sp_ip_id_check.obj" \
	"$(INTDIR)\sp_ip_tos_check.obj" \
	"$(INTDIR)\sp_ipoption_check.obj" \
	"$(INTDIR)\sp_pattern_match.obj" \
	"$(INTDIR)\sp_react.obj" \
	"$(INTDIR)\sp_reference.obj" \
	"$(INTDIR)\sp_respond.obj" \
	"$(INTDIR)\sp_rpc_check.obj" \
	"$(INTDIR)\sp_session.obj" \
	"$(INTDIR)\sp_tcp_ack_check.obj" \
	"$(INTDIR)\sp_tcp_flag_check.obj" \
	"$(INTDIR)\sp_tcp_seq_check.obj" \
	"$(INTDIR)\sp_ttl_check.obj" \
	"$(INTDIR)\spo_alert_fast.obj" \
	"$(INTDIR)\spo_alert_full.obj" \
	"$(INTDIR)\spo_alert_smb.obj" \
	"$(INTDIR)\spo_alert_syslog.obj" \
	"$(INTDIR)\spo_alert_unixsock.obj" \
	"$(INTDIR)\spo_database.obj" \
	"$(INTDIR)\spo_log_tcpdump.obj" \
	"$(INTDIR)\spo_xml.obj" \
	"$(INTDIR)\spp_anomsensor.obj" \
	"$(INTDIR)\spp_defrag.obj" \
	"$(INTDIR)\spp_http_decode.obj" \
	"$(INTDIR)\spp_minfrag.obj" \
	"$(INTDIR)\spp_portscan.obj" \
	"$(INTDIR)\spp_tcp_stream.obj" \
	"$(INTDIR)\syslog.obj" \
	"$(INTDIR)\name.res"

"$(OUTDIR)\snort.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "snort - Win32 MySQL Release"

OUTDIR=.\snort___Win32_MySQL_Release
INTDIR=.\snort___Win32_MySQL_Release
# Begin Custom Macros
OutDir=.\snort___Win32_MySQL_Release
# End Custom Macros

ALL : "$(OUTDIR)\snort.exe"


CLEAN :
	-@erase "$(INTDIR)\checksum.obj"
	-@erase "$(INTDIR)\decode.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\mstring.obj"
	-@erase "$(INTDIR)\name.res"
	-@erase "$(INTDIR)\parser.obj"
	-@erase "$(INTDIR)\plugbase.obj"
	-@erase "$(INTDIR)\rules.obj"
	-@erase "$(INTDIR)\snort.obj"
	-@erase "$(INTDIR)\sp_dsize_check.obj"
	-@erase "$(INTDIR)\sp_icmp_code_check.obj"
	-@erase "$(INTDIR)\sp_icmp_id_check.obj"
	-@erase "$(INTDIR)\sp_icmp_seq_check.obj"
	-@erase "$(INTDIR)\sp_icmp_type_check.obj"
	-@erase "$(INTDIR)\sp_ip_fragbits.obj"
	-@erase "$(INTDIR)\sp_ip_id_check.obj"
	-@erase "$(INTDIR)\sp_ip_tos_check.obj"
	-@erase "$(INTDIR)\sp_ipoption_check.obj"
	-@erase "$(INTDIR)\sp_pattern_match.obj"
	-@erase "$(INTDIR)\sp_react.obj"
	-@erase "$(INTDIR)\sp_reference.obj"
	-@erase "$(INTDIR)\sp_respond.obj"
	-@erase "$(INTDIR)\sp_rpc_check.obj"
	-@erase "$(INTDIR)\sp_session.obj"
	-@erase "$(INTDIR)\sp_tcp_ack_check.obj"
	-@erase "$(INTDIR)\sp_tcp_flag_check.obj"
	-@erase "$(INTDIR)\sp_tcp_seq_check.obj"
	-@erase "$(INTDIR)\sp_ttl_check.obj"
	-@erase "$(INTDIR)\spo_alert_fast.obj"
	-@erase "$(INTDIR)\spo_alert_full.obj"
	-@erase "$(INTDIR)\spo_alert_smb.obj"
	-@erase "$(INTDIR)\spo_alert_syslog.obj"
	-@erase "$(INTDIR)\spo_alert_unixsock.obj"
	-@erase "$(INTDIR)\spo_database.obj"
	-@erase "$(INTDIR)\spo_log_tcpdump.obj"
	-@erase "$(INTDIR)\spo_xml.obj"
	-@erase "$(INTDIR)\spp_anomsensor.obj"
	-@erase "$(INTDIR)\spp_defrag.obj"
	-@erase "$(INTDIR)\spp_http_decode.obj"
	-@erase "$(INTDIR)\spp_minfrag.obj"
	-@erase "$(INTDIR)\spp_portscan.obj"
	-@erase "$(INTDIR)\spp_tcp_stream.obj"
	-@erase "$(INTDIR)\syslog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\snort.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\Win32-Includes" /I "..\Win32-Includes\mysql" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D __BEGIN_DECLS="" /D __END_DECLS="" /D "ENABLE_MYSQL" /Fp"$(INTDIR)\snort.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\name.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\snort.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=user32.lib wsock32.lib libpcap.lib advapi32.lib mysqlclient.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\snort.pdb" /machine:I386 /out:"$(OUTDIR)\snort.exe" /libpath:"..\Win32-Libraries" /libpath:"..\Win32-Libraries\mysql" 
LINK32_OBJS= \
	"$(INTDIR)\checksum.obj" \
	"$(INTDIR)\decode.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\mstring.obj" \
	"$(INTDIR)\parser.obj" \
	"$(INTDIR)\plugbase.obj" \
	"$(INTDIR)\rules.obj" \
	"$(INTDIR)\snort.obj" \
	"$(INTDIR)\sp_dsize_check.obj" \
	"$(INTDIR)\sp_icmp_code_check.obj" \
	"$(INTDIR)\sp_icmp_id_check.obj" \
	"$(INTDIR)\sp_icmp_seq_check.obj" \
	"$(INTDIR)\sp_icmp_type_check.obj" \
	"$(INTDIR)\sp_ip_fragbits.obj" \
	"$(INTDIR)\sp_ip_id_check.obj" \
	"$(INTDIR)\sp_ip_tos_check.obj" \
	"$(INTDIR)\sp_ipoption_check.obj" \
	"$(INTDIR)\sp_pattern_match.obj" \
	"$(INTDIR)\sp_react.obj" \
	"$(INTDIR)\sp_reference.obj" \
	"$(INTDIR)\sp_respond.obj" \
	"$(INTDIR)\sp_rpc_check.obj" \
	"$(INTDIR)\sp_session.obj" \
	"$(INTDIR)\sp_tcp_ack_check.obj" \
	"$(INTDIR)\sp_tcp_flag_check.obj" \
	"$(INTDIR)\sp_tcp_seq_check.obj" \
	"$(INTDIR)\sp_ttl_check.obj" \
	"$(INTDIR)\spo_alert_fast.obj" \
	"$(INTDIR)\spo_alert_full.obj" \
	"$(INTDIR)\spo_alert_smb.obj" \
	"$(INTDIR)\spo_alert_syslog.obj" \
	"$(INTDIR)\spo_alert_unixsock.obj" \
	"$(INTDIR)\spo_database.obj" \
	"$(INTDIR)\spo_log_tcpdump.obj" \
	"$(INTDIR)\spo_xml.obj" \
	"$(INTDIR)\spp_anomsensor.obj" \
	"$(INTDIR)\spp_defrag.obj" \
	"$(INTDIR)\spp_http_decode.obj" \
	"$(INTDIR)\spp_minfrag.obj" \
	"$(INTDIR)\spp_portscan.obj" \
	"$(INTDIR)\spp_tcp_stream.obj" \
	"$(INTDIR)\syslog.obj" \
	"$(INTDIR)\name.res"

"$(OUTDIR)\snort.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("snort.dep")
!INCLUDE "snort.dep"
!ELSE 
!MESSAGE Warning: cannot find "snort.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "snort - Win32 Release" || "$(CFG)" == "snort - Win32 Debug" || "$(CFG)" == "snort - Win32 MySQL Debug" || "$(CFG)" == "snort - Win32 Flexresp Release" || "$(CFG)" == "snort - Win32 Flexresp Debug" || "$(CFG)" == "snort - Win32 MySQL Release"
SOURCE=..\checksum.c

"$(INTDIR)\checksum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\decode.c

"$(INTDIR)\decode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\WIN32-Code\getopt.c"

"$(INTDIR)\getopt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\log.c

"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\WIN32-Code\misc.c"

"$(INTDIR)\misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\mstring.c

"$(INTDIR)\mstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\parser.c

"$(INTDIR)\parser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\plugbase.c

"$(INTDIR)\plugbase.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\rules.c

"$(INTDIR)\rules.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\snort.c

"$(INTDIR)\snort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_dsize_check.c

"$(INTDIR)\sp_dsize_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_icmp_code_check.c

"$(INTDIR)\sp_icmp_code_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_icmp_id_check.c

"$(INTDIR)\sp_icmp_id_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_icmp_seq_check.c

"$(INTDIR)\sp_icmp_seq_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_icmp_type_check.c

"$(INTDIR)\sp_icmp_type_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_ip_fragbits.c

"$(INTDIR)\sp_ip_fragbits.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_ip_id_check.c

"$(INTDIR)\sp_ip_id_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_ip_tos_check.c

"$(INTDIR)\sp_ip_tos_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_ipoption_check.c

"$(INTDIR)\sp_ipoption_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_pattern_match.c

"$(INTDIR)\sp_pattern_match.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_react.c

"$(INTDIR)\sp_react.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_reference.c

"$(INTDIR)\sp_reference.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_respond.c

"$(INTDIR)\sp_respond.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_rpc_check.c

"$(INTDIR)\sp_rpc_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_session.c

"$(INTDIR)\sp_session.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_tcp_ack_check.c

"$(INTDIR)\sp_tcp_ack_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_tcp_flag_check.c

"$(INTDIR)\sp_tcp_flag_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_tcp_seq_check.c

"$(INTDIR)\sp_tcp_seq_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sp_ttl_check.c

"$(INTDIR)\sp_ttl_check.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_alert_fast.c

"$(INTDIR)\spo_alert_fast.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_alert_full.c

"$(INTDIR)\spo_alert_full.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_alert_smb.c

"$(INTDIR)\spo_alert_smb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_alert_syslog.c

"$(INTDIR)\spo_alert_syslog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_alert_unixsock.c

"$(INTDIR)\spo_alert_unixsock.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_database.c

"$(INTDIR)\spo_database.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_log_tcpdump.c

"$(INTDIR)\spo_log_tcpdump.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spo_xml.c

"$(INTDIR)\spo_xml.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spp_anomsensor.c

"$(INTDIR)\spp_anomsensor.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spp_defrag.c

"$(INTDIR)\spp_defrag.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spp_http_decode.c

"$(INTDIR)\spp_http_decode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spp_minfrag.c

"$(INTDIR)\spp_minfrag.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spp_portscan.c

"$(INTDIR)\spp_portscan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\spp_tcp_stream.c

"$(INTDIR)\spp_tcp_stream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\WIN32-Code\syslog.c"

"$(INTDIR)\syslog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\WIN32-Code\name.rc"

!IF  "$(CFG)" == "snort - Win32 Release"


"$(INTDIR)\name.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\name.res" /i "\code\snort-1.7\WIN32-Code" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "snort - Win32 Debug"


"$(INTDIR)\name.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\name.res" /i "\code\snort-1.7\WIN32-Code" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "snort - Win32 MySQL Debug"


"$(INTDIR)\name.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\name.res" /i "\code\snort-1.7\WIN32-Code" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "snort - Win32 Flexresp Release"


"$(INTDIR)\name.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\name.res" /i "\code\snort-1.7\WIN32-Code" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "snort - Win32 Flexresp Debug"


"$(INTDIR)\name.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\name.res" /i "\code\snort-1.7\WIN32-Code" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "snort - Win32 MySQL Release"


"$(INTDIR)\name.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\name.res" /i "\code\snort-1.7\WIN32-Code" /d "NDEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

