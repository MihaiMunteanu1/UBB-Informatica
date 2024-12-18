#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Numar insuficient de argumente"
    exit 1
fi

for file in $*
do
	if [ ! -f $file ]
	then
		echo $file "nu e fisier"
		continue
	fi
	grep -v '^$' "$file" | sort | uniq -c | sort -nr | head -n 1
done

exit 0
