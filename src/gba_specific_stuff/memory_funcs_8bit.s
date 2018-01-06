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

@ void memcpy8 (void* dst, const void* src, uint bytecount) 
@	__attribute__ ((_iwram_code));
@ 
@ r0, r1:  dst, src
@ r2:  bytecount
@ r3:  temporary storage


.section .iwram_code,"ax", %progbits
.align 4
.do_arm
.global memcpy8
.Type memcpy8, %function

memcpy8:
	.fnstart
	cmp r2, #0
	beq end_memcpy8

loop_memcpy8:
	ldrb r3, [r1], #1
	strb r3, [r0], #1
	subs r2, r2, #1
	bne loop_memcpy8

end_memcpy8:
	bx lr

	.fnend






@ void memfill8 (void* dst, u32 src, uint bytecount) 
@	__attribute__ ((_iwram_code));
@ 
@ r0, r1:  dst, src
@ r2:  bytecount

.section .iwram_code,"ax", %progbits
.align 4
.do_arm
.global memfill8
.Type memfill8, %function

memfill8:
	.fnstart
	cmp r2, #0
	beq end_memfill8

loop_memfill8:
	strb r1, [r0], #1
	subs r2, r2, #1
	bne loop_memfill8

end_memfill8:
	bx lr
	.fnend




