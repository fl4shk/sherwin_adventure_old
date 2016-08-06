#!/bin/bash

first_dir=$(realpath $1)
second_dir=$(realpath $2)

echo "$first_dir"
echo "$second_dir"

#echo
#echo

cd "$first_dir"
first_list=($(find "src" -type d -exec echo {} +))


cd "$second_dir"
second_list=($(find "src" -type d -exec echo {} +))

banned_dir="src"


shared_src_dirs=()
for val_i in "${first_list[@]}"
do
	for val_j in "${second_list[@]}"
	do
		if [[ "$val_i" == "$banned_dir" ]] 
		then
			break
		elif [[ "$val_i" == "$val_j" ]]
		then
			shared_src_dirs+=("$val_i")
			break
		fi
	done
done

echo ${shared_src_dirs[@]}
