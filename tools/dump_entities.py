#!/usr/bin/env python3
"""Dump entity data for each map from the entity function table."""
import struct, sys
from pathlib import Path

rom = bytearray(Path(sys.argv[1]).read_bytes())

TABLE_ADDR = 0x080E602C

print("Map | Handler     | Type\n" + "-"*50)
for mid in range(66):
    off = (TABLE_ADDR & 0x1FFFFFF) + mid*4
    ptr = struct.unpack_from('<I', rom, off)[0]
    note = "NONE"
    if ptr == 0x08000639:
        note = "empty"
    elif ptr:
        # Check what type of handler by looking at first instruction
        fn_off = (ptr & ~1) - 0x08000000
        if fn_off < len(rom):
            first = struct.unpack_from('<H', rom, fn_off)[0]
            if first == 0xb500:  # PUSH {LR}
                note = "simple init"
            elif first == 0xb530:  # PUSH {R4,R5,LR}
                note = "complex init"
            else:
                note = f"code 0x{first:04x}"
    if ptr:
        print(f"  {mid:2d} | 0x{ptr:08X} | {note}")
