@ NOTE:  This memcpy32 function was taken from this site:
@ http://www.coranac.com/tonc/text/asm.htm I also JUST BARELY modified one
@ directive of it To work with my linkscript.  Thank you, J Vijn, for this
@ function!


@ === void memcpy32(void *dst, const void *src, uint wdcount) IWRAM_CODE; =============
@ r0, r1: dst, src
@ r2: wdcount, then wdcount>>3
@ r3-r10: data buffer
@ r12: wdn&7
    .section .iwram_code,"ax", %progbits
    .align  2
    .code   32
    .global memcpy32
    .Type   memcpy32 STT_FUNC
memcpy32:
	@mov r11, r11
    and     r12, r2, #7     @ r12= residual word count
    movs    r2, r2, lsr #3  @ r2=Block count
    beq     .Lres_cpy32
    push    {r4-r10}
    @ Copy 32byte chunks with 8fold xxmia
    @ r2 in [1,inf>
.Lmain_cpy32:
        ldmia   r1!, {r3-r10}   
        stmia   r0!, {r3-r10}
        subs    r2, #1
        bne     .Lmain_cpy32
    pop     {r4-r10}
    @ And the residual 0-7 words. r12 in [0,7]
.Lres_cpy32:
        subs    r12, #1
        ldrcs   r3, [r1], #4
        strcs   r3, [r0], #4
        bcs     .Lres_cpy32
    bx  lr







@ On the other hand, this memfill32 function Is a somewhat more modified
@ form of memcpy32 from TONC.

@ This function fills memory using stmia
@ === void memfill32(void* dst, u32 fillval, u32 wdcount) ===
@ == Input Registers ==
@ r0:  dst
@ r1:  fillval
@ r2:  wdcount
@ == Used Registers == 
@ r1:  residual word count
@ r2:  Block count (32 bytes, or 8 words, per Block)
@ r3-r10: data buffer

.section ".iwram_code","ax",%progbits
.align 2
.arm

.global memfill32
.Type memfill32, %function
memfill32:
	@mov r11, r11				@ This Is a no$gba soft breakpoint

	mov r3, r1
	and r1, r2, #0x07			@ r1 = residual word count
	movs r2, r2, lsr #0x03		@ r2 = Block count
	beq .Lres_fill32

	push {r4-r10}

	@ A bunch of moves
	mov r4, r3 ; mov r5, r3 ; mov r6, r3 ; mov r7, r3 ; 
	mov r8, r3 ; mov r9, r3 ; mov r10, r3


	@ Fill 32-byte chunks wth 8-fold stmia
	@ r2 in [1, inf>
.Lmain_fill32:
		stmia r0!, {r3-r10}
		subs r2, #0x01
		bne .Lmain_fill32

	pop {r4-r10}
	@ And the residual 0-7 words. r1 in [0,7]
.Lres_fill32:
		subs r1, #0x01
		strcs r3, [r0], #4
		bcs .Lres_fill32

	bx lr





