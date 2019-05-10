#!/usr/bin/env bash
for n in 10 25 50 75 100 250 500 750 875 1000
do
    echo -e ${n}"\t"$(./zad ${n} 2>/dev/null | tr '\n' '\t')
done
