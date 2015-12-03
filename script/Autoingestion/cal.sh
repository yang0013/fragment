#!/bin/bash

# date=$(date -v -2d "+%Y%m%d")
date=$(date -d"-2 days" "+%Y%m%d")
cd /scriptDir/Autoingestion

# 下载统计数据
vendor=11101024
echo $date
/usr/local/jdk1.7.0_55/bin/java Autoingestion autoingestion.properties "$vendor" Sales Daily Summary "$date"

file="S_D_${vendor}_$date.txt"
gzip -d $file.gz
awk -F'\t' 'BEGIN{s1=0;s7=0}{if(NR>1) {if($7==1)s1+=$8;if($7==7)s7+=$8} }END{print "下载: "s1"\n更新: "s7}' $file >"$date.txt"
[ $? -eq 0 ] && /usr/bin/python sendmail.python $date
rm "$date.txt"
