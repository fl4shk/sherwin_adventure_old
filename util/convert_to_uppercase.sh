#!/bin/bash

orig="$1"
converted=$(echo "$orig" | sed -e 's/\(.*\)/\U\1/')

temp='s/'"$orig"'/'"$converted"'/g'

echo "Using this:  \"$temp\""

find . -type f -print0 | xargs -0 sed -i "$temp"
