#!/bin/bash
#find . -type f -iname "*.*pp" -exec vim {} +
find . -type f \( -iregex '.*\..*pp' -o -iregex '.*\.s' \) -exec vim {} +
