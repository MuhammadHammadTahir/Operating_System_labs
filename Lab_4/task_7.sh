#!/bin/zsh
table() {
touch table.txt
table_file=table.txt
echo "Table of $1 : ">> $table_file
i=1
while [ $i -le 10 ]
do
	echo " $1 x $i = $(($1 * $i)) ">>$table_file
	(( i++ ))
done
echo "$table_file"
}
echo "My name is Muhammad Hammad Tahir and time is $(date)"
echo "Enter the file to read : "
read file
if [ -f $file ]
then
	i=0
	while IFS= read -r line 
	do
		if [ $line -eq 32 ]
		then
			i=1
			break
		fi
	done<$file
	if [ $i -eq 1 ]
	then
		new_file=$( table $line )
		cat $new_file
	else
		echo "Last 2 digits of your registration numbers are not found in the file"
	fi 
else
	echo "!!!File not found!!!"
fi

