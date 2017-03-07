Snort Version 1.7-WIN32

by Michael Davis (mike@datanerds.net)

Distribution Site:
http://www.datanerds.net/~mike
http://www.snort.org
http://snort.sourceforge.net

Alternate Sites:

US:
http://www.technotronic.com
http://packetstorm.securify.com
http://snort.whitehats.com

Europe:
http://gd.tuwien.ac.at/infosys/security/snort
ftp://gd.tuwien.ac.at/infosys/security/snort
http://www.centus.com/snort/security.html

South America:
http://snort.safenetworks.com

Austrailia:
ftp://the.wiretapped.net/pub/security/network-intrusion-detection/snort


COPYRIGHT

Any WIN32 based modifications are:
******************************************************************************
 . Copyright (c) 2001 Michael Davis <mike@datanerds.net>
 . All rights reserved.
 .
 . Redistribution and use in source and binary forms, with or without
 . modification, are permitted provided that the following conditions
 . are met:
 .
 . 1. Redistributions of source code must retain the above copyright
 .    notice, this list of conditions and the following disclaimer.
 .
 . 2. Redistributions in binary form must reproduce the above copyright
 .    notice, this list of conditions and the following disclaimer in the
 .    documentation and/or other materials provided with the distribution.
 .
 . 3. The name of author may not be used to endorse or promote products
 .    derived from this software without specific prior written permission.
 .
 . THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 . INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 . AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 . THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 . EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 . PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 . OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 . WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 . OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 . ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************

Original snort code is:
******************************************************************************

Copyright (C)1998,1999,2000,2001 Martin Roesch

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

Some of this code has been taken from tcpdump, which was developed
by the Network Research Group at Lawrence Berkeley National Lab,
and is copyrighted by the University of California Regents.

******************************************************************************

DESCRIPTION

Snort is an open source network intrusion detection system, capable  of  
performing  real-time traffic analysis and packet logging on IP networks.  
It  can  perform  protocol analysis and content searching/matching in order to
detect a variety of attacks and  probes, such as buffer overflows, stealth port
scans, CGI attacks, SMB probes, OS fingerprinting attempts, and much more.  
Snort uses a flexible rules language to describe traffic that it should collect
or pass, as well as a detection engine  that  utilizes a modular plugin
architecture.  Snort has a real- time alerting capability as well, 
incorporating  alerting mechanisms  for  syslog,  user  specified  files, and EventLog.

Snort  has  three  primary  functional modes.   It  can  be  used as a straight
packet sniffer like tcpdump(1), a  packet  logger (useful  for network traffic
debugging, etc), or as a full blown network intrusion detection system.

Snort logs packets in either tcpdump(1) binary format  or in Snort's decoded
ASCII format to a hierarcical set of directories that are named based on the IP
address of the remote host.

Plugins allow the detection and reporting subsystems to be extended.  Available 
plugins include database or XML logging, small fragment detection, portscan 
detection, and HTTP URI normalization, IP defragmentation, TCP stream 
reassembly and statistical anomaly detection.  


******************************************************************************

[*][USAGE]

Command line: 

	snort -[options] <filters>

Options:

    -A <alert>  Set <alert> mode to full, fast or none.  Full mode
            does normal "classic Snort"-style alerts to the alert
            file.  Fast mode just writes the timestamp, message, 
            IPs, and ports to the file.  None turns off alerting.
            There is experimental support for UnixSock alerts 
            that allow alerting to a sepreate process.  Use the 
            "unsock" argument to activate this feature. 
            ** UNIXSOCK IS NOT SUPPORTED IN THIS WIN32 RELEASE. **

    -a	    Display ARP packets

    -b	    Log packets in tcpdump format.  All packets are logged
            in their native binary state to a tcpdump formatted 
            log file called "snort.log".  This option results in
            much faster operation of the program since it doesn't
            have to spend time in the packet binary->text
            converters.  Snort can keep up pretty well with 100Mbps
            networks in "-b" mode.

    -c <cf>	Use configuration file <cf>.  This is the rules file
            which tells the system what to log, alert on, or pass!

    -C      Dump the ASCII characters in packet payloads only, no
            hexdump

    -d      Dump the application layer data

    -D      Run Snort in daemon mode.  Alerts are sent to
            /var/log/snort/alert unless otherwise specified.
            ** NOT SUPPORTED IN THIS WIN32 RELEASE. **

    -e      Display/log the layer 2 packet header data.
    
    -E	    Log all events to the Windows EventLog.

    -F <bpf> Read BPF filters from file <bpf>.  Handy for those of
            you running Snort as a SHADOW replacement or with a
            love of super complex BPF filters.

    -g <gname> Run Snort as group ID <gname> after initialization. 
            This switch allows Snort to drop root priveleges after
            it's initialization phase has completed as a security
            measure. ** NOT SUPPORTED IN THIS WIN32 RELEASE. **

    -h <hn>	Set the "home network" to <hn>, which is a class C IP 
            address something like 192.168.1.0 or whatever.  If you
            use this switch, traffic coming from external networks
            will be formatted with the directional arrow of the 
            packet dump pointing right for incoming external 
            traffic, and left for outgoing internal traffic.  Kind
            of silly, but it looks nice.

    -i <if> Sniff on network interface <if>.  

    -I      Add the interface name to alert printouts (first interface only)

    -l <ld> Log packets to directory <ld>.  Sets up a hierarchical
            directory structure with the log directory as the base
            starting directory, and the IP address of the remote
            peer generating traffic as the directory which packets
            packets from that adress are stored in.  If you do not 
            use the -l switch, the default logging directory is 
            /var/log/snort.
          
    -L <fn> Set the binary output file's filename to <fn>.            

    -M <wkstn>  Send WinPopup messages to the list of workstations
            contained in the <wkstn> file.  This option requires
            Samba to be resident and in the path of the machine
            running Snort.  The workstation file is simple: each
            line of the file containes the SMB name of the box to
            send the message to (no \\'s needed).

    -n <num> Exit after processing <num> packets.

    -N      Turn off logging.  Alerts still function normally.

    -o      Change the order in which the rules are applied to 
            packets.  Instead of being applied in the standard
            Alert->Pass->Log order, this will apply them in 
            Pass->Alert->Log order, allowing people to avoid having
            to make huge BPF command line arguments to filter their
            alert rules.  

    -O      Obfuscate the IP addresses when in ASCII packet dump
            mode.  This switch changes the IP addresses that get
            printed to the screen/log file to "xxx.xxx.xxx.xxx".
            If the homenet address switch is set (-h), only 
            addresses on the homenet will be obfuscated while non-
            homenet IPs will be left visible.  Perfect for posting
            to your favorite security mailing list!

    -p		Turn off promiscuous mode sniffing.  Useful for places
            where that can screw up your host severely.

    -q	    Quiet. Don't show banner and status report.			

    -r <tf>	Read the tcpdump-generated file <tf>.  This will cause
            Snort to read and process the file fed to it.  This is
            useful if, for instance, you've got a bunch of Shadow
            files that you want to process for content, or even if
            you've got a bunch of reassembled packet fragments
            which have been written into a tcpdump formatted file.

    -s <serve:port>     Log alert messages to syslog on server.  On linux boxen, they
	        	will appear in /var/log/secure, /var/log/messages on
            		many other platforms.  You can change the logging facility 
            		by using the syslog output plugin, at which point the -s
            		switch is unneeded.

	-S <n=v> Set variable name "n" to value "v".  This is useful for
            setting the value of a defined variable name in a Snort
            rules file to a command line specified value.  For
            instance, if you define a HOME_NET variable name inside
            of a Snort rules file, you can set this value from
            it's predefined value at the command line.

    -t <chroot> Changes Snort's root directory to <chroot> after 
            initialization.  Please note that all log/alert filenames
            are relevant to chroot directory, if chroot is used.
            ** NOT SUPPORTED IN THIS WIN32 RELEASE. **

    -u <uname> Change the UID Snort runs under to <uname> after 
            initialization.
            ** NOT SUPPORTED IN THIS WIN32 RELEASE. **

    -v		Be verbose.  Prints packets out to the console.  There
            is one big problem with verbose mode: it's still kind
            of slow.  If you are doing IDS work with Snort, don't
            use the -v switch, you WILL drop packets (not many, but
            some).

    -V      Show the version number and exit.
    
    -W	    Lists all available interfaces that snort can listen on.

    -x      Show an annoying little message whenever you see an 
            annoying IPX packet.

    -X      Dump the raw packet data starting at the link layer.

    -?      Show the usage summary and exit.


[*][FILTERS]:

     The "filters" are standard BPF style filters as seen in tcpdump.  Look
at the man page for snort for docs on how to use it properly.  In general,
you can give it a host, net or protocol to filter on and some logical statements
to tie it together and get the specific traffic you're interested in.  For 
example:

C:\snort> snort -h 192.168.1.0/24 -d -v host 192.168.1.1

records the traffic to and from host 192.168.1.1.

C:\snort> snort -h 192.168.1.0/24 -d -v net 192.168.1 and not host 192.168.1.1

records all traffic on the 192.168.1.0/24 class C subnet, but not traffic 
to/from 192.168.1.1.  Notice that the command line data specified after the
"-h" switch is formated differently from the BPF commands provided at the end 
of the command line.  Sorry for the confusion, but I like the CIDR notation and
I'm not rewriting libpcap to make it consistent!  Anyway, you get the picture.
Mail me if you have trouble with it.

You can use the -F switch to read your BPF filters in from a file.  


[*][RULES]:
      
-------------------------------------------------------------------------
NOTE: The "official" rules document these days is available at:

http://www.snort.org/snort_rules.html
-------------------------------------------------------------------------

[*][RUN MODES]

Snort has three primary run-time modes: sniffer, packet logger, and network
intrusion detection.

Sniffer Mode: When in this mode, Snort reads and decodes all packets from 
the network and dumps them to the stdout.  To put Snort into straight sniffing
mode, use the "-v" verbose switch.  This will dump the packet headers only.
You can see the headers + the packet payloads by specifying the "-v" and "-d"
switch.  To print a dump of the raw bytes in the entire packet, specify the 
"-X" switch.  If you specify the "-X" switch, the -d switch is overridden.  You
can filter the traffic that shows up in this mode by using BPF filters.

Packet Logger Mode: This mode logs the packets to the disk in their decoded
ASCII format.  This mode is activated merely by specifying a directory to log
packets to with the "-l" switch.  This will log packets into the specified 
logging directory in a heirarchy of directories based upon the IP addresses of
the packets on the wire.  To log the packets in terms of the network being 
monitored (i.e. the directories created under the logging directory are the
IP addresses of the remote/non-home hosts) use the "-h" switch.  To log the 
packets in their raw binary format to the disk, use the "-b" switch.  Logging
the packets in this format will allow them to be run through other tools like 
Ethereal, tcpdump, etc.  Packet logger mode can be mixed with sniffer mode 
switches with no ill effects, however logging performance may be impacted by 
the slowness of the terminal.

Intrusion Detction Mode: Snort enters IDS mode when a configuration file is 
specified with the "-c" switch.  Output formats, rules, preprocessor 
configuration, etc are all specified in the configuration file.  Logger mode
is essentially disabled when in IDS mode, but that's ok because you specify
which packets you want to log when in IDS mode.  See the rule document (above) 
for how to write your own rules.  When an alert rule goes off the alert data is
logged to the alerting mechanism (be default a file called "alert" in the 
logging directory) in addition to being logged to the logging mechanism.  The
default logging directory is named ./log, which can be changed using the 
"-l" switch.   

You can use something like "rt" or just "tail -f" it to give a running display
of system alerts.  Alerts can also be sent to syslog (and monitored with
something like swatch), or they can be sent out as WinPopup messages with
smbclient.  Check out the "INSTALL" file for information on enabling the SMB
alerting option.  There are a variety of other alerting and logging mechanisms
available, check out the snort.conf file for information on enabling them.

Note that the system requires the use of the "-l" flag to redirect rules based
logging to a specific directory.  If you don't specify a place for it to go, it
defaults to the directory named log within the current directory.

******************************************************************************
/* $Id: README,v 1.11 2001/01/02 19:52:10 roesch Exp $ */
