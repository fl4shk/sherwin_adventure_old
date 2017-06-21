#!/bin/bash

orig="$1"
converted=$(echo "$orig" | sed -r 's/(^|_)([a-z])/\U\2/g')

temp='s/'"$orig"'/'"$converted"'/g'

echo "Using this:  \"$temp\""

find . -type f -print0 | xargs -0 sed -i "$temp"
