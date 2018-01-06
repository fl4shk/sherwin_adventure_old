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


first_script=util/get_most_rsync_exclude_args.sh
second_script=util/convert_project_name_in_license.sh

function quit()
{
	echo "Exiting...."
	exit 1
}

function quit_if_script_missing()
{
	if [ ! -f "$1" ]
	then
		echo "\"$1\" does not appear to exist."
		quit
	elif [ ! -x "$1" ]
	then
		echo "\"$1\" does not appear to be executable."
		quit
	fi
}


if [ ! -d "$1" ]
then
	echo "\"$1\" does not appear to be a valid directory."
	quit
fi

quit_if_script_missing "$first_script"
quit_if_script_missing "$second_script"


most_rsync_args=$($first_script)


#rsync -avh --progress --dry-run --existing "$1"/src .
#rsync -avh --progress --dry-run --existing "$1"/src .
bash -c "rsync -avuh --progress --existing --dry-run \
	--exclude=\"$second_script\" \
	$most_rsync_args \
	\"$1\"/ ."

#echo $thing2
