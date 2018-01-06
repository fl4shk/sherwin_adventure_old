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

.section ".iwram_code","ax",%progbits
.align 2
.do_arm
.global iwram_test_func
iwram_test_func:
	mov r0, #0x03000000
	bx lr

.section ".iwram_code","ax",%progbits
.align 2
.do_arm
.global iwram_test_func2
iwram_test_func2:
	mov r0, #0x9
	mov r1, #0x8
	add r0, r0, r1
	bx lr


.section ".ewram_code","ax",%progbits
.align 2
.do_thumb
.thumb_func
.global ewram_test_func
ewram_test_func:
	mov r0, #0x8f
	lsl r0, #0x4
	add r0, #0x5c
	lsr r0, #0x4
	bx lr



