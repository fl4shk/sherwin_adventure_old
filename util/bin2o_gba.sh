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


if [ ! -d "$DEVKITARM" ]
then
	echo 'Please set $DEVKITARM in your environment'
	echo "Exiting...."
	exit 1
fi

#$DEVKITARM/bin/bin2s "$1" | $DEVKITARM/bin/arm-none-eabi-as -o "$1".o
$DEVKITARM/bin/bin2s "$1" | $DEVKITARM/bin/arm-none-eabi-as -o "$2"
