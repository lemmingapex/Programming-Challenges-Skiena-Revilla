#!/bin/bash

N=300

echo -e "$N\n"
for i in `seq 1 $N`; do
	let M=($RANDOM%99)+1
	echo "$M"
	for j in `seq 1 $M`; do
		#echo "$j"
		let W=($RANDOM%449)+1
		echo "$W"
	done
	echo -e ""
done
