#!/bin/bash

#find whether a number is positive or negative

echo "Enter the number :"
read num

if [ $num -ge 0 ]
then
	echo "Number is positive : $num"
else
	echo "Number is negative "
fi
