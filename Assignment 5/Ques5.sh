#!/bin/bash
echo -e -n "Enter num1 :"
read n1
echo -e -n "Enter num2 :"
read n2
echo -e -n "Enter num3 :"
read n3

if [ $n1 -gt $n2 ]
then
	if [ $n1 -gt $n3]
	then
		echo "Num1 is greatest : $n1"
	else
		echo "Num3 is greatest : $n3"
	fi
else
	if [ $n2 -gt $n3 ]
	then
		echo "Num2 is greatest : $n2"
	else
		echo "Num3 is greatest : $n3"
	fi
fi

