#!/bin/bash

orig="$1"
orig_modded='\<'"$orig"'\>'
converted=$(echo "$orig" | sed -e 's/\(.*\)/\U\1/')

temp='s/'"$orig_modded"'/'"$converted"'/g'

echo "Using this:  \"$temp\""

find . -type f -print0 | xargs -0 sed -i "$temp"
