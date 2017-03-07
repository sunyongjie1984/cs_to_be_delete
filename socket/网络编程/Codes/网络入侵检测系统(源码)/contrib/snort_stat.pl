#!/usr/bin/perl 
#
# $Id: snort_stat.pl,v 1.3 2000/11/17 05:28:20 jpickel Exp $
# $Revision: 1.3 $
#
# snort_stat.pl is a perl script trying to generate statistical data from every
# day snort log file.
#
# USAGE: cat <snort_log> | snort_stat.pl -r -f -a -h -p -n
#        -r: resolve IP address to domain name
#        -f: use fixed rather than variable width columns
#        -a: snort alert format
#        -h: produce html output
#        -p: portscan log (in syslog now)
#        -n: anomsensor log (in syslog)
#
# or put it in the root's crontab file:
#59      10      *       *       *       root    cat /var/log/authlog | /etc/snort_stat.pl | sendmail root
#
# $Author: jpickel $
# Yen-Ming Chen, <chenym@ALUMNI.CMU.EDU>
# $Date: 2000/11/17 05:28:20 $
# 
# Angelos Karageorgiou, <angelos@unix.gr>
# contributed the DNS resolve and cache
#
# Andrew R. Baker <andrewb@uab.edu>
# 2000.03.06 - modifications to read snort alert file
#            - added html output option
#
# Paul Bobby, <paul.bobby@lmco.com>
# 03/13/2000 added scan for portscan detection in logs
#
# Ned Patterson, <jpatter@alum.mit.edu> 
# 4/26/2000 - correctly parse "last message repeated" syslog messages
#           - variable column widths for text output
# 
# Ryan Jian-Da Li, <jdli@freebsd.csie.nctu.edu.tw>
# 6/07/2000 - fix the problem of portscan() (add my %s5)
#           - fix the problem of signature matching
#             for the case ' IDS154 - PING CyberKit 2.2 Windows'
#           - enhance portscan(), add port counts
#

use Getopt::Std;		# use Getopt for options
use Socket;			# use socket for resolving domain name from IP
use vars qw($opt_r $opt_f $opt_a $opt_h $opt_p $opt_n);
%HOSTS = ();			# Hash for IP <-> domain name mapping  

getopts('rfahnp') || die "Could not getopts"; # get options in command line
$saddr_len = 15;
$daddr_len = 15;
$timeout = 3;  # for name resolver

# process whatever comes in
while (<>) {
  if ($opt_a) {
    # process data from a snort alert file
    chomp();
    # if the line is blank, go to the next one
    if ( $_ eq "" )  { next; }
    # is this line an alert message
    unless ( $_ =~ /^\[\*\*\]/ ) {
      # comment out this line to avoid some warning 
      # print STDERR "Warning, file may be corrupt.\n";
      next; 
    }
    $a = <>;
    chomp($a);
    unless ( $a eq "" ) {
      # strip off the [**] from either end.
      s/(\s)*\[\*\*\](\s)*//g;
    } else { 
      print STDERR "Warning, file may be incomplete\n";
      next;
    }
    $sig = $_;
    $a =~ m/^(\d+)\/(\d+)\-(\d+)\:(\d+)\:(\d+)\.(\d+)\s
          ([\d\.]+)[\:]*([\d]*)\s[\-\>]+\s([\d\.]+)[\:]*([\d]*)/ox;
    
    $month  = $1; $day   = $2;  $hour  = $3; $minute = $4;
    $second = $5; $saddr  = $7; $host = "localhost";
    $sport  = $9; $daddr = $9; $dport = $10;
  } else {			# If this is a snort log in syslog
    if ($_ =~
	m/^(\w{3}) \s+ (\d+) \s (\d+) \: (\d+) \: (\d+)\s 
        ([\w+\.]*)\s[\w+\/\[\d+\]]*:\s ([^:]+):\s ([\d\.]+)[\:]?
	([\d]*)\s[\-\>]+\s ([\d\.]+)[\:]? ([\d]*)/ox)
      {
	$month  = $1; $day   = $2;  $hour  = $3; $minute = $4;
	$second = $5; $host  = $6;  $sig   = $7; $saddr  = $8;
	$sport  = $9; $daddr = $10; $dport = $11;
      } 
    elsif ($_ =~ m/^(\w{3})\s+(\d+)\s(\d+)\:(\d+)\:(\d+)\s
	   ([\w+\.]*)\s[\w+\/\[\d+\]]*:
	   \sspp_portscan\:\sPORTSCAN\sDETECTED\sfrom\s([\d\.]+)/ox)
      {
	if ($opt_r) {
	  $psaddr = resolve($7);
	} else {
          $psaddr = ($7);
	}
	push @res , [$psaddr];
	push @rescnt , [$psaddr,$8];
	# Not used elsewhere.  Prob not needed. (Need to find out!)
	#          $tot++;
	next;
      }
    elsif ($_ =~ m/^(\w{3})\s+(\d+)\s(\d+)\:(\d+)\:(\d+)\s
           ([\w+\.]*)\s[\w+\/\[\d+\]]*\:
           \sspp_anomsensor\:\sAnomaly\sthreshold\sexceeded\:\s([\d\.]+)\:
           \s([\d\.]+)\:([\d]+)\s[\-\>]+\s([\d\.]+)\:([\d]+)/ox)
      {
        if ($opt_r) {
          $asaddr = resolve($8);
          $adaddr = resolve($10);
        } else {
          $asaddr = ($8);
          $adaddr = ($10);
        }
        $threshold = $7; $sport = $9; $dport = $11;
        push @anores , [$threshold,$asaddr,$sport,$adaddr,$dport];
        next;
      }
    # If a snort message has been repeated several times
    elsif ($lastwassnort && $_ =~ m/last message repeated (\d+) times/) {
      # put the data in the matrix again for each repeat
      $repeats = $1;
      while ($repeats)  {
	push @result, $result[-1];
	$repeats--;
      }
      next;
    }
    else {
      $lastwassnort = 0;
      next;
    }				# Message not related to snort
  }
  # if the resolve switch is on
  if ($opt_r) {
    $saddr = resolve($saddr);
    unless ($opt_f) {
      if ( length($saddr) > $saddr_len ) {
	$saddr_len = length($saddr);
      }
    }
    $daddr = resolve($daddr);
    unless ($opt_f) {
      if ( length($daddr) > $daddr_len ) {
	$daddr_len = length($daddr);
      }
    }
  }
  
  # put those data into a big matrix
  push @result ,[$month,$day,$hour,$minute,$second,
		 $host,$sig,$saddr,$sport,$daddr,$dport];
  $lastwassnort = 1;
}				# end of snort log

# begin statistics
# I should've used $#result + 1 as $total in the first version! :(
$total = $#result + 1;

for $i ( 0 .. $#result ) {
  # for the same pair of attacker and victim with same sig
  # to see the attack pattern
  # used in same_attack()
  $s0{"$result[$i]->[9]:$result[$i]->[7]:$result[$i]->[6]"}++;
  # for the same pair of attacker and victim 
  # to see how many ways are being tried
  # used in same_host_dest()
  $s1{"$result[$i]->[7]:$result[$i]->[9]"}++;
  # from same host use same method to attack 
  # to see how many attacks launched from one host
  # used in same_host_sig()
  $s2{"$result[$i]->[6]:$result[$i]->[7]"}++;
  # to same victim with same method
  # to see how many attacks received by one host
  # used in same_dest_sig_stat()
  $s3{"$result[$i]->[6]:$result[$i]->[9]"}++;
  # same signature
  # to see the popularity of one attack method
  # used in attack_distribution()
  $s4{"$result[$i]->[6]"}++;
  # source ip
  $s5{"$result[$i]->[7]"}++;
  # destination ip
  $s6{"$result[$i]->[9]"}++;
}

# begin report

print_head();
print_summary();
same_attack();
same_host_dest();
same_host_sig();
same_dest_sig_stat();
attack_distribution();
if ($opt_p) {
  portscan();
}
if ($opt_n) {
  anomsensor();
}
print_footer();

# print the header (e.g. for mail)
sub print_head {
  if($opt_h) {
    print "<html>\n<head>\n";
    print "<title>Snort Statistics</title>";
    print "</head>\n<body>\n";
    print "<h1>Snort Statistics</h1>\n";
  } else { 
    print "Subject: snort daily report\n\n";
  }
}

# print the time of begin and end of the log
sub print_summary {
  if($opt_h) {
    print "<table>\n";
    print "<tr><th>The log begins at:</th>\n";
    print "<td>$result[0]->[0] $result[0]->[1] $result[0]->[2]:$result[0]->[3]:$result[0]->[4]</td></tr>\n";
    print "<tr><th>The log ends at:</th>\n";
    print "<td>$result[$#result]->[0] $result[$#result]->[1] $result[$#result]->[2]:$result[$#result]->[3]:$result[$#result]->[4]</td></tr>\n";
    print "<tr><th>Total events:</th><td> $total</td></tr>\n";
    print "<tr><th>Signatures recorded:</th><td> ". keys(%s4) ."</td></tr>\n";
    print "<tr><th>Source IP recorded:</th><td> ". keys(%s5) ."</td></tr>\n";
    print "<tr><th>Destination IP recorded:</th><td> ". keys(%s6) ."</td></tr>\n";
    print "<tr><th>Anomaly detected:</th><td> ". eval '$#anores + 1'."</td></tr>\n";
    print "</table>\n";
    print "<hr>\n";
  } else {
    print "The log begins from: $result[0]->[0] $result[0]->[1] $result[0]->[2]:$result[0]->[3]:$result[0]->[4]\n";
    print "The log ends     at: $result[$#result]->[0] $result[$#result]->[1] $result[$#result]->[2]:$result[$#result]->[3]:$result[$#result]->[4]\n";
    print "Total events: $total\n";
    print "Signatures recorded: ". keys(%s4) ."\n";
    print "Source IP recorded: ". keys(%s5) ."\n";
    print "Destination IP recorded: ". keys(%s6) ."\n";
    print "Anomaly recorded: ". eval '$#anores +1'."\n";
  }
}

# to see the frequency of the attack from a certain pair of 
# host and destination
sub same_attack {
  if($opt_h) {
    print "<h3>The number of attack from same host to same destination using same method</h3>\n";
    print "<table>\n";
    print "<tr><th># of attacks</th><th>from</th><th>to</th><th>with</th</tr>";
    foreach $k (sort { $s0{$b} <=> $s0{$a} } keys %s0) { 
      @_ = split ":",$k;
      print "<tr><td>$s0{$k}</td><td>$_[1]</td><td>$_[0]</td>
             <td>$_[2]</td></tr>\n" if $s0{$k} >1;
    }
    print "</table><hr>\n";
  } else {
    section_header("The number of attacks from same host to same
destination using same method\n", "asdm");
    foreach $k (sort { $s0{$b} <=> $s0{$a} } keys %s0) { 
      @_ = split ":",$k;
      printf("   %-2d     %-${saddr_len}s   %-${daddr_len}s   %-20s\n",
	     $s0{$k},$_[1],$_[0],$_[2]) 
    }
  }
}

# to see the percentage and number of attacks from a host to a destination
sub same_host_dest {
  if($opt_h) {
    print "<h3>Percentage and number of attacks from a host to a destination</h3>\n";
    print "<table>\n";
    print "<tr><th>%</th><th># of attacks</th><th>from</th><th>to</th></tr>\n";
    foreach $k (sort { $s1{$b} <=> $s1{$a} } keys %s1) {
      @_ = split ":",$k;
      printf("<tr><td>%-2.2f</td><td>%-2d</td><td>%-20s</td><td>%-20s</td>
              <td>\n",$s1{$k}/$total*100,$s1{$k},$_[0],$_[1]) if $s1{$k} > 1;
    }
    print "</table><hr>\n";
  } else {
    section_header("Percentage and number of attacks from a host to a
destination\n", "pasd");  
    foreach $k (sort { $s1{$b} <=> $s1{$a} } keys %s1) {
      @_ = split ":",$k;
      printf("%5.2f    %-2d      %-${saddr_len}s   %-${daddr_len}s\n",
	     $s1{$k}/$total*100, $s1{$k},$_[0],$_[1]) 
    }
  }
}

# to see how many attacks launched from one host
sub same_host_sig {
  if ($opt_h) {
    print "<h3>Percentage and number of attacks from one host to any with same method</h3>\n";
    print "<table>\n";
    print "<tr><th>%</th><th># of attacks</th><th>from</th><th>type</th></tr>\n";
    foreach $k (sort { $s2{$b} <=> $s2{$a} } keys %s2) {
      @_ = split ":",$k;
      printf("<tr><td>%-2.2f</td><td>%-4d</td><td>%-20s</td><td>%-28s</td>
              </tr>\n",$s2{$k}/$total*100,$s2{$k},$_[1],$_[0]) if $s2{$k} > 1;
    }
    print "</table><hr>\n";
  } else { 
    section_header("Percentage and number of attacks from one host to any
with same method\n", "pasm");  
    foreach $k (sort { $s2{$b} <=> $s2{$a} } keys %s2) {
      @_ = split ":",$k;
      printf("%5.2f    %-4d    %-${saddr_len}s   %-28s\n",
	     $s2{$k}/$total*100, $s2{$k},$_[1],$_[0]) 
    }
  }
}

# to see how many attacks received by one host (destination correlated)
sub same_dest_sig_stat {
  if ($opt_h) {
    print "<h3>Percentage and number of attacks to one certain host</h3>\n";
    print "<table>\n";
    print "<tr><th>%</th><th># of attacks</th><th>to</th><th>type</th></tr>\n";
    foreach $k (sort { $s3{$b} <=> $s3{$a} } keys %s3) {
      @_ = split ":",$k;
      printf("<tr><td>%-2.2f</td><td>%-4d</td><td>%-25s</td><td>%-28s</td><td>\n",$s3{$k}/$total*100,$s3{$k},$_[1],$_[0]) if $s3{$k} > 1;
    }
    print "</table><hr>\n";
  } else {
    section_header("The percentage and number of attacks to one certain host \n", "padm");
    foreach $k (sort { $s3{$b} <=> $s3{$a} } keys %s3) {
      @_ = split ":",$k;
      printf("%5.2f    %-4d    %-${daddr_len}s  %-28s\n",$s3{$k}/$total*100 ,
	     $s3{$k},$_[1],$_[0]);
    }
  }
}

# to see the popularity of one attack method
sub attack_distribution {
  if($opt_h) {
    print "<h3>The distribution of attack methods</h3>\n";
    print "<table>\n";
    print "<tr><th>%</th><th># of attacks</th><th>methods</th></tr>\n";
    foreach $k (sort { $s4{$b} <=> $s4{$a} } keys %s4) {
      @_ = split ":",$k;
      printf("<tr><td>%-2.2f</td><td>%-4d</td><td>%-32s</td></tr>\n",
	     $s4{$k}/$total*100,$s4{$k},$_[0]);
    }
    print "</table><hr>\n";
  } else {
    section_header("The distribution of attack methods\n",
                   "pam");
    foreach $k (sort { $s4{$b} <=> $s4{$a} } keys %s4) {
      @_ = split ":",$k;
      printf("%5.2f    %-4d    %-32s\n",
	     $s4{$k}/$total*100,$s4{$k},$_[0]);
    }
  }
}

# portscan (if enable -p switch)
# Please use '-A fast' to generate the log, so portscan() can process it.
# contributed by: Paul Bobby, <paul.bobby@lmco.com>
#                 Jian-Da Li, <jdli@freebsd.csie.nctu.edu.tw>
sub portscan {
  my (%s5, %s6);
  # to see how many times a host performs portscan
  # used in portscan()
  for $i (0 .. $#res) {
    $s5{"$res[$i]->[0]"}++;
  }
  for $i (0 .. $#rescnt) {
    $s6{"$rescnt[$i]->[0]"} += $rescnt[$i]->[1];
  }
  if($opt_h) {
    print "<h3> Portscans performed to/from HOME_NET</h3>\n";
    print "<table>\n";
    print "<tr><th>Scan Attempts</th><th>Source Address</th><th>Number of Ports
</th></tr>\n";
    foreach $k (sort { $s5{$b} <=> $s5{$a} } keys %s5) {
      if ($s6{$k}) {
        print "<tr><td>$s5{$k}</td><td>$k</td><td>$s6{$k}</td></tr>\n";
      } else {
        print "<tr><td>$s5{$k}</td><td>$k</td><td>ERR</td></tr>\n";
      }
    }
    print "</table>\n";
  } else {
    format PORTSCAN_TOP =
    
Portscans performed to/from HOME_NET
=====================================
Times 	Source Address
=====================================
.
    $~ = PORTSCAN_TOP;
    write;
    
    foreach $k (sort { $s5{$b} <=> $s5{$a} } keys %s5) {
      printf(" %-4d    %-25s\n", $s5{$k},$k);
    }
  }
}

# anomsensor (if enable -n switch)
# This function process data generated by spp_anomsensor plug-in (SPADE)
# By Yen-Ming Chen <chenym@alumni.cmu.edu>
sub anomsensor {
  my (%s7);
  # to see how many times a host performs portscan
  # used in anomsensor()
  for $i (0 .. $#anores) {
    $s7{"$anores[$i]->[1],$anores[$i]->[3],$anores[$i]->[4]"}++;
  }
  if($opt_h) {
    print "<h3> Anomaly detected by SPADE</h3>\n";
    print "<table>\n";
    print "<tr><th>Scan Attempts</th><th>Source Address</th><th>Destination Address</th><th>Destination Ports</th></tr>\n";
    foreach $k (sort { $s7{$b} <=> $s7{$a} } keys %s7) {
      @_ = split(/,/,$k);
      print "<tr><td>$s7{$k}</td><td>$_[0]</td><td>$_[1]</td><td>$_[2]</td></tr>\n";
    }
    print "</table>\n";
  } else {
    format ANOMSENSOR_TOP =
    
Anomaly detected by SPADE
============================================================================
Attempts   Source Address      Destinatoin Address    Destination Ports
============================================================================
.
    $~ = ANOMSENSOR_TOP;
    write;
    foreach $k (sort { $s7{$b} <=> $s7{$a} } keys %s7) {
      @_ = split(/,/,$k);
      printf("   %-4d   %-25s %-25s %-6d\n", $s7{$k},$_[0],$_[1],$_[2]);
    }
  }
}

# print the footer (needed for html)
sub print_footer {
  if($opt_h) { 
    print "Generated by <a href=\"http://xanadu.incident.org/snort/\">snort_stat.pl</a>\n";
    print "</body>\n</html>\n";
  } 
}

#
# resolve host name and cache it
# contributed by: Angelos Karageorgiou, <angelos@stocktrade.gr>
# edited by: $Author: jpickel $
#
sub resolve {
  local ($mname, $miaddr, $mhost = shift);
  $miaddr = inet_aton($mhost);
  if (!$HOSTS{$mhost}) {
    $mname ="";
    eval {
      local $SIG{ALRM} = sub {die "alarm\n" }; # NB \n required
      alarm $timeout;
      $mname = gethostbyaddr($miaddr, AF_INET);
      alarm 0;
    };
    die if $@ && $@ ne "alarm\n";  # propagate errors
    if ($mname =~ /^$/) {
      $mname = $mhost;
    }
    $HOSTS{$mhost} = $mname;
  }
  return $HOSTS{$mhost};
}


# Use a title and a short code to write the section headers
# This is used in place of a FORMAT as this allows variable column widths
# contributed by: Ned Patterson, <jpatter@alum.mit.edu>
#
sub section_header {
  my $linelength;
  $title = shift; 
  $_ = shift;
  
  print("\n\n$title");
  
  # constant for method length for now
  $linelength = (/p/?7:0) + (/a/?10:0) + (/s/?$saddr_len:0) +
    (/d/?$daddr_len+3:0) + (/m/?20:0);
  print( '=' x $linelength, "\n");
  # print("Line length:\t$linelength\t\tHeaders:\t$_\n");
  print(" " x 7, " #  of\n")           if (/pa.*/);
  print("  # of\n attacks  ")          if (s/^a([sdm]*)/$1/);
  print("  %    ")                     if (s/^p([asdm]*)/$1/);
  print("attacks   ")                  if (s/^a([sdm]*)/$1/);
  printf("%-${saddr_len}s   ", "from") if (s/^s([dm]*)/$1/);
  printf("%-${daddr_len}s   ", "to"  ) if (s/^d(m*)/$1/);
  print("method")                      if (/^m/);
  print("\n");
  
  print( '=' x $linelength, "\n");
}


