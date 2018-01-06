#!/bin/bash

# This file is part of Sherwin's Adventure.
# 
# Copyright 2015-2018 Andrew Clark (FL4SHK).
# 
# Sherwin's Adventure is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
# 
# Sherwin's Adventure is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.

#"--exclude=\".gitignore\""

ret=( "--exclude=\"README.md\""
	"--exclude=\".gdb_history\""
	"--exclude=\".git\""
	"--exclude=\"objs\""
	"--exclude=\"deps\""
	"--exclude=\"asmouts\""
	"--exclude=\"objs_dis\""
	"--exclude=\"*.armasm\""
	"--exclude=\"src/main.cpp\""
	"--exclude=\"src/tags\""
	"--exclude=\"src/*types_*.taghl\""
	"--exclude=\"tags\""
	"--exclude=\"*types_*.taghl\""
	"--exclude=\".*.swp\""
	"--exclude=\".*.swo\"" 
	"--exclude=\"util/convert_project_name_in_license.sh\"" )

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
