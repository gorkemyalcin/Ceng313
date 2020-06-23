#!/bin/bash
echo Enter a sequence of numbers followed by "end"
input="not end"
while true; do
    read max
    if [[ -n ${max//[0-9]/} ]] || [[ "$max" == "end" ]]; then #if the input is not and integer or the end string program will ask for the right input
    	echo "Please enter only integers"
    else
		break #if everything is working as intended we exit the while loop
    fi
done
while true; do
    read input
    if [[ ! -n ${input//[0-9]/} ]] || [[ "$input" == "end" ]]; then
    	if [ "$input" == "end" ]; then
	    break
	elif [ $input -gt $max ]; then #if the input is greater than the current max value we update the max value with the input.
	    max=$input
	fi
    else
		echo "Please enter only integers"
    fi
done
echo "Maximum is $max"
