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



