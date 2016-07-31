#!/bin/bash

second_script=./util/convert_project_name_in_license.sh

function quit()
{
	echo "Exiting...."
	exit 1
}

if [ ! -d "$1" ]
then
	echo "\"$1\" does not appear to be a valid directory."
	quit
elif [ ! -f "$second_script" ]
then
	echo "\"$second_script\" does not appear to exist."
	quit
elif [ ! -x "$second_script" ]
then
	echo "\"$second_script\" does not appear to be executable."
	quit
fi

#rsync -avh --progress --dry-run --existing "$1"/src .
#rsync -avh --progress --dry-run --existing "$1"/src .
rsync -avuh --progress \
	--exclude="$second_script" \
	--exclude="README.md" \
	--exclude=".git" \
	--exclude="src/main.thumb.cpp" \
	--exclude="src/tags" --exclude="*types_*.taghl" \
	--exclude="tags" --exclude="*types_*.taghl" \
	--exclude=".*.swp" --exclude=".*.swo" \
	--existing "$1"/ .

echo "Running \"$second_script\""
$($second_script)
