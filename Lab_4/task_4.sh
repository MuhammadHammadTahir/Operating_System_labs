#!/bin/zsh
echo "My name is Muhammad Hammad Tahir and time is $(date)"
i=0
while IFS= read -r line   
do
	words=$(wc -w <<<"$line")
	echo "Words in Line $i = $words"
	((i++))
	newline="${line//o/a}"
	echo $newline >> new_file.txt
done < me

