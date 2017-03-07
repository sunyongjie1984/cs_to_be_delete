#!/bin/sh

pids=`ps -ef |grep "mcastserver" | grep -v "grep" | grep -v "stop" | awk '{ print $2 }'`
for pid in $pids
do
    kill -9 $pid
done

