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


@; Here are some macros for simulating something like the blx instruction
@; (assuming it does what I think it does in later versions of the ARM
@; ISA...  I'm not sure that I'm correct), which doesn't exist on the GBA's
@; ARM7TDMI processor.

@; BX to a Thumb mode function from Thumb mode
.macro bx_tft branch_reg:req temp_reg
.endm

@; BX to an ARM mode function from Thumb mode
.macro bx_aft branch_reg:req temp_reg
	.if in_thumb_mode
		.ifb \temp_reg		@; Whether \temp_reg has a value or not.
			@; Since \temp_reg is blank, we will use the stack.
			push { \branch_reg }
			mov \branch_reg, pc
			add \branch_reg, #.Lbx_to_func_temp_label\@ - . - 1
			mov lr, \branch_reg
			pop { \branch_reg }
			bx \branch_reg
		.Lbx_to_func_temp_label\@:
		.else
			@; Since \temp_reg ISN'T blank, we will use it instead of the
			@; stack.
			
			mov \temp_reg, pc
			add \temp_reg, #.Lbx_to_func_temp_label\@ - . - 1
			mov lr, \temp_reg
			bx \branch_reg
		.Lbx_to_func_temp_label\@:
		.endif
	.elseif in_arm_mode
		.error " Tried to use bx_to_func_thumb in ARM mode."
	.endif
.endm


@; BX to an ARM mode function from ARM mode
.macro bx_afa reg:req
	.if in_arm_mode
		mov lr, pc
		bx \reg
	.elseif in_thumb_mode
		.error " Tried to use bx_to_func_arm in Thumb mode."
	.endif
.endm


.macro .do_arm
	.ifdef in_thumb_mode
		.ifne in_thumb_mode
		@;	.print "I'm \"switching\" from Thumb mode to ARM mode!"
			.equ in_arm_mode, 1
		.else
		@;	.print "I'm already in ARM mode!"
		.endif
	.else
		@;.print "The in_thumb_mode symbol is not defined yet!"
		@;.print "I'm changing that now!"
		.equ in_arm_mode, 1
	.endif
	
	.equ in_thumb_mode, 0
	
	.arm
.endm


.macro .do_thumb
	.ifdef in_arm_mode
		.ifne in_arm_mode
		@;	.print "I'm \"switching\" from ARM mode to Thumb mode!"
			.equ in_thumb_mode, 1
		.else
		@;	.print "I'm already in Thumb mode!"
		.endif
	.else
		@;.print "The in_arm_mode symbol is not defined yet!"
		@;.print "I'm changing that now!"
		.equ in_thumb_mode, 1
	.endif
	
	.equ in_arm_mode, 0
	
	.thumb
.endm
