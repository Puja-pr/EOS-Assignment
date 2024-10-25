#!/bin/bash

echo "Enter the file name:"
read path

if [ -e $path ] 
then
	if [ -d $path ] 
	then
		echo "File is Directory"
		-x $path
	fi
else
	echo "File doesn't exist"
fi
