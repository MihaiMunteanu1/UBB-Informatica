#!/bin/bash

# I FIELD SEPARATOR ( nu rupe linia numa cand se termina) , inainte de exit trebuie restaurat IFS
while IFS= read -r LINIE
do
	echo "$LINIE"
done <$1

