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


# Utilizăm un while loop pentru a citi fiecare linie din fișier
while IFS= read -r line; do
    # Utilizăm awk pentru a căuta și afișa liniile care conțin un cuvânt repetat
	length=$(echo "$line" | wc -c)
	echo "$length"
done < "$1"

exit 0
