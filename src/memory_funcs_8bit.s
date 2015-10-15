.include "include/all_includes.s"

@ void memcpy8 ( void* dst, const void* src, uint bytecount ) 
@	__attribute__ ((_iwram_code));
@ 
@ r0, r1:  dst, src
@ r2:  bytecount
@ r3:  temporary storage


.section .iwram_code,"ax", %progbits
.align 2
.do_arm
.global memcpy8
.type memcpy8, %function

memcpy8:
	.fnstart
	
	ldrb r3, [r1], #1
	strb r3, [r0], #1
	subs r2, r2, #1
	bne memcpy8
	
	bx lr
	
	.fnend






@ void memfill8 ( void* dst, u8 src, uint bytecount ) 
@	__attribute__ ((_iwram_code));
@ 
@ r0, r1:  dst, src
@ r2:  bytecount

.section .iwram_code,"ax", %progbits
.align 2
.do_arm
.global memfill8
.type memfill8, %function

memfill8:
	.fnstart
	
	strb r1, [r0], #1
	subs r2, r2, #1
	bne memfill8
	
	bx lr
	.fnend




