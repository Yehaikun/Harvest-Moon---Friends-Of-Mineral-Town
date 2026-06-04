#!/usr/bin/env python3
"""Patch script 143 to warp to farm (map 2) instead of its original destination."""
import struct
from pathlib import Path

rom = bytearray(Path('fomt.gba').read_bytes())

# Find script 143 pointer
SCRIPT_TABLE = 0x0F89D4
entry_off = SCRIPT_TABLE + (143 - 1) * 4
ptr = struct.unpack_from('<I', rom, entry_off)[0]
file_off = ptr & 0x1FFFFFF

# Read CODE chunk
pos = file_off + 12  # Skip RIFF header (8) + type (4)
while pos < len(rom) - 8:
    ctype = bytes(rom[pos:pos+4])
    csize = struct.unpack_from('<I', rom, pos+4)[0]
    if ctype == b'CODE':
        code_start = pos + 8
        code = rom[code_start:code_start + csize]

        # Find Mary-format Proc016: 23 ?? 22 ?? ?? 22 ?? ?? 21 16
        for i in range(len(code) - 8):
            if code[i] == 0x23 and i+8 < len(code):
                if code[i+4] == 0x22 and code[i+7] == 0x21 and code[i+8] == 0x16:
                    # Proc016 found!
                    map_id_byte = code[i+1]
                    old_map = map_id_byte
                    rom[code_start + i + 1] = 2  # Change to map 2 (farm)
                    print(f"Script 143: patched map {old_map} -> 2 at ROM 0x{code_start+i+1:06X}")
                    break
        break
    pos += 8 + csize
    if pos % 2:
        pos += 1

Path('fomt.gba').write_bytes(bytes(rom))
print("Done")
