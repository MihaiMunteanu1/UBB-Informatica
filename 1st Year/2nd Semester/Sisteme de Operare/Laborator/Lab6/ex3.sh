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

# Calculăm numărul de vocale și consoane
vowels=$(grep -o -i "[aeiou]" "$1" | wc -l)
consonants=$(grep -o -i "[!aeiou]" "$1" | wc -l)

# Afișăm rezultatele
echo "Numărul de vocale din $1 este: $vowels"
echo "Numărul de consoane din $1 este: $consonants"

exit 0
