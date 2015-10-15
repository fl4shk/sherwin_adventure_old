.include "include/all_includes.s"

.macro .soft_break
	mov r11, r11
.endm


.org 0x00
.section ".startup","ax",%progbits
.align 2
@.arm
.do_arm

.global _start2

_start2:
	b next


.org 0x0100
.section ".startup","ax",%progbits
.align 2
.global next

.do_arm
next:
	@ Now we need to copy the code that goes in IWRAM to IWRAM
	@ We will use the memcpy32 from Tonc function that is --IN ROM-- to copy the memcpy32 from Tonc function to IWRAM (kind of ironic or something, isn't it?).
	ldr r0, =iwram_code_iwram_start			@ destination
	ldr r1, =iwram_code_rom_start	@ source
	ldr r2, =iwram_code_size		@ \ word count
	lsr r2, #0x02					@ / 
	
	
	@ Branch to the memcpy32 function that is --IN ROM-- and use that to copy the .iwram_code section to IWRAM.
	ldr r4, =memcpy32
	ldr r5, =iwram_code_iwram_start
	
	@.soft_break
	
	sub r6, r4, r5
	
	ldr r5, =iwram_code_rom_start
	add r6, r5
	@bx_afa r4
	
@.Lnext_infin:
	@.soft_break
	@b .next_infin_asdf_asdf
	@b .Lnext_infin
	
	mov lr, pc
	bx r6
	
	
	
	@ Now we will use the memcpy32 function that is in IWRAM to copy the .ewram_code section to EWRAM.
	ldr r0, =ewram_code_ewram_start			@ destination
	ldr r1, =ewram_code_rom_start	@ source
	ldr r2, =ewram_code_size		@ \ word count
	lsr r2, #0x02					@ / 
	
	@ Branch to the memcpy32 function that is in IWRAM and use it to copy the .ewram_code section to EWRAM.
	@ldr r4, =memcpy32
	@bx_afa r4
	
	@ r4 still contains the address of memcpy32 in IWRAM (horray for stack
	@ manipulation)
	mov lr, pc
	bx r4
	
	
	
	@ Copy the MaxMOD code to IWRAM
	ldr r0, =maxmod_code_iwram_start	@ destination
	ldr r1, =maxmod_code_rom_start		@ source
	ldr r2, =maxmod_code_size			@ \ word count
	lsr r2, #0x02						@ /
	
	@ r4 still contains the address of memcpy32 in IWRAM (horray for stack
	@ manipulation)
	mov lr, pc
	bx r4
	
	
	@ Clear the .bss section (Fill with 0x00)
.Lclear_bss:
	ldr r0, =__bss_start__
	ldr r2, =__bss_end__
	
	@ Compute the size of the .bss section in bytes.  This is the word
	@ count, multiplied by 4.
	sub r2, r2, r0
	
	@ Compute the word count.
	lsr r2, #0x02
	
	@ The .bss section is to be filled with 0x00
	@@mvn r1, #0x01
	mov r1, #0x00
	@ldr r1, silly_string
	
	
	ldr r4, =memfill32
	mov lr, pc
	bx r4
	
	
	
	
	
@ Now it's time to copy the initialized .data section from ROM to EWRAM
.Lcopy_initialized_data_from_rom_to_ewram:
	
	@ __data_start is the destination address, in EWRAM
	ldr r0, =__data_start
	
	@ __data_load is the source address, in ROM
	ldr r1, =__data_load
	
	@ __data_end is the final address of the .data section, in EWRAM
	ldr r2, =__data_end
	
	@ Compute the size of the .data section, in bytes.
	sub r2, r2, r0
	
	@ Compute the wdcount parameter of memcpy32
	lsr r2, #0x02
	
	@ Branch to the memcpy32 function.  It is indeed in IWRAM.
	ldr r3, =memcpy32
	mov lr, pc
	bx r3
	
	
@ Now it's time to copy the initialized .iwram_data section from ROM to 
@ IWRAM
.Lcopy_initialized_iwram_data_from_rom_to_iwram:
	
	@ __iwram_data_start is the destination address, in IWRAM
	ldr r0, =__iwram_data_start
	
	@ __iwram_data_load is the source address, in ROM
	ldr r1, =__iwram_data_load
	
	@ __iwram_data_end is the final address of the .data section, in IWRAM
	ldr r2, =__iwram_data_end
	
	@ Compute the size of the .iwram_data section, in bytes.
	sub r2, r2, r0
	
	@ Compute the wdcount parameter of memcpy32
	lsr r2, #0x02
	
	@ Branch to the memcpy32 function.  It is indeed in IWRAM.
	ldr r3, =memcpy32
	mov lr, pc
	bx r3
	
	
	
.Lcopy_init_array_section_from_rom_to_ewram:
	ldr r0, =__init_array_start
	ldr r1, =__init_array_load
	ldr r2, =__init_array_end
	sub r2, r2, r0
	lsr r2, #0x02
	
	ldr r3, =memcpy32
	mov lr, pc
	bx r3
	
	
	
	
	
	@@ Call the global C++ constructors
	ldr r3, =__libc_init_array
	
	mov lr, pc
	bx r3
	
	
	
	ldr r0, =asm_main + 1
	bx r0


@silly_string:
@	.ascii "olo_"


.ltorg
.align 2


.section ".rodata","ax",%progbits
.align 2
.global div_table
div_table:  
	.incbin "lookup_tables/table_for_1_divided_by_x_where_x_is_a_16-bit_unsigned_integer_greater_than_or_equal_to_2_--_also_each_value_in_the_table_is_a_32-bit_fixed_point_number_where_all_32_bits_are_fractional_bits.bin"


@ For kicks, I am throwing in the size of the division table (in bytes).
.equ div_table_size, . - div_table


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




@.section ".asm_text","ax",%progbits
.text
.align 2
.do_thumb
.thumb_func

.global asm_main
.type asm_main function

asm_main:
	bl main
	
.Lasm_main_infin:
	b .Lasm_main_infin



