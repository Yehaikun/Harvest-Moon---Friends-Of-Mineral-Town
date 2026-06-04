    .INCLUDE "asm/macro.inc"
    .SYNTAX UNIFIED

    thumb_func_start func_08003788
func_08003788: @ 0x08003788
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x2c
    adds r6, r1, #0
    str r2, [sp, #0x24]
    movs r0, #0
    mov sb, r0
    mov r1, sb
    strb r1, [r6]
    ldr r2, [sp, #0x24]
    adds r2, #0x10
    mov sl, r2
    movs r3, #0xc8
    str r3, [sp, #0x18]
    ldr r1, [sp, #0x24]
    ldrb r0, [r1, #0x10]
    lsrs r2, r0, #3
    lsls r1, r2, #3
    subs r1, r1, r2
    lsls r0, r0, #0x1d
    lsrs r0, r0, #0x1d
    adds r1, r1, r0
    str r1, [sp, #0x1c]
    add r2, sp, #0x1c
    add r0, sp, #0x18
    cmp r3, r1
    bls .L080037C6
    adds r0, r2, #0
.L080037C6:
    ldr r0, [r0]
    mov r1, sp
    movs r2, #0
    bl func_0804EC84
    ldr r2, .L08003B24 @ =gUnk_080E874C
    mov r8, r2
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003802
    mov r0, r8
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L080037F2
    adds r4, r5, #0
.L080037F2:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r0, r7, r4
    mov r1, sb
    strb r1, [r0]
.L08003802:
    mov r8, r6
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003832
    mov r0, sp
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003822
    adds r4, r5, #0
.L08003822:
    adds r0, r7, #0
    mov r1, sp
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L08003832:
    ldr r2, .L08003B28 @ =gUnk_080E8754
    mov sb, r2
    mov r0, r8
    bl strlen
    mov r1, r8
    adds r7, r1, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003866
    mov r0, sb
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003856
    adds r4, r5, #0
.L08003856:
    adds r0, r7, #0
    mov r1, sb
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L08003866:
    mov r2, sl
    ldrb r0, [r2, #1]
    lsls r0, r0, #0x1e
    lsrs r0, r0, #0x1e
    bl func_0800E2E4
    mov r8, r0
    mov r4, r8
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L080038A4
    adds r0, r4, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003894
    adds r4, r5, #0
.L08003894:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L080038A4:
    mov r1, sl
    ldrb r0, [r1, #1]
    lsls r0, r0, #0x19
    lsrs r0, r0, #0x1b
    adds r0, #1
    mov r1, sp
    movs r2, #0
    bl func_0804EC84
    ldr r2, .L08003B2C @ =gUnk_080E8758
    mov r8, r2
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L080038E8
    mov r0, r8
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L080038D8
    adds r4, r5, #0
.L080038D8:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L080038E8:
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003916
    mov r0, sp
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003906
    adds r4, r5, #0
.L08003906:
    adds r0, r7, #0
    mov r1, sp
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L08003916:
    ldr r0, .L08003B30 @ =gUnk_080E8760
    mov r8, r0
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003948
    mov r0, r8
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003938
    adds r4, r5, #0
.L08003938:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L08003948:
    mov r1, sl
    ldrb r2, [r1]
    lsls r2, r2, #0x1d
    lsrs r2, r2, #0x1d
    ldrb r3, [r1, #1]
    lsls r0, r3, #0x1e
    lsrs r0, r0, #0x1e
    lsls r3, r3, #0x19
    lsrs r3, r3, #0x1b
    adds r2, #6
    lsls r1, r0, #4
    subs r1, r1, r0
    lsls r1, r1, #1
    lsls r0, r2, #4
    subs r0, r0, r2
    lsls r0, r0, #3
    adds r1, r1, r0
    adds r2, r3, r1
    cmp r2, #6
    bls .L0800397A
    adds r0, r2, #0
    movs r1, #7
    bl __umodsi3
    adds r2, r0, #0
.L0800397A:
    movs r0, #7
    ands r2, r0
    adds r0, r2, #0
    bl func_0800E304
    mov r8, r0
    mov sb, r6
    mov r4, r8
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L080039B8
    adds r0, r4, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L080039A8
    adds r4, r5, #0
.L080039A8:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L080039B8:
    ldr r2, .L08003B34 @ =gUnk_080E8764
    mov r8, r2
    mov r0, sb
    bl strlen
    mov r1, sb
    adds r7, r1, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L080039EC
    mov r0, r8
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L080039DC
    adds r4, r5, #0
.L080039DC:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L080039EC:
    movs r1, #0xd
    add r0, sp, #0x20
    strb r1, [r0]
    adds r0, r6, #0
    bl strlen
    adds r3, r0, #1
    cmp r3, #0x7f
    bhi .L08003A0A
    adds r1, r6, r0
    movs r2, #0
    movs r0, #0xd
    strb r0, [r1]
    adds r0, r6, r3
    strb r2, [r0]
.L08003A0A:
    movs r1, #0xa
    mov r0, sp
    adds r0, #0x21
    strb r1, [r0]
    adds r0, r6, #0
    bl strlen
    adds r3, r0, #1
    cmp r3, #0x7f
    bhi .L08003A2A
    adds r1, r6, r0
    movs r2, #0
    movs r0, #0xa
    strb r0, [r1]
    adds r0, r6, r3
    strb r2, [r0]
.L08003A2A:
    ldr r0, [sp, #0x24]
    adds r0, #0x14
    bl method_08009AF4__C4Farm
    mov r8, r0
    mov r4, r8
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003A64
    adds r0, r4, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003A54
    adds r4, r5, #0
.L08003A54:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L08003A64:
    ldr r2, .L08003B38 @ =gUnk_080E8768
    mov r8, r2
    adds r0, r6, #0
    bl strlen
    adds r7, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003A96
    mov r0, r8
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003A86
    adds r4, r5, #0
.L08003A86:
    adds r0, r7, #0
    mov r1, r8
    adds r2, r4, #0
    bl memcpy
    adds r1, r7, r4
    movs r0, #0
    strb r0, [r1]
.L08003A96:
    movs r1, #0xd
    mov r0, sp
    adds r0, #0x22
    strb r1, [r0]
    adds r0, r6, #0
    bl strlen
    adds r3, r0, #1
    cmp r3, #0x7f
    bhi .L08003AB6
    adds r1, r6, r0
    movs r2, #0
    movs r0, #0xd
    strb r0, [r1]
    adds r0, r6, r3
    strb r2, [r0]
.L08003AB6:
    movs r1, #0xa
    mov r0, sp
    adds r0, #0x23
    strb r1, [r0]
    adds r0, r6, #0
    bl strlen
    adds r3, r0, #1
    cmp r3, #0x7f
    bhi .L08003AD6
    adds r1, r6, r0
    movs r2, #0
    movs r0, #0xa
    strb r0, [r1]
    adds r0, r6, r3
    strb r2, [r0]
.L08003AD6:
    ldr r1, [sp, #0x24]
    ldr r2, .L08003B3C @ =0x00001BD8
    adds r0, r1, r2
    bl func_0800E4E0
    adds r7, r0, #0
    adds r4, r7, #0
    adds r0, r6, #0
    bl strlen
    adds r6, r6, r0
    movs r1, #0x7f
    subs r5, r1, r0
    cmp r5, #0
    beq .L08003B12
    adds r0, r4, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08003B02
    adds r4, r5, #0
.L08003B02:
    adds r0, r6, #0
    adds r1, r7, #0
    adds r2, r4, #0
    bl memcpy
    adds r1, r6, r4
    movs r0, #0
    strb r0, [r1]
.L08003B12:
    add sp, #0x2c
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L08003B24: .4byte gUnk_080E874C
.L08003B28: .4byte gUnk_080E8754
.L08003B2C: .4byte gUnk_080E8758
.L08003B30: .4byte gUnk_080E8760
.L08003B34: .4byte gUnk_080E8764
.L08003B38: .4byte gUnk_080E8768
.L08003B3C: .4byte 0x00001BD8

    thumb_func_start func_08003B40
func_08003B40: @ 0x08003B40
    push {r4, r5, lr}
    sub sp, #0x14
    adds r5, r0, #0
    bl func_08008918
    mov r1, sp
    movs r2, #0x3f
    strh r2, [r1]
    adds r0, #0x50
    strh r2, [r0]
    adds r0, r5, #0
    bl func_08008918
    adds r1, r0, #0
    add r4, sp, #4
    movs r0, #0
    str r0, [sp, #4]
    str r0, [r4, #4]
    ldr r0, .L08003B8C @ =vtable_unk_080E5B80
    str r0, [sp, #0xc]
    add r0, sp, #0x10
    bl func_08009300
    ldr r1, .L08003B90 @ =0x00000889
    add r0, sp, #0x10
    movs r2, #1
    movs r3, #1
    bl func_0800934C
    adds r0, r5, #0
    bl func_08008940
    ldr r1, [r0, #8]
    ldr r2, [r1, #0x10]
    adds r1, r4, #0
    bl _call_via_r2
    b .L08003B9A
    .align 2, 0
.L08003B8C: .4byte vtable_unk_080E5B80
.L08003B90: .4byte 0x00000889
.L08003B94:
    adds r0, r5, #0
    bl func_080087C8
.L08003B9A:
    ldr r1, [sp, #4]
    rsbs r0, r1, #0
    orrs r0, r1
    cmp r0, #0
    blt .L08003B94
    adds r0, r4, #0
    movs r1, #2
    bl func_080094B8
    add sp, #0x14
    pop {r4, r5}
    pop {r0}
    bx r0

    thumb_func_start func_08003BB4
func_08003BB4: @ 0x08003BB4
    push {r4, r5, lr}
    sub sp, #0x14
    adds r5, r0, #0
    bl func_08008918
    mov r1, sp
    movs r2, #0x3f
    strh r2, [r1]
    adds r0, #0x50
    strh r2, [r0]
    adds r0, r5, #0
    bl func_08008918
    adds r1, r0, #0
    add r4, sp, #4
    movs r0, #0
    str r0, [sp, #4]
    str r0, [r4, #4]
    ldr r0, .L08003C00 @ =vtable_unk_080E5B80
    str r0, [sp, #0xc]
    add r0, sp, #0x10
    bl func_08009300
    ldr r1, .L08003C04 @ =0x00000889
    add r0, sp, #0x10
    movs r2, #1
    movs r3, #1
    bl func_08009378
    adds r0, r5, #0
    bl func_08008940
    ldr r1, [r0, #8]
    ldr r2, [r1, #0x10]
    adds r1, r4, #0
    bl _call_via_r2
    b .L08003C0E
    .align 2, 0
.L08003C00: .4byte vtable_unk_080E5B80
.L08003C04: .4byte 0x00000889
.L08003C08:
    adds r0, r5, #0
    bl func_080087C8
.L08003C0E:
    ldr r1, [sp, #4]
    rsbs r0, r1, #0
    orrs r0, r1
    cmp r0, #0
    blt .L08003C08
    adds r0, r4, #0
    movs r1, #2
    bl func_080094B8
    add sp, #0x14
    pop {r4, r5}
    pop {r0}
    bx r0

    thumb_func_start func_08003C28
func_08003C28: @ 0x08003C28
    push {r4, r5, r6, lr}
    mov r6, sb
    mov r5, r8
    push {r5, r6}
    sub sp, #0xc
    adds r4, r0, #0
    bl func_080088DC
    mov sb, r0
    adds r0, r4, #0
    bl func_08008920
    mov r8, r0
    adds r0, r4, #0
    bl func_08008918
    adds r6, r0, #0
    adds r0, r4, #0
    bl func_08008940
    adds r5, r0, #0
    adds r0, r4, #0
    bl func_0800894C
    adds r1, r4, #0
    adds r1, #0x10
    adds r4, #0x14
    str r5, [sp]
    str r0, [sp, #4]
    str r4, [sp, #8]
    adds r0, r1, #0
    mov r1, sb
    mov r2, r8
    adds r3, r6, #0
    bl func_08050D3C
    add sp, #0xc
    pop {r3, r4}
    mov r8, r3
    mov sb, r4
    pop {r4, r5, r6}
    pop {r0}
    bx r0
    .align 2, 0

    thumb_func_start func_08003C80
func_08003C80: @ 0x08003C80
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    ldr r4, .L08003DBC @ =0xFFFFD2D8
    add sp, r4
    ldr r4, .L08003DC0 @ =0x0600E800
    ldr r1, .L08003DC4 @ =0x06007FE0
    movs r0, #0
    movs r2, #0x20
    bl func_08008EB8
    movs r0, #1
    rsbs r0, r0, #0
    movs r2, #0x80
    lsls r2, r2, #4
    adds r1, r4, #0
    bl func_08008EB8
    movs r3, #0
    movs r2, #0
    ldr r5, .L08003DC8 @ =0x00002D08
    add r5, sp
    mov r0, sp
    adds r0, #8
    ldr r1, .L08003DCC @ =0x00002D24
    add r1, sp
    str r0, [r1]
    ldr r0, .L08003DD0 @ =0x00002D0C
    add r0, sp
    ldr r1, .L08003DD4 @ =0x00002D18
    add r1, sp
    str r0, [r1]
    ldr r0, .L08003DD8 @ =0x00002D10
    add r0, sp
    ldr r1, .L08003DDC @ =0x00002D1C
    add r1, sp
    str r0, [r1]
    ldr r0, .L08003DE0 @ =0x00002D14
    add r0, sp
    ldr r1, .L08003DE4 @ =0x00002D20
    add r1, sp
    str r0, [r1]
    adds r4, #0x40
.L08003CDA:
    movs r1, #0
    lsls r0, r2, #6
    adds r2, #1
    adds r0, r0, r4
.L08003CE2:
    strh r3, [r0]
    adds r3, #1
    adds r0, #2
    adds r1, #1
    cmp r1, #0x1d
    bls .L08003CE2
    cmp r2, #0xb
    bls .L08003CDA
    movs r1, #0x1e
    movs r2, #0xc
    ldr r0, .L08003DC8 @ =0x00002D08
    add r0, sp
    strh r1, [r0]
    strh r2, [r5, #2]
    ldr r0, [r0]
    ldr r2, .L08003DCC @ =0x00002D24
    add r2, sp
    ldr r1, [r2]
    movs r2, #0
    bl func_0804E7A0
    movs r7, #0
    movs r3, #0xc
    mov sl, r3
    ldr r0, .L08003DCC @ =0x00002D24
    add r0, sp
    ldr r6, [r0]
    movs r1, #0
    mov sb, r1
    ldr r2, .L08003DD0 @ =0x00002D0C
    add r2, sp
    mov r8, r2
.L08003D22:
    ldr r4, .L08003DE8 @ =gUnk_080E8704
    add r4, sb
    lsls r5, r7, #4
    ldr r1, [r4]
    movs r0, #0x1e
    mov r3, r8
    strh r0, [r3]
    mov r3, sl
    ldr r2, .L08003DD4 @ =0x00002D18
    add r2, sp
    ldr r2, [r2]
    strh r3, [r2, #2]
    mov r3, r8
    ldr r0, [r3]
    str r1, [sp]
    adds r1, r6, #0
    movs r2, #0x10
    adds r3, r5, #0
    bl func_0804E8F0
    ldr r1, [r4, #4]
    ldr r0, .L08003DD8 @ =0x00002D10
    add r0, sp
    movs r2, #0x1e
    strh r2, [r0]
    mov r2, sl
    ldr r3, .L08003DDC @ =0x00002D1C
    add r3, sp
    ldr r3, [r3]
    strh r2, [r3, #2]
    ldr r0, [r0]
    str r1, [sp]
    adds r1, r6, #0
    movs r2, #0x80
    adds r3, r5, #0
    bl func_0804E8F0
    ldr r1, [r4, #8]
    ldr r0, .L08003DE0 @ =0x00002D14
    add r0, sp
    movs r2, #0x1e
    strh r2, [r0]
    mov r2, sl
    ldr r3, .L08003DE4 @ =0x00002D20
    add r3, sp
    ldr r3, [r3]
    strh r2, [r3, #2]
    ldr r0, [r0]
    str r1, [sp]
    adds r1, r6, #0
    movs r2, #0xc0
    adds r3, r5, #0
    bl func_0804E8F0
    movs r0, #0xc
    add sb, r0
    adds r7, #1
    cmp r7, #5
    bls .L08003D22
    movs r1, #0xc0
    lsls r1, r1, #0x13
    movs r2, #0xb4
    lsls r2, r2, #6
    ldr r3, .L08003DCC @ =0x00002D24
    add r3, sp
    ldr r0, [r3]
    bl func_08008E64
    ldr r3, .L08003DEC @ =0x00002D28
    add sp, r3
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L08003DBC: .4byte 0xFFFFD2D8
.L08003DC0: .4byte 0x0600E800
.L08003DC4: .4byte 0x06007FE0
.L08003DC8: .4byte 0x00002D08
.L08003DCC: .4byte 0x00002D24
.L08003DD0: .4byte 0x00002D0C
.L08003DD4: .4byte 0x00002D18
.L08003DD8: .4byte 0x00002D10
.L08003DDC: .4byte 0x00002D1C
.L08003DE0: .4byte 0x00002D14
.L08003DE4: .4byte 0x00002D20
.L08003DE8: .4byte gUnk_080E8704
.L08003DEC: .4byte 0x00002D28

    thumb_func_start func_08003DF0
func_08003DF0: @ 0x08003DF0
    push {r4, r5, lr}
    sub sp, #8
    adds r5, r0, #0
    adds r4, r1, #0
    str r2, [sp]
    str r3, [sp, #4]
    mov r0, sp
    ldrb r1, [r0]
    adds r1, #8
    lsls r0, r4, #1
    adds r0, #1
    lsls r0, r0, #3
    adds r1, r1, r0
    lsls r1, r1, #0x18
    lsrs r1, r1, #0x18
    ldr r0, .L08003E78 @ =0xFFFFFF00
    ldr r2, [sp]
    ands r2, r0
    orrs r2, r1
    str r2, [sp]
    lsls r0, r2, #7
    lsrs r3, r0, #0x17
    adds r0, r5, #0
    adds r0, #0x84
    adds r0, r0, r4
    ldrb r0, [r0]
    adds r1, r3, #0
    adds r1, #0x80
    cmp r0, #0
    beq .L08003E2E
    adds r1, #0x40
.L08003E2E:
    ldr r0, .L08003E7C @ =0x000001FF
    ands r1, r0
    lsls r0, r1, #0x10
    ldr r1, .L08003E80 @ =0xFE00FFFF
    ands r1, r2
    orrs r1, r0
    str r1, [sp]
    cmp r4, #1
    bne .L08003E56
    adds r0, r5, #0
    adds r0, #0x80
    ldr r0, [r0]
    cmp r0, #1
    beq .L08003E56
    ldr r0, .L08003E84 @ =0xFFFFFCFF
    ands r0, r1
    movs r1, #0x80
    lsls r1, r1, #2
    orrs r0, r1
    str r0, [sp]
.L08003E56:
    adds r0, r5, #0
    bl func_08008920
    mov r2, sp
    movs r1, #0x7f
    ands r1, r4
    lsls r1, r1, #3
    adds r1, #4
    adds r0, r0, r1
    ldr r1, [sp]
    str r1, [r0]
    ldrh r1, [r2, #4]
    strh r1, [r0, #4]
    add sp, #8
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L08003E78: .4byte 0xFFFFFF00
.L08003E7C: .4byte 0x000001FF
.L08003E80: .4byte 0xFE00FFFF
.L08003E84: .4byte 0xFFFFFCFF

    thumb_func_start func_08003E88
func_08003E88: @ 0x08003E88
    push {r4, r5, lr}
    sub sp, #8
    adds r5, r0, #0
    adds r4, r1, #0
    cmp r4, #1
    bne .L08003E96
    movs r4, #0
.L08003E96:
    str r2, [sp]
    str r3, [sp, #4]
    mov r0, sp
    ldrb r1, [r0]
    adds r1, #8
    lsls r0, r4, #1
    adds r0, #1
    lsls r0, r0, #3
    adds r1, r1, r0
    lsls r1, r1, #0x18
    lsrs r1, r1, #0x18
    ldr r0, .L08003EE0 @ =0xFFFFFF00
    ldr r2, [sp]
    ands r2, r0
    orrs r2, r1
    lsls r1, r2, #7
    lsrs r1, r1, #0x17
    adds r1, #0x10
    ldr r0, .L08003EE4 @ =0x000001FF
    ands r1, r0
    lsls r1, r1, #0x10
    ldr r0, .L08003EE8 @ =0xFE00FFFF
    ands r0, r2
    orrs r0, r1
    str r0, [sp]
    adds r0, r5, #0
    bl func_08008920
    mov r2, sp
    ldr r1, [sp]
    str r1, [r0, #0x34]
    ldrh r1, [r2, #4]
    strh r1, [r0, #0x38]
    add sp, #8
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L08003EE0: .4byte 0xFFFFFF00
.L08003EE4: .4byte 0x000001FF
.L08003EE8: .4byte 0xFE00FFFF

    thumb_func_start func_08003EEC
func_08003EEC: @ 0x08003EEC
    push {lr}
    adds r2, r0, #0
    movs r1, #0
    adds r0, #0x80
    ldr r0, [r0]
    cmp r0, #5
    bhi .L08003F7E
    lsls r0, r0, #2
    ldr r1, .L08003F04 @ =.L08003F08
    adds r0, r0, r1
    ldr r0, [r0]
    mov pc, r0
    .align 2, 0
.L08003F04: .4byte .L08003F08
.L08003F08: @ jump table
    .4byte .L08003F20 @ case 0
    .4byte .L08003F38 @ case 1
    .4byte .L08003F64 @ case 2
    .4byte .L08003F6C @ case 3
    .4byte .L08003F74 @ case 4
    .4byte .L08003F7C @ case 5
.L08003F20:
    adds r0, r2, #0
    adds r0, #0x84
    ldrb r0, [r0]
    ldr r1, .L08003F30 @ =gUnk_080E877C
    cmp r0, #0
    beq .L08003F7E
    ldr r1, .L08003F34 @ =gUnk_080E8770
    b .L08003F7E
    .align 2, 0
.L08003F30: .4byte gUnk_080E877C
.L08003F34: .4byte gUnk_080E8770
.L08003F38:
    adds r0, r2, #0
    adds r0, #0x85
    ldrb r0, [r0]
    lsls r1, r0, #7
    adds r0, r1, r2
    adds r0, #0x98
    movs r3, #0
    ldrb r0, [r0]
    cmp r0, #0
    bne .L08003F4E
    movs r3, #1
.L08003F4E:
    cmp r3, #0
    bne .L08003F5A
    adds r0, r1, r2
    adds r1, r0, #0
    adds r1, #0x98
    b .L08003F7E
.L08003F5A:
    ldr r1, .L08003F60 @ =gUnk_080E878C
    b .L08003F7E
    .align 2, 0
.L08003F60: .4byte gUnk_080E878C
.L08003F64:
    ldr r1, .L08003F68 @ =gUnk_080E87A4
    b .L08003F7E
    .align 2, 0
.L08003F68: .4byte gUnk_080E87A4
.L08003F6C:
    ldr r1, .L08003F70 @ =gUnk_080E87FC
    b .L08003F7E
    .align 2, 0
.L08003F70: .4byte gUnk_080E87FC
.L08003F74:
    ldr r1, .L08003F78 @ =gUnk_080E8828
    b .L08003F7E
    .align 2, 0
.L08003F78: .4byte gUnk_080E8828
.L08003F7C:
    ldr r1, .L08003F94 @ =gUnk_080E8878
.L08003F7E:
    adds r0, r2, #0
    adds r0, #0x10
    cmp r1, #0
    bne .L08003F88
    ldr r1, .L08003F98 @ =gUnk_080E86C0
.L08003F88:
    movs r2, #0
    movs r3, #0
    bl func_08050DC8
    pop {r0}
    bx r0
    .align 2, 0
.L08003F94: .4byte gUnk_080E8878
.L08003F98: .4byte gUnk_080E86C0

    thumb_func_start func_08003F9C
func_08003F9C: @ 0x08003F9C
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x18
    adds r5, r0, #0
    ldr r0, [r5, #8]
    cmp r0, #0
    beq .L0800406A
    adds r0, r5, #0
    adds r0, #0x85
    ldrb r0, [r0]
    mov r8, r0
    adds r4, r5, #0
    adds r4, #0x90
    adds r0, r4, #0
    mov r1, r8
    bl func_080003DC
    str r0, [sp, #4]
    movs r0, #3
    mov sb, r0
    adds r7, r4, #0
    adds r1, r5, #0
    adds r1, #0x10
    str r1, [sp, #0x10]
    adds r0, r5, #0
    adds r0, #0x8c
    str r0, [sp, #0xc]
    adds r1, #8
    str r1, [sp, #0x14]
    mov r0, sp
    str r0, [sp, #8]
    mov r1, r8
    lsls r6, r1, #7
    adds r4, r6, r5
    adds r4, #0x98
    movs r0, #0x80
    lsls r0, r0, #5
    mov sl, r0
.L08003FEE:
    mov r0, sl
    bl func_08000528
    mov r1, sl
    ands r1, r0
    ldr r0, [sp, #8]
    strh r1, [r0]
    ldr r0, [r5, #8]
    adds r1, r7, #0
    ldr r2, [sp, #4]
    bl func_080115B0
    cmp r0, #0
    bne .L08004052
    adds r1, r6, #0
    adds r1, #0x98
    ldr r2, [r5, #8]
    adds r0, r5, #0
    adds r1, r5, r1
    bl func_08003788
    ldr r0, [sp, #0x10]
    adds r1, r4, #0
    movs r2, #0
    movs r3, #0
    bl func_08050DC8
    movs r0, #3
    ldr r1, [sp, #0xc]
    str r0, [r1]
    ldr r0, [sp, #0x14]
    movs r1, #0xc5
    bl func_08008B6C
    adds r0, r7, #0
    mov r1, r8
    bl func_080003E8
    adds r0, r7, #0
    mov r1, r8
    bl func_08000470
    mov r1, sp
    ldrh r0, [r1]
    cmp r0, #0
    beq .L0800404E
    bl func_080004F4
.L0800404E:
    movs r0, #1
    b .L0800408C
.L08004052:
    mov r1, sp
    ldrh r0, [r1]
    cmp r0, #0
    beq .L0800405E
    bl func_080004F4
.L0800405E:
    movs r0, #1
    rsbs r0, r0, #0
    add sb, r0
    mov r1, sb
    cmp r1, #0
    bne .L08003FEE
.L0800406A:
    adds r0, r5, #0
    adds r0, #0x10
    ldr r1, .L0800409C @ =gUnk_080E88C8
    movs r2, #0
    movs r3, #0
    bl func_08050DC8
    adds r1, r5, #0
    adds r1, #0x8c
    movs r0, #3
    str r0, [r1]
    adds r0, r5, #0
    adds r0, #0x18
    movs r1, #0xc7
    bl func_08008B6C
    movs r0, #0
.L0800408C:
    add sp, #0x18
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0
.L0800409C: .4byte gUnk_080E88C8

    thumb_func_start func_080040A0
func_080040A0: @ 0x080040A0
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x10
    adds r6, r0, #0
    adds r0, #0x85
    ldrb r0, [r0]
    mov r8, r0
    adds r4, r6, #0
    adds r4, #0x90
    adds r0, r4, #0
    mov r1, r8
    bl func_080003DC
    mov sl, r0
    movs r0, #0
    str r0, [sp, #8]
    movs r7, #3
    add r0, sp, #8
    mov sb, r0
    str r4, [sp, #0xc]
.L080040CE:
    mov r5, sp
    movs r4, #0x80
    lsls r4, r4, #5
    adds r0, r4, #0
    bl func_08000528
    ands r4, r0
    strh r4, [r5]
    ldr r0, .L08004118 @ =0x000034F4
    bl __builtin_new
    adds r1, r6, #0
    adds r1, #0x90
    mov r2, sl
    mov r3, sb
    bl func_08011650
    adds r1, r0, #0
    str r1, [sp, #4]
    ldr r0, [sp, #8]
    cmp r0, #0
    bne .L0800417C
    ldr r4, [r6, #8]
    cmp r4, #0
    beq .L0800411C
    adds r0, r4, #0
    movs r1, #2
    bl func_080D4480
    ldr r0, [r6, #8]
    cmp r0, #0
    beq .L0800414A
    ldr r1, [sp, #4]
    bl func_080D4178
    b .L0800414A
    .align 2, 0
.L08004118: .4byte 0x000034F4
.L0800411C:
    movs r0, #8
    bl __builtin_new
    ldr r1, .L08004178 @ =vtable_unk_080E5A4C
    str r1, [r0]
    ldr r1, [sp, #4]
    str r4, [sp, #4]
    str r1, [r0, #4]
    adds r5, r6, #0
    adds r5, #0xc
    adds r4, r0, #0
    ldr r1, [r6, #0xc]
    cmp r4, r1
    beq .L08004148
    cmp r1, #0
    beq .L08004148
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004148:
    str r4, [r5]
.L0800414A:
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xc5
    bl func_08008B6C
    ldr r0, [sp, #0xc]
    mov r1, r8
    bl func_08000470
    ldr r0, [sp, #4]
    cmp r0, #0
    beq .L08004168
    movs r1, #3
    bl func_080D4480
.L08004168:
    mov r1, sp
    ldrh r0, [r1]
    cmp r0, #0
    beq .L08004174
    bl func_080004F4
.L08004174:
    movs r0, #1
    b .L080041C6
    .align 2, 0
.L08004178: .4byte vtable_unk_080E5A4C
.L0800417C:
    movs r0, #0
    str r0, [sp, #4]
    adds r0, r1, #0
    bl __builtin_delete
    ldr r0, [sp, #4]
    cmp r0, #0
    beq .L08004192
    movs r1, #3
    bl func_080D4480
.L08004192:
    mov r1, sp
    ldrh r0, [r1]
    cmp r0, #0
    beq .L0800419E
    bl func_080004F4
.L0800419E:
    subs r7, #1
    cmp r7, #0
    bne .L080040CE
    adds r0, r6, #0
    adds r0, #0x10
    ldr r1, .L080041D8 @ =gUnk_080E88D8
    movs r2, #0
    movs r3, #0
    bl func_08050DC8
    adds r1, r6, #0
    adds r1, #0x8c
    movs r0, #3
    str r0, [r1]
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xc7
    bl func_08008B6C
    movs r0, #0
.L080041C6:
    add sp, #0x10
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0
.L080041D8: .4byte gUnk_080E88D8

    thumb_func_start func_080041DC
func_080041DC: @ 0x080041DC
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x70
    adds r7, r0, #0
    adds r4, r1, #0
    str r2, [sp, #0x40]
    add r1, sp, #0x38
    movs r0, #7
    movs r5, #0
    strb r0, [r1]
    strb r5, [r1, #1]
    adds r0, r7, #0
    bl func_08008574
    ldr r0, .L080043B0 @ =vtable_unk_080E5A5C
    str r0, [r7, #4]
    str r4, [r7, #8]
    ldr r1, [sp, #0x40]
    ldr r0, [r1]
    str r5, [r1]
    str r0, [r7, #0xc]
    add r0, sp, #0xc
    bl func_0800835C
    add r4, sp, #0x10
    adds r0, r4, #0
    bl func_0800770C
    adds r0, r7, #0
    adds r0, #0x10
    str r5, [sp]
    add r2, sp, #0xc
    str r2, [sp, #4]
    str r4, [sp, #8]
    movs r1, #0
    movs r2, #0x1f
    movs r3, #0xf
    bl func_08050CC0
    adds r0, r4, #0
    movs r1, #2
    bl func_08007714
    add r0, sp, #0xc
    movs r1, #2
    bl func_08008364
    adds r0, r7, #0
    adds r0, #0x14
    movs r1, #1
    bl func_08008B54
    adds r0, r7, #0
    adds r0, #0x18
    movs r1, #2
    bl func_08008B54
    adds r6, r7, #0
    adds r6, #0x1c
    ldr r1, .L080043B4 @ =gUnk_08728208
    adds r0, r6, #0
    bl func_0805E6CC
    adds r4, r7, #0
    adds r4, #0x4c
    adds r0, r4, #0
    bl func_08007874
    adds r0, r4, #0
    movs r1, #2
    bl func_08007B54
    str r0, [r4, #4]
    adds r4, #8
    adds r0, r4, #0
    bl func_08007128
    adds r0, r4, #0
    bl func_0800736C
    str r0, [r4, #4]
    movs r0, #0
    movs r1, #0
    str r0, [r7, #0x5c]
    str r1, [r7, #0x60]
    adds r0, r7, #0
    adds r0, #0x64
    movs r3, #0x80
    lsls r3, r3, #1
    adds r1, r6, #0
    movs r2, #0
    bl func_0805E824
    adds r0, r7, #0
    adds r0, #0x80
    str r5, [r0]
    adds r0, #0xc
    str r5, [r0]
    adds r0, #4
    bl func_08000640
    adds r0, r7, #0
    adds r0, #0x98
    movs r1, #1
    mov r3, sp
    adds r3, #0x14
    str r3, [sp, #0x6c]
    movs r3, #0
    movs r2, #1
    rsbs r2, r2, #0
.L080042BE:
    strb r3, [r0]
    adds r0, #0x80
    subs r1, #1
    cmp r1, r2
    bne .L080042BE
    movs r0, #0xcc
    lsls r0, r0, #1
    adds r4, r7, r0
    movs r5, #1
    movs r1, #0x1c
    adds r1, r1, r7
    mov sl, r1
    movs r2, #0x4c
    adds r2, r2, r7
    mov r8, r2
    adds r3, r7, #0
    adds r3, #0x54
    str r3, [sp, #0x44]
    movs r0, #0x90
    adds r0, r0, r7
    mov sb, r0
    adds r1, r7, #0
    adds r1, #0x60
    str r1, [sp, #0x4c]
    adds r2, r7, #0
    adds r2, #0x61
    str r2, [sp, #0x50]
    adds r3, #9
    str r3, [sp, #0x48]
    adds r0, r7, #0
    adds r0, #0x84
    str r0, [sp, #0x54]
    adds r1, #0x25
    str r1, [sp, #0x58]
    adds r2, #0x25
    str r2, [sp, #0x5c]
    adds r3, #0x2a
    str r3, [sp, #0x60]
    adds r0, #4
    str r0, [sp, #0x64]
    adds r1, #4
    str r1, [sp, #0x68]
    movs r6, #1
    rsbs r6, r6, #0
.L08004316:
    adds r0, r4, #0
    bl func_080114F8
    adds r4, #4
    subs r5, #1
    cmp r5, r6
    bne .L08004316
    ldr r0, [sp, #0x6c]
    mov r1, sl
    movs r2, #0
    bl func_0805E790
    ldr r0, [sp, #0x14]
    ldr r1, [r0, #4]
    ldr r0, [r0]
    str r0, [r7, #0x5c]
    str r1, [r7, #0x60]
    mov r2, r8
    ldr r1, [r2, #4]
    mov r0, r8
    bl func_08007D4C
    ldr r3, .L080043B8 @ =0x000003FF
    adds r1, r3, #0
    ands r0, r1
    ldr r1, [sp, #0x4c]
    ldrh r2, [r1]
    ldr r1, .L080043BC @ =0xFFFFFC00
    ands r1, r2
    orrs r1, r0
    ldr r2, [sp, #0x4c]
    strh r1, [r2]
    ldr r3, [sp, #0x44]
    ldr r1, [r3, #4]
    adds r0, r3, #0
    bl func_080074C0
    lsls r0, r0, #4
    ldr r1, [sp, #0x50]
    ldrb r2, [r1]
    movs r1, #0xf
    ands r1, r2
    orrs r1, r0
    ldr r2, [sp, #0x50]
    strb r1, [r2]
    ldr r3, [sp, #0x48]
    ldrb r0, [r3]
    movs r1, #0x10
    orrs r0, r1
    strb r0, [r3]
    ldr r0, [r7, #0x5c]
    ldr r1, [r7, #0x60]
    str r0, [r7, #0x78]
    str r1, [r7, #0x7c]
    movs r4, #0
.L08004384:
    mov r0, sb
    bl func_080003A0
    movs r1, #1
    lsls r1, r4
    ands r1, r0
    rsbs r0, r1, #0
    orrs r0, r1
    adds r1, r4, #1
    mov sl, r1
    cmp r0, #0
    bge .L08004426
    mov r0, sb
    adds r1, r4, #0
    bl func_080003DC
    mov r8, r0
    movs r0, #0
    str r0, [sp, #0x3c]
    movs r5, #3
    add r6, sp, #0x3c
    b .L080043E0
    .align 2, 0
.L080043B0: .4byte vtable_unk_080E5A5C
.L080043B4: .4byte gUnk_08728208
.L080043B8: .4byte 0x000003FF
.L080043BC: .4byte 0xFFFFFC00
.L080043C0:
    movs r0, #0
    str r0, [sp, #0x34]
    adds r0, r2, #0
    bl __builtin_delete
    ldr r0, [sp, #0x34]
    cmp r0, #0
    beq .L080043D6
    movs r1, #3
    bl func_080D4480
.L080043D6:
    subs r5, #1
    movs r0, #1
    rsbs r0, r0, #0
    cmp r5, r0
    beq .L08004426
.L080043E0:
    ldr r0, .L080044B8 @ =0x000034F4
    bl __builtin_new
    mov r1, sb
    mov r2, r8
    adds r3, r6, #0
    bl func_08011650
    adds r2, r0, #0
    str r2, [sp, #0x34]
    ldr r0, [sp, #0x3c]
    cmp r0, #0
    bne .L080043C0
    lsls r1, r4, #7
    adds r1, #0x98
    adds r1, r7, r1
    adds r0, r7, #0
    bl func_08003788
    ldr r2, [sp, #0x34]
    lsls r0, r4, #2
    adds r0, r0, r7
    movs r3, #0xcc
    lsls r3, r3, #1
    adds r0, r0, r3
    ldr r3, .L080044BC @ =0x00002210
    adds r1, r2, r3
    ldr r1, [r1]
    str r1, [r0]
    cmp r2, #0
    beq .L08004426
    adds r0, r2, #0
    movs r1, #3
    bl func_080D4480
.L08004426:
    mov r4, sl
    cmp r4, #1
    bls .L08004384
    mov r0, sb
    bl func_08000488
    adds r2, r0, #0
    ldr r0, [r7, #8]
    cmp r0, #0
    beq .L080044C0
    movs r0, #0
    ldr r1, [sp, #0x54]
    strb r0, [r1]
    rsbs r0, r2, #0
    orrs r0, r2
    lsrs r0, r0, #0x1f
    ldr r2, [sp, #0x58]
    strb r0, [r2]
    ldr r0, [r7, #8]
    ldr r3, .L080044BC @ =0x00002210
    adds r5, r0, r3
    movs r1, #0
    ldr r0, [r5]
    lsls r0, r0, #0x1f
    cmp r0, #0
    beq .L0800445C
    movs r1, #1
.L0800445C:
    ldr r0, [sp, #0x5c]
    strb r1, [r0]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #2
    bl func_08003DF0
    ldrb r0, [r5]
    lsrs r0, r0, #1
    movs r4, #1
    eors r0, r4
    ands r0, r4
    ldr r1, [sp, #0x60]
    strb r0, [r1]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #3
    bl func_08003DF0
    ldrb r0, [r5]
    lsrs r0, r0, #2
    eors r0, r4
    ands r0, r4
    ldr r2, [sp, #0x64]
    strb r0, [r2]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #4
    bl func_08003DF0
    ldrb r0, [r5]
    lsrs r0, r0, #3
    eors r0, r4
    ands r0, r4
    ldr r3, [sp, #0x68]
    strb r0, [r3]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #5
    bl func_08003DF0
    b .L08004548
    .align 2, 0
.L080044B8: .4byte 0x000034F4
.L080044BC: .4byte 0x00002210
.L080044C0:
    adds r0, r7, #0
    adds r0, #0x80
    movs r1, #1
    str r1, [r0]
    movs r5, #1
    ldr r0, [sp, #0x54]
    strb r1, [r0]
    rsbs r0, r2, #0
    orrs r0, r2
    lsrs r0, r0, #0x1f
    ldr r1, [sp, #0x58]
    strb r0, [r1]
    ldrb r0, [r1]
    lsls r0, r0, #2
    adds r4, r0, r7
    movs r2, #0xcc
    lsls r2, r2, #1
    adds r4, r4, r2
    movs r1, #0
    ldr r0, [r4]
    lsls r0, r0, #0x1f
    cmp r0, #0
    beq .L080044F0
    movs r1, #1
.L080044F0:
    ldr r3, [sp, #0x5c]
    strb r1, [r3]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #2
    bl func_08003DF0
    ldrb r0, [r4]
    lsrs r0, r0, #1
    eors r0, r5
    ands r0, r5
    ldr r1, [sp, #0x60]
    strb r0, [r1]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #3
    bl func_08003DF0
    ldrb r0, [r4]
    lsrs r0, r0, #2
    eors r0, r5
    ands r0, r5
    ldr r2, [sp, #0x64]
    strb r0, [r2]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #4
    bl func_08003DF0
    ldrb r0, [r4]
    lsrs r0, r0, #3
    eors r0, r5
    ands r0, r5
    ldr r3, [sp, #0x68]
    strb r0, [r3]
    ldr r2, [r7, #0x5c]
    ldr r3, [r7, #0x60]
    adds r0, r7, #0
    movs r1, #5
    bl func_08003DF0
.L08004548:
    ldr r0, [sp, #0x40]
    ldr r1, [r0]
    cmp r1, #0
    beq .L0800455C
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L0800455C:
    adds r0, r7, #0
    add sp, #0x70
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0

    thumb_func_start func_08004570
func_08004570: @ 0x08004570
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x5c
    str r0, [sp, #0x58]
    adds r6, r1, #0
    adds r0, r6, #0
    bl func_08008724
    adds r0, r6, #0
    bl func_08008918
    adds r5, r0, #0
    add r0, sp, #0xc
    movs r2, #0xe2
    lsls r2, r2, #5
    adds r1, r2, #0
    strh r1, [r0]
    movs r4, #0
    strh r1, [r5]
    ldr r0, .L080046A4 @ =gUnk_080F9F78
    ldr r0, [r0]
    movs r1, #0xa0
    lsls r1, r1, #0x13
    ldr r2, .L080046A8 @ =gUnk_080F9F7C
    ldr r2, [r2]
    bl func_08008E64
    add r1, sp, #0xc
    ldr r2, .L080046AC @ =0x00001E4C
    adds r0, r2, #0
    strh r0, [r1]
    strh r0, [r5, #0xe]
    ldr r0, .L080046B0 @ =gUnk_080F9F70
    ldr r0, [r0]
    ldr r1, .L080046B4 @ =0x0600C000
    ldr r2, .L080046B8 @ =gUnk_080F9F74
    ldr r2, [r2]
    bl func_08008E64
    ldr r0, .L080046BC @ =0x0600F000
    movs r1, #0x14
    str r1, [sp]
    str r4, [sp, #4]
    str r4, [sp, #8]
    movs r1, #0
    movs r2, #0
    movs r3, #0x1e
    bl func_08051320
    add r1, sp, #0xc
    movs r2, #0xea
    lsls r2, r2, #5
    adds r0, r2, #0
    strh r0, [r1]
    strh r0, [r5, #0xc]
    adds r0, r6, #0
    bl func_08003C80
    adds r4, r6, #0
    adds r4, #0x10
    adds r0, r4, #0
    movs r1, #0x2c
    bl func_08050E98
    adds r0, r4, #0
    bl func_08050D68
    adds r0, r6, #0
    bl func_08003C28
    ldrh r0, [r5, #8]
    movs r1, #0x40
    orrs r0, r1
    strh r0, [r5, #8]
    adds r0, r6, #0
    bl func_08003EEC
    add r0, sp, #0x10
    adds r1, r6, #0
    adds r1, #0x1c
    movs r2, #0
    bl func_0805E790
    ldr r4, [sp, #0x18]
    adds r0, r6, #0
    adds r0, #0x4c
    ldr r1, [r0, #4]
    bl func_08007D4C
    adds r1, r0, #0
    lsls r1, r1, #5
    ldr r0, .L080046C0 @ =0x06010000
    adds r1, r1, r0
    adds r0, r4, #0
    movs r2, #0x80
    bl func_08008E64
    ldr r4, [sp, #0x20]
    adds r0, r6, #0
    adds r0, #0x54
    ldr r1, [r0, #4]
    bl func_080074C0
    adds r1, r0, #0
    lsls r1, r1, #5
    ldr r2, .L080046C4 @ =0x05000200
    adds r1, r1, r2
    adds r0, r4, #0
    movs r2, #0x20
    bl func_08008E64
    movs r4, #0
.L08004656:
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    adds r1, r4, #0
    bl func_08003DF0
    adds r4, #1
    cmp r4, #5
    bls .L08004656
    adds r0, r6, #0
    bl func_08003B40
    movs r0, #0x8c
    adds r0, r0, r6
    mov sl, r0
.L08004674:
    adds r0, r6, #0
    bl func_080087C8
    adds r0, r6, #0
    bl func_080088B8
    adds r0, r6, #0
    bl func_08003C28
    adds r0, r6, #0
    bl func_080088D4
    adds r7, r0, #0
    mov r5, sl
    ldr r0, [r5]
    cmp r0, #1
    bne .L08004698
    b .L08004A9E
.L08004698:
    cmp r0, #1
    bgt .L080046C8
    cmp r0, #0
    beq .L080046D6
    b .L08004674
    .align 2, 0
.L080046A4: .4byte gUnk_080F9F78
.L080046A8: .4byte gUnk_080F9F7C
.L080046AC: .4byte 0x00001E4C
.L080046B0: .4byte gUnk_080F9F70
.L080046B4: .4byte 0x0600C000
.L080046B8: .4byte gUnk_080F9F74
.L080046BC: .4byte 0x0600F000
.L080046C0: .4byte 0x06010000
.L080046C4: .4byte 0x05000200
.L080046C8:
    cmp r0, #2
    bne .L080046CE
    b .L08004AC4
.L080046CE:
    cmp r0, #3
    bne .L080046D4
    b .L08004B1A
.L080046D4:
    b .L08004674
.L080046D6:
    adds r4, r6, #0
    adds r4, #0x64
    adds r0, r4, #0
    bl func_0805E8F0
    lsls r0, r0, #0x1e
    cmp r0, #0
    bge .L0800474A
    ldr r1, [r6, #0x64]
    ldr r3, [r1]
    ldrh r2, [r4, #0xc]
    lsls r2, r2, #2
    ldr r0, [r6, #0x68]
    adds r0, r0, r2
    ldrh r2, [r0]
    add r0, sp, #0x30
    ldr r3, [r3, #0x10]
    bl _call_via_r3
    add r1, sp, #0x30
    adds r0, r1, #0
    movs r2, #0x20
    bl memcpy
    ldr r1, [sp, #0x30]
    ldrb r0, [r1]
    adds r5, r6, #0
    adds r5, #0x78
    strb r0, [r5]
    ldrh r1, [r1, #2]
    lsls r1, r1, #0x17
    adds r3, r6, #0
    adds r3, #0x7a
    lsrs r1, r1, #0x17
    ldrh r2, [r3]
    ldr r0, .L0800479C @ =0xFFFFFE00
    ands r0, r2
    orrs r0, r1
    strh r0, [r3]
    adds r4, #0x1c
    ldr r1, [r4]
    ldr r2, [r6, #0x78]
    ldr r3, [r6, #0x7c]
    adds r0, r6, #0
    bl func_08003DF0
    ldr r1, [r4]
    ldr r0, [r6, #8]
    adds r2, r6, #0
    adds r2, #0x5c
    cmp r0, #0
    beq .L08004740
    adds r2, r5, #0
.L08004740:
    ldr r3, [r2, #4]
    ldr r2, [r2]
    adds r0, r6, #0
    bl func_08003E88
.L0800474A:
    movs r1, #2
    mov sb, r1
    adds r0, r7, #0
    ands r0, r1
    lsls r0, r0, #0x18
    lsrs r5, r0, #0x18
    cmp r5, #0
    beq .L080047AE
    ldr r0, [r6, #8]
    cmp r0, #0
    beq .L080047A0
    adds r4, r6, #0
    adds r4, #0x80
    ldr r0, [r4]
    cmp r0, #1
    beq .L0800476C
    b .L08004B36
.L0800476C:
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xc6
    bl func_08008B6C
    movs r0, #0
    str r0, [r4]
    adds r0, r6, #0
    bl func_08003EEC
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    movs r1, #1
    bl func_08003DF0
    ldr r2, [r6, #0x78]
    ldr r3, [r6, #0x7c]
    adds r0, r6, #0
    movs r1, #0
    bl func_08003DF0
    b .L08004674
    .align 2, 0
.L0800479C: .4byte 0xFFFFFE00
.L080047A0:
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xc6
    bl func_08008B6C
    add r4, sp, #0x50
    b .L08004AF2
.L080047AE:
    movs r2, #1
    mov r8, r2
    movs r1, #1
    adds r0, r7, #0
    ands r0, r1
    cmp r0, #0
    beq .L080048A0
    adds r0, r6, #0
    adds r0, #0x80
    ldr r7, [r0]
    cmp r7, #0
    bne .L080047F2
    str r1, [r0]
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    movs r1, #0
    bl func_08003DF0
    ldr r2, [r6, #0x78]
    ldr r3, [r6, #0x7c]
    adds r0, r6, #0
    movs r1, #1
    bl func_08003DF0
    adds r0, r6, #0
    bl func_08003EEC
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xc5
    bl func_08008B6C
    b .L08004674
.L080047F2:
    cmp r7, #1
    beq .L080047F8
    b .L08004674
.L080047F8:
    adds r0, r6, #0
    adds r0, #0x85
    ldrb r1, [r0]
    subs r0, #1
    ldrb r4, [r0]
    cmp r4, #0
    beq .L08004864
    lsls r0, r1, #7
    adds r0, r0, r6
    adds r0, #0x98
    movs r1, #0
    ldrb r0, [r0]
    cmp r0, #0
    bne .L08004816
    movs r1, #1
.L08004816:
    cmp r1, r8
    beq .L08004840
    adds r0, r6, #0
    adds r0, #0x10
    ldr r1, .L08004834 @ =gUnk_080E890C
    ldr r2, .L08004838 @ =gUnk_080E86EC
    ldr r3, .L0800483C @ =gUnk_080E86F0
    str r5, [sp]
    str r5, [sp, #4]
    str r5, [sp, #8]
    bl func_08050E30
    mov r0, sb
    b .L08004B30
    .align 2, 0
.L08004834: .4byte gUnk_080E890C
.L08004838: .4byte gUnk_080E86EC
.L0800483C: .4byte gUnk_080E86F0
.L08004840:
    adds r0, r6, #0
    adds r0, #0x10
    ldr r1, .L08004860 @ =gUnk_080E878C
    movs r2, #0
    movs r3, #0
    bl func_08050DC8
    movs r0, #3
    mov r2, sl
    str r0, [r2]
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xc7
    bl func_08008B6C
    b .L08004674
    .align 2, 0
.L08004860: .4byte gUnk_080E878C
.L08004864:
    lsls r0, r1, #7
    adds r0, r0, r6
    adds r0, #0x98
    movs r1, #0
    ldrb r0, [r0]
    cmp r0, #0
    bne .L08004874
    movs r1, #1
.L08004874:
    cmp r1, r8
    bne .L0800487A
    b .L08004ABC
.L0800487A:
    adds r0, r6, #0
    adds r0, #0x10
    ldr r1, .L08004894 @ =gUnk_080E8914
    ldr r2, .L08004898 @ =gUnk_080E86EC
    ldr r3, .L0800489C @ =gUnk_080E86F0
    str r4, [sp]
    str r4, [sp, #4]
    str r4, [sp, #8]
    bl func_08050E30
    mov r0, sl
    str r7, [r0]
    b .L08004674
    .align 2, 0
.L08004894: .4byte gUnk_080E8914
.L08004898: .4byte gUnk_080E86EC
.L0800489C: .4byte gUnk_080E86F0
.L080048A0:
    adds r0, r7, #0
    lsls r1, r0, #0x1b
    lsls r0, r0, #0x1a
    lsrs r1, r1, #0x1f
    lsrs r0, r0, #0x1f
    cmp r1, r0
    bne .L080048B0
    b .L08004A16
.L080048B0:
    adds r2, r6, #0
    adds r2, #0x80
    adds r1, r6, #0
    adds r1, #0x84
    ldr r0, [r2]
    adds r1, r1, r0
    ldrb r4, [r1]
    mov r0, r8
    eors r4, r0
    strb r4, [r1]
    ldr r0, [r6, #8]
    adds r5, r2, #0
    cmp r0, #0
    beq .L08004980
    ldr r0, [r5]
    cmp r0, #5
    bls .L080048D4
    b .L08004A08
.L080048D4:
    lsls r0, r0, #2
    ldr r1, .L080048E0 @ =.L080048E4
    adds r0, r0, r1
    ldr r0, [r0]
    mov pc, r0
    .align 2, 0
.L080048E0: .4byte .L080048E4
.L080048E4: @ jump table
    .4byte .L080048FC @ case 0
    .4byte .L080048FC @ case 1
    .4byte .L08004904 @ case 2
    .4byte .L08004924 @ case 3
    .4byte .L08004940 @ case 4
    .4byte .L0800495C @ case 5
.L080048FC:
    adds r0, r6, #0
    bl func_08003EEC
    b .L08004A08
.L08004904:
    ldr r3, [r6, #8]
    rsbs r1, r4, #0
    orrs r1, r4
    ldr r2, .L08004920 @ =0x00002210
    adds r3, r3, r2
    lsrs r1, r1, #0x1f
    ldrb r2, [r3]
    movs r0, #2
    rsbs r0, r0, #0
    ands r0, r2
    orrs r0, r1
    strb r0, [r3]
    b .L08004A08
    .align 2, 0
.L08004920: .4byte 0x00002210
.L08004924:
    ldr r2, [r6, #8]
    movs r3, #1
    cmp r4, #0
    beq .L0800492E
    movs r3, #0
.L0800492E:
    ldr r0, .L0800493C @ =0x00002210
    adds r2, r2, r0
    lsls r3, r3, #1
    ldrb r1, [r2]
    movs r0, #3
    rsbs r0, r0, #0
    b .L08004972
    .align 2, 0
.L0800493C: .4byte 0x00002210
.L08004940:
    ldr r2, [r6, #8]
    movs r3, #1
    cmp r4, #0
    beq .L0800494A
    movs r3, #0
.L0800494A:
    ldr r1, .L08004958 @ =0x00002210
    adds r2, r2, r1
    lsls r3, r3, #2
    ldrb r1, [r2]
    movs r0, #5
    rsbs r0, r0, #0
    b .L08004972
    .align 2, 0
.L08004958: .4byte 0x00002210
.L0800495C:
    ldr r2, [r6, #8]
    movs r3, #1
    cmp r4, #0
    beq .L08004966
    movs r3, #0
.L08004966:
    ldr r0, .L0800497C @ =0x00002210
    adds r2, r2, r0
    lsls r3, r3, #3
    ldrb r1, [r2]
    movs r0, #9
    rsbs r0, r0, #0
.L08004972:
    ands r0, r1
    orrs r0, r3
    strb r0, [r2]
    b .L08004A08
    .align 2, 0
.L0800497C: .4byte 0x00002210
.L08004980:
    adds r0, r6, #0
    bl func_08003EEC
    adds r0, r6, #0
    adds r0, #0x85
    ldrb r0, [r0]
    lsls r0, r0, #2
    adds r4, r0, r6
    movs r1, #0xcc
    lsls r1, r1, #1
    adds r4, r4, r1
    movs r1, #0
    ldr r0, [r4]
    lsls r0, r0, #0x1f
    cmp r0, #0
    beq .L080049A2
    movs r1, #1
.L080049A2:
    adds r0, r6, #0
    adds r0, #0x86
    strb r1, [r0]
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    movs r1, #2
    bl func_08003DF0
    ldrb r0, [r4]
    lsrs r0, r0, #1
    mov r2, r8
    eors r0, r2
    ands r0, r2
    adds r1, r6, #0
    adds r1, #0x87
    strb r0, [r1]
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    movs r1, #3
    bl func_08003DF0
    ldrb r0, [r4]
    lsrs r0, r0, #2
    mov r1, r8
    eors r0, r1
    ands r0, r1
    adds r1, r6, #0
    adds r1, #0x88
    strb r0, [r1]
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    movs r1, #4
    bl func_08003DF0
    ldrb r0, [r4]
    lsrs r0, r0, #3
    mov r2, r8
    eors r0, r2
    ands r0, r2
    adds r1, r6, #0
    adds r1, #0x89
    strb r0, [r1]
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    movs r1, #5
    bl func_08003DF0
.L08004A08:
    ldr r1, [r5]
    ldr r2, [r6, #0x78]
    ldr r3, [r6, #0x7c]
    adds r0, r6, #0
    bl func_08003DF0
    b .L08004A92
.L08004A16:
    ldr r0, [r6, #8]
    cmp r0, #0
    bne .L08004A1E
    b .L08004674
.L08004A1E:
    lsls r1, r7, #0x18
    lsls r0, r7, #0x19
    lsrs r1, r1, #0x1f
    lsrs r0, r0, #0x1f
    cmp r1, r0
    bne .L08004A2C
    b .L08004674
.L08004A2C:
    adds r1, r6, #0
    adds r1, #0x80
    ldr r4, [r1]
    movs r0, #0x80
    ands r0, r7
    lsls r0, r0, #0x18
    lsrs r0, r0, #0x18
    adds r5, r1, #0
    cmp r0, #0
    beq .L08004A52
    cmp r4, #0
    bne .L08004A48
    mov r0, sb
    b .L08004A66
.L08004A48:
    movs r0, #0
    cmp r4, #5
    beq .L08004A66
    adds r0, r4, #1
    b .L08004A66
.L08004A52:
    cmp r4, #2
    beq .L08004A66
    cmp r4, #1
    bne .L08004A5E
    movs r0, #5
    b .L08004A66
.L08004A5E:
    movs r0, #5
    cmp r4, #0
    beq .L08004A66
    subs r0, r4, #1
.L08004A66:
    str r0, [r5]
    ldr r2, [r6, #0x5c]
    ldr r3, [r6, #0x60]
    adds r0, r6, #0
    adds r1, r4, #0
    bl func_08003DF0
    ldr r1, [r5]
    ldr r2, [r6, #0x78]
    ldr r3, [r6, #0x7c]
    adds r0, r6, #0
    bl func_08003DF0
    ldr r1, [r5]
    ldr r2, [r6, #0x78]
    ldr r3, [r6, #0x7c]
    adds r0, r6, #0
    bl func_08003E88
    adds r0, r6, #0
    bl func_08003EEC
.L08004A92:
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xcb
    bl func_08008B6C
    b .L08004674
.L08004A9E:
    adds r4, r6, #0
    adds r4, #0x10
    adds r0, r4, #0
    bl func_08050D34
    cmp r0, #3
    beq .L08004AB2
    cmp r0, #6
    bne .L08004AB2
    b .L08004674
.L08004AB2:
    adds r0, r4, #0
    bl func_08050DF0
    cmp r0, #1
    bne .L08004B04
.L08004ABC:
    adds r0, r6, #0
    bl func_08003F9C
    b .L08004674
.L08004AC4:
    adds r4, r6, #0
    adds r4, #0x10
    adds r0, r4, #0
    bl func_08050D34
    cmp r0, #3
    beq .L08004AD8
    cmp r0, #6
    bne .L08004AD8
    b .L08004674
.L08004AD8:
    adds r0, r4, #0
    bl func_08050DF0
    cmp r0, #1
    bne .L08004B04
    adds r0, r6, #0
    bl func_080040A0
    lsls r0, r0, #0x18
    cmp r0, #0
    bne .L08004AF0
    b .L08004674
.L08004AF0:
    add r4, sp, #0x54
.L08004AF2:
    adds r0, r4, #0
    movs r1, #0
    bl func_08008B54
    adds r0, r4, #0
    movs r1, #2
    bl func_08008BF8
    b .L08004B36
.L08004B04:
    adds r0, r6, #0
    adds r0, #0x18
    movs r1, #0xc5
    bl func_08008B6C
    adds r0, r6, #0
    bl func_08003EEC
    movs r0, #0
    str r0, [r5]
    b .L08004674
.L08004B1A:
    adds r0, r6, #0
    adds r0, #0x10
    bl func_08050D34
    cmp r0, #5
    bne .L08004B28
    b .L08004674
.L08004B28:
    adds r0, r6, #0
    bl func_08003EEC
    movs r0, #0
.L08004B30:
    mov r1, sl
    str r0, [r1]
    b .L08004674
.L08004B36:
    adds r0, r6, #0
    bl func_08003BB4
    ldr r1, [r6, #0xc]
    movs r0, #0
    str r0, [r6, #0xc]
    ldr r2, [sp, #0x58]
    str r1, [r2]
    ldr r0, [sp, #0x58]
    add sp, #0x5c
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1

    thumb_func_start func_08004B58
func_08004B58: @ 0x08004B58
    push {r4, lr}
    sub sp, #4
    adds r4, r0, #0
    ldr r0, .L08004B8C @ =vtable_unk_080E5A68
    str r0, [r4]
    movs r0, #4
    bl __builtin_new
    ldr r1, .L08004B90 @ =vtable_unk_080E5A3C
    str r1, [r0]
    str r0, [sp]
    movs r0, #0xd0
    lsls r0, r0, #1
    bl __builtin_new
    movs r1, #0
    mov r2, sp
    bl func_080041DC
    str r0, [r4, #4]
    adds r0, r4, #0
    add sp, #4
    pop {r4}
    pop {r1}
    bx r1
    .align 2, 0
.L08004B8C: .4byte vtable_unk_080E5A68
.L08004B90: .4byte vtable_unk_080E5A3C

    thumb_func_start func_08004B94
func_08004B94: @ 0x08004B94
    push {r4, r5, r6, lr}
    sub sp, #4
    adds r6, r0, #0
    adds r5, r1, #0
    adds r4, r2, #0
    ldr r0, .L08004BD8 @ =vtable_unk_080E5A68
    str r0, [r6]
    ldr r1, [r4]
    movs r0, #0
    str r0, [r4]
    str r1, [sp]
    movs r0, #0xd0
    lsls r0, r0, #1
    bl __builtin_new
    adds r1, r5, #0
    mov r2, sp
    bl func_080041DC
    str r0, [r6, #4]
    ldr r4, [r4]
    cmp r4, #0
    beq .L08004BCE
    ldr r0, [r4]
    ldr r2, [r0, #8]
    adds r0, r4, #0
    movs r1, #3
    bl _call_via_r2
.L08004BCE:
    adds r0, r6, #0
    add sp, #4
    pop {r4, r5, r6}
    pop {r1}
    bx r1
    .align 2, 0
.L08004BD8: .4byte vtable_unk_080E5A68

    thumb_func_start func_08004BDC
func_08004BDC: @ 0x08004BDC
    push {r4, r5, lr}
    adds r4, r0, #0
    adds r5, r1, #0
    ldr r0, .L08004C08 @ =vtable_unk_080E5A68
    str r0, [r4]
    ldr r1, [r4, #4]
    cmp r1, #0
    beq .L08004BF8
    ldr r0, [r1, #4]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004BF8:
    adds r0, r4, #0
    adds r1, r5, #0
    bl func_080007EC
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L08004C08: .4byte vtable_unk_080E5A68

    thumb_func_start func_08004C0C
func_08004C0C: @ 0x08004C0C
    push {r4, lr}
    sub sp, #0xc
    adds r4, r0, #0
    ldr r1, [r1, #4]
    mov r0, sp
    bl func_08004570
    ldr r2, [sp]
    mov r0, sp
    str r0, [sp, #4]
    str r2, [sp, #8]
    adds r1, r0, #0
    movs r0, #0
    str r0, [r1]
    str r2, [r4]
    ldr r1, [sp]
    cmp r1, #0
    beq .L08004C3C
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004C3C:
    adds r0, r4, #0
    add sp, #0xc
    pop {r4}
    pop {r1}
    bx r1
    .align 2, 0

    thumb_func_start func_08004C48
func_08004C48: @ 0x08004C48
    ldr r1, .L08004C50 @ =vtable_unk_080E5A88
    str r1, [r0]
    bx lr
    .align 2, 0
.L08004C50: .4byte vtable_unk_080E5A88

    thumb_func_start func_08004C54
func_08004C54: @ 0x08004C54
    push {lr}
    ldr r2, .L08004C64 @ =vtable_unk_080E5A88
    str r2, [r0]
    bl func_080007EC
    pop {r0}
    bx r0
    .align 2, 0
.L08004C64: .4byte vtable_unk_080E5A88

    thumb_func_start func_08004C68
func_08004C68: @ 0x08004C68
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x5c
    str r0, [sp, #0x4c]
    add r0, sp, #4
    bl func_08008980
    movs r0, #0x23
    bl func_08008DB8
    add r4, sp, #8
    movs r0, #0
    strb r0, [r4]
    add r3, sp, #0x18
    strb r0, [r3]
    add r2, sp, #0x28
    strb r0, [r2]
    subs r0, #4
    mov r1, r8
    ands r0, r1
    movs r1, #0x7d
    rsbs r1, r1, #0
    ands r0, r1
    mov r8, r0
    mov sb, r3
    mov r0, sp
    adds r0, #0x38
    str r0, [sp, #0x54]
    mov r1, sp
    adds r1, #0x44
    str r1, [sp, #0x58]
    adds r6, r0, #0
    add r0, sp, #8
    mov sl, r0
    add r7, sp, #0x40
.L08004CB4:
    adds r0, r6, #0
    ldr r1, .L08004EE8 @ =gUnk_080E8934
    mov r2, sl
    bl func_08007078
    adds r0, r7, #0
    adds r1, r6, #0
    bl func_080070D4
    ldr r1, [sp, #0x40]
    cmp r1, #0
    beq .L08004CD8
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004CD8:
    adds r0, r6, #0
    bl func_08007110
    adds r5, r0, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xc
    bls .L08004CEC
    movs r4, #0xc
.L08004CEC:
    mov r0, sl
    adds r1, r5, #0
    adds r2, r4, #0
    bl memcpy
    mov r1, sl
    adds r0, r1, r4
    movs r1, #0
    strb r1, [r0]
    adds r0, r6, #0
    movs r1, #2
    bl func_080070A4
    adds r0, r6, #0
    mov r1, r8
    bl func_0806E9D8
    adds r0, r7, #0
    adds r1, r6, #0
    bl func_0806EA30
    ldr r1, [sp, #0x40]
    cmp r1, #0
    beq .L08004D28
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004D28:
    adds r0, r6, #0
    bl func_0806EA6C
    mov r8, r0
    adds r0, r6, #0
    movs r1, #2
    bl func_0806EA00
    adds r0, r6, #0
    ldr r1, .L08004EEC @ =gUnk_080E893C
    mov r2, sb
    bl func_08007078
    adds r0, r7, #0
    adds r1, r6, #0
    bl func_080070D4
    ldr r1, [sp, #0x40]
    cmp r1, #0
    beq .L08004D5C
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004D5C:
    adds r0, r6, #0
    bl func_08007110
    adds r5, r0, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xc
    bls .L08004D70
    movs r4, #0xc
.L08004D70:
    mov r0, sb
    adds r1, r5, #0
    adds r2, r4, #0
    bl memcpy
    mov r1, sb
    adds r0, r1, r4
    movs r1, #0
    strb r1, [r0]
    adds r0, r6, #0
    movs r1, #2
    bl func_080070A4
    adds r0, r6, #0
    ldr r1, .L08004EF0 @ =gUnk_080E8944
    add r2, sp, #0x28
    bl func_08007078
    adds r0, r7, #0
    adds r1, r6, #0
    bl func_080070D4
    ldr r1, [sp, #0x40]
    cmp r1, #0
    beq .L08004DAE
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004DAE:
    adds r0, r6, #0
    bl func_08007110
    adds r5, r0, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xc
    bls .L08004DC2
    movs r4, #0xc
.L08004DC2:
    add r0, sp, #0x28
    adds r1, r5, #0
    adds r2, r4, #0
    bl memcpy
    mov r0, sp
    adds r0, r0, r4
    adds r0, #0x28
    movs r1, #0
    strb r1, [r0]
    adds r0, r6, #0
    movs r1, #2
    bl func_080070A4
    add r0, sp, #0x28
    str r0, [sp]
    adds r0, r6, #0
    mov r1, sl
    mov r2, r8
    mov r3, sb
    bl func_0800598C
    adds r0, r7, #0
    adds r1, r6, #0
    bl func_08005A00
    ldr r1, [sp, #0x40]
    cmp r1, #0
    beq .L08004E08
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004E08:
    adds r0, r6, #0
    bl func_08005A3C
    adds r4, r0, #0
    lsls r4, r4, #0x18
    lsrs r4, r4, #0x18
    adds r0, r6, #0
    movs r1, #2
    bl func_080059D0
    cmp r4, #0
    bne .L08004E22
    b .L08004CB4
.L08004E22:
    movs r0, #0x38
    bl __builtin_new
    adds r6, r0, #0
    mov r0, sb
    add r1, sp, #8
    mov sl, r1
    mov r1, sp
    adds r1, #0x28
    str r1, [sp, #0x50]
    ldr r1, .L08004EF4 @ =__vt_13AUnk_0800080C
    str r1, [r6]
    ldr r1, .L08004EF8 @ =vtable_unk_080E5A78
    adds r5, r6, #0
    stm r5!, {r1}
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xc
    bls .L08004E4C
    movs r4, #0xc
.L08004E4C:
    adds r0, r5, #0
    mov r1, sb
    adds r2, r4, #0
    bl memcpy
    adds r0, r5, r4
    movs r7, #0
    strb r7, [r0]
    adds r5, r6, #0
    adds r5, #0x14
    mov r0, sl
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xc
    bls .L08004E6E
    movs r4, #0xc
.L08004E6E:
    adds r0, r5, #0
    add r1, sp, #8
    adds r2, r4, #0
    bl memcpy
    adds r0, r5, r4
    strb r7, [r0]
    adds r0, r6, #0
    adds r0, #0x24
    mov r1, r8
    strb r1, [r0]
    adds r5, r6, #0
    adds r5, #0x28
    ldr r0, [sp, #0x50]
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xc
    bls .L08004E96
    movs r4, #0xc
.L08004E96:
    adds r0, r5, #0
    add r1, sp, #0x28
    adds r2, r4, #0
    bl memcpy
    adds r0, r5, r4
    movs r1, #0
    strb r1, [r0]
    str r6, [sp, #0x38]
    ldr r0, [sp, #0x54]
    str r0, [sp, #0x44]
    ldr r1, [sp, #0x58]
    str r6, [r1, #4]
    movs r0, #0
    ldr r1, [sp, #0x54]
    str r0, [r1]
    ldr r0, [sp, #0x4c]
    str r6, [r0]
    ldr r1, [sp, #0x38]
    cmp r1, #0
    beq .L08004ECC
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08004ECC:
    add r0, sp, #4
    movs r1, #2
    bl func_08008A68
    ldr r0, [sp, #0x4c]
    add sp, #0x5c
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0
.L08004EE8: .4byte gUnk_080E8934
.L08004EEC: .4byte gUnk_080E893C
.L08004EF0: .4byte gUnk_080E8944
.L08004EF4: .4byte __vt_13AUnk_0800080C
.L08004EF8: .4byte vtable_unk_080E5A78

    thumb_func_start func_08004EFC
func_08004EFC: @ 0x08004EFC
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x28
    adds r7, r0, #0
    adds r6, r1, #0
    mov r8, r2
    str r3, [sp, #0x24]
    bl func_08008444
    ldr r0, .L080050A4 @ =vtable_unk_080E5A98
    str r0, [r7, #4]
    movs r0, #3
    add r5, sp, #0x10
    add r1, sp, #0x14
    mov sb, r1
    movs r1, #1
    rsbs r1, r1, #0
.L08004F24:
    subs r0, #1
    cmp r0, r1
    bne .L08004F24
    movs r0, #3
    movs r1, #1
    rsbs r1, r1, #0
.L08004F30:
    subs r0, #1
    cmp r0, r1
    bne .L08004F30
    ldr r2, .L080050A8 @ =0x00001A28
    adds r1, r7, r2
    movs r0, #2
    str r0, [r1]
    movs r0, #4
    bl __builtin_new
    adds r4, r0, #0
    add r0, sp, #0xc
    bl func_0800835C
    adds r0, r5, #0
    bl func_0800770C
    movs r0, #0
    str r0, [sp]
    add r0, sp, #0xc
    str r0, [sp, #4]
    str r5, [sp, #8]
    adds r0, r4, #0
    movs r1, #0
    movs r2, #0x1c
    movs r3, #4
    bl func_08050CC0
    ldr r2, .L080050AC @ =0x00001A2C
    adds r1, r7, r2
    str r0, [r1]
    adds r0, r5, #0
    movs r1, #2
    bl func_08007714
    add r0, sp, #0xc
    movs r1, #2
    bl func_08008364
    ldr r0, .L080050B0 @ =0x00001A30
    adds r4, r7, r0
    movs r0, #0xc8
    bl func_08008D3C
    str r0, [r4]
    ldr r1, .L080050B4 @ =0x00001A34
    adds r0, r7, r1
    movs r1, #3
    movs r3, #0
    movs r2, #1
    rsbs r2, r2, #0
.L08004F96:
    strb r3, [r0]
    adds r0, #0x10
    subs r1, #1
    cmp r1, r2
    bne .L08004F96
    ldr r2, .L080050B8 @ =0x00001A76
    adds r0, r7, r2
    movs r1, #0
    mov sl, r1
    mov r2, sl
    strb r2, [r0]
    ldr r0, .L080050B4 @ =0x00001A34
    adds r5, r7, r0
    adds r0, r6, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xf
    bls .L08004FBE
    movs r4, #0xf
.L08004FBE:
    adds r0, r5, #0
    adds r1, r6, #0
    adds r2, r4, #0
    bl memcpy
    adds r0, r5, r4
    mov r1, sl
    strb r1, [r0]
    mov r2, r8
    lsls r0, r2, #0x19
    lsrs r0, r0, #0x1b
    adds r0, #1
    mov r1, sb
    movs r2, #2
    bl func_0804EC84
    mov r1, r8
    lsls r0, r1, #0x1e
    lsrs r0, r0, #0x1e
    bl func_0800E2E4
    mov sb, r0
    ldr r2, .L080050BC @ =0x00001A44
    adds r6, r7, r2
    mov r4, sb
    adds r0, r6, #0
    bl strlen
    adds r1, r6, r0
    mov r8, r1
    movs r1, #0xf
    subs r5, r1, r0
    cmp r5, #0
    beq .L08005022
    adds r0, r4, #0
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08005010
    adds r4, r5, #0
.L08005010:
    mov r0, r8
    mov r1, sb
    adds r2, r4, #0
    bl memcpy
    mov r2, r8
    adds r0, r2, r4
    mov r1, sl
    strb r1, [r0]
.L08005022:
    adds r0, r6, #0
    bl strlen
    adds r6, r6, r0
    movs r1, #0xf
    subs r5, r1, r0
    cmp r5, #0
    beq .L08005050
    add r0, sp, #0x14
    bl strlen
    adds r4, r0, #0
    cmp r4, r5
    bls .L08005040
    adds r4, r5, #0
.L08005040:
    adds r0, r6, #0
    add r1, sp, #0x14
    adds r2, r4, #0
    bl memcpy
    adds r1, r6, r4
    movs r0, #0
    strb r0, [r1]
.L08005050:
    ldr r2, .L080050C0 @ =0x00001A54
    adds r5, r7, r2
    ldr r0, [sp, #0x24]
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xf
    bls .L08005062
    movs r4, #0xf
.L08005062:
    adds r0, r5, #0
    ldr r1, [sp, #0x24]
    adds r2, r4, #0
    bl memcpy
    adds r0, r5, r4
    movs r6, #0
    strb r6, [r0]
    ldr r0, .L080050C4 @ =0x00001A64
    adds r5, r7, r0
    ldr r0, [sp, #0x48]
    bl strlen
    adds r4, r0, #0
    cmp r4, #0xf
    bls .L08005084
    movs r4, #0xf
.L08005084:
    adds r0, r5, #0
    ldr r1, [sp, #0x48]
    adds r2, r4, #0
    bl memcpy
    adds r0, r5, r4
    strb r6, [r0]
    adds r0, r7, #0
    add sp, #0x28
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0
.L080050A4: .4byte vtable_unk_080E5A98
.L080050A8: .4byte 0x00001A28
.L080050AC: .4byte 0x00001A2C
.L080050B0: .4byte 0x00001A30
.L080050B4: .4byte 0x00001A34
.L080050B8: .4byte 0x00001A76
.L080050BC: .4byte 0x00001A44
.L080050C0: .4byte 0x00001A54
.L080050C4: .4byte 0x00001A64

    thumb_func_start func_080050C8
func_080050C8: @ 0x080050C8
    push {r4, r5, lr}
    adds r4, r0, #0
    adds r5, r1, #0
    ldr r0, .L080050F0 @ =vtable_unk_080E5A98
    str r0, [r4, #4]
    ldr r1, .L080050F4 @ =0x00001A2C
    adds r0, r4, r1
    ldr r0, [r0]
    cmp r0, #0
    beq .L080050E2
    movs r1, #3
    bl func_08050D0C
.L080050E2:
    adds r0, r4, #0
    adds r1, r5, #0
    bl func_080086BC
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L080050F0: .4byte vtable_unk_080E5A98
.L080050F4: .4byte 0x00001A2C

    thumb_func_start func_080050F8
func_080050F8: @ 0x080050F8
    push {r4, r5, r6, r7, lr}
    mov r7, sb
    mov r6, r8
    push {r6, r7}
    sub sp, #0x14
    mov sb, r0
    adds r6, r1, #0
    adds r0, r6, #0
    bl func_08005254
    adds r0, r6, #0
    bl func_08005260
    adds r0, r6, #0
    bl func_08005278
    adds r0, r6, #0
    bl func_08008918
    mov r1, sp
    movs r2, #0x3f
    strh r2, [r1]
    adds r0, #0x50
    strh r2, [r0]
    movs r0, #0x10
    bl __builtin_new
    adds r4, r0, #0
    adds r0, r6, #0
    bl func_08008918
    adds r1, r0, #0
    movs r0, #0
    str r0, [r4]
    str r0, [r4, #4]
    ldr r0, .L08005198 @ =vtable_unk_080E5B80
    str r0, [r4, #8]
    adds r5, r4, #0
    adds r5, #0xc
    adds r0, r5, #0
    bl func_08009300
    str r4, [sp, #4]
    ldr r1, .L0800519C @ =0x00000889
    adds r0, r5, #0
    movs r2, #1
    movs r3, #1
    bl func_0800934C
    adds r0, r6, #0
    bl func_08008940
    ldr r2, [r0, #8]
    ldr r1, [sp, #4]
    ldr r2, [r2, #0x10]
    bl _call_via_r2
    movs r4, #0
    movs r5, #0
    add r7, sp, #8
    add r0, sp, #0xc
    mov r8, r0
.L08005174:
    adds r0, r6, #0
    bl func_080087C8
    adds r0, r6, #0
    bl func_080088B8
    adds r0, r6, #0
    bl func_080088D4
    adds r0, r4, #0
    cmp r0, #1
    beq .L080051BA
    cmp r0, #1
    bgt .L080051A0
    cmp r0, #0
    beq .L080051AA
    b .L0800520A
    .align 2, 0
.L08005198: .4byte vtable_unk_080E5B80
.L0800519C: .4byte 0x00000889
.L080051A0:
    cmp r0, #2
    beq .L080051D4
    cmp r0, #3
    beq .L080051FC
    b .L0800520A
.L080051AA:
    ldr r0, [sp, #4]
    ldr r1, [r0]
    rsbs r0, r1, #0
    orrs r0, r1
    cmp r0, #0
    blt .L0800520A
    movs r4, #1
    b .L0800520A
.L080051BA:
    adds r0, r6, #0
    bl func_08005800
    ldr r1, .L080051D0 @ =0x00001A74
    adds r0, r6, r1
    ldrb r0, [r0]
    cmp r0, #0
    beq .L0800520A
    movs r4, #2
    b .L0800520A
    .align 2, 0
.L080051D0: .4byte 0x00001A74
.L080051D4:
    ldr r0, [sp, #4]
    adds r0, #0xc
    ldr r1, .L080051F8 @ =0x00000889
    movs r2, #1
    movs r3, #1
    bl func_08009378
    adds r0, r6, #0
    bl func_08008940
    ldr r2, [r0, #8]
    ldr r1, [sp, #4]
    ldr r2, [r2, #0x10]
    bl _call_via_r2
    movs r4, #3
    b .L0800520A
    .align 2, 0
.L080051F8: .4byte 0x00000889
.L080051FC:
    ldr r0, [sp, #4]
    ldr r1, [r0]
    rsbs r0, r1, #0
    orrs r0, r1
    cmp r0, #0
    blt .L0800520A
    movs r5, #1
.L0800520A:
    cmp r5, #0
    beq .L08005174
    movs r0, #0
    str r0, [sp, #8]
    str r7, [sp, #0xc]
    mov r1, r8
    str r0, [r1, #4]
    str r0, [r7]
    mov r1, sb
    str r0, [r1]
    ldr r1, [sp, #8]
    cmp r1, #0
    beq .L08005230
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08005230:
    ldr r1, [sp, #4]
    cmp r1, #0
    beq .L08005242
    ldr r0, [r1, #8]
    ldr r2, [r0, #0xc]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08005242:
    mov r0, sb
    add sp, #0x14
    pop {r3, r4}
    mov r8, r3
    mov sb, r4
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0

    thumb_func_start func_08005254
func_08005254: @ 0x08005254
    push {lr}
    bl func_08008724
    pop {r0}
    bx r0
    .align 2, 0

    thumb_func_start func_08005260
func_08005260: @ 0x08005260
    ldr r2, .L08005270 @ =0x00001A75
    adds r1, r0, r2
    movs r2, #0
    strb r2, [r1]
    ldr r1, .L08005274 @ =0x00001A74
    adds r0, r0, r1
    strb r2, [r0]
    bx lr
    .align 2, 0
.L08005270: .4byte 0x00001A75
.L08005274: .4byte 0x00001A74

    thumb_func_start func_08005278
func_08005278: @ 0x08005278
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x94
    mov sl, r0
    ldr r0, .L08005488 @ =gUnk_080F9F70
    ldr r0, [r0]
    ldr r1, .L0800548C @ =0x06004B00
    ldr r2, .L08005490 @ =gUnk_080F9F74
    ldr r2, [r2]
    bl func_08008E64
    ldr r0, .L08005494 @ =gUnk_080F9F78
    ldr r0, [r0]
    movs r1, #0xa0
    lsls r1, r1, #0x13
    movs r2, #0x20
    bl func_08008E64
    mov r0, sl
    bl func_08008918
    add r1, sp, #0xc
    movs r3, #0xba
    lsls r3, r3, #5
    adds r2, r3, #0
    strh r2, [r1]
    movs r4, #0
    strh r2, [r0]
    mov r0, sl
    bl func_08008918
    add r2, sp, #0xc
    ldr r5, .L08005498 @ =0x00001841
    adds r1, r5, #0
    strh r1, [r2]
    strh r1, [r0, #0xa]
    mov r0, sl
    bl func_08008918
    add r2, sp, #0xc
    ldr r7, .L0800549C @ =0x00001F01
    adds r1, r7, #0
    strh r1, [r2]
    strh r1, [r0, #0xc]
    ldr r0, .L080054A0 @ =0x0600F800
    movs r1, #0x14
    str r1, [sp]
    movs r1, #0x96
    lsls r1, r1, #2
    str r1, [sp, #4]
    str r4, [sp, #8]
    movs r1, #0
    movs r2, #0
    movs r3, #0x1e
    bl func_08051320
    ldr r1, .L080054A4 @ =0x06FFC000
    movs r0, #0
    movs r2, #0x20
    bl func_08008EB8
    movs r0, #0
    mov r8, r0
    add r5, sp, #0x20
    add r1, sp, #0x24
    mov sb, r1
    mov r2, sp
    adds r2, #0x28
    str r2, [sp, #0x64]
    mov r3, sp
    adds r3, #0x2c
    str r3, [sp, #0x68]
    mov r4, sp
    adds r4, #0x30
    str r4, [sp, #0x70]
    mov r7, sp
    adds r7, #0x34
    str r7, [sp, #0x74]
    mov r0, sp
    adds r0, #0x38
    str r0, [sp, #0x78]
    mov r1, sp
    adds r1, #0x10
    str r1, [sp, #0x5c]
    movs r7, #0xc
    movs r6, #2
    mov r4, sl
    adds r4, #0xc
.L0800532E:
    add r0, sp, #0x20
    strh r7, [r0]
    strh r6, [r5, #2]
    ldr r0, [sp, #0x20]
    adds r1, r4, #0
    movs r2, #0
    bl func_0804E7A0
    movs r2, #0xc1
    lsls r2, r2, #2
    adds r4, r4, r2
    movs r3, #1
    add r8, r3
    mov r0, r8
    cmp r0, #3
    bls .L0800532E
    movs r1, #0
    mov r8, r1
    ldr r7, .L080054A8 @ =0x00000C1C
    add r7, sl
    movs r2, #0xfa
    lsls r2, r2, #4
    add r2, sl
    str r2, [sp, #0x54]
    ldr r3, .L080054AC @ =0x00001324
    add r3, sl
    str r3, [sp, #0x58]
    ldr r4, .L080054B0 @ =0x000016A8
    add r4, sl
    str r4, [sp, #0x6c]
    movs r6, #0xe
    movs r5, #2
    ldr r4, .L080054A8 @ =0x00000C1C
    add r4, sl
.L08005372:
    add r0, sp, #0x24
    strh r6, [r0]
    mov r0, sb
    strh r5, [r0, #2]
    ldr r0, [sp, #0x24]
    adds r1, r4, #0
    movs r2, #0
    bl func_0804E7A0
    movs r1, #0xe1
    lsls r1, r1, #2
    adds r4, r4, r1
    movs r2, #1
    add r8, r2
    mov r3, r8
    cmp r3, #3
    bls .L08005372
    movs r4, #0
    mov r8, r4
    movs r6, #0xc
    movs r5, #2
    mov r4, sl
    adds r4, #0xc
.L080053A0:
    mov r0, r8
    lsls r1, r0, #4
    add r1, sl
    ldr r2, .L080054B4 @ =0x00001A34
    adds r1, r1, r2
    add r0, sp, #0x28
    strh r6, [r0]
    ldr r3, [sp, #0x64]
    strh r5, [r3, #2]
    ldr r0, [sp, #0x28]
    str r1, [sp]
    adds r1, r4, #0
    movs r2, #0
    movs r3, #0
    bl func_0804E8F0
    movs r0, #0xc1
    lsls r0, r0, #2
    adds r4, r4, r0
    movs r1, #1
    add r8, r1
    mov r2, r8
    cmp r2, #3
    bls .L080053A0
    ldr r1, .L080054B8 @ =gUnk_080E8958
    movs r4, #0xe
    movs r5, #2
    add r0, sp, #0x2c
    strh r4, [r0]
    ldr r3, [sp, #0x68]
    strh r5, [r3, #2]
    ldr r0, [sp, #0x2c]
    str r1, [sp]
    adds r1, r7, #0
    movs r2, #0
    movs r3, #0
    bl func_0804E8F0
    ldr r1, .L080054BC @ =gUnk_080E8968
    add r0, sp, #0x30
    strh r4, [r0]
    ldr r7, [sp, #0x70]
    strh r5, [r7, #2]
    ldr r0, [sp, #0x30]
    str r1, [sp]
    ldr r1, [sp, #0x54]
    movs r2, #0
    movs r3, #0
    bl func_0804E8F0
    ldr r1, .L080054C0 @ =gUnk_080E8978
    add r0, sp, #0x34
    strh r4, [r0]
    ldr r0, [sp, #0x74]
    strh r5, [r0, #2]
    ldr r0, [sp, #0x34]
    str r1, [sp]
    ldr r1, [sp, #0x58]
    movs r2, #0
    movs r3, #0
    bl func_0804E8F0
    ldr r1, .L080054C4 @ =gUnk_080E8988
    add r0, sp, #0x38
    strh r4, [r0]
    ldr r2, [sp, #0x78]
    strh r5, [r2, #2]
    ldr r0, [sp, #0x38]
    str r1, [sp]
    ldr r1, [sp, #0x6c]
    movs r2, #0
    movs r3, #0
    bl func_0804E8F0
    movs r3, #0
    mov r8, r3
    ldr r4, [sp, #0x5c]
    str r4, [sp, #0x4c]
    movs r5, #0xc0
    lsls r5, r5, #0x13
    str r5, [sp, #0x84]
    mov r7, sl
    adds r7, #0xc
    str r7, [sp, #0x88]
.L08005448:
    mov r0, sl
    bl func_08008910
    adds r6, r0, #0
    add r0, sp, #0x10
    ldr r1, [sp, #0x88]
    ldr r2, [sp, #0x84]
    movs r3, #0xc0
    lsls r3, r3, #2
    bl func_08008F0C
    ldr r1, [r6, #4]
    ldr r0, [r6, #0xc]
    cmp r1, r0
    beq .L080054C8
    cmp r1, #0
    beq .L08005476
    adds r0, r1, #0
    ldr r1, [sp, #0x4c]
    ldm r1!, {r2, r3, r4}
    stm r0!, {r2, r3, r4}
    ldr r1, [r1]
    str r1, [r0]
.L08005476:
    ldr r0, [r6, #4]
    adds r0, #0x10
    str r0, [r6, #4]
    movs r5, #0xc0
    lsls r5, r5, #2
    lsls r5, r5, #2
    str r5, [sp, #0x60]
    b .L08005596
    .align 2, 0
.L08005488: .4byte gUnk_080F9F70
.L0800548C: .4byte 0x06004B00
.L08005490: .4byte gUnk_080F9F74
.L08005494: .4byte gUnk_080F9F78
.L08005498: .4byte 0x00001841
.L0800549C: .4byte 0x00001F01
.L080054A0: .4byte 0x0600F800
.L080054A4: .4byte 0x06FFC000
.L080054A8: .4byte 0x00000C1C
.L080054AC: .4byte 0x00001324
.L080054B0: .4byte 0x000016A8
.L080054B4: .4byte 0x00001A34
.L080054B8: .4byte gUnk_080E8958
.L080054BC: .4byte gUnk_080E8968
.L080054C0: .4byte gUnk_080E8978
.L080054C4: .4byte gUnk_080E8988
.L080054C8:
    str r1, [sp, #0x8c]
    movs r0, #1
    str r0, [sp, #0x40]
    ldr r0, [r6]
    adds r7, r1, #0
    subs r0, r7, r0
    asrs r4, r0, #4
    str r4, [sp, #0x3c]
    add r1, sp, #0x40
    add r0, sp, #0x3c
    cmp r4, #1
    bhs .L080054E2
    adds r0, r1, #0
.L080054E2:
    ldr r0, [r0]
    adds r0, r4, r0
    cmp r0, #0
    beq .L08005500
    lsls r4, r0, #4
    adds r0, r4, #0
    bl malloc
    mov sb, r4
    cmp r0, #0
    bne .L08005504
    mov r0, sb
    bl func_080D3BC0
    b .L08005504
.L08005500:
    movs r0, #0
    mov sb, r0
.L08005504:
    adds r5, r0, #0
    str r5, [sp, #0x90]
    ldr r2, [r6]
    adds r3, r5, #0
    movs r0, #0xc0
    lsls r0, r0, #2
    lsls r0, r0, #2
    str r0, [sp, #0x60]
    ldr r1, [sp, #0x8c]
    cmp r2, r1
    beq .L08005534
.L0800551A:
    cmp r3, #0
    beq .L0800552A
    adds r0, r3, #0
    adds r1, r2, #0
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L0800552A:
    adds r2, #0x10
    adds r3, #0x10
    ldr r0, [sp, #0x8c]
    cmp r2, r0
    bne .L0800551A
.L08005534:
    adds r5, r3, #0
    ldr r0, [sp, #0x40]
    cmp r0, #1
    bne .L08005550
    cmp r5, #0
    beq .L0800554C
    adds r0, r5, #0
    ldr r1, [sp, #0x4c]
    ldm r1!, {r2, r3, r4}
    stm r0!, {r2, r3, r4}
    ldr r1, [r1]
    str r1, [r0]
.L0800554C:
    adds r5, #0x10
    b .L08005572
.L08005550:
    adds r3, r0, #0
    adds r2, r5, #0
    cmp r3, #0
    beq .L08005570
.L08005558:
    cmp r2, #0
    beq .L08005568
    adds r0, r2, #0
    ldr r1, [sp, #0x4c]
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08005568:
    subs r3, #1
    adds r2, #0x10
    cmp r3, #0
    bne .L08005558
.L08005570:
    adds r5, r2, #0
.L08005572:
    ldr r2, [r6, #4]
    ldr r0, [r6]
    adds r1, r0, #0
    cmp r0, r2
    beq .L08005582
.L0800557C:
    adds r1, #0x10
    cmp r1, r2
    bne .L0800557C
.L08005582:
    cmp r0, #0
    beq .L0800558A
    bl free
.L0800558A:
    ldr r0, [sp, #0x90]
    add r0, sb
    ldr r7, [sp, #0x90]
    str r7, [r6]
    str r5, [r6, #4]
    str r0, [r6, #0xc]
.L08005596:
    ldr r0, [sp, #0x84]
    movs r1, #0xc0
    lsls r1, r1, #2
    adds r0, r0, r1
    str r0, [sp, #0x84]
    ldr r2, [sp, #0x88]
    movs r3, #0xc1
    lsls r3, r3, #2
    adds r2, r2, r3
    str r2, [sp, #0x88]
    movs r4, #1
    add r8, r4
    mov r5, r8
    cmp r5, #3
    bhi .L080055B6
    b .L08005448
.L080055B6:
    movs r7, #0
    mov r8, r7
    mov r0, sp
    adds r0, #0xc
    str r0, [sp, #0x50]
    movs r0, #0xc0
    lsls r0, r0, #0x13
    ldr r1, [sp, #0x60]
    adds r0, r1, r0
    str r0, [sp, #0x7c]
    ldr r2, .L08005608 @ =0x00000C1C
    add r2, sl
    str r2, [sp, #0x80]
.L080055D0:
    mov r0, sl
    bl func_08008910
    adds r6, r0, #0
    add r0, sp, #0xc
    ldr r1, [sp, #0x80]
    ldr r2, [sp, #0x7c]
    movs r3, #0xe0
    lsls r3, r3, #2
    bl func_08008F0C
    ldr r1, [r6, #4]
    ldr r0, [r6, #0xc]
    cmp r1, r0
    beq .L0800560C
    cmp r1, #0
    beq .L080055FE
    adds r0, r1, #0
    add r1, sp, #0xc
    ldm r1!, {r3, r4, r5}
    stm r0!, {r3, r4, r5}
    ldr r1, [r1]
    str r1, [r0]
.L080055FE:
    ldr r0, [r6, #4]
    adds r0, #0x10
    str r0, [r6, #4]
    b .L080056CE
    .align 2, 0
.L08005608: .4byte 0x00000C1C
.L0800560C:
    str r1, [sp, #0x8c]
    movs r0, #1
    str r0, [sp, #0x48]
    ldr r0, [r6]
    adds r7, r1, #0
    subs r0, r7, r0
    asrs r4, r0, #4
    str r4, [sp, #0x44]
    add r1, sp, #0x48
    add r0, sp, #0x44
    cmp r4, #1
    bhs .L08005626
    adds r0, r1, #0
.L08005626:
    ldr r0, [r0]
    adds r0, r4, r0
    cmp r0, #0
    beq .L08005644
    lsls r4, r0, #4
    adds r0, r4, #0
    bl malloc
    mov sb, r4
    cmp r0, #0
    bne .L08005648
    mov r0, sb
    bl func_080D3BC0
    b .L08005648
.L08005644:
    movs r0, #0
    mov sb, r0
.L08005648:
    adds r5, r0, #0
    str r5, [sp, #0x90]
    ldr r2, [r6]
    adds r3, r5, #0
    b .L08005666
.L08005652:
    cmp r3, #0
    beq .L08005662
    adds r0, r3, #0
    adds r1, r2, #0
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08005662:
    adds r2, #0x10
    adds r3, #0x10
.L08005666:
    ldr r0, [sp, #0x8c]
    cmp r2, r0
    bne .L08005652
    adds r5, r3, #0
    ldr r0, [sp, #0x48]
    cmp r0, #1
    bne .L08005688
    cmp r5, #0
    beq .L08005684
    adds r0, r5, #0
    ldr r1, [sp, #0x50]
    ldm r1!, {r2, r3, r4}
    stm r0!, {r2, r3, r4}
    ldr r1, [r1]
    str r1, [r0]
.L08005684:
    adds r5, #0x10
    b .L080056AA
.L08005688:
    adds r3, r0, #0
    adds r2, r5, #0
    cmp r3, #0
    beq .L080056A8
.L08005690:
    cmp r2, #0
    beq .L080056A0
    adds r0, r2, #0
    ldr r1, [sp, #0x50]
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L080056A0:
    subs r3, #1
    adds r2, #0x10
    cmp r3, #0
    bne .L08005690
.L080056A8:
    adds r5, r2, #0
.L080056AA:
    ldr r2, [r6, #4]
    ldr r0, [r6]
    adds r1, r0, #0
    cmp r0, r2
    beq .L080056BA
.L080056B4:
    adds r1, #0x10
    cmp r1, r2
    bne .L080056B4
.L080056BA:
    cmp r0, #0
    beq .L080056C2
    bl free
.L080056C2:
    ldr r0, [sp, #0x90]
    add r0, sb
    ldr r7, [sp, #0x90]
    str r7, [r6]
    str r5, [r6, #4]
    str r0, [r6, #0xc]
.L080056CE:
    ldr r0, [sp, #0x7c]
    movs r1, #0xe0
    lsls r1, r1, #2
    adds r0, r0, r1
    str r0, [sp, #0x7c]
    ldr r2, [sp, #0x80]
    movs r3, #0xe1
    lsls r3, r3, #2
    adds r2, r2, r3
    str r2, [sp, #0x80]
    movs r4, #1
    add r8, r4
    mov r5, r8
    cmp r5, #3
    bhi .L080056EE
    b .L080055D0
.L080056EE:
    movs r0, #1
    rsbs r0, r0, #0
    ldr r4, .L080057E8 @ =0x0600C000
    movs r2, #0x80
    lsls r2, r2, #4
    adds r1, r4, #0
    bl func_08008EB8
    movs r7, #0
    mov r8, r7
    movs r1, #0x64
.L08005704:
    movs r5, #0
    mov r2, r8
    lsls r0, r2, #6
    adds r0, r0, r4
.L0800570C:
    strh r1, [r0]
    adds r0, #2
    adds r5, #1
    cmp r5, #0x1d
    bls .L0800570C
    movs r3, #1
    add r8, r3
    mov r5, r8
    cmp r5, #0x13
    bls .L08005704
    movs r5, #2
    ldr r6, .L080057EC @ =0x0600C080
.L08005724:
    movs r7, #0
    mov r8, r7
    lsls r1, r5, #1
    adds r4, r5, #0
    adds r4, #0x6c
    adds r3, r5, #0
    adds r3, #0x5e
    ldr r0, .L080057F0 @ =0x0600C040
    adds r2, r1, r0
.L08005736:
    strh r3, [r2]
    adds r0, r1, r6
    strh r4, [r0]
    adds r4, #0x1c
    adds r3, #0x1c
    adds r2, #0xc0
    adds r1, #0xc0
    movs r7, #1
    add r8, r7
    mov r0, r8
    cmp r0, #3
    bls .L08005736
    adds r5, #1
    cmp r5, #0xf
    bls .L08005724
    movs r5, #0x10
    ldr r1, .L080057F4 @ =0x0000FFF0
    adds r7, r1, #0
    ldr r2, .L080057EC @ =0x0600C080
    mov sb, r2
.L0800575E:
    movs r3, #0
    mov r8, r3
    lsls r1, r5, #1
    adds r6, r5, #1
    adds r0, r5, #0
    adds r0, #0xc
    adds r4, r0, r7
    adds r3, r5, r7
    ldr r5, .L080057F0 @ =0x0600C040
    adds r2, r1, r5
.L08005772:
    strh r3, [r2]
    mov r5, sb
    adds r0, r1, r5
    strh r4, [r0]
    adds r4, #0x18
    adds r3, #0x18
    adds r2, #0xc0
    adds r1, #0xc0
    movs r0, #1
    add r8, r0
    mov r5, r8
    cmp r5, #3
    bls .L08005772
    adds r5, r6, #0
    cmp r5, #0x1b
    bls .L0800575E
    ldr r0, .L080057F8 @ =0x00001A2C
    add r0, sl
    ldr r0, [r0]
    mov sb, r0
    mov r0, sl
    bl func_080088DC
    mov r8, r0
    mov r0, sl
    bl func_08008920
    adds r6, r0, #0
    mov r0, sl
    bl func_08008918
    adds r5, r0, #0
    mov r0, sl
    bl func_08008940
    adds r4, r0, #0
    mov r0, sl
    bl func_0800894C
    ldr r1, .L080057FC @ =0x00001A30
    add r1, sl
    str r4, [sp]
    str r0, [sp, #4]
    str r1, [sp, #8]
    mov r0, sb
    mov r1, r8
    adds r2, r6, #0
    adds r3, r5, #0
    bl func_08050D3C
    add sp, #0x94
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L080057E8: .4byte 0x0600C000
.L080057EC: .4byte 0x0600C080
.L080057F0: .4byte 0x0600C040
.L080057F4: .4byte 0x0000FFF0
.L080057F8: .4byte 0x00001A2C
.L080057FC: .4byte 0x00001A30

    thumb_func_start func_08005800
func_08005800: @ 0x08005800
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0xc
    adds r7, r0, #0
    ldr r0, .L0800586C @ =0x00001A2C
    adds r4, r7, r0
    ldr r0, [r4]
    bl func_08050D34
    adds r6, r0, #0
    ldr r4, [r4]
    mov sb, r4
    adds r0, r7, #0
    bl func_080088DC
    mov r8, r0
    adds r0, r7, #0
    bl func_08008920
    mov sl, r0
    adds r0, r7, #0
    bl func_08008918
    adds r5, r0, #0
    adds r0, r7, #0
    bl func_08008940
    adds r4, r0, #0
    adds r0, r7, #0
    bl func_0800894C
    ldr r2, .L08005870 @ =0x00001A30
    adds r1, r7, r2
    str r4, [sp]
    str r0, [sp, #4]
    str r1, [sp, #8]
    mov r0, sb
    mov r1, r8
    mov r2, sl
    adds r3, r5, #0
    bl func_08050D3C
    cmp r0, #6
    bls .L08005860
    b .L08005974
.L08005860:
    lsls r0, r0, #2
    ldr r1, .L08005874 @ =.L08005878
    adds r0, r0, r1
    ldr r0, [r0]
    mov pc, r0
    .align 2, 0
.L0800586C: .4byte 0x00001A2C
.L08005870: .4byte 0x00001A30
.L08005874: .4byte .L08005878
.L08005878: @ jump table
    .4byte .L08005894 @ case 0
    .4byte .L08005974 @ case 1
    .4byte .L08005974 @ case 2
    .4byte .L080058C0 @ case 3
    .4byte .L08005974 @ case 4
    .4byte .L08005974 @ case 5
    .4byte .L08005974 @ case 6
.L08005894:
    ldr r1, .L080058B4 @ =0x00001A75
    adds r0, r7, r1
    ldrb r0, [r0]
    cmp r0, #0
    beq .L080058A6
    ldr r2, .L080058B8 @ =0x00001A74
    adds r1, r7, r2
    movs r0, #1
    strb r0, [r1]
.L080058A6:
    ldr r1, .L080058BC @ =0x00001A2C
    adds r0, r7, r1
    ldr r0, [r0]
    bl func_08050D5C
    b .L08005974
    .align 2, 0
.L080058B4: .4byte 0x00001A75
.L080058B8: .4byte 0x00001A74
.L080058BC: .4byte 0x00001A2C
.L080058C0:
    cmp r6, #5
    bgt .L080058CE
    cmp r6, #4
    bge .L08005974
    cmp r6, #1
    beq .L080058E4
    b .L080058D2
.L080058CE:
    cmp r6, #6
    beq .L08005910
.L080058D2:
    ldr r2, .L080058E0 @ =0x00001A2C
    adds r0, r7, r2
    ldr r0, [r0]
    bl func_08050D74
    b .L08005974
    .align 2, 0
.L080058E0: .4byte 0x00001A2C
.L080058E4:
    ldr r1, .L08005900 @ =0x00001A2C
    adds r0, r7, r1
    ldr r0, [r0]
    ldr r1, .L08005904 @ =gUnk_080E8998
    ldr r2, .L08005908 @ =gUnk_080E89A4
    ldr r3, .L0800590C @ =gUnk_080E89A8
    movs r4, #0
    str r4, [sp]
    str r4, [sp, #4]
    str r4, [sp, #8]
    bl func_08050E30
    b .L08005974
    .align 2, 0
.L08005900: .4byte 0x00001A2C
.L08005904: .4byte gUnk_080E8998
.L08005908: .4byte gUnk_080E89A4
.L0800590C: .4byte gUnk_080E89A8
.L08005910:
    ldr r2, .L08005928 @ =0x00001A2C
    adds r0, r7, r2
    ldr r0, [r0]
    bl func_08050DF0
    cmp r0, #6
    bhi .L08005974
    lsls r0, r0, #2
    ldr r1, .L0800592C @ =.L08005930
    adds r0, r0, r1
    ldr r0, [r0]
    mov pc, r0
    .align 2, 0
.L08005928: .4byte 0x00001A2C
.L0800592C: .4byte .L08005930
.L08005930: @ jump table
    .4byte .L08005974 @ case 0
    .4byte .L0800594C @ case 1
    .4byte .L08005964 @ case 2
    .4byte .L08005974 @ case 3
    .4byte .L08005974 @ case 4
    .4byte .L08005974 @ case 5
    .4byte .L08005974 @ case 6
.L0800594C:
    ldr r1, .L0800595C @ =0x00001A75
    adds r0, r7, r1
    movs r1, #1
    strb r1, [r0]
    ldr r2, .L08005960 @ =0x00001A76
    adds r0, r7, r2
    strb r1, [r0]
    b .L08005974
    .align 2, 0
.L0800595C: .4byte 0x00001A75
.L08005960: .4byte 0x00001A76
.L08005964:
    ldr r0, .L08005984 @ =0x00001A75
    adds r1, r7, r0
    movs r2, #0
    movs r0, #1
    strb r0, [r1]
    ldr r1, .L08005988 @ =0x00001A76
    adds r0, r7, r1
    strb r2, [r0]
.L08005974:
    add sp, #0xc
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L08005984: .4byte 0x00001A75
.L08005988: .4byte 0x00001A76

    thumb_func_start func_0800598C
func_0800598C: @ 0x0800598C
    push {r4, r5, r6, lr}
    mov r6, sb
    mov r5, r8
    push {r5, r6}
    sub sp, #4
    adds r4, r0, #0
    adds r6, r1, #0
    mov r8, r2
    mov sb, r3
    ldr r5, [sp, #0x1c]
    ldr r0, .L080059C8 @ =vtable_unk_080E5AA4
    str r0, [r4]
    ldr r0, .L080059CC @ =0x00001A78
    bl __builtin_new
    str r5, [sp]
    adds r1, r6, #0
    mov r2, r8
    mov r3, sb
    bl func_08004EFC
    str r0, [r4, #4]
    adds r0, r4, #0
    add sp, #4
    pop {r3, r4}
    mov r8, r3
    mov sb, r4
    pop {r4, r5, r6}
    pop {r1}
    bx r1
    .align 2, 0
.L080059C8: .4byte vtable_unk_080E5AA4
.L080059CC: .4byte 0x00001A78

    thumb_func_start func_080059D0
func_080059D0: @ 0x080059D0
    push {r4, r5, lr}
    adds r4, r0, #0
    adds r5, r1, #0
    ldr r0, .L080059FC @ =vtable_unk_080E5AA4
    str r0, [r4]
    ldr r1, [r4, #4]
    cmp r1, #0
    beq .L080059EC
    ldr r0, [r1, #4]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L080059EC:
    adds r0, r4, #0
    adds r1, r5, #0
    bl func_080007EC
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L080059FC: .4byte vtable_unk_080E5AA4

    thumb_func_start func_08005A00
func_08005A00: @ 0x08005A00
    push {r4, lr}
    sub sp, #0xc
    adds r4, r0, #0
    ldr r1, [r1, #4]
    mov r0, sp
    bl func_080050F8
    ldr r2, [sp]
    mov r0, sp
    str r0, [sp, #4]
    str r2, [sp, #8]
    adds r1, r0, #0
    movs r0, #0
    str r0, [r1]
    str r2, [r4]
    ldr r1, [sp]
    cmp r1, #0
    beq .L08005A30
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08005A30:
    adds r0, r4, #0
    add sp, #0xc
    pop {r4}
    pop {r1}
    bx r1
    .align 2, 0

    thumb_func_start func_08005A3C
func_08005A3C: @ 0x08005A3C
    ldr r0, [r0, #4]
    ldr r1, .L08005A48 @ =0x00001A76
    adds r0, r0, r1
    ldrb r0, [r0]
    bx lr
    .align 2, 0
.L08005A48: .4byte 0x00001A76
.L08005A4C:
    .byte 0x01, 0x49, 0x40, 0x18
    .byte 0x00, 0x78, 0x70, 0x47, 0x76, 0x1A, 0x00, 0x00

    thumb_func_start func_08005A58
func_08005A58: @ 0x08005A58
    push {r4, r5, r6, r7, lr}
    mov r7, r8
    push {r7}
    sub sp, #0x14
    adds r5, r0, #0
    mov r8, r1
    adds r7, r2, #0
    bl func_08008444
    ldr r0, .L08005B1C @ =vtable_unk_080E5AB4
    str r0, [r5, #4]
    movs r0, #7
    add r6, sp, #0x10
    movs r1, #1
    rsbs r1, r1, #0
.L08005A76:
    subs r0, #1
    cmp r0, r1
    bne .L08005A76
    ldr r1, .L08005B20 @ =0x000045F0
    adds r0, r5, r1
    movs r1, #1
    bl func_08008B54
    ldr r2, .L08005B24 @ =0x000045F4
    adds r0, r5, r2
    movs r1, #2
    bl func_08008B54
    movs r0, #4
    bl __builtin_new
    adds r4, r0, #0
    add r0, sp, #0xc
    bl func_0800835C
    adds r0, r6, #0
    bl func_0800770C
    movs r0, #0
    str r0, [sp]
    add r3, sp, #0xc
    str r3, [sp, #4]
    str r6, [sp, #8]
    adds r0, r4, #0
    movs r1, #0
    movs r2, #0xf
    movs r3, #4
    bl func_08050CC0
    ldr r4, .L08005B28 @ =0x000045F8
    adds r1, r5, r4
    str r0, [r1]
    adds r0, r6, #0
    movs r1, #2
    bl func_08007714
    add r0, sp, #0xc
    movs r1, #2
    bl func_08008364
    ldr r6, .L08005B2C @ =0x000045FC
    adds r0, r5, r6
    mov r1, r8
    str r1, [r0]
    ldr r3, .L08005B30 @ =0x0000461C
    adds r2, r5, r3
    adds r1, r2, #0
    ldr r0, .L08005B34 @ =gUnk_080E8BE4
    ldm r0!, {r3, r4, r6}
    stm r1!, {r3, r4, r6}
    ldrb r0, [r0]
    strb r0, [r1]
    cmp r7, #0
    beq .L08005B0C
    movs r3, #0
    ldrb r0, [r7]
    cmp r0, #0
    beq .L08005B0C
    adds r4, r2, #0
    adds r2, r7, #0
.L08005AF8:
    adds r1, r4, r3
    ldrb r0, [r2]
    strb r0, [r1]
    adds r2, #1
    adds r3, #1
    cmp r3, #0xc
    bgt .L08005B0C
    ldrb r0, [r2]
    cmp r0, #0
    bne .L08005AF8
.L08005B0C:
    adds r0, r5, #0
    add sp, #0x14
    pop {r3}
    mov r8, r3
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0
.L08005B1C: .4byte vtable_unk_080E5AB4
.L08005B20: .4byte 0x000045F0
.L08005B24: .4byte 0x000045F4
.L08005B28: .4byte 0x000045F8
.L08005B2C: .4byte 0x000045FC
.L08005B30: .4byte 0x0000461C
.L08005B34: .4byte gUnk_080E8BE4

    thumb_func_start func_08005B38
func_08005B38: @ 0x08005B38
    push {r4, r5, lr}
    adds r4, r0, #0
    adds r5, r1, #0
    ldr r0, .L08005B60 @ =vtable_unk_080E5AB4
    str r0, [r4, #4]
    ldr r1, .L08005B64 @ =0x000045F8
    adds r0, r4, r1
    ldr r0, [r0]
    cmp r0, #0
    beq .L08005B52
    movs r1, #3
    bl func_08050D0C
.L08005B52:
    adds r0, r4, #0
    adds r1, r5, #0
    bl func_080086BC
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L08005B60: .4byte vtable_unk_080E5AB4
.L08005B64: .4byte 0x000045F8

    thumb_func_start func_08005B68
func_08005B68: @ 0x08005B68
    push {r4, r5, r6, r7, lr}
    mov r7, r8
    push {r7}
    sub sp, #0x28
    adds r7, r0, #0
    adds r6, r1, #0
    adds r0, r6, #0
    bl func_08008724
    mov r0, sp
    bl func_08007874
    movs r5, #0
    str r5, [sp, #4]
    mov r0, sp
    movs r1, #0
    bl func_08007C28
    mov r0, sp
    movs r1, #3
    bl func_08007B54
    adds r1, r0, #0
    str r1, [sp, #4]
    mov r0, sp
    bl func_08007D4C
    adds r4, r0, #0
    adds r0, r6, #0
    bl func_08005CDC
    adds r0, r6, #0
    adds r1, r4, #0
    bl func_080061A0
    adds r0, r6, #0
    bl func_08006334
    adds r0, r6, #0
    bl func_0800637C
    adds r0, r6, #0
    bl func_08008918
    add r1, sp, #8
    movs r2, #0x3f
    strh r2, [r1]
    adds r0, #0x50
    strh r2, [r0]
    adds r0, r6, #0
    bl func_08008918
    adds r1, r0, #0
    add r4, sp, #0xc
    str r5, [sp, #0xc]
    str r5, [r4, #4]
    ldr r0, .L08005C20 @ =vtable_unk_080E5B80
    str r0, [sp, #0x14]
    add r0, sp, #0x18
    bl func_08009300
    ldr r1, .L08005C24 @ =0x00000889
    add r0, sp, #0x18
    movs r2, #1
    movs r3, #1
    bl func_0800934C
    adds r0, r6, #0
    bl func_08008940
    ldr r1, [r0, #8]
    ldr r2, [r1, #0x10]
    adds r1, r4, #0
    bl _call_via_r2
    ldr r0, [sp, #0xc]
    rsbs r1, r0, #0
    orrs r1, r0
    mov r8, r4
    add r5, sp, #0x1c
    add r4, sp, #0x20
    cmp r1, #0
    bge .L08005C58
.L08005C0E:
    adds r0, r6, #0
    bl func_080087C8
    ldr r0, [sp, #0xc]
    rsbs r1, r0, #0
    orrs r1, r0
    cmp r1, #0
    blt .L08005C0E
    b .L08005C58
    .align 2, 0
.L08005C20: .4byte vtable_unk_080E5B80
.L08005C24: .4byte 0x00000889
.L08005C28:
    adds r0, r6, #0
    bl func_080088B8
    adds r0, r6, #0
    bl func_08006CDC
    adds r0, r6, #0
    bl func_080068CC
    adds r0, r6, #0
    bl func_0800637C
    adds r0, r6, #0
    bl func_080064E8
    adds r0, r6, #0
    bl func_08006858
    adds r0, r6, #0
    bl func_08006ED8
    adds r0, r6, #0
    bl func_080087C8
.L08005C58:
    ldr r1, .L08005C80 @ =0x00004636
    adds r0, r6, r1
    ldrb r0, [r0]
    cmp r0, #0
    beq .L08005C28
    ldr r1, .L08005C84 @ =0x00000889
    add r0, sp, #0x18
    movs r2, #1
    movs r3, #1
    bl func_08009378
    adds r0, r6, #0
    bl func_08008940
    ldr r1, [r0, #8]
    ldr r2, [r1, #0x10]
    mov r1, r8
    bl _call_via_r2
    b .L08005C8E
    .align 2, 0
.L08005C80: .4byte 0x00004636
.L08005C84: .4byte 0x00000889
.L08005C88:
    adds r0, r6, #0
    bl func_080087C8
.L08005C8E:
    ldr r1, [sp, #0xc]
    rsbs r0, r1, #0
    orrs r0, r1
    cmp r0, #0
    blt .L08005C88
    movs r0, #0
    str r0, [sp, #0x1c]
    str r5, [sp, #0x20]
    str r0, [r4, #4]
    str r0, [r5]
    str r0, [r7]
    ldr r1, [sp, #0x1c]
    cmp r1, #0
    beq .L08005CB6
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08005CB6:
    mov r0, r8
    movs r1, #2
    bl func_080094B8
    ldr r1, [sp, #4]
    mov r0, sp
    bl func_08007C28
    mov r0, sp
    movs r1, #2
    bl func_080079E8
    adds r0, r7, #0
    add sp, #0x28
    pop {r3}
    mov r8, r3
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1

    thumb_func_start func_08005CDC
func_08005CDC: @ 0x08005CDC
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x54
    mov sl, r0
    ldr r0, .L08005EC8 @ =gUnk_080F9F70
    ldr r0, [r0]
    ldr r1, .L08005ECC @ =0x06004B00
    ldr r2, .L08005ED0 @ =gUnk_080F9F74
    ldr r2, [r2]
    bl func_08008E64
    ldr r0, .L08005ED4 @ =gUnk_080F9F78
    ldr r0, [r0]
    movs r1, #0xa0
    lsls r1, r1, #0x13
    movs r2, #0x20
    bl func_08008E64
    mov r0, sl
    bl func_08008918
    add r1, sp, #0xc
    movs r3, #0xba
    lsls r3, r3, #5
    adds r2, r3, #0
    strh r2, [r1]
    movs r4, #0
    strh r2, [r0]
    mov r0, sl
    bl func_08008918
    add r2, sp, #0xc
    ldr r5, .L08005ED8 @ =0x00001841
    adds r1, r5, #0
    strh r1, [r2]
    strh r1, [r0, #0xa]
    mov r0, sl
    bl func_08008918
    add r2, sp, #0xc
    ldr r7, .L08005EDC @ =0x00001F02
    adds r1, r7, #0
    strh r1, [r2]
    strh r1, [r0, #0xc]
    ldr r0, .L08005EE0 @ =0x0600F800
    movs r1, #0x14
    str r1, [sp]
    movs r1, #0x96
    lsls r1, r1, #2
    str r1, [sp, #4]
    str r4, [sp, #8]
    movs r1, #0
    movs r2, #0
    movs r3, #0x1e
    bl func_08051320
    movs r0, #1
    rsbs r0, r0, #0
    ldr r4, .L08005EE4 @ =0x0600C000
    movs r2, #0x80
    lsls r2, r2, #4
    adds r1, r4, #0
    bl func_08008EB8
    movs r1, #0
    add r0, sp, #0x20
    mov r8, r0
    add r2, sp, #0x24
    mov sb, r2
    mov r3, sp
    adds r3, #0x10
    str r3, [sp, #0x44]
    mov r5, sp
    adds r5, #0x30
    str r5, [sp, #0x48]
    mov r7, sl
    adds r7, #0xc
    ldr r0, .L08005EE8 @ =0x000043B0
    add r0, sl
    str r0, [sp, #0x40]
    movs r2, #0xd1
    lsls r2, r2, #1
    adds r6, r2, #0
.L08005D88:
    movs r3, #0
    lsls r2, r1, #6
    adds r5, r1, #1
    adds r0, r2, r4
.L08005D90:
    strh r6, [r0]
    adds r0, #2
    adds r3, #1
    cmp r3, #0x1d
    bls .L08005D90
    adds r1, r5, #0
    cmp r1, #0x13
    bls .L08005D88
    movs r3, #0xa
    ldr r2, .L08005EEC @ =0x0600C094
    ldr r1, .L08005EF0 @ =0x0600C054
.L08005DA6:
    strh r3, [r1]
    adds r0, r3, #0
    adds r0, #0x1e
    strh r0, [r2]
    adds r2, #2
    adds r1, #2
    adds r3, #1
    cmp r3, #0xf
    bls .L08005DA6
    movs r3, #3
    movs r4, #0xd2
    lsls r4, r4, #1
    adds r5, r4, #0
    movs r0, #0xe1
    lsls r0, r0, #1
    adds r4, r0, #0
    ldr r2, .L08005EF4 @ =0x0600C486
    ldr r1, .L08005EF8 @ =0x0600C446
.L08005DCA:
    adds r0, r3, r5
    strh r0, [r1]
    adds r0, r3, r4
    strh r0, [r2]
    adds r2, #2
    adds r1, #2
    adds r3, #1
    cmp r3, #0x1a
    bls .L08005DCA
    movs r1, #4
    ldr r4, .L08005EE4 @ =0x0600C000
.L08005DE0:
    movs r3, #0
    lsls r2, r1, #6
    adds r5, r1, #1
    subs r1, #2
    lsls r0, r1, #4
    subs r0, r0, r1
    lsls r1, r0, #1
    adds r2, r2, r4
.L08005DF0:
    adds r0, r1, r3
    strh r0, [r2]
    adds r2, #2
    adds r3, #1
    cmp r3, #0x1d
    bls .L08005DF0
    adds r1, r5, #0
    cmp r1, #0xf
    bls .L08005DE0
    movs r3, #0x12
    movs r1, #0xf0
    lsls r1, r1, #1
    adds r5, r1, #0
    movs r2, #0xff
    lsls r2, r2, #1
    adds r4, r2, #0
    ldr r2, .L08005EFC @ =0x0600C0A4
    ldr r1, .L08005F00 @ =0x0600C064
.L08005E14:
    adds r0, r3, r5
    strh r0, [r1]
    adds r0, r3, r4
    strh r0, [r2]
    adds r2, #2
    adds r1, #2
    adds r3, #1
    cmp r3, #0x1d
    bls .L08005E14
    ldr r0, .L08005F04 @ =0x000045FC
    add r0, sl
    ldr r0, [r0]
    cmp r0, #0
    beq .L08005E52
    movs r3, #1
    ldr r4, .L08005F08 @ =0x0000021B
    adds r5, r4, #0
    movs r0, #0x89
    lsls r0, r0, #2
    adds r4, r0, #0
    ldr r2, .L08005F0C @ =0x0600C082
    ldr r1, .L08005F10 @ =0x0600C042
.L08005E40:
    adds r0, r3, r5
    strh r0, [r1]
    adds r0, r3, r4
    strh r0, [r2]
    adds r2, #2
    adds r1, #2
    adds r3, #1
    cmp r3, #9
    bls .L08005E40
.L08005E52:
    ldr r1, .L08005F14 @ =0x06FFC000
    movs r0, #0
    movs r2, #0x20
    bl func_08008EB8
    movs r4, #0x1e
    movs r5, #2
    add r0, sp, #0x20
    strh r4, [r0]
    mov r1, r8
    strh r5, [r1, #2]
    ldr r0, [sp, #0x20]
    adds r1, r7, #0
    movs r2, #0
    bl func_0804E7A0
    ldr r1, .L08005F18 @ =gUnk_080E8BF4
    add r0, sp, #0x24
    strh r4, [r0]
    mov r2, sb
    strh r5, [r2, #2]
    ldr r0, [sp, #0x24]
    str r1, [sp]
    adds r1, r7, #0
    movs r2, #0x58
    movs r3, #0
    bl func_0804E8F0
    mov r0, sl
    bl func_08008910
    movs r3, #0xf0
    lsls r3, r3, #3
    adds r6, r0, #0
    add r0, sp, #0x10
    adds r1, r7, #0
    movs r2, #0xc0
    lsls r2, r2, #0x13
    bl func_08008F0C
    ldr r3, [sp, #0x44]
    mov r8, r3
    ldr r1, [r6, #4]
    ldr r0, [r6, #0xc]
    cmp r1, r0
    beq .L08005F1C
    cmp r1, #0
    beq .L08005EBE
    adds r0, r1, #0
    mov r1, r8
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08005EBE:
    ldr r0, [r6, #4]
    adds r0, #0x10
    str r0, [r6, #4]
    b .L08005FE0
    .align 2, 0
.L08005EC8: .4byte gUnk_080F9F70
.L08005ECC: .4byte 0x06004B00
.L08005ED0: .4byte gUnk_080F9F74
.L08005ED4: .4byte gUnk_080F9F78
.L08005ED8: .4byte 0x00001841
.L08005EDC: .4byte 0x00001F02
.L08005EE0: .4byte 0x0600F800
.L08005EE4: .4byte 0x0600C000
.L08005EE8: .4byte 0x000043B0
.L08005EEC: .4byte 0x0600C094
.L08005EF0: .4byte 0x0600C054
.L08005EF4: .4byte 0x0600C486
.L08005EF8: .4byte 0x0600C446
.L08005EFC: .4byte 0x0600C0A4
.L08005F00: .4byte 0x0600C064
.L08005F04: .4byte 0x000045FC
.L08005F08: .4byte 0x0000021B
.L08005F0C: .4byte 0x0600C082
.L08005F10: .4byte 0x0600C042
.L08005F14: .4byte 0x06FFC000
.L08005F18: .4byte gUnk_080E8BF4
.L08005F1C:
    str r1, [sp, #0x4c]
    movs r0, #1
    str r0, [sp, #0x2c]
    ldr r0, [r6]
    subs r0, r1, r0
    asrs r4, r0, #4
    str r4, [sp, #0x28]
    add r1, sp, #0x2c
    add r0, sp, #0x28
    cmp r4, #1
    bhs .L08005F34
    adds r0, r1, #0
.L08005F34:
    ldr r0, [r0]
    adds r0, r4, r0
    cmp r0, #0
    beq .L08005F52
    lsls r4, r0, #4
    adds r0, r4, #0
    bl malloc
    mov sb, r4
    cmp r0, #0
    bne .L08005F56
    mov r0, sb
    bl func_080D3BC0
    b .L08005F56
.L08005F52:
    movs r0, #0
    mov sb, r0
.L08005F56:
    adds r5, r0, #0
    str r5, [sp, #0x50]
    ldr r2, [r6]
    adds r3, r5, #0
    ldr r4, [sp, #0x4c]
    cmp r2, r4
    beq .L08005F7E
.L08005F64:
    cmp r3, #0
    beq .L08005F74
    adds r0, r3, #0
    adds r1, r2, #0
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08005F74:
    adds r2, #0x10
    adds r3, #0x10
    ldr r5, [sp, #0x4c]
    cmp r2, r5
    bne .L08005F64
.L08005F7E:
    adds r5, r3, #0
    ldr r0, [sp, #0x2c]
    cmp r0, #1
    bne .L08005F9A
    cmp r5, #0
    beq .L08005F96
    adds r0, r5, #0
    mov r1, r8
    ldm r1!, {r2, r3, r7}
    stm r0!, {r2, r3, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08005F96:
    adds r5, #0x10
    b .L08005FBC
.L08005F9A:
    adds r3, r0, #0
    adds r2, r5, #0
    cmp r3, #0
    beq .L08005FBA
.L08005FA2:
    cmp r2, #0
    beq .L08005FB2
    adds r0, r2, #0
    mov r1, r8
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08005FB2:
    subs r3, #1
    adds r2, #0x10
    cmp r3, #0
    bne .L08005FA2
.L08005FBA:
    adds r5, r2, #0
.L08005FBC:
    ldr r2, [r6, #4]
    ldr r0, [r6]
    adds r1, r0, #0
    cmp r0, r2
    beq .L08005FCC
.L08005FC6:
    adds r1, #0x10
    cmp r1, r2
    bne .L08005FC6
.L08005FCC:
    cmp r0, #0
    beq .L08005FD4
    bl free
.L08005FD4:
    ldr r0, [sp, #0x50]
    add r0, sb
    ldr r1, [sp, #0x50]
    str r1, [r6]
    str r5, [r6, #4]
    str r0, [r6, #0xc]
.L08005FE0:
    movs r1, #0x8c
    lsls r1, r1, #7
    add r1, sl
    movs r0, #0
    str r0, [r1]
    ldr r0, .L08006074 @ =0x00004637
    add r0, sl
    movs r2, #1
    mov r8, r2
    mov r3, r8
    strb r3, [r0]
    mov r0, sl
    bl func_080064E8
    movs r5, #9
    movs r6, #2
    add r0, sp, #0x30
    strh r5, [r0]
    ldr r4, [sp, #0x48]
    strh r6, [r4, #2]
    ldr r0, [sp, #0x30]
    ldr r4, [sp, #0x40]
    adds r1, r4, #0
    movs r2, #0
    bl func_0804E7A0
    ldr r0, .L08006078 @ =0x000045FC
    add r0, sl
    ldr r1, [r0]
    cmp r1, #0
    beq .L08006032
    add r0, sp, #0x34
    strh r5, [r0]
    strh r6, [r0, #2]
    ldr r0, [sp, #0x34]
    str r1, [sp]
    adds r1, r4, #0
    movs r2, #0
    movs r3, #0
    bl func_0804E8F0
.L08006032:
    mov r0, sl
    bl func_08008910
    movs r3, #0x90
    lsls r3, r3, #2
    adds r6, r0, #0
    movs r2, #0xf0
    lsls r2, r2, #3
    lsls r2, r2, #3
    ldr r5, .L0800607C @ =0x06000780
    adds r2, r2, r5
    add r0, sp, #0xc
    ldr r1, [sp, #0x40]
    bl func_08008F0C
    add r7, sp, #0xc
    mov sb, r7
    ldr r1, [r6, #4]
    ldr r0, [r6, #0xc]
    cmp r1, r0
    beq .L08006080
    cmp r1, #0
    beq .L0800606C
    adds r0, r1, #0
    add r1, sp, #0xc
    ldm r1!, {r2, r3, r4}
    stm r0!, {r2, r3, r4}
    ldr r1, [r1]
    str r1, [r0]
.L0800606C:
    ldr r0, [r6, #4]
    adds r0, #0x10
    str r0, [r6, #4]
    b .L08006142
    .align 2, 0
.L08006074: .4byte 0x00004637
.L08006078: .4byte 0x000045FC
.L0800607C: .4byte 0x06000780
.L08006080:
    str r1, [sp, #0x4c]
    mov r5, r8
    str r5, [sp, #0x3c]
    ldr r0, [r6]
    adds r7, r1, #0
    subs r0, r7, r0
    asrs r4, r0, #4
    str r4, [sp, #0x38]
    add r1, sp, #0x3c
    add r0, sp, #0x38
    cmp r4, #1
    bhs .L0800609A
    adds r0, r1, #0
.L0800609A:
    ldr r0, [r0]
    adds r0, r4, r0
    cmp r0, #0
    beq .L080060B8
    lsls r4, r0, #4
    adds r0, r4, #0
    bl malloc
    mov r8, r4
    cmp r0, #0
    bne .L080060BC
    mov r0, r8
    bl func_080D3BC0
    b .L080060BC
.L080060B8:
    movs r0, #0
    mov r8, r0
.L080060BC:
    adds r5, r0, #0
    str r5, [sp, #0x50]
    ldr r2, [r6]
    adds r3, r5, #0
    b .L080060DA
.L080060C6:
    cmp r3, #0
    beq .L080060D6
    adds r0, r3, #0
    adds r1, r2, #0
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L080060D6:
    adds r2, #0x10
    adds r3, #0x10
.L080060DA:
    ldr r0, [sp, #0x4c]
    cmp r2, r0
    bne .L080060C6
    adds r5, r3, #0
    ldr r0, [sp, #0x3c]
    cmp r0, #1
    bne .L080060FC
    cmp r5, #0
    beq .L080060F8
    adds r0, r5, #0
    mov r1, sb
    ldm r1!, {r2, r3, r4}
    stm r0!, {r2, r3, r4}
    ldr r1, [r1]
    str r1, [r0]
.L080060F8:
    adds r5, #0x10
    b .L0800611E
.L080060FC:
    adds r3, r0, #0
    adds r2, r5, #0
    cmp r3, #0
    beq .L0800611C
.L08006104:
    cmp r2, #0
    beq .L08006114
    adds r0, r2, #0
    mov r1, sb
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08006114:
    subs r3, #1
    adds r2, #0x10
    cmp r3, #0
    bne .L08006104
.L0800611C:
    adds r5, r2, #0
.L0800611E:
    ldr r2, [r6, #4]
    ldr r0, [r6]
    adds r1, r0, #0
    cmp r0, r2
    beq .L0800612E
.L08006128:
    adds r1, #0x10
    cmp r1, r2
    bne .L08006128
.L0800612E:
    cmp r0, #0
    beq .L08006136
    bl free
.L08006136:
    ldr r0, [sp, #0x50]
    add r0, r8
    ldr r7, [sp, #0x50]
    str r7, [r6]
    str r5, [r6, #4]
    str r0, [r6, #0xc]
.L08006142:
    ldr r0, .L08006198 @ =0x000045F8
    add r0, sl
    ldr r0, [r0]
    mov sb, r0
    mov r0, sl
    bl func_080088DC
    mov r8, r0
    mov r0, sl
    bl func_08008920
    adds r6, r0, #0
    mov r0, sl
    bl func_08008918
    adds r5, r0, #0
    mov r0, sl
    bl func_08008940
    adds r4, r0, #0
    mov r0, sl
    bl func_0800894C
    ldr r1, .L0800619C @ =0x000045F0
    add r1, sl
    str r4, [sp]
    str r0, [sp, #4]
    str r1, [sp, #8]
    mov r0, sb
    mov r1, r8
    adds r2, r6, #0
    adds r3, r5, #0
    bl func_08050D3C
    add sp, #0x54
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L08006198: .4byte 0x000045F8
.L0800619C: .4byte 0x000045F0

    thumb_func_start func_080061A0
func_080061A0: @ 0x080061A0
    push {r4, r5, r6, r7, lr}
    adds r7, r0, #0
    adds r6, r1, #0
    ldr r0, .L080062E4 @ =0x00004608
    adds r1, r7, r0
    movs r0, #0
    movs r2, #8
    bl func_08008EB8
    ldr r2, .L080062E8 @ =0x00004614
    adds r1, r7, r2
    movs r0, #0
    movs r2, #8
    bl func_08008EB8
    ldr r4, .L080062EC @ =0x0000460B
    adds r3, r7, r4
    ldrb r2, [r3]
    movs r1, #0x3f
    adds r0, r1, #0
    ands r0, r2
    strb r0, [r3]
    ldr r0, .L080062F0 @ =0x00004617
    adds r3, r7, r0
    ldrb r2, [r3]
    adds r0, r1, #0
    ands r0, r2
    strb r0, [r3]
    ldr r2, .L080062F4 @ =0x00004615
    adds r3, r7, r2
    ldrb r0, [r3]
    ands r1, r0
    movs r0, #0x80
    orrs r1, r0
    strb r1, [r3]
    ldr r0, .L080062F8 @ =0x00004609
    adds r4, r7, r0
    ldrb r2, [r4]
    movs r1, #0xd
    rsbs r1, r1, #0
    adds r0, r1, #0
    ands r0, r2
    movs r2, #4
    orrs r0, r2
    strb r0, [r4]
    ldrb r0, [r3]
    ands r1, r0
    orrs r1, r2
    strb r1, [r3]
    ldr r2, .L080062FC @ =0x0000460C
    adds r4, r7, r2
    ldr r0, .L08006300 @ =0x000003FF
    adds r5, r0, #0
    adds r2, r6, #0
    ands r2, r5
    ldrh r3, [r4]
    ldr r1, .L08006304 @ =0xFFFFFC00
    adds r0, r1, #0
    ands r0, r3
    orrs r0, r2
    strh r0, [r4]
    ldr r4, .L08006308 @ =0x00004618
    adds r3, r7, r4
    ands r2, r5
    ldrh r0, [r3]
    ands r1, r0
    orrs r1, r2
    strh r1, [r3]
    ldr r0, .L0800630C @ =0x0000460D
    adds r3, r7, r0
    ldrb r2, [r3]
    movs r1, #0xf
    adds r0, r1, #0
    ands r0, r2
    movs r4, #0x40
    orrs r0, r4
    strb r0, [r3]
    ldr r0, .L08006310 @ =0x00004619
    adds r2, r7, r0
    ldrb r0, [r2]
    ands r1, r0
    orrs r1, r4
    strb r1, [r2]
    movs r3, #0
    lsls r6, r6, #5
    ldr r2, .L08006314 @ =0x88888888
.L0800624C:
    lsls r1, r3, #2
    adds r1, r6, r1
    ldr r4, .L08006318 @ =0x06010000
    adds r0, r1, r4
    str r2, [r0]
    adds r4, #0x20
    adds r0, r1, r4
    str r2, [r0]
    adds r4, #0x20
    adds r0, r1, r4
    str r2, [r0]
    adds r4, #0x20
    adds r0, r1, r4
    str r2, [r0]
    adds r4, #0x20
    adds r0, r1, r4
    str r2, [r0]
    adds r4, #0x20
    adds r0, r1, r4
    str r2, [r0]
    adds r4, #0x20
    adds r0, r1, r4
    str r2, [r0]
    ldr r0, .L0800631C @ =0x060100E0
    adds r1, r1, r0
    str r2, [r1]
    adds r0, r3, #1
    lsls r0, r0, #0x18
    lsrs r3, r0, #0x18
    cmp r3, #7
    bls .L0800624C
    ldr r1, .L08006320 @ =0x05000290
    ldr r2, .L08006324 @ =0x0000027F
    adds r0, r2, #0
    strh r0, [r1]
    ldr r4, .L08006328 @ =0x00004616
    adds r3, r7, r4
    ldrh r1, [r3]
    ldr r2, .L0800632C @ =0xFFFFFE00
    adds r0, r2, #0
    ands r0, r1
    movs r1, #0x90
    orrs r0, r1
    strh r0, [r3]
    ldr r0, .L080062E8 @ =0x00004614
    adds r1, r7, r0
    movs r4, #8
    movs r0, #8
    strb r0, [r1]
    ldr r0, .L08006330 @ =0x0000460A
    adds r1, r7, r0
    ldrh r0, [r1]
    ands r2, r0
    strh r2, [r1]
    ldr r2, .L080062E4 @ =0x00004608
    adds r1, r7, r2
    movs r0, #0x20
    strb r0, [r1]
    ldr r0, .L08006310 @ =0x00004619
    adds r3, r7, r0
    ldrb r2, [r3]
    movs r1, #0xd
    rsbs r1, r1, #0
    adds r0, r1, #0
    ands r0, r2
    orrs r0, r4
    strb r0, [r3]
    ldr r0, .L0800630C @ =0x0000460D
    adds r2, r7, r0
    ldrb r0, [r2]
    ands r1, r0
    orrs r1, r4
    strb r1, [r2]
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L080062E4: .4byte 0x00004608
.L080062E8: .4byte 0x00004614
.L080062EC: .4byte 0x0000460B
.L080062F0: .4byte 0x00004617
.L080062F4: .4byte 0x00004615
.L080062F8: .4byte 0x00004609
.L080062FC: .4byte 0x0000460C
.L08006300: .4byte 0x000003FF
.L08006304: .4byte 0xFFFFFC00
.L08006308: .4byte 0x00004618
.L0800630C: .4byte 0x0000460D
.L08006310: .4byte 0x00004619
.L08006314: .4byte 0x88888888
.L08006318: .4byte 0x06010000
.L0800631C: .4byte 0x060100E0
.L08006320: .4byte 0x05000290
.L08006324: .4byte 0x0000027F
.L08006328: .4byte 0x00004616
.L0800632C: .4byte 0xFFFFFE00
.L08006330: .4byte 0x0000460A

    thumb_func_start func_08006334
func_08006334: @ 0x08006334
    ldr r2, .L08006370 @ =0x00004639
    adds r1, r0, r2
    movs r2, #0
    strb r2, [r1]
    ldr r3, .L08006374 @ =0x00004638
    adds r1, r0, r3
    strb r2, [r1]
    subs r3, #2
    adds r1, r0, r3
    strb r2, [r1]
    adds r3, #1
    adds r1, r0, r3
    strb r2, [r1]
    subs r3, #0x32
    adds r1, r0, r3
    strb r2, [r1]
    subs r3, #1
    adds r1, r0, r3
    strb r2, [r1]
    subs r3, #4
    adds r1, r0, r3
    str r2, [r1]
    adds r3, #0x10
    adds r1, r0, r3
    strb r2, [r1]
    ldr r1, .L08006378 @ =0x0000463C
    adds r0, r0, r1
    str r2, [r0]
    bx lr
    .align 2, 0
.L08006370: .4byte 0x00004639
.L08006374: .4byte 0x00004638
.L08006378: .4byte 0x0000463C

    thumb_func_start func_0800637C
func_0800637C: @ 0x0800637C
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x30
    adds r5, r0, #0
    movs r0, #0xf0
    lsls r0, r0, #3
    mov sb, r0
    movs r1, #0x60
    movs r2, #0x10
    movs r3, #0
    add r0, sp, #0x1c
    movs r6, #0x1e
    movs r4, #2
    mov r8, r4
    strh r6, [r0]
    mov r7, r8
    strh r7, [r0, #2]
    ldr r0, [sp, #0x1c]
    ldr r7, .L08006410 @ =0x00003C2C
    adds r4, r5, r7
    str r1, [sp]
    str r2, [sp, #4]
    str r3, [sp, #8]
    adds r1, r4, #0
    movs r2, #0
    bl func_0804E7DC
    ldr r0, .L08006414 @ =0x0000461C
    adds r1, r5, r0
    add r0, sp, #0x20
    strh r6, [r0]
    mov r2, r8
    strh r2, [r0, #2]
    ldr r0, [sp, #0x20]
    str r1, [sp]
    adds r1, r4, #0
    movs r2, #0x90
    movs r3, #0
    bl func_0804E8F0
    adds r0, r5, #0
    bl func_08008910
    adds r6, r0, #0
    mov r3, sb
    lsls r2, r3, #3
    movs r0, #0xc0
    lsls r0, r0, #0x13
    adds r2, r2, r0
    add r0, sp, #0xc
    adds r1, r4, #0
    bl func_08008F0C
    add r4, sp, #0xc
    mov sb, r4
    ldr r1, [r6, #4]
    ldr r0, [r6, #0xc]
    cmp r1, r0
    beq .L08006418
    cmp r1, #0
    beq .L08006408
    adds r0, r1, #0
    add r1, sp, #0xc
    ldm r1!, {r2, r5, r7}
    stm r0!, {r2, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08006408:
    ldr r0, [r6, #4]
    adds r0, #0x10
    str r0, [r6, #4]
    b .L080064D8
    .align 2, 0
.L08006410: .4byte 0x00003C2C
.L08006414: .4byte 0x0000461C
.L08006418:
    mov sl, r1
    movs r0, #1
    str r0, [sp, #0x28]
    ldr r0, [r6]
    subs r0, r1, r0
    asrs r4, r0, #4
    str r4, [sp, #0x24]
    add r1, sp, #0x28
    add r0, sp, #0x24
    cmp r4, #1
    bhs .L08006430
    adds r0, r1, #0
.L08006430:
    ldr r0, [r0]
    adds r0, r4, r0
    cmp r0, #0
    beq .L0800644E
    lsls r4, r0, #4
    adds r0, r4, #0
    bl malloc
    mov r8, r4
    cmp r0, #0
    bne .L08006452
    mov r0, r8
    bl func_080D3BC0
    b .L08006452
.L0800644E:
    movs r0, #0
    mov r8, r0
.L08006452:
    adds r5, r0, #0
    str r5, [sp, #0x2c]
    ldr r2, [r6]
    adds r3, r5, #0
    cmp r2, sl
    beq .L08006476
.L0800645E:
    cmp r3, #0
    beq .L0800646E
    adds r0, r3, #0
    adds r1, r2, #0
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L0800646E:
    adds r2, #0x10
    adds r3, #0x10
    cmp r2, sl
    bne .L0800645E
.L08006476:
    adds r5, r3, #0
    ldr r0, [sp, #0x28]
    cmp r0, #1
    bne .L08006492
    cmp r5, #0
    beq .L0800648E
    adds r0, r5, #0
    mov r1, sb
    ldm r1!, {r2, r3, r4}
    stm r0!, {r2, r3, r4}
    ldr r1, [r1]
    str r1, [r0]
.L0800648E:
    adds r5, #0x10
    b .L080064B4
.L08006492:
    adds r3, r0, #0
    adds r2, r5, #0
    cmp r3, #0
    beq .L080064B2
.L0800649A:
    cmp r2, #0
    beq .L080064AA
    adds r0, r2, #0
    mov r1, sb
    ldm r1!, {r4, r5, r7}
    stm r0!, {r4, r5, r7}
    ldr r1, [r1]
    str r1, [r0]
.L080064AA:
    subs r3, #1
    adds r2, #0x10
    cmp r3, #0
    bne .L0800649A
.L080064B2:
    adds r5, r2, #0
.L080064B4:
    ldr r2, [r6, #4]
    ldr r0, [r6]
    adds r1, r0, #0
    cmp r0, r2
    beq .L080064C4
.L080064BE:
    adds r1, #0x10
    cmp r1, r2
    bne .L080064BE
.L080064C4:
    cmp r0, #0
    beq .L080064CC
    bl free
.L080064CC:
    ldr r0, [sp, #0x2c]
    add r0, r8
    ldr r7, [sp, #0x2c]
    str r7, [r6]
    str r5, [r6, #4]
    str r0, [r6, #0xc]
.L080064D8:
    add sp, #0x30
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0

    thumb_func_start func_080064E8
func_080064E8: @ 0x080064E8
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0x5c
    mov sl, r0
    ldr r0, .L080065D0 @ =0x00004637
    add r0, sl
    ldrb r0, [r0]
    cmp r0, #0
    bne .L08006502
    b .L08006842
.L08006502:
    movs r0, #1
    mov r8, r0
    mov r1, sp
    adds r1, #0x14
    str r1, [sp, #0x40]
    mov r2, sp
    adds r2, #0x18
    str r2, [sp, #0x44]
    mov r3, sp
    adds r3, #0x24
    str r3, [sp, #0x48]
    ldr r4, .L080065D4 @ =0x000034A8
    add r4, sl
    str r4, [sp, #0x50]
    mov r6, sp
    adds r6, #4
    str r6, [sp, #0x3c]
.L08006524:
    mov r7, r8
    lsls r4, r7, #4
    subs r4, r4, r7
    lsls r4, r4, #5
    add r4, r8
    lsls r4, r4, #2
    mov r0, sl
    adds r1, r4, r0
    add r0, sp, #0x14
    movs r2, #0x1e
    strh r2, [r0]
    movs r6, #2
    ldr r3, [sp, #0x40]
    strh r6, [r3, #2]
    ldr r0, [sp, #0x14]
    adds r1, #0xc
    movs r2, #0
    bl func_0804E7A0
    movs r0, #0x8c
    lsls r0, r0, #7
    add r0, sl
    ldr r3, [r0]
    mov r7, sl
    adds r1, r4, r7
    mov r0, r8
    lsls r2, r0, #5
    subs r2, r2, r0
    movs r0, #0xba
    muls r0, r3, r0
    adds r2, r2, r0
    ldr r0, .L080065D8 @ =gUnk_080E8997
    adds r2, r2, r0
    add r0, sp, #0x18
    movs r3, #0x1e
    strh r3, [r0]
    ldr r7, [sp, #0x44]
    strh r6, [r7, #2]
    ldr r0, [sp, #0x18]
    adds r1, #0xc
    str r2, [sp]
    movs r2, #0
    movs r3, #0
    bl func_0804E8F0
    mov r0, sl
    bl func_08008910
    add r4, sl
    adds r4, #0xc
    movs r1, #0xf0
    lsls r1, r1, #3
    mov r2, r8
    muls r2, r1, r2
    adds r5, r0, #0
    movs r3, #0xc0
    lsls r3, r3, #0x13
    adds r2, r2, r3
    add r0, sp, #4
    adds r1, r4, #0
    movs r3, #0xf0
    lsls r3, r3, #3
    bl func_08008F0C
    ldr r1, [r5, #4]
    ldr r0, [r5, #0xc]
    cmp r1, r0
    beq .L080065DC
    cmp r1, #0
    beq .L080065BC
    adds r0, r1, #0
    add r1, sp, #4
    ldm r1!, {r4, r6, r7}
    stm r0!, {r4, r6, r7}
    ldr r1, [r1]
    str r1, [r0]
.L080065BC:
    ldr r0, [r5, #4]
    adds r0, #0x10
    str r0, [r5, #4]
    movs r0, #1
    add r8, r0
    movs r1, #0xf0
    lsls r1, r1, #3
    lsls r1, r1, #3
    str r1, [sp, #0x4c]
    b .L080066AE
    .align 2, 0
.L080065D0: .4byte 0x00004637
.L080065D4: .4byte 0x000034A8
.L080065D8: .4byte gUnk_080E8997
.L080065DC:
    str r1, [sp, #0x54]
    movs r0, #1
    str r0, [sp, #0x20]
    ldr r0, [r5]
    adds r2, r1, #0
    subs r0, r2, r0
    asrs r4, r0, #4
    str r4, [sp, #0x1c]
    add r1, sp, #0x20
    add r0, sp, #0x1c
    cmp r4, #1
    bhs .L080065F6
    adds r0, r1, #0
.L080065F6:
    ldr r0, [r0]
    adds r0, r4, r0
    cmp r0, #0
    beq .L08006614
    lsls r4, r0, #4
    adds r0, r4, #0
    bl malloc
    mov sb, r4
    cmp r0, #0
    bne .L08006618
    mov r0, sb
    bl func_080D3BC0
    b .L08006618
.L08006614:
    movs r0, #0
    mov sb, r0
.L08006618:
    adds r4, r0, #0
    str r4, [sp, #0x58]
    ldr r2, [r5]
    adds r3, r4, #0
    movs r4, #1
    add r8, r4
    movs r6, #0xf0
    lsls r6, r6, #3
    lsls r6, r6, #3
    str r6, [sp, #0x4c]
    ldr r7, [sp, #0x54]
    cmp r2, r7
    beq .L0800664C
.L08006632:
    cmp r3, #0
    beq .L08006642
    adds r0, r3, #0
    adds r1, r2, #0
    ldm r1!, {r4, r6, r7}
    stm r0!, {r4, r6, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08006642:
    adds r2, #0x10
    adds r3, #0x10
    ldr r0, [sp, #0x54]
    cmp r2, r0
    bne .L08006632
.L0800664C:
    adds r4, r3, #0
    ldr r0, [sp, #0x20]
    cmp r0, #1
    bne .L08006668
    cmp r4, #0
    beq .L08006664
    adds r0, r4, #0
    ldr r1, [sp, #0x3c]
    ldm r1!, {r2, r3, r6}
    stm r0!, {r2, r3, r6}
    ldr r1, [r1]
    str r1, [r0]
.L08006664:
    adds r4, #0x10
    b .L0800668A
.L08006668:
    adds r3, r0, #0
    adds r2, r4, #0
    cmp r3, #0
    beq .L08006688
.L08006670:
    cmp r2, #0
    beq .L08006680
    adds r0, r2, #0
    ldr r1, [sp, #0x3c]
    ldm r1!, {r4, r6, r7}
    stm r0!, {r4, r6, r7}
    ldr r1, [r1]
    str r1, [r0]
.L08006680:
    subs r3, #1
    adds r2, #0x10
    cmp r3, #0
    bne .L08006670
.L08006688:
    adds r4, r2, #0
.L0800668A:
    ldr r2, [r5, #4]
    ldr r0, [r5]
    adds r1, r0, #0
    cmp r0, r2
    beq .L0800669A
.L08006694:
    adds r1, #0x10
    cmp r1, r2
    bne .L08006694
.L0800669A:
    cmp r0, #0
    beq .L080066A2
    bl free
.L080066A2:
    ldr r0, [sp, #0x58]
    add r0, sb
    ldr r7, [sp, #0x58]
    str r7, [r5]
    str r4, [r5, #4]
    str r0, [r5, #0xc]
.L080066AE:
    mov r0, r8
    cmp r0, #6
    bhi .L080066B6
    b .L08006524
.L080066B6:
    movs r4, #0x1e
    movs r5, #2
    add r0, sp, #0x24
    strh r4, [r0]
    ldr r1, [sp, #0x48]
    strh r5, [r1, #2]
    ldr r0, [sp, #0x24]
    ldr r1, [sp, #0x50]
    movs r2, #0
    bl func_0804E7A0
    movs r0, #0x8c
    lsls r0, r0, #7
    add r0, sl
    ldr r2, [r0]
    cmp r2, #1
    beq .L080066F8
    cmp r2, #1
    bgt .L080066E2
    cmp r2, #0
    beq .L080066E8
    b .L0800672A
.L080066E2:
    cmp r2, #2
    beq .L08006714
    b .L0800672A
.L080066E8:
    ldr r1, .L080066F4 @ =gUnk_080E8BFC
    add r0, sp, #0x28
    strh r4, [r0]
    strh r5, [r0, #2]
    ldr r0, [sp, #0x28]
    b .L08006702
    .align 2, 0
.L080066F4: .4byte gUnk_080E8BFC
.L080066F8:
    ldr r1, .L08006710 @ =gUnk_080E8C14
    add r0, sp, #0x2c
    strh r4, [r0]
    strh r5, [r0, #2]
    ldr r0, [sp, #0x2c]
.L08006702:
    str r1, [sp]
    ldr r1, [sp, #0x50]
    movs r2, #0x18
    movs r3, #0
    bl func_0804E8F0
    b .L0800672A
    .align 2, 0
.L08006710: .4byte gUnk_080E8C14
.L08006714:
    ldr r1, .L08006770 @ =gUnk_080E8C14
    add r0, sp, #0x30
    strh r4, [r0]
    strh r2, [r0, #2]
    ldr r0, [sp, #0x30]
    str r1, [sp]
    ldr r1, [sp, #0x50]
    movs r2, #0x18
    movs r3, #0
    bl func_0804E8F0
.L0800672A:
    mov r0, sl
    bl func_08008910
    adds r5, r0, #0
    ldr r3, [sp, #0x4c]
    movs r4, #0xf0
    lsls r4, r4, #3
    subs r2, r3, r4
    movs r6, #0xc0
    lsls r6, r6, #0x13
    adds r2, r2, r6
    add r0, sp, #4
    ldr r1, [sp, #0x50]
    adds r3, r4, #0
    bl func_08008F0C
    add r7, sp, #4
    mov sb, r7
    ldr r1, [r5, #4]
    ldr r0, [r5, #0xc]
    cmp r1, r0
    beq .L08006774
    cmp r1, #0
    beq .L08006766
    adds r0, r1, #0
    add r1, sp, #4
    ldm r1!, {r2, r3, r4}
    stm r0!, {r2, r3, r4}
    ldr r1, [r1]
    str r1, [r0]
.L08006766:
    ldr r0, [r5, #4]
    adds r0, #0x10
    str r0, [r5, #4]
    b .L0800683A
    .align 2, 0
.L08006770: .4byte gUnk_080E8C14
.L08006774:
    str r1, [sp, #0x54]
    movs r0, #1
    str r0, [sp, #0x38]
    ldr r0, [r5]
    adds r6, r1, #0
    subs r0, r6, r0
    asrs r4, r0, #4
    str r4, [sp, #0x34]
    add r1, sp, #0x38
    add r0, sp, #0x34
    cmp r4, #1
    bhs .L0800678E
    adds r0, r1, #0
.L0800678E:
    ldr r0, [r0]
    adds r0, r4, r0
    cmp r0, #0
    beq .L080067AC
    lsls r4, r0, #4
    adds r0, r4, #0
    bl malloc
    mov r8, r4
    cmp r0, #0
    bne .L080067B0
    mov r0, r8
    bl func_080D3BC0
    b .L080067B0
.L080067AC:
    movs r0, #0
    mov r8, r0
.L080067B0:
    adds r4, r0, #0
    str r4, [sp, #0x58]
    ldr r2, [r5]
    adds r3, r4, #0
    ldr r7, [sp, #0x54]
    cmp r2, r7
    beq .L080067D8
.L080067BE:
    cmp r3, #0
    beq .L080067CE
    adds r0, r3, #0
    adds r1, r2, #0
    ldm r1!, {r4, r6, r7}
    stm r0!, {r4, r6, r7}
    ldr r1, [r1]
    str r1, [r0]
.L080067CE:
    adds r2, #0x10
    adds r3, #0x10
    ldr r0, [sp, #0x54]
    cmp r2, r0
    bne .L080067BE
.L080067D8:
    adds r4, r3, #0
    ldr r0, [sp, #0x38]
    cmp r0, #1
    bne .L080067F4
    cmp r4, #0
    beq .L080067F0
    adds r0, r4, #0
    mov r1, sb
    ldm r1!, {r2, r3, r6}
    stm r0!, {r2, r3, r6}
    ldr r1, [r1]
    str r1, [r0]
.L080067F0:
    adds r4, #0x10
    b .L08006816
.L080067F4:
    adds r3, r0, #0
    adds r2, r4, #0
    cmp r3, #0
    beq .L08006814
.L080067FC:
    cmp r2, #0
    beq .L0800680C
    adds r0, r2, #0
    mov r1, sb
    ldm r1!, {r4, r6, r7}
    stm r0!, {r4, r6, r7}
    ldr r1, [r1]
    str r1, [r0]
.L0800680C:
    subs r3, #1
    adds r2, #0x10
    cmp r3, #0
    bne .L080067FC
.L08006814:
    adds r4, r2, #0
.L08006816:
    ldr r2, [r5, #4]
    ldr r0, [r5]
    adds r1, r0, #0
    cmp r0, r2
    beq .L08006826
.L08006820:
    adds r1, #0x10
    cmp r1, r2
    bne .L08006820
.L08006826:
    cmp r0, #0
    beq .L0800682E
    bl free
.L0800682E:
    ldr r0, [sp, #0x58]
    add r0, r8
    ldr r7, [sp, #0x58]
    str r7, [r5]
    str r4, [r5, #4]
    str r0, [r5, #0xc]
.L0800683A:
    ldr r1, .L08006854 @ =0x00004637
    add r1, sl
    movs r0, #0
    strb r0, [r1]
.L08006842:
    add sp, #0x5c
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L08006854: .4byte 0x00004637

    thumb_func_start func_08006858
func_08006858: @ 0x08006858
    push {r4, r5, lr}
    adds r4, r0, #0
    ldr r1, .L080068BC @ =0x0000463C
    adds r0, r4, r1
    ldr r0, [r0]
    cmp r0, #0
    bne .L0800688E
    adds r0, r4, #0
    bl func_08008920
    adds r3, r0, #0
    ldr r5, .L080068C0 @ =0x00004608
    adds r1, r4, r5
    ldrb r2, [r3]
    cmp r2, #0x7f
    bhi .L0800688E
    lsls r0, r2, #3
    adds r0, #4
    adds r0, r3, r0
    ldr r1, [r1]
    str r1, [r0]
    adds r5, #4
    adds r1, r4, r5
    ldrh r1, [r1]
    strh r1, [r0, #4]
    adds r0, r2, #1
    strb r0, [r3]
.L0800688E:
    adds r0, r4, #0
    bl func_08008920
    adds r3, r0, #0
    ldr r0, .L080068C4 @ =0x00004614
    adds r1, r4, r0
    ldrb r2, [r3]
    cmp r2, #0x7f
    bhi .L080068B6
    lsls r0, r2, #3
    adds r0, #4
    adds r0, r3, r0
    ldr r1, [r1]
    str r1, [r0]
    ldr r5, .L080068C8 @ =0x00004618
    adds r1, r4, r5
    ldrh r1, [r1]
    strh r1, [r0, #4]
    adds r0, r2, #1
    strb r0, [r3]
.L080068B6:
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L080068BC: .4byte 0x0000463C
.L080068C0: .4byte 0x00004608
.L080068C4: .4byte 0x00004614
.L080068C8: .4byte 0x00004618

    thumb_func_start func_080068CC
func_080068CC: @ 0x080068CC
    push {r4, r5, r6, r7, lr}
    adds r4, r0, #0
    ldr r1, .L08006948 @ =0x00004610
    adds r0, r4, r1
    ldrb r1, [r0]
    lsls r1, r1, #3
    adds r1, #0x90
    ldr r2, .L0800694C @ =0x00004616
    adds r3, r4, r2
    ldr r0, .L08006950 @ =0x000001FF
    adds r7, r0, #0
    ands r1, r7
    ldrh r2, [r3]
    ldr r6, .L08006954 @ =0xFFFFFE00
    adds r0, r6, #0
    ands r0, r2
    orrs r0, r1
    strh r0, [r3]
    ldr r2, .L08006958 @ =0x00004614
    adds r1, r4, r2
    movs r0, #8
    strb r0, [r1]
    ldr r0, .L0800695C @ =0x00004605
    adds r5, r4, r0
    movs r0, #0
    ldrsb r0, [r5, r0]
    cmp r0, #5
    bgt .L08006970
    ldr r1, .L08006960 @ =0x00004604
    adds r0, r4, r1
    movs r1, #0
    ldrsb r1, [r0, r1]
    lsls r1, r1, #4
    subs r2, #0xa
    adds r3, r4, r2
    ands r1, r7
    ldrh r2, [r3]
    adds r0, r6, #0
    ands r0, r2
    orrs r0, r1
    strh r0, [r3]
    movs r0, #0
    ldrsb r0, [r5, r0]
    lsls r0, r0, #4
    adds r0, #0x20
    ldr r2, .L08006964 @ =0x00004608
    adds r1, r4, r2
    strb r0, [r1]
    ldr r0, .L08006968 @ =0x0000460B
    adds r3, r4, r0
    ldrb r2, [r3]
    movs r1, #0x3f
    adds r0, r1, #0
    ands r0, r2
    strb r0, [r3]
    ldr r0, .L0800696C @ =0x00004609
    adds r2, r4, r0
    ldrb r0, [r2]
    ands r1, r0
    movs r0, #0x80
    b .L080069CC
    .align 2, 0
.L08006948: .4byte 0x00004610
.L0800694C: .4byte 0x00004616
.L08006950: .4byte 0x000001FF
.L08006954: .4byte 0xFFFFFE00
.L08006958: .4byte 0x00004614
.L0800695C: .4byte 0x00004605
.L08006960: .4byte 0x00004604
.L08006964: .4byte 0x00004608
.L08006968: .4byte 0x0000460B
.L0800696C: .4byte 0x00004609
.L08006970:
    movs r2, #0
    ldr r1, .L080069D8 @ =0x00004604
    adds r0, r4, r1
    ldrb r1, [r0]
    cmp r1, #4
    bls .L0800698C
.L0800697C:
    subs r0, r1, #5
    lsls r0, r0, #0x18
    lsrs r1, r0, #0x18
    adds r0, r2, #1
    lsls r0, r0, #0x18
    lsrs r2, r0, #0x18
    cmp r1, #4
    bhi .L0800697C
.L0800698C:
    lsls r1, r2, #2
    adds r1, r1, r2
    lsls r1, r1, #4
    adds r1, #0x18
    ldr r2, .L080069DC @ =0x0000460A
    adds r3, r4, r2
    ldr r2, .L080069E0 @ =0x000001FF
    adds r0, r2, #0
    ands r1, r0
    ldrh r2, [r3]
    ldr r0, .L080069E4 @ =0xFFFFFE00
    ands r0, r2
    orrs r0, r1
    strh r0, [r3]
    ldr r0, .L080069E8 @ =0x00004608
    adds r1, r4, r0
    movs r0, #0x88
    strb r0, [r1]
    ldr r1, .L080069EC @ =0x0000460B
    adds r3, r4, r1
    ldrb r2, [r3]
    movs r1, #0x3f
    adds r0, r1, #0
    ands r0, r2
    movs r2, #0x80
    orrs r0, r2
    strb r0, [r3]
    ldr r0, .L080069F0 @ =0x00004609
    adds r2, r4, r0
    ldrb r0, [r2]
    ands r1, r0
    movs r0, #0x40
.L080069CC:
    orrs r1, r0
    strb r1, [r2]
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L080069D8: .4byte 0x00004604
.L080069DC: .4byte 0x0000460A
.L080069E0: .4byte 0x000001FF
.L080069E4: .4byte 0xFFFFFE00
.L080069E8: .4byte 0x00004608
.L080069EC: .4byte 0x0000460B
.L080069F0: .4byte 0x00004609

    thumb_func_start func_080069F4
func_080069F4: @ 0x080069F4
    push {r4, r5, r6, lr}
    adds r4, r0, #0
    bl func_080088D4
    adds r1, r0, #0
    movs r0, #0x40
    ands r0, r1
    lsls r0, r0, #0x18
    lsrs r6, r0, #0x18
    cmp r6, #0
    beq .L08006A60
    ldr r1, .L08006A54 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xcb
    bl func_08008B6C
    ldr r3, .L08006A58 @ =0x00004605
    adds r2, r4, r3
    ldrb r0, [r2]
    subs r0, #1
    strb r0, [r2]
    lsls r0, r0, #0x18
    cmp r0, #0
    bge .L08006A30
    movs r0, #6
    strb r0, [r2]
    ldr r0, .L08006A5C @ =0x00004604
    adds r1, r4, r0
    movs r0, #0xc
    strb r0, [r1]
.L08006A30:
    ldrb r1, [r2]
    movs r0, #0
    ldrsb r0, [r2, r0]
    cmp r0, #5
    beq .L08006A3C
    b .L08006B8A
.L08006A3C:
    ldr r3, .L08006A5C @ =0x00004604
    adds r0, r4, r3
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #0xc
    bgt .L08006A4C
    b .L08006B8A
.L08006A4C:
    subs r0, r1, #1
    strb r0, [r2]
    b .L08006B8A
    .align 2, 0
.L08006A54: .4byte 0x000045F4
.L08006A58: .4byte 0x00004605
.L08006A5C: .4byte 0x00004604
.L08006A60:
    movs r0, #0x80
    ands r0, r1
    lsls r0, r0, #0x18
    lsrs r5, r0, #0x18
    cmp r5, #0
    beq .L08006AC8
    ldr r1, .L08006ABC @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xcb
    bl func_08008B6C
    ldr r3, .L08006AC0 @ =0x00004605
    adds r1, r4, r3
    ldrb r0, [r1]
    adds r0, #1
    strb r0, [r1]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #6
    ble .L08006A8A
    strb r6, [r1]
.L08006A8A:
    ldrb r2, [r1]
    movs r0, #0
    ldrsb r0, [r1, r0]
    cmp r0, #5
    bne .L08006AA6
    ldr r3, .L08006AC4 @ =0x00004604
    adds r0, r4, r3
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #0xc
    ble .L08006AA6
    adds r0, r2, #1
    strb r0, [r1]
.L08006AA6:
    ldr r1, .L08006AC0 @ =0x00004605
    adds r0, r4, r1
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #6
    bne .L08006B8A
    ldr r3, .L08006AC4 @ =0x00004604
    adds r1, r4, r3
    movs r0, #0xc
    b .L08006B88
    .align 2, 0
.L08006ABC: .4byte 0x000045F4
.L08006AC0: .4byte 0x00004605
.L08006AC4: .4byte 0x00004604
.L08006AC8:
    movs r0, #0x10
    ands r0, r1
    cmp r0, #0
    beq .L08006B2C
    ldr r1, .L08006AF0 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xcb
    bl func_08008B6C
    ldr r0, .L08006AF4 @ =0x00004605
    adds r3, r4, r0
    movs r0, #0
    ldrsb r0, [r3, r0]
    cmp r0, #6
    bne .L08006AFC
    ldr r3, .L08006AF8 @ =0x00004604
    adds r1, r4, r3
    movs r0, #0xc
    b .L08006B88
    .align 2, 0
.L08006AF0: .4byte 0x000045F4
.L08006AF4: .4byte 0x00004605
.L08006AF8: .4byte 0x00004604
.L08006AFC:
    ldr r0, .L08006B1C @ =0x00004604
    adds r1, r4, r0
    ldrb r0, [r1]
    adds r2, r0, #1
    strb r2, [r1]
    movs r0, #0
    ldrsb r0, [r3, r0]
    cmp r0, #5
    bne .L08006B20
    movs r0, #0
    ldrsb r0, [r1, r0]
    cmp r0, #0xc
    ble .L08006B8A
    strb r5, [r1]
    b .L08006B8A
    .align 2, 0
.L08006B1C: .4byte 0x00004604
.L08006B20:
    lsls r0, r2, #0x18
    asrs r0, r0, #0x18
    cmp r0, #0xe
    ble .L08006B8A
    strb r5, [r1]
    b .L08006B8A
.L08006B2C:
    movs r0, #0x20
    ands r0, r1
    cmp r0, #0
    beq .L08006B8A
    ldr r1, .L08006B54 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xcb
    bl func_08008B6C
    ldr r0, .L08006B58 @ =0x00004605
    adds r3, r4, r0
    movs r0, #0
    ldrsb r0, [r3, r0]
    cmp r0, #6
    bne .L08006B60
    ldr r3, .L08006B5C @ =0x00004604
    adds r1, r4, r3
    movs r0, #0xc
    b .L08006B88
    .align 2, 0
.L08006B54: .4byte 0x000045F4
.L08006B58: .4byte 0x00004605
.L08006B5C: .4byte 0x00004604
.L08006B60:
    ldr r0, .L08006B7C @ =0x00004604
    adds r1, r4, r0
    ldrb r0, [r1]
    subs r2, r0, #1
    strb r2, [r1]
    movs r0, #0
    ldrsb r0, [r3, r0]
    cmp r0, #5
    bne .L08006B80
    lsls r0, r2, #0x18
    cmp r0, #0
    bge .L08006B8A
    movs r0, #0xc
    b .L08006B88
    .align 2, 0
.L08006B7C: .4byte 0x00004604
.L08006B80:
    lsls r0, r2, #0x18
    cmp r0, #0
    bge .L08006B8A
    movs r0, #0xe
.L08006B88:
    strb r0, [r1]
.L08006B8A:
    pop {r4, r5, r6}
    pop {r0}
    bx r0

    thumb_func_start func_08006B90
func_08006B90: @ 0x08006B90
    push {r4, r5, lr}
    sub sp, #4
    adds r5, r0, #0
    mov r4, sp
    ldr r3, .L08006BDC @ =gUnk_080E89B6
    ldr r1, .L08006BE0 @ =0x00004604
    adds r0, r5, r1
    movs r1, #0
    ldrsb r1, [r0, r1]
    lsls r1, r1, #1
    ldr r2, .L08006BE4 @ =0x00004605
    adds r0, r5, r2
    movs r2, #0
    ldrsb r2, [r0, r2]
    lsls r0, r2, #5
    subs r0, r0, r2
    adds r1, r1, r0
    movs r2, #0x8c
    lsls r2, r2, #7
    adds r0, r5, r2
    ldr r2, [r0]
    movs r0, #0xba
    muls r0, r2, r0
    adds r1, r1, r0
    adds r1, r1, r3
    ldrb r1, [r1]
    strb r1, [r4]
    ldr r3, .L08006BE8 @ =0x00004610
    adds r2, r5, r3
    ldrb r4, [r2]
    adds r3, #0xc
    adds r0, r5, r3
    adds r3, r0, r4
    ldrb r0, [r3]
    cmp r0, r1
    bne .L08006BEC
    adds r0, r4, #1
    b .L08006BF2
    .align 2, 0
.L08006BDC: .4byte gUnk_080E89B6
.L08006BE0: .4byte 0x00004604
.L08006BE4: .4byte 0x00004605
.L08006BE8: .4byte 0x00004610
.L08006BEC:
    strb r1, [r3]
    ldrb r0, [r2]
    adds r0, #1
.L08006BF2:
    strb r0, [r2]
    ldr r0, .L08006C1C @ =0x00004610
    adds r2, r5, r0
    ldrb r0, [r2]
    cmp r0, #0xb
    bls .L08006C12
    ldr r3, .L08006C20 @ =0x00004604
    adds r1, r5, r3
    movs r0, #0xc
    strb r0, [r1]
    ldr r0, .L08006C24 @ =0x00004605
    adds r1, r5, r0
    movs r0, #6
    strb r0, [r1]
    movs r0, #0xb
    strb r0, [r2]
.L08006C12:
    add sp, #4
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L08006C1C: .4byte 0x00004610
.L08006C20: .4byte 0x00004604
.L08006C24: .4byte 0x00004605

    thumb_func_start func_08006C28
func_08006C28: @ 0x08006C28
    push {r4, lr}
    adds r4, r0, #0
    lsls r1, r1, #0x18
    lsrs r1, r1, #0x18
    cmp r1, #0xa
    bhi .L08006C4A
    ldr r0, .L08006C58 @ =0x0000461C
    adds r3, r4, r0
.L08006C38:
    adds r2, r3, r1
    adds r1, #1
    adds r0, r3, r1
    ldrb r0, [r0]
    strb r0, [r2]
    lsls r1, r1, #0x18
    lsrs r1, r1, #0x18
    cmp r1, #0xa
    bls .L08006C38
.L08006C4A:
    ldr r0, .L08006C5C @ =0x00004627
    adds r1, r4, r0
    movs r0, #0x5f
    strb r0, [r1]
    pop {r4}
    pop {r0}
    bx r0
    .align 2, 0
.L08006C58: .4byte 0x0000461C
.L08006C5C: .4byte 0x00004627

    thumb_func_start func_08006C60
func_08006C60: @ 0x08006C60
    push {r4, r5, r6, r7, lr}
    adds r7, r0, #0
    movs r6, #0
    movs r5, #0
    ldr r0, .L08006C88 @ =0x00004629
    adds r4, r7, r0
    subs r0, #0xd
    adds r1, r7, r0
    adds r0, r4, #0
    bl strcpy
    movs r1, #0
.L08006C78:
    adds r0, r4, r1
    ldrb r0, [r0]
    cmp r0, #0x5f
    bne .L08006C8C
    adds r5, #1
    adds r0, r1, #1
    b .L08006C96
    .align 2, 0
.L08006C88: .4byte 0x00004629
.L08006C8C:
    cmp r0, #0x20
    bne .L08006C92
    adds r5, #1
.L08006C92:
    adds r6, r1, #1
    adds r0, r6, #0
.L08006C96:
    adds r1, r0, #0
    cmp r1, #0xb
    ble .L08006C78
    cmp r5, #0xc
    bne .L08006CA4
    movs r6, #0
    b .L08006CC0
.L08006CA4:
    movs r2, #0
    cmp r2, r6
    bge .L08006CC0
    ldr r1, .L08006CD8 @ =0x00004629
    adds r3, r7, r1
    movs r4, #0x20
.L08006CB0:
    adds r1, r3, r2
    ldrb r0, [r1]
    cmp r0, #0x5f
    bne .L08006CBA
    strb r4, [r1]
.L08006CBA:
    adds r2, #1
    cmp r2, r6
    blt .L08006CB0
.L08006CC0:
    ldr r1, .L08006CD8 @ =0x00004629
    adds r0, r7, r1
    adds r0, r0, r6
    movs r1, #0
    strb r1, [r0]
    rsbs r0, r6, #0
    orrs r0, r6
    lsrs r0, r0, #0x1f
    pop {r4, r5, r6, r7}
    pop {r1}
    bx r1
    .align 2, 0
.L08006CD8: .4byte 0x00004629

    thumb_func_start func_08006CDC
func_08006CDC: @ 0x08006CDC
    push {r4, r5, r6, r7, lr}
    sub sp, #4
    adds r4, r0, #0
    ldr r0, .L08006D2C @ =0x0000463C
    adds r5, r4, r0
    ldr r6, [r5]
    cmp r6, #0
    beq .L08006CEE
    b .L08006EC8
.L08006CEE:
    adds r0, r4, #0
    bl func_080069F4
    adds r0, r4, #0
    bl func_080088D4
    str r0, [sp]
    mov r0, sp
    ldrb r1, [r0]
    movs r7, #1
    adds r0, r7, #0
    ands r0, r1
    cmp r0, #0
    beq .L08006DA6
    ldr r1, .L08006D30 @ =0x00004605
    adds r0, r4, r1
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #5
    bgt .L08006D34
    subs r1, #0x11
    adds r0, r4, r1
    movs r1, #0x6a
    bl func_08008B6C
    adds r0, r4, #0
    bl func_08006B90
    b .L08006EC8
    .align 2, 0
.L08006D2C: .4byte 0x0000463C
.L08006D30: .4byte 0x00004605
.L08006D34:
    ldr r1, .L08006D54 @ =0x00004604
    adds r0, r4, r1
    ldrb r1, [r0]
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #4
    bgt .L08006D5C
    movs r0, #0x8c
    lsls r0, r0, #7
    adds r1, r4, r0
    ldr r0, [r1]
    cmp r0, #2
    bne .L08006D58
    str r6, [r1]
    b .L08006D7A
    .align 2, 0
.L08006D54: .4byte 0x00004604
.L08006D58:
    adds r0, #1
    b .L08006D78
.L08006D5C:
    subs r0, r1, #5
    lsls r0, r0, #0x18
    lsrs r0, r0, #0x18
    cmp r0, #4
    bhi .L08006D98
    movs r0, #0x8c
    lsls r0, r0, #7
    adds r1, r4, r0
    ldr r0, [r1]
    cmp r0, #0
    bne .L08006D76
    movs r0, #2
    b .L08006D78
.L08006D76:
    subs r0, #1
.L08006D78:
    str r0, [r1]
.L08006D7A:
    ldr r1, .L08006D90 @ =0x00004637
    adds r0, r4, r1
    movs r1, #1
    strb r1, [r0]
    ldr r1, .L08006D94 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xca
    bl func_08008B6C
    b .L08006EC8
    .align 2, 0
.L08006D90: .4byte 0x00004637
.L08006D94: .4byte 0x000045F4
.L08006D98:
    adds r0, r4, #0
    bl func_08006C60
    lsls r0, r0, #0x18
    cmp r0, #0
    bne .L08006E48
    b .L08006DE8
.L08006DA6:
    movs r2, #2
    adds r0, r2, #0
    ands r0, r1
    cmp r0, #0
    beq .L08006E14
    ldr r0, .L08006DC4 @ =0x00004610
    adds r1, r4, r0
    ldrb r0, [r1]
    cmp r0, #0
    beq .L08006DC8
    subs r0, #1
    strb r0, [r1]
    ldrb r1, [r1]
    adds r0, r4, #0
    b .L08006E00
    .align 2, 0
.L08006DC4: .4byte 0x00004610
.L08006DC8:
    movs r2, #0
    movs r1, #0
    ldr r0, .L08006DF4 @ =0x0000461C
    adds r3, r4, r0
.L08006DD0:
    adds r0, r3, r1
    ldrb r0, [r0]
    cmp r0, #0x5f
    bne .L08006DDE
    adds r0, r2, #1
    lsls r0, r0, #0x18
    lsrs r2, r0, #0x18
.L08006DDE:
    adds r1, #1
    cmp r1, #0xb
    ble .L08006DD0
    cmp r2, #0xc
    bne .L08006DFC
.L08006DE8:
    ldr r1, .L08006DF8 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xc7
    bl func_08008B6C
    b .L08006EC8
    .align 2, 0
.L08006DF4: .4byte 0x0000461C
.L08006DF8: .4byte 0x000045F4
.L08006DFC:
    adds r0, r4, #0
    movs r1, #0
.L08006E00:
    bl func_08006C28
    ldr r1, .L08006E10 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0x6c
    bl func_08008B6C
    b .L08006EC8
    .align 2, 0
.L08006E10: .4byte 0x000045F4
.L08006E14:
    movs r0, #8
    ands r0, r1
    cmp r0, #0
    beq .L08006E78
    ldr r1, .L08006E58 @ =0x00004605
    adds r0, r4, r1
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #6
    bne .L08006E60
    subs r1, #1
    adds r0, r4, r1
    ldrb r0, [r0]
    lsls r0, r0, #0x18
    asrs r0, r0, #0x18
    cmp r0, #9
    ble .L08006E60
    cmp r0, #0xe
    bgt .L08006E60
    adds r0, r4, #0
    bl func_08006C60
    lsls r0, r0, #0x18
    cmp r0, #0
    beq .L08006E4A
.L08006E48:
    str r7, [r5]
.L08006E4A:
    ldr r1, .L08006E5C @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xc5
    bl func_08008B6C
    b .L08006EC8
    .align 2, 0
.L08006E58: .4byte 0x00004605
.L08006E5C: .4byte 0x000045F4
.L08006E60:
    ldr r0, .L08006E70 @ =0x00004604
    adds r1, r4, r0
    movs r0, #0xc
    strb r0, [r1]
    ldr r0, .L08006E74 @ =0x00004605
    adds r1, r4, r0
    movs r0, #6
    b .L08006E90
    .align 2, 0
.L08006E70: .4byte 0x00004604
.L08006E74: .4byte 0x00004605
.L08006E78:
    mov r0, sp
    ldrb r1, [r0, #1]
    adds r0, r2, #0
    ands r0, r1
    cmp r0, #0
    beq .L08006EA8
    ldr r0, .L08006EA0 @ =0x00004610
    adds r1, r4, r0
    ldrb r0, [r1]
    cmp r0, #0
    beq .L08006E92
    subs r0, #1
.L08006E90:
    strb r0, [r1]
.L08006E92:
    ldr r1, .L08006EA4 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xcb
    bl func_08008B6C
    b .L08006EC8
    .align 2, 0
.L08006EA0: .4byte 0x00004610
.L08006EA4: .4byte 0x000045F4
.L08006EA8:
    adds r0, r7, #0
    ands r0, r1
    cmp r0, #0
    beq .L08006EC8
    ldr r0, .L08006ED0 @ =0x00004610
    adds r1, r4, r0
    ldrb r0, [r1]
    cmp r0, #0xb
    beq .L08006EBE
    adds r0, #1
    strb r0, [r1]
.L08006EBE:
    ldr r1, .L08006ED4 @ =0x000045F4
    adds r0, r4, r1
    movs r1, #0xcb
    bl func_08008B6C
.L08006EC8:
    add sp, #4
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L08006ED0: .4byte 0x00004610
.L08006ED4: .4byte 0x000045F4

    thumb_func_start func_08006ED8
func_08006ED8: @ 0x08006ED8
    push {r4, r5, r6, r7, lr}
    mov r7, sl
    mov r6, sb
    mov r5, r8
    push {r5, r6, r7}
    sub sp, #0xc
    adds r7, r0, #0
    ldr r1, .L08006F50 @ =0x0000463C
    adds r0, r7, r1
    ldr r0, [r0]
    cmp r0, #0
    bne .L08006EF2
    b .L08007064
.L08006EF2:
    ldr r2, .L08006F54 @ =0x000045F8
    adds r4, r7, r2
    ldr r0, [r4]
    bl func_08050D34
    adds r6, r0, #0
    ldr r4, [r4]
    mov sb, r4
    adds r0, r7, #0
    bl func_080088DC
    mov r8, r0
    adds r0, r7, #0
    bl func_08008920
    mov sl, r0
    adds r0, r7, #0
    bl func_08008918
    adds r5, r0, #0
    adds r0, r7, #0
    bl func_08008940
    adds r4, r0, #0
    adds r0, r7, #0
    bl func_0800894C
    ldr r2, .L08006F58 @ =0x000045F0
    adds r1, r7, r2
    str r4, [sp]
    str r0, [sp, #4]
    str r1, [sp, #8]
    mov r0, sb
    mov r1, r8
    mov r2, sl
    adds r3, r5, #0
    bl func_08050D3C
    cmp r0, #6
    bls .L08006F44
    b .L08007064
.L08006F44:
    lsls r0, r0, #2
    ldr r1, .L08006F5C @ =.L08006F60
    adds r0, r0, r1
    ldr r0, [r0]
    mov pc, r0
    .align 2, 0
.L08006F50: .4byte 0x0000463C
.L08006F54: .4byte 0x000045F8
.L08006F58: .4byte 0x000045F0
.L08006F5C: .4byte .L08006F60
.L08006F60: @ jump table
    .4byte .L08006F7C @ case 0
    .4byte .L08007064 @ case 1
    .4byte .L08007064 @ case 2
    .4byte .L08006FD8 @ case 3
    .4byte .L08007064 @ case 4
    .4byte .L08007064 @ case 5
    .4byte .L08007064 @ case 6
.L08006F7C:
    ldr r0, .L08006FC0 @ =0x00004638
    adds r2, r7, r0
    ldrb r0, [r2]
    cmp r0, #0
    beq .L08006F90
    ldr r0, .L08006FC4 @ =0x0000463C
    adds r1, r7, r0
    movs r0, #0
    str r0, [r1]
    strb r0, [r2]
.L08006F90:
    ldr r2, .L08006FC8 @ =0x00004639
    adds r1, r7, r2
    ldrb r0, [r1]
    cmp r0, #0
    beq .L08006FB2
    movs r0, #0
    strb r0, [r1]
    ldr r0, .L08006FCC @ =0x00004636
    adds r1, r7, r0
    movs r0, #1
    strb r0, [r1]
    ldr r1, .L08006FD0 @ =0x0000461C
    adds r0, r7, r1
    subs r2, #0x10
    adds r1, r7, r2
    bl strcpy
.L08006FB2:
    ldr r1, .L08006FD4 @ =0x000045F8
    adds r0, r7, r1
    ldr r0, [r0]
    bl func_08050D5C
    b .L08007064
    .align 2, 0
.L08006FC0: .4byte 0x00004638
.L08006FC4: .4byte 0x0000463C
.L08006FC8: .4byte 0x00004639
.L08006FCC: .4byte 0x00004636
.L08006FD0: .4byte 0x0000461C
.L08006FD4: .4byte 0x000045F8
.L08006FD8:
    cmp r6, #5
    bgt .L08006FE6
    cmp r6, #4
    bge .L08007064
    cmp r6, #1
    beq .L08006FFC
    b .L08006FEA
.L08006FE6:
    cmp r6, #6
    beq .L08007034
.L08006FEA:
    ldr r2, .L08006FF8 @ =0x000045F8
    adds r0, r7, r2
    ldr r0, [r0]
    bl func_08050D74
    b .L08007064
    .align 2, 0
.L08006FF8: .4byte 0x000045F8
.L08006FFC:
    ldr r1, .L08007020 @ =0x0000463C
    adds r0, r7, r1
    ldr r0, [r0]
    cmp r0, #1
    bne .L08007064
    ldr r2, .L08007024 @ =0x000045F8
    adds r0, r7, r2
    ldr r0, [r0]
    ldr r1, .L08007028 @ =gUnk_080E8C2C
    ldr r2, .L0800702C @ =gUnk_080E8C44
    ldr r3, .L08007030 @ =gUnk_080E8C48
    movs r4, #0
    str r4, [sp]
    str r4, [sp, #4]
    str r4, [sp, #8]
    bl func_08050E30
    b .L08007064
    .align 2, 0
.L08007020: .4byte 0x0000463C
.L08007024: .4byte 0x000045F8
.L08007028: .4byte gUnk_080E8C2C
.L0800702C: .4byte gUnk_080E8C44
.L08007030: .4byte gUnk_080E8C48
.L08007034:
    ldr r1, .L0800704C @ =0x000045F8
    adds r0, r7, r1
    ldr r0, [r0]
    bl func_08050DF0
    adds r2, r0, #0
    cmp r2, #1
    beq .L08007050
    cmp r2, #2
    beq .L0800705C
    b .L08007064
    .align 2, 0
.L0800704C: .4byte 0x000045F8
.L08007050:
    ldr r1, .L08007058 @ =0x00004639
    adds r0, r7, r1
    strb r2, [r0]
    b .L08007064
    .align 2, 0
.L08007058: .4byte 0x00004639
.L0800705C:
    ldr r2, .L08007074 @ =0x00004638
    adds r1, r7, r2
    movs r0, #1
    strb r0, [r1]
.L08007064:
    add sp, #0xc
    pop {r3, r4, r5}
    mov r8, r3
    mov sb, r4
    mov sl, r5
    pop {r4, r5, r6, r7}
    pop {r0}
    bx r0
    .align 2, 0
.L08007074: .4byte 0x00004638

    thumb_func_start func_08007078
func_08007078: @ 0x08007078
    push {r4, r5, r6, lr}
    adds r4, r0, #0
    adds r5, r1, #0
    adds r6, r2, #0
    ldr r0, .L0800709C @ =vtable_unk_080E5AC0
    str r0, [r4]
    ldr r0, .L080070A0 @ =0x00004640
    bl __builtin_new
    adds r1, r5, #0
    adds r2, r6, #0
    bl func_08005A58
    str r0, [r4, #4]
    adds r0, r4, #0
    pop {r4, r5, r6}
    pop {r1}
    bx r1
    .align 2, 0
.L0800709C: .4byte vtable_unk_080E5AC0
.L080070A0: .4byte 0x00004640

    thumb_func_start func_080070A4
func_080070A4: @ 0x080070A4
    push {r4, r5, lr}
    adds r4, r0, #0
    adds r5, r1, #0
    ldr r0, .L080070D0 @ =vtable_unk_080E5AC0
    str r0, [r4]
    ldr r1, [r4, #4]
    cmp r1, #0
    beq .L080070C0
    ldr r0, [r1, #4]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L080070C0:
    adds r0, r4, #0
    adds r1, r5, #0
    bl func_080007EC
    pop {r4, r5}
    pop {r0}
    bx r0
    .align 2, 0
.L080070D0: .4byte vtable_unk_080E5AC0

    thumb_func_start func_080070D4
func_080070D4: @ 0x080070D4
    push {r4, lr}
    sub sp, #0xc
    adds r4, r0, #0
    ldr r1, [r1, #4]
    mov r0, sp
    bl func_08005B68
    ldr r2, [sp]
    mov r0, sp
    str r0, [sp, #4]
    str r2, [sp, #8]
    adds r1, r0, #0
    movs r0, #0
    str r0, [r1]
    str r2, [r4]
    ldr r1, [sp]
    cmp r1, #0
    beq .L08007104
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08007104:
    adds r0, r4, #0
    add sp, #0xc
    pop {r4}
    pop {r1}
    bx r1
    .align 2, 0

    thumb_func_start func_08007110
func_08007110: @ 0x08007110
    ldr r0, [r0, #4]
    ldr r1, .L08007118 @ =0x0000461C
    adds r0, r0, r1
    bx lr
    .align 2, 0
.L08007118: .4byte 0x0000461C
.L0800711C:
    .byte 0x01, 0x49, 0x40, 0x18
    .byte 0x70, 0x47, 0x00, 0x00, 0x1C, 0x46, 0x00, 0x00
