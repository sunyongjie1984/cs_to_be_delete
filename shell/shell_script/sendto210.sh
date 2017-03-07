#!/bin/sh
datestring=`date -d today +%Y%m%d`
#datestring=`date -d '-2 day' +%Y%m%d`
/usr/local/bin/sshpass -p wangtian scp -P22 /home/sunyongjie/tmp.txt root@172.16.16.234:"/home/sunyongjie"$datestring"a.csv"
/usr/local/bin/sshpass -p wangtian scp -P22 /home/sunyongjie/tmp.txt root@172.16.16.234:"/home/sunyongjie"$datestring"b.csv"
