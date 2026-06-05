#!/usr/bin/env python3
"""List all NPC entity creation functions with their schedule/anim/vtable."""
import re

with open('asm/code_entities_08034CEC.s') as f:
    asm = f.read()

sections = asm.split('thumb_func_start ')
for sec in sections:
    if '__10ANpcEntity' not in sec:
        continue
    func_name = sec.split('\n')[0].strip()
    sc = re.search(r'ldr r0, .L[0-9A-F]+ @ =(gUnk_|ScheduleInfo_)([^\s]+)', sec)
    an = re.search(r'ldr r0, .L[0-9A-F]+ @ =0x([0-9A-F]+)', sec)
    vt = re.search(r'ldr r0, .L[0-9A-F]+ @ =(vtable_[^\s]+)', sec)
    sched = sc.group(2) if sc else '?'
    anim = int(an.group(1), 16) if an else 0
    vtable = vt.group(1) if vt else '?'
    print(f"{func_name:30s} anim=0x{anim:04X} ({anim:5d}) sched={sched:25s} {vtable}")
