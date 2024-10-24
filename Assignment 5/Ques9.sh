#!/bin/bash

echo "Enter the number :"
read n
i=1
fact=1
if [ $n -le 0 ]
then
	echo "Factorial of negative no does not exist"
else
	while [ $i -le $n ]
	do	
		fact=`expr $fact \* $i`
		i=`expr $i + 1`
	done
	
fi

echo "Factorial of number = $fact"
	
