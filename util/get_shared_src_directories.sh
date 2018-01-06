#!/bin/bash

# This file is part of Sherwin's Adventure.
# 
# Copyright 2015-2018 Andrew Clark (FL4SHK).
# 
# Sherwin's Adventure is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
# 
# Sherwin's Adventure is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


first_dir=$(realpath $1)
second_dir=$(realpath $2)

#echo "$first_dir"
#echo "$second_dir"

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
