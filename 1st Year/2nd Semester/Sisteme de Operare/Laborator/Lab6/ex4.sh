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
    echo "$line" | awk '{
        for (i=1; i<=NF; i++) {
            for (j=i+1; j<=NF; j++) {
                if ($i == $j) {
                    print;
                    next;
                }
            }
        }
    }'
done < "$1"

exit 0
