    .INCLUDE "asm/macro.inc"
    .SYNTAX UNIFIED

    thumb_func_start func_080004F4
func_080004F4: @ 0x080004F4
    push {lr}
    lsls r0, r0, #0x10
    ldr r1, .L08000508 @ =func_03000A1C
    bl _call_via_r1
    lsls r0, r0, #0x10
    lsrs r0, r0, #0x10
    pop {r1}
    bx r1
    .align 2, 0
.L08000508: .4byte func_03000A1C

    thumb_func_start func_0800050C
func_0800050C: @ 0x0800050C
    push {lr}
    lsls r0, r0, #0x10
    lsrs r0, r0, #0x10
    ldr r1, .L08000524 @ =0x04000202
    strh r0, [r1]
    bl func_080004F4
    lsls r0, r0, #0x10
    lsrs r0, r0, #0x10
    pop {r1}
    bx r1
    .align 2, 0
.L08000524: .4byte 0x04000202

    thumb_func_start func_08000528
func_08000528: @ 0x08000528
    push {lr}
    lsls r0, r0, #0x10
    lsrs r0, r0, #0x10
    ldr r1, .L0800053C @ =func_03000A1C
    bl _call_via_r1
    lsls r0, r0, #0x10
    lsrs r0, r0, #0x10
    pop {r1}
    bx r1
    .align 2, 0
.L0800053C: .4byte func_03000A1C

    thumb_func_start func_08000540
func_08000540: @ 0x08000540
    push {lr}
    lsls r1, r1, #0x10
    lsrs r1, r1, #0x10
    bl func_080D101C
    lsls r0, r0, #0x10
    lsrs r0, r0, #0x10
    pop {r1}
    bx r1
    .align 2, 0
.L08000554:
    .byte 0x00, 0xB5, 0x01, 0x1C, 0x09, 0x04, 0x09, 0x0C, 0x00, 0x20, 0xD3, 0xF0
    .byte 0xF9, 0xF8, 0x01, 0xBC, 0x00, 0x47, 0x00, 0x00

    thumb_func_start func_08000568
func_08000568: @ 0x08000568
    push {lr}
    adds r1, r0, #0
    lsls r1, r1, #0x10
    lsrs r1, r1, #0x10
    movs r0, #1
    bl IntrWait
    pop {r0}
    bx r0
    .align 2, 0
.L0800057C:
    .byte 0x08, 0x1C, 0x70, 0x47
    .byte 0x08, 0x1C, 0x70, 0x47, 0x00, 0xB5, 0x00, 0xF0, 0x25, 0xF8, 0x02, 0xBC, 0x08, 0x47, 0x00, 0x00
    .byte 0x00, 0xB5, 0x00, 0xF0, 0x39, 0xF8, 0x01, 0xBC, 0x00, 0x47, 0x00, 0x00
