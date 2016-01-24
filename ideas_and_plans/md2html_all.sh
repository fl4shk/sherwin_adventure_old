#!/bin/bash

for file in *.md
do
	markdown "$file" > "${file%%.*}.html"
done

