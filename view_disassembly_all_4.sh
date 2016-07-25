#!/bin/bash

make disassemble_all_4 > disassembly_all_4.armasm && vimview-mate disassembly_all_4.armasm
