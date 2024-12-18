#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Numar insuficient de argumente"
    exit 1
fi

arg=$1

if [ ! -d $arg ]
then
	echo $arg "nu e director"
	exit 1
fi

find $arg -type f | while IFS= read -r file
do
	ln=$(echo $file | awk -F/ '{print $2}' | awk -F. '{print $1}' | wc -c)
	nume=$(echo $file | awk -F/ '{print $2}' | awk -F. '{print $1}')
	if [ $ln -lt 9 ]
	then
		echo "File:" $nume
		head -10 $file
	fi
done

exit 0
