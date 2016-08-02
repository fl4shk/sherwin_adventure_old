#!/bin/bash

# Man I love the find program.

find . \( -path ./.git -o -path ./small_code_testing_things \
	-o -path ./deps -o -path ./objs -o -path ./asmouts \
	-o -path ./lookup_tables \
	\
	-o -iname "*.swp" -o -iname "*.swo" -o -iname "*.gdb_history*" \
	-o -path ./util/convert_project_name_in_license.sh \
	-o -iname "*tags" -o -iname "*types*.taghl" \
	-o -iname "*.gba" -o -iname "*.elf" \
	-o -iname "*README*" -o -iname "*COPYING*" \
	-o -iname "*linker_map.txt*" \
	\) -prune \
	\
	-o -type f \
	-exec sed -i 's/Sherwin'\''s Adventure/GBA Project Template/g' {} +
	#-print


