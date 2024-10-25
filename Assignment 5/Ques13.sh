#!/bin/bash

echo "Enter the path"
read $path

if [ -e $path ]
then
	echo "File exists"
	if [ -d $path ]
	then
		echo "it is a directory"
		ls -a | grep "^\."
	fi
else
	echo "File doesnt exist"
fi
