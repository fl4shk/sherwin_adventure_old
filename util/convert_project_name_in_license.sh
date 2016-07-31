#!/bin/bash

# Man I love the find program.

find . -type d \( -path ./.git -o -path ./small_code_testing_things \
	-o -path ./deps -o -path ./objs -o -path ./asmouts \) -prune \
	\
	-type f -path ./util/convert_project_name_in_license.sh -prune \
	\
	-type f \
	-exec sed -i 's/GBA Project Template/Sherwin'\''s Adventure/g' {} +
