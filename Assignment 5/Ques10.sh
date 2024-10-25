#!/bin/bash

echo "Enter the number of terms  : "
read n
term1=1
term2=0
curr=0
i=1
if [ $n -lt 1 ]
then
	echo "Invalid number of terms"
else
	while [ $i -le $n ]
	do
	if [ $i -gt 2 ]
	then
		curr= `expr $term1 + $term2`
		term2 = term1
		term1 = curr
		echo "$curr"
	elif [ $i -eq 1 ]
	then
		echo "$term2"
	else
#	[ $i -eq 2 ]
		echo "$term1"
	fi


	done
	
	
fi
