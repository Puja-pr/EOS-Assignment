#!/bin/bash

i=1
while [ $i -le 5 ]
do
    j=1
    while [ $j -le $i ]
	do
        echo -n "* "
        j=$((j + 1))
    done
    echo
    i=$((i + 1))
done
