#!/bin/zsh
echo "My name is Muhammad Hammad Tahir and time is $(date)"
is_even() {
if ((($1%2) == 0))
then
	return 0
else
	return 1
fi
}
echo "Enter a Number : "
read num
if is_even $num
then
	echo "The entered number is EVEN Number"
else
	echo "The entered number is ODD Number"
fi

