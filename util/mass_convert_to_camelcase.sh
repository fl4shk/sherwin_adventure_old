#!/bin/bash

for a in "$@"
do
	./convert_to_camelcase.sh "$a"
done
