#!/bin/bash

outputfile="input2";

i=0; 
n=20;
echo -e "1\n" > $outputfile;
echo ${n} >> $outputfile;
while [ $i -lt $n ] ; do 
	x=`echo "scale=1; ($[RANDOM%2000]/10)-100;" | bc`; 
	y=`echo "scale=1; ($[RANDOM%2000]/10)-100;" | bc`; 
	echo ${x}" "${y} >> $outputfile; 
	let i=i+1; 
done;

