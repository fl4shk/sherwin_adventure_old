#!/bin/bash

make disassemble_all_3 > disassembly_all_3.armasm && vimview-mate disassembly_all_3.armasm
