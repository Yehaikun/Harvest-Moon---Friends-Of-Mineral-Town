	.INCLUDE "asm/macro.inc"
	.SYNTAX UNIFIED

	thumb_func_start memcpy
memcpy: @ 0x080D3994
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r4, r5, #0
	adds r3, r1, #0
	cmp r2, #0xf
	bls .L080D39D4
	adds r0, r3, #0
	orrs r0, r5
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne .L080D39D4
	adds r1, r5, #0
.L080D39AE:
	ldm r3!, {r0}
	stm r1!, {r0}
	ldm r3!, {r0}
	stm r1!, {r0}
	ldm r3!, {r0}
	stm r1!, {r0}
	ldm r3!, {r0}
	stm r1!, {r0}
	subs r2, #0x10
	cmp r2, #0xf
	bhi .L080D39AE
	cmp r2, #3
	bls .L080D39D2
.L080D39C8:
	ldm r3!, {r0}
	stm r1!, {r0}
	subs r2, #4
	cmp r2, #3
	bhi .L080D39C8
.L080D39D2:
	adds r4, r1, #0
.L080D39D4:
	subs r2, #1
	movs r0, #1
	rsbs r0, r0, #0
	cmp r2, r0
	beq .L080D39EE
	adds r1, r0, #0
.L080D39E0:
	ldrb r0, [r3]
	strb r0, [r4]
	adds r3, #1
	adds r4, #1
	subs r2, #1
	cmp r2, r1
	bne .L080D39E0
.L080D39EE:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start memmove
memmove: @ 0x080D39F8
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r4, r5, #0
	adds r3, r1, #0
	cmp r3, r5
	bhs .L080D3A2A
	adds r0, r3, r2
	cmp r5, r0
	bhs .L080D3A2A
	adds r3, r0, #0
	adds r4, r5, r2
	subs r2, #1
	movs r0, #1
	rsbs r0, r0, #0
	cmp r2, r0
	beq .L080D3A7C
	adds r1, r0, #0
.L080D3A1A:
	subs r4, #1
	subs r3, #1
	ldrb r0, [r3]
	strb r0, [r4]
	subs r2, #1
	cmp r2, r1
	bne .L080D3A1A
	b .L080D3A7C
.L080D3A2A:
	cmp r2, #0xf
	bls .L080D3A62
	adds r0, r3, #0
	orrs r0, r4
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne .L080D3A62
	adds r1, r3, #0
.L080D3A3C:
	ldm r1!, {r0}
	stm r4!, {r0}
	ldm r1!, {r0}
	stm r4!, {r0}
	ldm r1!, {r0}
	stm r4!, {r0}
	ldm r1!, {r0}
	stm r4!, {r0}
	subs r2, #0x10
	cmp r2, #0xf
	bhi .L080D3A3C
	cmp r2, #3
	bls .L080D3A60
.L080D3A56:
	ldm r1!, {r0}
	stm r4!, {r0}
	subs r2, #4
	cmp r2, #3
	bhi .L080D3A56
.L080D3A60:
	adds r3, r1, #0
.L080D3A62:
	subs r2, #1
	movs r0, #1
	rsbs r0, r0, #0
	cmp r2, r0
	beq .L080D3A7C
	adds r1, r0, #0
.L080D3A6E:
	ldrb r0, [r3]
	strb r0, [r4]
	adds r3, #1
	adds r4, #1
	subs r2, #1
	cmp r2, r1
	bne .L080D3A6E
.L080D3A7C:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start memset
memset: @ 0x080D3A84
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r4, r1, #0
	adds r3, r5, #0
	cmp r2, #3
	bls .L080D3ACA
	movs r0, #3
	ands r0, r5
	cmp r0, #0
	bne .L080D3ACA
	adds r1, r5, #0
	movs r0, #0xff
	ands r4, r0
	lsls r3, r4, #8
	orrs r3, r4
	lsls r0, r3, #0x10
	orrs r3, r0
	cmp r2, #0xf
	bls .L080D3ABE
.L080D3AAA:
	stm r1!, {r3}
	stm r1!, {r3}
	stm r1!, {r3}
	stm r1!, {r3}
	subs r2, #0x10
	cmp r2, #0xf
	bhi .L080D3AAA
	b .L080D3ABE
.L080D3ABA:
	stm r1!, {r3}
	subs r2, #4
.L080D3ABE:
	cmp r2, #3
	bhi .L080D3ABA
	adds r3, r1, #0
	b .L080D3ACA
.L080D3AC6:
	strb r4, [r3]
	adds r3, #1
.L080D3ACA:
	adds r0, r2, #0
	subs r2, #1
	cmp r0, #0
	bne .L080D3AC6
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

