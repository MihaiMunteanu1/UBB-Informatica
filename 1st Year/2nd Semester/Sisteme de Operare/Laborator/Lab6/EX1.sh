#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente"
	exit 1
fi

if [ ! -f $1 ]
then
	echo "Nu e fisier"
	exit 1
fi

lines=()
while IFS= read -r line
do
	lines+=("$line")
done <$1

for (( i=${#lines[@]}-1; i>=0; i-- )); do
    echo "${lines[i]}"
done

exit 0
