    .INCLUDE "asm/macro.inc"
    .SYNTAX UNIFIED

    thumb_func_start AgbMain
AgbMain: @ 0x0800018C
    push {r4, lr}
    sub sp, #0x1c
    ldr r1, .L08000228 @ =0x04000204
    ldr r2, .L0800022C @ =0x00004014
    adds r0, r2, #0
    strh r0, [r1]
    bl func_080004C4
    ldr r1, .L08000230 @ =func_03000490
    movs r0, #0xd
    bl func_080D100C
    movs r0, #0x80
    lsls r0, r0, #6
    bl func_0800050C
    add r4, sp, #0xc
    adds r0, r4, #0
    bl func_08000640
    adds r0, r4, #0
    bl func_080002E0
    lsls r0, r0, #0x18
    cmp r0, #0
    bne .L080001C6
    adds r0, r4, #0
    bl func_08000358
.L080001C6:
    ldr r1, .L08000234 @ =func_08000240
    movs r0, #0xc
    bl func_080D100C
    ldr r1, .L08000238 @ =0x04000132
    ldr r2, .L0800023C @ =0x0000C00F
    adds r0, r2, #0
    strh r0, [r1]
    movs r0, #0x80
    lsls r0, r0, #5
    bl func_0800050C
    bl func_08008AFC
    mov r0, sp
    bl func_08008980
    movs r0, #8
    bl __builtin_new
    bl func_080036F8
    add r1, sp, #8
    str r1, [sp, #0x14]
    str r0, [sp, #0x18]
    movs r1, #0
    str r1, [sp, #8]
    str r0, [sp, #4]
    add r0, sp, #4
    bl func_0800082C
    ldr r1, [sp, #8]
    cmp r1, #0
    beq .L08000216
    ldr r0, [r1]
    ldr r2, [r0, #8]
    adds r0, r1, #0
    movs r1, #3
    bl _call_via_r2
.L08000216:
    mov r0, sp
    movs r1, #2
    bl func_08008A68
    add sp, #0x1c
    pop {r4}
    pop {r0}
    bx r0
    .align 2, 0
.L08000228: .4byte 0x04000204
.L0800022C: .4byte 0x00004014
.L08000230: .4byte func_03000490
.L08000234: .4byte func_08000240
.L08000238: .4byte 0x04000132
.L0800023C: .4byte 0x0000C00F
