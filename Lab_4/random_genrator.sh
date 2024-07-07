#!/bin/zsh
i=0
while (( i<100 ))
do
	rand=$(((RANDOM % 90)+10))
	echo "$rand"
	echo $rand >> numbers.txt
	((i++))
done
