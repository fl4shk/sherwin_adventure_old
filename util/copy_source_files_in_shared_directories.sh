#!/bin/bash

first_script=util/get_most_rsync_exclude_args.sh
second_script=util/convert_project_name_in_license.sh
third_script=util/get_shared_src_directories.sh

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
quit_if_script_missing "$third_script"


most_rsync_args=$($first_script)
shared_src_dirs=($("$third_script" . "$1"))

##rsync -avh --progress --dry-run --existing "$1"/src .
##rsync -avh --progress --dry-run --existing "$1"/src .
##bash -c "rsync -avuh --progress --existing \
##	--exclude=\"$second_script\" \
##	$most_rsync_args \
##	\"$1\"/ ."
#

for dir in "${shared_src_dirs[@]}"
do
	bash -c "rsync -avuh --progress \
		--exclude=\"$second_script\" \
		\"$1\"/\"$dir\"/ ."
done

echo "Running \"$second_script\""
$($second_script)
