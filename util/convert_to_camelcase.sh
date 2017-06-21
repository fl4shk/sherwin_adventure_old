#!/bin/bash

function convert
{
	orig="$1"
	orig_modded='\<'"$orig"'\>'
	converted=$(echo "$orig" | sed -r 's/(^|_)([a-z])/\U\2/g')

	temp='s/'"$orig_modded"'/'"$converted"'/g'

	echo "Using this:  \"$temp\""

	find . -type f -print0 | xargs -0 sed -i "$temp"
}

for a in "$@"
do
	convert "$a"
done
