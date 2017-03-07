# $Id: Makefile.am,v 1.21 2001/01/05 19:27:33 roesch Exp $
AUTOMAKE_OPTIONS=foreign no-dependencies
bin_PROGRAMS = snort
snort_SOURCES = snort.c snort.h log.c log.h decode.c decode.h         \
mstring.h mstring.c rules.c rules.h plugbase.c plugbase.h             \
sp_pattern_match.c sp_pattern_match.h sp_tcp_flag_check.c             \
sp_tcp_flag_check.h sp_icmp_type_check.c sp_icmp_type_check.h         \
sp_icmp_code_check.c sp_icmp_code_check.h sp_ttl_check.c              \
sp_ttl_check.h sp_ip_id_check.c sp_ip_id_check.h sp_tcp_ack_check.c   \
sp_tcp_ack_check.h sp_tcp_seq_check.c sp_tcp_seq_check.h              \
sp_dsize_check.c sp_dsize_check.h spp_http_decode.h spp_http_decode.c \
spp_minfrag.c spp_minfrag.h spp_portscan.c spp_portscan.h             \
sp_ipoption_check.h sp_ipoption_check.c sp_rpc_check.h sp_rpc_check.c \
sp_icmp_id_check.c sp_icmp_id_check.h sp_icmp_seq_check.h             \
sp_icmp_seq_check.c sp_respond.c sp_respond.h spo_alert_syslog.c      \
spo_alert_syslog.h spo_log_tcpdump.c spo_log_tcpdump.h prototypes.h   \
spo_database.c spo_database.h sp_session.h sp_session.c               \
spp_defrag.c spp_defrag.h parser.c parser.h spo_alert_fast.c          \
spo_alert_fast.h spo_alert_full.c spo_alert_full.h spo_alert_smb.c    \
spo_alert_smb.h spo_alert_unixsock.c spo_alert_unixsock.h sp_react.c  \
sp_react.h spo_xml.c spo_xml.h sp_ip_tos_check.c sp_ip_tos_check.h    \
spp_tcp_stream.c spp_tcp_stream.h snprintf.c snprintf.h checksum.c    \
checksum.h sp_reference.c sp_reference.h sp_ip_fragbits.c             \
sp_ip_fragbits.h spp_anomsensor.h spp_anomsensor.c

EXTRA_DIST = BUGS RULES.SAMPLE CREDITS snort.conf USAGE backdoor-lib  \
ftp-lib overflow-lib scan-lib web-lib webfp-lib ddos-lib misc-lib     \
ping-lib smtp-lib webcf-lib webiis-lib finger-lib netbios-lib rpc-lib \
telnet-lib webcgi-lib webmisc-lib templates/sp_template.c             \
templates/sp_template.h templates/spp_template.h                      \
templates/spp_template.c snort.8 README.PLUGINS README.FLEXRESP       \
README.database README.tcpstream README.xml README.Spade              \
README.Spade.Usage LICENSE                                            \
contrib/ACID-0.9.5b9.tar.gz contrib/SnortSnarf-111500.1.tar.gz        \
contrib/Spade-092200.1.tar.gz contrib/Guardian.tar.gz                 \
contrib/Net-SnortLog-0.1.tar.gz contrib/README                        \
contrib/address_config.sh contrib/create_mysql                        \
contrib/create_postgresql contrib/mysql.php3 contrib/passiveOS.tar.gz \
contrib/pgsql.php3 contrib/snml.dtd contrib/snort-sort.pl             \
contrib/snort2html.pl contrib/snort_stat.pl contrib/snortdb-extra.gz  \
contrib/snortlog contrib/snortnet.tar.gz contrib/snortwatch-0.7.tar.gz\
contrib/idmef-xml-plugin_0.1.tar.gz cdefs.h

INCLUDES = @extra_incl@
man_MANS = snort.8
