#!/bin/bash

echo "Enter the file name :"
read filename

if [ -e $filename ]
then
	echo "File exist"
	 stat -c %y $filename
else
	echo "File doesn't exist"
fi
