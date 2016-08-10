#!/bin/bash
#find . -type f -iname "*.*pp" -exec vim {} +
find . -type f \( -iregex '.*\.thumb\.c' -o -iregex '.*\..*pp' -o -iregex '.*\.s' \) -exec vim {} +
