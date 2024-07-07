#!/bin/zsh
echo "My name is Muhammad Hammad Tahir and time is $(date)"
while true
do
	echo "Choose an option :\n1) Display list \n2)Create directory \n3)Exit"
	read op
	case $op in
		1)
		ls;;
		2)
		echo "Enter the directory name : "
		read name
		mkdir $name
		echo "!!!!!!!$name Directory is created!!!!!!";;
		3)
		exit 0;;
		*)
		echo "INVALID INPUT"
	esac
done


