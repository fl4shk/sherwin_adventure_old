#!/bin/bash

nm $(basename $(pwd)).elf > symbols.txt && vimview-mate symbols.txt
