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
suma=0
while IFS= read -r linie
do
	numere_valide=$(echo "$linie" | grep -oE '[0-9]+')
        for numar in $numere_valide; do
        	suma=$((suma + numar))
    	done
done < $1

echo "$suma"

exit 0
