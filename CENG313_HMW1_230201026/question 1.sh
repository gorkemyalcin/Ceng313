#!/bin/bash
while line='' read -r line || [[ -n "$line" ]]; do #if there exists line while loop will work
	if [[ -n ${line//[0-9]/} ]]; then #if the read line is not an integer, print an error message
	    	printf "This line had non-integer values.\n"
	else
		eval "printf '*'%.0s {1..$line}" #if everything is working as intended print the value times stars.
	fi
done < "$1"
