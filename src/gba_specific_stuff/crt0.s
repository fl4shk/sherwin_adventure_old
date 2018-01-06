@ This file is part of Sherwin's Adventure.
@ 
@ Copyright 2015-2018 by Andrew Clark (FL4SHK).
@ 
@ Sherwin's Adventure is free software: you can redistribute it and/or
@ modify it under the terms of the GNU General Public License as published
@ by the Free Software Foundation, either version 3 of the License, or (at
@ your option) any later version.
@ 
@ Sherwin's Adventure is distributed in the hope that it will be useful,
@ but WITHOUT ANY WARRANTY; without even the implied warranty of
@ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
@ General Public License for more details.
@ 
@ You should have received a copy of the GNU General Public License along
@ with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


.include "include/all_includes.s"

.macro .soft_break
	mov r11, r11
.endm

.macro long_call_via_r4_fata func_addr
	ldr r4, =\func_addr
	mov lr, pc
	bx r4
.endm

.macro long_call_via_r4_fatt func_addr
	ldr r4, =\func_addr + 1
	mov lr, pc
	bx r4
.endm

.macro long_call_via_r4_fata_type_2
	mov lr, pc
	bx r4
.endm

.macro long_call_via_r6_fata_type_2
	mov lr, pc
	bx r6
.endm


.org 0x00
.section ".startup","ax",%progbits
.align 2
@.arm
.do_arm

.global _start2

_start2:
	b next

@.global _start
@
@_start:
@	b next




.org 0x0100
.section ".startup","ax",%progbits
.align 2
.global next

.do_arm
next:
	@@ Now we need To copy the code That goes in IWRAM To IWRAM
	@@ We will use the memcpy32 from Tonc function That Is --IN ROM-- To copy the memcpy32 from Tonc function To IWRAM (kind of ironic or something, isn't it?).


	@ Now we need To copy the code That goes in IWRAM To IWRAM
	ldr r0, =iwram_code_iwram_start			@ destination
	ldr r1, =iwram_code_rom_start			@ source
	ldr r2, =iwram_code_section_size		@ byte count



	@ Branch To the slower_memcpy() function That Is --IN ROM-- and use
	@ THAT To copy the .iwram_code section To IWRAM.

	long_call_via_r4_fatt slower_memcpy




	@ Now we will use the memcpy function That Is in IWRAM To copy the .ewram_code section To EWRAM.
	ldr r0, =ewram_code_ewram_start			@ destination
	ldr r1, =ewram_code_rom_start	@ source
	ldr r2, =ewram_code_section_size		@ byte count

	@ Branch To the memcpy function That Is in IWRAM and use it To copy the .ewram_code section To EWRAM.
	long_call_via_r4_fata memcpy



	@ Copy Some of the MaxMOD code To IWRAM
	ldr r0, =some_maxmod_code_iwram_start	@ destination
	ldr r1, =some_maxmod_code_rom_start		@ source
	ldr r2, =some_maxmod_code_section_size			@ byte count


	@ r4 still Contains the address of memcpy in IWRAM (horray for stack
	@ manipulation)
	long_call_via_r4_fata_type_2


.L_copy_text_hot_code_to_iwram:
	ldr r0, =text_hot_iwram_start
	ldr r1, =text_hot_rom_start

	ldr r2, =text_hot_section_size
	long_call_via_r4_fata_type_2

.L_done_copying_text_hot_to_iwram:


	@ Clear the .bss section (Fill with 0x00)
.L_clear_bss:
	ldr r0, =__bss_start__
	ldr r2, =__bss_end__

	@ Compute the size of the .bss section in bytes.
	sub r2, r2, r0

	@ The .bss section Is To be filled with 0x00
	mov r1, #0x00


	long_call_via_r4_fata memset




@ Now it's time To copy the initialized .data section from ROM To EWRAM
.L_copy_initialized_data_from_rom_to_ewram:

	@ __data_start Is the destination address, in EWRAM
	ldr r0, =__data_start

	@ __data_load Is the source address, in ROM
	ldr r1, =__data_load

	@ __data_end Is the final address of the .data section, in EWRAM
	ldr r2, =__data_end

	@ Compute the size of the .data section, in bytes.
	sub r2, r2, r0


	@@ Compute the wdcount parameter of memcpy32
	@lsr r2, #0x02

	@@ Branch To the memcpy32 function.  It Is indeed in IWRAM.
	@ldr r3, =memcpy32


	@ Branch To the memcpy function.  It Is indeed in IWRAM.
	@ldr r4, =memcpy
	@mov lr, pc
	@bx r4
	long_call_via_r4_fata memcpy


@ Now it's time To copy the initialized .iwram_data section from ROM To 
@ IWRAM
.L_copy_initialized_iwram_data_from_rom_to_iwram:

	@ __iwram_data_start Is the destination address, in IWRAM
	ldr r0, =__iwram_data_start

	@ __iwram_data_load Is the source address, in ROM
	ldr r1, =__iwram_data_load

	@ __iwram_data_end Is the final address of the .data section, in IWRAM
	ldr r2, =__iwram_data_end

	@ Compute the size of the .iwram_data section, in bytes.
	sub r2, r2, r0

	@@ Compute the wdcount parameter of memcpy32
	@lsr r2, #0x02


	@ Branch To the memcpy function.  It Is indeed in IWRAM.
	long_call_via_r4_fata_type_2


.L_copy_init_array_section_from_rom_to_ewram:
	ldr r0, =__init_array_start
	ldr r1, =__init_array_load
	ldr r2, =__init_array_end
	sub r2, r2, r0
	long_call_via_r4_fata_type_2


.L_call_the__libc_init_array:
	@@ Call the global C++ constructors
	@ldr r4, =__libc_init_array
	@mov lr, pc
	@bx r4
	long_call_via_r4_fata __libc_init_array


.L_branch_to_asm_main:
	@ Switch To THUMB mode.
	ldr r0, =asm_main + 1
	bx r0



.ltorg
.align 2


.section ".rodata"
.align 2
.global udiv_table
udiv_table:  
	.incbin "lookup_tables/unsigned_one_slash_x_lut_65536_entries_of_0p32.bin"


.global sdiv_table
sdiv_table:  
	.incbin "lookup_tables/signed_one_slash_x_lut_65536_entries_of_0p32.bin"

@ A lookup table for sine where there are 512 degrees in a circle and
@ where the values stored in the LUT are of the fixed-point format 4.12 
.global sin_table
sin_table:
	.incbin "lookup_tables/sine_lut_512_entries_of_4p12.bin"

.equ sin_table_size, . - sin_table



.section ".startup","ax",%progbits
.align 2
.do_arm
_blx_r3_stub:
	bx r3




.section ".asm_text","ax",%progbits
@.text
.align 2
.do_thumb
.thumb_func

.global asm_main
.Type asm_main function

asm_main:
	bl main

.L_asm_main_infin:
	b .L_asm_main_infin



