#!/bin/bash
$DEVKITARM/bin/bin2s "$1" | $DEVKITARM/bin/arm-none-eabi-as -o "$1".o
