#!/bin/sh
datestring=`date -d today +%Y%m%d`

# the following lines are an example
# you have to intall the software sshpass and log on to the 172.16.16.234 as user sunyongjie at least one time using ssh
# copy file from local to 172.16.16.234 and change the name level2Quota.csv.20121119 to level2Quota.csv

/usr/local/bin/sshpass -p wangtian scp -P22 /home/sunyongjie/level2Quota.csv."$datestring" sunyongjie@172.16.16.234:"/home/sunyongjie/level2Quota"
