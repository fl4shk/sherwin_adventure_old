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


