@ This file is part of Sherwin's Adventure.
@ 
@ Copyright 2015-2018 Andrew Clark (FL4SHK).
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


@ Macros and defines for button (key) stuffs

@ The key registers (both 16-bit, as usual)
.equ reg_keyinput, 0x04000130
.equ reg_keycnt, 0x04000132


@ The individual key bitmasks
.equ key_a, 0x0001
.equ key_b, 0x0002
.equ key_select, 0x0004
.equ key_start, 0x0008
.equ key_right, 0x0010
.equ key_left, 0x0020
.equ key_up, 0x0040
.equ key_down, 0x0080
.equ key_r, 0x0100
.equ key_l, 0x0200


@ The key REGISTER bitmask
.equ key_mask, 0x03ff



@ Here is a macro for polling the keys.
@ It expects the addresses of key_prev_state and key_curr_state to be in r0 and r1, respectively.

.macro key_poll
	.if in_thumb_mode
		ldr r2, [r1]
		strh r2, [r0]
		ldrh r3, =key_mask
		
		
	.elseif in_arm_mode
		ldr r2, [r1]
		strh r2, [r0]
		ldrh r3, =key_mask
		
		
	.endif
.endm


