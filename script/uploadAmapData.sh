#!/bin/bash

dir=/uploadDir
tableid=xxxxxxx
key=xxxxx

for i in `ls data*.csv`
do
echo -n "$i "
curl -F "file=@${dir}/$i" http://yuntuapi.amap.com/datamanage/data/batchcreate\?key\=$key\&tableid\=$tableid\&_name\=name\&loctype\=1\&_address\=address\&longitude\=longitude\&latitude\=latitude
echo " "
sleep 60
done
#exit

