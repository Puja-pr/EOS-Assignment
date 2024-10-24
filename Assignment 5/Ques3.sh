#!/bin/bash

echo "Enter the file name:"
read path

if [ -e $path ] 
then
	if [ -d $path ] 
	then
		echo "File is Directory"

	elif [ -f $path ] 
	then
		echo "Regular file"
		if [ -x $path ]
		then
			echo "File is executable"
		fi
	fi
else
	echo "File doesn't exist"
fi
