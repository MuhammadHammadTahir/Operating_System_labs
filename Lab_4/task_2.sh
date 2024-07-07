#!/bin/zsh
rand=$(((RANDOM%20)+1))
echo "My name is Muhammad Hammad Tahir and time is $(date)"
while true
do
	echo "Enter a number between 1 to 20 :"
	read num
	if [ $rand -eq $num ]
	then
		echo "Congratulation!!! You guess the correct number"
		break
	else
		echo "Sorry!!! Try again"
	fi
done
