#!/usr/bin/env python3
"""Patch entity function table to give map 63 farm's entities (for testing)."""
import struct
from pathlib import Path

TABLE_ADDR = 0x080E602C
TABLE_OFF = TABLE_ADDR & 0x1FFFFFF

rom = bytearray(Path('fomt.gba').read_bytes())

# Copy map 2's entity handler (0x080DC5A9) to map 63's slot
map2_val = struct.unpack_from('<I', rom, TABLE_OFF + 2*4)[0]
struct.pack_into('<I', rom, TABLE_OFF + 63*4, map2_val)
print(f"Entity patch: map 63 <- map 2 handler (0x{map2_val:08X})")

Path('fomt.gba').write_bytes(bytes(rom))
print("Done")
