#!/bin/bash


#rsync -avh --progress --dry-run --existing "$1"/src .
#rsync -avh --progress --dry-run --existing "$1"/src .
rsync -avuh --progress --exclude=".git" --exclude="src/main.thumb.cpp" \
	--exclude=".*.swp" --exclude=".*.swo" --existing "$1"/ .


find src -type f -exec sed -i 's/GBA Project Template/Sherwin'\''s Adventure/g' {} +


