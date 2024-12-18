#!/bin/awk

{
	linii[NR] = $0
}
END {
	for ( i = NR; i > 0; i--)
		print linii[i]
}
