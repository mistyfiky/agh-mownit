#!/usr/bin/env bash
a=0
b=1
for s in 10 100 1000 10000 100000 1000000
do
    for n in $(seq ${s} ${s} $((${s} * 10 - 1)))
	do
	    echo -e ${n}"\t"$(./zad2 ${a} ${b} ${n} | tail -1)
	done
done
