#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insufiecent de argumente"
	exit 1
fi

if [ ! -f $1 ]
then
	echo "Nu e fisier"
	exit 1
fi

linie_max=""
lm=0
while IFS= read -r linie
do
	length=$(echo "$linie" | wc -c)
	if [ $length -gt $lm ]
	then
		lm=$length
		linie_max="$linie"
	fi
done < $1

echo "$linie_max cu $lm caractere"

exit 0
