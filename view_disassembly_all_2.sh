#!/bin/bash

make disassemble_all_2 > disassembly_all_2.armasm && vimview-mate disassembly_all_2.armasm
