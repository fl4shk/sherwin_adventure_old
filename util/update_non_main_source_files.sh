#!/bin/bash

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
bash -c "rsync -avuh --progress --existing \
	--exclude=\"$second_script\" \
	$most_rsync_args \
	\"$1\"/ ."

echo "Running \"$second_script\""
$($second_script)
