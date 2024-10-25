#!/bin/bash

read -p "Enter the first file name: " file1
read -p "Enter the second file name: " file2
echo
echo "Contents of file-1 :"
cat "$file1"
echo "Contents of file-2 :"
cat "$file2"
echo
tr 'a-zA-Z' 'A-Za-z' < "$file1" >> "$file2"

echo "Appended Contents of file-2 :"
cat "$file2"
