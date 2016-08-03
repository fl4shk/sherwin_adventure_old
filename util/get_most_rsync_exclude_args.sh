#!/bin/bash

ret=( "--exclude=\"README.md\""
	"--exclude=\".gitignore\""
	"--exclude=\".git\""
	"--exclude=\"objs\""
	"--exclude=\"deps\""
	"--exclude=\"asmouts\""
	"--exclude=\"objs_dis\""
	"--exclude=\"*.armasm\""
	"--exclude=\"src/main.thumb.cpp\""
	"--exclude=\"src/tags\""
	"--exclude=\"*types_*.taghl\""
	"--exclude=\"tags\""
	"--exclude=\"*types_*.taghl\""
	"--exclude=\".*.swp\""
	"--exclude=\".*.swo\"" )

echo ${ret[@]}


#echo --exclude=\"README.md\" \
#	--exclude=\".gitignore\" \
#	--exclude=\".git\" \
#	--exclude=\"objs\" \
#	--exclude=\"deps\" \
#	--exclude=\"asmouts\" \
#	--exclude=\"objs_dis\" \
#	--exclude=\"*.armasm\" \
#	--exclude=\"src/main.thumb.cpp\" \
#	--exclude=\"src/tags\" \
#	--exclude=\"*types_*.taghl\" \
#	--exclude=\"tags\" \
#	--exclude=\"*types_*.taghl\" \
#	--exclude=\".*.swp\" \
#	--exclude=\".*.swo\" \

#echo --exclude=\".git\"
