#!/bin/zsh
echo "My name is Muhammad Hammad Tahir and time is $(date)"
add_num() {
	local sum=$(( $1 + $2 ))  #spaces are important in syntax
	return $sum
}
subtract_num() {
	local sub=$(( $1 - $2 ))
        return $sub
}
multiply_num() {
	local mul=$(( $1 * $2 ))
        return $mul
}
divide_num() {
	local div=$(( $1 / $2 ))
        return $div
}
echo "Enter the first number : "
read num1
echo "Enter the second number : "
read num2
echo "Choose an operation :\n1)Addtion\n2)Subtraction\n3)Multiply\n4)Divide"
read op
case $op in
	1)
		add_num $num1 $num2
		echo "Addition of $num1 and $num2 = $?";; # $? holds the satus or result of last executed command
	2)
		subtract_num $num1 $num2
                echo "Subtraction of $num1 and $num2 = $?";;

	3)
		multiply_num $num1 $num2
                echo "Multiplication of $num1 and $num2 = $?";;

	4)
		divide_num $num1 $num2
                echo "Division of $num1 and $num2 = $?";;

esac
