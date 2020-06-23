#!/bin/bash
echo "Please enter the directory that you want the 0 length files in it to be removed."
read directory
if [ "$directory" == "" ];then #if its not given
	find / -type f -size 0 -delete #it finds 0 size files and deletes them
	echo Zero-length files are removed from the current directory.
else
	find /$directory -type f -size 0 -delete #if the directory is given then it goes to the directory and does the removal.
	echo Zero-length files are removed from the directory:$directory
fi
