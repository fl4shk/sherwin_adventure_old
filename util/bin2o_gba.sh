#!/bin/bash
bin2s "$1" | arm-none-eabi-as -o "$1".o
