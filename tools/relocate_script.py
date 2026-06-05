#!/usr/bin/env python3
"""Relocate a script to free space for unlimited dialogue.

When a script's text is too long for its original slot, this tool
moves the entire script to free space and updates the script table.
"""
import struct, sys
from pathlib import Path

rom = bytearray(Path(sys.argv[1]).read_bytes())
SCRIPT_TABLE = 0x0F89D4
FREE_START = 0x75C244
FREE_END = 0x2000000

def relocate(sid):
    """Move script `sid` to free space so it can be larger."""
    entry_off = SCRIPT_TABLE + (sid - 1) * 4
    old_ptr = struct.unpack_from('<I', rom, entry_off)[0]
    if old_ptr == 0:
        print(f"Script {sid}: empty slot"); return

    file_off = old_ptr & 0x1FFFFFF
    if rom[file_off:file_off+4] != b'RIFF':
        print(f"Script {sid}: not RIFF format"); return

    total_size = struct.unpack_from('<I', rom, file_off+4)[0] + 8

    # Find free space large enough
    offset = FREE_START
    found = False
    while offset + total_size <= FREE_END:
        if all(b == 0xFF for b in rom[offset:offset + total_size]):
            found = True
            break
        offset += 4

    if not found:
        print(f"Script {sid}: no free space for {total_size}B"); return

    # Copy script to free space
    rom[offset:offset + total_size] = rom[file_off:file_off + total_size]
    new_ptr = 0x08000000 | offset
    struct.pack_into('<I', rom, entry_off, new_ptr)
    print(f"Script {sid}: 0x{old_ptr:08X} -> 0x{new_ptr:08X} ({total_size}B)")
    return offset

if __name__ == '__main__':
    if '--script' in sys.argv:
        i = sys.argv.index('--script')
        sid = int(sys.argv[i+1])
        relocate(sid)
        Path(sys.argv[1]).write_bytes(bytes(rom))
        print("Saved!")
    else:
        print("Usage: --script N to relocate, then --extend SIZE")
        for sid in [1, 167, 143]:
            relocate(sid)
        Path(sys.argv[1]).write_bytes(bytes(rom))
