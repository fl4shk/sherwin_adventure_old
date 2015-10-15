.include "include/all_includes.s"

.section ".iwram_code","ax",%progbits
.align 2

@ --Input Registers--
@ r0 = numerator
@ r1 = divisor (16-bit and not 0 or 1)
@ --Output Registers--
@ r0, r1 = 64-bit return value (in umull's order)
@ --Scratch Registers (NOT Saved)--
@ r2, r3
@ 
@ Note that this function DOESN'T check whether the divisor has a
@ corresponding LUT value, other than when the divisor has a value of 0 or
@ 1.
@ However, this function DOES subtract 2 and shift left by 2


.do_arm
.global lut_udiv
.type lut_udiv, %function
lut_udiv:
	.fnstart
	cmp r1, #0x01
	bgt .Llut_udiv_continue
	mov r1, #0x00
	bx lr
	
.Llut_udiv_continue:
	@ r2 and r3 are scratch registers
	mov r2, r0
	mov r3, r1
	
	sub r3, #0x02		@ Subtract by two to index the table
	lsl r3, #0x02		@ Multiply by four for the same reason (the table consists of 32-bit values, not 8-bit ones!)
	
	ldr r0, =div_table		@ \ Temporarily use r0
	ldr r3, [r0, r3]		@ / 
	
	umull r0, r1, r2, r3
	
	bx lr
	
	.fnend


.align 2
.ltorg




