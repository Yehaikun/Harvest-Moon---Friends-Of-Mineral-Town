#!/usr/bin/env python3
"""NPC schedule inspector. Usage: python3 inspect_npcs.py fomt.gba"""
import struct, sys
from pathlib import Path

rom = bytearray(Path(sys.argv[1]).read_bytes())

SCHEDULES = {
    0x080F1A80: "ScheduleInfo_Unk_080F1A80",
    0x080F280C: "gUnk_080F280C",
}

def dump(addr):
    off = addr & 0x1FFFFFF
    fn = struct.unpack_from('<I', rom, off)[0]
    cnt = struct.unpack_from('<I', rom, off+4)[0]
    tbl = struct.unpack_from('<I', rom, off+8)[0]
    print(f"\n=== {SCHEDULES.get(addr, hex(addr))} ===")
    print(f"  selector=0x{fn:08X}, {cnt} schedules, table=0x{tbl:08X}")
    if cnt < 1 or cnt > 50 or not tbl:
        return
    toff = tbl & 0x1FFFFFF
    for i in range(cnt):
        sa = struct.unpack_from('<I', rom, toff + i*4)[0]
        if not sa:
            continue
        soff = sa & 0x1FFFFFF
        num = struct.unpack_from('<H', rom, soff)[0]
        eptr = struct.unpack_from('<I', rom, soff+4)[0]
        print(f"\n  Schedule[{i}]: {num} entries @ 0x{eptr:08X}")
        for j in range(min(num, 5)):
            eo = (eptr & 0x1FFFFFF) + j*8
            t = struct.unpack_from('<H', rom, eo)[0]
            pp = struct.unpack_from('<I', rom, eo+4)[0]
            po = pp & 0x1FFFFFF
            np = struct.unpack_from('<H', rom, po)[0]
            x = struct.unpack_from('<h', rom, po+2)[0]
            y = struct.unpack_from('<h', rom, po+4)[0]
            print(f"    time={t:4d}: ({x:4d},{y:4d}) {np} pts")
        if num > 5:
            print(f"    ... ({num-5} more entries)")

for addr in SCHEDULES:
    dump(addr)
